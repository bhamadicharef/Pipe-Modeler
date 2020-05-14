// PipeEditCtrl2.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "PipeEditCtrl2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPipeEditCtrl2

CPipeEditCtrl2::CPipeEditCtrl2()
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

CPipeEditCtrl2::~CPipeEditCtrl2()
{
	if(m_fontScale.m_hObject)
	{
		m_fontScale.Detach();
	}
}

BEGIN_MESSAGE_MAP(CPipeEditCtrl2, CWnd)
	//{{AFX_MSG_MAP(CPipeEditCtrl2)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPipeEditCtrl2 message handlers

int CPipeEditCtrl2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

BOOL CPipeEditCtrl2::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pContext = NULL;

	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

//////////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//TRACE("Paint PipeEditCtrl2\n");

	EraseOldPipeShapeToneHole(&dc);
	DrawAxis(&dc);
	DrawPipeShapeToneHole(&dc);
}

/////////////////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl2::DrawAxis(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	m_pOldPen = pDC->SelectObject(&m_penWhite);

	CRect rcClient;
	GetClientRect(m_rcClient);

	// Save old font and select new one
	m_pFont = pDC->SelectObject(&m_fontScale);

	int XAxis;
	int YAxis;

/*	// Central Axis
	YAxis = (int) (0.5 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);
*/	// Top Axis ()
	YAxis = (int) (0.1 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);
	// Bottom Axis ()
	YAxis = (int) (0.9 * m_rcClient.Height());
	pDC->MoveTo (m_rcClient.left, YAxis);
	pDC->LineTo (m_rcClient.right, YAxis);

	// Central Axis
	XAxis = (int) (0.5 * m_rcClient.Width());
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
void CPipeEditCtrl2::EraseOldPipeShapeToneHole(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	int nRadiusLow, nRadiusHigh;
	int nHeight;
//	int nDiameterToneHole;
//	int i;

	m_pOldPen = pDC->SelectObject(&m_penGray);

	GetClientRect(m_rcClient);
	int nXMiddle = (int)(0.5 * m_rcClient.Width());
	int nYLowRef = (int)(0.9 * m_rcClient.Height());

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 1
	nRadiusLow = (int)(0.5 * m_fOldDiameterBore[0] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fOldDiameterBore[1] * 0.8 * m_rcClient.Width());
	nHeight = (int)(m_fOldLength[0] * LENGTH0_RATIO * m_rcClient.Height());

	// Upper part of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 1
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 2
	nRadiusLow = (int)(0.5 * m_fOldDiameterBore[1] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fOldDiameterBore[2] * 0.8 * m_rcClient.Width());
	nYLowRef =	(int)(0.9 * m_rcClient.Height()) -
				(int)(m_fOldLength[0] * LENGTH0_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fOldLength[1] * LENGTH1_RATIO * m_rcClient.Height());

	// Upper part of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 2
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 3
	nRadiusLow = (int)(0.5 * m_fOldDiameterBore[2] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fOldDiameterBore[3] * 0.8 * m_rcClient.Width());
	nYLowRef =	(int)(0.9 * m_rcClient.Height()) -
				(int)(m_fOldLength[0] * LENGTH0_RATIO * m_rcClient.Height()) -
				(int)(m_fOldLength[1] * LENGTH1_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fOldLength[2] * LENGTH2_RATIO * m_rcClient.Height());

	// Upper part of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 3
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 4
	nRadiusLow = (int)(0.5 * m_fOldDiameterBore[3] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fOldDiameterBore[4] * 0.8 * m_rcClient.Width());
	nYLowRef =	(int)(0.9 * m_rcClient.Height()) -
				(int)(m_fOldLength[0] * LENGTH0_RATIO * m_rcClient.Height()) -
				(int)(m_fOldLength[1] * LENGTH1_RATIO * m_rcClient.Height()) -
				(int)(m_fOldLength[2] * LENGTH2_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fOldLength[3] * LENGTH3_RATIO * m_rcClient.Height());

	// Upper part of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 4
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

/*	////////////////////////////////////////////////////////////////////////////////////
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
*/
	// Restore original pen
	pDC->SelectObject(m_pOldPen);
}

////////////////////////////////////////////////////////////////////////

void CPipeEditCtrl2::DrawPipeShapeToneHole(CPaintDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	int nRadiusLow, nRadiusHigh;
	int nHeight;
//	int nDiameterToneHole;
	int i;

	m_pOldPen = pDC->SelectObject(&m_penBlack);

	GetClientRect(m_rcClient);
	int nXMiddle = (int)(0.5 * m_rcClient.Width());
	int nYLowRef = (int)(0.9 * m_rcClient.Height());

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 1
	nRadiusLow = (int)(0.5 * m_fDiameterBore[0] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fDiameterBore[1] * 0.8 * m_rcClient.Width());
	nHeight = (int)(m_fLength[0] * LENGTH0_RATIO * m_rcClient.Height());

	// Upper part of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 1
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 1
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 2
	nRadiusLow = (int)(0.5 * m_fDiameterBore[1] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fDiameterBore[2] * 0.8 * m_rcClient.Width());
	nYLowRef = (int)(0.9 * m_rcClient.Height()) -
				(int)(m_fLength[0] * LENGTH0_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fLength[1] * LENGTH1_RATIO * m_rcClient.Height());

	// Upper part of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 2
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 2
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 3
	nRadiusLow = (int)(0.5 * m_fDiameterBore[2] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fDiameterBore[3] * 0.8 * m_rcClient.Width());
	nYLowRef =	(int)(0.9 * m_rcClient.Height()) -
				(int)(m_fLength[0] * LENGTH0_RATIO * m_rcClient.Height()) -
				(int)(m_fLength[1] * LENGTH1_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fLength[2] * LENGTH2_RATIO * m_rcClient.Height());

	// Upper part of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 3
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 3
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

	////////////////////////////////////////////////////////////////////////////////////
	// Tube 4
	nRadiusLow = (int)(0.5 * m_fDiameterBore[3] * 0.8 * m_rcClient.Width());
	nRadiusHigh = (int)(0.5 * m_fDiameterBore[4] * 0.8 * m_rcClient.Width());
	nYLowRef =	(int)(0.9 * m_rcClient.Height()) -
				(int)(m_fLength[0] * LENGTH0_RATIO * m_rcClient.Height()) -
				(int)(m_fLength[1] * LENGTH1_RATIO * m_rcClient.Height()) -
				(int)(m_fLength[2] * LENGTH2_RATIO * m_rcClient.Height());
	nHeight = (int)(m_fLength[3] * LENGTH3_RATIO * m_rcClient.Height());

	// Upper part of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	// Lower part of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusLow, nYLowRef);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);
	// Left Vertical Line of Tube 4
	pDC->MoveTo(nXMiddle - nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle - nRadiusLow, nYLowRef);
	// Right Vertical Line of Tube 4
	pDC->MoveTo(nXMiddle + nRadiusHigh, nYLowRef - nHeight);
	pDC->LineTo(nXMiddle + nRadiusLow, nYLowRef);

/*
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
*/
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

/*
//////////////////////////////////////////////////////////
void CPipeEditCtrl2::EraseOldPipeShapeToneHole(CPaintDC* pDC)
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

void CPipeEditCtrl2::DrawPipeShapeToneHole(CPaintDC* pDC)
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
*/

//////////////////////////////////////////////////////////

void CPipeEditCtrl2::SetLength(int nWhichTube, MY_FLOAT fLength)
{
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	ASSERT(fLength >= 0.0);
	ASSERT(fLength <= 1.0);
	m_fLength[nWhichTube] = fLength;
}

void CPipeEditCtrl2::SetDiameter(int nWhichTube, MY_FLOAT fDiameter)
{
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	ASSERT(fDiameter >= 0.0);
	ASSERT(fDiameter <= 1.0);
	m_fDiameter[nWhichTube] = fDiameter;
}

void CPipeEditCtrl2::SetDiameterBore(int nWhichToneHoleJunc, MY_FLOAT fDiameterBore)
{
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_JUNCTIONS);
	ASSERT(fDiameterBore >= 0.0);
	ASSERT(fDiameterBore <= 1.0);
	m_fDiameterBore[nWhichToneHoleJunc] = fDiameterBore;
}

void CPipeEditCtrl2::SetDiameterToneHole(int nWhichToneHoleJunc, MY_FLOAT fDiameterToneHole)
{
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	ASSERT(fDiameterToneHole >= 0.0);
	ASSERT(fDiameterToneHole <= 1.0);
	m_fDiameterToneHole[nWhichToneHoleJunc] = fDiameterToneHole;
}

/////////////////////////////////////////////////////////////////////////////

MY_FLOAT CPipeEditCtrl2::GetLength(int nWhichTube)
{
	ASSERT(nWhichTube >= 0);
	return m_fLength[nWhichTube];
}

MY_FLOAT CPipeEditCtrl2::GetDiameter(int nWhichTube)
{
	ASSERT(nWhichTube >= 0);
	return m_fDiameter[nWhichTube];
}

MY_FLOAT CPipeEditCtrl2::GetDiameterBore(int nWhichToneHoneJunc)
{
	ASSERT(nWhichToneHoneJunc >= 0);
	ASSERT(nWhichToneHoneJunc < NB_TH_JUNCTIONS);
	return m_fDiameterBore[nWhichToneHoneJunc];
}

MY_FLOAT CPipeEditCtrl2::GetDiameterToneHole(int nWhichToneHoneJunc)
{
	ASSERT(nWhichToneHoneJunc >= 0);
	ASSERT(nWhichToneHoneJunc < NB_TH_JUNCTIONS);
	return m_fDiameterToneHole[nWhichToneHoneJunc];
}


