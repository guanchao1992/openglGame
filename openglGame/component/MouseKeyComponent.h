#pragma once
#include "Component.hpp"
#include "dexode/EventBus.hpp"
#include <functional>

struct MouseKeyEvent;
class MouseKeyComponent;

typedef void FUNC_MOUSE_KEY(MouseKeyComponent&, const MouseKeyEvent&);

class MouseKeyComponent :public Component
{
public:
	bool onMouseKeyEvent(const MouseKeyEvent&et);
	void setMouseKeyFunc(std::function<void(MouseKeyComponent&, const MouseKeyEvent&)> func);
	inline void setThrough(bool through) {
		_clickThrough = through;
	}
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_MOUSE_KEY; }
	virtual void doBegin();
	virtual void doEnd(); 
private:
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
	std::function <FUNC_MOUSE_KEY> _funcMouseKey;

	bool _clickThrough = false;		//´©Í¸
};
