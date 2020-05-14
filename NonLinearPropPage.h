#if !defined(AFX_NonLinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_NonLinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NonLinearPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNonLinearPropPage dialog

class CNonLinearPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNonLinearPropPage)

// Construction
public:
	CNonLinearPropPage();
	~CNonLinearPropPage();
	void	UpdateTextNonLinear();
	void	UpdateSlidersNonLinear();


public:
	CCurveEditCtrl		m_CurveEditCtrl;
	COrganPipeModel*	m_pOrganPipeModel;

// Dialog Data
	//{{AFX_DATA(CNonLinearPropPage)
	enum { IDD = IDD_GUI_PPAGE_NONLINEAR };
	CSliderCtrl	m_SliderNonLinear8;
	CSliderCtrl	m_SliderNonLinear7;
	CSliderCtrl	m_SliderNonLinear6;
	CSliderCtrl	m_SliderNonLinear5;
	CSliderCtrl	m_SliderNonLinear4;
	CSliderCtrl	m_SliderNonLinear3;
	CSliderCtrl	m_SliderNonLinear2;
	CSliderCtrl	m_SliderNonLinear1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNonLinearPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNonLinearPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLinear();
	afx_msg void OnCook();
	afx_msg void OnSlit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NonLinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
