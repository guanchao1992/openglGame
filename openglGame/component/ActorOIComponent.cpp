#include "ActorOIComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"


void ActorOIComponent::doBegin()
{
	__super::doBegin();

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorOIComponent::update, this, std::placeholders::_1));

	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([this](const KeyEvent& et) {
		Actor* actor = (Actor*)_object;
		switch (et._key)
		{
		case GLFW_KEY_UP: case 'w': case 'W':
			actor->onUp(et._isDown);
			break;
		case GLFW_KEY_DOWN: case 's': case 'S':
			actor->onDown(et._isDown);
			break;
		case GLFW_KEY_LEFT: case 'a': case 'A':
			actor->onLeft(et._isDown);
			break;
		case GLFW_KEY_RIGHT: case 'd': case 'D':
			actor->onRight(et._isDown);
			break;
		case GLFW_KEY_SPACE:
			if (et._isDown)
			{
				//actor->fire();
			}
			break;
		default:
			break;
		}
	});
	_listener->listen([this](const MouseKeyEvent&et) {
		if (et._isDown)
		{
			Actor* actor = (Actor*)_object;
			auto pos = GameApp::getInstance()->convertViewToNode(actor->getParent(), Vector2(et._x, et._y));
			auto offset = Vector2(0, 40);
			pos.setVector(pos._x - actor->getPosition()._x - offset._x, pos._y - actor->getPosition()._y - offset._y);
			actor->fire(pos, offset);
		}
	});
}

void ActorOIComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

void ActorOIComponent::update(float time)
{

	return ;
}
