#include "GameUI.h"
#include "2d/FillDrawNode.h"
#include "EgameController.h"
#include "GameEvent.h"
#include "GameApp.h"
#include "control/TimerController.h"
#include <math.h>
#include <2d/FontDrawNode.h>


void GameUI::init()
{
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

	_debug = Node::create();
	addChild(_debug);
	
	initBk();
	initDebug();
}

void GameUI::initBk()
{
	auto fd1 = FillDrawNode::create();
	fd1->addVertex(Vector2(0, 0));
	fd1->addVertex(Vector2(0, 100));
	fd1->addVertex(Vector2(10, 100));
	fd1->addVertex(Vector2(10, 10));
	fd1->addVertex(Vector2(100, 10));
	fd1->addVertex(Vector2(100, 0));
	fd1->setColor(Vector4(1, 0, 0, 0.6));
	fd1->setPosition(30, 30);
	_leftBottom->addChild(fd1);

	auto fd2 = FillDrawNode::create();
	fd2->addVertex(Vector2(0, 0));
	fd2->addVertex(Vector2(0, -100));
	fd2->addVertex(Vector2(10, -100));
	fd2->addVertex(Vector2(10, -10));
	fd2->addVertex(Vector2(100, -10));
	fd2->addVertex(Vector2(100, 0));
	fd2->setColor(Vector4(1, 0, 0, 0.6));
	fd2->setPosition(30, -30);
	_leftTop->addChild(fd2);

	auto fd3 = FillDrawNode::create();
	fd3->addVertex(Vector2(0, 0));
	fd3->addVertex(Vector2(0, 100));
	fd3->addVertex(Vector2(-10, 100));
	fd3->addVertex(Vector2(-10, 10));
	fd3->addVertex(Vector2(-100, 10));
	fd3->addVertex(Vector2(-100, 0));
	fd3->setColor(Vector4(1, 0, 0, 0.6));
	fd3->setPosition(-30, 30);
	_rightBottom->addChild(fd3);

	auto fd4 = FillDrawNode::create();
	fd4->addVertex(Vector2(0, 0));
	fd4->addVertex(Vector2(0, -100));
	fd4->addVertex(Vector2(-10, -100));
	fd4->addVertex(Vector2(-10, -10));
	fd4->addVertex(Vector2(-100, -10));
	fd4->addVertex(Vector2(-100, 0));
	fd4->setColor(Vector4(1, 0, 0, 0.6));
	fd4->setPosition(-30, -30);
	_rightTop->addChild(fd4);

	auto fd5 = FillDrawNode::create();
	fd5->addVertex(Vector2(5, 5));
	fd5->addVertex(Vector2(100, 5));
	fd5->addVertex(Vector2(100, -5));
	fd5->addVertex(Vector2(5, -5));
	fd5->addVertex(Vector2(5, -100));
	fd5->addVertex(Vector2(-5, -100));
	fd5->addVertex(Vector2(-5, -5));
	fd5->addVertex(Vector2(-100, -5));
	fd5->addVertex(Vector2(-100, 5));
	fd5->addVertex(Vector2(-5, 5));
	fd5->addVertex(Vector2(-5, 100));
	fd5->addVertex(Vector2(5, 100));
	fd5->setColor(Vector4(1, 0, 0, 0.6));
	fd5->setPosition(0, 0);
	_center->addChild(fd5);
}

void GameUI::initDebug()
{
	auto debugText1 = FontDrawNode::create(DEFAULTE_FONT_FILE);

	{
		auto text1 = FontDrawNode::create("res/simhei.ttf");
		text1->setFontSize(10);
		addChild(text1, 10000);
		text1->setText(L"abc中文def");
		text1->setPosition(300, 100);
		text1->setScale(3,3);
	}
	{
		auto text1 = FontDrawNode::create("res/simhei.ttf");
		text1->setFontSize(14);
		addChild(text1, 10000);
		text1->setText(L"abc中文def");
		text1->setPosition(300, 130);
		text1->setScale(3,3);
	}
	{
		auto text1 = FontDrawNode::create("res/simhei.ttf");
		text1->setFontSize(18);
		addChild(text1, 10000);
		text1->setText(L"abc中文def");
		text1->setPosition(300, 160);
		text1->setScale(3, 3);
	}
	{
		auto text1 = FontDrawNode::create("res/simhei.ttf");
		text1->setFontSize(20);
		addChild(text1, 10000);
		text1->setText(L"abc中文def");
		text1->setPosition(300, 190);
		text1->setScale(3, 3);
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
	char s[256] = { 0 };
	frame++;
	t_time = t_time + time;
	if (t_time - timebase > 1) {
		sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));
		timebase = t_time;
		frame = 0;
		printf("帧率为：%s\n", s);
	}
}
