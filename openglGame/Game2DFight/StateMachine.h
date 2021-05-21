#pragma once
#include <memory>
#include <functional>
#include <map>
#include <set>

enum StateType : unsigned int
{
	STATE_NONE	= 0,	//��
	STATE_ACTIVE,		//����
	STATE_NOTACTIVE,	//�Ǽ���
	STATE_IDLE,			//����
	STATE_HIT,			//�ܻ�
	STATE_READY,		//˼��
	STATE_FIRE,			//����
	STATE_DEATH,		//����

	STATE_STAND,		//δ�ƶ�
	STATE_MOVE,			//�ƶ�

	STATE_CUSTOM=1000,	//�Զ���
};

struct State
{
	StateType _type;
	std::set<StateType> _froms;
	StateType	_to;				//����ʱ�������,�Զ�������һ��״̬
	float		_time;				//����ʱ��
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
	void enterState(StateType stype);		//�����from
	bool checkEnterState(StateType stype);	//���from���������򷵻�false
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

