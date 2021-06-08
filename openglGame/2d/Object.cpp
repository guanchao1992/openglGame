#include "Object.hpp"
#include "../component/Component.hpp"
#include <memory>
#include "component/RanderComponent.h"

Object::~Object()
{
	removeAllComponent();
}

Component* Object::addComponent(Component* com)
{
	auto name = typeid(*com).name();
	//auto name = com->getName();
	auto it = _components_map.find(name);
	if (it != _components_map.end())
	{
		printf("不允许重复添加组件:%s！\n", name);
		auto comController = ComponentController::getInstance();
		comController->delComponent(com);
		return it->second;
	}
	_components_map.insert(map<string, Component*>::value_type(name, com));

	com->setObject(this);
	com->setActive(true);
	com->doBegin();
	return com;
}
void Object::removeComponent(Component* com)
{
	com->doEnd();
	com->setActive(false);
	com->setObject(nullptr);
	ComponentController::getInstance()->delComponent(com);

	_components_map.erase(typeid(com).name());
}

void Object::removeAllComponent()
{
	for (auto it = _components_map.begin(); it != _components_map.end(); it++)
	{
		it->second->doEnd();
		it->second->setActive(false);
		it->second->setObject(nullptr);
		ComponentController::getInstance()->delComponent(it->second);
	}
	_components_map.clear();
}

Component* Object::getComponent(ComponentType type)
{
	for (auto it = _components_map.begin(); it != _components_map.end(); it++)
	{
		if (it->second->getType() == type)
		{
			return it->second;
		}
	}
	return nullptr;
}
