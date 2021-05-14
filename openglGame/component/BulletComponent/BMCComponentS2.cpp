#include "BMCComponentS2.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"

void BMCComponentS2::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentS2::doEnd()
{
	__super::doEnd();
}

void BMCComponentS2::update(float time)
{
	if (!_active)
		return;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;

	auto a = sinf(_totalTime * 10);
	if (a > 0.8f)
	{
		Vector2 dir = { 0.f, 1.f + sinf(bmc->getRadianIncrement()) };
		bmc->setDirIncrement(atan2f(dir._y, dir._x));
	}
	else if (a < -0.8)
	{
		Vector2 dir = { 0.f, -1.f + sinf(bmc->getRadianIncrement()) };
		bmc->setDirIncrement(atan2f(dir._y, dir._x));
	}
	else
	{
		Vector2 dir = { 1.f + cosf(bmc->getRadianIncrement()), sinf(bmc->getRadianIncrement()) };
		bmc->setDirIncrement(atan2f(dir._y, dir._x));
	}
	return;
}
