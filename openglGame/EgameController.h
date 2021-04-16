#pragma once
#include "base/Singleton.h"
#include <2d/Node.h>
#include "2d/DrawBoxNode.h"
#include "dexode/EventBus.hpp"
#include "base/ControllerBase.hpp"
#include <nlohmann/json.hpp>
#include "GameEvent.h"
#include "dexode/eventbus/Bus.hpp"

typedef int BLOCK_ST[4][2];

StatementNode(Block)
class Block:public Node
{
	StatementCreate(Block)
public:
	~Block();
	static const Vector4& getBlockColor(int blocktype);
	void init();
	void resetType(int blocktype,int dir);
	void resetDir(int dir);
	void setColor(const Vector4&);
	const nlohmann::json& getCurBlockST();
	const nlohmann::json& getBlockST(int dir);

	//vector<vector<int[2]>> _blockST;
	//vector<int[2]> _blockXY;
	//vector<int[2]> _blockNXY;
	nlohmann::json _blockST;	//具体格式在表中约定
	int _blockType;
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

	void update(float time);

	void restartBlock();
private:
	void updatePos();
	void setDir(int dir);
	void rectrBlock();
	bool checkCan(int mx, int my, int dir);
	bool moveBlock(int mx, int my);
	void redrawAll();
	int checkEliminate();
	void setBlockPlace(const SPBlock&sp);
	bool updateBlockTimer(float time);
	void handlerKeyEvent(const KeyEvent& et);
private:


private:
	int _max_x = 14;	//0~max
	int _max_y = 16;
	int _place[15][25] = { 0 };
	int _block_scale = 40;
	int _move_type = 0; //0不动，1左2右4下。
	SPBlock _cur_block = nullptr;
	int _cur_x = 5;
	int _cur_y = 20;
	int _cur_dir = 0;
	SPNode _game_node = nullptr;
	SPNode _place_draw = nullptr;
	int _update_timer = -1;
	int _move_timer_left = -1;
	int _move_timer_right = -1;
	int _move_timer_down = -1;
	shared_ptr<dexode::eventbus::Listener<dexode::eventbus::Bus>> _block_listener;
};

