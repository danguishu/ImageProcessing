#pragma once


// CDlgRotate 对话框

class CDlgRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotate)

public:
	CDlgRotate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRotate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_rotateAngle;
};
