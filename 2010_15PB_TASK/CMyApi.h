#pragma once

#include <TlHelp32.h>
#include <vector>
using std::vector;



#define MYTITLE			_T("��ӭʹ��")
#define gdefstrPPID		_T("PPID")
#define gdefidxPPID		0x01
#define gdefstrPID		_T("PID")
#define gdefidxPID		0x02
#define gdefstrTHs		_T("�߳���")
#define gdefidxTHs		0x03
#define gdefstrNam		_T("������")
#define gdefidxNam		0x04
#define gdefstrPath		_T("·����")
#define gdefidxPath		0x05
#define gdefstrMAdd		_T("��ַ")
#define gdefidxMAdd		0x02
#define gdefstrMLen		_T("��С")
#define gdefidxMLen		0x03

typedef struct _MODULEINFO {	// ģ����Ϣ
	DWORD	tMLP = 0;			// ģ���ַ
	DWORD	pPID = 0;			// ��������ID
	DWORD	size = 0;			// ģ��Ĵ�С
	BYTE* modBaseAddr = 0;		// ģ��ļ��ػ���ַ
	CString	name;
	CString	path;
}MODULEINFO, * LPMODULEINFO;

typedef struct _PROCESSINFO {	//������Ϣ
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
#define gdefidx����		0x00
#define gdefidx����		0x01
#define gdefidxģ��		0x02
#define gdefidx�߳�		0x03
#define gdefidx��ջ		0x04
#define gdefidx�ļ�		0x05
const TCHAR defStrsTab[][3] = {
	{_T("����")},
	{_T("����")},
	{_T("ģ��")},
	{_T("�߳�")},
	{_T("��ջ")},
	{_T("�ļ�")}
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