#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "BMCComponent.h"


class BMCComponentK :public BMCComponent
{
public:
	virtual const char* getName() { return "BMCComponentK"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE_CHANGE; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);

private:
	float	_accumulatedTime = 0.f;	//¿€º∆ ±º‰
};
