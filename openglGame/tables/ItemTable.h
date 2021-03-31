#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <iostream> 
#include <fstream> 
/*
id 测试用道具表
name 道具名
type 道具类型：1=类型1，2=类型2，3=类型3
max 堆叠上限
sort 排序规则
*/
struct ItemTableBase{
int _id;
std::string _name;
int _type;
int _max;
int _sort;
};
typedef shared_ptr<ItemTableBase> SPItemTableBase;

struct ItemTableDatas
{
	ItemTableDatas(const char*path)
	{
		std::ifstream iofile(path);
		nlohmann::json j;
        iofile >> j;
		for (auto it = j.begin(); it != j.end(); it++)
		{
			SPItemTableBase spTB = make_shared<ItemTableBase>();
            spTB->_id = it->at("id");
            spTB->_name = it->at("name");
            spTB->_type = it->at("type");
            spTB->_max = it->at("max");
            spTB->_sort = it->at("sort");

            _list_datas.push_back(spTB);
			_map_datas[spTB->_id] = spTB;
		}
    }
    static ItemTableDatas* getInstance()
    {
        static ItemTableDatas* s_instance = new ItemTableDatas("tables/ItemTable.json");
        return s_instance;
    }
    static std::vector<SPItemTableBase> getDatas()
    {
        return ItemTableDatas::getInstance()->_list_datas;
    }
    static SPItemTableBase getData(int id)
    {
        return ItemTableDatas::getInstance()->_map_datas[id];
    }
    std::vector<SPItemTableBase> _list_datas;
    std::map<int, SPItemTableBase> _map_datas;
};
