#pragma once

#include "base/ControllerBase.hpp"
#include<map>
#include <string>
#include "nlohmann/json.hpp"
using namespace nlohmann;




struct TableData
{
	json _json;
};
typedef shared_ptr<TableData> SPTableData;

class TableController :public ControllerBaseT<TableController>
{
public:
	virtual void init();
	virtual void reset();

	SPTableData loadTable(const char*path);
private:
	map<string, SPTableData> _datas;
};
