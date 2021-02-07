#include "GameStart.h"
#include "2d/FillDrawNode.h"


SPGameStart GameStart::create()
{
	SPGameStart node = make_shared<GameStart>();
	node->record(node);
	node->init();
	return node;
}


void GameStart::init()
{
	auto fd = FillDrawNode::create();
	fd->addVertex(Vector2(0, 0));
	fd->addVertex(Vector2(55, 0));
	fd->addVertex(Vector2(55, 90));
	fd->addVertex(Vector2(0, 90));
	fd->enforceVertex();
	addChild(fd);

	fd->setColor(Vector4(1, 0, 1, 1));
	fd->setPosition(Vector2(100, 100));
	_test = fd;
}

void GameStart::update(GLfloat time)
{
}

void GameStart::onUp(bool keyPress)
{
	_test->setPosition(_test->getPosition() + Vector2(0, 10));
}

void GameStart::onDown(bool keyPress)
{
	_test->setPosition(_test->getPosition() + Vector2(0, -10));
}

void GameStart::onLeft(bool keyPress)
{
	_test->setPosition(_test->getPosition() + Vector2(-10, 0));
}

void GameStart::onRight(bool keyPress)
{
	_test->setPosition(_test->getPosition() + Vector2(10, 0));
}
