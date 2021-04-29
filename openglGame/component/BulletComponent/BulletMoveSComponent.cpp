#include "BulletMoveSComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"


void BulletMoveSComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&BulletMoveSComponent::update, this, std::placeholders::_1));

	auto bmc = _object->getComponent<BulletMoveComponent>();
	_defaultSpeed = bmc->getSpeed();
}

void BulletMoveSComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

bool BulletMoveSComponent::update(float time)
{
	if (!_active)
		return false;
	_totalTime += time;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	auto d = (_defaultSpeed._x + _defaultSpeed._y) * 1.5;
	bmc->setSpeed(_defaultSpeed + Vector2(d * sin(_totalTime * 15), d * cos(_totalTime * 15)));

	return false;
}
