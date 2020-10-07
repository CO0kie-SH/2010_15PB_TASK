#pragma once

#include <TlHelp32.h>
#include <vector>
using std::vector;


#define gdefidx����		0x01
#define gdefidxģ��		0x02

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

typedef struct _PROCESSINFO {	//������Ϣ
	DWORD	tPID = 0;
	DWORD	pPID = 0;
	DWORD	tTHs = 0;
	DWORD	is32 = 0;
	CString	name;
	CString	path;
}PROCESSINFO, * LPPROCESSINFO;

typedef struct _MODULEINFO {	// ģ����Ϣ
	DWORD	tMLP = 0;			// ģ���ַ
	DWORD	pPID = 0;			// ��������ID
	DWORD	size = 0;			// ģ��Ĵ�С
	BYTE* modBaseAddr = 0;	// ģ��ļ��ػ���ַ
	CString	name;
	CString	path;
}MODULEINFO, * LPMODULEINFO;

#define gdefTabLen		0x06
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

private:

};

