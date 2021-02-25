#pragma once
#include "Base/Singleton.h"
#include <2d/Node.h>
#include "2d/DrawBoxNode.h"
#include "dexode/EventBus.hpp"


enum BlockType
{
	BLOCK_1 = 0,
	BLOCK_2,
	BLOCK_3,
	BLOCK_4,
	BLOCK_5,
	BLOCK_6,
	BLOCK_7,
};

StatementNode(Block)
class Block:public Node
{
	StatementCreate(Block)
public:
	void init();
	void resetType(BlockType bt);
	void resetDir(int dir);

	BlockType _blockType;
	int _pos[4][2];
	const int(*_tarPos)[4][2];
	int _tarSize;
	int _dir;
};

//一行
struct BlockRow
{
	vector<DrawBoxNode> blocks;
};

//俄罗斯方块 游戏控制器
class EgameController
{
	SingletonClase(EgameController);
public:

	void restart(int width, int height);
	void update(float time);

private:

	vector<BlockRow> _vecBlocks;
	int _widthSize = 10;
	int _heightSize = 10;

	dexode::eventbus::Listener<dexode::EventBus> _listener;
};

