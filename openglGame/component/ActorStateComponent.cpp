#include "ActorStateComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include <functional>
#include "control/TimerController.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/ActorMoveComponent.h"
#include "component/ActorTipsComponent.h"
#include <GameApp.h>
#include "component/BulletComponent/BMCComponentS.h"
#include "component/BulletComponent/BMCComponentK.h"
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletComponent/BMCComponentS1.h"
#include "component/BulletComponent/BMCComponentS2.h"
#include "component/ConllisionComponent/CollisionComponent.h"
#include "component/ConllisionComponent/CollisionBulletComponent.h"
#include "component/ConllisionComponent/CollisionActorComponent.h"
#include "DrawRanderComponent.h"
#include "Game2DFight/Bullet.h"

void ActorStateComponent::doBegin()
{
	__super::doBegin();
	auto node = dynamic_cast<Node*>(_object);

	auto name = Text::create(L"名字好多个字哦", DEFAULTE_FONT_FILE, 24);
	node->addChild(name);
	_ui_name = name.get();
	_ui_name->addComponent<OutlineBoxComponent>();
	auto nameAreaCom = _ui_name->getComponent<AreaComponent>();
	nameAreaCom->setAnchor(Vector2(0.5, 0.5));
	_ui_name->setPosition(0, 90);

	auto state = Text::create(L"状态", DEFAULTE_FONT_FILE, 18);
	node->addChild(state);
	_ui_state = state.get();
	auto stateAreaCom = _ui_state->getComponent<AreaComponent>();
	stateAreaCom->setAnchor(Vector2(0.5, 0.5));
	_ui_state->setPosition(0, 50);

	auto hp = DrawProgress::create(Vector4(1, 0, 0, 1), Vector4(1, 1, 1, 0.3), Size(100, 20));
	node->addChild(hp);
	_ui_hp = hp.get();
	auto hpAreaCom = _ui_hp->getComponent<AreaComponent>();
	hpAreaCom->setAnchor(Vector2(0.5, 0.5));
	_ui_hp->setPosition(0, 70);

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorStateComponent::update, this, std::placeholders::_1));

	_sm = StateMachine::create();
	_sm_move = StateMachine::create();

	_sm->addState({ STATE_ACTIVE,{},STATE_ACTIVE,0,std::bind(&ActorStateComponent::__activeEnter,this),std::bind(&ActorStateComponent::__activeExit,this) });
	_sm->addState({ STATE_NOTACTIVE,{},STATE_NOTACTIVE,0,std::bind(&ActorStateComponent::__notactiveEnter,this),std::bind(&ActorStateComponent::__notactiveExit,this) });
	_sm->addState({ STATE_IDLE,{},STATE_IDLE,0,std::bind(&ActorStateComponent::__idleEnter,this),std::bind(&ActorStateComponent::__idleExit,this) });
	_sm->addState({ STATE_HIT,{STATE_IDLE,STATE_READY,STATE_FIRE,STATE_ACTIVE},STATE_IDLE,0.15,std::bind(&ActorStateComponent::__hitEnter,this),std::bind(&ActorStateComponent::__hitExit,this) });
	_sm->addState({ STATE_READY,{},STATE_READY,0.1,std::bind(&ActorStateComponent::__readyEnter,this),std::bind(&ActorStateComponent::__readyExit,this) });
	_sm->addState({ STATE_FIRE,{STATE_IDLE},STATE_IDLE,0.1,std::bind(&ActorStateComponent::__fireEnter,this),std::bind(&ActorStateComponent::__fireExit,this) });
	_sm->addState({ STATE_DEATH,{},STATE_DEATH,1,std::bind(&ActorStateComponent::__deathEnter,this),std::bind(&ActorStateComponent::__deathExit,this) });

	_sm->checkEnterState(STATE_IDLE);

	_sm_move->addState({ STATE_STAND,{},STATE_NONE,0,std::bind(&ActorStateComponent::__standEnter,this),std::bind(&ActorStateComponent::__standExit,this) });
	_sm_move->addState({ STATE_MOVE, {},STATE_STAND, 0.3,std::bind(&ActorStateComponent::__moveEnter,this),std::bind(&ActorStateComponent::__moveExit,this) });

	_sm_move->checkEnterState(STATE_STAND);
}

void ActorStateComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);
}

void ActorStateComponent::update(float time)
{
	_sm->update(time);
	_sm_move->update(time);

	if (_fireKey)
	{
		double x = 0, y = 0;
		auto window = glfwGetCurrentContext();
		if (window)
		{
			glfwGetCursorPos(window, &x, &y);
			y = GameApp::getInstance()->getViewHeight() - y;
		}

		Actor* actor = (Actor*)_object;
		auto pos = GameApp::getInstance()->convertViewToNode(actor->getParent(), Vector2(x, y));
		auto offset = Vector2(0, 40);
		pos.setVector(pos._x - actor->getPosition()._x - offset._x, pos._y - actor->getPosition()._y - offset._y);
		actor->fire(pos, offset);
	}
	return;
}

bool ActorStateComponent::enterState(StateType stype)
{
	if (_sm->checkEnterState(stype))
	{
		return true;
	}
	return false;
}

bool ActorStateComponent::enterMoveState()
{
	if (_sm->isState(STATE_DEATH) || _sm->isState(STATE_NOTACTIVE))
		return false;
	return _sm_move->checkEnterState(STATE_MOVE);
}

bool ActorStateComponent::isMoveing()
{
	return _sm_move->isState(STATE_MOVE);
}

void ActorStateComponent::calculateMove()
{
	auto amCom = _object->getComponent<ActorMoveComponent>();
	Vector2 as(0, 0);
	if (_upKey)
	{
		as._y += 10000;
	}
	if (_downKey)
	{
		as._y -= 10000;
	}
	if (_rightKey)
	{
		as._x += 10000;
	}
	if (_leftKey)
	{
		as._x -= 10000;
	}
	amCom->setAcceleratedSpeed(as);
}

void ActorStateComponent::setName(const wchar_t*name)
{
	_ui_name->setString(name);
}

void ActorStateComponent::setState(const wchar_t*state)
{
	_ui_state->setString(state);
}

void ActorStateComponent::setHP(int hp)
{
	_hp = hp;
	_ui_hp->setProportion(1.0f * _hp / _hpMax);

	if (_hp <= 0)
	{
		_sm->checkEnterState(STATE_DEATH);
	}
}


/**************状态机发生变化***************/
void ActorStateComponent::__activeEnter()
{
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：激活", _sm->getState());
	atCom->addTips(str);
}
void ActorStateComponent::__activeExit()
{

}
void ActorStateComponent::__notactiveEnter()
{
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"未激活", _sm->getState());
	//atCom->addTips(str);
	setState(str);
}
void ActorStateComponent::__notactiveExit()
{

}
void ActorStateComponent::__idleEnter()
{
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"空闲", _sm->getState());
//	atCom->addTips(str);
	setState(str);
}
void ActorStateComponent::__idleExit()
{

}

void ActorStateComponent::__hitEnter()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"受击", _sm->getState());
//	atCom->addTips(str);

	actor->setColor(Vector4(0.8, 0.1, 0, 1));

	setState(str);

}
void ActorStateComponent::__hitExit()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;

	actor->setColor(Vector4(0, 0, 0, 0));
}

void ActorStateComponent::__readyEnter()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"思考", _sm->getState());
//	atCom->addTips(str);
	setState(str);
}
void ActorStateComponent::__readyExit()
{
}
void ActorStateComponent::__fireEnter()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"开火", _sm->getState());
//	atCom->addTips(str);
	setState(str);
}
void ActorStateComponent::__fireExit()
{
}
void ActorStateComponent::__deathEnter()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;
	auto atCom = _object->getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"死亡", _sm->getState());
	//atCom->addTips(str);

	setState(str);
}

void ActorStateComponent::__deathExit()
{
	auto actor = dynamic_cast<Actor*>(_object);
	if (!actor)
		return;
	actor->removeFromParent();
	_object = nullptr;

}

void ActorStateComponent::__standEnter()
{
}
void ActorStateComponent::__standExit()
{
}
void ActorStateComponent::__moveEnter()
{
}
void ActorStateComponent::__moveExit()
{
}
