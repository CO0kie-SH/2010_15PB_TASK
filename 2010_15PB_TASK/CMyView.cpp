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
		CVLSpe->InsertColumn(0, gdefstrNam, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, L"大小", LVCFMT_CENTER, 99);
		CVLSpe->InsertColumn(0, L"基址", LVCFMT_CENTER, 194);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 65);
		break;
	default: break;
	}
	if (index > 0)
		CVLSpe->InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50);
}

void CMyView::SetList(const int index)
{
	switch (index) {
	case gdefidx进程: {
		vector<PROCESSINFO>& PE = gData.PEINFO;
		size_t i = PE.size();	CString str;
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
	default: break;
	}
}

