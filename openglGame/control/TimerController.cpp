#include "TimerController.h"


Timer::Timer(float interval, int num, TimerCallback callback)
	:_interval(interval), _num(num), _function(callback)
{
}

void Timer::update(float time)
{
	if (_pause || _stop)
	{
		return;
	}
	_totalTime += time;
	_accumulatedTime += time;
	if (_accumulatedTime > _interval)
	{
		if (_function)
		{
			if (_function(_totalTime - _lastTime))
			{
				_stop = true;
			}
		}
		_lastTime = _totalTime;
		_accumulatedTime = _accumulatedTime - _interval;
		if (_num > 0 && ++_accumulatedNum >= _num)
		{
			_stop = true;
		}
	}
}

void Timer::resetTime()
{
	_accumulatedTime = 0;
}

void TimerController::init()
{ }

void TimerController::reset()
{
	_timers->clear();

}

void TimerController::update(float time)
{
	for (auto it = _timers->begin(); it != _timers->end(); )
	{
		it->second->update(time);
		if (it->second->_stop)
		{
			it = _timers->erase(it);
		}
		else
		{
			it++;
		}
	}
}

int TimerController::addTimer(float interval, int num, TimerCallback callback)
{
	auto t = make_shared<Timer>(interval, num, callback);
	auto index = _nextIndex++;
	_timers->insert(map<int, SPTimer>::value_type(index, t));
	return index;
}

void TimerController::killTimer(int id)
{
	auto it = _timers->find(id);
	if (it!= _timers->end())
	{
		_timers->erase(it);
	}
}

void TimerController::resetTime(int timeid)
{
	auto tr = _timers->find(timeid);
	if (tr != _timers->end())
	{
		tr->second->resetTime();
	}
}
