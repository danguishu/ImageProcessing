
// DigitalPicProcessingView.cpp : CDigitalPicProcessingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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
	ON_COMMAND(ID_32780, &CDigitalPicProcessingView::OnFourier)
	ON_COMMAND(ID_32782, &CDigitalPicProcessingView::OnCosTran)
END_MESSAGE_MAP()

// CDigitalPicProcessingView 构造/析构

CDigitalPicProcessingView::CDigitalPicProcessingView()
{
	m_hDIB = NULL;
	m_hDIBAfter = NULL;
	m_palDIB = NULL;
	m_palDIBAfter = NULL;
}


CDigitalPicProcessingView::~CDigitalPicProcessingView()
{
	if (m_hDIB != NULL)	//判断是否有dib对象
	{
		::GlobalFree(m_hDIB);
	}
	if (m_hDIBAfter != NULL)	//判断是否有图像处理后的dib对象
	{
		::GlobalFree(m_hDIBAfter);
	}

	if (m_palDIB != NULL)	//判断是否有调色板
	{
		delete m_palDIB;
	}
	if (m_palDIBAfter != NULL)	//判断是否有图像处理后的调色板
	{
		delete m_palDIBAfter;
	}
}

BOOL CDigitalPicProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDigitalPicProcessingView 绘制

void CDigitalPicProcessingView::OnDraw(CDC* pDC)
{
	CDigitalPicProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int cxDIB;

	// 判断DIB是否为空
	if (m_hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

		// 获取DIB宽度
		cxDIB = (int)m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB = (int)m_dib.GetHeight(lpDibSection);

		::GlobalUnlock((HGLOBAL)m_hDIB);

		CRect rcDIB(0, 0, cxDIB, cyDIB);

		CRect rcDest = rcDIB;
		// 输出DIB
		m_dib.DrawDib(pDC->m_hDC, &rcDest, m_hDIB, &rcDIB, m_palDIB);
	}

	if (m_hDIBAfter != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIBAfter);

		// 获取DIB宽度
		int cxDIB1 = (int)m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB1 = (int)m_dib.GetHeight(lpDibSection);

		::GlobalUnlock((HGLOBAL)m_hDIBAfter);

		CRect rcDIB(0, 0, cxDIB1, cyDIB1);

		CRect rcDest(cxDIB + 10, 0, cxDIB1, cyDIB1);
		// 输出DIB
		m_dib.DrawDib(pDC->m_hDC, &rcDest, m_hDIBAfter, &rcDIB, m_palDIBAfter);
	}
}


// CDigitalPicProcessingView 打印

BOOL CDigitalPicProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDigitalPicProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDigitalPicProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDigitalPicProcessingView 诊断

#ifdef _DEBUG
void CDigitalPicProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalPicProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalPicProcessingDoc* CDigitalPicProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalPicProcessingDoc)));
	return (CDigitalPicProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

void CDigitalPicProcessingView::SetDib(HGLOBAL hDIB, CPalette *& palDIB)
{
	LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

	if (m_dib.GetWidth(lpdib) > INT_MAX || m_dib.GetHeight(lpdib) > INT_MAX)// 判断图像是否过大
	{
		::GlobalUnlock((HGLOBAL)hDIB);
		::GlobalFree((HGLOBAL)hDIB);	// 释放DIB对象			
		hDIB = NULL;// 设置DIB为空		
		MessageBox(L"图片过大,初始化失败");
		return;
	}
	::GlobalUnlock((HGLOBAL)hDIB);
	palDIB = new CPalette;// 创建新调色板		
	if (palDIB == NULL)// 判断是否创建成功
	{
		::GlobalFree((HGLOBAL)hDIB);	// 失败		
		hDIB = NULL;// 设置DIB对象为空
		return;
	}
	// 调用CreateDIBPalette来创建调色板
	if (m_dib.ConstructPalette(hDIB, palDIB) == NULL)
	{
		delete palDIB;// 删除				
		palDIB = NULL;// 设置为空	
		return;// 返回空
	}
}
// CDigitalPicProcessingView 消息处理程序

void CDigitalPicProcessingView::OnRotate()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;		            //图像每行的字节数
	long	lSrcWidth;                  //图像的宽度
	long	lSrcHeight;					//图像的高度
	LPSTR	lpSrcDib;		            //指向源图像的指针
	LPSTR	lpSrcStartBits;	            //指向原像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的旋转，其它的可以类推）
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
	}

	lpSrcStartBits = m_dib.GetBits(lpSrcDib);					// 找到DIB图像像素起始位置	
	lSrcWidth = m_dib.GetWidth(lpSrcDib);						// 获取图像的宽度		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);						// 获取图像的高度		
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图像每行的字节数

	CDlgRotate rotateDlg;
	if (rotateDlg.DoModal() != IDOK)
		return;

	
	float fRotateAngle = (float)AngleToRadian(rotateDlg.m_rotateAngle);

	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	BeginWaitCursor();

	m_hDIBAfter = (HGLOBAL)RotateDIB2(lpSrcDib, fRotateAngle, lpSrcStartBits, lSrcWidth, lSrcHeight, palSize);

	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));//MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定//::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnTranslation()
{
	//判断图片是否加载
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;						//图像每行的字节数
	long lSrcWidth;							//图像的宽度
	long lSrcHeight;						//图像的高度
	LPSTR lpSrcDib;							//指向源图像的指针
	LPSTR lpSrcStartBits;					//指向原像素的指针
	long lDstLineBytes;						//新图像每行的字节数
	lpSrcDib = (LPSTR) ::GlobalLock(m_hDIB);//锁住DIB
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
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
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnFileOpen()
{
	CFileDialog dlg(true, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		L"所有支持文件(*.bmp)|*.bmp||");
	if (dlg.DoModal() == IDOK)
	{
		//文件完整路径
		CString m_szPathName = dlg.GetPathName();

		CFile file;
		if (!file.Open(m_szPathName, CFile::modeRead |
			CFile::shareDenyWrite))// 打开文件
		{
			MessageBox(L"文件打开失败");
			return;
		}
		if (m_hDIB != NULL)	//判断是否有dib对象
		{
			;; GlobalFree(m_hDIB);
			m_hDIB = NULL;
		}
		if (m_hDIBAfter != NULL)	//判断是否有dib对象
		{
			;; GlobalFree(m_hDIBAfter);
			m_hDIBAfter = NULL;
		}
		if (m_palDIB != NULL)	//判断是否有调色板
		{
			delete m_palDIB;
			m_palDIB = NULL;
		}
		if (m_palDIBAfter != NULL)	//判断是否有调色板
		{
			delete m_palDIBAfter;
			m_palDIBAfter = NULL;
		}
		m_hDIB = m_dib.LoadFile(file);
		if (m_hDIB == NULL)// 调用ReadDIBFile()读取图像
		{
			MessageBox(L"读取图像失败");
			return;
		}
		SetDib(m_hDIB, m_palDIB);// 初始化DIB

		Invalidate();
	}
}


void CDigitalPicProcessingView::OnMirrorH()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;						//图像每行的字节数
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
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
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnMirrorV()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;						//图像每行的字节数
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
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
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnTranspose()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;						//图像每行的字节数
	long lDstLineBytes;
	long lSrcWidth;
	long lSrcHeight;
	LPSTR lpSrcDib;
	LPSTR lpSrcStartBits;
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
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
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnZoom()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long	lSrcLineBytes;	//图像每行的字节数
	long	lSrcWidth;      //图像的宽度
	long	lSrcHeight;		//图像的高度
	LPSTR	lpSrcDib;		//指向源图像的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	long	lDstWidth;      //临时图像的宽度
	long	lDstHeight;		//临时图像的高度
	long	lDstLineBytes;	//临时图像每行的字节数

	lpSrcDib =(LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));                // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);			// 找到DIB图像像素起始位置	
	lSrcWidth = m_dib.GetWidth(lpSrcDib);					// 获取图像的宽度		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);					// 获取图像的高度		
	lSrcLineBytes = m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图像每行的字节数
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);

	CDlgZoom dlg;
	if (dlg.DoModal() != IDOK)
		return;
	float fX = dlg.m_zoomH;// 获取设定的缩放比率
	float fY = dlg.m_zoomV;

	lDstWidth = (long)(lSrcWidth*fX + 0.5);// 计算缩放后的图像实际宽度,加0.5是由于强制类型转换时不四舍五入，而是直接截去小数部分
	lDstLineBytes = m_dib.GetReqByteWidth(lDstWidth * 8);	//转换后图像应有的行字节数，为4的倍数
	lDstHeight = (long)(lSrcHeight * fY + 0.5);// 计算缩放后的图像高度

	BeginWaitCursor();

	m_hDIBAfter = (HGLOBAL)Zoom(lpSrcDib, lpSrcStartBits, lSrcWidth, lSrcHeight,
		lSrcLineBytes, palSize, lDstWidth, lDstLineBytes, lDstHeight, fX, fY);// 调用Zoom()函数转置DIB		

	if (m_hDIBAfter != NULL)// 判断旋转是否成功
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnFourier()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;      //图像的宽度和高度
	long	lSrcHeight;
	LPSTR	lpSrcDib;		//指向源图像的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR)::GlobalLock(m_hDIB);
	if (m_dib.GetColorNum(lpSrcDib) != 256)
	{
		AfxMessageBox(_T("对不起，不是色位图！"));              // 警告
		::GlobalUnlock((HGLOBAL)m_hDIB);						// 解除锁定
		return;													//返回
	}
	BeginWaitCursor();

	lpSrcStartBits = m_dib.GetBits(lpSrcDib);				// 找到DIB图像像素起始位置	
	lSrcWidth =m_dib.GetWidth(lpSrcDib);					// 获取图像的宽度		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);					// 获取图像的高度		
	lSrcLineBytes =m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图像每行的字节数
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);


	double dTmp;					// 临时变量
	long	wid = 1, hei = 1;		// 进行傅立叶变换的宽度和高度，初始化为1		
	int		widpor = 0, heiPor = 0;	//2的幂数	
	unsigned char*	lpSrcUnChr;		//指向像素的指针
	long i;							//行循环变量
	long j;							//列循环变量	
	while (wid < lSrcWidth)// 计算进行傅立叶变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}
	while (hei < lSrcHeight)
	{
		hei *= 2;
		heiPor++;
	}
	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*wid * hei];// 分配内存
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*wid * hei];

	// 初始化
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData
	// 有一部分数据需要补0
	for (i = 0; i < hei; i++)
	{
		for (j = 0; j < wid; j++)
		{
			pTd[i*wid + j].re = 0;
			pTd[i*wid + j].im = 0;
		}
	}
	// 把图像数据传给pCTData
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrcUnChr = (unsigned char*)lpSrcStartBits + lSrcLineBytes*(lSrcHeight - 1 - i) + j;
			pTd[i*wid + j].re = *lpSrcUnChr;//complex<double>(unchValue,0);
			pTd[i*wid + j].im = 0;
		}
	}
	Fourier(pTd, lSrcWidth, lSrcHeight, pFd);

	LPSTR	lpDstDib;		//指向临时图像的指针
	LPSTR	lpDstStartBits;	//指向临时图像对应像素的指针 
	m_hDIBAfter= (HGLOBAL) ::GlobalAlloc(GHND, lSrcLineBytes * lSrcHeight + *(LPDWORD)lpSrcDib + palSize);// 分配内存，以保存新DIB		
	if (m_hDIBAfter == NULL)// 判断是否是有效的DIB对象
	{
		MessageBox(L"分配内存失败");
		return;// 不是，则返回
	}
	lpDstDib = (char *)::GlobalLock((HGLOBAL)m_hDIBAfter);// 锁定内存		
	memcpy(lpDstDib, lpSrcDib, *(LPDWORD)lpSrcDib + palSize);// 复制DIB信息头和调色板		
	lpDstStartBits = lpDstDib + *(LPDWORD)lpDstDib+ palSize;// 求像素起始位置,作用如同::FindDIBBits(gCo.lpSrcDib)，这里尝试使用了这种方法，以避免对全局函数的调用
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			dTmp = pFd[i * wid + j].re* pFd[i * wid + j].re
				+ pFd[i * wid + j].im* pFd[i * wid + j].im;
			dTmp = sqrt(dTmp);

			// 为了显示，需要对幅度的大小进行伸缩
			dTmp /= 100;
			// 限制图像数据的大小
			//			dTmp = min(dTmp, 255) ;
			lpDstStartBits[i*lSrcLineBytes + j] = (unsigned char)(int)dTmp;
		}
	}
	delete pTd;// 释放内存
	delete pFd;
	SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
	Invalidate();
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}


void CDigitalPicProcessingView::OnCosTran()
{
	if (m_hDIB == NULL)
	{
		MessageBox(L"请选择图片");
		return;
	}
	long	lSrcLineBytes;		//图像每行的字节数
	long	lSrcWidth;			//图像的宽度和高度
	long	lSrcHeight;
	LPSTR	lpSrcDib;			//指向源图像的指针	
	LPSTR	lpSrcStartBits;		//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);// 锁定DIB
	if (m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(_T("对不起，不是256色位图！"));// 警告				
		::GlobalUnlock((HGLOBAL)m_hDIB);// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = m_dib.GetBits(lpSrcDib);				// 找到DIB图像像素起始位置	
	lSrcWidth =m_dib.GetWidth(lpSrcDib);					// 获取图像的宽度		
	lSrcHeight = m_dib.GetHeight(lpSrcDib);					// 获取图像的高度		
	lSrcLineBytes =m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图像每行的字节数
	DWORD palSize = m_dib.GetPalSize(lpSrcDib);
	BeginWaitCursor();
	m_hDIBAfter = CosTran(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, palSize, lpSrcDib);
	if (m_hDIBAfter != NULL)
	{
		SetDib(m_hDIBAfter, m_palDIBAfter);				           // 更新DIB大小和调色板		
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("分配内存失败！"));
	}
	::GlobalUnlock((HGLOBAL)m_hDIB);  // 解除锁定
	EndWaitCursor();
}
