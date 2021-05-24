#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"
#include "Game2DFight/StateMachine.h"
#include "ActorStateComponent.h"

class BulletStateComponent :public Component
{
public:
	virtual const char* getName() { return "BulletStateComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_STATE; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);

	inline void setCamp(ActorCamp camp) { _camp = camp; }
	inline ActorCamp getCamp() { return _camp; }

	int getAttack() { return _attack; }
	void setAttack(int attack) { _attack = attack; }
private:
	int _timerId;

	ActorCamp _camp = ACTORCAMP_NULL;	//ÕóÓª

	int _attack = 5;
};
