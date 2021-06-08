#pragma once
#include <2d/Node.h>
#include "StateMachine.h"
#include "2d/Text.h"
#include "2d/DrawProgress.h"


StatementNode(Actor)
class Actor : public Node
{
public:
	StatementCreate(Actor);
	void init();
public:
	void fire(const Vector3&aim);

private:
};

