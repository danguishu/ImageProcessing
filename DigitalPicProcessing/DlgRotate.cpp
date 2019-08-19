// DlgRotate.cpp : 实现文件
//

#include "stdafx.h"
#include "DigitalPicProcessing.h"
#include "DlgRotate.h"
#include "afxdialogex.h"


// CDlgRotate 对话框

IMPLEMENT_DYNAMIC(CDlgRotate, CDialogEx)

CDlgRotate::CDlgRotate(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ROTATE, pParent)
	, m_rotateAngle(0)
{

}

CDlgRotate::~CDlgRotate()
{
}

void CDlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rotateAngle);
}


BEGIN_MESSAGE_MAP(CDlgRotate, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRotate::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRotate 消息处理程序


void CDlgRotate::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
