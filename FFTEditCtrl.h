// FftEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFftEditCtrl window


#if !defined(AFX_FftEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
#define AFX_FftEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	FFT_SIZE_MAX	4096

class CFftEditCtrl : public CWnd
{
// Construction
public:
	CFftEditCtrl();
	void Clear();
	void Noise();

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

	int		m_nN;
	float	m_fData[FFT_SIZE_MAX];
	float	m_fOldData[FFT_SIZE_MAX];

// Operations
public:
	void	SetN(int nN);
	int		GetN();
	void	SetData(int nCoef, float fValue);
	float	GetData(int nCoef);
	float	GetOldData(int nCoef);

protected:
	void	DrawAxis(CPaintDC* pDC);
	void	EraseOldFFT(CPaintDC* pDC);
	void	DrawFFT(CPaintDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFftEditCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual	~CFftEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFftEditCtrl)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FftEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
