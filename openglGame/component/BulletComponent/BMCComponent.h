#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class BMCComponent :public Component
{
public:
	virtual const char* getName() { return "BMCComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE_CHANGE; }
	virtual void doBegin();
	virtual void doEnd(); 
	virtual void update(float time);

private:
};
