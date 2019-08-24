
// DigitalPicProcessingView.h : CDigitalPicProcessingView ��Ľӿ�
//

#pragma once
#include "Dib.h"

class CDigitalPicProcessingView : public CView
{
protected: // �������л�����
	CDigitalPicProcessingView();
	DECLARE_DYNCREATE(CDigitalPicProcessingView)

// ����
public:
	CDigitalPicProcessingDoc* GetDocument() const;

// ����
public:
	void SetDib(HGLOBAL hDIB, CPalette *&palDIB);				//��ʼ��dib����
private:
	CDib m_dib;				//����һ��DIB����
	HGLOBAL m_hDIB;			//DIB���
	HGLOBAL m_hDIBAfter;	//ͼ������DIB���
	CPalette *m_palDIB;		//��ɫ��ָ��
	CPalette *m_palDIBAfter;//ͼ�����ĵ�ɫ��ָ��

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDigitalPicProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // DigitalPicProcessingView.cpp �еĵ��԰汾
inline CDigitalPicProcessingDoc* CDigitalPicProcessingView::GetDocument() const
   { return reinterpret_cast<CDigitalPicProcessingDoc*>(m_pDocument); }
#endif

