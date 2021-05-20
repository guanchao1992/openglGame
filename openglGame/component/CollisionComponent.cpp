#include "CollisionComponent.h"
#include <GameApp.h>
#include "control/CollisionController.h"
#include <Game2DFight/Actor.h>
#include <Game2DFight/Bullet.h>


void CollisionComponent::doBegin()
{
	__super::doBegin();
}

void CollisionComponent::doEnd()
{
	__super::doEnd();
	CollisionController::getInstance()->erase(this);
}

bool CollisionComponent::update(float time)
{
	if (!_active)
		return false;

	return false;
}


void CollisionComponent::enableCollision(COLLISIONMARK flagMark, int doMark)
{
	_flagMark = flagMark;
	_doMark = doMark;

	CollisionController::getInstance()->insert(this);
}

static int ctd = 0;
CollisionTreeData::CollisionTreeData(CollisionComponent *collCom)
{
	_collCom = collCom;
	ctd++;
}

CollisionTreeData:: ~CollisionTreeData()
{
	ctd--;
}

int CollisionTreeData::X() const
{
	if (_collCom->getObject())
	{
	}
	Node* node = (Node*)_collCom->getObject();
	return node->getPosition()._x;
}

int CollisionTreeData::Y() const
{
	Node* node = (Node*)_collCom->getObject();
	return node->getPosition()._y;

}
