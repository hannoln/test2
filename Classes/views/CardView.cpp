#include "CardView.h"
#include "services/CardService.h"
#include <iostream>

CardView* CardView::create(CardModel* model)
{
	auto ret = new CardView();
	if (ret && ret->init(model)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool CardView::init(CardModel* model)
{
	if (!Node::init()) return false;
	
	_model = model;

/*******精灵初始化***********/
	//卡牌背景
	_bgSprite = Sprite::create("res/card_general.png");
	auto  size = _bgSprite->getContentSize();

	this->setContentSize(size);
	this->setAnchorPoint(Vec2(0.5, 0.5));

	_bgSprite->setAnchorPoint(Vec2(0.5, 0.5));
	_bgSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	if (_bgSprite == nullptr)	std::cout << "load card_backgroud failed" << std::endl;
	
	addChild(_bgSprite);

	//  数字
	_numberSprite = Sprite::create();
	
	_numberSprite->setPosition(size.width / 2, size.height / 2);
	addChild(_numberSprite);
	
	//花色
	_suitSprite = Sprite::create();
	_suitSprite->setAnchorPoint(Vec2(1, 1));
	_suitSprite->setPosition(size.width-20 , size.height -20);
	addChild(_suitSprite);

	//小数字
	_smallnumberSprite = Sprite::create();
	_smallnumberSprite->setAnchorPoint(Vec2(0, 1));
	_smallnumberSprite->setPosition(20 , size.height -20 );
	addChild(_smallnumberSprite);
	refresh();

	/*******点击事件监听***********/

	// 1. 创建单点触摸监听器
	auto listener = EventListenerTouchOneByOne::create();
	// 2. 设置吞噬触摸（防止点击透传到下层的牌）
	listener->setSwallowTouches(true);
	// 3. 编写点击开始逻辑
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		// 获取点击在当前节点的坐标
		Vec2 pos = this->convertToNodeSpace(touch->getLocation());
		// 获取当前节点的尺寸矩形
		Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

		// 判断点击位置是否在卡牌范围内
		if (rect.containsPoint(pos)) {
			if (this->getModel()->isInHand) {
				if (_onClicked) {
					_onClicked(this);
			}
			}
			if (this->getModel()->isTopAreaCard) {
				if (_onTableCardClicked) {
				_onTableCardClicked(this);
			}
			}
			
			return true; 
		}
		return false; // 不在此区域，不处理
		};
	// 4. 将监听器注册到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void CardView::refresh()
{
	if (!_model) return;

	// 获取资源路径（由 Service 决定）
	std::string numberTex =
		CardService::getBigNumberSprite(
			_model->rank,
			_model->suit);

	std::string suitTex =
		CardService::getSuitSprite(
			_model->suit);

	std::string smallNumberTex= CardService::getSmallNumberSprite(
		_model->rank,
		_model->suit);

	_numberSprite->setTexture(numberTex);
	_suitSprite->setTexture(suitTex);
	_smallnumberSprite->setTexture(smallNumberTex);

	// 正反面控制
	this->setVisible(_model->faceup);
}

