#pragma once

#include <TlHelp32.h>
#include <vector>
#include <list>
using std::vector;
using std::list;


//	标题
#define MYTITLE			_T("欢迎使用")

//	进程
#define gdefstrPPID		_T("PPID")
#define gdefidxPPID		0x01
#define gdefstrPID		_T("PID")
#define gdefstrTID		_T("TID")
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
#define gdefidxTHCT		0x05
#define gdefstrTHCout	_T("挂起次数")
#define gdefidxTHCout	0x04

//	文件
#define gdefstrFName	_T("文件名")
#define gdefidxFName	0x01
#define gdefstrFPath	_T("父路径")
#define gdefidxFPath	0x03

typedef struct _MODULEINFO {	// 模块信息
	size_t	tMLP = 0;			// 模块基址
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

typedef struct _HEADINFO
{
	DWORD		th32ProcessID;	// 进程PID
	DWORD		dwFlags;		// 堆块移动属性
	SIZE_T		dwBlockSize;	// 堆块的大小，以字节为单位
	ULONG_PTR	dwAddress;		// 块开始的线性地址
	HANDLE		hHandle;		// 堆块的句柄
} HEADINFO, * LPHEADINFO;

typedef struct _FILEINFO
{
	DWORD	isDIR	= 0;
	DWORD	FSize	= 0;
	WIN32_FIND_DATA data = {};
	CString	pName;
} FILEINFO, * LPFILEINFO;

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
	bool GetHeap(vector<HEADINFO>& HDs, DWORD pid = 0);
	bool GetHwnds(vector<ULONG>* HWs);
	bool GetHwndThreadProcessId(ULONG hwnd, LPDWORD pid, LPDWORD tid);	//从窗口句柄获取PID
	bool GetHwndText(ULONG hwnd, CString& str);	//从窗口句柄获取标题
	bool GetPaths(vector<FILEINFO>* FLs, CString* path = nullptr);
	bool GetPathMode(FILEINFO& Path, CString& str);

	bool SetThreadSuspend(const DWORD TID, DWORD* count = nullptr);
	bool SetThreadResume(const DWORD TID, DWORD* count = nullptr);
	bool SetThreadTerminate(const DWORD TID, DWORD* count = nullptr);

	bool GetCPU(int& cpu);
public:
	double	FILETIME2Double(_FILETIME& ftime) {
		LARGE_INTEGER li;
		li.LowPart = ftime.dwLowDateTime;
		li.HighPart = ftime.dwHighDateTime;
		return (double)li.QuadPart;
	};
	static __int64 file_time_2_utc(const FILETIME* ftime) {
		LARGE_INTEGER li;
		li.LowPart = ftime->dwLowDateTime;
		li.HighPart = ftime->dwHighDateTime;
		return li.QuadPart;
	};
	bool FileTime2SysTime(FILETIME&fTime, CString&str) {
		FILETIME LocalTime = { 0 };
		FileTimeToLocalFileTime(&fTime, &LocalTime);
		SYSTEMTIME SystemTime = {0};
		FileTimeToSystemTime(&LocalTime, &SystemTime);
		str.Format(_T("%d-%02d-%02d_%02d:%02d:%02d.%03d\n"),
			SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
			SystemTime.wHour, SystemTime.wMinute,
			SystemTime.wSecond, SystemTime.wMilliseconds);
		return true;
	};
private:
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
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
	vector<FILEINFO>	gFILE;
	CString	oldPath;
	vector<PROCESSINFO> PEINFO;
};

extern CMyData gData;
extern CMyApi gAPI;