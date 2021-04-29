#include "BulletMoveComponent.h"
#include <GameApp.h>


void BulletMoveComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&BulletMoveComponent::update, this, std::placeholders::_1));
}

void BulletMoveComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

bool BulletMoveComponent::update(float time)
{
	if (!_active)
		return false;
	Node*node = (Node*)_object;

	node->setPosition(node->getPosition()._x + _speed._x * time, node->getPosition()._y + _speed._y * time);

	_leftTime -= time;
	if (_leftTime < 0)
	{
		node->removeFromParent();
	}

	return false;
}

void BulletMoveComponent::setSpeed(const Vector2&speed)
{
	_speed = speed;
}
