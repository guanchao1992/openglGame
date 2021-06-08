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
#include <component/BulletComponent/BMCComponent.h>


void GameUI::init()
{
	auto app = GameApp::getInstance();
	_listener = app->createListenerSP();
	auto w = app->getProjectWidth();
	auto h = app->getProjectHeight();

	auto areaCom = addComponent<AreaComponent>();
	areaCom->setSize(Size(w, h));
	addComponent<OutlineBoxComponent>();
	areaCom->setAnchor(Vector2(0.5, 0.5));
	
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

	_leftBottom->setPosition(0, 0);
	_leftTop->setPosition(0, h);
	_rightBottom->setPosition(w, 0);
	_rightTop->setPosition(w, h);
	_center->setPosition(w / 2, h / 2);

	//setScale(0.5);

	auto eventCom = addComponent<EventComponent>();
	eventCom->addEvent(EVENT_GAME_RESTART, [this](Object*obj, const Event&event) {
		auto childs = getChilds();
		for (auto child : childs)
		{
			child->removeAllChild();
		}
		initBk();
		initDebug();
		showStartUI();
	});
	eventCom->addEvent(EVENT_KEY, [this](Object*obj, const Event&event) {
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
			case 'o':
			case 'O':
			{
				SPNode a = Node::create();
				//std::list<SPNode> _visitLeft = list<SPNode>>();
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
	Vector4 bgcolor(0.4, 0.4, 0.2, 0.3);
	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector3(0, 0, 0), bgcolor);
		drawCom->addVertex(Vector3(0, 100, 0), bgcolor);
		drawCom->addVertex(Vector3(20, 100, 0), bgcolor);
		drawCom->addVertex(Vector3(20, 20, 0), bgcolor);
		drawCom->addVertex(Vector3(100, 20, 0), bgcolor);
		drawCom->addVertex(Vector3(100, 0,0), bgcolor);
		fd->setPosition(0, 0);
		_leftBottom->addChild(fd);
		fd->setTag(100);
	}

	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector3(0, 0, 0), bgcolor);
		drawCom->addVertex(Vector3(0, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(20, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(20, -20, 0), bgcolor);
		drawCom->addVertex(Vector3(100, -20, 0), bgcolor);
		drawCom->addVertex(Vector3(100, 0, 0), bgcolor);
		fd->setPosition(0, -0);
		_leftTop->addChild(fd);
		fd->setTag(100);
	}

	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector3(0, 0, 0), bgcolor);
		drawCom->addVertex(Vector3(0, 100, 0), bgcolor);
		drawCom->addVertex(Vector3(-20, 100, 0), bgcolor);
		drawCom->addVertex(Vector3(-20, 20, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, 20, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, 0, 0), bgcolor);
		fd->setPosition(-0, 0);
		_rightBottom->addChild(fd);
		fd->setTag(100);
	}

	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector3(0, 0, 0), bgcolor);
		drawCom->addVertex(Vector3(0, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(-20, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(-20, -20, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, -20, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, 0, 0), bgcolor);
		fd->setPosition(-0, -0);
		_rightTop->addChild(fd);
		fd->setTag(100);
	}

	{
		auto fd = Node::create();
		auto drawCom = fd->addComponent<DrawRanderComponent>();
		drawCom->addVertex(Vector3(1, 1, 0), bgcolor);
		drawCom->addVertex(Vector3(100, 1, 0), bgcolor);
		drawCom->addVertex(Vector3(100, -1, 0), bgcolor);
		drawCom->addVertex(Vector3(1, -1, 0), bgcolor);
		drawCom->addVertex(Vector3(1, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(-1, -100, 0), bgcolor);
		drawCom->addVertex(Vector3(-1, -1, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, -1, 0), bgcolor);
		drawCom->addVertex(Vector3(-100, 1, 0), bgcolor);
		drawCom->addVertex(Vector3(-1, 1, 0), bgcolor);
		drawCom->addVertex(Vector3(-1, 100, 0), bgcolor);
		drawCom->addVertex(Vector3(1, 100, 0), bgcolor);
		_center->addChild(fd);
		fd->setTag(100);
	}

	/*
	addTimer(0, -1, [this](float time) {
		static float total_time = 0;
		total_time = total_time + time;
		_leftBottom->getChildByTag(100)->setAngleCoordinate(90 * total_time, 0, 0);
		_leftTop->getChildByTag(100)->setAngleCoordinate(90 * total_time, 0, 0);
		_rightBottom->getChildByTag(100)->setAngleCoordinate(90 * total_time, 0, 0);
		_rightTop->getChildByTag(100)->setAngleCoordinate(90 * total_time, 0, 0);
		_center->getChildByTag(100)->setAngleCoordinate(90 * total_time, 0, 0);
		return false;
	});
	*/
}

void GameUI::initDebug()
{
	_debug = Node::create();
	_leftBottom->addChild(_debug, 1000);
	setPosition(0, 0, 0);

	auto text1 = Text::create(L"������debug��Ϣ", DEFAULTE_FONT_FILE, 24);
	auto textAreaCom = text1->addComponent<AreaComponent>();
	textAreaCom->setAnchor(Vector2(0.5, 0.5));
	text1->addComponent<OutlineBoxComponent>();
	_debug->addChild(text1);
	text1->setPosition(0, 0);
	text1->setScale(1, 1, 1);
	text1->setTag(1);
	text1->setColor(Vector4(1, 1, 1, 0.6));

	auto textAreaCom2 = text1->getComponent<AreaComponent>();

	_debug->addTimer(0, -1, [this](float time) {
		static float t_time = 0.f;
		static int frame = 0;
		static int timebase = 0;
		//static char s[256] = { 0 };
		static wchar_t s[256] = { 0 };
		frame++;
		t_time = t_time + time;
		if (t_time > 1.f) {
			//sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));

			swprintf_s(s, 256, L"FPS:%4.2f  node������%d", frame * 1.0f / t_time, GameApp::getInstance()->getNodeCount());

			timebase = t_time;
			t_time = 0;
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
		return false; 
	});
}

void GameUI::reshape()
{
	__super::reshape();
	
	auto w = GameApp::getInstance()->getProjectWidth();
	auto h = GameApp::getInstance()->getProjectHeight();
	//setScale(0.5);

}

void GameUI::showStartUI()
{
	auto node_start_uis = Node::create();
	_rightTop->addChild(node_start_uis);
	{
		auto btn_start = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_start->setTitle(L"��ʼ", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_start);
		btn_start->setPosition(-130, -140);
		btn_start->setCallBack([this]() {
			printf("��ʼ��Ϸ");
			//node_start_uis->removeFromParent();
		});
		btn_start->setAngleCoordinate(0, 1, 0);
	}
	{
		auto btn_start = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_start->setTitle(L"��ʼ2", DEFAULTE_FONT_FILE, 24);
		_leftBottom->addChild(btn_start);
		btn_start->setPosition(300, 0);
		btn_start->setCallBack([this]() {
			printf("��ʼ��Ϸ2");
			//node_start_uis->removeFromParent();
		});
		btn_start->setAngleCoordinate(0, 1, 0);
	}
	/*
	{
		auto btn_setting = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_setting->setTitle(L"����", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_setting);
		btn_setting->setPosition(-130, -200);
		btn_setting->setCallBack([]() {

		});
	}
	{
		auto btn_exit = Button::create("./res/btn_normal.png", "./res/btn_select.png");
		btn_exit->setTitle(L"�˳�", DEFAULTE_FONT_FILE, 24);
		node_start_uis->addChild(btn_exit);
		btn_exit->setPosition(-130, -260);
		btn_exit->setCallBack([]() {
			exit(0);
		});
	}
	*/
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
