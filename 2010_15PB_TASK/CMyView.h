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
	void SetList(const int index);
	void PopupMenu(LPNMITEMACTIVATE& LP,
		CMenu& obj, CDialogEx* that) {
		CMenu* pSubMenu1 = obj.GetSubMenu(1);
		int& index = LP->iItem;
		pSubMenu1->AppendMenu(MF_GRAYED, MF_POPUP,
			gData.PEINFO[index].name);
		pSubMenu1->TrackPopupMenu(TPM_LEFTALIGN,
			LP->ptAction.x, LP->ptAction.y, that);
	};

public:
	//int GetIndexNow() { return mIndexNow; };
private:
	int	mIndexNow = 0;
	CButton* CVBtnC1 = nullptr;
	CListCtrl*	CVLShw = nullptr;
	CListCtrl*	CVLSpe = nullptr;
};

extern CMyView gView;