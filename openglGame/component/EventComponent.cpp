#include "EventComponent.h"
#include "2d/Node.h"
#include "GameApp.h"


EventComponent::~EventComponent()
{
}

void EventComponent::doBegin()
{
	__super::doBegin();
	_listener = GameApp::getInstance()->createListenerSP();
	_map_callback = make_shared<std::map<EventType, std::function<void(Object*, const Event&)>>>();

	_listener->listen([this](const Event& event) { onEventHandler(event); });
}

void EventComponent::doEnd()
{
	__super::doEnd();
	Node* node = (Node*)(_object);
	if (node)
	{ }
	_listener->unlistenAll();
}

void EventComponent::addEvent(EventType et, std::function<void(Object*, const Event&)> func)
{
	if (_map_callback->find(et) != _map_callback->end())
	{
		_map_callback->erase(et);
	}

	_map_callback->insert(std::map<EventType, std::function<void(Object*, const Event&)>>::value_type(et, func));
	switch (et)
	{
	case EVENT_KEY:
		_listener->listen([this](const KeyEvent& event) { onEventHandler(event); });
		break;
	case EVENT_MOUSEKEY:
		_listener->listen([this](const MouseKeyEvent& event) { onEventHandler(event); });
		break;
	case EVENT_MOUSEMOUSE:
		_listener->listen([this](const MouseMoveEvent& event) { onEventHandler(event); });
		break;
	case EVENT_MOUSEWHEEL:
		_listener->listen([this](const MouseWheelEvent& event) { onEventHandler(event); });
		break;
	case EVENT_CUSTOM:
	case EVENT_NULL:
	case EVENT_GAME_RESTART:
	default:
		break;
	}
}

void EventComponent::onEventHandler(const Event&event)
{
	auto it = _map_callback->find((EventType)event._eventId);
	if (it != _map_callback->end())
	{
		it->second(_object, event);
	}
}

