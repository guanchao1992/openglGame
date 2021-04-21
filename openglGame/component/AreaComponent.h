#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class AreaComponent :public Component
{
public:
	void setSize(const Size&size);
	void setAnchor(const Vector2&anchor);
	bool isPosInArea(const Vector2& pos);

public:
	inline const Size& getSize() { return _contentSize; }
	inline const Vector2& getAnchor() { return _anchor; }
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_AREA; }
	virtual void doBegin();
	virtual void doEnd(); 
private:
	Vector2 _anchor = Vector2(0.0, 0.0);	//0~1
	Size _contentSize = Size(40.f, 40.f);
};
