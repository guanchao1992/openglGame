#include "CollisionController.h"
#include "GameApp.h"
#include "component/AreaComponent.h"
#include "Game2DFight/Actor.h"
#include "Game2DFight/Bullet.h"

CollisionController::~CollisionController()
{
	delete _tree;
}

void CollisionController::init()
{
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_SELF, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_SELF_BULLET, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_ENEMY, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_ENEMY_BULLET, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_FRIENDLY, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_FRIENDLY_BULLET, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_STONE, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_NEUTRAL, std::set<CollisionComponent*>()));
	_collisions.insert(std::map<COLLISIONMARK, std::set<CollisionComponent*>>::value_type(CMARK_NEUTRAL_BULLET, std::set<CollisionComponent*>()));

	_tree = new QTree::CQTreeBase<int, CollisionTreeData>(QTree::CQTreeBase<int, CollisionTreeData>::CRect(0, 0, 1400, 900));
}

void CollisionController::insert(CollisionComponent*col)
{
	_collisions[col->getFlagMark()].insert(col);
}

void CollisionController::erase(CollisionComponent*col)
{
	_collisions[col->getFlagMark()].erase(col);
}

void CollisionController::collisionDetection()
{
	_tree->clear();

	for (auto it = _collisions.begin(); it != _collisions.end(); it++)
	{
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			if ((*jt)->isActive())
			{
				_tree->AddData(new CollisionTreeData(*jt));
			}
		}
	}
	//先需要检测会动的物体
	/*
	_collisions[CMARK_SELF];
	_collisions[CMARK_ENEMY];
	_collisions[CMARK_FRIENDLY];
	*/

	_collisionNum = 0;
	std::vector<QTree::CQTreeBase<int, CollisionTreeData>::CQTreeNode*> searchNodes;

	//主角与其他碰撞检测
	for (auto it = _collisions[CMARK_SELF].begin(); it != _collisions[CMARK_SELF].end(); it++)
	{
		searchNodes.clear();
		auto node = (Node*)(*it)->getObject();
		auto areaCom = node->getComponent<AreaComponent>();
		auto rect = areaCom->getAreaRect(true);
		_tree->Search(rect._left, rect._bottom, rect._right, rect._top, searchNodes);

		for (auto jt = searchNodes.begin(); jt != searchNodes.end(); jt++)
		{
			for (auto kt : (*jt)->_datas)
			{
				collisionPlayerToOther(*it, kt->_collCom);
			}
		}
	}

	//敌方演员与其他碰撞
	for (auto it = _collisions[CMARK_ENEMY].begin(); it != _collisions[CMARK_ENEMY].end(); it++)
	{
		searchNodes.clear();
		auto node = (Node*)(*it)->getObject();
		auto areaCom = node->getComponent<AreaComponent>();
		auto rect = areaCom->getAreaRect(true);
		_tree->Search(rect._left, rect._bottom, rect._right, rect._top, searchNodes);

		for (auto jt = searchNodes.begin(); jt != searchNodes.end(); jt++)
		{
			for (auto kt : (*jt)->_datas)
			{
				collisionEnemyToOther(*it, kt->_collCom);
			}
		}
	}

	//友军演员与其他碰撞
	for (auto it = _collisions[CMARK_FRIENDLY].begin(); it != _collisions[CMARK_FRIENDLY].end(); it++)
	{
		searchNodes.clear();
		auto node = (Node*)(*it)->getObject();
		node->setColor(Vector4(1, 0, 0, 1));
		auto areaCom = node->getComponent<AreaComponent>();
		auto rect = areaCom->getAreaRect(true);
		_tree->Search(rect._left, rect._bottom, rect._right, rect._top, searchNodes);

		for (auto jt = searchNodes.begin(); jt != searchNodes.end(); jt++)
		{
			for (auto kt : (*jt)->_datas)
			{
				collisionFriendlyToOther(*it, kt->_collCom);
			}
		}
	}

	//然后是子弹
	//子弹检测和非以上物体进行检测，因为子弹比较多，所以反过来
	_collisions[CMARK_STONE];

		
	//_tree.Search();
}

bool CollisionController::collisionPlayerToOther(CollisionComponent*selfCol, CollisionComponent*colB)
{
	if (selfCol == colB)
		return false;
	auto actorA = dynamic_cast<Actor*>(selfCol->getObject());
	if ((selfCol->getDoMark() & colB->getFlagMark()) || (selfCol->getFlagMark() & colB->getDoMark()))
	{
		if (colB->getFlagMark() == CMARK_ENEMY_BULLET)
		{
		}
		else
		{
		}
	}
	return false;
}

bool CollisionController::collisionEnemyToOther(CollisionComponent*actorCol, CollisionComponent*colB)
{
	if (actorCol == colB)
		return false;
	auto actorA = dynamic_cast<Actor*>(actorCol->getObject());
	if ((actorCol->getDoMark() & colB->getFlagMark()) || (actorCol->getFlagMark() & colB->getDoMark()))
	{
		if (colB->getFlagMark() == CMARK_SELF_BULLET || colB->getFlagMark() == CMARK_FRIENDLY_BULLET)
		{
			if (collisionAABB(actorCol,colB))
			{
				auto bulletB = dynamic_cast<Bullet*>(actorCol->getObject());
				actorA->enterState(STATE_HIT);
				//bulletB->removeFromParent();
				return true;
			}
		}
		else
		{
		}
	}
	return false;
}

bool CollisionController::collisionFriendlyToOther(CollisionComponent*actorCol, CollisionComponent*colB)
{
	return false;
}


bool CollisionController::collisionAB(CollisionComponent*colA, CollisionComponent*colB)
{
	if (colA == colB)
		return false;
	auto actorA = dynamic_cast<Actor*>(colA->getObject());
	auto actorB = dynamic_cast<Actor*>(colB->getObject());
	//auto actor = (Actor*)colA->getObject();

	//enterState
	return false;
}

bool CollisionController::collisionAABB(CollisionComponent*colA, CollisionComponent*colB)
{
	_collisionNum++;
	auto nodeA = dynamic_cast<Node*>(colA->getObject());
	auto nodeB = dynamic_cast<Node*>(colB->getObject());

	auto areaComA = nodeA->getComponent<AreaComponent>();
	auto areaComB = nodeB->getComponent<AreaComponent>();

	auto rectA = areaComA->getAreaRect(true);
	auto rectB = areaComB->getAreaRect(true);

	if (rectA._left <= rectB._right && rectA._bottom <= rectB._top && rectB._left <= rectA._right && rectB._bottom <= rectA._top)
	{
		return true;
	}
	return false;
}
