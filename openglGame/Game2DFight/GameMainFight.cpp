#include "GameMainFight.h"
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
#include "Actor.h"
#include "component/ActorMoveComponent.h"
#include "component/ActorOIComponent.h"
#include "control/CollisionController.h"


void GameMainFight::init()
{
	auto colContr = CollisionController::getInstance();//��ʼ��

	auto areaCom = addComponent<AreaComponent>();
	areaCom->setSize(Size(10000, 10000));
	areaCom->setAnchor(Vector2(0.5, 0.5));
	auto mouseCom = addComponent<MouseComponent>();
	mouseCom->setMouseKeyFunc([this](MouseComponent&mouseCon, const MouseKeyEvent&event) {
	});
	mouseCom->setMouseMoveFunc([this](MouseComponent&mouseCon, const MouseMoveEvent&event) {
	});

	_objectLayer = Node::create();
	addChild(_objectLayer, 10);

	_player = Actor::create();
	_objectLayer->addChild(_player);
	_player->setPosition(100, 100);
	_player->addComponent<ActorOIComponent>();
	auto playerCollCom = _player->addComponent<CollisionComponent>();
	playerCollCom->enableCollision(CMARK_SELF, CMARK_ENEMY | CMARK_ENEMY_BULLET | CMARK_STONE);

	/*
	auto target1 = Actor::create();
	_objectLayer->addChild(target1);
	target1->setPosition(500, 100);
	target1->setName(L"ľ׮");
	auto target1CollCom = target1->addComponent<CollisionComponent>();
	target1CollCom->enableCollision(CMARK_ENEMY, CMARK_SELF | CMARK_SELF_BULLET | CMARK_STONE);

	for (int i = 0; i < 20; i++)
	{
		auto target2 = Actor::create();
		_objectLayer->addChild(target2);
		target2->setPosition(rand() % 800 + 100, rand() % 500 + 40);
		target2->setName(L"ľ׮");
		auto target2CollCom = target2->addComponent<CollisionComponent>();
		target2CollCom->enableCollision(CMARK_ENEMY, CMARK_SELF | CMARK_SELF_BULLET | CMARK_STONE);
	}
	*/


	TimerController::getInstance()->addTimer(0, -1, std::bind(&GameMainFight::update, this, std::placeholders::_1));
}

void GameMainFight::restart()
{
}

bool GameMainFight::update(float time)
{
	CollisionController::getInstance()->collisionDetection();
	return false;
}
