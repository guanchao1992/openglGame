#pragma once
#include "2d/Node.h"
#include "EgameController.h"
#include "box2d.h"


StatementNode(GameStart)
class GameStart :public Node
{
	StatementCreate(GameStart)
public:
	void init();
	void initListen();
	void initWorld();
	virtual void update(GLfloat time);

public:
	void restartBlock();
public:

	void onUp(bool keyPress);
	void onDown(bool keyPress);
	void onLeft(bool keyPress);
	void onRight(bool keyPress);

	void onRotate(bool keyPress);
	void onRotateR(bool keyPress);
	
	void onAddBlockDown();

	void onAddBox(const Vector2& pos, const Size& size, const Vector4& color = Vector4(1, 1, 1, 1));
public:

	SPBlock _curblock;
	SPNode _filldraw;


	shared_ptr<b2World> _world;


private:
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};

