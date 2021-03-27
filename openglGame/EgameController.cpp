#include "EgameController.h"
#include <assert.h>


//椅子
const static BLOCK_ST block_1[] = {
	{ {0, 1}, { 0,0 },{1,0} ,{1,-1} },
	{ {-1, -1}, { 0,-1 },{0,0} ,{1,0} }
};
//7
const static BLOCK_ST block_2[] = {
	{ {0, 2}, { 0,1 },{0,0} ,{1,0} },
	{ {2, 0}, { 1,0 },{0,0} ,{0,-1} },
	{ {0, -2}, { 0,-1 },{0,0} ,{-1,0} },
	{ {-2, 0}, { -1,0 },{0,0} ,{0,1} },
};
//山
const static BLOCK_ST block_3[] = {
	{ {0, 1}, { 0,0 },{0,-1} ,{1,0} },
	{ {-1, 0}, { 0,0 },{1,0} ,{0,-1} },
	{ {0, 1}, { 0,0 },{0,-1} ,{-1,0} },
	{ {-1, 0}, { 0,0 },{1,0} ,{0,1} },
};
//田
const static BLOCK_ST block_4[] = {
	{ {0, 0}, { 1,0 },{1,1} ,{0,1} },
};

//椅子，反向
const static BLOCK_ST block_5[] = {
	{ {-1, -1}, { -1,0 },{0,0} ,{0,1} },
	{ {-1, 1}, { 0,1 },{0,0} ,{1,0} }
};
//7,反向
const static BLOCK_ST block_6[] = {
	{ {0, 2}, { 0,1 },{0,0} ,{-1,0} },
	{ {2, 0}, { 1,0 },{0,0} ,{0,1} },
	{ {0, -2}, { 0,-1 },{0,0} ,{1,0} },
	{ {-2, 0}, { -1,0 },{0,0} ,{0,-1} },
};
//1
const static BLOCK_ST block_7[] = {
	{ {0, 2}, { 0,1 },{0,0} ,{0,-1} },
	{ {-2, 0}, { -1,0 },{0,0} ,{1,0} },
};

Block::~Block()
{
}

void Block::init()
{
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			auto tb = TxcBoxNode::create();
			addChild(tb);
		}
		else
		{
			auto db = DrawBoxNode::create();
			addChild(db);
		}
	}
	resetType(BLOCK_1);
}

void Block::setBlocks(const BLOCK_ST* blocks, int size)
{
	_tarPoss = blocks;
	_blockSize = size;
}

const BLOCK_ST& Block::getCurBlockST()
{
	BLOCK_ST& poss = _tarPoss[_dir % _blockSize];
	return poss;
}

const BLOCK_ST& Block::getBlockST(int dir)
{
	BLOCK_ST& poss = _tarPoss[dir % _blockSize];
	return poss;
}

const Vector4 s_block_color[] = {
	Vector4{0.1, 0.1, 0.2, 0.3},
	Vector4{0.7, 0.1, 0.2, 1},
	Vector4{0.3, 0.4, 0.2, 1},
	Vector4{0.1, 0.7, 0.3, 1},
	Vector4{0.7, 0.2, 0.4, 1},
	Vector4{0.2, 0.5, 0.5, 1},
	Vector4{0.1, 0.9, 0.6, 1},
	Vector4{0.1, 0.7, 0.7, 1},
};

const Vector4& Block::getBlockColor(BlockType bt)
{
	if ((int)bt > 8 || (int)bt <0)
	{
		bt = (BlockType)0;
	}
	return s_block_color[(int)bt];
}

void Block::resetType(BlockType bt)
{
	_blockType = bt;
	switch (bt)
	{
	case BLOCK_1: setBlocks(block_1, sizeof(block_1) / sizeof(*block_1)); setColor(getBlockColor(bt)); break;
	case BLOCK_2: setBlocks(block_2, sizeof(block_2) / sizeof(*block_2)); setColor(getBlockColor(bt)); break;
	case BLOCK_3: setBlocks(block_3, sizeof(block_3) / sizeof(*block_3)); setColor(getBlockColor(bt)); break;
	case BLOCK_4: setBlocks(block_4, sizeof(block_4) / sizeof(*block_4)); setColor(getBlockColor(bt)); break;
	case BLOCK_5: setBlocks(block_5, sizeof(block_5) / sizeof(*block_5)); setColor(getBlockColor(bt)); break;
	case BLOCK_6: setBlocks(block_6, sizeof(block_6) / sizeof(*block_6)); setColor(getBlockColor(bt)); break;
	case BLOCK_7: setBlocks(block_7, sizeof(block_7) / sizeof(*block_7)); setColor(getBlockColor(bt)); break;
	default:
		assert(true, "未定义的方块类型");
		//错误
		break;
	}
	resetDir(_dir);
}

void Block::setColor(const Vector4& color) {
	auto childs = getChilds();

	for (int i = 0; i < 4; ++i)
	{
		childs[i]->setColor(color);
	}
	Node::setColor(color);
}

void Block::resetDir(int dir)
{
	_dir = dir;
	auto childs = getChilds();
	auto poss = _tarPoss[_dir % _blockSize];

	for (int i = 0; i < 4; ++i)
	{
		childs[i]->setPosition(poss[i][0] * 40, poss[i][1] * 40);
	}
}


void EgameController::restart(int width, int height)
{
	_widthSize = width ;
	_heightSize = height;
	_vecBlocks.resize(_heightSize);
	for (auto it = _vecBlocks.begin(); it != _vecBlocks.end(); it++)
	{
		it->blocks.resize(_widthSize);
		for (auto jt = it->blocks.begin(); jt != it->blocks.end(); jt++)
		{
			//*jt = BOX_NULL;
			jt->resetBoxType(BOX_NULL);
		}
	}
}

void EgameController::update(float time)
{

}
