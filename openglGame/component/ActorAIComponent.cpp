#include "ActorAIComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"
#include "control/ComponentController.hpp"
#include "ActorMoveComponent.h"
#include "ActorStateComponent.h"
#include "Game2DFight/GameMainFight.h"


void ActorAIComponent::doBegin()
{
	__super::doBegin();

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorAIComponent::update, this, std::placeholders::_1));

	_targetCamp = ACTORCAMP_PLAYER;
}

void ActorAIComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

void ActorAIComponent::update(float time)
{
	//追简单的AI，追着主角开火

	_nextTime = _nextTime - time;
	if (_nextTime < 0)
	{
		if (!_target || !_target->isActive())
		{
			_target = nullptr;
			//搜索地图，找到符合条件的目标
			auto sg = dynamic_pointer_cast<GameMainFight>(GameApp::getInstance()->_start);
			const auto childs = sg->getChildObjects();
			for (auto it = childs.begin(); it != childs.end(); it++)
			{
				auto stateCom = (*it)->getComponent<ActorStateComponent>();
				if (stateCom &&stateCom->isActive() && stateCom->getCamp() == _targetCamp)
				{
					_target = dynamic_pointer_cast<ActorStateComponent>(ComponentController::getInstance()->recordExtraComponent(stateCom));
				}
			}
		}
	}
	
	//追赶
	if (_target != nullptr)
	{
		auto actor = dynamic_cast<Node*>(_object);
		auto target_node = dynamic_cast<Node*>(_target->getObject());
		auto amc = _object->getComponent<ActorMoveComponent>();
		if (amc)
		{
			if (actor && target_node)
			{
				auto p = target_node->getPosition() - actor->getPosition();
				auto r = atan2(p._y, p._x);

				amc->setAcceleratedSpeed(Vector2(cosf(r) * 500, sinf(r) * 500));
			}
			else
			{
				amc->setAcceleratedSpeed(Vector2(0, 0));
			}
		}
	}

	return;
}
