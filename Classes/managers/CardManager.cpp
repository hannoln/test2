#include "CardManager.h"

void CardManager::initFromJson(const std::string& filename, CardAreaView* mainCardArea)
{

	//  读取文件
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string content = FileUtils::getInstance()->getStringFromFile(filePath);

	//  解析 JSON
	rapidjson::Document doc;
	doc.Parse(content.c_str());
	if (doc.HasParseError()) return;

	if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
	{
		const rapidjson::Value& playfield = doc["Playfield"];

		for (rapidjson::SizeType i = 0; i < playfield.Size(); ++i)
		{
			const  rapidjson::Value& cardData = playfield[i];
			const int face = cardData["CardFace"].GetInt();
			const int suit = cardData["CardSuit"].GetInt();
			float x = cardData["Position"]["x"].GetFloat();
			float y = cardData["Position"]["y"].GetFloat();

			CardModel* model = new CardModel((CardFaceType)face, (CardSuitType)suit, true);
			// 创建 View
			model->isTopAreaCard = true;
			CardView* view = CardView::create(model);
			view->setPosition(Vec2(x, y));
			// 添加到主牌区
			mainCardArea->addChild(view);

			view->_onTableCardClicked = [this, mainCardArea](CardView* clickedView) {
				this->handleTableCardChange(clickedView, mainCardArea);
				};
		}
	}

}


void CardManager::initHandCard(const std::string& filename, CardAreaView* mainCardArea)
{

	//  读取文件
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string content = FileUtils::getInstance()->getStringFromFile(filePath);

	//  解析 JSON
	rapidjson::Document doc;
	doc.Parse(content.c_str());
	if (doc.HasParseError()) return;

	if (doc.HasMember("Stack") && doc["Stack"].IsArray())
	{
		const rapidjson::Value& playfield = doc["Stack"];

		for (rapidjson::SizeType i = 0; i < playfield.Size(); ++i)
		{
			const  rapidjson::Value& cardData = playfield[i];
			const int face = cardData["CardFace"].GetInt();
			const int suit = cardData["CardSuit"].GetInt();
			float x = cardData["Position"]["x"].GetFloat();
			float y = cardData["Position"]["y"].GetFloat();


			// 创建 Model
			CardModel* model = new CardModel((CardFaceType)face, (CardSuitType)suit, true);
			model->isInHand = true;//
			// 创建 View
			CardView* view = CardView::create(model);

			view->setAnchorPoint(Vec2(0.5f, 0.5f));
			if (i != playfield.Size() - 1)
				view->setPosition(Vec2(200 + i * 100, 270));
			if (i == playfield.Size() - 1) {
				view->setPosition(Vec2(800, 270));
				_handCardview = view;//记录一下第一张手牌，等会删除
			}
			_stack.push_back(model);
			// 添加到主牌区
			mainCardArea->addChild(view);

			view->_onClicked = [this, mainCardArea](CardView* clickedView) {
				this->handleHandCardChange(clickedView, mainCardArea);
				};
		}
	}
}

void CardManager::handleHandCardChange(CardView* clickedView, CardAreaView* area)
{

	if (!clickedView || !clickedView->getModel()) return;
	if (_handCardview == clickedView) return;
	CardModel* clickedModel = clickedView->getModel();
	clickedModel->isSelected = true;
	//clickedView->showGlow(true);
	pushUndoRecord(clickedView,false);
	//移动到定好的顶牌位置 先移再删
	Vec2 targetPos = Vec2(800, 270);
	clickedView->setLocalZOrder(100);
	auto moveTo = MoveTo::create(0.3f, targetPos);
	auto ease = EaseSineOut::create(moveTo);
	clickedView->runAction(ease);
	pushUndoRecord(_handCardview,true);
	_handCardview->removeFromParent();
	if (!_stack.empty()) {
		_stack.pop_back();
	}
	_handCardview = clickedView;
}

void CardManager::handleTableCardChange(CardView* clickedView, CardAreaView* area)
{
	
	if (!_handCardview) return;
	if (!clickedView || !clickedView->getModel()) return;
	if (_handCardview == clickedView) return;
	
	CardModel* tableModel = clickedView->getModel();
	CardModel* handModel = _handCardview->getModel();

	if (std::abs(tableModel->rank - handModel->rank) == 1) {
		pushUndoRecord(clickedView,false);
		Vec2 targetPos = Vec2(800, -310);
		
		auto moveTo = MoveTo::create(0.3f, targetPos);
		auto ease = EaseSineOut::create(moveTo);
		clickedView->setLocalZOrder(100);
		clickedView->runAction(ease);
		//先移再删
		pushUndoRecord(_handCardview,true);
		_handCardview->removeFromParent();
		_handCardview = clickedView;
		_stack.push_back(_handCardview->getModel());

	}
}

void CardManager::undo()
{
	if (_undoStack.empty()) {
		return;
	}
	//取出最后一条记录并出栈
	UndoRecord last = _undoStack.back();
	_undoStack.pop_back();

	if (last.isTopHandCard) {
		//重新生成view
		CardModel* newModel = new CardModel(last.modelSnapshot);
		CardView* newView = CardView::create(newModel);
		
		if (newModel->isTopAreaCard) {
			newView->setPosition(Vec2(800, -310));
		}
		else {
			newView->setPosition(Vec2(800, 270));
		}

		
		if (last.targetArea) {
			last.targetArea->addChild(newView, last.originalZOrder);
			CardAreaView* areaPtr = last.targetArea;
			//重新绑定回调
			if (!newModel->isTopAreaCard) {
				newView->_onClicked = [this, areaPtr](CardView* clickedView) {
					this->handleHandCardChange(clickedView, areaPtr);
					};
			}
			else {
				newView->_onTableCardClicked = [this, areaPtr](CardView* clickedView) {	
					this->handleTableCardChange(clickedView, areaPtr);
					};
			}
			
		}
		
		//把移动的牌移动回原位
		last = _undoStack.back();
		_undoStack.pop_back();
		auto move = MoveTo::create(0.3f, last.originalPos);
		auto ease = EaseSineOut::create(move);
		_handCardview->runAction(ease);
		_handCardview = newView;
		_stack.push_back(newModel);
			
	}
	
	
}

void CardManager::pushUndoRecord(CardView* view,bool isTopHandCard)
{
	if (!view || !view->getModel()) return;

	UndoRecord record;

	record.modelSnapshot = *(view->getModel());
	record.originalPos = view->getPosition();
	record.originalZOrder = view->getLocalZOrder();
	
	record.targetArea = static_cast<CardAreaView*>(view->getParent());

	record.isTopHandCard = isTopHandCard; 	
	_undoStack.push_back(record);
}


