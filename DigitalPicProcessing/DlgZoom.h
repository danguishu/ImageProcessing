#pragma once


// CDlgZoom �Ի���

class CDlgZoom : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZoom)

public:
	CDlgZoom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgZoom();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ZOOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_zoomH;
	float m_zoomV;
	afx_msg void OnBnClickedOk();
};
