#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
USING_NS_CC;
//负责渲染图像
class CardView : public cocos2d::Node
{
public:
    static CardView* create(CardModel* model);
    bool init(CardModel* model);
    void refresh();
    CardModel* getModel() const { return _model; }
    //点击手牌
    void setHandCardClickCallback(const std::function<void(CardView*)>& callback) {
        _onClicked = callback;
    }
    //点击桌牌
    void setTableCardClickCallback(const std::function<void(CardView*)>& callback) {
        _onTableCardClicked = callback;
    }
    //给选中的牌加一个框框
    //手牌点击事件
    std::function<void(CardView*)> _onClicked;
    //桌牌点击事件
    std::function<void(CardView*)> _onTableCardClicked;

private:
    CardModel* _model = nullptr;  //卡牌模型

    cocos2d::Sprite* _bgSprite = nullptr; //背景精灵
    cocos2d::Sprite* _numberSprite = nullptr; //数字精灵
    cocos2d::Sprite* _suitSprite = nullptr;//花色精灵
    cocos2d::Sprite* _smallnumberSprite = nullptr; //数字精灵

    cocos2d::DrawNode* _drawNode = nullptr;//集合图形绘制类 

   

   
};