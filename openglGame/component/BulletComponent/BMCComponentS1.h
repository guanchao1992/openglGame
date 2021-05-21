#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "BMCComponent.h"


class BMCComponentS1:public BMCComponent
{
public:
	virtual const char* getName() { return "BMCComponentS1"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE_CHANGE; }
	virtual void doBegin();
	virtual void doEnd(); 
	virtual void update(float time);
private:
	float _totalTime = 0.f;
};
