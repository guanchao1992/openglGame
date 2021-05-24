#pragma once
#include <2d/Node.h>
#include "StateMachine.h"
#include "2d/Text.h"


StatementNode(Actor)
class Actor : public Node
{
public:
	StatementCreate(Actor);
	void init();
	void setName(const wchar_t*name);
public:
	void fire(const Vector2&aim, const Vector2&offset);
	void setState(const wchar_t*state);
private:
	SPText		_name = nullptr;
	SPText		_state = nullptr;
};

