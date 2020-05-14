#if !defined(AFX_ExcitationPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_ExcitationPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ExcitationPropPage.h : header file
//

#include "WaveFormPropPage.h"
#include "FilesPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CExcitationPropPage dialog

class CExcitationPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CExcitationPropPage)

protected:
//	CNoiseEditCtrl m_NoiseEditCtrl;

public:
	// Construction
public:
	CExcitationPropPage();
	~CExcitationPropPage();

	void	UpdateText(int nID, CString strName, float fValue, CString strUnit);

public:
	COrganPipeModel*	m_pOrganPipeModel;
	CFilesPropPage*		m_pFilesPropPage;
	CWaveFormPropPage*	m_pWaveFormPropPage;
	//CString*			m_pstrPath;
	CString				m_strPlayPath;

// Dialog Data
	//{{AFX_DATA(CExcitationPropPage)
	enum { IDD = IDD_GUI_PPAGE_EXCITATION };
	CSliderCtrl	m_SliderAttack;
	CSliderCtrl	m_SliderSustain;
	CSliderCtrl	m_SliderRelease;
	BOOL	m_bExp;
	CSliderCtrl	m_SliderNoiseGain;
	CSliderCtrl	m_SliderMaxPressure;
	CSliderCtrl	m_SliderVibratoGain;
	CSliderCtrl	m_SliderVibratoFreq;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CExcitationPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CExcitationPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ExcitationPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
