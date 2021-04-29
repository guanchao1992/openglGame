#include "Bullet.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/BulletComponent/BulletMoveComponent.h"


SPBullet Bullet::create(Actor* father, const Vector2&speed)
{
	auto ret = make_shared<Bullet>();
	ret->_father = father;
	ret->init(speed);
	return ret;
}
	
void Bullet::init(const Vector2&speed)
{
	_name = Text::create(L"µ¯", DEFAULTE_FONT_FILE, 24);
	_name->addComponent<OutlineBoxComponent>();
	auto nameAreaCom = _name->getComponent<AreaComponent>();
	nameAreaCom->setAnchor(Vector2(0.5, 0.5));
	addChild(_name);
	_name->setPosition(0, 0);

	addComponent<OutlineBoxComponent>();
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(0.5, 0.5));
	areaCom->setSize(Size(20, 20));

	auto bmCom = addComponent<BulletMoveComponent>();

	bmCom->setSpeed(speed);

}
