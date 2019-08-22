#pragma once


// CDlgZoom 对话框

class CDlgZoom : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZoom)

public:
	CDlgZoom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZoom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ZOOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_zoomH;
	float m_zoomV;
	afx_msg void OnBnClickedOk();
};
