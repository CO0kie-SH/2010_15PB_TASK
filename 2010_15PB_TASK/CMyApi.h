#pragma once

#include <TlHelp32.h>
#include <vector>
using std::vector;



#define MYTITLE			_T("欢迎使用")
#define gdefstrPPID		_T("PPID")
#define gdefidxPPID		0x01
#define gdefstrPID		_T("PID")
#define gdefidxPID		0x02
#define gdefstrTHs		_T("线程数")
#define gdefidxTHs		0x03
#define gdefstrNam		_T("进程名")
#define gdefidxNam		0x04
#define gdefstrPath		_T("路径名")
#define gdefidxPath		0x05
#define gdefstrMAdd		_T("基址")
#define gdefidxMAdd		0x02
#define gdefstrMLen		_T("大小")
#define gdefidxMLen		0x03

typedef struct _MODULEINFO {	// 模块信息
	DWORD	tMLP = 0;			// 模块基址
	DWORD	pPID = 0;			// 所属进程ID
	DWORD	size = 0;			// 模块的大小
	BYTE* modBaseAddr = 0;		// 模块的加载基地址
	CString	name;
	CString	path;
}MODULEINFO, * LPMODULEINFO;

typedef struct _PROCESSINFO {	//进程信息
	DWORD	tPID = 0;
	DWORD	pPID = 0;
	DWORD	tTHs = 0;
	DWORD	tMDs = 0;
	DWORD	is32 = 0;
	LPMODULEINFO tPMD = 0;
	CString	name;
	CString	path;
}PROCESSINFO, * LPPROCESSINFO;


#define gdefTabLen		0x06
#define gdefidx窗口		0x00
#define gdefidx进程		0x01
#define gdefidx模块		0x02
#define gdefidx线程		0x03
#define gdefidx堆栈		0x04
#define gdefidx文件		0x05
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

public:
	bool GetPEs(vector<PROCESSINFO>* INFOs = nullptr);
	bool GetMDs(PROCESSINFO& PE) { return false; };
};


class CMyData
{
public:
	void CleanPEs() {
		size_t i = PEINFO.size();
		while (i--) {
			if (PEINFO[i].tMDs)
				delete[] PEINFO[i].tPMD;
		}PEINFO.clear();
	};
public:
	vector<PROCESSINFO> PEINFO;
};

extern CMyData gData;
extern CMyApi gAPI;