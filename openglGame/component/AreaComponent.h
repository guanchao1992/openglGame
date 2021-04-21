#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class AreaComponent :public Component
{
public:
	void setSize(const Size&size);
	const Size& getSize();
	bool isPosInArea(const Vector2& pos);
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_AREA; }
	virtual void doBegin();
	virtual void doEnd(); 
private:
	Size _contentSize = Size(10.f, 10.f);
};
