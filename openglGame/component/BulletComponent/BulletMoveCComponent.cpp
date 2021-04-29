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
	_defaultRadian = bmc->getRadian();
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
		bmc->setDir(_defaultRadian);
		break;
	case 1:
		bmc->setDir(_defaultRadian + PI / 2);
		break;
	case 2:
		bmc->setDir(_defaultRadian);
		break;
	case 3:
		bmc->setDir(_defaultRadian - PI / 2);
		break;
	default:
		break;
	}
	return false;
}
