﻿#pragma once


// CMyDL2 对话框

class CMyDL2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDL2)

public:
	CMyDL2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDL2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
