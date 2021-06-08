#include "GameStart.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>
#include "control/TableController.h"

#include "tables/ItemTable.h"
#include "component/DrawRanderComponent.h"
#include "component/MouseComponent.h"
#include "component/AreaComponent.h"


#define WORLD_SCALE 10	//世界坐标系与物理坐标系比例

void GameStart::init()
{
	initListen();
	//initWorld();

	//画格子
	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		fd->setPosition(0, 0);
		addChild(fd, -1000);
		for (int x = 0; x < 5; ++x)
		{
			for (int y = 0; y < 5; ++y)
			{
				if ((x + y) % 2 == 0)
				{
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 0, 0), Vector4(0.0f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 0, 0), Vector4(0.0f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 120, 0), Vector4(0.0f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 120, 0), Vector4(0.0f, 0.2f, 0.2f, 1));
					drawCom->signDraw(GL_TRIANGLE_FAN);
				}
				else
				{
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 0, 0), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 0, 0), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 120, 0), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 120, 0), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->signDraw(GL_TRIANGLE_FAN);
				}
			}
		}
		for (int x = 0; x < 5; ++x)
		{
			for (int y = 0; y < 5; ++y)
			{
				if ((x + y) % 2 == 0)
				{
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 0, 100), Vector4(0.4f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 0, 100), Vector4(0.4f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 120, 100), Vector4(0.4f, 0.2f, 0.2f, 1));
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 120, 100), Vector4(0.4f, 0.2f, 0.2f, 1));
					drawCom->signDraw(GL_TRIANGLE_FAN);
				}
				else
				{
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 0, 100), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 0, 100), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 120, 120 * y + 120, 100), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->addVertex(Vector3(120 * x + 0, 120 * y + 120, 100), Vector4(0.3, 0.3, 0.3, 1));
					drawCom->signDraw(GL_TRIANGLE_FAN);
				}
			}
		}
	}

	//TableController::getInstance()->reset();
	/*
	auto item1 = ItemTableDatas::getData(10001);
	auto item2 = ItemTableDatas::getData(10006);
	auto item3 = ItemTableDatas::getData(10008);
	printf(item1->_name.c_str());
	printf(item2->_name.c_str());
	printf(item3->_name.c_str());
	*/

	/*
	addTimer(0.1, -1, [this](float time) {
		onAddBlockDown();
		return false;
	});
	*/

	/*
	*/
	auto areaCom = addComponent<AreaComponent>();
	areaCom->setSize(Size(10000, 10000));
	areaCom->setAnchor(Vector2(0.5, 0.5));
	auto mouseCom = addComponent<MouseComponent>();
	mouseCom->setMouseKeyFunc([this](MouseComponent&mouseCon, const MouseKeyEvent&event) {
		if (event.button & 1 && event._isDown)
		{

		}
	});
	mouseCom->setMouseMoveFunc([this](MouseComponent&mouseCon, const MouseMoveEvent&event) {
		if (event._buttons & 1)
		{
			//this->setAngleCoordinate(_angleX + (event._x - _oldDownPos._x)*0.001, _angleY + (event._y - _oldDownPos._y)*0.001, 0);
			this->setAngleCoordinate(_angleX - (event._y - _oldDownPos._y)*0.1, _angleY + (event._x - _oldDownPos._x)*0.1, 0);
		}
		else if (event._buttons & 2)
		{
			auto app = GameApp::getInstance();
			this->setPosition(_position._x + (event._x - _oldDownPos._x) / app->getProScale(), _position._y + (event._y - _oldDownPos._y) / app->getProScale());

		}
		_oldDownPos = Vector2(event._x, event._y);


	});
}


void GameStart::initListen()
{
	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([this](const KeyEvent& et) {
		switch (et._key)
		{
		case GLFW_KEY_UP: case 'w': case 'W':
			onUp(et._isDown);
			break;
		case GLFW_KEY_DOWN: case 's': case 'S':
			onDown(et._isDown);
			break;
		case GLFW_KEY_LEFT: case 'a': case 'A':
			onLeft(et._isDown);
			break;
		case GLFW_KEY_RIGHT: case 'd': case 'D':
			onRight(et._isDown);
			break;
		case GLFW_KEY_SPACE:
			onRotate(et._isDown);
			break;
		case 'r': case 'R':
			if (et._isDown)
				restartBlock();
			break;
		default:
			break;
		}
	});

	_listener->listen([this](const MouseMoveEvent& et) {
		//printf("x:%.2f,y:%.2f,bts:%d\n", et._x, et._y, et._buttons);
	});
	_listener->listen([this](const MouseKeyEvent& et) {
		if ((et.button & 4) && et._isDown)
		{
			auto app = GameApp::getInstance();
			auto vPos1 = app->posViewToWorld(et._x, et._y, 0);
			auto vPos2 = app->posViewToWorld(et._x, et._y, 1000);

			printf("s:(%f,%f,%f)---(%f,%f,%f)\n", vPos1._x, vPos1._y, vPos1._z, vPos2._x, vPos2._y, vPos2._z);
			auto pos1 = app->convertViewToNode(this, vPos1);
			auto pos2 = app->convertViewToNode(this, vPos2);

			auto axz = (pos2._z - pos1._z) / (pos2._x - pos1._x);
			auto bxz = pos1._z - axz * pos1._x;

			auto ayz = (pos2._z - pos1._z) / (pos2._y - pos1._y);
			auto byz = pos1._z - ayz * pos1._y;

			//令z==0，求x,y
			float x = 0;
			float y = 0;
			if (pos1._x == pos2._x)
				x = pos1._x;
			else
				x = (0 - bxz) / axz;
			if (pos1._y == pos2._y)
				y = pos1._y;
			else
				y = (0 - byz) / ayz;

			printf("e:(%f,%f,%f)---(%f,%f,%f)\n", pos1._x, pos1._y, pos1._z, pos2._x, pos2._y, pos2._z);
			printf("相交的点：(%f,%f,%f)\n", x, y, 0.f);
			/*
			auto pos = GameApp::getInstance()->convertViewToNode(this, Vector3(et._x, et._y, 0));
			onAddBox(Vector2(pos._x / WORLD_SCALE, pos._y / WORLD_SCALE), Size(4, 4), Vector4(0.5, 0.1, 0, 1));
			*/
			//onAddBox(Vector2(x / WORLD_SCALE, y / WORLD_SCALE), Size(4, 4), Vector4(0.5, 0.1, 0, 1));


			{
				auto fd = Node::create();
				auto drawCom = fd->addComponent<DrawRanderComponent>();
				fd->setPosition(0, 0);
				addChild(fd, 10);
				drawCom->addVertex(pos1, Vector4(1.0f, 0.2f, 0.2f, 1));
				drawCom->addVertex(pos2, Vector4(1.0f, 0.2f, 0.2f, 1));
				drawCom->signDraw(GL_LINE_STRIP);
			}

			auto fd = Node::create();
			auto drawCom = fd->addComponent<DrawRanderComponent>();
			fd->setPosition(x, y);
			addChild(fd, 10);
			drawCom->addVertex(Vector3(-10, -10, 0), Vector4(0.5f, 0.2f, 0.2f, 1));
			drawCom->addVertex(Vector3(10, -10, 0), Vector4(0.5f, 0.2f, 0.2f, 1));
			drawCom->addVertex(Vector3(10, 10, 0), Vector4(0.5f, 0.2f, 0.2f, 1));
			drawCom->addVertex(Vector3(-10, 10, 0), Vector4(0.5f, 0.2f, 0.2f, 1));
			drawCom->signDraw(GL_TRIANGLE_FAN);

		}
	});
}

void GameStart::initWorld()
{
	b2Vec2 gravity(0.0f, 0.0f);
	_world = make_shared<b2World>(gravity);

	//_world->SetDebugDraw();

	//创建地面
	{
		auto w = 100.f;
		auto h = 1.f;
		auto ground1 = Node::create();
		auto com = ground1->addComponent<DrawRanderComponent>();
		com->addVertex(-w * WORLD_SCALE, h * WORLD_SCALE, 0);
		com->addVertex(w * WORLD_SCALE, h * WORLD_SCALE, 0);
		com->addVertex(w * WORLD_SCALE, -h * WORLD_SCALE, 0);
		com->addVertex(-w * WORLD_SCALE, -h * WORLD_SCALE, 0);
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
	addTimer(0.1, 200, [this](float time) {
		//onAddBox(Vector2(10.0f + time_i / 10 * 4, 10.0f + time_i % 10 * 4), Size(2, 4), Vector4(0.1, 0.5, 0.8, 1));
		time_i++;
		return false;
	});

	addTimer(0, -1, [this](float time) {

		static float timeStep = 1.0f / 60.0f;
		static int32 velocityIterations = 6;
		static int32 positionIterations = 2;
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
		return false;
	});
}

void GameStart::restartBlock()
{
	EgameController::getInstance()->restartBlock();
}

void GameStart::onUp(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onDown(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onLeft(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onRight(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onRotate(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onRotateR(bool keyPress)
{
	if (keyPress)
	{
	}
}

void GameStart::onAddBlockDown()
{
}

//传入的参数是相对于物理坐标系的
void GameStart::onAddBox(const Vector2& pos, const Size& size, const Vector4& color)
{
	auto box1 = Node::create();
	auto com = box1->addComponent<DrawRanderComponent>();
	com->addVertex(size._width / 2 * WORLD_SCALE, -size._height / 2 * WORLD_SCALE, 0);
	com->addVertex(size._width / 2 * WORLD_SCALE, size._height / 2 * WORLD_SCALE, 0);
	com->addVertex(-size._width / 2 * WORLD_SCALE, size._height / 2 * WORLD_SCALE, 0);
	com->addVertex(-size._width / 2 * WORLD_SCALE, -size._height / 2 * WORLD_SCALE, 0);
	box1->setColor(color);
	addChild(box1);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos._x, pos._y);
	bodyDef.linearVelocity = b2Vec2(0, 0); //指定初始线性速度
	bodyDef.userData._node = box1.get();
	bodyDef.linearDamping = 4.0f;
	bodyDef.angularDamping = 0.4;
	b2Body* body = _world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;	//设置形状
	dynamicBox.SetAsBox(size._width / 2, size._height / 2);

	b2FixtureDef fixtureDef;	//设置物体的各种参数
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);
}
