#pragma once
#include "2d/Node.h"
#include "dexode/eventbus/Bus.hpp"
#include "Actor.h"
#include "base/QTreeBase.hpp"
#include "component/ConllisionComponent/CollisionComponent.h"

StatementNode(GameMainFight)
class GameMainFight :public Node
{
	StatementCreate(GameMainFight)
public:
	virtual void init();
	virtual void restart();
	void update(float time);

	inline const vector<SPNode>& getChildObjects()
	{
		return _objectLayer->getChilds();
	}
public:
private:
	SPActor	_player;
	SPNode _objectLayer;

};

