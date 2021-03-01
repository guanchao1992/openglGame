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
	_accumulatedTime += time;
	if (_accumulatedTime > _interval - _offsetTime)
	{
		if (_function)
		{
			if (_function(_accumulatedTime))
			{
				_stop = true;
			}
		}
		_offsetTime = _accumulatedTime - _interval;
		_accumulatedTime = 0;
		if (_num > 0 && ++_accumulatedNum >= _num)
		{
			_stop = true;
		}
	}
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
