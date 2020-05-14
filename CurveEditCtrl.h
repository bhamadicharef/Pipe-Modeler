// CurveEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurveEditCtrl window


#if !defined(AFX_CurveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
#define AFX_CurveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Polynomial.h"

class CCurveEditCtrl : public CWnd
{
// Construction
public:
	CCurveEditCtrl();

// Attributes
public:
protected:
	CRect	m_rcClient;
	CPen*	m_pOldPen;
	CPen	m_penBlack;
	CPen	m_penGray;
	CPen	m_penWhite;
	CPen	m_penRed;

	CFont*	m_pFont;
	CFont	m_fontScale;

public:
	CPolynomial*	m_pPolynomial;

// Operations

protected:
	void	DrawAxis(CPaintDC* pDC);
	void	EraseOldCurveShape(CPaintDC* pDC);
	void	DrawCurveShape(CPaintDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveEditCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual	~CCurveEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCurveEditCtrl)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CurveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
