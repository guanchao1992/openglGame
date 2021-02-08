#pragma once
#include "2d/Node.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"


StatementNode(GameStart)
class GameStart :public Node
{
	StatementCreate(GameStart)
public:
	void init();
	virtual void update(GLfloat time);
public:

	void onUp(bool keyPress);
	void onDown(bool keyPress);
	void onLeft(bool keyPress);
	void onRight(bool keyPress);

	void onRotate(bool keyPress);
	void onRotateR(bool keyPress);
public:

	SPNode _test;


	SPBlock _block;
};

