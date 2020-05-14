// PipeEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "PipeEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipeEditCtrl

CPipeEditCtrl::CPipeEditCtrl()
{
	int i;

	m_pOldPen = NULL;
	m_penBlack.CreatePen(PS_SOLID, 0,  RGB(0, 0, 0));
	m_penGray.CreatePen(PS_SOLID, 0,  RGB(192, 192, 192));
	m_penWhite.CreatePen(PS_SOLID, 0,  RGB(255, 255, 255));

	m_pFont = NULL;
	m_fontScale.CreateFont( -10, 0, 0, 0, 700, 0, 0, 0, 1,
		0, 0, 0, 0, _T("Arial") );
//			0, 0, 0, 0, _T("MS Sans Serif") );

/*
	m_pTube1 = NULL;
	m_pTube2 = NULL;
	m_pJunction = NULL;
*/

	for(i = 0; i < NB_TUBES; i++)
	{
		m_fLength[i] = (MY_FLOAT) 0.25;
		m_fOldLength[i] = m_fLength[i];
		m_fDiameter[i] = (MY_FLOAT) 1.0;
		m_fOldDiameter[i] = m_fDiameter[i];
	}
	
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_fDiameterBore[i] = (MY_FLOAT) 0.75;
		m_fOldDiameterBore[i] = m_fDiameterBore[i];
		m_fDiameterToneHole[i] = (MY_FLOAT) 0.75;
		m_fOldDiameterToneHole[i] = m_fDiameterToneHole[i];
	}
}

CPipeEditCtrl::~CPipeEditCtrl()
{
	if(m_fontScale.m_hObject)
	{
		m_fontScale.Detach();
	}
}

BEGIN_MESSAGE_MAP(CPipeEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CPipeEditCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPipeEditCtrl message handlers

int CPipeEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

BOOL CPipeEditCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

//////////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//TRACE("Paint PipeEditCtrl\n");

	EraseOldPipeShapeToneHole(&dc);
	DrawAxis(&dc);
	DrawPipeShapeToneHole(&dc);
/*
	EraseOldPipeShape(&dc);
	DrawAxis(&dc);
	DrawPipeShape(&dc);
*/
}

/////////////////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl::DrawAxis(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penWhite);

	CRect rcClient;
	GetClientRect(m_rcClient);

	// Save old font and select new one
	m_pFont = pDC->SelectObject(&m_fontScale);

	// Central Axis
	int YAxis = (int) (0.5 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);
	// Top Axis ()
	YAxis = (int) (0.1 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);
	// Bottom Axis ()
	YAxis = (int) (0.9 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);

	// Central Axis
	int XAxis = (int) (0.5 * m_rcClient.Width());
	pDC->MoveTo (XAxis, m_rcClient.top);
	pDC->LineTo (XAxis, m_rcClient.bottom);
	// Top Axis ()
	XAxis = (int) (0.1 * m_rcClient.Width());
	pDC->MoveTo (XAxis, m_rcClient.top);
	pDC->LineTo (XAxis, m_rcClient.bottom);
	// Bottom Axis ()
	XAxis = (int) (0.9 * m_rcClient.Width());
	pDC->MoveTo (XAxis, m_rcClient.top);
	pDC->LineTo (XAxis, m_rcClient.bottom);

	pDC->SelectObject(m_pOldPen);
}

//////////////////////////////////////////////////////////

void CPipeEditCtrl::EraseOldPipeShape(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
/*
	ASSERT(m_pTube1 != NULL);
	ASSERT(m_pTube2 != NULL);
	ASSERT(m_pJunction != NULL);
*/
	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int nXMiddle = m_rcClient.Width() / 2;
	int nYMiddle = m_rcClient.Height() / 2;
	int nYTop = (int)(0.1 * m_rcClient.Height());

	int nDiameter;
	int nLength;

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 1
	nDiameter = (int)(m_fOldDiameter[0] * 2.0 * 0.8 * nYMiddle);
	nLength = (int)(m_fOldLength[0] * 0.8 * nXMiddle);

	// Upper part of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle - nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXMiddle, nYTop + nDiameter);
	pDC->LineTo(nXMiddle - nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube1
	pDC->MoveTo(nXMiddle - nLength, nYTop);
	pDC->LineTo(nXMiddle - nLength, nYTop + nDiameter);

	// Right Vertical Line of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle, nYTop + nDiameter);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 2
	nDiameter = (int)(m_fOldDiameter[1] * 2.0 * 0.8 * nYMiddle);
	nLength = (int)(m_fOldLength[1] * 0.8 * nXMiddle);

	// Upper part of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle + nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXMiddle, nYTop + nDiameter);
	pDC->LineTo(nXMiddle + nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube1
	pDC->MoveTo(nXMiddle + nLength, nYTop);
	pDC->LineTo(nXMiddle + nLength, nYTop + nDiameter);

	// Right Vertical Line of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle, nYTop + nDiameter);

	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

void CPipeEditCtrl::DrawPipeShape(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	int i;
/*
	ASSERT(m_pTube1 != NULL);
	ASSERT(m_pTube2 != NULL);
	ASSERT(m_pJunction != NULL);
*/
	m_pOldPen = pDC->SelectObject(&m_penBlack);

	GetClientRect(m_rcClient);
	int nXMiddle = m_rcClient.Width() / 2;
	int nYMiddle = m_rcClient.Height() / 2;
	int nYTop = (int)(0.1 * m_rcClient.Height());

	int nDiameter;
	int nLength;

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 1
	nDiameter = (int)(m_fDiameter[0] * 2.0 * 0.8 * nYMiddle);
	nLength = (int)(m_fLength[0] * 0.8 * nXMiddle);

	// Upper part of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle - nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXMiddle, nYTop + nDiameter);
	pDC->LineTo(nXMiddle - nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube1
	pDC->MoveTo(nXMiddle - nLength, nYTop);
	pDC->LineTo(nXMiddle - nLength, nYTop + nDiameter);

	// Right Vertical Line of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle, nYTop + nDiameter);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 2
	nDiameter = (int)(m_fDiameter[1] * 2.0 * 0.8 * nYMiddle);
	nLength = (int)(m_fLength[1] * 0.8 * nXMiddle);

	// Upper part of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle + nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXMiddle, nYTop + nDiameter);
	pDC->LineTo(nXMiddle + nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube1
	pDC->MoveTo(nXMiddle + nLength, nYTop);
	pDC->LineTo(nXMiddle + nLength, nYTop + nDiameter);

	// Right Vertical Line of Tube1
	pDC->MoveTo(nXMiddle, nYTop);
	pDC->LineTo(nXMiddle, nYTop + nDiameter);
	
	// Restore original pen
	pDC->SelectObject(m_pOldPen);

	//
	for(i = 0; i < NB_TUBES; i++)
	{
		m_fOldLength[i] = m_fLength[i];
		m_fOldDiameter[i] = m_fDiameter[i];
	}
	
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_fOldDiameterBore[i] = m_fDiameterBore[i];
		m_fOldDiameterToneHole[i] = m_fDiameterToneHole[i];
	}
}

/////////////////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl::EraseOldPipeShapeToneHole(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	int nDiameter;
	int nLength;
	int nDiameterToneHole;

	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int nXLeft = (int)(0.1 * m_rcClient.Width());
	int nYTop = (int)(0.1 * m_rcClient.Height());

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 
	nDiameter = (int)(m_fOldDiameterBore[0] * 0.8 * m_rcClient.Height());
	nLength = (int)(((	m_fOldLength[0] + m_fOldLength[1] + m_fOldLength[2] +
						m_fOldLength[3]) /4) * 0.8 * m_rcClient.Width());

	// Upper part of Tube
	pDC->MoveTo(nXLeft, nYTop);
	pDC->LineTo(nXLeft + nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXLeft, nYTop + nDiameter);
	pDC->LineTo(nXLeft + nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube1
	pDC->MoveTo(nXLeft, nYTop);
	pDC->LineTo(nXLeft, nYTop + nDiameter);

	// Right Vertical Line of Tube
	pDC->MoveTo(nXLeft + nLength, nYTop);
	pDC->LineTo(nXLeft + nLength, nYTop + nDiameter);

	////////////////////////////////////////////////////////////////////////////////////
	// Draw the ToneHole1
	nLength = (int)(m_fOldLength[0] * 0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fOldDiameterToneHole[0]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Draw the ToneHole
	nLength = (int)((	m_fOldLength[0] + m_fOldLength[1]) *
						0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fOldDiameterToneHole[1]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Draw the ToneHole
	nLength = (int)((	m_fOldLength[0] + m_fOldLength[1] + m_fOldLength[2]) *
						0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fOldDiameterToneHole[2]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl::DrawPipeShapeToneHole(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	int nDiameter;
	int nLength;
	int nDiameterToneHole;
	int i;

	m_pOldPen = pDC->SelectObject(&m_penBlack);

	GetClientRect(m_rcClient);
	int nXLeft = (int)(0.1 * m_rcClient.Width());
	int nYTop = (int)(0.1 * m_rcClient.Height());

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 1
	nDiameter = (int)(m_fDiameterBore[0] * 0.8 * m_rcClient.Height());
	nLength = (int)(((m_fLength[0] + m_fLength[1] + m_fLength[2] + m_fLength[3]) /4) * 0.8 * m_rcClient.Width());

	// Upper part of Tube
	pDC->MoveTo(nXLeft, nYTop);
	pDC->LineTo(nXLeft + nLength, nYTop);

	// Lower part of Tube1
	pDC->MoveTo(nXLeft, nYTop + nDiameter);
	pDC->LineTo(nXLeft + nLength, nYTop + nDiameter);

	// Left Vertical Line of Tube
	pDC->MoveTo(nXLeft, nYTop);
	pDC->LineTo(nXLeft, nYTop + nDiameter);

	// Right Vertical Line of Tube
	pDC->MoveTo(nXLeft + nLength, nYTop);
	pDC->LineTo(nXLeft + nLength, nYTop + nDiameter);

	////////////////////////////////////////////////////////////////////////////////////
	// Draw the ToneHole
	nLength = (int)(m_fLength[0] * 0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fDiameterToneHole[0]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Draw the ToneHole
	nLength = (int)((	m_fLength[0] + m_fLength[1]) *
						0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fDiameterToneHole[1]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Draw the ToneHole
	nLength = (int)((	m_fLength[0] + m_fLength[1] + m_fLength[2]) *
						0.25 * 0.8 * m_rcClient.Width());
	nDiameterToneHole = (int)(20 * m_fDiameterToneHole[2]);
	pDC->Arc(	nXLeft + nLength - nDiameterToneHole, nYTop - nDiameterToneHole,
				nXLeft + nLength + nDiameterToneHole, nYTop + nDiameterToneHole,
				nXLeft + nLength - nDiameterToneHole, nYTop,
				nXLeft + nLength + nDiameterToneHole, nYTop);

	// Restore original pen
	pDC->SelectObject(m_pOldPen);

	//
	for(i = 0; i < NB_TUBES; i++)
	{
		m_fOldLength[i] = m_fLength[i];
		m_fOldDiameter[i] = m_fDiameter[i];
	}
	
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_fOldDiameterBore[i] = m_fDiameterBore[i];
		m_fOldDiameterToneHole[i] = m_fDiameterToneHole[i];
	}
}

//////////////////////////////////////////////////////////

void CPipeEditCtrl::SetLength(int nWhichTube, MY_FLOAT fLength)
{
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	ASSERT(fLength >= 0.0);
	ASSERT(fLength <= 1.0);
	m_fLength[nWhichTube] = fLength;
}

void CPipeEditCtrl::SetDiameter(int nWhichTube, MY_FLOAT fDiameter)
{
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	ASSERT(fDiameter >= 0.0);
	ASSERT(fDiameter <= 1.0);
	m_fDiameter[nWhichTube] = fDiameter;
}

void CPipeEditCtrl::SetDiameterBore(int nWhichToneHoleJunc, MY_FLOAT fDiameterBore)
{
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	ASSERT(fDiameterBore >= 0.0);
	ASSERT(fDiameterBore <= 1.0);
	m_fDiameterBore[nWhichToneHoleJunc] = fDiameterBore;
}

void CPipeEditCtrl::SetDiameterToneHole(int nWhichToneHoleJunc, MY_FLOAT fDiameterToneHole)
{
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	ASSERT(fDiameterToneHole >= 0.0);
	ASSERT(fDiameterToneHole <= 1.0);
	m_fDiameterToneHole[nWhichToneHoleJunc] = fDiameterToneHole;
}

/////////////////////////////////////////////////////////////////////////////


