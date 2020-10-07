#pragma once
#include "CMyApi.h"

class CMyView
{
public:
	void Init(
		CButton* CVBtnC1,
		CListCtrl* CVLShw,
		CListCtrl* CVLSpe);
	void InitList(int index);
private:
	int	mIndexNow = 0;
	CButton* CVBtnC1 = nullptr;
	CListCtrl*	CVLShw = nullptr;
	CListCtrl*	CVLSpe = nullptr;
};

extern CMyView gView;