#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"


class ActorOIComponent :public Component
{
public:
	virtual const char* getName() { return "ActorOIComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_OI; }
	virtual void doBegin();
	virtual void doEnd(); 
	bool update(float time);
private:
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;

	int _timerId;

};
