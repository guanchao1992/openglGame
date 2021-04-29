#pragma once
#include <2d/Node.h>
#include "2d/Text.h"
#include "Actor.h"


StatementNode(Bullet)
class Bullet : public Node
{
public:
	static SPBullet create(Actor* father);
	void init();
public:
	void setSpeed(float speed,float radian);
	void setSpeed(float speed);
	void setDir(const Vector2&dir);
	void setSpeed(const Vector2&speed);

	inline Actor* getFather() { return _father; }
private:
	Actor*		_father;
	SPText		_name;
};

