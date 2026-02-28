#pragma once
#include "CardManager.h"
#include "models/CardModel.h"
#include "views/CardView.h"
#include "views/CardAreaView.h"
#include "json/document.h"
#include "cocos2d.h"
//负责具体逻辑实现
struct UndoRecord {
	CardModel modelSnapshot;    // 存储 Model 的副本（值拷贝）
	cocos2d::Vec2 originalPos;  // 记录它原本的位置
	int originalZOrder;         // 记录层级
	CardAreaView* targetArea;   // 记录它属于哪个区域（手牌区或桌牌区）
	//bool isHandCard;//好加入栈队列
	bool isTopHandCard;//好重新生成一个
	
};

class CardManager
{
	
public:
	//根据json文件初始化
	void initFromJson(const std::string& filename, CardAreaView* mainCardArea);
	void initHandCard(const std::string& filename, CardAreaView* mainCardArea);

	void handleHandCardChange(CardView* clickedView, CardAreaView* area);
	void handleTableCardChange(CardView* clickedView, CardAreaView* area);

	void pushUndoRecord(CardView* view, bool isTopHandCard);
	void undo();
private:
	
	CardView* _handCardview = nullptr;//当前手牌

	std::vector<UndoRecord> _undoStack;//回退栈
	std::vector<CardModel*> _stack; //手牌记录栈

};

