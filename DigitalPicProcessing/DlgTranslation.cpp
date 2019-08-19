// DlgTranslation.cpp : 实现文件
//

#include "stdafx.h"
#include "DigitalPicProcessing.h"
#include "DlgTranslation.h"
#include "afxdialogex.h"


// CDlgTranslation 对话框

IMPLEMENT_DYNAMIC(CDlgTranslation, CDialogEx)

CDlgTranslation::CDlgTranslation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_TRANSLATION, pParent)
	, m_transH(0)
	, m_transV(0)
{

}

CDlgTranslation::~CDlgTranslation()
{
}

void CDlgTranslation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_transH);
	DDX_Text(pDX, IDC_EDIT2, m_transV);
}


BEGIN_MESSAGE_MAP(CDlgTranslation, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTranslation::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTranslation 消息处理程序


void CDlgTranslation::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
