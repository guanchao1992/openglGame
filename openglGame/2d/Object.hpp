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
	~Object();
public:
	template <class T>
	shared_ptr<T> addComponent() {
		return dynamic_pointer_cast<T>(addComponent(make_shared<T>()));
	}

	virtual void removeComponent(shared_ptr<Component> com);
	shared_ptr<Component> getComponent(ComponentType type);

	template <class T>
	T* getComponent() {
		auto name = typeid(T).name();
		//printf("getComponent:%s\n", name);
		auto it = _components_map.find(name);
		if (it == _components_map.end())
		{
			return nullptr;
		}
		return (T*)(it->second.get());
	}

	virtual void removeAllComponent();
private:
	virtual shared_ptr<Component> addComponent(shared_ptr<Component> com);
private:
	map<string, shared_ptr<Component>> _components_map;
};
