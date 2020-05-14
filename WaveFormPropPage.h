#if !defined(AFX_WaveFormPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_WaveFormPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WaveFormPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaveFormPropPage dialog

class CWaveFormPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CWaveFormPropPage)

// Construction
public:
	CWaveFormPropPage();
	~CWaveFormPropPage();

public:
	COrganPipeModel*	m_pOrganPipeModel;

	CWaveEditCtrlEx		m_WaveEditCtrl;
	BOOL				m_bSustain;
	BOOL				m_bZeroCrossing;
 
// Dialog Data
	//{{AFX_DATA(CWaveFormPropPage)
	enum { IDD = IDD_GUI_PPAGE_WAVEFORM };
	CSliderCtrl	m_SliderWaveformLength;
	CButton	m_BtnZeroCrossing;
	CButton	m_BtnSustain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWaveFormPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWaveFormPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSustain();
	afx_msg void OnCheckZeroCrossing();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WaveFormPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
