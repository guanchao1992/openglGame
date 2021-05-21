
#include "StateMachine.h"

StateMachine::~StateMachine()
{
}

SPStateMachine StateMachine::create()
{
	auto ret = std::make_shared<StateMachine>();
	ret->init();
	return ret;
}

void StateMachine::init()
{
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
		_toState = it->second._to;
		_accumulationTime = 0;
		_nextTime = it->second._time;
	}
}

bool StateMachine::checkEnterState(StateType stype)
{
	if (_state == stype)
	{
		return false;
	}
	auto it = _mapStats.find(stype);
	if (_state != STATE_NONE && it->second._froms.size() > 0 && it->second._froms.find(_state) == it->second._froms.end())
	{
		return false;
	}
	enterState(stype);
	return true;
}

void StateMachine::update(float time)
{
	if (_toState == STATE_NONE || _toState == _state)
		return;
	_accumulationTime += time;
	if (_accumulationTime >= _nextTime)
	{
		enterState(_toState);
	}

	return;
}
