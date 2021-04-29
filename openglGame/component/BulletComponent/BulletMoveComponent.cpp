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

	node->setPosition(node->getPosition()._x + _speed * cosf(_radian) * time, node->getPosition()._y + _speed * sinf(_radian) * time);

	_leftTime -= time;
	if (_leftTime < 0)
	{
		node->removeFromParent();
	}

	return false;
}

void BulletMoveComponent::setSpeed(const Vector2&speed)
{
	_radian = atan2f(speed._y, speed._x);
	_speed = sqrtf((speed._x * speed._x) + (speed._y * speed._y));
}

void BulletMoveComponent::setDir(const Vector2&dir)
{
	_radian = atan2f(dir._y, dir._x);
}

void BulletMoveComponent::setDir(float radian)
{
	_radian = radian;
}

void BulletMoveComponent::setSpeed(float speed)
{
	_speed = speed;
}
