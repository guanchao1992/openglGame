#include "ControllerBase.hpp"


shared_ptr<ControllerMaster> ControllerMaster::_instance = nullptr;
shared_ptr<ControllerMaster> ControllerMaster::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = make_shared<ControllerMaster>();
	}
	return _instance;
}

shared_ptr<ControllerBase> ControllerMaster::getControllerByIndex(unsigned int index)
{
	if (index >= _controllers->size())
	{
		return nullptr;
	}
	return _controllers->at(index);
}

unsigned int ControllerMaster::pushBackController(shared_ptr<ControllerBase> cb)
{
	_controllers->push_back(cb);
	return _controllers->size() - 1;
}

void ControllerMaster::update(float time)
{
	for (auto it : *_controllers)
	{
		it->update(time);
	}
	
}
