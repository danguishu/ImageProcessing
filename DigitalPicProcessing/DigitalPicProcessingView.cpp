
// DigitalPicProcessingView.cpp : CDigitalPicProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DigitalPicProcessing.h"
#endif

#include "DigitalPicProcessingDoc.h"
#include "DigitalPicProcessingView.h"
#include "function.h"
#include "DlgRotate.h"
#include "DlgTranslation.h"
#include "DlgZoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalPicProcessingView

IMPLEMENT_DYNCREATE(CDigitalPicProcessingView, CView)

BEGIN_MESSAGE_MAP(CDigitalPicProcessingView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32772, &CDigitalPicProcessingView::OnRotate)
	ON_COMMAND(ID_32771, &CDigitalPicProcessingView::OnTranslation)
	ON_COMMAND(ID_FILE_OPEN, &CDigitalPicProcessingView::OnFileOpen)
	ON_COMMAND(ID_32774, &CDigitalPicProcessingView::OnMirrorH)
	ON_COMMAND(ID_32775, &CDigitalPicProcessingView::OnMirrorV)
	ON_COMMAND(ID_32776, &CDigitalPicProcessingView::OnTranspose)
	ON_COMMAND(ID_32778, &CDigitalPicProcessingView::OnZoom)
END_MESSAGE_MAP()

// CDigitalPicProcessingView ����/����

CDigitalPicProcessingView::CDigitalPicProcessingView()
{
	m_hDIB = NULL;
	m_hDIBAfter = NULL;
	m_palDIB = NULL;
	m_palDIBAfter = NULL;
}


CDigitalPicProcessingView::~CDigitalPicProcessingView()
{
	if (m_hDIB != NULL)	//�ж��Ƿ���dib����
	{
		::GlobalFree(m_hDIB);
	}
	if (m_hDIBAfter != NULL)	//�ж��Ƿ���ͼ������dib����
	{
		::GlobalFree(m_hDIBAfter);
	}

	if (m_palDIB != NULL)	//�ж��Ƿ��е�ɫ��
	{
		delete m_palDIB;
	}
	if (m_palDIBAfter != NULL)	//�ж��Ƿ���ͼ�����ĵ�ɫ��
	{
		delete m_palDIBAfter;
	}
}

BOOL CDigitalPicProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDigitalPicProcessingView ����

void CDigitalPicProcessingView::OnDraw(CDC* pDC)
{
	CDigitalPicProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int cxDIB;

	// �ж�DIB�Ƿ�Ϊ��
	if (m_hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

		// ��ȡDIB���
		cxDIB = (int)m_dib.GetWidth(lpDibSection);

		// ��ȡDIB�߶�
		int cyDIB = (int)m_dib.GetHeight(lpDibSection);

		::GlobalUnlock((HGLOBAL)m_hDIB);

		CRect rcDIB(0, 0, cxDIB, cyDIB);

		CRect rcDest = rcDIB;
		// ���DIB
		m_dib.DrawDib(pDC->m_hDC, &rcDest, m_hDIB, &rcDIB, m_palDIB);
	}

	if (m_hDIBAfter != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIBAfter);

		// ��ȡDIB���
		int cxDIB1 = (int)m_dib.GetWidth(lpDibSection);

		// ��ȡDIB�߶�
		int cyDIB1 = (int)m_dib.GetHeight(lpDibSection);

		::GlobalUnlock((HGLOBAL)m_hDIBAfter);

		CRect rcDIB(0, 0, cxDIB1, cyDIB1);

		CRect rcDest(cxDIB + 10, 0, cxDIB1, cyDIB1);
		// ���DIB
		m_dib.DrawDib(pDC->m_hDC, &rcDest, m_hDIBAfter, &rcDIB, m_palDIBAfter);
	}
}


// CDigitalPicProcessingView ��ӡ

BOOL CDigitalPicProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDigitalPicProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDigitalPicProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDigitalPicProcessingView ���

#ifdef _DEBUG
void CDigitalPicProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalPicProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalPicProcessingDoc* CDigitalPicProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalPicProcessingDoc)));
	return (CDigitalPicProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

void CDigitalPicProcessingView::SetDib(HGLOBAL hDIB, CPalette *& palDIB)
{
	LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

	if (m_dib.GetWidth(lpdib) > INT_MAX || m_dib.GetHeight(lpdib) > INT_MAX)// �ж�ͼ���Ƿ����
	{
		::GlobalUnlock((HGLOBAL)hDIB);
		::GlobalFree((HGLOBAL)hDIB);	// �ͷ�DIB����			
		hDIB = NULL;// ����DIBΪ��		
		MessageBox(L"ͼƬ����,��ʼ��ʧ��");
		return;
	}
	::GlobalUnlock((HGLOBAL)hDIB);
	palDIB = new CPalette;// �����µ�ɫ��		
	if (palDIB == NULL)// �ж��Ƿ񴴽��ɹ�
	{
		::GlobalFree((HGLOBAL)hDIB);	// ʧ��		
		hDIB = NULL;// ����DIB����Ϊ��
		return;
	}
	// ����CreateDIBPalette��������ɫ��
	if (m_dib.ConstructPalette(hDIB, palDIB) == NULL)
	{
		delete palDIB;// ɾ��				
		palDIB = NULL;// ����Ϊ��	
		return;// ���ؿ�
	}
}
// CDigitalPicProcessingView ��Ϣ�������

void CDigitalPicProcessingView::OnRotate()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long lSrcLineBytes;		            //ͼ��ÿ�е��ֽ���
	long	lSrcWidth;                  //ͼ��Ŀ��
	long	lSrcHeight;					//ͼ��ĸ߶�
	LPSTR	lpSrcDib;		            //ָ��Դͼ���ָ��
	LPSTR	lpSrcStartBits;	            //ָ��ԭ���ص�ָ��
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ת�������Ŀ������ƣ�
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}

	lpSrcStartBits = m_dib.GetBits(lpSrcDib);					// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = m_dib.GetWidth(lpSrcDib);						// ��ȡͼ��Ŀ��		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);						// ��ȡͼ��ĸ߶�		
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);		// ����ͼ��ÿ�е��ֽ���

	CDlgRotate rotateDlg;
	if (rotateDlg.DoModal() != IDOK)
		return;

	
	float fRotateAngle = (float)AngleToRadian(rotateDlg.m_rotateAngle);

	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	BeginWaitCursor();

	m_hDIBAfter = (HGLOBAL)Rotate(lpSrcDib, fRotateAngle, lpSrcStartBits, lSrcWidth, lSrcHeight, palSize);

	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));//MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������//::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnTranslation()
{
	//�ж�ͼƬ�Ƿ����
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long lSrcLineBytes;						//ͼ��ÿ�е��ֽ���
	long lSrcWidth;							//ͼ��Ŀ��
	long lSrcHeight;						//ͼ��ĸ߶�
	LPSTR lpSrcDib;							//ָ��Դͼ���ָ��
	LPSTR lpSrcStartBits;					//ָ��ԭ���ص�ָ��
	long lDstLineBytes;						//��ͼ��ÿ�е��ֽ���
	lpSrcDib = (LPSTR) ::GlobalLock(m_hDIB);//��סDIB
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);
	lSrcWidth = m_dib.GetWidth(lpSrcDib);
	lSrcHeight = m_dib.GetHeight(lpSrcDib);
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);
	lDstLineBytes = m_dib.GetReqByteWidth(lSrcHeight * 8);
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);
	CDlgTranslation tranPara;
	if (tranPara.DoModal() != IDOK)
		return;
	int transH = tranPara.m_transH;
	int transV = tranPara.m_transV;
	BeginWaitCursor();
	m_hDIBAfter = (HGLOBAL)Translation(lpSrcStartBits, lSrcWidth, lSrcHeight, transH, transV, lSrcLineBytes, lDstLineBytes, palSize, lpSrcDib);
	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnFileOpen()
{
	CFileDialog dlg(true, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		L"����֧���ļ�(*.bmp)|*.bmp||");
	if (dlg.DoModal() == IDOK)
	{
		//�ļ�����·��
		CString m_szPathName = dlg.GetPathName();

		CFile file;
		if (!file.Open(m_szPathName, CFile::modeRead |
			CFile::shareDenyWrite))// ���ļ�
		{
			MessageBox(L"�ļ���ʧ��");
			return;
		}
		if (m_hDIB != NULL)	//�ж��Ƿ���dib����
		{
			;; GlobalFree(m_hDIB);
			m_hDIB = NULL;
		}
		if (m_hDIBAfter != NULL)	//�ж��Ƿ���dib����
		{
			;; GlobalFree(m_hDIBAfter);
			m_hDIBAfter = NULL;
		}
		if (m_palDIB != NULL)	//�ж��Ƿ��е�ɫ��
		{
			delete m_palDIB;
			m_palDIB = NULL;
		}
		if (m_palDIBAfter != NULL)	//�ж��Ƿ��е�ɫ��
		{
			delete m_palDIBAfter;
			m_palDIBAfter = NULL;
		}
		m_hDIB = m_dib.LoadFile(file);
		if (m_hDIB == NULL)// ����ReadDIBFile()��ȡͼ��
		{
			MessageBox(L"��ȡͼ��ʧ��");
			return;
		}
		SetDib(m_hDIB, m_palDIB);// ��ʼ��DIB

		Invalidate();
	}
}


void CDigitalPicProcessingView::OnMirrorH()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long lSrcLineBytes;						//ͼ��ÿ�е��ֽ���
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);
	lSrcWidth = m_dib.GetWidth(lpSrcDib);
	lSrcHeight = m_dib.GetHeight(lpSrcDib);
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	BeginWaitCursor();
	m_hDIBAfter = Mirror(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, palSize, lpSrcDib);
	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnMirrorV()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long lSrcLineBytes;						//ͼ��ÿ�е��ֽ���
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);
	lSrcWidth = m_dib.GetWidth(lpSrcDib);
	lSrcHeight = m_dib.GetHeight(lpSrcDib);
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	BeginWaitCursor();
	m_hDIBAfter = MirrorV(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, palSize, lpSrcDib);
	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnTranspose()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long lSrcLineBytes;						//ͼ��ÿ�е��ֽ���
	long lDstLineBytes;
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);
	lSrcWidth = m_dib.GetWidth(lpSrcDib);
	lSrcHeight = m_dib.GetHeight(lpSrcDib);
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);
	lDstLineBytes = m_dib.GetReqByteWidth(lSrcHeight * 8);
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);


	BeginWaitCursor();
	m_hDIBAfter = Transpose(lpSrcDib,lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, lDstLineBytes,palSize);
	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnZoom()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"��ѡ��ͼƬ");
		return;
	}
	long	lSrcLineBytes;	//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;		//ͼ��ĸ߶�
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
	long	lDstWidth;      //��ʱͼ��Ŀ��
	long	lDstHeight;		//��ʱͼ��ĸ߶�
	long	lDstLineBytes;	//��ʱͼ��ÿ�е��ֽ���

	lpSrcDib =(LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("�Բ��𣬲���ɫλͼ��"));                // ����
		::GlobalUnlock((HGLOBAL)m_hDIB);						// �������
		return;													//����
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);			// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = m_dib.GetWidth(lpSrcDib);					// ��ȡͼ��Ŀ��		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);					// ��ȡͼ��ĸ߶�		
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);		// ����ͼ��ÿ�е��ֽ���
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	CDlgZoom dlg;
	if (dlg.DoModal() != IDOK)
		return;
	float fX = dlg.m_zoomH;// ��ȡ�趨�����ű���
	float fY = dlg.m_zoomV;

	lDstWidth = (long)(lSrcWidth*fX + 0.5);// �������ź��ͼ��ʵ�ʿ��,��0.5������ǿ������ת��ʱ���������룬����ֱ�ӽ�ȥС������
	lDstLineBytes = m_dib.GetReqByteWidth(lDstWidth * 8);	//ת����ͼ��Ӧ�е����ֽ�����Ϊ4�ı���
	lDstHeight = (long)(lSrcHeight * fY + 0.5);// �������ź��ͼ��߶�

	BeginWaitCursor();

	m_hDIBAfter = (HGLOBAL)Zoom(lpSrcDib, lpSrcStartBits, lSrcWidth, lSrcHeight,
		lSrcLineBytes, palSize, lDstWidth, lDstLineBytes, lDstHeight, fX, fY);// ����Zoom()����ת��DIB		

	if (m_hDIBAfter != NULL)// �ж���ת�Ƿ�ɹ�
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // ����DIB��С�͵�ɫ��		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("�����ڴ�ʧ�ܣ�"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // �������
	EndWaitCursor();
}
