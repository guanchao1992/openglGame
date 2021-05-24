#include "CollisionActorComponent.h"
#include <GameApp.h>
#include "control/CollisionController.h"
#include <Game2DFight/Actor.h>
#include <Game2DFight/Bullet.h>
#include "CollisionBulletComponent.h"
#include "../ActorMoveComponent.h"
#include "../ActorStateComponent.h"
#include "../BulletStateComponent.h"


void CollisionActorComponent::doBegin()
{
	__super::doBegin();

}

void CollisionActorComponent::doEnd()
{
	__super::doEnd();
}

void CollisionActorComponent::collision(Object*other)
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (actor)
	{
		auto otherColCom = other->getComponent<CollisionBulletComponent>();
		//ÅÐ¶ÏÊÇ·ñÎª×Óµ¯
		//CollisionBulletComponent* othercbc = dynamic_cast<CollisionBulletComponent*>(otherColCom);
		//auto otherStateCom = other->getComponent<BulletStateComponent>();
		auto otherStateCom = dynamic_cast<BulletStateComponent*>(other->getComponent(COMPONENT_BULLET_STATE));
		if (otherStateCom)
		{
			auto stateCom = _object->getComponent<ActorStateComponent>();
			stateCom->enterState(STATE_HIT);
			stateCom->setHP(stateCom->getHP() - otherStateCom->getAttack());
		}
		else {
			auto amc = _object->getComponent<ActorMoveComponent>();
			if (amc)
			{
				auto app = GameApp::getInstance();
				auto other_node = dynamic_cast<Node*>(other);
				auto p = actor->getPosition() - other_node->getPosition();
				auto r = atan2(p._y, p._x);

				amc->setSpeed(amc->getSpeed() + Vector2(cosf(r) * _weight * app->getLastTime() * 2000, sinf(r) * _weight * app->getLastTime() * 2000));
			}
		}
	}
}
