#include "ActorMoveComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"


void ActorMoveComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorMoveComponent::update, this, std::placeholders::_1));
}

void ActorMoveComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);

}

bool ActorMoveComponent::update(float time)
{
	if (!_active)
		return false;
	Actor*actor = (Actor*)_object;

	if (_acceleratedSpeed._x == 0)
	{
		if (_speed._x > 0)
		{
			_speed.setVectorX(_speed._x - _damp * time);
			if (_speed._x < 0)
			{
				_speed.setVectorX(0);
			}
		}
		else if (_speed._x < 0)
		{
			_speed.setVectorX(_speed._x + _damp * time);
			if (_speed._x > 0)
			{
				_speed.setVectorX(0);
			}
		}
	}
	if (_acceleratedSpeed._y == 0)
	{
		if (_speed._y > 0)
		{
			_speed.setVectorY(_speed._y - _damp * time);
			if (_speed._y < 0)
			{
				_speed.setVectorY(0);
			}
		}
		else if (_speed._y < 0)
		{
			_speed.setVectorY(_speed._y + _damp * time);
			if (_speed._y > 0)
			{
				_speed.setVectorY(0);
			}
		}
	}
	if (_acceleratedSpeed._x == 0 && _acceleratedSpeed._x == 0)
	{
		actor->enterMoveState();
	}

	_speed = _speed + _acceleratedSpeed * time;
	if (_speed._x > _maxSpeed)
	{
		_speed.setVectorX(_maxSpeed);
	}
	else if (_speed._x < -_maxSpeed)
	{
		_speed.setVectorX(-_maxSpeed);
	}
	if (_speed._y > _maxSpeed)
	{
		_speed.setVectorY(_maxSpeed);
	}
	else if (_speed._y < -_maxSpeed)
	{
		_speed.setVectorY(-_maxSpeed);
	}
	actor->setPosition(actor->getPosition()._x + _speed._x * time, actor->getPosition()._y + _speed._y * time);

	return false;
}

void ActorMoveComponent::setAcceleratedSpeed(const Vector2&acceleratedSpeed)
{
	_acceleratedSpeed = acceleratedSpeed;
}
