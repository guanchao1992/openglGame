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
	Component();
	~Component();
	//标记组件名称
	virtual const char* getName() { return "Component"; }

	virtual ComponentType getType() { return ComponentType::COMPONENT_CUSTOM; }

	/*
	template <typename T>
	static string getComponentName() { return T::getComponentName(); }
	*/

	virtual void doBegin() {}
	virtual void doEnd() {}
public:



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
	/*

	template <class T>
	shared_ptr<T> addComponent() {
		if (!_object)
			return nullptr;
		return _object->addComponent<T>();
	}
	template <class T>
	shared_ptr<T> getComponent() {
		if (!_object)
			return nullptr;
		return _object->getComponent<T>();
	}

	*/

	shared_ptr<Component> getComponent(ComponentType type);

	template <class T>
	bool isComponent() {
		T* t = dynamic_cast<T*>(this);
		return t != NULL;
	}
	inline void setActive(bool active) { _active = active; }
	inline bool isActive() { return _active; }
protected:
	Object* _object = nullptr;
	bool _active = true;
};

