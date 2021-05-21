#include "BMCComponentS1.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"

void BMCComponentS1::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentS1::doEnd()
{
	__super::doEnd();
}

void BMCComponentS1::update(float time)
{
	if (!_active)
		return;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;

	Vector2 dir = { 0.5f + cosf(bmc->getRadianIncrement()),  sinf(_totalTime * 10) + sinf(bmc->getRadianIncrement()) };

	bmc->setDirIncrement(atan2f(dir._y, dir._x));
	return;
}
