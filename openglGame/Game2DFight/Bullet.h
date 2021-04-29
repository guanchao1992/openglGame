#pragma once
#include <2d/Node.h>
#include "2d/Text.h"
#include "Actor.h"


StatementNode(Bullet)
class Bullet : public Node
{
public:
	static SPBullet create(Actor* father, const Vector2&speed);
	void init(const Vector2&speed);
public:

	inline Actor* getFather() { return _father; }
private:
	Actor*		_father;
	SPText		_name;
};

