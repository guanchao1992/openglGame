#include "EgameController.h"
#include <assert.h>
#include "tables/BlockTypeTable.h"
#include <nlohmann/detail/conversions/from_json.hpp>
#include "GameEvent.h"
#include "GameApp.h"
#include "component/DrawRanderComponent.h"
#include <2d/Object.hpp>


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
	resetType(1, 0);
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

void Block::resetType(int bt, int dir)
{
	_blockType = bt;

	auto spData = BlockTypeTableDatas::getData(_blockType);
	_blockST = spData->_dirtype;
	_blockSize = _blockST.size();

	//std::cout << _blockST.dump() << std::endl;

	resetDir(dir);

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


/*==================EgameController========================*/

void EgameController::update(float time)
{

}

bool EgameController::updateBlockTimer(float time)
{
	if (checkCan(0, -1, _cur_dir))
	{
		_cur_y--;
		updatePos();
	}
	else
	{
		setBlockPlace(_cur_block);
		rectrBlock();
	}
	return false;
}

void EgameController::handlerKeyEvent(const KeyEvent& et)
{
	switch (et._key)
	{
	case GLFW_KEY_UP: case 'w': case 'W':case GLFW_KEY_SPACE:
		if (et._isDown)
		{
			if (checkCan(0, 0, _cur_dir + 1))
			{
				setDir(++_cur_dir);
			}
		}
		break;
	case GLFW_KEY_DOWN: case 's': case 'S':
		if (et._isDown)
		{
			if (!(_move_type & 0x0100))
			{
				_move_type = _move_type | 0x0100;
				TimerController::getInstance()->resetTime(_move_timer_down);
				if (checkCan(0, -1, _cur_dir))
				{
					_cur_y--;
					updatePos();
				}
				else
				{
					setBlockPlace(_cur_block);
					rectrBlock();
				}
			}
		}
		else
			_move_type = _move_type & ~0x0100;
		break;
	case GLFW_KEY_LEFT: case 'a': case 'A':
		if (et._isDown)
		{
			if (!(_move_type & 0x0001))
			{
				_move_type = _move_type | 0x0001;
				TimerController::getInstance()->resetTime(_move_timer_left);
				moveBlock(-1, 0);
			}
		}
		else
			_move_type = _move_type & ~0x0001;
		break;
	case GLFW_KEY_RIGHT: case 'd': case 'D':
		if (et._isDown)
		{
			if (!(_move_type & 0x0010))
			{
				_move_type = _move_type | 0x0010;
				TimerController::getInstance()->resetTime(_move_timer_right);
				moveBlock(1, 0);
			}
		}
		else
			_move_type = _move_type & ~0x0010;
		break;
	default:
		break;
	}
}

//以下保存了全部游戏逻辑
void EgameController::restartBlock()
{
	if (_game_node == nullptr)
	{
		_game_node = Node::create();
		GameApp::getInstance()->_start->addChild(_game_node);
	}
	if (_cur_block == nullptr)
	{
		_cur_block = Block::create();
		_game_node->addChild(_cur_block);
	}
	if (_place_draw == nullptr)
	{
		_place_draw = Node::create();
		_game_node->addChild(_place_draw);
		auto drawCom = _place_draw->addComponent<DrawRanderComponent>();
	}
	_cur_x = 5;
	_cur_y = 20;
	_cur_dir = 0;
	memset(_place, 0, 4 * 15 * 25);
	redrawAll();

	rectrBlock();

	if (_update_timer == -1)
	{
		_update_timer = TimerController::getInstance()->addTimer(1, -1, std::bind(&EgameController::updateBlockTimer, this, std::placeholders::_1));
	}

	if (_move_timer_left == -1)
	{
		_move_timer_left = TimerController::getInstance()->addTimer(0.15, -1, [this](float time) {
			if (_move_type & 0x0001)
			{
				moveBlock(-1, 0);
			}
			return false;
		});
	}
	if (_move_timer_right == -1)
	{
		_move_timer_right = TimerController::getInstance()->addTimer(0.15, -1, [this](float time) {
			if (_move_type & 0x0010)
			{
				moveBlock(1, 0);
			}
			return false;
		});
	}
	if (_move_timer_down == -1)
	{
		_move_timer_down = TimerController::getInstance()->addTimer(0.1, -1, [this](float time) {
			if (_move_type & 0x0100)
			{
				if (checkCan(0, -1, _cur_dir))
				{
					_cur_y--;
					updatePos();
				}
				else
				{
					setBlockPlace(_cur_block);
					rectrBlock();
				}
			}
			return false;
		});
	}
	if (_block_listener == nullptr)
	{
		_block_listener = GameApp::getInstance()->createListenerSP();
		_block_listener->listen<KeyEvent>(std::bind(&EgameController::handlerKeyEvent, this, std::placeholders::_1));

	}
}

void EgameController::updatePos()
{
	_cur_block->setPosition(_block_scale * _cur_x, _block_scale * _cur_y);
}

void EgameController::setDir(int dir)
{
	_cur_block->resetDir(dir);
}

void EgameController::rectrBlock()
{
	_cur_dir = 0;
	_cur_x = 5;
	_cur_y = 20;
	_cur_block->resetType(rand() % 7 + 1, _cur_dir);
	updatePos();

	//std::cout << _cur_block->_blockST << std::endl;
	//std::cout << _cur_block->getCurBlockST() << std::endl;
}

bool EgameController::checkCan(int mx, int my, int dir)
{
	int temp_x = _cur_x + mx;
	int temp_y = _cur_y + my;
	for (int n = 0; n < 4; ++n)
	{
		auto block = _cur_block->getBlockST(dir);
		int ix = block[n][0];
		int iy = block[n][1];

		if (temp_x + ix < 0 || temp_x + ix > _max_x || temp_y + iy < 0)
		{
			//std::cout << block;
			return false;
		}
		if (_place[temp_x + ix][temp_y + iy] != 0)
		{
			return false;
		}
	}
	return true;
}

bool EgameController::moveBlock(int mx, int my)
{
	if (checkCan(mx, my, _cur_dir))
	{
		_cur_x += mx;
		_cur_y += my;
		updatePos();
		return true;
	}
	else
	{
		return false;
	}
}

void EgameController::redrawAll()
{
	//_place_draw->clearAllVertex();
	auto drawCom = _place_draw->getComponent<DrawRanderComponent>();
	drawCom->clearAllVertex();
	for (int y = 0; y <= _max_y; ++y)
	{
		for (int x = 0; x <= _max_x; ++x)
		{
			if (_place[x][y] != 0)
			{
				auto color = Block::getBlockColor(_place[x][y]);
				drawCom->addVertex(Vector2((x + 0) * _block_scale, (y + 0)*_block_scale), color);
				drawCom->addVertex(Vector2((x + 1) * _block_scale, (y + 0)*_block_scale), color);
				drawCom->addVertex(Vector2((x + 1) * _block_scale, (y + 1)*_block_scale), color);
				drawCom->addVertex(Vector2((x + 0) * _block_scale, (y + 1)*_block_scale), color);
				drawCom->signDraw(GL_TRIANGLE_FAN);
			}
		}
	}
}

int EgameController::checkEliminate()
{
	std::map<int, bool> eliminateYs;
	for (int y = 0; y < _max_y; ++y)
	{
		bool isEliminate = true;
		for (int x = 0; x <= _max_x; x++)
		{
			if (_place[x][y] == 0)
			{
				isEliminate = false;
				break;
			}
		}
		if (isEliminate)
		{
			eliminateYs[y] = true;
		}
	}
	if (eliminateYs.size() == 0)
	{
		return 0;
	}

	int temp_y = 0;
	for (int y = 0; y <= _max_y; ++y)
	{
		while (eliminateYs.find(temp_y) != eliminateYs.end())
		{
			temp_y++;
		}
		for (int x = 0; x <= _max_x; ++x)
		{
			_place[x][y] = temp_y <= _max_y ? _place[x][temp_y] : 0;
		}
		temp_y++;
	}
	return (int)eliminateYs.size();
}

void EgameController::setBlockPlace(const SPBlock&sp)
{
	auto drawCom = _place_draw->getComponent<DrawRanderComponent>();
	for (int n = 0; n < 4; ++n)
	{
		auto block = sp->getCurBlockST();
		int ix = block[n][0];
		int iy = block[n][1];
		int x = _cur_x + ix;
		int y = _cur_y + iy;

		if ((x >= 0 && x <= _max_x) && (y >= 0 && y < _max_y))
		{
			_place[x][y] = (int)sp->_blockType;
			drawCom->addVertex(Vector2((x + 0) * _block_scale, (y + 0)*_block_scale), sp->getColor());
			drawCom->addVertex(Vector2((x + 1) * _block_scale, (y + 0)*_block_scale), sp->getColor());
			drawCom->addVertex(Vector2((x + 1) * _block_scale, (y + 1)*_block_scale), sp->getColor());
			drawCom->addVertex(Vector2((x + 0) * _block_scale, (y + 1)*_block_scale), sp->getColor());
			drawCom->signDraw(GL_TRIANGLE_FAN);
		}
	}

	if (checkEliminate() > 0)
	{
		//redrawAll();
	}
	redrawAll();
}

