#pragma once

#include "base/ControllerBase.hpp"
#include<map>
#include <functional>


#define TimerCallback std::function<void(float time)>


struct Timer
{
	friend class TimerController;
public:
	Timer(float interval, int num, TimerCallback callback);

	void resetTime();
	void stop();
private:
	void update(float time);
	float			_interval = 1.0f;		//间隔
	int				_num = 0;				//次数 (小于0表示不限次数)
	float			_accumulatedTime = 0.f;	//累计时间
	float			_accumulatedNum = 0.f;	//累计次数
	float			_totalTime = 0.f;				//总时间
	float			_lastTime = 0.f;				//上一次的时间
	bool			_stop = false;
	bool			_pause = false;
	TimerCallback	_function = nullptr;
};

class TimerCompilations
{
};

typedef shared_ptr<Timer> SPTimer;

class TimerController :public ControllerBaseT<TimerController>
{
public:
	virtual void init();
	virtual void reset();
	virtual void update(float time);

	//callback返回true将强制中断定时器。
	//建议使用Node中的addTimer
	int addTimer(float interval, int num, TimerCallback callback);
	void killTimer(int id);

	void resetTime(int timeid);
private:
	shared_ptr<map<int, SPTimer>> _timers = make_shared<map<int, shared_ptr<Timer>>>();
	int _nextIndex = 1;
};
