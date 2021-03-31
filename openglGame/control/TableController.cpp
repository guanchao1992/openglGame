#include "TableController.h"
#include <iostream> 
#include <fstream> 
#include "tables/ItemTable.h"

void TableController::init()
{
	// read a JSON file

	//_datas

	/*
	std::ifstream i("res/datas/ItemTable.json");
	json j;
	i >> j;
	*/

	//json j = { {"2",21} ,{"test","efw"} };

	// write prettified JSON to another file
	//std::ofstream o("res/pretty.json");
	//o << j << std::endl;
	//auto a = ItemTableDatas::getDatas();
}

void TableController::reset()
{
}

SPTableData TableController::loadTable(const char*path)
{
	char szDrive[_MAX_DRIVE];   //磁盘名
	char szDir[_MAX_DIR];       //路径名
	char szFname[_MAX_FNAME];   //文件名
	char szExt[_MAX_EXT];       //后缀名
	_splitpath_s(path, szDrive, szDir, szFname, szExt); //分解路径

	std::ifstream stream(path);
	SPTableData pdata = make_shared<TableData>();
	stream >> pdata->_json;

	return pdata;
}
