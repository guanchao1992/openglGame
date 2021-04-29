#include "Actor.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/ActorMoveComponent.h"
#include "component/ActorTipsComponent.h"
#include "Bullet.h"
#include <GameApp.h>
#include "component/BulletComponent/BulletMoveSComponent.h"
#include "component/BulletComponent/BulletMoveCComponent.h"
#include "component/BulletComponent/BulletMoveKComponent.h"


void Actor::init()
{
	_sm = StateMachine::create();
	_sm_move = StateMachine::create();

	_sm->addState({ STATE_ACTIVE,{},STATE_ACTIVE,0,std::bind(&Actor::__activeEnter,this),std::bind(&Actor::__activeExit,this) });
	_sm->addState({ STATE_NOTACTIVE,{},STATE_NOTACTIVE,0,std::bind(&Actor::__notactiveEnter,this),std::bind(&Actor::__notactiveExit,this) });
	_sm->addState({ STATE_IDLE,{},STATE_IDLE,0,std::bind(&Actor::__idleEnter,this),std::bind(&Actor::__idleExit,this) });
	_sm->addState({ STATE_READY,{},STATE_READY,0.1,std::bind(&Actor::__readyEnter,this),std::bind(&Actor::__readyExit,this) });
	_sm->addState({ STATE_FIRE,{STATE_IDLE},STATE_IDLE,0.1,std::bind(&Actor::__fireEnter,this),std::bind(&Actor::__fireExit,this) });
	_sm->addState({ STATE_DEATH,{},STATE_DEATH,0,std::bind(&Actor::__deathEnter,this),std::bind(&Actor::__deathExit,this) });

	_sm->enterState(STATE_IDLE);

	_sm_move->addState({ STATE_STAND,{},STATE_NONE,0,std::bind(&Actor::__standEnter,this),std::bind(&Actor::__standExit,this) });
	_sm_move->addState({ STATE_MOVE, {},STATE_STAND, 0.3,std::bind(&Actor::__moveEnter,this),std::bind(&Actor::__moveExit,this) });

	_sm_move->enterState(STATE_STAND);

	_name = Text::create(L"名字好多个字哦", DEFAULTE_FONT_FILE, 24);
	_name->addComponent<OutlineBoxComponent>();
	auto nameAreaCom = _name->getComponent<AreaComponent>();
	nameAreaCom->setAnchor(Vector2(0.5, 0.5));
	addChild(_name);
	_name->setPosition(0, 70);

	addComponent<OutlineBoxComponent>();
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(0.5, 0));
	areaCom->setSize(Size(40, 60));

	auto amCom = addComponent<ActorMoveComponent>();

	auto atCom = addComponent<ActorTipsComponent>();
}

bool Actor::enterState(StateType stype)
{
	if (_sm->checkEnterState(stype))
	{
		auto atCom = getComponent<ActorTipsComponent>();
		wchar_t str[256];
		swprintf_s(str, 256, L"状态：%d", _sm->getState());
		atCom->addTips(str);
		return true;
	}
	return false;
}

bool Actor::enterMoveState()
{
	if (_sm->isState(STATE_DEATH) || _sm->isState(STATE_NOTACTIVE))
		return false;
	return _sm_move->checkEnterState(STATE_MOVE);
}

bool Actor::isMoveing()
{
	return _sm_move->isState(STATE_MOVE);
}

void Actor::calculateMove()
{
	auto amCom = getComponent<ActorMoveComponent>();
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

void Actor::fire()
{
	if (enterState(STATE_FIRE))
	{
		auto b = Bullet::create(this, Vector2(450.f, 150.f));
		GameApp::getInstance()->_start->addChild(b);
		b->setPosition(getPosition() + Vector3(0.f, 20.f, 0.f));
		b->addComponent<BulletMoveCComponent>();
		b->addComponent<BulletMoveKComponent>();
	}
}

/**************状态机发生变化***************/
void Actor::__activeEnter()
{
}
void Actor::__activeExit()
{

}
void Actor::__notactiveEnter()
{

}
void Actor::__notactiveExit()
{

}
void Actor::__idleEnter()
{

}
void Actor::__idleExit()
{

}

void Actor::__readyEnter()
{
}
void Actor::__readyExit()
{
}
void Actor::__fireEnter()
{
}
void Actor::__fireExit()
{
}
void Actor::__deathEnter()
{
}
void Actor::__deathExit()
{
}


void Actor::__standEnter()
{
}
void Actor::__standExit()
{
}
void Actor::__moveEnter()
{
}
void Actor::__moveExit()
{
}
