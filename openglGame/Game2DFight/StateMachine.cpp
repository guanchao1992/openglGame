
#include "StateMachine.h"
#include "control/TimerController.h"

StateMachine::~StateMachine()
{
	TimerController::getInstance()->killTimer(_timerId);
}

SPStateMachine StateMachine::create()
{
	auto ret = std::make_shared<StateMachine>();
	ret->init();
	return ret;
}

void StateMachine::init()
{
	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&StateMachine::update, this, std::placeholders::_1));
}

void StateMachine::addState(const State& s)
{
	_mapStats[s._type] = s;
}

void StateMachine::enterState(StateType stype)
{
	auto it = _mapStats.find(stype);
	if (it != _mapStats.end())
	{
		auto cur_it = _mapStats.find(_state);
		if (cur_it != _mapStats.end())
		{
			if (cur_it->second._exitFunc)
			{
				cur_it->second._exitFunc();
			}
		}
		if (it->second._enterFunc)
		{
			it->second._enterFunc();
		}
		_state = stype;
	}
}

bool StateMachine::checkEnterState(StateType stype)
{
	if (_state == stype)
	{
		_accumulationTime = 0;
		return true;
	}
	auto it = _mapStats.find(stype);
	if (_state != STATE_NONE && it->second._froms.size() > 0 && it->second._froms.find(_state) == it->second._froms.end())
	{
		return false;
	}
	enterState(stype);
	return true;
}

bool StateMachine::update(float time)
{
	if (_toState == STATE_NONE || _toState == _state)
		return false;
	_accumulationTime += time;
	if (_accumulationTime >= _nextTime)
	{
		enterState(_toState);
	}

	return false;
}
