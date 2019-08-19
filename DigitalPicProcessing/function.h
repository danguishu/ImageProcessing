// function.h: interface for the function class.
//�ӿں�����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
#define AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"
#include <math.h>
// ������
#define pi 3.1415926535
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#include <direct.h>
#include <complex>
using namespace std;
#define PI 3.14159265358979323846

//#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)

typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;


struct CplexNum
{
	double re;
	double im;
};

/////////////////////////////////////////////////////////
//���ڸ�������
CplexNum Add(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re+c2.re;
	c.im=c1.im+c2.im;
	return c;
}
CplexNum Sub(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re-c2.re;
	c.im=c1.im-c2.im;
	return c;
}
CplexNum Mul(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re*c2.re-c1.im*c2.im;
	c.im=c1.re*c2.im+c2.re*c1.im;
	return c;
}

////////////////////////////////////////////////////////
/*************************************************************************
* �������ƣ�AngleToRadian(int angle)
* ��������:
*   int angle
* ��������:float      
* ��������:�����Ƕȵ����ȵ�ת��
************************************************************************/

double AngleToRadian(int angle)
{
	return ((angle)*pi/180.0);
}


/*************************************************************************
* �������ƣ�ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
double *pMainCross, double *pHypoCross)
* ��������:
*   double  *pMatrix ��ָ������ָ��
*   int     rank  ���������
*   double	 *pQMatrix  �� householder�任��ĵľ����ָ��
*   double  *pMainCross ���Գ��������е����Խ�Ԫ�ص�ָ��
*   double  *pHypoCross �� �Գ��������еĴζԽ�Ԫ�ص�ָ��
* ��������:BOOL
*��������:��n��ʵ�Գƾ���Ϊ�Գ�������
************************************************************************/

BOOL  ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
					double *pMainCross, double *pHypoCross)
{	
	int i, j, k, u;//��������
	double h, f, g, h2;   

	for(i = 0; i <= rank-1; i++)// ������pQMatrix��ʼ��
	{
		for(j = 0; j <= rank-1; j++)
		{
			u = i*rank + j; 
			pQMatrix[u] = pMatrix[u];
		}
	}
	for (i = rank-1; i >= 1; i--)
	{
		h = 0.0;
		if (i > 1)
			for (k = 0; k <= i-1; k++)
			{
				u = i*rank + k; 
				h = h + pQMatrix[u]*pQMatrix[u];
			}      

			if (h + 1.0 == 1.0)// ���һ��ȫ��Ϊ��
			{
				pHypoCross[i] = 0.0;
				if (i == 1) 
				{
					pHypoCross[i] = pQMatrix[i*rank+i-1];
				}
				pMainCross[i] = 0.0;
			}        		
			else
			{// ���������������ֵ

				pHypoCross[i] = sqrt(h);// ��ζԽ�Ԫ�ص�ֵ            			
				u = i*rank + i - 1;
				if (pQMatrix[u] > 0.0) // �ж�i��i-1��Ԫ���ǲ��Ǵ�����
				{
					pHypoCross[i] = -pHypoCross[i];
				}            
				h = h - pQMatrix[u]*pHypoCross[i];
				pQMatrix[u] = pQMatrix[u] - pHypoCross[i];
				f = 0.0;            			
				for (j = 0; j <= i-1; j++)// householder�任
				{ 
					pQMatrix[j*rank+i] = pQMatrix[i*rank+j] / h;
					g = 0.0;

					for (k = 0; k <= j; k++)
					{
						g = g + pQMatrix[j*rank+k]*pQMatrix[i*rank+k];
					}                
					if (j+1 <= i-1)
						for (k = j+1; k <= i-1; k++)
				  {
					  g = g + pQMatrix[k*rank+j]*pQMatrix[i*rank+k];
						}                
						pHypoCross[j] = g / h;
						f = f + g*pQMatrix[j*rank+i];
				}

				h2 = f / (h + h);            			
				for (j = 0; j <= i-1; j++)// �����������ֵ
				{
					f = pQMatrix[i*rank + j];
					g = pHypoCross[j] - h2*f;
					pHypoCross[j] = g;

					for (k = 0; k <= j; k++)
					{
						u = j*rank + k;
						pQMatrix[u] = pQMatrix[u] - f*pHypoCross[k] - g*pQMatrix[i*rank + k];
					}
				}
				pMainCross[i] = h;
			}
	}

	for (i = 0; i <= rank-2; i++) // ����ֵ
	{
		pHypoCross[i] = pHypoCross[i + 1];
	}
	pHypoCross[rank - 1] = 0.0;
	pMainCross[0]        = 0.0;    
	for (i = 0; i <= rank-1; i++)
	{ // ���Խ�Ԫ�صļ���		
		if ((pMainCross[i] != 0.0) && (i-1 >= 0))
			for (j = 0; j <= i-1; j++)
			{
				g = 0.0;
				for (k = 0; k <= i-1; k++)
				{g = g + pQMatrix[i*rank + k]*pQMatrix[k*rank + j];
				}
				for (k = 0; k <= i-1; k++)
				{ 
					u = k*rank + j;
					pQMatrix[u] = pQMatrix[u] - g*pQMatrix[k*rank + i];
				}
			}       
			u = i*rank + i;// �洢���Խ��ߵ�Ԫ��
			pMainCross[i] = pQMatrix[u]; 
			pQMatrix[u]   = 1.0;       		
			if (i-1 >= 0)// �����Խ������е�Ԫ�ظ���ֵ
				for (j = 0; j <= i-1; j++)
				{ 
					pQMatrix[i*rank + j] = 0.0; 
					pQMatrix[j*rank+i]   = 0.0;
				}
	}    
	return(TRUE);// ����
}


/*************************************************************************
*
* �������ƣ�EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
double *pMatrix, double Precision, int MaxT)
* ��������:
*   int     rank ������A�Ľ���
*   double	 *pMainCross  ���Գ��������е����Խ�Ԫ�ص�ָ�룬����ʱ���A������ֵ
*   double  *pHypoCross  ���Գ��������еĴζԽ�Ԫ�ص�ָ��
*	 double  *pMatrix  ���Գƾ���A������������ָ��
*   double Precision �����ƾ���
*   int MaxT  �� ����������
* ��������:BOOL 
* ��������:�ü���ʵ�Գ����Ǿ����ȫ������ֵ�Լ���Ӧ����������
************************************************************************/
BOOL EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
					  double *pMatrix, double Precision, int MaxT)
{

	int i, j, k, m, it, u, v;// ��������
	double d, f, h, g, p, r, e, s;

	pHypoCross[rank - 1] = 0.0; // ��ʼ��
	d = 0.0; 
	f = 0.0;

	for(j = 0; j <= rank-1; j++)
	{							//  �������ȵĿ���		
		it = 0;
		h = Precision * (fabs(pMainCross[j]) + fabs(pHypoCross[j]));
		if(h > d) 
		{
			d = h;
		}
		m = j;

		while((m <= rank-1) && (fabs(pHypoCross[m]) > d)) 
		{
			m = m + 1;    
		}
		if(m != j)
		{
			// ���������A������ֵ����������
			do
			{
				// ������������������ʧ��
				if(it == MaxT)
				{
					return(FALSE);
				}
				it = it + 1;
				g = pMainCross[j];
				p = (pMainCross[j + 1] - g) / (2.0 * pHypoCross[j]);
				r = sqrt(p*p + 1.0);                
				// ���p����0
				if (p >= 0.0)
				{
					pMainCross[j] = pHypoCross[j]/(p + r);
				}
				else
				{
					pMainCross[j] = pHypoCross[j]/(p - r); 
				}
				h = g - pMainCross[j];                
				//  �������Խ��ߵ�Ԫ��
				for (i = j + 1; i <= rank - 1; i++)
				{
					pMainCross[i] = pMainCross[i] - h;  
				}
				// ��ֵ
				f = f + h;
				p = pMainCross[m];
				e = 1.0; s = 0.0;

				for(i = m - 1; i >= j; i--)
				{
					g = e * pHypoCross[i];
					h = e * p;

					//  ���Խ���Ԫ�صľ���ֵ�Ƿ���ڴζԽ���Ԫ�ص�
					if(fabs(p) >= fabs(pHypoCross[i]))
					{
						e = pHypoCross[i] / p;
						r = sqrt(e*e + 1.0);
						pHypoCross[i + 1] = s*p*r; 
						s = e / r;  e = 1.0 / r;
					}
					else
					{
						e = p / pHypoCross[i]; 
						r = sqrt(e*e + 1.0);
						pHypoCross[i+1] = s * pHypoCross[i] * r;
						s = 1.0 / r; e = e / r;
					}                   
					p = e*pMainCross[i] - s*g;
					pMainCross[i + 1] = h + s*(e*g + s*pMainCross[i]);

					// ���´洢��������
					for(k = 0; k <= rank - 1; k++)
					{
						u = k*rank + i + 1; v = u - 1;
						h = pMatrix[u]; 
						pMatrix[u] = s*pMatrix[v] + e*h;
						pMatrix[v] = e*pMatrix[v] - s*h;
					}

				}               
				// �����Խ��ߺʹζԽ���Ԫ�����¸�ֵ
				pHypoCross[j] = s * p; 
				pMainCross[j] = e * p;

			}
			while (fabs(pHypoCross[j]) > d);
		}

		pMainCross[j] = pMainCross[j] + f;
	}   	
	for (i = 0; i <= rank-1; i++)
	{// ����A������ֵ
		k = i; p = pMainCross[i];        		
		if(i+1 <= rank-1)
		{// ��A����ֵ����p
			j = i + 1;
			while((j <= rank-1) && (pMainCross[j] <= p))
			{ k = j; 
			p = pMainCross[j]; 
			j = j+1;
			}
		}        		
		if (k != i)
		{// �洢A������ֵ����������
			pMainCross[k] = pMainCross[i];
			pMainCross[i] = p;
			for(j = 0; j <= rank-1; j++)
			{
				u = j*rank + i; 
				v = j*rank + k;
				p = pMatrix[u]; 
				pMatrix[u] = pMatrix[v];
				pMatrix[v] = p;
			}
		}
	}  
	return(TRUE);// ����
}

/*************************************************************************
* �������ƣ�LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
* ��������:
LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
long	lWidth��DIBͼ��Ŀ��
long	lHeight��DIBͼ��ĸ߶�
long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL        
* ��������:�ú���������ͼ����ж����任 
************************************************************************/

BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{			
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{	
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��
			*lpSrcUnChr=50*(unsigned char)log((double)(*lpSrcUnChr+1));
		}
	}
	return TRUE;
}

/*************************************************************************
* �������ƣ�
*   Transpose(LPSTR lpSrcDib,LPSTR lpDibBits,long	lWidth,long	lHeight,
long lLineBytes,long lDstLineBytes)
* ��������:
*   LPSTR	lpSrcDib��ָ��ԴDIB��ָ��
LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
long	lWidth��DIBͼ��Ŀ��
long	lHeight��DIBͼ��ĸ߶�
long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
long	lDstLineBytes����ʱDIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL        
* ��������:�ú�������ת��DIBͼ��
************************************************************************/

BOOL  Transpose(LPSTR lpSrcDib,LPSTR lpSrcStartBits,long lWidth,long lHeight,
				long lLineBytes,long lDstLineBytes)
{
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����
	LPBITMAPINFOHEADER lpbmi;							  // ָ��BITMAPINFOHEADER�ṹ��ָ��
	lpbmi = (LPBITMAPINFOHEADER)lpSrcDib;
	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// ������ʱ�ڴ�
	if (hDstDIBBits== NULL)								 // �ж��Ƿ��ڴ����
	{		
		return FALSE;									// �����ڴ�ʧ��
	}	
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);	// �����ڴ�		
	for(i = 0; i < lHeight; i++)						// ���ͼ��ÿ�н��в���
	{		
		for(j = 0; j < lWidth; j++)						// ���ÿ��ͼ��ÿ�н��в���
		{						
			lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��ԴDIB��i�У���j�����ص�ָ��
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lWidth - 1 - j) + i;// ָ��ת��DIB��j�У���i�����ص�ָ��			
			*(lpDstDIBBits)= *(lpSrcDIBBits);			// ��������			
		}		
	}	
	memcpy(lpSrcStartBits, lpDstStartBits, lWidth * lDstLineBytes);// ����ת�ú��ͼ��
	lpbmi->biWidth = lHeight;		
	lpbmi->biHeight = lWidth;

	LocalUnlock(hDstDIBBits);							// �ͷ��ڴ�
	LocalFree(hDstDIBBits);								
	return TRUE;										// ����
}

/*************************************************************************
* �������ƣ�Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
* ��������:
LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
long	lWidth��DIBͼ��Ŀ��
long	lHeight��DIBͼ��ĸ߶�
long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL        
* ��������:�ú�����������DIBͼ�񣬱�����ֻʵ����ˮƽ���񣬴�ֱ�����ԭ������Ҳ̸���� ������ʵ��           
************************************************************************/

BOOL  Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����
	LPSTR	lpBits;	// ָ���м����ص�ָ�룬������ͼ��ʱ���ṩ��ʱ�������ڴ�ռ�
	hDstDIBBits= LocalAlloc(LHND, lLineBytes);// ������ʱ�ڴ汣����ͼ��
	if (hDstDIBBits == NULL)		
	{		
		return FALSE;									// �����ڴ�ʧ��
	}		
	lpDstDIBBits= (char * )LocalLock(hDstDIBBits);// ����				
	for(i = 0; i < lHeight; i++)// ˮƽ�������ͼ��ÿ�н��в���
	{			
		for(j = 0; j < lWidth / 2; j++)// ���ÿ��ͼ����벿�ֽ��в���
		{							
			lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * i + j;// ָ������i�У���j�����ص�ָ��								
			lpBits= (char *)lpSrcStartBits + lLineBytes * (i + 1) - j;// ָ������i+1�У�������j�����ص�ָ��								
			*lpDstDIBBits=*lpBits;//�����м�����								
			*lpBits = *lpSrcDIBBits;// ��������i�У���j�����ظ��Ƶ�������i�У�������j������								
			*lpSrcDIBBits=*lpDstDIBBits;// ��������i�У�������j�����ظ��Ƶ�������i�У���j������
		}			
	}		
	LocalUnlock(hDstDIBBits);// �ͷ��ڴ�
	LocalFree(hDstDIBBits);
	return TRUE;
}


/*************************************************************************
* �������ƣ�Mirror2(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
* ��������:
LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
long	lWidth��DIBͼ��Ŀ��
long	lHeight��DIBͼ��ĸ߶�
long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL        
* ��������:�ú���������ֱ����DIBͼ��         
************************************************************************/

BOOL  Mirror2(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����
	LPSTR	lpBits;	// ָ���м����ص�ָ�룬������ͼ��ʱ���ṩ��ʱ�������ڴ�ռ�
	hDstDIBBits= LocalAlloc(LHND, lLineBytes);// ������ʱ�ڴ汣����ͼ��
	if (hDstDIBBits == NULL)		
	{		
		return FALSE;									// �����ڴ�ʧ��
	}		
	lpDstDIBBits= (char * )LocalLock(hDstDIBBits);// ����				
	for(i = 0; i < lHeight / 2; i++)// ��ֱ�������ͼ��ÿ�н��в���
	{			
		//for(j = 0; j < lWidth / 2; j++)// ���ÿ��ͼ����벿�ֽ��в���
		//{							
		lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * i ;//+ j;// ָ������i�У���j�����ص�ָ��								
		lpBits= (char *)lpSrcStartBits + lLineBytes * (lHeight - i + 1);// - j;// ָ������i+1�У�������j�����ص�ָ��								
		memcpy(lpDstDIBBits, lpBits, lLineBytes);
		memcpy(lpBits, lpSrcDIBBits, lLineBytes);
		memcpy(lpSrcDIBBits, lpDstDIBBits, lLineBytes);
		//*lpDstDIBBits=*lpBits;//�����м�����								
		//*lpBits = *lpSrcDIBBits;// ��������i�У���j�����ظ��Ƶ�������i�У�������j������								
		//*lpSrcDIBBits=*lpDstDIBBits;// ��������i�У�������j�����ظ��Ƶ�������i�У���j������
		//}			
	}		
	LocalUnlock(hDstDIBBits);// �ͷ��ڴ�
	LocalFree(hDstDIBBits);
	return TRUE;
}

/*************************************************************************
* �������ƣ�Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lXOffset, 
long lYOffset,long lLineBytes,long lDstLineBytes)
* ��������:
*   LPSTR	lpSrcStartBits��ָ��ԴDIB��ʼ���ص�ָ��
* 	 long	lWidth��DIBͼ��Ŀ��
* 	 long	lHeight��DIBͼ��ĸ߶�
* 	 long	lXOffset,X����ƫ����
* 	 long	lYOffset,Y����ƫ����
* 	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
* 	 long	lDstLineBytes����ʱDIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL        
* ��������:�ú�������ƽ��DIBͼ��
************************************************************************/
BOOL  Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, 
				  long lXOffset, long lYOffset,long lLineBytes,long lDstLineBytes)					 
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����

	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// ������ʱ�ڴ�
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);// �����ڴ�	
	if (hDstDIBBits== NULL)// �ж��Ƿ��ڴ����		
		return FALSE;// �����ڴ�ʧ��				
	for(i = 0; i < lHeight; i++)// ��
	{
		for(j = 0; j < lWidth; j++)	// ��
		{
			lpDstDIBBits=(char*)lpDstStartBits+lLineBytes*(lHeight-1-i)
				+j;// ָ����DIB��i�У���j�����ص�ָ��												
			if( (j-lYOffset>= 0) && (j-lYOffset< lWidth) && // ������ԴDIB�е�����j-lXOffset
				(i-lXOffset>= 0) && (i-lXOffset < lHeight))// �ж��Ƿ���Դͼ��Χ��
			{
				lpSrcDIBBits=(char *)lpSrcStartBits+lLineBytes*(lHeight-1-
					(i-lXOffset))+(j-lYOffset);// ָ��ԴDIB��i0�У���j0�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{				
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ��û�е����أ���Ϊ255
			}			
		}
	}
	memcpy(lpSrcStartBits, lpDstStartBits, lLineBytes * lHeight);// ����ͼ��		
	LocalUnlock(hDstDIBBits);// �ͷ��ڴ�
	LocalFree(hDstDIBBits);		
	return TRUE;
}

/*************************************************************************
* �������ƣ�Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
long lLineBytes,	WORD palSize, long lDstWidth, 
long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
* ��������:
*   LPSTR lpSrcDib,ָ��ԴDIB��ָ��
*   LPSTR lpSrcStartBits,ָ��ԴDIB����ʼ���ص�ָ��
*   long lWidth,ԴDIBͼ����
*   long lHeight,ԴDIBͼ��߶�
*	 long lLineBytes,ԴDIBͼ���ֽڿ�ȣ�4�ı�����
*	 WORD palSize,ԴDIBͼ���ɫ���С
*	 long lDstWidth,Ŀ��ͼ����
*	 long lDstHeight,Ŀ��DIBͼ��߶�
*	 long lDstLineBytes,Ŀ��DIBͼ�����ֽ�����4�ı�����
*	 float	fSina,��ת�ǵ����ң�˵����Ϊ�˱���������ȡ�����ң�������Ϊ����������������
*	 float fCosa,��ת�ǵ�����
* ��������:HGLOBAL
* ��������:������תDIBͼ��
************************************************************************/
HGLOBAL  Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				long lLineBytes,	WORD palSize, long lDstWidth, 
				long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
{	
	float varFloat1;        //�����������1
	float varFloat2;        //�����������2
	LPSTR	lpDstDib;		//ָ����ʱͼ���ָ��

	long i;                 //��ѭ������
	long j;                 //��ѭ������
	long i1;                 //��ѭ������
	long j1;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 			

	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFOHEADER�ṹ��ָ��		
	varFloat1= (float) (-0.5 * (lDstWidth - 1) * fCosa - 0.5 * (lDstHeight - 1) * fSina// �������õ���������������������Ա���Ϊ����ʹ��
		+ 0.5 * (lDstWidth  - 1));
	varFloat2= (float) ( 0.5 * (lDstWidth - 1) * fSina - 0.5 * (lDstHeight - 1) * fCosa
		+ 0.5 * (lDstHeight - 1));		
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes * lDstHeight + *(LPDWORD)lpSrcDib +palSize);// �����ڴ棬�Ա�����DIB		
	if (hDIB == NULL)// �ж��Ƿ�����Ч��DIB����
	{		
		return FALSE;// ���ǣ��򷵻�
	}	
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�		
	memcpy(lpDstDib,lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// ����DIB��Ϣͷ�͵�ɫ��			

	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// ��ȡָ��	
	lpbmi->biHeight=lDstHeight;// ����DIB��ͼ��ĸ߶ȺͿ��
	lpbmi->biWidth =lDstWidth;

	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib
		+palSize;// ��������ʼλ��,������ͬ::FindDIBBits(gCo.lpSrcDib)�����ﳢ��ʹ�������ַ������Ա����ȫ�ֺ����ĵ���

	for(i = 0; i < lDstHeight; i++)// �в���
	{		
		for(j = 0; j < lDstWidth; j++)// �в���
		{			
			lpDstDIBBits= (char *)lpDstStartBits+ lDstLineBytes * (lDstHeight - 1 - i) + j;// ָ����DIB��i�У���j�����ص�ָ��			
			i1= (long) (-((float) j) * fSina + ((float) i) * fCosa + varFloat2 + 0.5);// �����������ԴDIB�е�����
			j1= (long) ( ((float) j) * fCosa + ((float) i) * fSina + varFloat1 + 0.5);						
			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// �ж��Ƿ���Դͼ��				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// ָ��ԴDIB��i0�У���j0�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ�в����ڵ����أ���Ϊ255
			}			
		}		
	}
	return hDIB;
}

/*************************************************************************
* �������ƣ�Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
long lLineBytes,	WORD palSize, long lDstWidth, 
long lDstHeight,long lDstLineBytes,float	fXZoomRatio, float fYZoomRatio)
* ��������:
*   LPSTR lpSrcDib,ָ��ԴDIB��ָ��
*   LPSTR lpSrcStartBits,ָ��ԴDIB����ʼ���ص�ָ��
*   long lWidth,ԴDIBͼ����
*   long lHeight,ԴDIBͼ��߶�
*	 long lLineBytes,ԴDIBͼ���ֽڿ�ȣ�4�ı�����
*	 WORD palSize,ԴDIBͼ���ɫ���С
*	 long lDstWidth,Ŀ��ͼ����
*	 long lDstHeight,Ŀ��DIBͼ��߶�
*	 long lDstLineBytes,Ŀ��DIBͼ�����ֽ�����4�ı�����
*	 float	fhorRatio,ˮƽ���ű���
*	 float fverRatio,��ֱ���ű���
* ��������:HGLOBAL
* ��������:��������DIBͼ��
************************************************************************/

HGLOBAL  Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
			  long lLineBytes,	WORD palSize,long lDstWidth,long lDstLineBytes,long lDstHeight,
			  float fhorRatio,float fverRatio)
{			
	LPSTR	lpDstDib;		//ָ����ʱͼ���ָ��	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	long i1;                 //��ѭ������
	long j1;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		

	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFO�ṹ��ָ��

	// �����ڴ棬�Ա������ź��DIB
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes* lDstHeight + *(LPDWORD)lpSrcDib +palSize);	
	if (hDIB == NULL)// �ж��Ƿ�����Ч��DIB����
	{		
		return FALSE;// ���ǣ��򷵻�
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�		
	memcpy(lpDstDib, lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// ����DIB��Ϣͷ�͵�ɫ��		

	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib// �ҵ���DIB������ʼλ��
		+palSize;// ��������ʼλ��,������ͬ::FindDIBBits(lpSrcDib)�����ﳢ��ʹ�������ַ������Ա����ȫ�ֺ����ĵ���		
	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// ��ȡָ��

	lpbmi->biWidth = lDstWidth;// ����DIB��ͼ��ĸ߶ȺͿ��
	lpbmi->biHeight =lDstHeight;	

	for(i = 0; i < lDstHeight; i++)// �в���
	{		
		for(j = 0; j < lDstWidth; j++)// �в���
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lDstHeight-1-i)+j;						
			i1= (long) (i / fverRatio + 0.5);// �����������ԴDIB�е�����
			j1= (long) (j / fhorRatio + 0.5);			

			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// �ж��Ƿ���Դͼ��				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// ָ��ԴDIB��i�У���j�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ�в����ڵ����أ���Ϊ255
			}				
		}		
	}
	return hDIB;
}

/*************************************************************************
* �������ƣ�FastFourierTran(CplexNum * pTd, CplexNum* pFd, int power)
* ��������:
*   CplexNum * pTd,ָ��ʱ�������ָ��
*   CplexNum * pFd,ָ��Ƶ�������ָ��
*   int             power,2������������������
* ��������:void 
��������:����ʵ�ֿ��ٸ���Ҷ�任
************************************************************************/
void  FastFourierTran(CplexNum * pTd, CplexNum * pFd, int power)
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������

	long	dotCount;// ����Ҷ�任����		
	int		k;// ѭ������		
	int		bfsize,p;// �м����		
	double	angle;// �Ƕ�	
	CplexNum *pWn,*temReg1,*temReg2,*temReg;	

	dotCount= 1 <<power;// ���㸶��Ҷ�任����		
	pWn= new CplexNum[sizeof(CplexNum)*dotCount/ 2];// ������������洢��
	temReg1 = new CplexNum[sizeof(CplexNum)*dotCount];
	temReg2 = new CplexNum[sizeof(CplexNum)*dotCount];		
	for(i = 0; i < dotCount/ 2; i++)// �����Ȩϵ��
	{
		angle = -i * pi* 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im=sin(angle);
	}	
	memcpy(temReg1, pTd, sizeof(CplexNum)*dotCount);// ��ʱ���д��temReg1		
	for(k = 0; k < power; k++)// ���õ����㷨���п��ٸ���Ҷ�任
	{
		for(j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (power-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i+p]=Add(temReg1[i+p],temReg1[i+p+bfsize/2]);
				temReg2[i+p+bfsize/2]=Mul(Sub(temReg1[i+p],temReg1[i+p+bfsize/2]),
					pWn[i*(1<<k)]);
			}
		}
		temReg  = temReg1;
		temReg1 = temReg2;
		temReg2 = temReg;
	}		
	for(j = 0; j <dotCount; j++)// ��������
	{
		p = 0;
		for(i = 0; i <power; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(power-i-1);
			}
		}
		pFd[j]=temReg1[p];
	}		
	delete pWn;// �ͷ��ڴ�
	delete temReg1;
	delete temReg2;
}

/*************************************************************************
*
* �������ƣ�InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
* ��������:
*   CplexNum  * pFd��ָ��Ƶ��ֵ��ָ��
*   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
*   int power	��2������
*��������:void
*��������:����ʵ�ֿ��ٸ���Ҷ���任
************************************************************************/
void  InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
{	
	LONG	dotCount;			// ����Ҷ�任����	
	int		i;				// ѭ������
	CplexNum *pX;		
	dotCount= 1 << power;		// ���㸶��Ҷ�任����		
	pX = new CplexNum[sizeof(CplexNum)*dotCount];// ������������洢��		
	memcpy(pX, pFd, sizeof(CplexNum)*dotCount);// ��Ƶ���д��X		
	for(i = 0; i <dotCount; i++)// ����
	{
		pX[i].re= pX[i].re;
		pX[i].im=-pX[i].im;
	}	
	FastFourierTran(pX, pTd, power);// ���ÿ��ٸ���Ҷ�任		
	for(i = 0; i <dotCount; i++)// ��ʱ���Ĺ���
	{
		pTd[i].re =pTd[i].re/dotCount;
		pTd[i].im=-pTd[i].im/dotCount;

	}		
	delete pX;				// �ͷ��ڴ�
}

/*************************************************************************
* �������ƣ�Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
* ��������:
*   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
*   int    lWidth��ͼ����
*   int    lHeight��ͼ��߶�
*   CplexNum * pFd	��ָ��Ƶ��ֵ��ָ��
*
* ��������:void
* ��������:��ά���ٸ���Ҷ�任
*************************************************************************/
void  Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
{

	// ѭ�����Ʊ���
	int	j;
	int	i;
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}	

	for(i = 0; i < hei; i++)
	{
		// x������п��ٸ���Ҷ�任
		FastFourierTran(&pTd[wid * i], &pFd[wid * i], widpor);
	}

	// pFd��Ŀǰ�洢��pTd�����б任�Ľ��
	// Ϊ��ֱ������FastFourierTran����Ҫ��pFd�Ķ�ά����ת�ã���һ������FastFourierTran����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pTd[hei * j + i] = pFd[wid * i + j];
		}
	}

	for(j = 0; j < wid; j++)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		FastFourierTran(&pTd[j * hei], &pFd[j * hei], heiPor);
	}

	// pFd��Ŀǰ�洢��pTd������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pTd[wid * i + j] = pFd[hei * j + i];
		}
	}

	memcpy(pTd, pFd, sizeof(CplexNum) * hei * wid );
}
/*************************************************************************
* �������ƣ�InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
* ��������:
*   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
*   CplexNum * pFd	��ָ��Ƶ��ֵ��ָ��
*   int    lWidth��ͼ����
*   int    lHeight��ͼ��߶�
* ��������:void
* ��������:��ά���ٸ���Ҷ���任
*************************************************************************/
void  InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
{
	// ѭ�����Ʊ���
	int	j;
	int	i;
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	// ���乤����Ҫ���ڴ�ռ�
	CplexNum *pCWork= new CplexNum[sizeof(CplexNum)*wid * hei];

	//��ʱ����
	CplexNum *pCTmp ;

	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pCTmp = &pFd[wid * i + j] ;
			pCWork[wid * i + j].re=pCTmp->re;
			pCWork[wid * i + j].im=-pCTmp->im;
			//= complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// ���ø���Ҷ���任
	Fourier(pCWork, lWidth, lHeight, pTd) ;

	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pCTmp = &pTd[wid * i + j];
			pTd[wid * i + j].re=pCTmp->re/(wid*hei);
			pTd[wid * i + j].im=-pCTmp->im/(wid*hei);			

		}
	}
	delete pCWork ;
}

/*************************************************************************
* �������ƣ�DisFCosTran(double *pTd, double *pFd, int power)
* ��������:
*   double * pTd,ָ��ʱ��ֵ��ָ��
*   double * pFd,ָ��Ƶ��ֵ��ָ��
*   int    power,2������
*
* ��������:void
* ��������: ����ʵ�ֿ�����ɢ���ұ任
************************************************************************/
void  DisFCosTran(double *pTd, double *pFd, int power)
{	
	long i;                 //��ѭ������				
	long	dotCount;// ��ɢ���ұ任����			
	double	dTemp;// ��ʱ����	
	CplexNum *temReg;		
	dotCount = 1<<power;// ������ɢ���ұ任����		
	temReg = new CplexNum[sizeof(CplexNum) *dotCount*2];// �����ڴ�		
	memset(temReg, 0, sizeof(CplexNum) * dotCount * 2);// ��Ϊ0		
	for(i=0;i<dotCount;i++)// ��ʱ���д������temReg
	{
		temReg[i].re=pTd[i];
		temReg[i].im=0;
	}		
	FastFourierTran(temReg,temReg,power+1);// ���ÿ��ٸ���Ҷ�任		
	dTemp = 1/sqrt((double)dotCount);// ����ϵ��		
	pFd[0] = temReg[0].re*dTemp;// ��pFd[0]	
	dTemp *= sqrt(2.0f);		
	for(i = 1; i < dotCount; i++)// ��pFd[u]	
	{
		pFd[i]=(temReg[i].re* cos(i*pi/(dotCount*2)) + temReg[i].im* sin(i*pi/(dotCount*2))) * dTemp;
	}		
	delete temReg;// �ͷ��ڴ�
}

/*************************************************************************
* �������ƣ�CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
* ��������:
*   LPSTR lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
*   long lWidth,DIB�Ŀ��
*   long lHeight,DIB�ĸ߶�
*	 long lLineBytes,DIB�����ֽ�����Ϊ4�ı���
* ��������:BOOL
* ��������: ������ͼ�������ɢ���ұ任
************************************************************************/
BOOL  CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{		
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	long i;                 //��ѭ������
	long j;                 //��ѭ������ 			
	long	wid=1,hei=1;// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���ʼ��Ϊ1
	double	dTemp;// �м����	
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd= new double[wid * hei];// �����ڴ�
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// ��ʱ��ֵ
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		DisFCosTran(&pTd[wid * i], &pFd[wid * i], widpor);// ��y���������ɢ���ұ任
	}		
	for(i = 0; i < hei; i++)// ���������
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		DisFCosTran(&pTd[j * hei], &pFd[j * hei], heiPor);// ��x���������ɢ���ұ任
	}		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{			
			dTemp = fabs(pFd[j*hei+i]);// ����Ƶ��


			if (dTemp > 255)// �Ƿ񳬹�255,�����ģ�ֱ������Ϊ255
			{
				dTemp = 255;
			}			
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete pTd;// �ͷ��ڴ�
	delete pFd;	
	return TRUE;
}

/*************************************************************************
* �������ƣ�Walshei_Har(double *pTd, double *pFd, int power)
* ��������:
*   double * pTd,ָ��ʱ��ֵ��ָ��
*   double * pFd,ָ��Ƶ��ֵ��ָ��
*   int    power,2������
*
* ��������:void
* ��������: ����ʵ�ֿ����ֶ�ʲ-������任
************************************************************************/

void  Walshei_Har(double *pTd, double *pFd, int power)
{	
	long	dotCount;// �ֶ�ʲ-������任����		
	int		i,j,k;// ѭ������	
	int		bfsize,p;// �м����	
	double *temReg1,*temReg2,*temReg;		
	dotCount = 1 << power;// ��������ֶ�ʲ�任����		
	temReg1 = new double[dotCount];// �����������������
	temReg2 = new double[dotCount];
	memcpy(temReg1, pTd, sizeof(double) * dotCount);// ��ʱ���д������temReg1		
	for(k = 0; k < power; k++)// ��������
	{
		for(j = 0; j < 1<<k; j++)
		{
			bfsize = 1 << (power-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i + p] = temReg1[i + p] + temReg1[i + p + bfsize / 2];
				temReg2[i + p + bfsize / 2] = temReg1[i + p] - temReg1[i + p + bfsize / 2];
			}
		}				
		temReg = temReg1;// ����temReg1��temReg2  
		temReg1 = temReg2;
		temReg2 = temReg;
	}	
	for(j = 0; j < dotCount; j++)// ����ϵ��
	{
		p = 0;
		for(i = 0; i < power; i++)
		{
			if (j & (1<<i))
			{
				p += 1 << (power-i-1);
			}
		}
		pFd[j] = temReg1[p] / dotCount;
	}		
	delete temReg1;// �ͷ��ڴ�
	delete temReg2;
}

/*************************************************************************
* �������ƣ�Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
* ��������:
*   LPSTR lpSrcStartBits,ָ��ԴDIBͼ��ָ��
*   long  lWidth,ԴDIBͼ����
*   long  lHeight,ԴDIBͼ��߶�
*   long lLineBytes,ԴDIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL
* ��������:������ͼ������ֶ�ʲ-������任
************************************************************************/

BOOL  Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	long i;                 //��ѭ������
	long j;                 //��ѭ������		

	long	wid=1,hei=1;// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���ʼ��Ϊ1
	double	dTemp;// �м����	
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd = new double[wid * hei];// �����ڴ�
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// ��
	{

		for(j = 0; j < wid; j++)// ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// ��ʱ��ֵ
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		Walshei_Har(pTd + wid * i, pFd + wid * i, widpor);// ��y��������ֶ�ʲ-������任
	}		
	for(i = 0; i < hei; i++)// ���������
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		Walshei_Har(pTd + j * hei, pFd+ j * hei, heiPor);// ��x��������ֶ�ʲ-������任
	}		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{			
			dTemp = fabs(pFd[j * hei + i] * 1000);// ����Ƶ��						
			if (dTemp > 255)// ���ڳ���255�ģ�ֱ������Ϊ255
			{
				dTemp = 255;
			}			
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete pTd;//�ͷ��ڴ�
	delete pFd;
	return TRUE;
}

/*************************************************************************
*
* �������ƣ�
*   DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
*��������:
*   LPSTR lpSrcStartBits,ָ��ԴDIBͼ��ָ��
*   long  lWidth,ԴDIBͼ����
*   long  lHeight,ԴDIBͼ��߶�
*   long lLineBytes,ԴDIBͼ������ֽ�����Ϊ4�ı���
* ��������:BOOL
* ��������:������ͼ�������ת
************************************************************************/

BOOL DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	LONG	i,j,// ѭ������
		lMaxRange,// �����任��ͼ�������ܷ�Χ		
		AverEx,AverEy,//  Ŀ�������ֵ		
		ToaCount;//  Ŀ���ܵ�������	
	double  Matr4C[2][2],// ����ֵ��Э�������
		QMatrix[2][2],// ���Э����������������		
		MainCross[2],HypoCross[2],//  ���Խ�������ԽǺʹζԽ���Ԫ��		
		dTemp;// ��ʱ����
	LONG    lTempI,lTempJ;

	if(lWidth>lHeight)// ����ͼ�񾭹���ת��������Ŀ�Ⱥ͸߶�
	{
		lMaxRange = lWidth;
	}
	else
	{
		lMaxRange =lHeight;
	}

	AverEx=0.0;// ��ʼ��
	AverEy=0.0;
	ToaCount = 0;
	Matr4C[0][0] = Matr4C[0][1] = Matr4C[1][0] = Matr4C[1][1] = 0.0;

	double *F = new double[lWidth*lHeight];// �����ڴ�		
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{			
			F[i*lWidth + j] = 255;// ����ת���������ÿ���㸳��ֵ
			// ָ��λͼi��j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*i + j;

			// ֵС��255���Ǳ���ɫ��ɫ����������ΪĿ���һ����
			// ����������ֵx��y������ά���ʸ��
			if((*lpSrcUnChr) < 255)
			{				

				AverEx=AverEx+i;// ����Ŀ�����ص�Y�����X�����ۼ�ֵ
				AverEy=AverEy+j;				
				ToaCount++;// Ŀ���ܵ���������һ

				// ���ʸ��Э���������ۼ�ֵ
				Matr4C[0][0] = Matr4C[0][0] + i*i;
				Matr4C[0][1] = Matr4C[0][1] + i*j;
				Matr4C[1][0] = Matr4C[1][0] + j*i;
				Matr4C[1][1] = Matr4C[1][1] + j*j;
			}
		}
	}

	AverEx = AverEx/ToaCount;// �������ʸ���ľ�ֵ
	AverEy = AverEy/ToaCount;

	Matr4C[0][0] = Matr4C[0][0]/ToaCount - AverEx*AverEx;//  �������ʸ����Э�������
	Matr4C[0][1] = Matr4C[0][1]/ToaCount - AverEx*AverEy;
	Matr4C[1][0] = Matr4C[1][0]/ToaCount - AverEx*AverEy;
	Matr4C[1][1] = Matr4C[1][1]/ToaCount - AverEy*AverEy;

	double Precision = 0.000001;// �涨�����ļ��㾫��

	ThreeCrossMat(*Matr4C, 2, *QMatrix, MainCross, HypoCross);// ��Э������������ԽǶԳ���		
	EigenvalueVector(2, MainCross,HypoCross, *Matr4C, Precision, 50);// ��Э������������ֵ������ʸ����

	dTemp = Matr4C[0][1];// ������������ת��������������
	Matr4C[0][1] = Matr4C[1][0];
	Matr4C[1][0] = dTemp;

	for(i=0;i<=1;i++)
	{// ���������������й�һ��
		dTemp = pow(Matr4C[i][0],2) + pow(Matr4C[i][1],2);
		dTemp = sqrt(dTemp);
		Matr4C[i][0] = Matr4C[i][0]/dTemp;
		Matr4C[i][1] = Matr4C[i][1]/dTemp;
	}	
	// ���Ҿ���ɢK-L�任����������ԭ����ϵ�е�����    
	for(i = -lMaxRange+1; i < lMaxRange; i++)
	{
		for(j = -lMaxRange+1; j < lMaxRange; j++)
		{
			//  ��������ֵӳ�䵽�ɵ�����ϵ
			int Cx = (int)(i*Matr4C[0][0]-j*Matr4C[0][1])+AverEx;
			int Cy = (int)(-i*Matr4C[1][0]+j*Matr4C[1][1])+AverEy;

			//  ӳ��ֵ�Ƿ�����Դͼ��
			if( Cx>=0 && Cx<lHeight && Cy>=0 && Cy<lWidth )
			{
				lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*Cx + Cy;

				// ӳ��ֵ�Ƿ�����ԭ����Ŀ��
				if(*(lpSrcUnChr)<255)
				{
					//  ��������ϵԭ��ƽ�Ƶ����ģ��Ա���ʾ
					lTempI=(LONG)(lHeight/2)+j;
					lTempJ=(LONG)(lWidth/2)+i;

					// ������ܹ�������ʾ����ֵ�����飬���д洢
					if( lTempI>=0 && lTempI<lHeight && lTempJ>=0 && lTempJ<lWidth )
						F[lTempJ+ (lTempI) * lWidth]=*(lpSrcUnChr);
				}

			}		
		}
	}

	for(i = 0; i < lMaxRange; i++)// ��
	{		
		for(j = 0; j < lMaxRange; j++)// ��
		{			
			dTemp = F[i * lMaxRange + j] ;// ��ɢK-L�任�������ֵ			
			// ָ��λͼi��j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete F;// �ͷ��ڴ�	
	return TRUE;// ����
}





/*************************************************************************
*
* \�������ƣ�
*   FFT_1D()
*
* \�������:
*   complex<double> * pCTData	- ָ��ʱ�����ݵ�ָ�룬�������Ҫ�任������
*   complex<double> * pCFData	- ָ��Ƶ�����ݵ�ָ�룬����ľ����任������
*   nLevel						������Ҷ�任�����㷨�ļ�����2��������
*
* \����ֵ:
*   ��
*
* \˵��:
*   һά���ٸ���Ҷ�任��
*
*************************************************************************
*/
void FFT_1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
	// ѭ�����Ʊ���
	int		i;
	int     j;
	int     k;

	// ����Ҷ�任����
	int	nCount =0 ;

	// ���㸵��Ҷ�任����
	nCount =(int)pow((double)2,(double)nLevel) ;

	// ĳһ���ĳ���
	int		nBtFlyLen;
	nBtFlyLen = 0 ;

	// �任ϵ���ĽǶ� ��2 * PI * i / nCount
	double	dAngle;

	complex<double> *pCW ;

	// �����ڴ棬�洢����Ҷ�仯��Ҫ��ϵ����
	pCW  = new complex<double>[nCount / 2];

	// ���㸵��Ҷ�任��ϵ��
	for(i = 0; i < nCount / 2; i++)
	{
		dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork1,*pCWork2; 

	// ���乤���ռ�
	pCWork1 = new complex<double>[nCount];

	pCWork2 = new complex<double>[nCount];


	// ��ʱ����
	complex<double> *pCTmp;

	// ��ʼ����д������
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// ��ʱ����
	int nInter; 
	nInter = 0;

	// �����㷨���п��ٸ���Ҷ�任
	for(k = 0; k < nLevel; k++)
	{
		for(j = 0; j < (int)pow((double)2,(double)k); j++)
		{
			//���㳤��
			nBtFlyLen = (int)pow( (double)2,(double)(nLevel-k) );

			//�������ţ���Ȩ����
			for(i = 0; i < nBtFlyLen/2; i++)
			{
				nInter = j * nBtFlyLen;
				pCWork2[i + nInter] = 
					pCWork1[i + nInter] + pCWork1[i + nInter + nBtFlyLen / 2];
				pCWork2[i + nInter + nBtFlyLen / 2] =
					(pCWork1[i + nInter] - pCWork1[i + nInter + nBtFlyLen / 2]) 
					* pCW[(int)(i * pow((double)2,(double)k))];
			}
		}

		// ���� pCWork1��pCWork2������
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}

	// ��������
	for(j = 0; j < nCount; j++)
	{
		nInter = 0;
		for(i = 0; i < nLevel; i++)
		{
			if ( j&(1<<i) )
			{
				nInter += 1<<(nLevel-i-1);
			}
		}
		pCFData[j]=pCWork1[nInter];
	}

	// �ͷ��ڴ�ռ�
	delete pCW;
	delete pCWork1;
	delete pCWork2;
	pCW		=	NULL	;
	pCWork1 =	NULL	;
	pCWork2 =	NULL	;

}
/*************************************************************************
*
* \�������ƣ�
*    IFFT_1D()
*
* \�������:
*   complex<double> * pCTData	- ָ��ʱ�����ݵ�ָ�룬�������Ҫ���任������
*   complex<double> * pCFData	- ָ��Ƶ�����ݵ�ָ�룬����ľ������任������
*   nLevel						������Ҷ�任�����㷨�ļ�����2��������
*
* \����ֵ:
*   ��
*
* \˵��:
*   һά���ٸ���Ҷ���任��
*
************************************************************************
*/
void IFFT_1D(complex<double> * pCFData, complex<double> * pCTData, int nLevel)
{

	// ѭ�����Ʊ���
	int		i;

	// ����Ҷ���任����
	int nCount;

	// ���㸵��Ҷ�任����
	nCount = (int)pow((double)2,(double)nLevel) ;

	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork;	

	// ���乤���ռ�
	pCWork = new complex<double>[nCount];

	// ����Ҫ���任������д�빤���ռ�pCWork
	memcpy(pCWork, pCFData, sizeof(complex<double>) * nCount);

	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(i = 0; i < nCount; i++)
	{
		pCWork[i] = complex<double> (pCWork[i].real(), -pCWork[i].imag());
	}

	// ���ÿ��ٸ���Ҷ�任ʵ�ַ��任������洢��pCTData��
	FFT_1D(pCWork, pCTData, nLevel);

	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��nCount
	for(i = 0; i < nCount; i++)
	{
		pCTData[i] = 
			complex<double> (pCTData[i].real() / nCount, -pCTData[i].imag() / nCount);
	}

	// �ͷ��ڴ�
	delete pCWork;
	pCWork = NULL;
}

/*************************************************************************
*
* \�������ƣ�
*   FFT_2D()
*
* \�������:
*   complex<double> * pCTData	- ͼ������
*   int    nWidth				- ���ݿ��
*   int    nHeight				- ���ݸ߶�
*   complex<double> * pCFData	- ����Ҷ�任��Ľ��
*
* \����ֵ:
*   ��
*
* \˵��:
*   ��ά����Ҷ�任��
*
************************************************************************
*/
void FFT_2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{

	// ѭ�����Ʊ���
	int	x;
	int	y;

	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log((double)nWidth)/log((double)2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;

	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log((double)nHeight)/log((double)2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;	

	// x��y�����У������ϵĵ�������
	int		nXLev;
	int		nYLev;

	// ����x��y�����У������ϵĵ�������
	nXLev = (int) ( log((double)nTransWidth)/log((double)2) +  0.5 );
	nYLev = (int) ( log((double)nTransHeight)/log((double)2) + 0.5 );

	for(y = 0; y < nTransHeight; y++)
	{
		// x������п��ٸ���Ҷ�任
		FFT_1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}

	// pCFData��Ŀǰ�洢��pCTData�����б任�Ľ��
	// Ϊ��ֱ������FFT_1D����Ҫ��pCFData�Ķ�ά����ת�ã���һ������FFT_1D����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}

	for(x = 0; x < nTransWidth; x++)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		FFT_1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData��Ŀǰ�洢��pCTData������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransWidth * y + x] = pCFData[nTransHeight * x + y];
		}
	}

	memcpy(pCTData, pCFData, sizeof(complex<double>) * nTransHeight * nTransWidth );
}

/*************************************************************************
*
* \�������ƣ�
*   IFFT_2D()
*
* \�������:
*   complex<double> * pCFData	- Ƶ������
*   complex<double> * pCTData	- ʱ������
*   int    nWidth				- ͼ�����ݿ��
*   int    nHeight				- ͼ�����ݸ߶�
*
* \����ֵ:
*   ��
*
* \˵��:
*   ��ά����Ҷ���任��
*
************************************************************************
*/
void IFFT_2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{
	// ѭ�����Ʊ���
	int	x;
	int	y;

	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;

	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log((double)nWidth)/log((double)2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;

	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log((double)nHeight)/log((double)2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow((double)2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;

	// ���乤����Ҫ���ڴ�ռ�
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];

	//��ʱ����
	complex<double> *pCTmp ;

	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// ���ø���Ҷ���任
	FFT_2D(pCWork, nWidth, nHeight, pCTData) ;

	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCTData[nTransWidth * y + x] ;
			pCTData[nTransWidth * y + x] = 
				complex<double>( pCTmp->real()/(nTransWidth*nTransHeight),
				-pCTmp->imag()/(nTransWidth*nTransHeight) );
		}
	}
	delete pCWork ;
	pCWork = NULL ;
}




/////////////////////////////////////////////////
const double hCoef[10][20] =
{
	{ .707106781187,  .707106781187},

	{ .482962913145,  .836516303738,  .224143868042, -.129409522551 },

	{ .332670552950,  .806891509311,  .459877502118, -.135011020010, -.085441273882,  .035226291882 },

	{ .230377813309,  .714846570553,  .630880767930, -.027983769417,
	-.187034811719,  .030841381836,  .032883011667, -.010597401785 },

	{ .160102397974,  .603829269797,  .724308528438,  .138428145901, -.242294887066,
	-.032244869585,  .077571493840, -.006241490213, -.012580751999,  .003335725285 },

	{ .111540743350,  .494623890398,  .751133908021,  .315250351709, -.226264693965,
	-.129766867567,  .097501605587,  .027522865530, -.031582039318,  .000553842201,
	.004777257511, -.001077301085 },

	{ .077852054085,  .396539319482,  .729132090846,  .469782287405, -.143906003929,
	-.224036184994,  .071309219267,  .080612609151, -.038029936935, -.016574541631,
	.012550998556,  .000429577973, -.001801640704,  .000353713800 },

	{ .054415842243,  .312871590914,  .675630736297,  .585354683654, -.015829105256,
	-.284015542962,  .000472484574,  .128747426620, -.017369301002, -.044088253931,
	.013981027917,  .008746094047, -.004870352993, -.000391740373,  .000675449406,
	-.000117476784 },

	{ .038077947364,  .243834674613,  .604823123690,  .657288078051,  .133197385825,
	-.293273783279, -.096840783223,  .148540749338,  .030725681479, -.067632829061,
	.000250947115,  .022361662124, -.004723204758, -.004281503682,  .001847646883,
	.000230385764, -.000251963189,  .000039347320 },

	{ .026670057901,  .188176800078,  .527201188932,  .688459039454,  .281172343661,
	-.249846424327, -.195946274377,  .127369340336,  .093057364604, -.071394147166,
	-.029457536822,  .033212674059,  .003606553567, -.010733175483,  .001395351747,
	.001992405295, -.000685856695, -.000116466855,  .000093588670, -.000013264203 }
};
/*************************************************************************
*
* \�������ƣ�
*   DWTStep_1D()
*
* \�������:
*   double * pDbSrc		- ָ��Դ���ݵ�ָ��
*   int nCurLevel		- ��ǰ�ֽ�Ĳ���
*   int nInv			- �Ƿ�ΪDWT��1��ʾΪIDWT��0��ʾDWT
*   int nStep			- ��ǰ�ļ������
*   int nSupp			- С�����Ľ�֧���ĳ���
*
* \����ֵ:
*   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
*
* \˵��:
*   �ú����öԴ����pDBSrc�е����ݽ���һ���һάDWT����IDWT�����У�nInvΪ��ʾ����
*   DWT����IDWT�ı�־��nCurLevelΪ��ǰ��Ҫ���зֽ�Ĳ�����nStepΪ�Ѿ��ֽ�Ĳ���
*   ����������Դ����pDbSrc��
*
*************************************************************************
*/
BOOL DWTStep_1D(double* pDbSrc, int nCurLevel,
				int nInv, int nStep,int nSupp)
{
	double s = sqrt((double)2);
	// ���С������ָ��
	double* h = (double*)hCoef[nSupp-1];
	// ȷ�ϵ�ǰ������Ч
	ASSERT(nCurLevel>=0);

	// ���㵱ǰ�����ĳ���
	int CurN = 1<<nCurLevel;
	if (nInv) CurN <<= 1;

	// ȷ����ѡ���С�����͵�ǰ�����ĳ�����Ч
	if (nSupp<1 || nSupp>10 || CurN<2*nSupp) 
		return FALSE;

	// ������ʱ�ڴ����ڴ�Ž��
	double *ptemp = new double[CurN];
	if (!ptemp) return FALSE;

	double	s1, s2;
	int	Index1, Index2;

	// �ж��ǽ���DWT����IDWT
	if (!nInv)
	{	// DWT
		Index1=0;
		Index2=2*nSupp-1;

		// ���о��������s1Ϊ��Ƶ���֣�s2Ϊ��Ƶ���ֵĽ��
		for (int i=0; i<CurN/2; i++)
		{	
			s1 = s2 = 0;
			double t = -1;
			for (int j=0; j<2*nSupp; j++, t=-t)
			{
				s1 += h[j]*pDbSrc[(Index1 & CurN-1) * nStep];
				s2 += t*h[j]*pDbSrc[(Index2 & CurN-1) * nStep];

				Index1++;
				Index2--;
			}

			// ������������ʱ�ڴ���
			ptemp[i] = s1/s;
			ptemp[i+CurN/2] = s2/s;

			Index1 -= 2*nSupp;
			Index2 += 2*nSupp;
			Index1 += 2;
			Index2 += 2;
		}
	}

	// �������IDWT
	else
	{	// IDWT
		Index1 = CurN/2;
		Index2 = CurN/2-nSupp+1;

		// ���о������������s1Ϊ��Ƶ���֣�s2Ϊ��Ƶ���ֵĽ��
		for (int i=0; i<CurN/2; i++)
		{
			s1 = s2 = 0;
			int Index3 = 0;
			for (int j=0; j<nSupp; j++)
			{
				s1 += h[Index3]*pDbSrc[(Index1 & CurN/2-1) * nStep]
				+h[Index3+1]*pDbSrc[((Index2 & CurN/2-1) + CurN/2) * nStep];
				s2 += h[Index3+1]*pDbSrc[(Index1 & CurN/2-1) * nStep]
				-h[Index3]*pDbSrc[((Index2 & CurN/2-1) + CurN/2) * nStep];

				Index3+=2;
				Index1--,		Index2++;
			}

			// �����������ʱ�ڴ�
			ptemp[2*i] = s1*s;
			ptemp[2*i+1] = s2*s;

			Index1 += nSupp;
			Index2 -= nSupp;
			Index1++;
			Index2++;
		}
	}

	// ���������Դͼ����
	for (int i=0; i<CurN; i++)
		pDbSrc[i*nStep] = ptemp[i];

	// �ͷ���ʱ�ڴ棬������
	delete[] ptemp;
	return TRUE;
}

/*************************************************************************
*
* \�������ƣ�
*   DWTStep_2D()
*
* \�������:
*   double * pDbSrc		- ָ��Դ���ݵ�ָ��
*   int nCurWLevel		- X�����ϵ�ǰ�ֽ�Ĳ���
*   int nCurHLevel		- Y�����ϵ�ǰ�ֽ�Ĳ���
*   int nMaxWLevel		- X���������ɷֽ�Ĳ���
*   int nMaxHLevel		- Y���������ɷֽ�Ĳ���
*   int nInv			- �Ƿ�ΪDWT��1��ʾΪIDWT��0��ʾDWT
*   int nStep			- ��ǰ�ļ������
*   int nSupp			- С�����Ľ�֧���ĳ���
*
* \����ֵ:
*   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
*
* \˵��:
*   �ú����öԴ����pDBSrc�е����ݽ���һ��Ķ�άDWT����IDWT��
*   ����������Դ����pDbSrc��
*
*************************************************************************
*/
BOOL DWTStep_2D(double* pDbSrc, int nCurWLevel, int nCurHLevel,
				int nMaxWLevel, int nMaxHLevel, int nInv, int nStep, int nSupp)
{
	// ����ͼ��ĳ��ȺͿ�ȣ�2���ݶ��룩
	int W = 1<<nMaxWLevel, H = 1<<nMaxHLevel;

	// ���㵱ǰ�ֽ��ͼ��ĳ��ȺͿ��
	int CurW = 1<<nCurWLevel, CurH = 1<<nCurHLevel;

	// �ж��ǽ���DWT����IDWT
	if (!nInv)
	{	
		int i = 0;
		// ���н���һάDWT
		for (i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
		// ���н���һάDWT
		for (i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
	}

	// �������IDWT
	else
	{
		// ���㵱ǰ�任��ͼ��ĳ��ȺͿ��
		CurW <<= 1;
		CurH <<= 1;

		int i = 0;
		// ���н���IDWT
		for (i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
		// ���н���IDWT
		for (i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
	}

	// ����
	return TRUE;
}


/*************************************************************************
*
* \�������ƣ�
*   FloatToByte()
*
* \�������:
*   double  f			- ����˫���ȱ���
*
* \����ֵ:
*   BYTE			- ���ر����ͱ���
*
* \˵��:
*   �ú����������˫���ȱ���ת��ΪBYTE�͵ı���
*
*************************************************************************
*/
BYTE FloatToByte(double f)
{
	if (f<=0) return (BYTE)0;
	else if (f>=255) return (BYTE)255;
	else return (BYTE)(f+0.5);
}

/*************************************************************************
*
* \�������ƣ�
*   FloatToChar()
*
* \�������:
*   double  f			- ����˫���ȱ���
*
* \����ֵ:
*   Char			- �����ַ�����
*
* \˵��:
*   �ú����������˫���ȱ���ת��ΪChar�͵ı���
*
*************************************************************************
*/
char FloatToChar(double f)
{
	if (f>=0)
		if (f>=127.0)
			return (char)127;
		else return (char)(f+0.5);
	else
		if (f<=-128)
			return (char)-128;
		else return -(char)(-f+0.5);
}

/*************************************************************************
*
* \�������ƣ�
*   Log2()
*
* \�������:
*   int  n			- �������ͱ���
*
* \����ֵ:
*   int			- ������������Ķ���
*
* \˵��:
*   �ú�����ȡ�����������2Ϊ�׵Ķ�������ת��Ϊ���������
*
*************************************************************************
*/
int Log2(int n)
{
	int rsl = 0;
	while (n >>= 1) rsl++;
	return rsl;
}




BOOL DIBDWTStep(LPSTR lpDIBBits,double*m_pDbImage, int nWidth,int nHeight, int nInv,int m_nDWTCurDepth,int m_nSupp)
{
	// ѭ������
	int i, j;

	// ��ȡ�任��������
	int nMaxWLevel = Log2(nWidth);
	int nMaxHLevel = Log2(nHeight);
	int nMaxLevel;
	if (nWidth == 1<<nMaxWLevel && nHeight == 1<<nMaxHLevel)
		nMaxLevel = min(nMaxWLevel, nMaxHLevel);

	// ��ʱ����
	double	*pDbTemp;
	BYTE	*pBits;

	// ���С���任�Ĵ洢�ڴ滹û�з��䣬�������ڴ�
	if(!m_pDbImage){			
		m_pDbImage = new double[nWidth*nHeight];
		if (!m_pDbImage)	return FALSE;

		// ��ͼ�����ݷ���m_pDbImage�� 
		for (j=0; j<nHeight; j++)
		{
			pDbTemp = m_pDbImage + j*nWidth;
			pBits = (unsigned char *)lpDIBBits + (nHeight-1-j)*nWidth;		
			for (i=0; i<nWidth; i++)
				pDbTemp[i] = pBits[i];
		}
	}

	// ����С���任���򷴱任��
	if (!DWTStep_2D(m_pDbImage, nMaxWLevel-m_nDWTCurDepth, nMaxHLevel-m_nDWTCurDepth,
		nMaxWLevel, nMaxHLevel, nInv, 1, m_nSupp))
		return FALSE;

	// ����Ƿ��任����ǰ������1
	if (nInv)
		m_nDWTCurDepth --;
	// �����1
	else
		m_nDWTCurDepth ++;

	// Ȼ�󣬽����ݿ�����ԭCDib�У���������Ӧ������ת��
	int lfw = nWidth>>m_nDWTCurDepth, lfh = nHeight>>m_nDWTCurDepth;
	for (j=0; j<nHeight; j++)
	{
		pDbTemp = m_pDbImage + j*nWidth;
		pBits = (unsigned char *)lpDIBBits + (nHeight-1-j)*nWidth;
		for (i=0; i<nWidth; i++)
		{
			if (j<lfh && i<lfw)
				pBits[i] = FloatToByte(pDbTemp[i]);
			else
				pBits[i] = BYTE(FloatToChar(pDbTemp[i]) ^ 0x80);			
		}
	}

	// ����
	return TRUE;
}


/*************************************************************************
* �������ƣ�
*   Interpolation()
* ����:
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   FLOAT x			- ��ֵԪ�ص�x����
*   FLOAT y		    - ��ֵԪ�ص�y����
* ����ֵ:
*   unsigned char      - ���ز�ֵ��������
* ˵��:
*   �ú�������˫���Բ�ֵ�㷨����������ֵ�����ڳ���ͼ��Χ�����أ�
* ֱ�ӷ���255��
************************************************************************/
unsigned char Interpolation (LPSTR lpDIBBits, LONG lWidth, 
							 LONG lHeight, FLOAT x, FLOAT y)
{
	// �ĸ����ٽ����ص�����(i1, j1), (i2, j1), (i1, j2), (i2, j2)
	LONG	i1, i2;
	LONG	j1, j2;

	unsigned char	f1, f2, f3, f4;	// �ĸ����ٽ�����ֵ	
	unsigned char	f12, f34;		// ������ֵ�м�ֵ	

	// ����һ��ֵ���������������С�ڸ�ֵʱ��Ϊ������ͬ
	FLOAT			EXP;	

	LONG lLineBytes;				// ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	EXP = (FLOAT) 0.0001;

	// �����ĸ����ٽ����ص�����
	i1 = (LONG) x;
	i2 = i1 + 1;
	j1 = (LONG) y;
	j2 = j1 + 1;

	// ���ݲ�ͬ����ֱ���
	if( (x < 0) || (x > lWidth - 1) || (y < 0) || (y > lHeight - 1))
	{		
		return 255;		// Ҫ����ĵ㲻��Դͼ��Χ�ڣ�ֱ�ӷ���255��
	}
	else
	{
		if (fabs(x - lWidth + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���ұ�Ե��
			if (fabs(y - lHeight + 1) <= EXP)
			{
				// Ҫ����ĵ�������ͼ�������½���һ�����أ�ֱ�ӷ��ظõ�����ֵ
				f1 = *((unsigned char *)lpDIBBits + lLineBytes * 
					(lHeight - 1 - j1) + i1);
				return f1;
			}
			else
			{
				// ��ͼ���ұ�Ե���Ҳ������һ�㣬ֱ��һ�β�ֵ����
				f1 = *((unsigned char *)lpDIBBits + lLineBytes * 
					(lHeight - 1 - j1) + i1);
				f3 = *((unsigned char *)lpDIBBits + lLineBytes * 
					(lHeight - 1 - j1) + i2);

				// ���ز�ֵ���
				return ((unsigned char) (f1 + (y -j1) * (f3 - f1)));
			}
		}
		else if (fabs(y - lHeight + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���±�Ե���Ҳ������һ�㣬ֱ��һ�β�ֵ����
			f1 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
			f2 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i1);

			// ���ز�ֵ���
			return ((unsigned char) (f1 + (x -i1) * (f2 - f1)));
		}
		else
		{
			// �����ĸ����ٽ�����ֵ
			f1 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
			f2 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i1);
			f3 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i2);
			f4 = *((unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i2);

			// ��ֵ1
			f12 = (unsigned char) (f1 + (x - i1) * (f2 - f1));			
			// ��ֵ2
			f34 = (unsigned char) (f3 + (x - i1) * (f4 - f3));			
			// ��ֵ3
			return ((unsigned char) (f12 + (y -j1) * (f34 - f12)));
		}
	}
}	

/////////////////////////////////////////

/*************************************************************************
* �������ƣ�
*   RotateDIB2()
* ����:
*   LPSTR lpDIB		- ָ��ԴDIB��ָ��
*   int iRotateAngle	- ��ת�ĽǶȣ�0-360�ȣ�
* ����ֵ:
*   HGLOBAL            - ��ת�ɹ�������DIB��������򷵻�NULL��
* ˵��:
*   �ú���������ͼ������Ϊ������תDIBͼ�񣬷���������DIB�ľ����
* ���øú������Զ�����ͼ������ʾ���е����ء������в���˫���Բ�
* ֵ�㷨���в�ֵ��
************************************************************************/
HGLOBAL RotateDIB2(LPSTR lpSrcDib, float fRotateAngle,LPSTR lpSrcStartBits,long lWidth, 
				   long lHeight,WORD palSize)
{	
	//LONG	lWidth;				// Դͼ��Ŀ��
	//LONG	lHeight;			// Դͼ��ĸ߶�	
	LONG	lNewWidth;			// ��ת��ͼ��Ŀ��
	LONG	lNewHeight;			// ��ת��ͼ��ĸ߶�
	LONG	lNewLineBytes;		// ��ת��ͼ��Ŀ�ȣ�lNewWidth'��������4�ı�����	
	LPSTR	lpDIBBits;			// ָ��Դͼ���ָ��	
	HGLOBAL	hDIB;				// ��ת����DIB���	
	LPSTR	lpDst;				// ָ����תͼ���Ӧ���ص�ָ��	
	LPSTR	lpNewDIB;			// ָ����תͼ���ָ��
	LPSTR	lpNewDIBBits;	
	LPBITMAPINFOHEADER lpbmi;	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��	
	LPBITMAPCOREHEADER lpbmc;	// ָ��BITMAPCOREINFO�ṹ��ָ��

	LONG	i;					// ѭ����������������DIB�е����꣩
	LONG	j;	
	FLOAT	i0;					// ������ԴDIB�е�����
	FLOAT	j0;	

	//float	fRotateAngle;		// ��ת�Ƕȣ����ȣ�	
	float	fSina, fCosa;		// ��ת�Ƕȵ����Һ�����	
	// Դͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;	
	// ��ת���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	float	f1,f2;


	lpDIBBits = lpSrcStartBits;		// �ҵ�ԴDIBͼ��������ʼλ��	
	//lWidth = DIBWidth(lpDIB);			// ��ȡͼ��Ŀ��
	//lHeight = DIBHeight(lpDIB);			// ��ȡͼ��ĸ߶�

	// ����ת�ǶȴӶ�ת��������
	//float fRotateAngle = (float) AngleToRadian(RotPara.m_rotAngle);

	fSina = (float) sin((double)fRotateAngle);	// ������ת�Ƕȵ�����
	fCosa = (float) cos((double)fRotateAngle);	// ������ת�Ƕȵ�����

	// ����ԭͼ���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fSrcX1 = (float) (- (lWidth  - 1) / 2);
	fSrcY1 = (float) (  (lHeight - 1) / 2);
	fSrcX2 = (float) (  (lWidth  - 1) / 2);
	fSrcY2 = (float) (  (lHeight - 1) / 2);
	fSrcX3 = (float) (- (lWidth  - 1) / 2);
	fSrcY3 = (float) (- (lHeight - 1) / 2);
	fSrcX4 = (float) (  (lWidth  - 1) / 2);
	fSrcY4 = (float) (- (lHeight - 1) / 2);

	// ������ͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// ������ת���ͼ��ʵ�ʿ��
	lNewWidth  = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);

	// ������ת���ͼ��߶�
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// �����ڴ棬�Ա�����DIB
	hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + 
		*(LPDWORD)lpSrcDib + palSize);	
	if (hDIB == NULL)
	{
		return NULL;
	}

	lpNewDIB =  (char * )::GlobalLock((HGLOBAL) hDIB);

	// ����DIB��Ϣͷ�͵�ɫ��
	memcpy(lpNewDIB, lpSrcDib, *(LPDWORD)lpSrcDib + palSize);

	// �ҵ���DIB������ʼλ��
	lpNewDIBBits = lpNewDIB+ *(LPDWORD)lpNewDIB +palSize;;//FindDIBBits(lpNewDIB);
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	/*
	// ����DIB��ͼ��ĸ߶ȺͿ��
		if (IS_WIN30_DIB(lpNewDIB))
		{
			// ����Windows 3.0 DIB
			lpbmi->biWidth = lNewWidth;
			lpbmi->biHeight = lNewHeight;
		}
		else
		{
			// ����������ʽ��DIB
			lpbmc->bcWidth = (unsigned short) lNewWidth;
			lpbmc->bcHeight = (unsigned short) lNewHeight;
		}*/

	lpbmi->biWidth = lNewWidth;
	lpbmi->biHeight = lNewHeight;
	

	for(i = 0; i < lNewHeight; i++)		// ���ͼ��ÿ�н��в���
	{			
		for(j = 0; j < lNewWidth; j++)	// ���ͼ��ÿ�н��в���
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע��˴���Ⱥ͸߶�����DIB�Ŀ�Ⱥ͸߶�
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// �����������ԴDIB�е�����
			i0 = -((float) j) * fSina + ((float) i) * fCosa + f2;
			j0 =  ((float) j) * fCosa + ((float) i) * fSina + f1;

			// ����˫���Բ�ֵ�㷨����������ֵ
			*lpDst = Interpolation (lpDIBBits, lWidth, lHeight, j0, i0);			
		}		
	}

	return hDIB;
}









#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
