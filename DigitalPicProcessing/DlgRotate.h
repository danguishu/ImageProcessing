#pragma once


// CDlgRotate �Ի���

class CDlgRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotate)

public:
	CDlgRotate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRotate();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_rotateAngle;
};
