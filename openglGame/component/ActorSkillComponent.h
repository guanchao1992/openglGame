#pragma once
#include "Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "dexode/eventbus/Bus.hpp"
#include <nlohmann/json_fwd.hpp>
#include <set>

class SkillTableBase;

struct SkillData
{
	SkillTableBase* _skillBase = nullptr;
};

struct SkillEffectDoing
{
	int _type = 0;			//效果类型
	float _dir = 0.f;		//朝向
	int _speed = 100;		//速度
	float _delay = 0.f;		//延时
	float _time = 0.f;		//持续时间
	int _loop = 1;			//次数

	float _deltaTime = 0.f;	//累计时间
	float _deltaNum = 0;	//累计执行次数
	float _playingState = 0;//0->delay->1->time->0
};

class ActorSkillComponent :public Component
{
public:
	virtual const char* getName() { return "ActorSkillComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_ACTOR_SKILL; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);
	void fire(int id, float dir);

	void addSkill(int id);
	void delSkill(int id);
private:
	void doingEffect(const SkillEffectDoing&ef);
	void checkDoEffect(int id, float dir);
	void checkDoEffect(const nlohmann::json &effect, float dir);
private:
	int _timerId;
	std::map<int, SkillData>		_skills;			//记录拥有的技能
	std::map<int, float>			_cdSkills;			//正在cd的技能
	std::list<SkillEffectDoing>		_playingSkills;		//效果正在执行的效果
};
