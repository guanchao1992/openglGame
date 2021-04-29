#include "BulletMoveKComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"
#include "Game2DFight/Bullet.h"

void BulletMoveKComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&BulletMoveKComponent::update, this, std::placeholders::_1));

	auto bmc = _object->getComponent<BulletMoveComponent>();
	_defaultSpeed = bmc->getSpeed();
	_defaultRadian = atan2f(_defaultSpeed._y, _defaultSpeed._x);
}

void BulletMoveKComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

bool BulletMoveKComponent::update(float time)
{
	if (!_active)
		return false;
	_accumulatedTime += time;
	if (_accumulatedTime > 0.8)
	{
		_accumulatedTime = 0;
		auto originBullet = (Bullet*)_object;
		auto bmc = originBullet->getComponent<BulletMoveComponent>();

		auto radian1 = _defaultRadian + PI / 8;
		auto radian3 = _defaultRadian - PI / 8;
		auto p = (_defaultSpeed._x + _defaultSpeed._y) / 8;

		auto b1 = Bullet::create(originBullet->getFather(), _defaultSpeed + Vector2(p * cosf(radian1), p * sinf(radian1)));
		auto b2 = Bullet::create(originBullet->getFather(), _defaultSpeed + Vector2(p * cosf(_defaultRadian), p * sinf(_defaultRadian)));
		auto b3 = Bullet::create(originBullet->getFather(), _defaultSpeed + Vector2(p * cosf(radian3), p * sinf(radian3)));
		originBullet->getParent()->addChild(b1);
		originBullet->getParent()->addChild(b2);
		originBullet->getParent()->addChild(b3);
		b1->setPosition(originBullet->getPosition());
		b2->setPosition(originBullet->getPosition());
		b3->setPosition(originBullet->getPosition());
		originBullet->removeFromParent();
	}

	return false;
}
