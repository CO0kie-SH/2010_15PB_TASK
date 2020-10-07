#pragma once

#include "CMyView.h"
#include "CMyDL1.h"
#include "CMyDL2.h"

// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

public://给tab添加选项，一个选项对应一个窗口，对应一个选项名，对应一个对话框ID
	// InitTab(5,L"选项1名字",窗口对象,对话框ID,
	//           L"选项2名字", 窗口对象, 对话框ID
	//...                                        )
	void InitTab(int nCount, ...);
private:
	vector<	CDialogEx* >m_vecDlg;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
};


