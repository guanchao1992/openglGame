#pragma once
#include "CollisionComponent.h"

//基础实体碰撞
class CollisionActorComponent :public CollisionComponent
{
public:
	virtual const char* getName() { return "CollisionActorComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_COLLISION; }
	virtual void doBegin();
	virtual void doEnd();
	virtual void collision(Object*other);

	inline void setWeight(float weight) {
		_weight = weight;
	}
private:
	float _weight = 1.0f; //碰撞参数
};

