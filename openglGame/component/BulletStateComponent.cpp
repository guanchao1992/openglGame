#include "BulletStateComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/ActorMoveComponent.h"
#include "component/ActorTipsComponent.h"
#include <GameApp.h>
#include "component/BulletComponent/BMCComponentS.h"
#include "component/BulletComponent/BMCComponentK.h"
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletComponent/BMCComponentS1.h"
#include "component/BulletComponent/BMCComponentS2.h"
#include "component/ConllisionComponent/CollisionComponent.h"
#include "component/ConllisionComponent/CollisionBulletComponent.h"
#include "component/ConllisionComponent/CollisionActorComponent.h"
#include "DrawRanderComponent.h"
#include "Game2DFight/Bullet.h"

void BulletStateComponent::doBegin()
{
	__super::doBegin();

	//_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&BulletStateComponent::update, this, std::placeholders::_1));

}

void BulletStateComponent::doEnd()
{
	__super::doEnd();
	//TimerController::getInstance()->killTimer(_timerId);
}

void BulletStateComponent::update(float time)
{

}

