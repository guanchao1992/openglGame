#pragma once
#include <memory>
#include <functional>
#include <map>
#include <set>

enum StateType : unsigned int
{
	STATE_NONE	= 0,	//无
	STATE_ACTIVE,		//激活
	STATE_NOTACTIVE,	//非激活
	STATE_IDLE,			//闲置
	STATE_HIT,			//受击
	STATE_READY,		//思索
	STATE_FIRE,			//攻击
	STATE_DEATH,		//死亡

	STATE_STAND,		//未移动
	STATE_MOVE,			//移动

	STATE_CUSTOM=1000,	//自定义
};

struct State
{
	StateType _type;
	std::set<StateType> _froms;
	StateType	_to;				//持续时间结束后,自动进入下一个状态
	float		_time;				//持续时间
	std::function<void()> _enterFunc;
	std::function<void()> _exitFunc;
};

class StateMachine;
typedef std::shared_ptr<StateMachine> SPStateMachine;

class StateMachine
{
public:
	static SPStateMachine create();
	~StateMachine();
	void init();
	void addState(const State& s);
	void enterState(StateType stype);		//不检查from
	bool checkEnterState(StateType stype);	//检查from，不满足则返回false
	void update(float time);
public:
	inline StateType getState() {
		return _state;
	}
	inline bool isState(StateType stype) {
		return _state == stype;
	}
private:
	std::map<StateType, State> _mapStats;
	StateType _state = STATE_NONE;
	StateType _toState = STATE_NONE;
	float _nextTime = 0;
	float _accumulationTime = 0;
	int _timerId;
};

