// CMyDL1.cpp: 实现文件
//

#include "pch.h"
#include "2010_15PB_TASK.h"
#include "CMyDL1.h"
#include "afxdialogex.h"


// CMyDL1 对话框

IMPLEMENT_DYNAMIC(CMyDL1, CDialogEx)

CMyDL1::CMyDL1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMyDL1::~CMyDL1()
{
}

void CMyDL1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, CMyCheck1);
}


BEGIN_MESSAGE_MAP(CMyDL1, CDialogEx)
END_MESSAGE_MAP()


// CMyDL1 消息处理程序
