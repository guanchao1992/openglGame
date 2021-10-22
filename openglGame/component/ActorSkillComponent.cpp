#include "ActorSkillComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"
#include "ActorStateComponent.h"
#include "ActorTipsComponent.h"
#include <control/TableController.h>
#include "tables/SkillTable.h"
#include "Game2DFight/Bullet.h"
#include "BulletStateComponent.h"


void ActorSkillComponent::doBegin()
{
	__super::doBegin();

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorSkillComponent::update, this, std::placeholders::_1));

}

void ActorSkillComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

void ActorSkillComponent::update(float time)
{
	for (auto it = _playingSkills.begin(); it != _playingSkills.end();)
	{
		it->_deltaTime += time;
		if (it->_playingState == 0)
		{
			if (it->_deltaTime > it->_delay)
			{
				it->_loop--;
				it->_playingState = 1;
				doingEffect(*it);
			}
		}
		else
		{
			if (it->_deltaTime > it->_delay + it->_time)
			{
				it->_playingState = 0;
				it->_deltaTime -= it->_delay + it->_time;
				if (it->_loop == 0)
				{
					it = _playingSkills.erase(it);
					continue;
				}
			}
		}
		it++;
	}

	//转cd
	for (auto it = _cdSkills.begin(); it != _cdSkills.end();)
	{
		it->second += time;
		if (it->second >= _skills[it->first]._skillBase->_cd)
		{
			it = _cdSkills.erase(it);
			continue;
		}
		it++;
	}
	return;
}

void ActorSkillComponent::doingEffect(const SkillEffectDoing&ef)
{
	auto actor = dynamic_cast<Actor*>(_object);
	auto stateCom = _object->getComponent<ActorStateComponent>();
	switch (ef._type)
	{
	case 1:
	{
		auto b = Bullet::create(actor);
		b->setSpeed(400.f, ef._dir * PI / 180.f);
		auto bsCom = b->getComponent<BulletStateComponent>();
		bsCom->setAttack(stateCom->getAttack());
		bsCom->setCamp(stateCom->getCamp());
		GameApp::getInstance()->_start->addChild(b);
		b->setPosition(actor->getPosition());

		break;
	}
	case 2:
	{

		break;
	}
	default:
		break;
	}
}

void ActorSkillComponent::checkDoEffect(int id, float dir)
{
	auto stData = SkillTableDatas::getData(id);
	const nlohmann::json &effect = stData->_effect1;
	if (stData == nullptr)
	{
		return;
	}

	checkDoEffect(stData->_effect1, dir);
	checkDoEffect(stData->_effect2, dir);
	checkDoEffect(stData->_effect3, dir);
}

void ActorSkillComponent::checkDoEffect(const nlohmann::json &effect, float dir)
{
	SkillEffectDoing sed;

	if (effect.find("type") != effect.end())
		sed._type = effect["type"].get<int>();
	if (sed._type == 0)
		return;

	sed._dir = dir;

	if (effect.find("dir") != effect.end())
		sed._dir = effect["dir"].get<float>() + dir;
	if (effect.find("speed") != effect.end())
		sed._speed = effect["speed"].get<float>();
	if (effect.find("delay") != effect.end())
		sed._delay = effect["delay"].get<float>();
	if (effect.find("time") != effect.end())
		sed._time = effect["time"].get<float>();
	if (effect.find("loop") != effect.end())
		sed._loop = effect["loop"].get<int>();

	_playingSkills.push_back(sed);
}

void ActorSkillComponent::fire(int id, float dir)
{
	static wchar_t str[256];
	auto it = _skills.find(id);
	if (it == _skills.end())
	{
		auto spData = SkillTableDatas::getData(id);
		if (spData == nullptr)
		{
			swprintf_s(str, 256, L"未知的技能id：%d", id);
		}
		else
		{
			swprintf_s(str, 256, L"您没有技能：%s", spData->_name);
		}
		_object->getComponent<ActorTipsComponent>()->addTips(str);
		return;
	}
	if (_cdSkills.find(id) != _cdSkills.end())
	{
		auto spData = SkillTableDatas::getData(id);
		//swprintf_s(str, L"技能冷却中：%s", spData->_name);
		//_object->getComponent<ActorTipsComponent>()->addTips(str);
		return;
	}
	_cdSkills[id] = 0.f;
	//检测并执行技能效果
	checkDoEffect(id, dir);
}

void ActorSkillComponent::addSkill(int id)
{
	SkillData sd;
	sd._skillBase = SkillTableDatas::getData(id).get();
	_skills.insert(std::map<int, SkillData>::value_type(id, sd));
}

void ActorSkillComponent::delSkill(int id)
{
	_skills.erase(id);
}
