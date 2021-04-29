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
	_defaultRadian = bmc->getRadian();
	_addRadian = -PI / 3;
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
	auto bmc = _object->getComponent<BulletMoveComponent>();
	_totalTime += time;


	Vector2 dir = { cosf(_totalTime * 10) + 0.7f, sinf(_totalTime * 10) };
	bmc->setDir(atan2f(dir._y, dir._x) + _defaultRadian);

	return false;
}
