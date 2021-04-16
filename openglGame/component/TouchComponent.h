#pragma once
#include "Component.hpp"
#include "dexode/EventBus.hpp"


class TouchComponent :public Component
{
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_TOUCH; }
	virtual void doBegin();
	virtual void doEnd(); 
private:
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};
