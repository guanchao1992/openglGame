#include "Object.hpp"
#include "../component/Component.hpp"
#include <memory>
#include "component/RanderComponent.h"

Object::~Object()
{
	removeAllComponent();
}

shared_ptr<Component> Object::addComponent(shared_ptr<Component> com)
{
	auto name = typeid(*com.get()).name();
	//auto name = com->getName();
	auto it = _components_map.find(name);
	if (it != _components_map.end())
	{
		printf("不允许重复添加组件:%s！\n", name);
		return com;
	}
	_components_map.insert(map<string, shared_ptr<Component>>::value_type(name, com));

	com->setObject(this);
	com->setActive(true);
	com->doBegin();
	return com;
}
void Object::removeComponent(shared_ptr<Component> com)
{
	com->doEnd();
	com->setActive(false);
	com->setObject(nullptr);

	_components_map.erase(typeid(com).name());
}

void Object::removeAllComponent()
{
	for (auto it = _components_map.begin(); it != _components_map.end(); it++)
	{
		it->second->doEnd();
		it->second->setActive(false);
		it->second->setObject(nullptr);
	}
	_components_map.clear();
}

/*
shared_ptr<Component> Object::getComponent(const string&name) {
	auto it = _components_map.find(name);
	if (it == _components_map.end())
	{
		return nullptr;
	}
	return _components_map.at(name);
}
*/

shared_ptr<Component> Object::getComponent(ComponentType type)
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
