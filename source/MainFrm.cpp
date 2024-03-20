
// MainFrm.cpp: CMainFrame 类的实现

#include "pch.h"
#include "framework.h"
#include "SaleSystem.h"
#include "InfoFile.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "CUserDlg.h"
#include "CSellDlg.h"
#include "CInfoDlg.h"
#include "CAddDlg.h"
#include "CDelDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
	ON_COMMAND(ID_32771, &CMainFrame::OnQuit)
	ON_COMMAND(ID_32772, &CMainFrame::OnUserInfo)
	ON_COMMAND(ID_32773, &CMainFrame::OnSellView)
	ON_COMMAND(ID_32774, &CMainFrame::OnStockView)
	ON_COMMAND(ID_32775, &CMainFrame::OnStockAddView)
	ON_COMMAND(ID_32776, &CMainFrame::OnStockDelView)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 设置图标，IDI_IDON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	// 设置标题 右侧标题
	SetTitle(TEXT("SaleSystem-s2024/3/4")); 

	// 设置窗口大小 0 0为起点坐标 800 500 窗口宽度和高度
	MoveWindow(0, 0, 900, 600);

	// 将窗口设置居中显示
	CenterWindow();

	// 测试CInfoFile类
	/*CInfoFile file;
	CString name;
	CString pwd;
	file.ReadLogin(name, pwd);

	MessageBox(name);
	MessageBox(pwd);

	file.WritePwd("张三", "123");*/

	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	// 拆成一行两列
	m_spliter.CreateStatic(this, 1, 2);

	// 左侧和右侧具体显示的内容
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 600), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 600), pContext);

	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext   Context;
	switch (wParam)
	{
	case NM_A:
		{
			//挂载页面
			//CUserDlg类需要包含头文件#include "UserDlg.h"
			Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 600), &Context);
			CUserDlg* pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
		break;
	case NM_B:
	{
		//挂载页面
		Context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 600), &Context);
		CSellDlg* pNewView = (CSellDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
		break;
	case NM_C:
	{
		//挂载页面
		Context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 600), &Context);
		CInfoDlg* pNewView = (CInfoDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
		break;
	case NM_D:
	{
		//挂载页面
		Context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(600, 600), &Context);
		CAddDlg* pNewView = (CAddDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
		break;
	case NM_E:
	{
		//挂载页面
		Context.m_pNewViewClass = RUNTIME_CLASS(CDelDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDelDlg), CSize(600, 600), &Context);
		CDelDlg* pNewView = (CDelDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
		break;
	default:
		MessageBox(_T("error"));
	}
	return 0;
}

void CMainFrame::OnQuit()
{
	// TODO: 在此添加命令处理程序代码

	// 退出按钮
	exit(0);
}


void CMainFrame::OnUserInfo()
{
	// TODO: 在此添加命令处理程序代码
	// 个人信息
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CMainFrame::OnSellView()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}


void CMainFrame::OnStockView()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
}


void CMainFrame::OnStockAddView()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
}


void CMainFrame::OnStockDelView()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
}
