#pragma once
#include <memory>
#include <vector>

using namespace std;

class ControllerBase
{
public:
	virtual void reset() {};//重置控制器数据
	virtual void init() {};
	virtual void update(float time) {};
};

template <typename T>
class ControllerBaseT :public ControllerBase
{
public:
	static shared_ptr<T> getInstance()
	{
		auto cbank = ControllerMaster::getInstance();
		static unsigned int controller_index = -1;
		shared_ptr<ControllerBase> cb = cbank->getControllerByIndex(controller_index);
		if (cb == nullptr)
		{
			cb = make_shared<T>();
			cb->init();
			unsigned int index = cbank->pushBackController(cb);
			controller_index = index;
		}
		
		return dynamic_pointer_cast<T>(cb);
	}
};

class ControllerMaster
{
public:
	static shared_ptr<ControllerMaster> getInstance();

	int getControllerSize() { return _controllers->size(); }

	shared_ptr<ControllerBase> getControllerByIndex(unsigned int index);

	unsigned int pushBackController(shared_ptr<ControllerBase> cb);

	void update(float time);

private:
	shared_ptr<vector<shared_ptr<ControllerBase>>> _controllers = make_shared<vector<shared_ptr<ControllerBase>>>();
	static shared_ptr<ControllerMaster> _instance;
};
