#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "base/Rect.h"
#include <vector>


class RouteComponent :public Component
{
public:
	virtual const char* getName() { return "RouteComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_AREA; }
	virtual void doBegin();
	virtual void doEnd(); 

	virtual void resetRoutes();
	//返回第t秒时的点
	virtual Vector2 getRoutes(float t);

protected:
	vector<Vector2> _routes;
};
