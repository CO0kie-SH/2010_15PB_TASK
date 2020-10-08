#include "pch.h"
#include "CMyView.h"

CMyView gView;

void CMyView::Init(CButton* CVBtnC1, CListCtrl* CVLShw, CListCtrl* CVLSpe)
{
	this->CVBtnC1 = CVBtnC1;
	CVBtnC1->SetCheck(BST_CHECKED);
	this->CVLShw = CVLShw;
	this->CVLSpe = CVLSpe;
	CVLShw->InsertColumn(0, L"窗口句柄", LVCFMT_CENTER, 65);
	CVLShw->InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50);
	CVLShw->SetExtendedStyle(/*LVS_EX_CHECKBOXES |*/
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CMyView::InitList(const int index)
{
	this->mIndexNow = index;
	if (index > 0) {
		CVLSpe->DeleteAllItems();
		while (CVLSpe->DeleteColumn(0));
		CVLSpe->SetExtendedStyle(/*LVS_EX_CHECKBOXES |*/
			LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}
	switch (index) {
	case gdefidx进程:
		CVLSpe->InsertColumn(0, gdefstrNam, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, gdefstrTHs, LVCFMT_CENTER, 66);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 66);
		CVLSpe->InsertColumn(0, gdefstrPPID, LVCFMT_CENTER, 66);
		break;
	case gdefidx模块:
		CVLSpe->InsertColumn(0, gdefstrPath, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, _T("模块名"), LVCFMT_CENTER, 200);
		CVLSpe->InsertColumn(0, gdefstrMLen, LVCFMT_CENTER, 90);
		CVLSpe->InsertColumn(0, gdefstrMAdd, LVCFMT_CENTER, 190);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 65);
		break;
	case gdefidx线程:
		CVLSpe->InsertColumn(0, gdefstrTHCT, LVCFMT_CENTER, 77);
		CVLSpe->InsertColumn(0, gdefstrTHCout, LVCFMT_CENTER, 211);
		CVLSpe->InsertColumn(0, gdefstrTHPri, LVCFMT_CENTER, 77);
		CVLSpe->InsertColumn(0, gdefstrTHid, LVCFMT_CENTER, 66);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 65);
		break;
	default: break;
	}
	if (index > 0)
		CVLSpe->InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50);
}

//	设置列表框的值
void CMyView::SetList(const int index, const int idxPE)
{
	vector<PROCESSINFO>& PE = gData.PEINFO;
	size_t i = PE.size();	CString str;
	switch (index) {
	case gdefidx进程: {
		while (i--) {
			str.Format(_T("%ld"), (unsigned long)(i + 1));	//格式化序号
			CVLSpe->InsertItem(0, str);
			str.Format(_T("%ld"), PE[i].pPID);
			CVLSpe->SetItemText(0, gdefidxPPID, str);		//输出父PID
			str.Format(_T("%ld"), PE[i].tPID);
			CVLSpe->SetItemText(0, gdefidxPID, str);		//输出PID
			str.Format(_T("%ld"), PE[i].tTHs);
			CVLSpe->SetItemText(0, gdefidxTHs, str);		//输出线程数
			CVLSpe->SetItemText(0, gdefidxNam, PE[i].name);	//输出进程名
		}
		CVLSpe->EnsureVisible((int)(PE.size() - 1), FALSE);	//滚动条到底
	}break;
	case gdefidx模块: {
		i = (size_t)PE[idxPE].tMDs;
		LPMODULEINFO pMD = PE[idxPE].tPMD;
		while (i--) {
			str.Format(_T("%ld"), (unsigned long)(i + 1));	//格式化序号
			CVLSpe->InsertItem(0, str);
			str.Format(_T("%ld"), pMD[i].pPID);
			CVLSpe->SetItemText(0, gdefidxPPID, str);		//输出进程
			str.Format(_T("0x%p"), pMD[i].modBaseAddr);
			CVLSpe->SetItemText(0, gdefidxMAdd, str);		//输出基址
			str.Format(_T("0x%06X"), pMD[i].size);
			CVLSpe->SetItemText(0, gdefidxMLen, str);		//输出大小
			CVLSpe->SetItemText(0, gdefidxNam, pMD[i].name);//输出名称
			CVLSpe->SetItemText(0, gdefidxPat, pMD[i].path);//输出路径
		}
		CVLSpe->EnsureVisible((PE[idxPE].tMDs - 1), FALSE);	//滚动条到底
	}break;
	default: break;
	}
}

//	重载设置列表框的值
void CMyView::SetList(vector<THREADINFO>& THs)
{
	size_t i = THs.size();	CString str;
	if (i > 999)	this->CVLSpe->ShowWindow(SW_HIDE);	//大量数据则隐藏
	while (i--) {
		str.Format(_T("%ld"), (unsigned long)(i + 1));	//格式化序号
		CVLSpe->InsertItem(0, str);
		str.Format(_T("%ld"), THs[i].th32OwnerProcessID);
		CVLSpe->SetItemText(0, gdefidxPPID, str);		//输出进程
		str.Format(_T("%ld"), THs[i].th32ThreadID);
		CVLSpe->SetItemText(0, gdefidxTHid, str);		//输出线程ID
		str.Format(_T("%ld"), THs[i].tpBasePri);
		CVLSpe->SetItemText(0, gdefidxTHPri, str);		//输出优先级
		if (gAPI.GetThreadCreateTime(THs[i])) {
			SYSTEMTIME& SystemTime = THs[i].thCreatTime;
			str.Format(_T("%d-%2d-%02d_%02d:%02d:%02d.%03d\n"),
				SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
				SystemTime.wHour, SystemTime.wMinute,
				SystemTime.wSecond, SystemTime.wMilliseconds);
			CVLSpe->SetItemText(0, gdefidxTHCT, str);		//输出创建时间
		}
	}
	CVLSpe->EnsureVisible((int)(THs.size() - 1), FALSE);//滚动条到底
	if (THs.size() > 999)	this->CVLSpe->ShowWindow(SW_NORMAL);
}

