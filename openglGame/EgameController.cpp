#include "EgameController.h"
#include <assert.h>

//椅子
const static int block_1[][4][2] = {
	{ {0, 1}, { 0,0 },{1,0} ,{1,-1} },
	{ {-1, -1}, { 0,-1 },{0,0} ,{1,0} }
};
//7
const static int block_2[][4][2] = {
	{ {0, 2}, { 0,1 },{0,0} ,{1,0} },
	{ {2, 0}, { 1,0 },{0,0} ,{0,-1} },
	{ {0, -2}, { 0,-1 },{0,0} ,{-1,0} },
	{ {-2, 0}, { -1,0 },{0,0} ,{0,1} },
};
//山
const static int block_3[][4][2] = {
	{ {0, 1}, { 0,0 },{0,-1} ,{1,0} },
	{ {-1, 0}, { 0,0 },{1,0} ,{0,-1} },
	{ {0, 1}, { 0,0 },{0,-1} ,{-1,0} },
	{ {-1, 0}, { 0,0 },{1,0} ,{0,1} },
};
//田
const static int block_4[][4][2] = {
	{ {0, 0}, { 1,0 },{1,1} ,{0,1} },
};

//椅子，反向
const static int block_5[][4][2] = {
	{ {-1, -1}, { -1,0 },{0,0} ,{0,1} },
	{ {-1, 1}, { 0,1 },{0,0} ,{1,0} }
};
//7,反向
const static int block_6[][4][2] = {
	{ {0, 2}, { 0,1 },{0,0} ,{-1,0} },
	{ {2, 0}, { 1,0 },{0,0} ,{0,1} },
	{ {0, -2}, { 0,-1 },{0,0} ,{1,0} },
	{ {-2, 0}, { -1,0 },{0,0} ,{0,-1} },
};
//1
const static int block_7[][4][2] = {
	{ {0, 2}, { 0,1 },{0,0} ,{0,-1} },
	{ {-2, 0}, { -1,0 },{0,0} ,{1,0} },
};

void Block::init()
{
	for (int i = 0; i < 4; ++i)
	{
		addChild(DrawBoxNode::create());
	}
	resetType(BLOCK_1);
}

void Block::resetType(BlockType bt)
{
	_blockType = bt;
	switch (bt)
	{
	case BLOCK_1: _tarPos = block_1; _tarSize = sizeof(block_1) / sizeof(*block_1); break;
	case BLOCK_2: _tarPos = block_2; _tarSize = sizeof(block_2) / sizeof(*block_2);  break;
	case BLOCK_3: _tarPos = block_3; _tarSize = sizeof(block_3) / sizeof(*block_3);  break;
	case BLOCK_4: _tarPos = block_4; _tarSize = sizeof(block_4) / sizeof(*block_4);  break;
	case BLOCK_5: _tarPos = block_5; _tarSize = sizeof(block_5) / sizeof(*block_5);  break;
	case BLOCK_6: _tarPos = block_6; _tarSize = sizeof(block_6) / sizeof(*block_6);  break;
	case BLOCK_7: _tarPos = block_7; _tarSize = sizeof(block_7) / sizeof(*block_7);  break;
	default:
		assert(true, "未定义的方块类型");
		//错误
		break;
	}
	resetDir(_dir);
}

void Block::resetDir(int dir)
{
	_dir = dir;
	auto childs = getChilds();
	//childs[0]->setPosition();
	auto dirSize = sizeof(_tarPos) / sizeof(*_tarPos);
	//auto poss = _tarPos[_dir % dirSize];
	auto poss = _tarPos[_dir % _tarSize];

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
