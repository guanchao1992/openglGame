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


void GameMainFight::init()
{
	auto areaCom = addComponent<AreaComponent>();
	areaCom->setSize(Size(10000, 10000));
	areaCom->setAnchor(Vector2(0.5, 0.5));
	auto mouseCom = addComponent<MouseComponent>();
	mouseCom->setMouseKeyFunc([&](MouseComponent&mouseCon, const MouseKeyEvent&event) {
	});
	mouseCom->setMouseMoveFunc([&](MouseComponent&mouseCon, const MouseMoveEvent&event) {
	});

	_objectLayer = Node::create();
	addChild(_objectLayer, 10);

	_player = Actor::create();
	_objectLayer->addChild(_player);
	_player->setPosition(100, 100);
	_player->addComponent<ActorOIComponent>();
	

	auto target1 = Actor::create();
	_objectLayer->addChild(target1);
	target1->setPosition(500, 100);
	target1->setName(L"ľ׮");

	auto target2 = Actor::create();
	_objectLayer->addChild(target2);
	target2->setPosition(500, 300);
	target2->setName(L"ľ׮");
}

void GameMainFight::restart()
{

}

