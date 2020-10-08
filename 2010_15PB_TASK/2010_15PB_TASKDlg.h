
// 2010_15PB_TASKDlg.h: 头文件
//

#pragma once
#include "CMyTabCtrl.h"

// CMy201015PBTASKDlg 对话框
class CMy201015PBTASKDlg : public CDialogEx
{
// 构造
public:
	CMy201015PBTASKDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2010_15PB_TASK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CTabCtrl mobjTabC;
	CMyTabCtrl mobjTabC;
	afx_msg void OnClickMenu();
	afx_msg void OnClickMenuTH();
};
