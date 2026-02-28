#include "CardAreaView.h"

CardAreaView* CardAreaView::create(const cocos2d::Size& size, Color4B color)
{

    auto ret = new CardAreaView();
    if (ret && ret->init(size,color))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardAreaView::init(const cocos2d::Size& size,Color4B color)
{

    if (!Node::init())
        return false;
    _areaSize = size;
    setContentSize(size);
    setAnchorPoint(Vec2(0.5f, 0.5f));

    auto bg = LayerColor::create(
        color,
        size.width,
        size.height
    );

    bg->setIgnoreAnchorPointForPosition(false);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2::ZERO);

    addChild(bg);
    return true;
}



