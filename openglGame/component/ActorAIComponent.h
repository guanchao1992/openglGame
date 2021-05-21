#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"
#include "ActorStateComponent.h"

class ActorStateComponent;

class ActorAIComponent :public Component
{
public:
	virtual const char* getName() { return "ActorAIComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_AI; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);
private:
	int _timerId;
	ActorCamp _targetCamp = ACTORCAMP_NULL;
	shared_ptr<ActorStateComponent> _target = nullptr;

	float _nextTime = 0.5f;	//下次思考的时间
};
