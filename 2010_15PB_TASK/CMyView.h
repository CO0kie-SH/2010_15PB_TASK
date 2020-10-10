#pragma once
#include "CMyApi.h"

class CMyView
{
public:
	void Init(
		CButton* CVBtnC1,
		CListCtrl* CVLShw,
		CListCtrl* CVLSpe,
		CButton* CVBtnC2,
		CButton* CVBtnC3);
	void InitList(const int index);
	void SetList(const int index, const int idxPE = 0);
	void SetList(vector<THREADINFO>& THs);
	void SetList(vector<HEADINFO>& HDs);
	void SetList(vector<ULONG>& HWs);
	void SetList(vector<FILEINFO>& FLs);
public:
	void Init(CDialogEx* CVMain) {
		this->CVMain = CVMain;
	};

	void PopupMenu(LPNMITEMACTIVATE& LP, CMenu& obj) {
		int x = mIndexNow;	CString str;
		int& index = LP->iItem;
		//if (gdefidx文件 != x)
		//	if (index == -1 || x == 0) return;

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
		else if (gdefidx文件 == mIndexNow) {
			x--; bool isNULL = gData.oldPath == _T("");
			if (index == -1)
				str = _T("[空]");
			else {
				str = CVLSpe->GetItemText(index,
					isNULL ? gdefidxFPath : gdefidxFName);
			}
		}
		CMenu* pSubMenu1 = obj.GetSubMenu(x);
		pSubMenu1->AppendMenu(MF_GRAYED, MF_POPUP, str);
		pSubMenu1->TrackPopupMenu(TPM_LEFTALIGN,
			LP->ptAction.x, LP->ptAction.y, CVMain);
	};

	int GetPEIndex() {
		return this->CVLSpe->GetSelectionMark();
	};
	bool GetFIlePath(int& index, CString& str) {
		if (index == -1)	return false;
		else if (index == -2)	index = CVLSpe->GetSelectionMark();
		str = CVLSpe->GetItemText(index, gdefidxFPath);
		return true;
	};

	bool GetFIleName(int& index, CString& str, bool clean = true) {
		if (index == -1)	return false;
		if (gData.oldPath == _T(""))	return false;
		else if (index == -2)	index = CVLSpe->GetSelectionMark();
		if (clean)	str = _T("");
		CString s = CVLSpe->GetItemText(index, gdefidxFName);
		//if (wcscmp(s, _T("..")) == 0)
		//	str = CVLSpe->GetItemText(index, gdefidxFPath);
		//else
			str += /*_T("\\") +*/ s;
		return true;
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
	CButton* CVBtnC2 = nullptr;
	CButton* CVBtnC3 = nullptr;
	CListCtrl*	CVLShw = nullptr;
	CListCtrl*	CVLSpe = nullptr;
	CDialogEx*	CVMain = nullptr;
};

extern CMyView gView;