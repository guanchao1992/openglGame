#pragma once
#include <map>
#include <string>
#include <memory>
#include "component/ComponentUtils.h"
#include "component/Component.hpp"

using namespace std;
class Component;
class RanderComponent;

class Object
{
public:
	template <class T>
	shared_ptr<T> addComponent() {
		auto com = make_shared<T>();
		addComponent(com);
		return com;
	}

	shared_ptr<Component> addComponent(shared_ptr<Component> com);
	void removeComponent(shared_ptr<Component> com);
	//shared_ptr<Component> getComponent(const string&name);
	shared_ptr<Component> getComponent(ComponentType type);

	template <class T>
	shared_ptr<T> getComponent() {
		auto name = typeid(T).name();
		printf("getComponent:%s\n", name);
		auto it = _components_map->find(name);
		if (it == _components_map->end())
		{
			return nullptr;
		}
		return dynamic_pointer_cast<T>(it->second);
	}

private:
	shared_ptr<map<string, shared_ptr<Component>>> _components_map = make_shared<map<string, shared_ptr<Component>>>();
};
