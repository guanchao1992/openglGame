#include "BulletMoveCComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"


void BulletMoveCComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&BulletMoveCComponent::update, this, std::placeholders::_1));

	auto bmc = _object->getComponent<BulletMoveComponent>();
	_defaultSpeed = bmc->getSpeed();
}

void BulletMoveCComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

bool BulletMoveCComponent::update(float time)
{
	if (!_active)
		return false;
	_totalTime += time;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	int tt = ((int)(_totalTime * 12)) % 4;
	switch (tt)
	{
	case 0:
		bmc->setSpeed(Vector2(_defaultSpeed._x, _defaultSpeed._y));
		break;
	case 1:
		bmc->setSpeed(Vector2(_defaultSpeed._y, _defaultSpeed._x));
		break;
	case 2:
		bmc->setSpeed(Vector2(_defaultSpeed._x, _defaultSpeed._y));
		break;
	case 3:
		bmc->setSpeed(Vector2(_defaultSpeed._y, -_defaultSpeed._x));
		break;
	default:
		break;
	}
	return false;
}
