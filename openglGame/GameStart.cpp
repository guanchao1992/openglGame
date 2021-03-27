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
	initBlock();

	/*
	auto fd = Block::create();
	addChild(fd,200);
	fd->setPosition(Vector2(100, 100));
	_curblock = fd;
	fd->setTag(1001);
	*/

	_filldraw = FillDrawNode::create();
	
	/*
	// read a JSON file
	std::ifstream i("file.json");
	json j;
	i >> j;
	*/


	json j = { {"2",21} ,{"test","efw"} };

	// write prettified JSON to another file
	std::ofstream o("res/pretty.json");
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
	b2Vec2 gravity(0.0f, 0.0f);
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

	addTimer(0, -1, [&](float time) {

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

void GameStart::initBlock()
{
	static int max_x = 11;	//0~max
	static int max_y = 14;
	static int place[12][25] = { 0 };
	static Vector2 off_pos = { 0,0 };
	static int block_scale = 40;
	static int _move_type = 0; //0不动，1左2右4下。

	static SPFillDrawNode place_draw = FillDrawNode::create();
	addChild(place_draw);
	place_draw->setPosition(off_pos);

	static SPBlock cur_block = Block::create();
	addChild(cur_block);
	static int cur_x = 5;
	static int cur_y = 20;
	static int cur_dir = 0;

	auto func_update_pos = []() {
		cur_block->setPosition(off_pos._x + block_scale * cur_x, off_pos._x + block_scale * cur_y);
	};

	auto func_update_dir = [](int dir) {
		cur_block->resetDir(dir);
	};

	auto func_rectr_block = [&]() {
		cur_dir = 0;
		cur_x = 5;
		cur_y = 20;
		func_update_pos();
		cur_block->resetType((BlockType)(rand()%7 + 1));
		func_update_dir(cur_dir);
	};

	auto func_check_can = [&](int mx, int my,int dir)
	{
		int temp_x = cur_x + mx;
		int temp_y = cur_y + my;

		for (int n = 0; n < 4; ++n)
		{
			auto block = cur_block->getBlockST(dir);
			int ix = block[n][0];
			int iy = block[n][1];

			if (temp_x + ix < 0 || temp_x + ix > max_x || temp_y + iy < 0)
			{
				return false;
			}
			if (place[temp_x + ix][temp_y + iy] > 0)
			{
				return false;
			}
		}
		return true;
	};

	auto func_move = [&](int mx, int my) {
		if (func_check_can(mx, my, cur_dir))
		{
			cur_x += mx;
			cur_y += my;
			func_update_pos();
			return true;
		}
		else
		{
			return false;
		}
	};

	auto func_redraw_all = [&]() {
		place_draw->clearAllVertex();
		for (int y = 0; y <= max_y; ++y)
		{
			for (int x = 0; x <= max_x; ++x)
			{
				if (place[x][y] > 0)
				{
					auto color = Block::getBlockColor((BlockType)place[x][y]);
					place_draw->addVertex(Vector2((x + 0) * block_scale, (y + 0)*block_scale), color);
					place_draw->addVertex(Vector2((x + 1) * block_scale, (y + 0)*block_scale), color);
					place_draw->addVertex(Vector2((x + 1) * block_scale, (y + 1)*block_scale), color);
					place_draw->addVertex(Vector2((x + 0) * block_scale, (y + 1)*block_scale), color);
					place_draw->signDraw(GL_TRIANGLE_FAN);
				}
			}
		}
	};

	auto func_check_eliminate = [&]() {
		std::map<int, bool> eliminateYs;
		for (int y = 0; y < max_y; ++y)
		{
			bool isEliminate = true;
			for (int x = 0; x <= max_x; x++)
			{
				if (place[x][y] == 0)
				{
					isEliminate = false;
					break;
				}
			}
			if (isEliminate)
			{
				eliminateYs[y] = true;
			}
		}
		if (eliminateYs.size() == 0)
		{
			return 0;
		}

		int temp_y = 0;
		for (int y = 0; y <= max_y; ++y)
		{
			while (eliminateYs.find(temp_y) != eliminateYs.end())
			{
				temp_y++;
			}
			for (int x = 0; x <= max_x; ++x)
			{
				place[x][y] = temp_y <= max_y ? place[x][temp_y] : 0;
			}
			temp_y++;
		}
		return (int)eliminateYs.size();
	};

	auto fun_set_place = [&](const SPBlock&sp) {

		for (int n = 0; n < 4; ++n)
		{
			auto block = sp->getCurBlockST();
			int ix = block[n][0];
			int iy = block[n][1];
			int x = cur_x + ix;
			int y = cur_y + iy;

			if ((x >= 0 && x <= max_x) && (y >= 0 && y < max_y))
			{
				place[x][y] = (int)sp->_blockType;
				/*
				place_draw->addVertex(Vector2((x + 0) * block_scale, (y + 0)*block_scale), sp->getColor());
				place_draw->addVertex(Vector2((x + 1) * block_scale, (y + 0)*block_scale), sp->getColor());
				place_draw->addVertex(Vector2((x + 1) * block_scale, (y + 1)*block_scale), sp->getColor());
				place_draw->addVertex(Vector2((x + 0) * block_scale, (y + 1)*block_scale), sp->getColor());
				place_draw->signDraw(GL_TRIANGLE_FAN);
				*/
			}
		}
		if (func_check_eliminate() > 0)
		{
			func_redraw_all();
		}
		else
		{
			func_redraw_all();
		}
	};


	func_rectr_block();
	auto update_timer = addTimer(1, -1, [&](float time) {
		if (func_check_can(0, -1, cur_dir))
		{
			cur_y--;
			func_update_pos();
		}
		else
		{
			fun_set_place(cur_block);
			func_rectr_block();
		}
		return false;
	});

	static auto move_timer_left = addTimer(0.15, -1, [&](float time) {
		if (_move_type & 0x0001)
		{
			func_move(-1, 0);
		}
		return false;
	});
	static auto move_timer_right = addTimer(0.15, -1, [&](float time) {
		if (_move_type & 0x0010)
		{
			func_move(1, 0);
		}
		return false;
	});
	static auto move_timer_down = addTimer(0.1, -1, [&](float time) {
		if (_move_type & 0x0100)
		{
			if (func_check_can(0, -1, cur_dir))
			{
				cur_y--;
				func_update_pos();
			}
			else
			{
				fun_set_place(cur_block);
				func_rectr_block();
			}
		}
		return false;
	});

	static auto block_listener = GameApp::getInstance()->createListenerSP();
	block_listener->listen([&](const KeyEvent& et) {
	
		if (et._key == GLFW_KEY_UP || et._key == 'w' || et._key == 'W' || et._key == GLFW_KEY_SPACE)
		{
			if (et._isDown)
			{
				if (func_check_can(0, 0, cur_dir + 1))
				{
					func_update_dir(++cur_dir);
				}
			}
		}
		if (et._key == GLFW_KEY_DOWN || et._key == 's' || et._key == 'S')
		{
			if (et._isDown)
			{
				if (!(_move_type & 0x0100))
				{
					_move_type = _move_type | 0x0100;

					TimerController::getInstance()->resetTime(move_timer_down);
					if (func_check_can(0, -1, cur_dir))
					{
						cur_y--;
						func_update_pos();
					}
					else
					{
						fun_set_place(cur_block);
						func_rectr_block();
					}
				}
			}
			else
				_move_type = _move_type & ~0x0100;

		}
		if (et._key == GLFW_KEY_LEFT || et._key == 'a' || et._key == 'A')
		{
			if (et._isDown)
			{
				if (!(_move_type & 0x0001))
				{
					_move_type = _move_type | 0x0001;
					TimerController::getInstance()->resetTime(move_timer_left);
					func_move(-1, 0);
				}
			}
			else
				_move_type = _move_type & ~0x0001;
		}
		if (et._key == GLFW_KEY_RIGHT || et._key == 'd' || et._key == 'D')
		{
			if (et._isDown)
			{
				if (!(_move_type & 0x0010))
				{
					_move_type = _move_type | 0x0010;
					TimerController::getInstance()->resetTime(move_timer_right);
					func_move(1, 0);
				}
			}
			else
				_move_type = _move_type & ~0x0010;
		}
	});
}

void GameStart::update(GLfloat time)
{
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
	auto block = Block::create();
	block->setPosition(10 + rand() % 20 * 60, 500);
	this->addChild(block, 20);
	block->resetType((BlockType)(rand() % 7 + 1));

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
	bodyDef.linearDamping = 4.0f;
	bodyDef.angularDamping = 0.4;
	b2Body* body = _world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;	//设置形状
	dynamicBox.SetAsBox(size.m_width / 2, size.m_height / 2);

	b2FixtureDef fixtureDef;	//设置物体的各种参数
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);
}
