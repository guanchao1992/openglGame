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

	_player = Actor::create();
	addChild(_player);
	_player->setPosition(100, 100);
	_player->addComponent<ActorOIComponent>();
}

void GameMainFight::restart()
{

}

