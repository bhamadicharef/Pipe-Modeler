#if !defined(AFX_SpectrumPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_SpectrumPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpectrumPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpectrumPropPage dialog

class CSpectrumPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSpectrumPropPage)

// Construction
public:
	CSpectrumPropPage();
	~CSpectrumPropPage();

public:
	COrganPipeModel*	m_pOrganPipeModel;

	CFftEditCtrl		m_FftEditCtrl;
	CFFT				m_FFT;

	BOOL				m_bLogScale;

// Dialog Data
	//{{AFX_DATA(CSpectrumPropPage)
	enum { IDD = IDD_GUI_PPAGE_SPECTRUM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSpectrumPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLogScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SpectrumPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
