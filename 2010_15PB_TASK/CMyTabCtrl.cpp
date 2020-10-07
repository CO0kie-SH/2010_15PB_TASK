// CMyTabCtrl.cpp: 实现文件
//

#include "pch.h"
#include "2010_15PB_TASK.h"
#include "CMyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
	size_t i = m_vecDlg.size();
	while (i--)
	{
		delete m_vecDlg[i];
	}
}

void CMyTabCtrl::InitTab(int nCount, ...)
{
	va_list  vl;	int i = 0;
	CDialogEx* pDlg = nullptr;
	va_start(vl, nCount);
	for (; i < gdefTabLen; i++)
		InsertItem(i, defStrsTab[i]);
	for (i = 0; i < nCount; i++)
	{
		//1 获取这一个选项，需要的数据
		wchar_t* szTabItemName = va_arg(vl, wchar_t*);
		pDlg = va_arg(vl, CDialogEx*);
		DWORD dwId = va_arg(vl, DWORD);
		//2 创建选项，创建子窗口
		//InsertItem(i, szTabItemName);
		pDlg->Create(dwId, this);
		pDlg->ShowWindow(SW_HIDE);
		//3 将子窗口移动合适的位置上
		CRect rc = {};
		GetClientRect(&rc);
		//4 将矩形框，缩小一下，能够把Tab的表头 显示出来
		rc.DeflateRect(1, 28, 1, 1);
		//5 移动
		pDlg->MoveWindow(rc);
		m_vecDlg.push_back(pDlg);
	}
	m_vecDlg[0]->ShowWindow(SW_SHOW);
	gView.Init(
		(CButton*)m_vecDlg[0]->GetDlgItem(IDC_CHECK1),
		(CListCtrl*)m_vecDlg[0]->GetDlgItem(IDC_LIST1),
		(CListCtrl*)m_vecDlg[1]->GetDlgItem(IDC_LIST2)
	);
	va_end(vl);
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序

void CMyTabCtrl::OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = GetCurSel();
	if (nSel > 0) {
		m_vecDlg[0]->ShowWindow(SW_HIDE);
		m_vecDlg[1]->ShowWindow(SW_SHOW);
	}
	else {
		m_vecDlg[0]->ShowWindow(SW_SHOW);
		m_vecDlg[1]->ShowWindow(SW_HIDE);
	}
	gView.InitList(nSel);
	*pResult = 0;
}
