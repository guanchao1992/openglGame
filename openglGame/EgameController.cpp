#include "EgameController.h"
#include <assert.h>
#include "tables/BlockTypeTable.h"
#include <nlohmann/detail/conversions/from_json.hpp>


Block::~Block()
{
}

void Block::init()
{
	for (int i = 0; i < 4; ++i)
	{
		///if (i == 0)
		if (false)
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
	resetType(1);
}

const nlohmann::json& Block::getCurBlockST()
{
	return _blockST[_dir % _blockSize];
}

const nlohmann::json& Block::getBlockST(int dir)
{
	return _blockST[dir % _blockSize];
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

const Vector4& Block::getBlockColor(int bt)
{
	if (bt > 8 || bt <0)
	{
		bt = 0;
	}
	return s_block_color[(int)bt];
}

void Block::resetType(int bt)
{
	_blockType = bt;

	auto spData = BlockTypeTableDatas::getData(_blockType);
	_blockST = spData->_dirtype;
	_blockSize = _blockST.size();

	resetDir(_dir);

	setColor(getBlockColor(bt));
}

void Block::setColor(const Vector4& color) {
	auto& childs = getChilds();
	for (int i = 0; i < childs.size(); ++i)
	{
		childs[i]->setColor(color);
	}
	Node::setColor(color);
}

void Block::resetDir(int dir)
{
	_dir = dir;

	const nlohmann::json &bk = _blockST[_dir % _blockST.size()];

	auto &childs = getChilds();
	for (int i = 0; i < bk.size() - childs.size(); i++)
	{
		auto db = DrawBoxNode::create();
		addChild(db);
	}
	for (int i = 0; i < childs.size(); ++i)
	{
		if (i < bk.size())
		{
			childs[i]->setPosition(bk[i][0].get<int>() * 40 , bk[i][1].get<int>() * 40 );
		}
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
