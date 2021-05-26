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
#include "component/ConllisionComponent/CollisionActorComponent.h"
#include "component/ActorAIComponent.h"


void GameMainFight::init()
{
	auto colContr = CollisionController::getInstance();//≥ı ºªØ

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
	auto playerCollCom = _player->addComponent<CollisionActorComponent>();
	playerCollCom->enableCollision(CMARK_SELF, CMARK_SELF | CMARK_ENEMY | CMARK_ENEMY_BULLET | CMARK_STONE);
	_player->getComponent<ActorStateComponent>()->setCamp(ACTORCAMP_PLAYER);

	auto target1 = Actor::create();
	_objectLayer->addChild(target1);
	target1->setPosition(500, 100);
	target1->getComponent<ActorStateComponent>()->setName(L"ƒæ◊Æ");

	auto target1CollCom = target1->addComponent<CollisionActorComponent>();
	target1CollCom->enableCollision(CMARK_ENEMY, CMARK_SELF | CMARK_ENEMY | CMARK_SELF_BULLET | CMARK_STONE);
	auto target1_stateCom = target1->getComponent<ActorStateComponent>();
	target1_stateCom->setCamp(ACTORCAMP_ENEMY);

	auto target1_sm = target1_stateCom->getStateData(STATE_FIRE);
	target1_sm->_time = 3;

	target1->addComponent<ActorAIComponent>();

	for (int i = 0; i < 20; i++)
	{
		auto target2 = Actor::create();
		_objectLayer->addChild(target2);
		target2->setPosition(rand() % 800 + 100, rand() % 500 + 40);
		target2->getComponent<ActorStateComponent>()->setName(L"ƒæ◊Æ");
		auto target2CollCom = target2->addComponent<CollisionActorComponent>();
		target2CollCom->enableCollision(CMARK_ENEMY, CMARK_SELF | CMARK_ENEMY | CMARK_SELF_BULLET | CMARK_STONE);
		target2->getComponent<ActorStateComponent>()->setCamp(ACTORCAMP_ENEMY);
	}


	TimerController::getInstance()->addTimer(0, -1, std::bind(&GameMainFight::update, this, std::placeholders::_1));
}

void GameMainFight::restart()
{
}

void GameMainFight::update(float time)
{
	CollisionController::getInstance()->collisionDetection();
	return;
}
