#pragma once
#include "base/Singleton.h"
#include <2d/Node.h>
#include "2d/DrawBoxNode.h"
#include "dexode/EventBus.hpp"
#include "base/ControllerBase.hpp"


enum BlockType
{
	BLOCK_NULL = 0,
	BLOCK_1 = 1,
	BLOCK_2,
	BLOCK_3,
	BLOCK_4,
	BLOCK_5,
	BLOCK_6,
	BLOCK_7,
};

typedef const int BLOCK_ST[4][2];

StatementNode(Block)
class Block:public Node
{
	StatementCreate(Block)
public:
	~Block();
	static const Vector4& getBlockColor(BlockType);
	void init();
	void resetType(BlockType bt);
	void resetDir(int dir);
	void setBlocks(const BLOCK_ST* block, int size);
	void setColor(const Vector4&);
	const BLOCK_ST& getCurBlockST();
	const BLOCK_ST& getBlockST(int dir);

	BlockType _blockType;
	BLOCK_ST* _tarPoss;
	int _blockSize;
	int _dir;
};

//一行
struct BlockRow
{
	vector<DrawBoxNode> blocks;
};

//俄罗斯方块 游戏控制器
class EgameController :public ControllerBaseT<EgameController>
{
public:

	void restart(int width, int height);
	void update(float time);

private:

	vector<BlockRow> _vecBlocks;
	int _widthSize = 10;
	int _heightSize = 10;

	dexode::eventbus::Listener<dexode::EventBus> _listener;
};

