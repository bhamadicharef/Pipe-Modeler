// PipeEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPipeEditCtrl window


#if !defined(AFX_PipeEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
#define AFX_PipeEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Junction.h"
#include "TubeSection.h"

class CPipeEditCtrl : public CWnd
{
// Construction
public:
	CPipeEditCtrl();

// Attributes
protected:
	CRect		m_rcClient;
	CPen*		m_pOldPen;
	CPen		m_penBlack;
	CPen		m_penGray;
	CPen		m_penWhite;

	CFont*		m_pFont;
	CFont		m_fontScale;

	MY_FLOAT	m_fLength[NB_TUBES],	m_fOldLength[NB_TUBES];
	MY_FLOAT	m_fDiameter[NB_TUBES],	m_fOldDiameter[NB_TUBES];

	MY_FLOAT	m_fDiameterBore[NB_TH_JUNCTIONS],
				m_fOldDiameterBore[NB_TH_JUNCTIONS];
	MY_FLOAT	m_fDiameterToneHole[NB_TH_JUNCTIONS],
				m_fOldDiameterToneHole[NB_TH_JUNCTIONS];

public:
/*
	CJunction*		m_pJunction;
	CTubeSection*	m_pTube1;
	CTubeSection*	m_pTube2;
*/

// Operations
public:
	void	SetLength(int nWhichTube, MY_FLOAT fLength1);
	void	SetDiameter(int nWhichTube, MY_FLOAT fDiameter1);

	void	SetDiameterBore(int nWhichToneHoleJunc, MY_FLOAT fDiameterBore);
	void	SetDiameterToneHole(int nWhichToneHoleJunc, MY_FLOAT fDiameterToneHole);


	MY_FLOAT	GetLength(int nWhichTube);
								//{ return m_fLength[nWhichTube]; };
	MY_FLOAT	GetDiameter(int nWhichTube);
								//{ return m_fDiameter[nWhichTube]; };

	MY_FLOAT	GetDiameterBore(int nWhichToneHoneJunc);
								//{ return m_fDiameterBore; };
	MY_FLOAT	GetDiameterToneHole(int nWhichToneHoneJunc);
								//{ return m_fDiameterToneHole; };


protected:
	void	DrawAxis(CPaintDC* pDC);
	void	EraseOldPipeShape(CPaintDC* pDC);
	void	DrawPipeShape(CPaintDC* pDC);

	void	EraseOldPipeShapeToneHole(CPaintDC* pDC);
	void	DrawPipeShapeToneHole(CPaintDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPipeEditCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual	~CPipeEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPipeEditCtrl)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PipeEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
