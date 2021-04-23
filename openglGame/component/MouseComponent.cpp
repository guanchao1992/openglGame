#include "MouseComponent.h"
#include "2d/Node.h"
#include <GameApp.h>
#include "GameEvent.h"
#include "control/MouseController.h"
#include "AreaComponent.h"


bool MouseComponent::onMouseKeyEvent(const MouseKeyEvent&et)
{
	if (_active && _funcMouseKey)
	{
		Node*node = (Node*)(_object);
		if (!node)
			return false;
		auto pos = GameApp::getInstance()->convertViewToNode(node, Vector2(et._x, et._y));
		if (node->getComponent<AreaComponent>()->isPosInArea(pos))
		{
			if (et._isDown)
			{
				_isThisDown = true;
			}
			else
			{
				if (_isThisDown)
				{
					_isThisDown = false;
					if (_funcMouseClick)
					{
						_funcMouseClick();
					}
				}
			}
			_funcMouseKey(*this, et);
			if (!_clickThrough)
			{
				return true;
			}
		}
	}
	return false;
}

bool MouseComponent::onMouseMoveEvent(const MouseMoveEvent&et)
{
	if (_active && _doMove)
	{
		Node*node = (Node*)(_object);
		if (!node)
			return false;
		auto pos = GameApp::getInstance()->convertViewToNode(node, Vector2(et._x, et._y));
		if (node->getComponent<AreaComponent>()->isPosInArea(pos))
		{
			doMouseIn(et);
			if (_funcMouseMove)
			{
				_funcMouseMove(*this, et);
			}
			if (!_clickThrough)
			{
				return true;
			}
		}
		else
		{
			doMouseOut(et);
		}
	}
	return false;
}

void MouseComponent::setMouseKeyFunc(std::function<void(MouseComponent&, const MouseKeyEvent&)> func)
{
	_funcMouseKey = func;
}

void MouseComponent::setMouseClickFunc(std::function<void()> func)
{
	_funcMouseClick = func;
}

void MouseComponent::setMouseMoveFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func)
{
	_funcMouseMove = func;
	_doMove = true;
}

void MouseComponent::setMouseMoveInFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func)
{
	_funcMouseMoveIn = func;
	_doMove = true;
}

void MouseComponent::setMouseMoveOutFunc(std::function<void(MouseComponent&, const MouseMoveEvent&)> func)
{
	_funcMouseMoveOut = func;
	_doMove = true;
}

void MouseComponent::doMouseIn(const MouseMoveEvent&et)
{
	if (!_isInArea)
	{
		_isInArea = true;
		if (_funcMouseMoveIn)
		{
			_funcMouseMoveIn(*this, et);
		}
	}
}

void MouseComponent::doMouseOut(const MouseMoveEvent&et)
{
	if (_isInArea)
	{
		_isInArea = false;
		if (_funcMouseMoveOut)
		{
			_funcMouseMoveOut(*this, et);
		}
	}
}

void MouseComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)(_object);
	if (node)
	{
		node->setMouseKeyComponent(this);
		MouseController::getInstance()->addMouseComponent(this);
	}
}

void MouseComponent::doEnd()
{
	__super::doEnd();
	Node* node = (Node*)(_object);
	if (node)
	{
		MouseController::getInstance()->removeMouseComponent(this);
		node->setMouseKeyComponent(nullptr);
	}
}

