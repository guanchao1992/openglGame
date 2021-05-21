#include "ActorAIComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"


void ActorAIComponent::doBegin()
{
	__super::doBegin();

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorAIComponent::update, this, std::placeholders::_1));




}

void ActorAIComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

void ActorAIComponent::update(float time)
{
	//׷�򵥵�AI��׷�����ǿ���


	return;
}
