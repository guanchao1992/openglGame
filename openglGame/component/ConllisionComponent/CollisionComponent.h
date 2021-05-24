#pragma once
#include "../Component.hpp"
#include "base/Size.h"
#include "base/Vector2.h"
#include "base/QTreeBase.hpp"

class Node;

enum COLLISIONMARK 
{
	CMARK_SELF				= 0X0000000000000001,
	CMARK_SELF_BULLET		= 0X0000000000000010,
	CMARK_ENEMY				= 0X0000000000000100,
	CMARK_ENEMY_BULLET		= 0X0000000000001000,
	CMARK_FRIENDLY			= 0X0000000000010000,
	CMARK_FRIENDLY_BULLET	= 0X0000000000100000,
	CMARK_STONE				= 0X0000000001000000,
	CMARK_NEUTRAL			= 0X0000000010000000,
	CMARK_NEUTRAL_BULLET	= 0X0000000100000000,
};


class CollisionComponent :public Component
{
public:
	virtual const char* getName() { return "CollisionComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_COLLISION; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);

	inline bool checkCollision(COLLISIONMARK doMark) { return _flagMark & doMark; }
	inline COLLISIONMARK getFlagMark() { return _flagMark; }
	inline int getDoMark() { return _doMark; }

	void enableCollision(COLLISIONMARK flagMark, int doMark);	//启用碰撞检测

	virtual void collision(Object*other) = 0;

private:

	COLLISIONMARK	_flagMark;		//所属位，单一
	int				_doMark;		//二进制。保存与哪位进行检测
};


class CollisionTreeData :public QTree::CQTreeDataBase<int>
{
public:
	CollisionTreeData(CollisionComponent *collCom);
	~CollisionTreeData();
	virtual int X() const;
	virtual int Y() const;

	CollisionComponent * _collCom;
};
