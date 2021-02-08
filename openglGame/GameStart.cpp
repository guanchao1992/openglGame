#include "GameStart.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"


void GameStart::init()
{
	/*
	auto fd = FillDrawNode::create();
	fd->addVertex(Vector2(0, 0));
	fd->addVertex(Vector2(55, 0));
	fd->addVertex(Vector2(55, 90));
	fd->addVertex(Vector2(0, 90));
	fd->enforceVertex();
	addChild(fd);
	*/
	auto fd = Block::create();
	addChild(fd);

	fd->setPosition(Vector2(100, 100));
	_block = fd;

}

void GameStart::update(GLfloat time)
{
	static float s_t = 0;
	s_t += time;
	_block->resetType(BlockType(((int)s_t) % 7));
	
}

void GameStart::onUp(bool keyPress)
{
	if (keyPress)
	{
		_block->setPosition(_block->getPosition() + Vector2(0, 10));
	}
}

void GameStart::onDown(bool keyPress)
{
	if (keyPress)
	{
		_block->setPosition(_block->getPosition() + Vector2(0, -10));
	}
}

void GameStart::onLeft(bool keyPress)
{
	if (keyPress)
	{
		_block->setPosition(_block->getPosition() + Vector2(-10, 0));
	}
}

void GameStart::onRight(bool keyPress)
{
	if (keyPress)
	{
		_block->setPosition(_block->getPosition() + Vector2(10, 0));
	}
}

void GameStart::onRotate(bool keyPress)
{
	if (keyPress)
	{
		_block->resetDir(_block->_dir + 1);
	}
}

void GameStart::onRotateR(bool keyPress)
{
	if (keyPress)
	{
		_block->resetDir(_block->_dir - 1);
	}
}
