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
	void setDir(const Vector2&dir);
	void setDir(float radian);
	void setSpeed(float speed);

	inline float getSpeed() { return _speed; }
	inline float getRadian() { return _radian; }

private:
	int _timerId;
	float _totalTime = 3.f;
	float _leftTime = 3.f;
	float _radian = 0.f;	//»¡¶È
	float _speed = 0.f;		//ËÙ¶È
};
