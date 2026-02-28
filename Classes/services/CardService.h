#pragma once
#include "models/CardModel.h"
#include <iostream>
#include "models/Enums.h"

//负责和程序外部通信
class CardService {
public:
    //获得花色图片路径
    static std::string getSuitSprite(CardSuitType suit);
    //获得数字图片路径
    static std::string getBigNumberSprite(CardFaceType  rank, CardSuitType suit);

    static std::string getSmallNumberSprite(CardFaceType  rank, CardSuitType suit);
};