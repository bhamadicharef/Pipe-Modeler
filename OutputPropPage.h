#if !defined(AFX_OutputPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_OutputPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputPropPage dialog

#define	SLIDER_MAX	200
#define	SLIDER_MID	SLIDER_MAX / 2

#define	SLIDER_FREQUENCY_MAX 2000

class COutputPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COutputPropPage)

// Construction
public:
	COutputPropPage();
	~COutputPropPage();
	void	UpdateText(int nID, CString strName, float fValue, CString strUnit);

public:
	COrganPipeModel*	m_pOrganPipeModel;

// Dialog Data
	//{{AFX_DATA(COutputPropPage)
	enum { IDD = IDD_GUI_PPAGE_OUTPUT };
	CSliderCtrl	m_SliderJetReflection;
	CSliderCtrl	m_SliderEndReflection;
	CSliderCtrl	m_SliderFrequency;
	CSliderCtrl	m_SliderBoreGain;
	CSliderCtrl	m_SliderToneHole1Gain;
	CSliderCtrl	m_SliderToneHole2Gain;
	CSliderCtrl	m_SliderToneHole3Gain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COutputPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COutputPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OutputPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
