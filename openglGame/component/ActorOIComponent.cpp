#include "ActorOIComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"
#include "ActorStateComponent.h"


void ActorOIComponent::doBegin()
{
	__super::doBegin();

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorOIComponent::update, this, std::placeholders::_1));

	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([this](const KeyEvent& et) {
		Actor* actor = (Actor*)_object;
		auto stateCom = _object->getComponent <ActorStateComponent>();
		if (!stateCom)
			return;
		switch (et._key)
		{
		case GLFW_KEY_UP: case 'w': case 'W':
			stateCom->onUp(et._isDown);
			break;
		case GLFW_KEY_DOWN: case 's': case 'S':
			stateCom->onDown(et._isDown);
			break;
		case GLFW_KEY_LEFT: case 'a': case 'A':
			stateCom->onLeft(et._isDown);
			break;
		case GLFW_KEY_RIGHT: case 'd': case 'D':
			stateCom->onRight(et._isDown);
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
		if (et.button & 1)
		{
			auto stateCom = _object->getComponent <ActorStateComponent>();
			if (!stateCom)
				return;
			stateCom->onFire(et._isDown);
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
