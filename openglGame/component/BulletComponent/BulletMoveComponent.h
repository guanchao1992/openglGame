#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class BulletMoveComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE; }
	virtual void doBegin();
	virtual void doEnd(); 
	bool update(float time);

	void setSpeed(const Vector2&speed);
	inline const Vector2& getSpeed()
	{
		return _speed;
	}
private:
	int _timerId;
	float _totalTime = 3.f;
	float _leftTime = 3.f;
	Vector2 _speed = { 0.f,0.f };				//ËÙ¶È
};
