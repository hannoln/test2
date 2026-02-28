# pragma once
#include "cocos2d.h"
#include "managers/CardManager.h"
//对view和manger进行控制
class GameController {
public:
	void initGame(const std::string& configPath);
	GameController(Scene* scene)
		: _parentScene(scene), _mainCardArea(nullptr), _handCardArea(nullptr) {
	}

	~GameController() {}
private:
	CardManager _cardManager;

	CardAreaView* _mainCardArea;
	CardAreaView* _handCardArea;

	Scene* _parentScene;

};