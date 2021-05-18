#include "Actor.h"
#include "component/OutlineBoxComponent.h"
#include "component/AreaComponent.h"
#include <component/FontRanderComponent.h>
#include "component/ActorMoveComponent.h"
#include "component/ActorTipsComponent.h"
#include "Bullet.h"
#include <GameApp.h>
#include "component/BulletComponent/BMCComponentS.h"
#include "component/BulletComponent/BMCComponentK.h"
#include "component/BulletComponent/BulletMoveComponent.h"
#include "component/BulletComponent/BMCComponentS1.h"
#include "component/BulletComponent/BMCComponentS2.h"
#include "component/CollisionComponent.h"


void Actor::init()
{
	auto atCom = addComponent<ActorTipsComponent>();

	_sm = StateMachine::create();
	_sm_move = StateMachine::create();

	_sm->addState({ STATE_ACTIVE,{},STATE_ACTIVE,0,std::bind(&Actor::__activeEnter,this),std::bind(&Actor::__activeExit,this) });
	_sm->addState({ STATE_NOTACTIVE,{},STATE_NOTACTIVE,0,std::bind(&Actor::__notactiveEnter,this),std::bind(&Actor::__notactiveExit,this) });
	_sm->addState({ STATE_IDLE,{},STATE_IDLE,0,std::bind(&Actor::__idleEnter,this),std::bind(&Actor::__idleExit,this) });
	_sm->addState({ STATE_HIT,{STATE_IDLE,STATE_READY,STATE_FIRE,STATE_ACTIVE},STATE_IDLE,0.15,std::bind(&Actor::__hitEnter,this),std::bind(&Actor::__hitExit,this) });
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


	auto drawCom = addComponent<DrawRanderComponent>();
	drawCom->addVertex(Vector2(0.f, 0));
	drawCom->addVertex(Vector2(40.f, 0));
	drawCom->addVertex(Vector2(40.f, 40));
	drawCom->addVertex(Vector2(0.f, 40));
	drawCom->signDraw(GL_TRIANGLE_FAN);


	addComponent<OutlineBoxComponent>();
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(0.5, 0));
	areaCom->setSize(Size(40, 60));

	auto amCom = addComponent<ActorMoveComponent>();

}

bool Actor::enterState(StateType stype)
{
	if (_sm->checkEnterState(stype))
	{
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

void Actor::setName(const wchar_t*name)
{
	_name->setString(name);
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

void Actor::fire(const Vector2&aim, const Vector2&offset)
{
	if (enterState(STATE_FIRE))
	{
		float vec[] = { aim._x,aim._y };
		glusVector2Normalizef(vec);
		//发射
		for (int i = 0; i < 1; i++)
		{
			auto b = Bullet::create(this);
			b->setDir(aim);
			b->setSpeed(400.f);
			GameApp::getInstance()->_start->addChild(b);
			b->setPosition(getPosition()._x + offset._x, getPosition()._y + offset._y);
			/*
			b->addComponent<BMCComponentS>();
			b->addComponent<BMCComponentS1>();
			b->addComponent<BMCComponentS2>();
			*/

			auto bulletCollCom = b->addComponent<CollisionComponent>();
			auto collCom = getComponent<CollisionComponent>();
			if (collCom)
			{
				switch (collCom->getFlagMark())
				{
				case  CMARK_SELF:
				case  CMARK_SELF_BULLET:
					bulletCollCom->enableCollision(CMARK_SELF_BULLET, CMARK_ENEMY | CMARK_STONE);
					break;
				case  CMARK_ENEMY:
				case  CMARK_ENEMY_BULLET:
					bulletCollCom->enableCollision(CMARK_ENEMY_BULLET, CMARK_SELF | CMARK_STONE);
					break;
				case  CMARK_FRIENDLY:
				case  CMARK_FRIENDLY_BULLET:
					bulletCollCom->enableCollision(CMARK_FRIENDLY_BULLET, CMARK_ENEMY | CMARK_STONE);
					break;
				case  CMARK_STONE:
				case  CMARK_NEUTRAL:
				case  CMARK_NEUTRAL_BULLET:
					//他们(石头和中立单位)应该不会开枪
				default:
					break;
				}

			}
		}
	}
}

/**************状态机发生变化***************/
void Actor::__activeEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：激活", _sm->getState());
	atCom->addTips(str);
}
void Actor::__activeExit()
{

}
void Actor::__notactiveEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：未激活", _sm->getState());
	atCom->addTips(str);
}
void Actor::__notactiveExit()
{

}
void Actor::__idleEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：空闲", _sm->getState());
	atCom->addTips(str);
}
void Actor::__idleExit()
{

}

void Actor::__hitEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：受击", _sm->getState());
	atCom->addTips(str);
	setColor(Vector4(1, 1, 0, 1));
}
void Actor::__hitExit()
{
	setColor(Vector4(1, 0, 0, 1));
}

void Actor::__readyEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：思考", _sm->getState());
	atCom->addTips(str);
}
void Actor::__readyExit()
{
}
void Actor::__fireEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：开火", _sm->getState());
	atCom->addTips(str);
}
void Actor::__fireExit()
{
}
void Actor::__deathEnter()
{
	auto atCom = getComponent<ActorTipsComponent>();
	wchar_t str[256];
	swprintf_s(str, 256, L"状态：死亡", _sm->getState());
	atCom->addTips(str);
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
