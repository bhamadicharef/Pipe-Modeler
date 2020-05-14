// CurveEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "CurveEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveEditCtrl

CCurveEditCtrl::CCurveEditCtrl()
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

	m_pPolynomial = NULL;
}

CCurveEditCtrl::~CCurveEditCtrl()
{
	if(m_fontScale.m_hObject)
	{
		m_fontScale.Detach();
	}
}

BEGIN_MESSAGE_MAP(CCurveEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CCurveEditCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveEditCtrl message handlers

int CCurveEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

BOOL CCurveEditCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

void CCurveEditCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//TRACE("Paint CurveEditCtrl\n");
	EraseOldCurveShape(&dc);
	DrawAxis(&dc);
	DrawCurveShape(&dc);
}

void CCurveEditCtrl::DrawAxis(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	GetClientRect(m_rcClient);

	// Save old font and select new one
	m_pFont = pDC->SelectObject(&m_fontScale);
	m_pOldPen = pDC->SelectObject(&m_penRed);

	int nHeight = (int) (0.5 * m_rcClient.Height());
	int nWidth = (int) (0.5 * m_rcClient.Width());
	int YAxis = nHeight;
	int XAxis = nWidth;

	// Horizontal Central Axis
	pDC->MoveTo (XAxis - 100, YAxis);
	pDC->LineTo (XAxis + 100, YAxis);
	// Vertical Central Axis
	pDC->MoveTo (XAxis, YAxis - 100);
	pDC->LineTo (XAxis, YAxis + 100);

	pDC->SelectObject(m_pOldPen);
	m_pOldPen = pDC->SelectObject(&m_penWhite);
	
	// Top Axis ()
	YAxis = nHeight - 100;
	pDC->MoveTo (XAxis - 100, YAxis);
	pDC->LineTo (XAxis + 100, YAxis);
	// Bottom Axis ()
	YAxis = nHeight + 100;
	pDC->MoveTo (XAxis - 100, YAxis);
	pDC->LineTo (XAxis + 100, YAxis);
	// Top Axis ()
	YAxis = nHeight - 50;
	pDC->MoveTo (XAxis - 100, YAxis);
	pDC->LineTo (XAxis + 100, YAxis);
	// Bottom Axis ()
	YAxis = nHeight + 50;
	pDC->MoveTo (XAxis - 100, YAxis);
	pDC->LineTo (XAxis + 100, YAxis);

	YAxis = nHeight;
	// Top Axis ()
	XAxis = nWidth - 100;
	pDC->MoveTo (XAxis, YAxis - 100);
	pDC->LineTo (XAxis, YAxis + 100);
	// Bottom Axis ()
	XAxis = nWidth + 100;
	pDC->MoveTo (XAxis, YAxis - 100);
	pDC->LineTo (XAxis, YAxis + 100);
	// Top Axis ()
	XAxis = nWidth - 50;
	pDC->MoveTo (XAxis, YAxis - 100);
	pDC->LineTo (XAxis, YAxis + 100);
	// Bottom Axis ()
	XAxis = nWidth + 50;
	pDC->MoveTo (XAxis, YAxis - 100);
	pDC->LineTo (XAxis, YAxis + 100);

	pDC->SelectObject(m_pOldPen);
}

void CCurveEditCtrl::EraseOldCurveShape(CPaintDC* pDC)
{
	ASSERT_VALID(m_pPolynomial);
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int XAxis = (int) (0.5 * m_rcClient.Width());
	int YAxis = (int) (0.5 * m_rcClient.Height());

	ASSERT(m_rcClient.Height() >= 200);
	ASSERT(m_rcClient.Width() >= 200);

	int x1, y1, x2, y2;
	float fValue1, fResult1;
	float fValue2, fResult2;

	for(int i = -100; i < 100; i++)
	{
		fValue1 = ((float)(i) / (float)(100.0));
		fResult1 = m_pPolynomial->TickOld(fValue1);
		
		fValue2 = (float)((float)(i+1) / (float)(100.0));
		fResult2 = m_pPolynomial->TickOld(fValue2);

		x1 = XAxis + i;
		x2 = XAxis + i + 1;
		y1 = YAxis - (int)(100.0 * fResult1);
		y2 = YAxis - (int)(100.0 * fResult2);

		if((x1 >= (XAxis - 100)) && ((x2 >= XAxis - 100)))
		{
			if((x1 <= (XAxis + 100)) && ((x2 <= (XAxis + 100))))
			{
				if((y1 >= (YAxis - 100)) && (y2 >= (YAxis - 100)))
				{
					if((y1 <= (YAxis + 100)) && ((y2 <= (YAxis + 100))))
					{
						pDC->MoveTo(x1, y1);
						pDC->LineTo(x2, y2);
					}
				}
			}
		}
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

void CCurveEditCtrl::DrawCurveShape(CPaintDC* pDC)
{
	ASSERT_VALID(m_pPolynomial);
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penBlack);
	GetClientRect(m_rcClient);
	int XAxis = (int) (0.5 * m_rcClient.Width());
	int YAxis = (int) (0.5 * m_rcClient.Height());

	ASSERT(m_rcClient.Height() >= 200);
	ASSERT(m_rcClient.Width() >= 200);

	int x1, y1, x2, y2;
	float fValue1, fResult1;
	float fValue2, fResult2;

	for(int i = -100; i < 100; i++)
	{
		fValue1 = ((float)(i) / (float)(100.0));
		fResult1 = m_pPolynomial->Tick(fValue1);
		
		fValue2 = (float)((float)(i+1) / (float)(100.0));
		fResult2 = m_pPolynomial->Tick(fValue2);

		x1 = XAxis + i;
		x2 = XAxis + i + 1;
		y1 = YAxis - (int)(100.0 * fResult1);
		y2 = YAxis - (int)(100.0 * fResult2);

		if((x1 >= (XAxis - 100)) && ((x2 >= XAxis - 100)))
		{
			if((x1 <= (XAxis + 100)) && ((x2 <= (XAxis + 100))))
			{
				if((y1 >= (YAxis - 100)) && (y2 >= (YAxis - 100)))
				{
					if((y1 <= (YAxis + 100)) && ((y2 <= (YAxis + 100))))
					{
						pDC->MoveTo(x1, y1);
						pDC->LineTo(x2, y2);
					}
				}
			}
		}
	}

	// Restore original pen
	pDC->SelectObject(m_pOldPen);

	//
	for(int i = 0; i < m_pPolynomial->GetN(); i++)
	{
		m_pPolynomial->SetOldCoef(i, m_pPolynomial->GetCoef(i));
	}
}

