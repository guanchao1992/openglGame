#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class BulletMoveKComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE_S; }
	virtual void doBegin();
	virtual void doEnd(); 
	bool update(float time);

private:
	int		_timerId;
	float	_accumulatedTime = 0.f;	//¿€º∆ ±º‰

	Vector2 _defaultSpeed;
	float _defaultRadian;
};
