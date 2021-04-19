#include "MouseKeyComponent.h"
#include "2d/Node.h"
#include <GameApp.h>
#include "GameEvent.h"
#include "control/MouseKeysController.h"


bool MouseKeyComponent::onMouseKeyEvent(const MouseKeyEvent&et)
{
	if (_active && _funcMouseKey)
	{
		_funcMouseKey(*this, et);
		if (!_clickThrough)
		{
			return true;
		}
	}
	return false;
}

void MouseKeyComponent::setMouseKeyFunc(std::function<void(MouseKeyComponent&, const MouseKeyEvent&)> func)
{
	_funcMouseKey = func;
}

void MouseKeyComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)(_object);
	if (node)
	{
		node->setMouseKeyComponent(this);
		MouseKeysController::getInstance()->addMouseKeyComponent(node->getComponent<MouseKeyComponent>());
	}
	/*
	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([&](const MouseKeyEvent& et) {
		if ((et.button & 1) && et._isDown)
		{
			Node* node = (Node*)_object;
			node->setPosition(et._x, et._y);
		}
	});
	*/
}

void MouseKeyComponent::doEnd()
{
	__super::doEnd();
	Node* node = (Node*)(_object);
	if (node)
	{
		node->setMouseKeyComponent(nullptr);
	}
	_listener->unlistenAll();
}
