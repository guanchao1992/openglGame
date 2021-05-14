#include "BMCComponentS3.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"

void BMCComponentS3::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentS3::doEnd()
{
	__super::doEnd();
}

void BMCComponentS3::update(float time)
{
	if (!_active)
		return;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;

	Vector2 dir = { cosf(_totalTime * 10) + 0.7f, sinf(_totalTime * 10) };
	bmc->setDirIncrement(atan2f(dir._y, dir._x) + bmc->getRadianIncrement());
	return;
}
