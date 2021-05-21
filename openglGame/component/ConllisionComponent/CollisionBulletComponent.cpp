#include "CollisionBulletComponent.h"
#include <GameApp.h>
#include "control/CollisionController.h"


void CollisionBulletComponent::doBegin()
{
	__super::doBegin();

}

void CollisionBulletComponent::doEnd()
{
	__super::doEnd();
}

void CollisionBulletComponent::collision(Object*other)
{
	auto node = dynamic_cast<Node*>(_object);
	if (node)
	{
		node->removeFromParent();
	}
}
