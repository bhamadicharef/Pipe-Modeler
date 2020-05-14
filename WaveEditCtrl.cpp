// WaveEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "WaveEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveEditCtrl

CWaveEditCtrl::CWaveEditCtrl()
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

	m_nN = WAVE_SIZE_MAX;
	Clear();
}

CWaveEditCtrl::~CWaveEditCtrl()
{
	if(m_fontScale.m_hObject)
	{
		m_fontScale.Detach();
	}
}

void CWaveEditCtrl::Clear()
{
	for(int i = 0; i < m_nN; i++)
	{
		m_fData[i] = 0.0;
		m_fOldData[i] = 0.0;
	}
}

void CWaveEditCtrl::Noise()
{
	for(int i = 0; i < m_nN; i++)
	{
		m_fData[i] = (float) (i / (float) m_nN);
	}
}

BEGIN_MESSAGE_MAP(CWaveEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CWaveEditCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveEditCtrl message handlers

int CWaveEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

BOOL CWaveEditCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

//////////////////////////////////////////////////////////////////////////////

void CWaveEditCtrl::SetN(int nN)
{
	ASSERT(nN > 0);
	ASSERT(nN <= WAVE_SIZE_MAX);
	m_nN = nN;

	Clear();
}

int CWaveEditCtrl::GetN()
{
	return m_nN;
}

void CWaveEditCtrl::SetData(int nCoef, float fValue)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	m_fData[nCoef] = fValue;
}

float CWaveEditCtrl::GetData(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fData[nCoef]);
}

float CWaveEditCtrl::GetOldData(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fOldData[nCoef]);
}

//////////////////////////////////////////////////////////////////////////////

void CWaveEditCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//TRACE("Paint WaveEditCtrl\n");
	EraseOldWave(&dc);
	DrawAxis(&dc);
	DrawWave(&dc);
}

void CWaveEditCtrl::DrawAxis(CPaintDC* pDC)
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

	pDC->SelectObject(m_pOldPen);
	m_pOldPen = pDC->SelectObject(&m_penWhite);

	// Middle
	pDC->MoveTo (nX1, (int)(nHeight * 0.5));
	pDC->LineTo (nX2, (int)(nHeight * 0.5));

	pDC->SelectObject(m_pOldPen);
	m_pOldPen = pDC->SelectObject(&m_penRed);
	
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

void CWaveEditCtrl::EraseOldWave(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int nHeight = m_rcClient.Height();
	int nWidth = m_rcClient.Width();
	int nX1, nX2, nY1, nY2;
	int j1, j2;

	nX1 = (int)(0.05 * nWidth);
	nX2 = (int)(0.95 * nWidth);
	nY1 = (int)(0.05 * nHeight);
	nY2 = (int)(0.95 * nHeight);

//	TRACE("Width = %d\n", nX2 - nX1);

	int nYMid = (nY2 - nY1) / 2;
	for(int i = 1; i < (nX2 - nX1); i++)
	{
		j1 = (int)(((i - 1) * m_nN) / (nX2 - nX1));
		int nZ1 = (int)(2 * nYMid * m_fOldData[j1]);
		j2 = (int)((i * m_nN) / (nX2 - nX1));
		int nZ2 = (int)(2 * nYMid * m_fOldData[j2]);
		// Point Mode
		pDC->MoveTo(nX1 + i - 1, nY1 + nYMid - nZ1);
		pDC->LineTo(nX1 + i, nY1 + nYMid - nZ2);
		// Line
		//pDC->MoveTo(nX1 + i, 1 + nY1 + nYMid);
		//pDC->LineTo(nX1 + i, nY1 + nYMid - nY);
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

void CWaveEditCtrl::DrawWave(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penBlack);

	GetClientRect(m_rcClient);
	int nHeight = m_rcClient.Height();
	int nWidth = m_rcClient.Width();
	int nX1, nX2, nY1, nY2;
	int j1, j2;

	nX1 = (int)(0.05 * nWidth);
	nX2 = (int)(0.95 * nWidth);
	nY1 = (int)(0.05 * nHeight);
	nY2 = (int)(0.95 * nHeight);

	int nYMid = (nY2 - nY1) / 2;
	for(int i = 1; i < (nX2 - nX1); i++)
	{
		j1 = (int)(((i - 1) * m_nN) / (nX2 - nX1));
		int nZ1 = (int)(2 * nYMid * m_fData[j1]);
		j2 = (int)((i * m_nN) / (nX2 - nX1));
		int nZ2 = (int)(2 * nYMid * m_fData[j2]);
		// Point Mode
		pDC->MoveTo(nX1 + i - 1, nY1 + nYMid - nZ1);
		pDC->LineTo(nX1 + i, nY1 + nYMid - nZ2);
		// Line
		//pDC->MoveTo(nX1 + i, 1 + nY1 + nYMid);
		//pDC->LineTo(nX1 + i, nY1 + nYMid - nY);
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);

	//
	for(int i = 0; i < m_nN; i++)
	{
		m_fOldData[i] = m_fData[i];
	}
}

