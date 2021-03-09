#include "GameStart.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>
#include "nlohmann/json.hpp"
#include <iostream> 
#include <fstream> 

using namespace nlohmann;

#define WORLD_SCALE 10	//世界坐标系与物理坐标系比例

void GameStart::init()
{
	initListen();
	initWorld();

	auto fd = Block::create();
	addChild(fd,200);

	fd->setPosition(Vector2(100, 100));
	_block = fd;
	fd->setTag(1001);

	
	/*
	// read a JSON file
	std::ifstream i("file.json");
	json j;
	i >> j;
	*/


	json j = { {"2",21} ,{"test","efw"} };

	// write prettified JSON to another file
	std::ofstream o("pretty.json");
	o << j << std::endl;

	/*
	addTimer(0.1, -1, [&](float time) {
		onAddBlockDown();
		return false;
	});
	*/
}

void GameStart::initListen()
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

	_listener->listen([&](const MouseMoveEvent& et) {
		printf("x:%.2f,y:%.2f,bts:%d\n", et._x, et._y, et._buttons);
	});
	_listener->listen([&](const MouseKeyEvent& et) {
		if ((et.button & 4) && et._isDown)
		{
			onAddBox(Vector2(et._x / WORLD_SCALE, et._y / WORLD_SCALE), Size(4, 4), Vector4(0.5, 0.1, 0, 1));
		}
	});
}

void GameStart::initWorld()
{
	b2Vec2 gravity(0.0f, -10.0f);
	_world = make_shared<b2World>(gravity);

	//_world->SetDebugDraw();

	//创建地面
	{
		auto w = 100.f;
		auto h = 1.f;
		auto ground1 = FillDrawNode::create();
		ground1->addVertex(-w * WORLD_SCALE, h * WORLD_SCALE);
		ground1->addVertex(w * WORLD_SCALE, h * WORLD_SCALE);
		ground1->addVertex(w * WORLD_SCALE, -h * WORLD_SCALE);
		ground1->addVertex(-w * WORLD_SCALE, -h * WORLD_SCALE);
		ground1->setColor(1, 0, 0, 1);
		addChild(ground1);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(50.0f, 1.0f);
		groundBodyDef.userData._node = ground1.get();
		b2Body* groundBody = _world->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(w, h);
		groundBody->CreateFixture(&groundBox, 0.0f);
	}


	for (size_t i = 0; i < 200; i++)
	{
		//onAddBox(Vector2(10.0f + i / 10 * 4, 10.0f + i % 10 * 4), Size(2, 4), Vector4(0.1, 0.5, 0.8, 1));
	}

	static int time_i = 0;
	addTimer(0.1, 200, [&](float time) {
		//onAddBox(Vector2(10.0f + time_i / 10 * 4, 10.0f + time_i % 10 * 4), Size(2, 4), Vector4(0.1, 0.5, 0.8, 1));
		time_i++;
		return false;
	});
	/*
	addTimer(0.1, -1, [&](float time) {
		return false;
	});
	*/

}

const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

void GameStart::update(GLfloat time)
{
	static float s_t = 0;
	s_t += time;
	_block->resetType(BlockType(((int)s_t) % 7));

	if (time > timeStep)
	{
		time = timeStep;
	}
	_world->Step(time, velocityIterations, positionIterations);

	auto body = _world->GetBodyList();
	while (body)
	{
		auto pos = body->GetPosition();
		auto angle = body->GetAngle();
		auto node = body->GetUserData()._node;
		node->setPosition(pos.x * WORLD_SCALE, pos.y * WORLD_SCALE);
		node->setEulerAngle(angle);

		body = body->GetNext();
	}
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

//传入的参数是相对于物理坐标系的
void GameStart::onAddBox(const Vector2& pos, const Size& size, const Vector4& color)
{
	auto box1 = FillDrawNode::create();
	box1->addVertex(size.m_width / 2 * WORLD_SCALE, -size.m_height / 2 * WORLD_SCALE);
	box1->addVertex(size.m_width / 2 * WORLD_SCALE, size.m_height / 2 * WORLD_SCALE);
	box1->addVertex(-size.m_width / 2 * WORLD_SCALE, size.m_height / 2 * WORLD_SCALE);
	box1->addVertex(-size.m_width / 2 * WORLD_SCALE, -size.m_height / 2 * WORLD_SCALE);
	box1->setColor(color);
	addChild(box1);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos._x, pos._y);
	bodyDef.linearVelocity = b2Vec2(10, 0); //指定初始线性速度
	bodyDef.userData._node = box1.get();
	b2Body* body = _world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;	//设置形状
	dynamicBox.SetAsBox(size.m_width / 2, size.m_height / 2);

	b2FixtureDef fixtureDef;	//设置物体的各种参数
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);
}
