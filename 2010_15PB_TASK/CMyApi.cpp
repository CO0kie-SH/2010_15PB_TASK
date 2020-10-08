#include "pch.h"
#include "CMyApi.h"

CMyData gData;
CMyApi gAPI;

CMyApi::CMyApi()
{
}

CMyApi::~CMyApi()
{
	gData.CleanPEs();
}

bool CMyApi::GetPEs(vector<PROCESSINFO>* INFOs)
{
	if (INFOs == nullptr)   return false;
	//1. 得到快照的句柄
	HANDLE hToolHelp = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, 0);
	if (hToolHelp == INVALID_HANDLE_VALUE)	return false;
	//2. 获取第一个结点的信息
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	if (Process32First(hToolHelp, &pe))
	{
		if (INFOs->size())	gData.CleanPEs();
		PROCESSINFO tmp;
		do {
			tmp = PROCESSINFO{
				pe.th32ProcessID,
				pe.th32ParentProcessID,
				pe.cntThreads
			};
			tmp.name.Format(_T("%s"), pe.szExeFile);
			INFOs->push_back(tmp);
		} while (Process32Next(hToolHelp, &pe));
		CloseHandle(hToolHelp);
	}
	return INFOs->size() != 0;
}

bool CMyApi::GetP64(PROCESSINFO& PE)
{
	BOOL ret = FALSE, is32;
	//	获取32位或64位
	HANDLE hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION, FALSE, PE.tPID);
	if (NULL == hProcess) return false;
	if (IsWow64Process(hProcess, &is32))
		PE.is32 = is32 ? 32 : 64;
	else	PE.is32 = GetLastError();
	ret = CloseHandle(hProcess);
	return (bool)ret;
}

bool CMyApi::GetMDs(PROCESSINFO& PE, vector<MODULEINFO>& MDs)
{
	if (!PE.tPID) return false;
	//	获取模块
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PE.tPID);
	if (Snapshot == INVALID_HANDLE_VALUE) return false;
	BOOL ret = FALSE;
	MODULEENTRY32 ModuleInfo = { sizeof(MODULEENTRY32) };
	if (Module32First(Snapshot, &ModuleInfo))
	{
		PE.path.Format(_T("%s"), ModuleInfo.szExePath);
		if (MDs.size() > 0x00) MDs.clear();
		CString str;
		MODULEINFO tmp;
		do {
			tmp = MODULEINFO{
				(DWORD)ModuleInfo.modBaseAddr,
				ModuleInfo.th32ProcessID,
				ModuleInfo.modBaseSize,
				ModuleInfo.modBaseAddr
			};
			tmp.name.Format(_T("%s"), ModuleInfo.szModule);
			tmp.path.Format(_T("%s"), ModuleInfo.szExePath);
			MDs.push_back(tmp);
			/*
			typedef struct tagMODULEENTRY32W
			{
				DWORD   th32ProcessID;      // 所属进程ID
				BYTE  * modBaseAddr;        // 模块的加载基地址
				DWORD   modBaseSize;        // 模块的大小
				HMODULE hModule;            // 模块的句柄(加载基址)
				WCHAR   szModule[MAX_MODULE_NAME32 + 1];	// 模块名
				WCHAR   szExePath[MAX_PATH];				// 所在路径
			} MODULEENTRY32W;
			*/
		} while (Module32Next(Snapshot, &ModuleInfo));
		ret = CloseHandle(Snapshot);
	}
	return MDs.size() > 0;
}

bool CMyApi::GetTHs(vector<THREADINFO>& THs, DWORD pid)
{
	//if (pid == 0)	return false;	//获取所有线程
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	if (Snapshot == INVALID_HANDLE_VALUE) return false;
	THREADENTRY32 ThreadInfo = { sizeof(THREADENTRY32) };
	if (Thread32First(Snapshot, &ThreadInfo))
	{
		THREADINFO tmp;
		do {
			if (pid > 0) {
				if (pid != ThreadInfo.th32OwnerProcessID)
					continue;
			}
			tmp = THREADINFO{
				ThreadInfo.th32ThreadID,
				ThreadInfo.th32OwnerProcessID,
				ThreadInfo.tpBasePri
			};
			THs.push_back(tmp);
		} while (Thread32Next(Snapshot, &ThreadInfo));
	}
	return (bool)CloseHandle(Snapshot);
}

bool CMyApi::GetThreadCreateTime(THREADINFO& TH)
{
	BOOL ret = FALSE;
	// 创建对应的结构保存时间
	FILETIME CreateTime = { 0 }, UserTime = { 0 };
	FILETIME KernelTime = { 0 }, ExitTime = { 0 };
	HANDLE Thread = OpenThread(THREAD_QUERY_INFORMATION,
		false, TH.th32ThreadID);
	if (NULL == Thread)	return false;
	// 使用函数获取到线程的创建时间
	ret=GetThreadTimes(Thread, &CreateTime,
		&ExitTime, &KernelTime, &UserTime);
	CloseHandle(Thread);
	if (!ret) return false;
	// 将时间转换为本地的系统时间
	FILETIME LocalTime = { 0 };
	FileTimeToLocalFileTime(&CreateTime, &LocalTime);
	//SYSTEMTIME SystemTime = { 0 };
	TH.thCreatTime = { 0 };
	FileTimeToSystemTime(&LocalTime, &TH.thCreatTime);
	//CString str;
	//str.Format(L"%ld\t%d-%2d-%02d_%02d:%02d:%02d.%3d\n", TH.th32ThreadID,
	//	SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
	//	SystemTime.wHour, SystemTime.wMinute,
	//	SystemTime.wSecond,SystemTime.wMilliseconds);
	//OutputDebugStringW(str);
	// 输出线程的创建时间
	//printf("%d 年 %d 月 %d 日 %d 时 %d 分 %d 秒\n",
	//	SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
	//	SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	return true;
}
