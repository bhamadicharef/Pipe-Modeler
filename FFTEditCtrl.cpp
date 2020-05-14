// FftEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "FftEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFftEditCtrl

CFftEditCtrl::CFftEditCtrl()
{
	m_pOldPen = NULL;
	m_penBlack.CreatePen(PS_SOLID, 0,  RGB(0, 0, 0));
	m_penGray.CreatePen(PS_SOLID, 0,  RGB(192, 192, 192));
	m_penWhite.CreatePen(PS_SOLID, 0,  RGB(255, 255, 255));
	m_penRed.CreatePen(PS_SOLID, 0,  RGB(255, 0, 0));

	m_pFont = NULL;
	m_fontScale.CreateFont( -10, 0, 0, 0, 700, 0, 0, 0, 1,
		0, 0, 0, 0, _T("Arial") );
//			0, 0, 0, 0, _T("MS Sans Serif") );

	m_nN = FFT_SIZE_MAX;
	Clear();
}

CFftEditCtrl::~CFftEditCtrl()
{
	if(m_fontScale.m_hObject)
	{
		m_fontScale.Detach();
	}
}

void CFftEditCtrl::Clear()
{
	for(int i = 0; i < FFT_SIZE_MAX; i++)
	{
		m_fData[i] = 0.0;
		m_fOldData[i] = 0.0;
	}
}

void CFftEditCtrl::Noise()
{
	for(int i = 0; i < FFT_SIZE_MAX; i++)
	{
		m_fData[i] = (float)(((float)rand()) / (float)327.68);
	}
}


BEGIN_MESSAGE_MAP(CFftEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CFftEditCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFftEditCtrl message handlers

int CFftEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

BOOL CFftEditCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

//////////////////////////////////////////////////////////////////////////////

void CFftEditCtrl::SetN(int nN)
{
	ASSERT(nN > 0);
	ASSERT(nN <= FFT_SIZE_MAX);
	m_nN = nN;

	Clear();
}

int CFftEditCtrl::GetN()
{
	return m_nN;
}

void CFftEditCtrl::SetData(int nCoef, float fValue)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	m_fData[nCoef] = fValue;
}

float CFftEditCtrl::GetData(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fData[nCoef]);
}

float CFftEditCtrl::GetOldData(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fOldData[nCoef]);
}

//////////////////////////////////////////////////////////////////////////////

void CFftEditCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//TRACE("Paint FftEditCtrl\n");
	EraseOldFFT(&dc);
	DrawAxis(&dc);
	DrawFFT(&dc);
}

void CFftEditCtrl::DrawAxis(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	GetClientRect(m_rcClient);

	// Save old font and select new one
	m_pFont = pDC->SelectObject(&m_fontScale);
	m_pOldPen = pDC->SelectObject(&m_penRed);

	int nHeight = m_rcClient.Height();
	int nWidth = m_rcClient.Width();
	int nX1, nX2, nY1, nY2;

	nX1 = (int)(0.05 * nWidth);
	nX2 = (int)(0.95 * nWidth);
	nY1 = (int)(0.05 * nHeight);
	nY2 = (int)(0.95 * nHeight);

	// Top
	pDC->MoveTo (nX1, nY1);
	pDC->LineTo (nX2, nY1);

	// Bottom
	pDC->MoveTo (nX1, nY2);
	pDC->LineTo (nX2, nY2);

	// Left
	pDC->MoveTo (nX1, nY1);
	pDC->LineTo (nX1, nY2);

	// Right
	pDC->MoveTo (nX2, nY1);
	pDC->LineTo (nX2, nY2);

	pDC->SelectObject(m_pOldPen);
}

void CFftEditCtrl::EraseOldFFT(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int nHeight = m_rcClient.Height();
	int nWidth = m_rcClient.Width();
	int nX1, nX2, nY1, nY2;
	int j;

	nX1 = (int)(0.05 * nWidth);
	nX2 = (int)(0.95 * nWidth);
	nY1 = (int)(0.05 * nHeight);
	nY2 = (int)(0.95 * nHeight);

//	TRACE("Width = %d\n", nX2 - nX1);

	for(int i = 0; i < (nX2 - nX1); i++)
	{
		j = (int)((i * (0.5 * m_nN)) / (nX2 - nX1));
		int nY = (int)((nY2 - nY1)*(m_fOldData[j] / 100));
		pDC->MoveTo(nX1 + i, nY2);
		pDC->LineTo(nX1 + i, nY2 - nY);
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

void CFftEditCtrl::DrawFFT(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penBlack);

	GetClientRect(m_rcClient);
	int nHeight = m_rcClient.Height();
	int nWidth = m_rcClient.Width();
	int nX1, nX2, nY1, nY2;
	int j;

	nX1 = (int)(0.05 * nWidth);
	nX2 = (int)(0.95 * nWidth);
	nY1 = (int)(0.05 * nHeight);
	nY2 = (int)(0.95 * nHeight);

	for(int i = 0; i < (nX2 - nX1); i++)
	{
		j = (int)((i * (0.5 * m_nN)) / (nX2 - nX1));
		int nY = (int)((nY2 - nY1)*(m_fData[j] / 100));
		pDC->MoveTo(nX1 + i, nY2);
		pDC->LineTo(nX1 + i, nY2 - nY);
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);

	//
	int i;
	for(i = 0; i < FFT_SIZE_MAX; i++)
	{
		m_fOldData[i] = m_fData[i];
	}
}

