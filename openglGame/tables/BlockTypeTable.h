#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <iostream> 
#include <fstream> 
/*
id 唯一Id索引
name 名字
dirtype 方块的各个方向
*/
struct BlockTypeTableBase{
int _id;
std::string _name;
nlohmann::json _dirtype;
};
typedef shared_ptr<BlockTypeTableBase> SPBlockTypeTableBase;

struct BlockTypeTableDatas
{
	BlockTypeTableDatas(const char*path)
	{
		std::ifstream iofile(path);
		nlohmann::json j;
        iofile >> j;
		for (auto it = j.begin(); it != j.end(); it++)
		{
			SPBlockTypeTableBase spTB = make_shared<BlockTypeTableBase>();
            spTB->_id = it->at("id");
            spTB->_name = it->at("name");
            spTB->_dirtype = nlohmann::json::parse(std::string(it->at("dirtype")));

            _list_datas.push_back(spTB);
			_map_datas[spTB->_id] = spTB;
		}
    }
    static BlockTypeTableDatas* getInstance()
    {
        static BlockTypeTableDatas* s_instance = new BlockTypeTableDatas("tables/BlockTypeTable.json");
        return s_instance;
    }
    static std::vector<SPBlockTypeTableBase> getDatas()
    {
        return BlockTypeTableDatas::getInstance()->_list_datas;
    }
    static SPBlockTypeTableBase getData(int id)
    {
        return BlockTypeTableDatas::getInstance()->_map_datas[id];
    }
    std::vector<SPBlockTypeTableBase> _list_datas;
    std::map<int, SPBlockTypeTableBase> _map_datas;
};
