#pragma once
#include <map>
#include <string>
#include <memory>
#include "component/ComponentUtils.h"
#include "component/Component.hpp"
#include "control/ComponentController.hpp"

using namespace std;
class Component;
class RanderComponent;
class ComponentController;

class Object
{
public:
	~Object();
public:
	template <class T>
	T* addComponent() {
		auto comController = ComponentController::getInstance();
		auto com = comController->recordComponent(make_shared<T>());
		return  dynamic_cast<T*>(addComponent(com));
	}

	virtual void removeComponent(Component* com);
	Component* getComponent(ComponentType type);

	template <class T>
	T* getComponent() {
		auto name = typeid(T).name();
		//printf("getComponent:%s\n", name);
		auto it = _components_map.find(name);
		if (it == _components_map.end())
		{
			return nullptr;
		}
		return (T*)(it->second);
	}

	virtual void removeAllComponent();
private:
	virtual Component* addComponent(Component* com);
private:
	map<string, Component*> _components_map;
};
