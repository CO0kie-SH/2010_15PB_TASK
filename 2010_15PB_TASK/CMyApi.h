#pragma once
#include <vector>
using std::vector;


#define defTabLen		0x06
const TCHAR defStrsTab[][3] = {
	{_T("窗口")},
	{_T("进程")},
	{_T("模块")},
	{_T("线程")},
	{_T("堆栈")},
	{_T("文件")}
};

class CMyApi
{
public:
	CMyApi();
	~CMyApi();

private:

};

