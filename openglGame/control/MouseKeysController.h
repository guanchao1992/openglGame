#pragma once
#include "base/ControllerBase.hpp"
#include "component/MouseKeyComponent.h"
#include <vector>
#include <memory>

using namespace std;

class MouseKeysController : public ControllerBaseT<MouseKeysController>
{
public:
	void init();
	void addMouseKeyComponent(shared_ptr<MouseKeyComponent> com);
	void sortAllComs();
private:
	shared_ptr<vector<shared_ptr<MouseKeyComponent>>> _mouseKeyComs = make_shared<vector<shared_ptr<MouseKeyComponent>>>();

	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};

