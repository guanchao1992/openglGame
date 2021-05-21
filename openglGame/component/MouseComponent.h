#pragma once
#include "Component.hpp"
#include "dexode/EventBus.hpp"
#include <functional>

struct MouseKeyEvent;
struct MouseMoveEvent;
class MouseComponent;

class MouseComponent :public Component
{
	friend class MouseController;
public:
	virtual const char* getName() { return "MouseComponent"; }
	bool onMouseKeyEvent(const MouseKeyEvent&et);
	bool onMouseMoveEvent(const MouseMoveEvent&et);

	void setMouseKeyFunc(std::function<void(MouseComponent&, const MouseKeyEvent&)> func);
	void setMouseClickFunc(std::function<void()> func);
	void setMouseMoveFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func);
	void setMouseMoveInFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func);
	void setMouseMoveOutFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func);
	
	void doMouseIn(const MouseMoveEvent&et);
	void doMouseOut(const MouseMoveEvent&et);
public:
	inline void setThrough(bool through) {
		_clickThrough = through;
	}
	inline bool isThisDown() { return _isThisDown; }
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_MOUSE_KEY; }
	virtual void doBegin();
	virtual void doEnd(); 
private:
	//shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
	std::function <void(MouseComponent&, const MouseKeyEvent&)> _funcMouseKey = nullptr;
	std::function <void()> _funcMouseClick = nullptr;
	std::function <void(MouseComponent&, const MouseMoveEvent&)> _funcMouseMove = nullptr;
	std::function<void(MouseComponent&, const MouseMoveEvent&)> _funcMouseMoveIn = nullptr;
	std::function<void(MouseComponent&, const MouseMoveEvent&)> _funcMouseMoveOut = nullptr;

	bool _doMove = false;
	bool _isInArea = false;
	bool _clickThrough = false;		//´©Í¸

	bool _isThisDown = false;
};
