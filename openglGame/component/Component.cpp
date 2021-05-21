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

Component* Component::getComponent(ComponentType type)
{
	if (_object == nullptr)
		return nullptr;
	return _object->getComponent(type);
}
