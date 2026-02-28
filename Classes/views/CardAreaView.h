#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
USING_NS_CC;
//视图区域类
class CardAreaView : public cocos2d::Node
{
public:
    static CardAreaView* create(const cocos2d::Size& size,Color4B color);
    bool init(const cocos2d::Size& size, Color4B color);

private:
    Color4B color;//背景颜色
    cocos2d::Size _areaSize;
   
};

