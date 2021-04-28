#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class ActorMoveComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_OI; }
	virtual void doBegin();
	virtual void doEnd(); 
	bool update(float time);

	void setAcceleratedSpeed(const Vector2&acceleratedSpeed);

	inline void setMaxSpeed(float speed) {
		_maxSpeed = speed;
	}
	inline void setDamp(float damp) {
		_damp = damp;
	}
private:

	int _timerId;
	Vector2 _acceleratedSpeed = { 0.f,0.f };	//加速度
	Vector2 _speed = { 0.f,0.f };				//速度
	float _maxSpeed = 200;						//像素每秒
	float _damp = 1000;							//阻尼系数
};
