#include "GameStart.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>


void GameStart::init()
{
	_listener = GameApp::getInstance()->createListenerSP();

	_listener->listen([&](const KeyEvent& et) {
		if (et._isDown)
		{
			printf("event:%d按下了按键:%d\n", et._eventId, et._key);
		}
		else
		{
			printf("event:%d放开了按键:%d\n", et._eventId, et._key);
		}
		if (et._key == GLFW_KEY_UP || et._key == 'w' || et._key == 'W')
		{
			onUp(et._isDown);
		}
		if (et._key == GLFW_KEY_DOWN || et._key == 's' || et._key == 'S')
		{
			onDown(et._isDown);
		}
		if (et._key == GLFW_KEY_LEFT || et._key == 'a' || et._key == 'A')
		{
			onLeft(et._isDown);
		}
		if (et._key == GLFW_KEY_RIGHT || et._key == 'd' || et._key == 'D')
		{
			onRight(et._isDown);
		}
		if (et._key == GLFW_KEY_SPACE)
		{
			onRotate(et._isDown);
		}
	});

	auto fd = Block::create();
	addChild(fd,200);

	fd->setPosition(Vector2(100, 100));
	_block = fd;
	fd->setTag(1001);

	/*
	*/
	addTimer(0.1, -1, [&](float time) {
		onAddBlockDown();
		return false;
	});
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

void GameStart::onAddBlockDown()
{
	auto block = Block::create();
	block->setPosition(10 + rand() % 20 * 60, 500);
	this->addChild(block, 20);
	block->resetType((BlockType)(rand() % 7));

	addTimer(0.0, -1, [&, block](float time) {
		auto pos = block->getPosition();
		block->setPosition(pos._x, pos._y - 200 * time);
		if (block->getPosition()._y < 100)
		{
			block->removeFromParent();
			return true;
		}
		;
		return false;
	});
}
