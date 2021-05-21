#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"


class ActorAIComponent :public Component
{
public:
	virtual const char* getName() { return "ActorAIComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_AI; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);
private:
	int _timerId;
	Object* _target;

};
