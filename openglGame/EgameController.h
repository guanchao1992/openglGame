#pragma once
#include "base/Singleton.h"
#include <2d/Node.h>
#include "2d/DrawBoxNode.h"
#include "dexode/EventBus.hpp"
#include "base/ControllerBase.hpp"
#include <nlohmann/json.hpp>

typedef int BLOCK_ST[4][2];

StatementNode(Block)
class Block:public Node
{
	StatementCreate(Block)
public:
	~Block();
	static const Vector4& getBlockColor(int blocktype);
	void init();
	void resetType(int blocktype);
	void resetDir(int dir);
	void setBlocks(const BLOCK_ST* block, int size);
	void setColor(const Vector4&);
	const nlohmann::json& getCurBlockST();
	const nlohmann::json& getBlockST(int dir);

	//vector<vector<int[2]>> _blockST;
	//vector<int[2]> _blockXY;
	//vector<int[2]> _blockNXY;
	nlohmann::json _blockST;	//�����ʽ�ڱ���Լ��
	int _blockType;
	int _blockSize;
	int _dir;
};

//һ��
struct BlockRow
{
	vector<DrawBoxNode> blocks;
};

//����˹���� ��Ϸ������
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

