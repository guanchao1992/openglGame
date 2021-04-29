#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class BulletMoveSComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE_S; }
	virtual void doBegin();
	virtual void doEnd(); 
	bool update(float time);

private:
	int _timerId;
	float _totalTime = 0.f;
	float _addRadian = 0.f;
	bool _isup = false;
	float _accumulatedRadian = 0.f;

	float _defaultSpeed;
	float _defaultRadian;
};
