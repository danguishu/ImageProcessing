
// DigitalPicProcessingView.h : CDigitalPicProcessingView 类的接口
//

#pragma once
#include "Dib.h"

class CDigitalPicProcessingView : public CView
{
protected: // 仅从序列化创建
	CDigitalPicProcessingView();
	DECLARE_DYNCREATE(CDigitalPicProcessingView)

// 特性
public:
	CDigitalPicProcessingDoc* GetDocument() const;

// 操作
public:
	void SetDib(HGLOBAL hDIB, CPalette *&palDIB);				//初始化dib对象
private:
	CDib m_dib;				//声明一个DIB对象
	HGLOBAL m_hDIB;			//DIB句柄
	HGLOBAL m_hDIBAfter;	//图像处理后的DIB句柄
	CPalette *m_palDIB;		//调色板指针
	CPalette *m_palDIBAfter;//图像处理后的调色板指针

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDigitalPicProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRotate();
	afx_msg void OnTranslation();
	afx_msg void OnFileOpen();
	afx_msg void OnMirrorH();
	afx_msg void OnMirrorV();
	afx_msg void OnTranspose();
	afx_msg void OnZoom();
	afx_msg void OnFourier();
	afx_msg void OnCosTran();
};

#ifndef _DEBUG  // DigitalPicProcessingView.cpp 中的调试版本
inline CDigitalPicProcessingDoc* CDigitalPicProcessingView::GetDocument() const
   { return reinterpret_cast<CDigitalPicProcessingDoc*>(m_pDocument); }
#endif

