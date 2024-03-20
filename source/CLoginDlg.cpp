﻿// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序
void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 登录按钮点击事件

	UpdateData(TRUE); // 控件内容同步到变量

	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名或密码不能为空，请重新输入！"));
		return;
	}

	// 获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (name == m_user)
	{
		if (pwd == m_pwd)
		{
			// 关闭当前对话框
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码有误！"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名有误！"));
	}
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 默认登录信息
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_user = name;
	m_pwd = pwd;
	// 同步到控件中
	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 关闭当前对话框
	//CDialogEx::OnClose();

	// 退出程序
	exit(0);
}
