#if !defined(AFX_FirstPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_FirstPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FirstPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstPropPage dialog

class CFirstPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFirstPropPage)

protected:
//	CNoiseEditCtrl m_NoiseEditCtrl;

public:
	// Construction
public:
	CFirstPropPage();
	~CFirstPropPage();

// Dialog Data
	//{{AFX_DATA(CFirstPropPage)
	enum { IDD = IDD_GUI_PPAGE_FIRST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFirstPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFirstPropPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FirstPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
