#include "../2d/Object.hpp"
#include "Component.hpp"
#include "FontRanderComponent.h"
#include <set>


Component::Component()
{
}

Component::~Component()
{
}

/*
void Component::addComponent(shared_ptr<Component> com)
{
	if (_object == nullptr)
		return;
	_object->addComponent(com);
}
void Component::removeComponent(shared_ptr<Component> com)
{
	if (_object == nullptr)
		return;
	_object->removeComponent(com);
}

shared_ptr<Component> Component::getComponent(const string&name)
{
	if (_object == nullptr)
		return nullptr;
	return _object->getComponent(name);
}
*/

shared_ptr<Component> Component::getComponent(ComponentType type)
{
	if (_object == nullptr)
		return nullptr;
	return _object->getComponent(type);
}
