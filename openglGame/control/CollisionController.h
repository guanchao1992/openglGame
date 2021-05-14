#pragma once
#include "base/ControllerBase.hpp"
#include <vector>
#include <memory>
#include <map>
#include "component/CollisionComponent.h"
#include <list>
#include <set>
#include "base/QTreeBase.hpp"

using namespace std;

class CollisionController : public ControllerBaseT<CollisionController>
{
public:
	~CollisionController();
	void init();

	void insert(CollisionComponent*col);
	void erase(CollisionComponent*col);
	void collisionDetection();

private:
	//主角和其他物体发生碰撞
	bool collisionPlayerToOther(CollisionComponent*self, CollisionComponent*colB);
	//敌方演员与子弹碰撞
	bool collisionEnemyToOther(CollisionComponent*actor, CollisionComponent*colB);
	//友方演员与子弹碰撞
	bool collisionFriendlyToOther(CollisionComponent*actor, CollisionComponent*colB);
	//其他的碰撞处理
	bool collisionAB(CollisionComponent*colA, CollisionComponent*colB);

	//盒子碰撞检测
	bool collisionAABB(CollisionComponent*colA, CollisionComponent*colB);
private:

	//记录所有的碰撞体<标记,碰撞体们>
	std::map<COLLISIONMARK, std::set<CollisionComponent*>> _collisions;

	QTree::CQTreeBase<int, CollisionTreeData>* _tree;

	int _collisionNum = 0;	//记录一轮碰撞的总数
};

