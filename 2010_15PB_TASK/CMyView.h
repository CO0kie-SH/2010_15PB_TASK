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
	void SetList(vector<HEADINFO>& HDs);
	void SetList(vector<ULONG>& HWs);
public:
	void Init(CDialogEx* CVMain) {
		this->CVMain = CVMain;
	};

	void PopupMenu(LPNMITEMACTIVATE& LP, CMenu& obj) {
		int x = mIndexNow;	CString str;
		int& index = LP->iItem;
		if (index == -1 || x == 0) return;
		if (gdefidx窗口 == mIndexNow)	return;
		else if (gdefidx进程 == mIndexNow) {
			str = gData.PEINFO[index].name;
		}
		else if (gdefidx模块 == mIndexNow) {
			return;
		}
		else if (gdefidx线程 == mIndexNow) {
			str.Format(_T("TID="));
			str += this->CVLSpe->GetItemText(
				index, gdefidxTHid);
		}
		CMenu* pSubMenu1 = obj.GetSubMenu(x);
		pSubMenu1->AppendMenu(MF_GRAYED, MF_POPUP, str);
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
			str.Format(_T("%ld"), cout);
		this->CVLSpe->SetItemText(line, gdefidxTHCout, str);
	};
	int GetThreadID(int line) {
		if (line == -1)	return -1;
		CString& str=
			CVLSpe->GetItemText(line, gdefidxTHid);
		return _ttoi(str);
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