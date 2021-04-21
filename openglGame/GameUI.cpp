#include "GameUI.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>
#include <corecrt_wstdio.h>
#include "tables/ItemTable.h"
#include "component/MouseComponent.h"
#include "component/DrawRanderComponent.h"
#include "component/FontRanderComponent.h"
#include "2d/Node.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include "2d/Button.h"


void GameUI::init()
{
	_listener = GameApp::getInstance()->createListenerSP();
	
	_leftBottom = Node::create();
	_leftTop = Node::create();
	_rightBottom = Node::create();
	_rightTop = Node::create();
	_center = Node::create();

	addChild(_leftBottom);
	addChild(_leftTop);
	addChild(_rightBottom);
	addChild(_rightTop);
	addChild(_center);

	_listener->listen([&](const KeyEvent& et) {
		if (et._isDown)
		{
			static int angle = 0;
			switch (et._key)
			{
			case GLFW_KEY_SPACE:
			{
				angle += 10;
				_center->setAngle(angle);
				break;
			}
			case 'v':
			case 'V':
			{
				break;
			}
			}
		}
	});
	_listener->listen([&](const MouseMoveEvent& et) {
		if (et._buttons & 1)
		{
			//et._x
		}
	});
	/*
	auto com1 = _leftBottom->addComponent<MouseComponent>();
	com1->setMouseKeyFunc([&](MouseComponent&com, const MouseKeyEvent&et) {
		if (et._isDown)
		{
		}
	});

	auto com2 = _rightBottom->addComponent<MouseComponent>();
	com2->setMouseKeyFunc([&](MouseComponent&com, const MouseKeyEvent&et) {
		if (et._isDown)
		{
		}
	});
	*/


	/*
	auto fontNode = FontDrawNode::create(DEFAULTE_FONT_FILE);
	fontNode->setFontSize(30);
	addChild(fontNode);
	fontNode->setPosition(200, 100);
	fontNode->setScale(1, 1);
	fontNode->setTag(1);
	auto item1 = ItemTableDatas::getData(10001);
	fontNode->setText(item1->_name);
	*/

	/*
	string curLocale = setlocale(LC_ALL, NULL);   //curLocale="C"
	setlocale(LC_ALL, "zh_CN.UTF-8");
	//string title = item1->_test_json.at("title");
	//printf(title.c_str());
	setlocale(LC_ALL, curLocale.c_str());
	*/

	_debug = Node::create();
	_leftBottom->addChild(_debug, 1000);

	//auto touchCom = _debug->addComponent<MouseComponent>();

	initBk();
	initDebug();
}

void GameUI::initBk()
{
	{
		auto fd1 = Node::create();
		auto drawCom = fd1->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector2(0, 0));
		drawCom->addVertex(Vector2(0, 100));
		drawCom->addVertex(Vector2(3, 100));
		drawCom->addVertex(Vector2(3, 3));
		drawCom->addVertex(Vector2(100, 3));
		drawCom->addVertex(Vector2(100, 0));
		fd1->setColor(Vector4(0.4, 0.4, 0.2, 0.4));
		fd1->setPosition(30, 30);
		_leftBottom->addChild(fd1);
	}

	{
		auto fd2 = Node::create();
		auto drawCom = fd2->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector2(0, 0));
		drawCom->addVertex(Vector2(0, -100));
		drawCom->addVertex(Vector2(3, -100));
		drawCom->addVertex(Vector2(3, -3));
		drawCom->addVertex(Vector2(100, -3));
		drawCom->addVertex(Vector2(100, 0));
		fd2->setColor(Vector4(0.4, 0.4, 0.2, 0.4));
		fd2->setPosition(30, -30);
		_leftTop->addChild(fd2);
	}

	{
		auto fd3 = Node::create();
		auto drawCom = fd3->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector2(0, 0));
		drawCom->addVertex(Vector2(0, 100));
		drawCom->addVertex(Vector2(-3, 100));
		drawCom->addVertex(Vector2(-3, 3));
		drawCom->addVertex(Vector2(-100, 3));
		drawCom->addVertex(Vector2(-100, 0));
		fd3->setColor(Vector4(0.4, 0.4, 0.2, 0.4));
		fd3->setPosition(-30, 30);
		_rightBottom->addChild(fd3);
	}

	{
	auto fd4 = Node::create();
	auto drawCom = fd4->addComponent<DrawRanderComponent>();
	drawCom->addVertex(Vector2(0, 0));
	drawCom->addVertex(Vector2(0, -100));
	drawCom->addVertex(Vector2(-3, -100));
	drawCom->addVertex(Vector2(-3, -3));
	drawCom->addVertex(Vector2(-100, -3));
	drawCom->addVertex(Vector2(-100, 0));
	fd4->setColor(Vector4(0.4, 0.4, 0.2, 0.4));
	fd4->setPosition(-30, -30);
	_rightTop->addChild(fd4);
	}

	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector2(1, 1));
		drawCom->addVertex(Vector2(100, 1));
		drawCom->addVertex(Vector2(100, -1));
		drawCom->addVertex(Vector2(1, -1));
		drawCom->addVertex(Vector2(1, -100));
		drawCom->addVertex(Vector2(-1, -100));
		drawCom->addVertex(Vector2(-1, -1));
		drawCom->addVertex(Vector2(-100, -1));
		drawCom->addVertex(Vector2(-100, 1));
		drawCom->addVertex(Vector2(-1, 1));
		drawCom->addVertex(Vector2(-1, 100));
		drawCom->addVertex(Vector2(1, 100));
		fd->setColor(Vector4(0.4, 0.4, 0.2, 0.4));
		_center->addChild(fd);
	}
	for (int i = 0; i < 10; i++)
	{
		auto btn = Button::create("BUTTON", ".\\res\\btn_normal.png", ".\\res\\btn_select.png");
		btn->setPosition(30 * i, 10 * i);
		_center->addChild(btn);
		btn->setTag(i);
		//btn->addComponent<AreaComponent>()->setSize(Size(100, 100));
		//btn->addComponent<OutlineBoxComponent>()->setFill(true);
	}
}

void GameUI::initDebug()
{
	{
		auto text1 = Node::create();
		auto fontCom = text1->addComponent<FontRanderComponent>();
		fontCom->setFont(DEFAULTE_FONT_FILE);
		fontCom->setFontSize(30);
		fontCom->setText(L"这里是debug信息");

		_debug->addChild(text1);

		text1->setPosition(0, 0);
		text1->setScale(1,1);
		text1->setTag(1);
		text1->setColor(Vector4(1, 1, 1, 0.6));
	}
	{
		auto text1 = Node::create();
		auto fontCom = text1->addComponent<FontRanderComponent>();
		fontCom->setFont(DEFAULTE_FONT_FILE);
		fontCom->setFontSize(30);
		fontCom->setText(L"这里是debug信息");

		_debug->addChild(text1);

		text1->setPosition(0, 30);
		text1->setScale(1, 1);
		text1->setTag(1);
		text1->setColor(Vector4(1, 1, 1, 0.6));
	}
}

void GameUI::reshape()
{
	auto w = GameApp::getInstance()->getViewWidth();
	auto h = GameApp::getInstance()->getViewHeight();

	//_leftBottom->setPosition(0, 0);
	_leftTop->setPosition(0, h);
	_rightBottom->setPosition(w, 0);
	_rightTop->setPosition(w, h);
	_center->setPosition(w / 2, h / 2);
}

void GameUI::update(GLfloat time)
{
	static float t_time = 0.f;
	static int frame = 0;
	static int timebase = 0;
	//char s[256] = { 0 };
	static wchar_t s[256] = { 0 };
	frame++;
	t_time = t_time + time;
	if (t_time - timebase > 1) {
		//sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));

		swprintf(s, 256, L"FPS:%4.2f  node数量：%d", frame * 1.0 / (t_time - timebase), GameApp::getInstance()->getNodeCount());
		timebase = t_time;
		frame = 0;

		//SPFontDrawNode txt = dynamic_pointer_cast<FontDrawNode>(_debug->getChildByTag(1));
		auto txt_node = _debug->getChildByTag(1);
		auto fontCom = txt_node->getComponent<FontRanderComponent>();
		if (fontCom)
		{
			fontCom->setText(s);
		}
	}
}
