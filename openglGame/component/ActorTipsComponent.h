#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "2d/Text.h"


class ActorTipsComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_OI; }
	virtual void doBegin();
	virtual void doEnd();
	bool update(float time);
	void addTips(const wchar_t*text);

private:
	std::list<SPText>	_listTexts;
	int _timerId;
};
