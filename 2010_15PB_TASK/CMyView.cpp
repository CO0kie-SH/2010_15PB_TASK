#include "pch.h"
#include "CMyView.h"

CMyView gView;

void CMyView::Init(CButton* CVBtnC1, CListCtrl* CVLShw, CListCtrl* CVLSpe)
{
	this->CVBtnC1 = CVBtnC1;
	this->CVLShw = CVLShw;
	this->CVLSpe = CVLSpe;
	CVLShw->InsertColumn(0, gdefstrPath, LVCFMT_CENTER, 222);
	CVLShw->InsertColumn(0, gdefstrNam, LVCFMT_CENTER, 222);
	CVLShw->InsertColumn(0, L"大小", LVCFMT_CENTER, 99);
	CVLShw->InsertColumn(0, L"基址", LVCFMT_CENTER, 194);
	CVLShw->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 65);
	CVLShw->InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50);
	CVLShw->SetExtendedStyle(/*LVS_EX_CHECKBOXES |*/
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CMyView::InitList(int index)
{
	this->mIndexNow = index;
	if (index > 0) {
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
