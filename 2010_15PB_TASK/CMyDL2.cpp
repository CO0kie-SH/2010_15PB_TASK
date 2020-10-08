// CMyDL2.cpp: 实现文件
//

#include "pch.h"
#include "2010_15PB_TASK.h"
#include "CMyDL2.h"
#include "afxdialogex.h"
#include "CMyView.h"

// CMyDL2 对话框

IMPLEMENT_DYNAMIC(CMyDL2, CDialogEx)

CMyDL2::CMyDL2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CMyDL2::~CMyDL2()
{
}

void CMyDL2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDL2, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CMyDL2::OnNMDblclkList2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CMyDL2::OnRclickList2)
END_MESSAGE_MAP()


// CMyDL2 消息处理程序


void CMyDL2::OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}


void CMyDL2::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1 &&
		gView.mIndexNow > 0) {
		ClientToScreen(&pNMItemActivate->ptAction);
		CMenu obj;
		obj.LoadMenuW(IDR_MENU1);
		gView.PopupMenu(pNMItemActivate, obj);
	}
	*pResult = 0;
}
