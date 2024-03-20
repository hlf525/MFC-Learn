// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CDelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DEL)
	, m_price(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化下拉框
	CInfoFile file;
	// 把商品读到file对象中
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		// 遍历商品的容器 

		//it->name是string AddString(CString)
		// string -> CString
		m_combo.AddString(CString(it->name.c_str()));
	}

	// 默认选中第一个商品
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1(); // 更新第一个商品信息
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString text;
	// 获取当前选中项
	int index = m_combo.GetCurSel();
	// 获取当前内容
	m_combo.GetLBText(index, text);

	// 根据商品名称，获取商品信息
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		// 遍历商品的容器 
		if ((CString)it->name.c_str() == text)
		{
			m_price = it->price;
			m_num = 0;
			// 同步到控件上
			UpdateData(FALSE);
		}
	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_num == 0)
	{
		MessageBox(TEXT("个数不能为0！"));
		return;
	}

	CString type;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(TEXT("删除商品：%s \r\n单价：%d \r\n个数：%d"), type, m_price, m_num);
	MessageBox(str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		// 遍历商品的容器 
		if ((CString)it->name.c_str() == type)
		{
			it->num -= m_num;
			// 同步到控件上
			UpdateData(FALSE);
		}
	}
	file.WirteDocline();
	m_num = 0;
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	m_combo.SetCurSel(0);
	m_num = 0;
	OnCbnSelchangeCombo1();
}
