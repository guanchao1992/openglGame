#pragma once
#include "2d/Node.h"
#include "dexode/eventbus/Bus.hpp"
#include "Actor.h"

StatementNode(GameMainFight)
class GameMainFight :public Node
{
	StatementCreate(GameMainFight)
public:
	virtual void init();
	virtual void restart();
public:
private:
	SPActor	_player;


	SPNode _objectLayer;
};

