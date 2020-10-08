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
