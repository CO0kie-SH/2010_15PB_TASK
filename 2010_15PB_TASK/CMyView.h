#pragma once
#include "CMyApi.h"

class CMyView
{
public:
	void Init(
		CButton* CVBtnC1,
		CListCtrl* CVLShw,
		CListCtrl* CVLSpe);
	void InitList(const int index);
	void SetList(const int index, const int idxPE = 0);
	void SetList(vector<THREADINFO>& THs);
public:
	void Init(CDialogEx* CVMain) {
		this->CVMain = CVMain;
	};

	void PopupMenu(LPNMITEMACTIVATE& LP, CMenu& obj) {
		int x = 0;
		if (gdefidx窗口 == mIndexNow)	return;
		else if (gdefidx进程 == mIndexNow)	x = 1;
		else if (gdefidx模块 == mIndexNow)	x = 2;
		CMenu* pSubMenu1 = obj.GetSubMenu(x);
		int& index = LP->iItem;
		pSubMenu1->AppendMenu(MF_GRAYED, MF_POPUP,
			gData.PEINFO[index].name);
		pSubMenu1->TrackPopupMenu(TPM_LEFTALIGN,
			LP->ptAction.x, LP->ptAction.y, CVMain);
	};

	int GetPEIndex() {
		return this->CVLSpe->GetSelectionMark();
	};

	void SetThreadCount(int line, DWORD cout = 0) {
		if (line == -1) return;
		CString str;
		if (cout)
			str.Format(_T("%ld"), 1);
		this->CVLSpe->SetItemText(line, gdefidxTHCT, str);
	};
	//int GetIndexNow() { return mIndexNow; };
public:
	int	mIndexNow = 0;
private:
	CButton* CVBtnC1 = nullptr;
	CListCtrl*	CVLShw = nullptr;
	CListCtrl*	CVLSpe = nullptr;
	CDialogEx*	CVMain = nullptr;
};

extern CMyView gView;