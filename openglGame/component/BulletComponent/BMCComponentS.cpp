#include "BMCComponentS.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"

void BMCComponentS::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentS::doEnd()
{
	__super::doEnd();
}

void BMCComponentS::update(float time)
{
	if (!_active)
		return;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;

	Vector2 dir = { (cosf(_totalTime * 10) + 0.7f) * (1 + cosf(bmc->getRadianIncrement())), sinf(_totalTime * 10) + sinf(bmc->getRadianIncrement()) };
	bmc->setDirIncrement(atan2f(dir._y, dir._x));
	return;
}
