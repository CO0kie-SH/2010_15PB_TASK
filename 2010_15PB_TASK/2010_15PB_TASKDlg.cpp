﻿
// 2010_15PB_TASKDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "2010_15PB_TASK.h"
#include "2010_15PB_TASKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#pragma region _关于 菜单
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
#pragma endregion

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy201015PBTASKDlg 对话框
#pragma region _注册对话框
CMy201015PBTASKDlg::CMy201015PBTASKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY2010_15PB_TASK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy201015PBTASKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB1, mobjTabC);
	DDX_Control(pDX, IDC_TAB1, mobjTabC);
}

BEGIN_MESSAGE_MAP(CMy201015PBTASKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32778, &CMy201015PBTASKDlg::OnClickMenu)
	ON_COMMAND(ID_32779, &CMy201015PBTASKDlg::OnClickMenuTH)
END_MESSAGE_MAP()

#pragma endregion

// CMy201015PBTASKDlg 消息处理程序

BOOL CMy201015PBTASKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
#pragma region _	系统初始化

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
#pragma endregion
	// TODO: 在此添加额外的初始化代码
	SetWindowText(MYTITLE);
	mobjTabC.InitTab(2,
		defStrsTab[0], new CMyDL1(), IDD_DIALOG1,
		defStrsTab[1], new CMyDL2(), IDD_DIALOG2
		//_T("选项3"), new CMyDialog3(), IDD_DIALOG3,
		//_T("选项4"), new CMyDialog4(), IDD_DIALOG4,
		//_T("选项5"), new CMyDialog5(), IDD_DIALOG5
	);
	gView.Init(this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy201015PBTASKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy201015PBTASKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy201015PBTASKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy201015PBTASKDlg::OnClickMenu()
{
	// TODO: 在此添加命令处理程序代码
	int index = gView.GetPEIndex();
	if (index < 0)	return;
	PROCESSINFO& pe = gData.PEINFO[index];
	vector<MODULEINFO> MDs;
	if (gAPI.GetMDs(pe, MDs)) {
		if (pe.tMDs) delete[] pe.tPMD;
		pe.tMDs = (DWORD)MDs.size();
		pe.tPMD = new MODULEINFO[pe.tMDs];
		for (DWORD i = pe.tMDs; i--; )
			pe.tPMD[i] = MDs[i];
		//改变TAB控件
		((CTabCtrl*)this->GetDlgItem(IDC_TAB1))
			->SetCurSel(gdefidx模块);
		gView.InitList(gdefidx模块);
		gView.SetList(gdefidx模块, index);
	}
}


void CMy201015PBTASKDlg::OnClickMenuTH()
{
	// TODO: 在此添加命令处理程序代码
	int index = gView.GetPEIndex();
	if (index < 0)	return;
	PROCESSINFO& pe = gData.PEINFO[index];

	vector<THREADINFO> THs;
	if (gAPI.GetTHs(THs, pe.tPID)) {
		((CTabCtrl*)this->GetDlgItem(IDC_TAB1))
			->SetCurSel(gdefidx线程);
		gView.InitList(gdefidx线程);
		gView.SetList(THs);
	}
}
