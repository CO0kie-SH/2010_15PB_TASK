#pragma once


// CMyDL1 对话框

class CMyDL1 : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDL1)

public:
	CMyDL1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDL1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK() { return; };
	virtual void OnCancel() { return; };
	//afx_msg void OnClose(); //响应关闭事件！
	DECLARE_MESSAGE_MAP()
public:
	CButton CMyCheck1;
};
