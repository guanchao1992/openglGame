#include "GameUI.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>
#include <2d/FontDrawNode.h>
#include <corecrt_wstdio.h>
#include "tables/ItemTable.h"


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

	auto fontNode = FontDrawNode::create(DEFAULTE_FONT_FILE);
	fontNode->setFontSize(30);
	addChild(fontNode);
	fontNode->setPosition(200, 100);
	fontNode->setScale(1, 1);
	fontNode->setTag(1);
	auto item1 = ItemTableDatas::getData(10001);
	fontNode->setText(item1->_name);

	_debug = Node::create();
	_leftBottom->addChild(_debug, 1000);
	
	initBk();
	initDebug();
}

void GameUI::initBk()
{
	auto fd1 = FillDrawNode::create();
	fd1->addVertex(Vector2(0, 0));
	fd1->addVertex(Vector2(0, 100));
	fd1->addVertex(Vector2(3, 100));
	fd1->addVertex(Vector2(3, 3));
	fd1->addVertex(Vector2(100, 3));
	fd1->addVertex(Vector2(100, 0));
	fd1->setColor(Vector4(1, 0, 0, 0.6));
	fd1->setPosition(30, 30);
	_leftBottom->addChild(fd1);

	auto fd2 = FillDrawNode::create();
	fd2->addVertex(Vector2(0, 0));
	fd2->addVertex(Vector2(0, -100));
	fd2->addVertex(Vector2(3, -100));
	fd2->addVertex(Vector2(3, -3));
	fd2->addVertex(Vector2(100, -3));
	fd2->addVertex(Vector2(100, 0));
	fd2->setColor(Vector4(1, 0, 0, 0.6));
	fd2->setPosition(30, -30);
	_leftTop->addChild(fd2);

	auto fd3 = FillDrawNode::create();
	fd3->addVertex(Vector2(0, 0));
	fd3->addVertex(Vector2(0, 100));
	fd3->addVertex(Vector2(-3, 100));
	fd3->addVertex(Vector2(-3, 3));
	fd3->addVertex(Vector2(-100, 3));
	fd3->addVertex(Vector2(-100, 0));
	fd3->setColor(Vector4(1, 0, 0, 0.6));
	fd3->setPosition(-30, 30);
	_rightBottom->addChild(fd3);

	auto fd4 = FillDrawNode::create();
	fd4->addVertex(Vector2(0, 0));
	fd4->addVertex(Vector2(0, -100));
	fd4->addVertex(Vector2(-3, -100));
	fd4->addVertex(Vector2(-3, -3));
	fd4->addVertex(Vector2(-100, -3));
	fd4->addVertex(Vector2(-100, 0));
	fd4->setColor(Vector4(1, 0, 0, 0.6));
	fd4->setPosition(-30, -30);
	_rightTop->addChild(fd4);

	auto fd5 = FillDrawNode::create();
	fd5->addVertex(Vector2(1, 1));
	fd5->addVertex(Vector2(100, 1));
	fd5->addVertex(Vector2(100, -1));
	fd5->addVertex(Vector2(1, -1));
	fd5->addVertex(Vector2(1, -100));
	fd5->addVertex(Vector2(-1, -100));
	fd5->addVertex(Vector2(-1, -1));
	fd5->addVertex(Vector2(-100, -1));
	fd5->addVertex(Vector2(-100, 1));
	fd5->addVertex(Vector2(-1, 1));
	fd5->addVertex(Vector2(-1, 100));
	fd5->addVertex(Vector2(1, 100));
	fd5->setColor(Vector4(1, 0, 0, 0.6));
	fd5->setPosition(0, 0);
	_center->addChild(fd5);
}

void GameUI::initDebug()
{
	{
		auto text1 = FontDrawNode::create(DEFAULTE_FONT_FILE);
		text1->setFontSize(30);
		_debug->addChild(text1);
		text1->setText(L"������debug��Ϣ");
		text1->setPosition(0, 0);
		text1->setScale(1,1);
		text1->setTag(1);
	}
	{
		auto text1 = FontDrawNode::create(DEFAULTE_FONT_FILE);
		text1->setFontSize(30);
		_debug->addChild(text1);
		text1->setText(L"������debug��Ϣ");
		text1->setPosition(0, 30);
		text1->setScale(1, 1);
		text1->setTag(1);
		_listener->listen([&, text1](const MouseMoveEvent& et) {
			wchar_t s[256];
			swprintf(s, 256, L"x:%.2f,y:%.2f,bts:%d", et._x, et._y, et._buttons);
			text1->setText(s);
		});
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

		swprintf(s, 256, L"FPS:%4.2f  node������%d", frame * 1.0 / (t_time - timebase), GameApp::getInstance()->getNodeCount());
		timebase = t_time;
		frame = 0;

		SPFontDrawNode txt = dynamic_pointer_cast<FontDrawNode>(_debug->getChildByTag(1));
		txt->setText(s);
	}
}