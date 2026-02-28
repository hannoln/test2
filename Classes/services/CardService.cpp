#include "CardService.h"

//花色
std::string CardService::getSuitSprite(CardSuitType suit)
{
    switch (suit) {
    case CST_CLUBS:
        return "res/suits/club.png";//梅花

    case CST_DIAMONDS:
        return "res/suits/diamond.png";//方块

    case CST_HEARTS:
        return "res/suits/heart.png";//红心

    case CST_SPADES:
        return "res/suits/spade.png";//黑桃
    }
}

std::string CardService::getBigNumberSprite(CardFaceType rank, CardSuitType suit)
{

    //黑桃和梅花用黑色数字
    if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {

    switch (rank)
    {
    case CFT_ACE:     return "res/number/big_black_A.png";
    case CFT_TWO:     return "res/number/big_black_2.png";
    case CFT_THREE:   return "res/number/big_black_3.png";
    case CFT_FOUR:    return "res/number/big_black_4.png";
    case CFT_FIVE:    return "res/number/big_black_5.png";
    case CFT_SIX:     return "res/number/big_black_6.png";
    case CFT_SEVEN:   return "res/number/big_black_7.png";
    case CFT_EIGHT:   return "res/number/big_black_8.png";
    case CFT_NINE:    return "res/number/big_black_9.png";
    case CFT_TEN:     return "res/number/big_black_10.png";
    case CFT_JACK:    return "res/number/big_black_J.png";
    case CFT_QUEEN:   return "res/number/big_black_Q.png";
    case CFT_KING:    return "res/number/big_black_K.png";

    default:
        return "none.png";
    }
    }
    //红心和方块用红色数字
    if (suit == CardSuitType::CST_DIAMONDS || suit == CardSuitType::CST_HEARTS) {

        switch (rank)
        {
        case CFT_ACE:     return "res/number/big_red_A.png";
        case CFT_TWO:     return "res/number/big_red_2.png";
        case CFT_THREE:   return "res/number/big_red_3.png";
        case CFT_FOUR:    return "res/number/big_red_4.png";
        case CFT_FIVE:    return "res/number/big_red_5.png";
        case CFT_SIX:     return "res/number/big_red_6.png";
        case CFT_SEVEN:   return "res/number/big_red_7.png";
        case CFT_EIGHT:   return "res/number/big_red_8.png";
        case CFT_NINE:    return "res/number/big_red_9.png";
        case CFT_TEN:     return "res/number/big_red_10.png";
        case CFT_JACK:    return "res/number/big_red_J.png";
        case CFT_QUEEN:   return "res/number/big_red_Q.png";
        case CFT_KING:    return "res/number/big_red_K.png";

        default:
            return "none.png";
        }
    }
   
}

std::string CardService::getSmallNumberSprite(CardFaceType rank, CardSuitType suit)
{
    //黑桃和梅花用黑色数字
    if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {

        switch (rank)
        {
        case CFT_TWO:     return "res/number/small_black_2.png";
        case CFT_ACE:     return "res/number/small_black_A.png";
        case CFT_THREE:   return "res/number/small_black_3.png";
        case CFT_FOUR:    return "res/number/small_black_4.png";
        case CFT_FIVE:    return "res/number/small_black_5.png";
        case CFT_SIX:     return "res/number/small_black_6.png";
        case CFT_SEVEN:   return "res/number/small_black_7.png";
        case CFT_EIGHT:   return "res/number/small_black_8.png";
        case CFT_NINE:    return "res/number/small_black_9.png";
        case CFT_TEN:     return "res/number/small_black_10.png";
        case CFT_JACK:    return "res/number/small_black_J.png";
        case CFT_QUEEN:   return "res/number/small_black_Q.png";
        case CFT_KING:    return "res/number/small_black_K.png";

        default:
            return "none.png";
        }
    }
    //红心和方块用红色数字
    if (suit == CardSuitType::CST_DIAMONDS || suit == CardSuitType::CST_HEARTS) {

        switch (rank)
        {
        case CFT_ACE:     return "res/number/small_red_A.png";
        case CFT_TWO:     return "res/number/small_red_2.png";
        case CFT_THREE:   return "res/number/small_red_3.png";
        case CFT_FOUR:    return "res/number/small_red_4.png";
        case CFT_FIVE:    return "res/number/small_red_5.png";
        case CFT_SIX:     return "res/number/small_red_6.png";
        case CFT_SEVEN:   return "res/number/small_red_7.png";
        case CFT_EIGHT:   return "res/number/small_red_8.png";
        case CFT_NINE:    return "res/number/small_red_9.png";
        case CFT_TEN:     return "res/number/small_red_10.png";
        case CFT_JACK:    return "res/number/small_red_J.png";
        case CFT_QUEEN:   return "res/number/small_red_Q.png";
        case CFT_KING:    return "res/number/small_red_K.png";

        default:
            return "none.png";
        }
    }
}


