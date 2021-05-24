#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"
#include "Game2DFight/StateMachine.h"

enum ActorCamp
{
	ACTORCAMP_NULL = 0,		//无阵营
	ACTORCAMP_PLAYER = 1,	//友
	ACTORCAMP_ENEMY = 2,	//敌
	ACTORCAMP_NEUTRAL = 4,	//中立

};

class ActorStateComponent :public Component
{
public:
	virtual const char* getName() { return "ActorStateComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_STATE; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);

	bool enterState(StateType stype);
	bool enterMoveState();
	bool isMoveing();

	inline void onUp(bool keyPress) {
		_upKey = keyPress;
		calculateMove();
	}
	inline void onDown(bool keyPress) {
		_downKey = keyPress;
		calculateMove();
	}
	inline void onLeft(bool keyPress) {
		_leftKey = keyPress;
		calculateMove();
	}
	inline void onRight(bool keyPress) {
		_rightKey = keyPress;
		calculateMove();
	}
	void calculateMove();

	inline void onFire(bool keyPress) {
		_fireKey = keyPress;
	}
	inline bool isFireDown() {
		return _fireKey;
	}

	inline void setCamp(ActorCamp camp) { _camp = camp; }
	inline ActorCamp getCamp() { return _camp; }

	inline StateMachine* getStateMachine() { return _sm.get(); }
	inline StateMachine* getMoveStateMachine() { return _sm_move.get(); }
	inline State* getStateData(StateType stype) {
		if (stype == STATE_MOVE)
		{
			return _sm_move->getStateData(STATE_MOVE);
		}
		else
		{
			return _sm->getStateData(stype);
		}
	};

	int getHP() { return _hp; }
	void setHP(int hp) { _hp = hp; }
	int getAttack() { return _attack; }
	void setAttack(int attack) { _attack = attack; }
private:
	virtual void __activeEnter();
	virtual void __activeExit();
	virtual void __notactiveEnter();
	virtual void __notactiveExit();
	virtual void __idleEnter();
	virtual void __idleExit();
	virtual void __hitEnter();
	virtual void __hitExit();
	virtual void __readyEnter();
	virtual void __readyExit();
	virtual void __fireEnter();
	virtual void __fireExit();
	virtual void __deathEnter();
	virtual void __deathExit();

	virtual void __standEnter();
	virtual void __standExit();
	virtual void __moveEnter();
	virtual void __moveExit();

private:

	bool _upKey = false;
	bool _downKey = false;
	bool _leftKey = false;
	bool _rightKey = false;
	bool _fireKey = false;
	SPStateMachine _sm;
	SPStateMachine _sm_move;	//移动单独抠出来

	int _timerId;

	ActorCamp _camp = ACTORCAMP_NULL;	//阵营

	int _hp = 100;
	int _attack = 5;
};
