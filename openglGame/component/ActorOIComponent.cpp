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
	_listener->listen([&](const KeyEvent& et) {
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
				actor->fire();
			}
			break;
		default:
			break;
		}
	});
}

void ActorOIComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

bool ActorOIComponent::update(float time)
{

	return false;
}
