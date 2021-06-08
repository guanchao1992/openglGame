#include "Actor.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/ActorMoveComponent.h"
#include "component/ActorTipsComponent.h"
#include "Bullet.h"
#include <GameApp.h>
#include "component/BulletComponent/BMCComponentS.h"
#include "component/BulletComponent/BMCComponentK.h"
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletComponent/BMCComponentS1.h"
#include "component/BulletComponent/BMCComponentS2.h"
#include "component/ConllisionComponent/CollisionComponent.h"
#include "component/ConllisionComponent/CollisionBulletComponent.h"
#include "component/ConllisionComponent/CollisionActorComponent.h"
#include "component/ActorStateComponent.h"
#include "component/BulletStateComponent.h"
#include "2d/DrawProgress.h"
#include "component/ActorSkillComponent.h"


void Actor::init()
{

	
	auto atCom = addComponent<ActorTipsComponent>();
	auto amCom = addComponent<ActorMoveComponent>();
	auto stateCom = addComponent<ActorStateComponent>();

	auto drawCom = addComponent<DrawRanderComponent>();
	drawCom->addVertex(Vector3(0.f, 0, 0), Vector4(0.1, 0.1, 0.8, 1));
	drawCom->addVertex(Vector3(40.f, 0, 0), Vector4(0.1, 0.1, 0.8, 1));
	drawCom->addVertex(Vector3(40.f, 60, 0), Vector4(0.1, 0.1, 0.8, 1));
	drawCom->addVertex(Vector3(0.f, 60, 0), Vector4(0.1, 0.1, 0.8, 1));
	drawCom->signDraw(GL_TRIANGLE_FAN);

	//addComponent<OutlineBoxComponent>();
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(0.5, 0));
	areaCom->setSize(Size(40, 60));

}

void Actor::fire(const Vector3&aim)
{
	auto stateCom = getComponent<ActorStateComponent>();
	if (!stateCom)
		return;

	auto asCom = getComponent<ActorSkillComponent>();
	if (!asCom)
		return;

	auto l = atan2(aim._y, aim._x) / PI * 180;
	asCom->fire(30001, l);

	return;

	if (stateCom->enterState(STATE_FIRE))
	{
		float vec[] = { aim._x,aim._y };
		glusVector2Normalizef(vec);
		//发射
		for (int i = 0; i < 1; i++)
		{
			auto b = Bullet::create(this);
			b->setDir(Vector2(aim._x, aim._y));
			b->setSpeed(400.f);
			auto bsCom = b->getComponent<BulletStateComponent>();
			bsCom->setAttack(stateCom->getAttack());
			bsCom->setCamp(stateCom->getCamp());
			GameApp::getInstance()->_start->addChild(b);
			b->setPosition(getPosition()._x, getPosition()._y);

			/*
			b->addComponent<BMCComponentS>();
			b->addComponent<BMCComponentS1>();
			b->addComponent<BMCComponentS2>();
			*/

			auto bulletCollCom = b->addComponent<CollisionBulletComponent>();
			auto collCom = getComponent<CollisionActorComponent>();
			if (collCom)
			{
				switch (collCom->getFlagMark())
				{
				case  CMARK_SELF:
				case  CMARK_SELF_BULLET:
					bulletCollCom->enableCollision(CMARK_SELF_BULLET, CMARK_ENEMY | CMARK_STONE);
					break;
				case  CMARK_ENEMY:
				case  CMARK_ENEMY_BULLET:
					bulletCollCom->enableCollision(CMARK_ENEMY_BULLET, CMARK_SELF | CMARK_STONE);
					break;
				case  CMARK_FRIENDLY:
				case  CMARK_FRIENDLY_BULLET:
					bulletCollCom->enableCollision(CMARK_FRIENDLY_BULLET, CMARK_ENEMY | CMARK_STONE);
					break;
				case  CMARK_STONE:
				case  CMARK_NEUTRAL:
				case  CMARK_NEUTRAL_BULLET:
					//他们(石头和中立单位)应该不会开枪
				default:
					break;
				}

			}
		}
	}
}
