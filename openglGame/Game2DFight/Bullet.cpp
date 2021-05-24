#include "Bullet.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletStateComponent.h"


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
