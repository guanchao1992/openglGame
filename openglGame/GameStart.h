#pragma once
#include "2d/Node.h"
#include "2d/FillDrawNode.h"


StatementNode(GameStart)
class GameStart :public Node
{
public:
	static SPGameStart create();

	void init();
	virtual void update(GLfloat time);
public:

	void onUp(bool keyPress);
	void onDown(bool keyPress);
	void onLeft(bool keyPress);
	void onRight(bool keyPress);
public:



	SPFillDrawNode _test;
};

