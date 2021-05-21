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
	float			_interval = 1.0f;		//���
	int				_num = 0;				//���� (С��0��ʾ���޴���)
	float			_accumulatedTime = 0.f;	//�ۼ�ʱ��
	float			_accumulatedNum = 0.f;	//�ۼƴ���
	float			_totalTime = 0.f;				//��ʱ��
	float			_lastTime = 0.f;				//��һ�ε�ʱ��
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

	//callback����true��ǿ���ж϶�ʱ����
	//����ʹ��Node�е�addTimer
	int addTimer(float interval, int num, TimerCallback callback);
	void killTimer(int id);

	void resetTime(int timeid);
private:
	shared_ptr<map<int, SPTimer>> _timers = make_shared<map<int, shared_ptr<Timer>>>();
	int _nextIndex = 1;
};
