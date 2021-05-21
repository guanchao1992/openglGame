#pragma once
#include "base/ControllerBase.hpp"
#include <vector>
#include <memory>
#include <map>
#include "component/ConllisionComponent/CollisionComponent.h"
#include <list>
#include <set>
#include "base/QTreeBase.hpp"

using namespace std;
class Node;

class CollisionController : public ControllerBaseT<CollisionController>
{
public:
	~CollisionController();
	void init();

	void insert(CollisionComponent*col);
	void erase(CollisionComponent*col);
	void collisionDetection();

private:
	//���Ǻ��������巢����ײ
	bool collisionPlayerToOther(CollisionComponent*self, CollisionComponent*colB);
	//�з���Ա���ӵ���ײ
	bool collisionEnemyToOther(CollisionComponent*actor, CollisionComponent*colB);
	//�ѷ���Ա���ӵ���ײ
	bool collisionFriendlyToOther(CollisionComponent*actor, CollisionComponent*colB);

	//������ײ��⣬�򵥵ľ�����ײ���ú�����Ҫ�Ż�
	bool collisionAABB(CollisionComponent*colA, CollisionComponent*colB);
private:

	//��¼���е���ײ��<���,��ײ����>
	std::map<COLLISIONMARK, std::set<CollisionComponent*>> _collisions;

	QTree::CQTreeBase<int, CollisionTreeData>* _tree;

	std::list<Node*> _delNodes;//��ʱɾ���Ķ���

	int _collisionNum = 0;	//��¼һ����ײ������
};

