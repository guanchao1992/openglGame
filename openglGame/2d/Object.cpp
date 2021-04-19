#include "Object.hpp"
#include "../component/Component.hpp"
#include <memory>
#include "component/RanderComponent.h"

shared_ptr<Component> Object::addComponent(shared_ptr<Component> com)
{
	auto name = typeid(*com.get()).name();
	printf("addComponent:%s\n", name);
	if (_components_map->find(name) != _components_map->end())
	{
		printf("不允许重复添加组件:%s！\n", name);
		return nullptr;
	}
	_components_map->insert(map<string, shared_ptr<Component>>::value_type(name, com));
	/*
	if (com->getType() == COMPONENT_RANDER)
	{
		_randerComponent = dynamic_pointer_cast<RanderComponent>(com);
	}
	*/
	com->setObject(this);
	com->doBegin();
	return com;
}
void Object::removeComponent(shared_ptr<Component> com)
{
	/*
	if (_randerComponent == com)
	{
		_randerComponent = nullptr;
	}
	*/
	com->doEnd();
	com->setObject(nullptr);

	_components_map->erase(typeid(com).name());
}

/*
shared_ptr<Component> Object::getComponent(const string&name) {
	auto it = _components_map->find(name);
	if (it == _components_map->end())
	{
		return nullptr;
	}
	return _components_map->at(name);
}
*/

shared_ptr<Component> Object::getComponent(ComponentType type)
{
	for (auto it = _components_map->begin(); it != _components_map->end(); it++)
	{
		if (it->second->getType() == type)
		{
			return it->second;
		}
	}
	return nullptr;
}
