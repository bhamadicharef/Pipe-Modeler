#if !defined(AFX_LinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_LinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LinearPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinearPropPage dialog

#define DIAMETER_RES	400
#define LENGTH_RES		400

class CLinearPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CLinearPropPage)

// Construction
public:
	CLinearPropPage();
	~CLinearPropPage();
	void UpdateText(int nID, CString strName, float fValue, CString strUnit);

public:
	COrganPipeModel*	m_pOrganPipeModel;
	CPipeEditCtrl2		m_PipeEditCtrl;

// Dialog Data
	//{{AFX_DATA(CLinearPropPage)
	enum { IDD = IDD_GUI_PPAGE_LINEAR };
	CSliderCtrl	m_SliderD1;
	CSliderCtrl	m_SliderD2;
	CSliderCtrl	m_SliderD3;
	CSliderCtrl	m_SliderD4;
	CSliderCtrl	m_SliderD5;
	CSliderCtrl	m_SliderD6;			// Diameter of the ToneHole
	CSliderCtrl	m_SliderL1;
	CSliderCtrl	m_SliderL2;
	CSliderCtrl	m_SliderL3;
	CSliderCtrl	m_SliderL4;
	CSliderCtrl	m_SliderL5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLinearPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLinearPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LinearPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
