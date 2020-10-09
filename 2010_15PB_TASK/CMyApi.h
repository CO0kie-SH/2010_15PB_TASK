#pragma once

#include <TlHelp32.h>
#include <vector>
#include <list>
using std::vector;
using std::list;


//	����
#define MYTITLE			_T("��ӭʹ��")

//	����
#define gdefstrPPID		_T("PPID")
#define gdefidxPPID		0x01
#define gdefstrPID		_T("PID")
#define gdefstrTID		_T("TID")
#define gdefidxPID		0x02
#define gdefstrTHs		_T("�߳���")
#define gdefidxTHs		0x03
#define gdefstrNam		_T("������")
#define gdefidxNam		0x04
#define gdefstrPath		_T("·����")
#define gdefidxPat		0x05

//	ģ��
#define gdefstrMAdd		_T("��ַ")
#define gdefidxMAdd		0x02
#define gdefstrMLen		_T("��С")
#define gdefidxMLen		0x03

//	�߳�
#define gdefstrTHid		_T("�߳�ID")
#define gdefidxTHid		0x02
#define gdefstrTHPri	_T("���ȼ�")
#define gdefidxTHPri	0x03
#define gdefstrTHCT		_T("����ʱ��")
#define gdefidxTHCT		0x05
#define gdefstrTHCout	_T("�������")
#define gdefidxTHCout	0x04

typedef struct _MODULEINFO {	// ģ����Ϣ
	size_t	tMLP = 0;			// ģ���ַ
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

typedef struct _THREADINFO
{
	DWORD   th32ThreadID;       // �߳�ID
	DWORD   th32OwnerProcessID; // ����PID
	LONG    tpBasePri;			// �������ȼ�
	SYSTEMTIME thCreatTime;		// �̴߳���ʱ��
} THREADINFO, * LPTHREADINFO;

typedef struct _HEADINFO
{
	DWORD		th32ProcessID;	// ����PID
	DWORD		dwFlags;		// �ѿ��ƶ�����
	SIZE_T		dwBlockSize;	// �ѿ�Ĵ�С�����ֽ�Ϊ��λ
	ULONG_PTR	dwAddress;		// �鿪ʼ�����Ե�ַ
	HANDLE		hHandle;		// �ѿ�ľ��
} HEADINFO, * LPHEADINFO;

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
	bool GetP64(PROCESSINFO& PE);
	bool GetMDs(PROCESSINFO& PE, vector<MODULEINFO>& MDs);
	bool GetTHs(vector<THREADINFO>& THs, DWORD pid = 0);
	bool GetThreadCreateTime(THREADINFO& TH);
	bool GetHeap(vector<HEADINFO>& HDs, DWORD pid = 0);
	bool GetHwnds(vector<ULONG>* HWs);
	bool GetHwndThreadProcessId(ULONG hwnd, LPDWORD pid, LPDWORD tid);	//�Ӵ��ھ����ȡPID
	bool GetHwndText(ULONG hwnd, CString& str);	//�Ӵ��ھ����ȡ����

	bool SetThreadSuspend(const DWORD TID, DWORD* count = nullptr);
	bool SetThreadResume(const DWORD TID, DWORD* count = nullptr);
	bool SetThreadTerminate(const DWORD TID, DWORD* count = nullptr);
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
	vector<PROCESSINFO> PEINFO;
};

extern CMyData gData;
extern CMyApi gAPI;