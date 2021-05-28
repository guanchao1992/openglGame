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
	int _type = 0;			//Ч������
	float _dir = 0.f;		//����
	int _speed = 100;		//�ٶ�
	float _delay = 0.f;		//��ʱ
	float _time = 0.f;		//����ʱ��
	int _loop = 1;			//����

	float _deltaTime = 0.f;	//�ۼ�ʱ��
	float _deltaNum = 0;	//�ۼ�ִ�д���
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
	std::map<int, SkillData>		_skills;			//��¼ӵ�еļ���
	std::map<int, float>			_cdSkills;			//����cd�ļ���
	std::list<SkillEffectDoing>		_playingSkills;		//Ч������ִ�е�Ч��
};
