#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <iostream> 
#include <fstream> 
/*
id 技能表
name 技能名
baseId 基础id
type 技能type
cd 技能cd
effect1 技能效果1

effect2 技能效果2
effect3 技能效果3
*/
struct SkillTableBase{
int _id;
std::string _name;
int _baseId;
int _type;
float _cd;
nlohmann::json _effect1;
nlohmann::json _effect2;
nlohmann::json _effect3;
};
typedef shared_ptr<SkillTableBase> SPSkillTableBase;

struct SkillTableDatas
{
	SkillTableDatas(const char*path)
	{
		std::ifstream iofile(path);
		nlohmann::json j;
        iofile >> j;
		for (auto it = j.begin(); it != j.end(); it++)
		{
			SPSkillTableBase spTB = make_shared<SkillTableBase>();
            spTB->_id = it->at("id");
            spTB->_name = it->at("name");
            spTB->_baseId = it->at("baseId");
            spTB->_type = it->at("type");
            spTB->_cd = it->at("cd");
            spTB->_effect1 = nlohmann::json::parse(std::string(it->at("effect1")));
            spTB->_effect2 = nlohmann::json::parse(std::string(it->at("effect2")));
            spTB->_effect3 = nlohmann::json::parse(std::string(it->at("effect3")));

            _list_datas.push_back(spTB);
			_map_datas[spTB->_id] = spTB;
		}
    }
    static SkillTableDatas* getInstance()
    {
        static SkillTableDatas* s_instance = new SkillTableDatas("tables/SkillTable.json");
        return s_instance;
    }
    static std::vector<SPSkillTableBase> getDatas()
    {
        return SkillTableDatas::getInstance()->_list_datas;
    }
    static SPSkillTableBase getData(int id)
    {
        return SkillTableDatas::getInstance()->_map_datas[id];
    }
    std::vector<SPSkillTableBase> _list_datas;
    std::map<int, SPSkillTableBase> _map_datas;
};
