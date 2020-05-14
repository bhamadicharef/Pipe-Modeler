#if !defined(AFX_OtherPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_OtherPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OtherPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherPropPage dialog

class COtherPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COtherPropPage)

// Construction
public:
	COtherPropPage();
	~COtherPropPage();

public:

// Dialog Data
	//{{AFX_DATA(COtherPropPage)
	enum { IDD = IDD_GUI_PPAGE_OTHER };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COtherPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COtherPropPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OtherPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
