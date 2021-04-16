#include "TouchComponent.h"
#include "2d/Node.h"
#include <GameApp.h>

void TouchComponent::doBegin() 
{
	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([&](const MouseKeyEvent& et) {
		if ((et.button & 1) && et._isDown)
		{
			Node* node = (Node*)_object;
			node->setPosition(et._x, et._y);
		}
	});
}

void TouchComponent::doEnd()
{
	_listener->unlistenAll();
}
