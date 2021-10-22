#include "Bullet.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include "component/FontRanderComponent.h"
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletStateComponent.h"
#include "component/ConllisionComponent/CollisionBulletComponent.h"
#include "component/ConllisionComponent/CollisionActorComponent.h"


SPBullet Bullet::create(Actor* father)
{
	auto ret = make_shared<Bullet>();
	ret->_father = father;
	ret->init();
	return ret;
}
	
void Bullet::init()
{
	_name = Text::create(L"µ¯", DEFAULTE_FONT_FILE, 24);
	auto nameAreaCom = _name->getComponent<AreaComponent>();
	nameAreaCom->setAnchor(Vector2(0.5, 0.5));
	addChild(_name);
	_name->setPosition(0, 0);

	addComponent<OutlineBoxComponent>();
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(0.5, 0.5));
	areaCom->setSize(Size(20, 20));

	auto bmCom = addComponent<BulletMoveComponent>();
	auto bsCom = addComponent<BulletStateComponent>();

	initComp();
}

void Bullet::initComp()
{
	auto bulletCollCom = addComponent<CollisionBulletComponent>();
	if (!_father) {
		bulletCollCom->enableCollision(CMARK_NEUTRAL_BULLET, CMARK_SELF | CMARK_FRIENDLY | CMARK_ENEMY | CMARK_STONE);
		return;
	}
	auto collCom = _father->getComponent<CollisionActorComponent>();
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
			bulletCollCom->enableCollision(CMARK_NEUTRAL_BULLET, CMARK_SELF | CMARK_FRIENDLY | CMARK_ENEMY | CMARK_STONE);
			break;
		default:
			break;
		}

	}

}

void Bullet::setSpeed(float speed, float radian)
{
	auto bmc = getComponent<BulletMoveComponent>();
	bmc->setSpeedOriginal(speed);
	bmc->setDirOriginal(radian);
}

void Bullet::setSpeed(float speed)
{
	auto bmc = getComponent<BulletMoveComponent>();
	bmc->setSpeedOriginal(speed);
}

void Bullet::setSpeed(const Vector2&speed)
{
	auto bmc = getComponent<BulletMoveComponent>();
	bmc->setSpeedOriginal(speed);
}

void Bullet::setDir(const Vector2&dir)
{
	auto bmc = getComponent<BulletMoveComponent>();
	bmc->setDirOriginal(dir);
}
