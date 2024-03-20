// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CSellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_setinfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cambo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_setinfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化消息订单窗口

	// 初始化下拉框
	CInfoFile file;
	// 把商品读到file对象中
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		// 遍历商品的容器 
		
		//it->name是string AddString(CString)
		// string -> CString
		m_cambo.AddString(CString(it->name.c_str()));
	}

	// 默认选中第一个商品
	m_cambo.SetCurSel(0);
	OnCbnSelchangeCombo1(); // 更新第一个商品信息
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 切换商品 触发的事件

	// 先获取商品名称
	int index = m_cambo.GetCurSel();
	// 根据索引获取具体内容
	CString name;
	m_cambo.GetLBText(index, name);
	
	// 根据商品名称，获取商品信息
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		// 遍历商品的容器 
		if ((CString)it->name.c_str() == name)
		{
			m_price = it->price;
			m_left = it->num;
			// 同步到控件上
			UpdateData(FALSE);
		}
	}

}


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	// 购买
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量要大于0！"));
		return;
	}
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量不能大于库存！"));
		return;
	}

	// 获取购买商品名称
	int index = m_cambo.GetCurSel();
	CString name;
	m_cambo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			// 同步库存量
			it->num -= m_num;
			m_left = it->num; // 控件上的数量
			
			CString str;
			str.Format(TEXT("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price * m_num);
			m_setinfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("购买成功！\n"+ str));
		}
	}

	// 把新数据写到文件
	file.WirteDocline();

	// 清空数据
	m_num = 0;
	m_setinfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 取消
	m_num = 0;
	UpdateData(FALSE);
	// 默认选择第一个
	m_cambo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
