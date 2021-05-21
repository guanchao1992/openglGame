#include "BMCComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "BulletMoveComponent.h"


void BMCComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;
	auto bmc = _object->getComponent<BulletMoveComponent>();
	bmc->insert(this);
}

void BMCComponent::doEnd()
{
	__super::doEnd();
	auto bmc = _object->getComponent<BulletMoveComponent>();
	bmc->erase(this);
}

void BMCComponent::update(float time)
{
	return;
}
