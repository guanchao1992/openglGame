#pragma once
#include "base/ControllerBase.hpp"
#include "component/MouseComponent.h"
#include <vector>
#include <memory>

using namespace std;

class MouseController : public ControllerBaseT<MouseController>
{
public:
	void init();
	void addMouseComponent(shared_ptr<MouseComponent> com);
	void sortAllComs();
private:
	shared_ptr<vector<shared_ptr<MouseComponent>>> _mouseComs = make_shared<vector<shared_ptr<MouseComponent>>>();

	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};

