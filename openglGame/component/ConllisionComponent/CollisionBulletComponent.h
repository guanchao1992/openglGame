#pragma once
#include "CollisionComponent.h"

//»ù´¡×Óµ¯Åö×²
class CollisionBulletComponent :public CollisionComponent
{
public:
	virtual const char* getName() { return "CollisionBulletComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_COLLISION; }
	virtual void doBegin();
	virtual void doEnd(); 
	virtual void collision(Object*other);
private:
};

