#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

string ws2s(const wstring& ws)
{
	size_t convertedChars = 0;
	string curLocale = setlocale(LC_ALL, NULL); //curLocale="C"
	setlocale(LC_ALL, "zh_CN.UTF-8");
	const wchar_t* wcs = ws.c_str();
	size_t dByteNum = sizeof(wchar_t)*ws.size() + 1;
	//cout << "ws.size():" << ws.size() << endl;            //8  ��123ABC��á���8���ַ�
	char* dest = new char[dByteNum];
	wcstombs_s(&convertedChars, dest, dByteNum, wcs, _TRUNCATE);
	//cout << "ws2s_convertedChars:" << convertedChars << endl; //11 ��ʹ����11���ֽڴ洢���ֽ��ַ��� ����������
	string result = dest;
	delete[] dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

wstring s2ws(const string& s)
{
	size_t convertedChars = 0;
	string curLocale = setlocale(LC_ALL, NULL);   //curLocale="C"
	setlocale(LC_ALL, "zh_CN.UTF-8");
	const char* source = s.c_str();
	size_t charNum = sizeof(char)*s.size() + 1;
	cout << "s.size():" << s.size() << endl;   //10 ��123ABC��á���10���ֽ�
	wchar_t* dest = new wchar_t[charNum];
	auto error = mbstowcs_s(&convertedChars, dest, charNum, source, _TRUNCATE);
	cout << "s2ws_convertedChars:" << convertedChars << endl; //9 ת��Ϊ9���ַ� ����������
	wstring result = dest;
	delete[] dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
