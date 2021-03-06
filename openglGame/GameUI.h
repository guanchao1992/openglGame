#pragma once
#include "2d/Node.h"
#include "EgameController.h"


StatementNode(GameUI)
class GameUI :public Node
{
	StatementCreate(GameUI)
public:
	void init();
	void initBk();
	void initDebug();
	virtual void update(GLfloat time);
	virtual void reshape();
public:

private:

	SPNode _leftBottom;
	SPNode _leftTop;
	SPNode _rightBottom;
	SPNode _rightTop;
	SPNode _center;

	SPNode _debug;

	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};

