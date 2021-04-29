#pragma once
#include <2d/Node.h>
#include "StateMachine.h"
#include "2d/Text.h"


StatementNode(Actor)
class Actor : public Node
{
public:
	StatementCreate(Actor);
	void init();
	bool enterState(StateType stype);
	bool enterMoveState();
	bool isMoveing();
	void setName(const wchar_t*name);
public:
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
	void fire(const Vector2&aim, const Vector2&offset);
private:
	virtual void __activeEnter();
	virtual void __activeExit();
	virtual void __notactiveEnter();
	virtual void __notactiveExit();
	virtual void __idleEnter();
	virtual void __idleExit();
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
	SPText		_name;

	bool _upKey = false;
	bool _downKey = false;
	bool _leftKey = false;
	bool _rightKey = false;
	SPStateMachine _sm;
	SPStateMachine _sm_move;	//移动单独抠出来
};

