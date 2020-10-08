#pragma once

#include <TlHelp32.h>
#include <vector>
using std::vector;


//	标题
#define MYTITLE			_T("欢迎使用")

//	进程
#define gdefstrPPID		_T("PPID")
#define gdefidxPPID		0x01
#define gdefstrPID		_T("PID")
#define gdefidxPID		0x02
#define gdefstrTHs		_T("线程数")
#define gdefidxTHs		0x03
#define gdefstrNam		_T("进程名")
#define gdefidxNam		0x04
#define gdefstrPath		_T("路径名")
#define gdefidxPat		0x05

//	模块
#define gdefstrMAdd		_T("基址")
#define gdefidxMAdd		0x02
#define gdefstrMLen		_T("大小")
#define gdefidxMLen		0x03

//	线程
#define gdefstrTHid		_T("线程ID")
#define gdefidxTHid		0x02
#define gdefstrTHPri	_T("优先级")
#define gdefidxTHPri	0x03
#define gdefstrTHCT		_T("创建时间")
#define gdefidxTHCT		0x04
#define gdefstrTHCout	_T("挂起次数")
#define gdefidxTHCout	0x05

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

typedef struct _THREADINFO
{
	DWORD   th32ThreadID;       // 线程ID
	DWORD   th32OwnerProcessID; // 进程PID
	LONG    tpBasePri;			// 进程优先级
	SYSTEMTIME thCreatTime;		// 线程创建时间
} THREADINFO, * LPTHREADINFO;

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
	bool GetP64(PROCESSINFO& PE);
	bool GetMDs(PROCESSINFO& PE, vector<MODULEINFO>& MDs);
	bool GetTHs(vector<THREADINFO>& THs, DWORD pid = 0);
	bool GetThreadCreateTime(THREADINFO& TH);
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