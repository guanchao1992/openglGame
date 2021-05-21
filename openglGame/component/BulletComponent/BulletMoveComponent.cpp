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

void BulletMoveComponent::update(float time)
{
	if (!_active)
		return;
	_speedIncrement = 0.f;
	_radianIncrement = 0.f;
	for (auto it = _bmcComponents.begin(); it != _bmcComponents.end(); it++)
	{
		(*it)->update(time);
	}

	auto speed = _speedOriginal + _speedIncrement;
	auto radian = _radianOriginal + _radianIncrement;

	Node*node = (Node*)_object;
	node->setPosition(node->getPosition()._x + speed * cosf(radian) * time, node->getPosition()._y + speed * sinf(radian) * time);

	_leftTime -= time;
	if (_leftTime < 0)
	{
		node->removeFromParent();
	}

	return;
}

bool BulletMoveComponent::collision()
{

	return false;
}

void BulletMoveComponent::setSpeedOriginal(const Vector2&speed)
{
	_radianOriginal = atan2f(speed._y, speed._x);
	_speedOriginal = sqrtf((speed._x * speed._x) + (speed._y * speed._y));
}

void BulletMoveComponent::setDirOriginal(const Vector2&dir)
{
	_radianOriginal = atan2f(dir._y, dir._x);
}

void BulletMoveComponent::setDirOriginal(float radian)
{
	_radianOriginal = radian;
}

void BulletMoveComponent::setSpeedOriginal(float speed)
{
	_speedOriginal = speed;
}

void BulletMoveComponent::setSpeedIncrement(const Vector2&speed)
{
	_radianIncrement = atan2f(speed._y, speed._x);
	_speedIncrement = sqrtf((speed._x * speed._x) + (speed._y * speed._y));
}

void BulletMoveComponent::setDirIncrement(const Vector2&dir)
{
	_radianIncrement = atan2f(dir._y, dir._x);
}

void BulletMoveComponent::setDirIncrement(float radian)
{
	_radianIncrement = radian;
}

void BulletMoveComponent::setSpeedIncrement(float speed)
{
	_speedIncrement = speed;
}

void BulletMoveComponent::insert(BMCComponent*bmcc)
{
	_bmcComponents.push_back(bmcc);
}

void BulletMoveComponent::erase(BMCComponent*bmcc)
{
	for (auto it = _bmcComponents.begin(); it != _bmcComponents.end(); it++)
	{
		if (*it == bmcc)
		{
			_bmcComponents.erase(it);
			break;
		}
	}
}

