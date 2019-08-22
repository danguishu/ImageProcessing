// DlgZoom.cpp : 实现文件
//

#include "stdafx.h"
#include "DigitalPicProcessing.h"
#include "DlgZoom.h"
#include "afxdialogex.h"


// CDlgZoom 对话框

IMPLEMENT_DYNAMIC(CDlgZoom, CDialogEx)

CDlgZoom::CDlgZoom(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ZOOM, pParent)
	, m_zoomH(0)
	, m_zoomV(0)
{

}

CDlgZoom::~CDlgZoom()
{
}

void CDlgZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_zoomH);
	DDX_Text(pDX, IDC_EDIT2, m_zoomV);
}


BEGIN_MESSAGE_MAP(CDlgZoom, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgZoom::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgZoom 消息处理程序


void CDlgZoom::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
