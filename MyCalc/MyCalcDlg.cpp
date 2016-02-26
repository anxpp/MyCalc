
// MyCalcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyCalc.h"
#include "MyCalcDlg.h"
#include "afxdialogex.h"
#include "cexpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCalcDlg �Ի���



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


// CMyCalcDlg ��Ϣ�������

BOOL CMyCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyCalcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyCalcDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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