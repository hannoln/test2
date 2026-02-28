#include "GameController.h"
#include "ui/UIButton.h"

void GameController::initGame(const std::string& configPath)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 1. 初始化顶部区域 (Main Area)
    _mainCardArea = CardAreaView::create(Size(1080, 1500), Color4B(80, 120, 200, 120));
    _mainCardArea->setAnchorPoint(Vec2(0.5f, 1.0f));
    _mainCardArea->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    _parentScene->addChild(_mainCardArea, 20);

    // 2. 初始化手牌区域 (Hand Area)
    _handCardArea = CardAreaView::create(Size(1080, 580), Color4B(255, 165, 0, 120));
    _handCardArea->setAnchorPoint(Vec2(0.5f, 0.5f));
    _handCardArea->setPosition(Vec2(visibleSize.width / 2, 290));
    _parentScene->addChild(_handCardArea, -1);

    // 3. 生成卡牌初始布局 (通过 Manager)
    // 注意：这里假设 _cardManager 已经在某处定义或作为成员变量
    _cardManager.initFromJson(configPath, _mainCardArea);
    _cardManager.initHandCard(configPath, _handCardArea);

    auto undoButton = ui::Button::create("normal.png");
    undoButton->setTitleText("Undo");
    undoButton->setTitleFontSize(36);
    undoButton->setPosition(Vec2(540, 2000));
    undoButton->setScale(1.5f);

    undoButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            _cardManager.undo();
        }
        });
    _parentScene->addChild(undoButton, 100);
}
