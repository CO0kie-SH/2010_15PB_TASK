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
				(size_t)ModuleInfo.modBaseAddr,
				ModuleInfo.th32ProcessID,
				ModuleInfo.modBaseSize,
				ModuleInfo.modBaseAddr
			};
			tmp.name.Format(_T("%s"), ModuleInfo.szModule);
			tmp.path.Format(_T("%s"), ModuleInfo.szExePath);
			//str.Format(_T("pid=%ld\t0x%p\t0x%06X\t%-20s\t%s\n"),
			//	tmp.pPID, tmp.modBaseAddr, tmp.tMLP,
			//	ModuleInfo.szModule, ModuleInfo.szExePath);
			OutputDebugString(str);
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

bool CMyApi::GetHeap(vector<HEADINFO>& HDs, DWORD pid)
{
	if (pid == 0)	return false;
	HANDLE hHeapSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPHEAPLIST, pid);
	if (INVALID_HANDLE_VALUE == hHeapSnap)	return false;
	HEAPLIST32 hl = { sizeof(HEAPLIST32) };
	BOOL ret = FALSE;	CString str;
	if (Heap32ListFirst(hHeapSnap, &hl))
	{
		HEAPENTRY32 he = { sizeof(HEAPENTRY32) };
		HEADINFO tmp;	size_t i = 0;
		do {			//外层循环PID
			//if (pid != hl.th32ProcessID)	continue;
			if (Heap32First(&he, GetCurrentProcessId(), hl.th32HeapID))
			{
				do {	//内层循环堆块
					if (he.dwBlockSize <= 130)	continue;
					tmp = HEADINFO{
						he.th32ProcessID,	// 进程PID
						he.dwFlags,			// 堆块移动属性
						he.dwBlockSize,		// 堆块的大小，以字节为单位
						he.dwAddress,		// 块开始的线性地址
						he.hHandle
					};
					HDs.push_back(tmp);
					/*
					str.Format(L"%5lld\tPID=%ld\t%ld\t0x%llX\tsize=%lld\n",
						++i, tmp.th32ProcessID, tmp.dwFlags,
						tmp.dwAddress, tmp.dwBlockSize
					);
					OutputDebugStringW(str);
					/*typedef struct tagHEAPENTRY32
					{
						SIZE_T dwSize;
						HANDLE hHandle;			// 堆块的句柄
						ULONG_PTR dwAddress;	// 块开始的线性地址
						SIZE_T dwBlockSize;		// 堆块的大小，以字节为单位
						DWORD  dwFlags;			// 堆块移动属性
						DWORD  dwLockCount;		// 该成员不再使用，始终为零
						DWORD  dwResvd;			// 保留；请勿使用或更改
						DWORD  th32ProcessID;	// PID
						ULONG_PTR  th32HeapID;	// 堆标识符
					} HEAPENTRY32;*/
				} while (Heap32Next(&he));
			}
		} while (Heap32ListNext(hHeapSnap, &hl));
	}
	CloseHandle(hHeapSnap);
	return HDs.size() > 0;
}

bool CMyApi::GetHwnds(vector<ULONG>* HWs)
{
	HWs->clear();
	EnumWindows(EnumWindowsProc, (LPARAM)HWs);
	return HWs->size() > 0;
}

BOOL CALLBACK CMyApi::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	vector<ULONG>* HWs = (vector<ULONG>*)lParam;
	HWs->push_back(static_cast<ULONG>((size_t)hwnd));
	return TRUE;
}

bool CMyApi::GetHwndThreadProcessId(ULONG hwnd, LPDWORD pid, LPDWORD tid)
{
	if (hwnd == 0)	return false;
	DWORD ttid = GetWindowThreadProcessId(
		(HWND)static_cast<size_t>(hwnd), pid
	);
	*tid = ttid;
	return ttid > 0;
}

bool CMyApi::GetHwndText(ULONG hwnd,CString& str)
{
	if (hwnd == 0)	return false;
	HWND hw = (HWND)static_cast<size_t>(hwnd);
	DWORD len = GetWindowTextLength(hw) + 1;
	if (len == 1)	return false;
	TCHAR* buff = new TCHAR[len];
	GetWindowTextW(hw, buff, len);
	str.Format(_T("%s"), buff);
	delete[] buff;
	return true;
}


bool CMyApi::SetThreadSuspend(const DWORD TID, DWORD* count)
{
	// 打开线程内核对象
	HANDLE Thread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, TID);
	if (NULL == Thread)	return false;
	BOOL ret = FALSE;
	DWORD rcount = SuspendThread(Thread);
	if (rcount != (DWORD)-1) {
		ret = TRUE;
		if (count) *count = rcount + 1;
	}
	CloseHandle(Thread);
	return (bool)ret;
}

bool CMyApi::SetThreadResume(const DWORD TID, DWORD* count)
{
	// 打开线程内核对象
	HANDLE Thread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, TID);
	if (NULL == Thread)	return false;
	BOOL ret = FALSE;
	DWORD rcount = ResumeThread(Thread);
	if (rcount != (DWORD)-1) {
		ret = TRUE;
		if (count) *count = rcount - 1;
	}
	CloseHandle(Thread);
	return (bool)ret;
}

bool CMyApi::SetThreadTerminate(const DWORD TID, DWORD* count)
{
	HANDLE Thread = OpenThread(THREAD_TERMINATE, FALSE, TID);
	if (NULL == Thread)	return false;
	DWORD exid = count == nullptr ? 0 : (*count);
	BOOL ret = TerminateThread(Thread, exid);
	CloseHandle(Thread);
	return bool(ret);
}
