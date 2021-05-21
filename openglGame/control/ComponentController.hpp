#pragma once
#include "base/ControllerBase.hpp"
#include "component/Component.hpp"
#include <vector>
#include <memory>
#include <map>

using namespace std;
class Component;
class Object;

class ComponentController : public ControllerBaseT<ComponentController>
{
public:
	~ComponentController();
	void init();
	void update(float time);

public:
	template <class T>
	T* createComponent()
	{
		auto com = make_shared<T>();
		_components_map[com.get()] = com;
		return com.get();
	}
	Component* recordComponent(shared_ptr<Component> com)
	{
		_components_map[com.get()] = com;
		return com.get();
	}

	void delComponent(Component*com) {
		_del_components_map[com] = _components_map[com];
		//_components_map[com] = nullptr;
		_components_map.erase(com);
	}
private:
	map<Component*, shared_ptr<Component>> _components_map;	//记录所有的组件
	map<Component*, shared_ptr<Component>> _del_components_map; //将要销毁的com
	int _timerId;
};

