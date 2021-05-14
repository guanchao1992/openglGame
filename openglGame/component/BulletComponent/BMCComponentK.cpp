#include "BMCComponentK.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"
#include "Game2DFight/Bullet.h"

void BMCComponentK::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentK::doEnd()
{
	__super::doEnd();
}

void BMCComponentK::update(float time)
{
	if (!_active)
		return;
	_accumulatedTime += time;
	if (_accumulatedTime > 0.8)
	{
		_accumulatedTime = 0;
		auto originBullet = (Bullet*)_object;
		auto bmc = originBullet->getComponent<BulletMoveComponent>();

		auto speedOriginal = bmc->getSpeedOriginal();
		auto radianOriginal = bmc->getRadianOriginal();

		auto b1 = Bullet::create(originBullet->getFather());
		b1->setSpeed(speedOriginal, radianOriginal + PI / 8);
		auto b2 = Bullet::create(originBullet->getFather());
		b2->setSpeed(speedOriginal, radianOriginal);
		auto b3 = Bullet::create(originBullet->getFather());
		b3->setSpeed(speedOriginal, radianOriginal - PI / 8);

		originBullet->getParent()->addChild(b1);
		originBullet->getParent()->addChild(b2);
		originBullet->getParent()->addChild(b3);
		b1->setPosition(originBullet->getPosition());
		b2->setPosition(originBullet->getPosition());
		b3->setPosition(originBullet->getPosition());
		originBullet->removeFromParent();
	}

	return;
}
