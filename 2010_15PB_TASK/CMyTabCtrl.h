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

public://��tab���ѡ�һ��ѡ���Ӧһ�����ڣ���Ӧһ��ѡ��������Ӧһ���Ի���ID
	// InitTab(5,L"ѡ��1����",���ڶ���,�Ի���ID,
	//           L"ѡ��2����", ���ڶ���, �Ի���ID
	//...                                        )
	void InitTab(int nCount, ...);
private:
	vector<	CDialogEx* >m_vecDlg;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
};


