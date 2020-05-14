// WaveEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaveEditCtrlEx window


#if !defined(AFX_WaveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
#define AFX_WaveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	WAVE_SIZE_MAX	4096
#define	WAVE_NB_MAX		2

class CWaveEditCtrlEx : public CWnd
{
// Construction
public:
	CWaveEditCtrlEx();
	void Clear();
	void Noise(int nSignal);

// Attributes
protected:
	CRect	m_rcClient;
	CPen*	m_pOldPen;

	CPen	m_penBlack;
	CPen	m_penGray;
	CPen	m_penWhite;
	CPen	m_penRed;
	CPen	m_penGreen;

	CFont*	m_pFont;
	CFont	m_fontScale;

	int		m_nN;
	float	m_fData[WAVE_NB_MAX][WAVE_SIZE_MAX];
	float	m_fOldData[WAVE_NB_MAX][WAVE_SIZE_MAX];

// Operations
public:
	void	SetN(int nN);
	int		GetN();
	void	SetData(int nSignal, int nCoef, float fValue);
	float	GetData(int nSignal, int nCoef);
	float	GetOldData(int nSignal, int nCoef);

protected:
	void	DrawAxis(CPaintDC* pDC);
	void	EraseOldWave(int nSignal, CPaintDC* pDC);
	void	DrawWave(int nSignal, CPaintDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveEditCtrlEx)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual	~CWaveEditCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWaveEditCtrlEx)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WaveEDITCTRL_H__86B89403_39AB_11D2_B4AD_C89CE0BA5D63__INCLUDED_)
