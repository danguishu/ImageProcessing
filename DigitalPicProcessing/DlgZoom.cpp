// DlgZoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DigitalPicProcessing.h"
#include "DlgZoom.h"
#include "afxdialogex.h"


// CDlgZoom �Ի���

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


// CDlgZoom ��Ϣ�������


void CDlgZoom::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
