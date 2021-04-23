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
#include "component/EventComponent.h"


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


	auto eventCom = addComponent<EventComponent>();
	eventCom->addEvent(EVENT_GAME_RESTART, [&](Object*obj, const Event&event) {
		auto childs = getChilds();
		for (auto child : childs)
		{
			child->removeAllChild();
		}
		initBk();
		initDebug();
		showStartUI();
	});
	eventCom->addEvent(EVENT_KEY, [&](Object*obj, const Event&event) {
		const KeyEvent& ke = (KeyEvent&)event;
		if (ke._isDown)
		{
			switch (ke._key)
			{
			case 'r':
			case 'R':
				GameApp::getInstance()->postEvent(EVENT_GAME_RESTART);
				break;
			case 'q':
			case 'Q':
			{
				auto childs = getChilds();
				for (auto child : childs)
				{
					child->removeAllChild();
				}
			}
			break;
			default:
				break;
			}
		}
	});
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
}

void GameUI::initDebug()
{
	_debug = Node::create();
	_leftBottom->addChild(_debug, 1000);

	auto text1 = Text::create(L"这里是debug信息", DEFAULTE_FONT_FILE, 24);
	text1->addComponent<OutlineBoxComponent>();
	_debug->addChild(text1);
	text1->setPosition(10, 10);
	text1->setScale(1, 1);
	text1->setTag(1);
	text1->setColor(Vector4(1, 1, 1, 0.6));
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
	//static char s[256] = { 0 };
	static wchar_t s[256] = { 0 };
	frame++;
	t_time = t_time + time;
	if (t_time - timebase > 1) {
		//sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));

		swprintf_s(s, 256, L"FPS:%4.2f  node数量：%d", frame * 1.0 / (t_time - timebase), GameApp::getInstance()->getNodeCount());

		timebase = t_time;
		frame = 0;

		//SPFontDrawNode txt = dynamic_pointer_cast<FontDrawNode>(_debug->getChildByTag(1));
		auto txt_node = _debug->getChildByTag(1);
		if (txt_node)
		{
			auto fontCom = txt_node->getComponent<FontRanderComponent>();
			if (fontCom)
			{
				fontCom->setText(s);
			}
		}
	}
}

void GameUI::showStartUI()
{
	auto node_start_uis = Node::create();
	_rightTop->addChild(node_start_uis);
	{
		auto btn_start = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_start->setTitle(L"开始", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_start);
		btn_start->setPosition(-200, -140);
		btn_start->setCallBack([&]() {
			printf("开始游戏");
			//node_start_uis->removeFromParent();
		});
	}
	{
		auto btn_setting = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_setting->setTitle(L"设置", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_setting);
		btn_setting->setPosition(-200, -200);
		btn_setting->setCallBack([]() {

		});
	}
	{
		auto btn_exit = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_exit->setTitle(L"退出", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_exit);
		btn_exit->setPosition(-200, -260);
		btn_exit->setCallBack([]() {
			exit(0);
		});
	}
}

void GameUI::showGameUI()
{
	auto game_ui_lt = Node::create();
	_leftTop->addChild(game_ui_lt);
	{
		auto game_ui_lt = Node::create();
		_leftTop->addChild(game_ui_lt);
	}

}
