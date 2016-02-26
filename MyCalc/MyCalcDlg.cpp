
// MyCalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCalc.h"
#include "MyCalcDlg.h"
#include "afxdialogex.h"
#include "cexpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCalcDlg 对话框



CMyCalcDlg::CMyCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyCalcDlg::IDD, pParent)
	, v_expression(_T(""))
	, v_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Expression, v_expression);
	DDX_Text(pDX, IDC_Result, v_result);
}

BEGIN_MESSAGE_MAP(CMyCalcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyCalcDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyCalcDlg 消息处理程序

BOOL CMyCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyCalcDlg::OnPaint()
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
HCURSOR CMyCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyCalcDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
	UpdateData();
	CString sss = v_expression;

	USES_CONVERSION; 
	string s(W2A(sss));

//	MessageBox(sss);

	CExpression ce = CExpression(s);
	char re[200];
	sprintf(re,"%f",ce.Calculate());
	CString ss=CString(re);
	v_result = ss;
	
	UpdateData(0);
}