#pragma once
#include "Enums.h"

//卡牌模型，存储卡牌属性
class CardModel {
	
public:
	//牌面 花色 是否正面
	CardModel(CardFaceType f = CFT_NONE, CardSuitType s = CST_NONE, bool up = false)
		: rank(f), suit(s), faceup(up)
	{
	}
	int id;
	CardSuitType suit;//花色
	CardFaceType rank;//牌面

	bool faceup;  //是否正面
	bool isSelected = false;//是否选中
	bool isInHand = false;//是不是手牌 
	bool isTopAreaCard = false;
};