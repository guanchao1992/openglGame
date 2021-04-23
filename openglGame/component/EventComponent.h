#pragma once
#include "component/Component.hpp"
#include "dexode/eventbus/Listener.hpp"
#include "dexode/eventbus/Bus.hpp"
#include "GameEvent.h"

class Object;

class EventComponent : public Component
{
public:
	~EventComponent();
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_RANDER; }

	virtual void doBegin();
	virtual void doEnd();

	void onEventHandler(const Event&);

public:
	void addEvent(EventType, std::function<void(Object*, const Event&)>);
protected:
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
	shared_ptr<std::map<EventType, std::function<void(Object*, const Event&)>>> _map_callback = nullptr;
};

