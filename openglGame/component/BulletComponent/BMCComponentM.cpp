#include "BMCComponentM.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"

void BMCComponentM::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

}

void BMCComponentM::doEnd()
{
	__super::doEnd();
}

void BMCComponentM::update(float time)
{
	if (!_active)
		return;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;

	bmc->setSpeedIncrement(0.1 + bmc->getSpeedIncrement());
	return;
}
