#include "pch.h"
#include "CMyView.h"

CMyView gView;

void CMyView::Init(CButton* CVBtnC1, CListCtrl* CVLShw, CListCtrl* CVLSpe)
{
	this->CVBtnC1 = CVBtnC1;
	CVBtnC1->SetCheck(BST_CHECKED);
	this->CVLShw = CVLShw;
	this->CVLSpe = CVLSpe;
	CVLShw->InsertColumn(0, L"���ھ��", LVCFMT_CENTER, 65);
	CVLShw->InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
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
	case gdefidx����:
		CVLSpe->InsertColumn(0, gdefstrNam, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, gdefstrTHs, LVCFMT_CENTER, 66);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 66);
		CVLSpe->InsertColumn(0, gdefstrPPID, LVCFMT_CENTER, 66);
		break;
	case gdefidxģ��:
		CVLSpe->InsertColumn(0, gdefstrPath, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, gdefstrNam, LVCFMT_CENTER, 222);
		CVLSpe->InsertColumn(0, L"��С", LVCFMT_CENTER, 99);
		CVLSpe->InsertColumn(0, L"��ַ", LVCFMT_CENTER, 194);
		CVLSpe->InsertColumn(0, gdefstrPID, LVCFMT_CENTER, 65);
		break;
	default: break;
	}
	if (index > 0)
		CVLSpe->InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
}

void CMyView::SetList(const int index)
{
	switch (index) {
	case gdefidx����: {
		vector<PROCESSINFO>& PE = gData.PEINFO;
		size_t i = PE.size();	CString str;
		while (i--) {
			str.Format(_T("%ld"), (unsigned long)(i + 1));	//��ʽ�����
			CVLSpe->InsertItem(0, str);
			str.Format(_T("%ld"), PE[i].pPID);
			CVLSpe->SetItemText(0, gdefidxPPID, str);		//�����PID
			str.Format(_T("%ld"), PE[i].tPID);
			CVLSpe->SetItemText(0, gdefidxPID, str);		//���PID
			str.Format(_T("%ld"), PE[i].tTHs);
			CVLSpe->SetItemText(0, gdefidxTHs, str);		//����߳���
			CVLSpe->SetItemText(0, gdefidxNam, PE[i].name);	//���������
		}
		CVLSpe->EnsureVisible((int)(PE.size() - 1), FALSE);	//����������
	}break;
	default: break;
	}
}

