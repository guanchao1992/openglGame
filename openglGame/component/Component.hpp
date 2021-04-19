#pragma once
#include <assert.h>
#include <string>
#include "2d/Object.hpp"

using namespace std;

class Component;
class Object;


class Component
{
public:
	Component()
	{
		_name = typeid(*this).name();
	}
	//标记组件名称，可以直接返回类名
	//static string getName() { return "Component"; }
	inline const string& getName() { return _name; }

	virtual ComponentType getType() { return ComponentType::COMPONENT_CUSTOM; }

	/*
	template <typename T>
	static string getComponentName() { return T::getComponentName(); }
	*/

	virtual void doBegin() {}
	virtual void doEnd() {}
	virtual void update() {}
public:
	//void addComponent(shared_ptr<Component> com);
	//void removeComponent(shared_ptr<Component> com);
	//shared_ptr<Component> getComponent(const string&name);
	shared_ptr<Component> getComponent(ComponentType type);

	inline void setObject(Object*obj) { _object = obj; }
	inline Object*getObject() { return _object; }
public:
	/*
	template <class T>
	static shared_ptr<T> createComponent(shared_ptr<Object> obj) {
		auto com = make_shared<T>();
		com->setObject(obj.get());
		return com;
	}
	*/
	template <class T>
	static shared_ptr<T> createComponent() {
		auto com = make_shared<T>();
		return com;
	}

	template <class T>
	bool isComponent() {
		T* t = dynamic_cast<T*>(this);
		return t != NULL;
	}
	inline void setActive(bool active) { _active = active; }
	inline bool isActive() { return _active; }
protected:
	Object* _object = nullptr;
	string _name;
	bool _active = true;
};

