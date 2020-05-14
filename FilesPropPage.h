#if !defined(AFX_FilesPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_FilesPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FilesPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilesPropPage dialog

class CFilesPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFilesPropPage)

// Construction
public:
	CFilesPropPage();
	~CFilesPropPage();
	CString	GetPlayPath();

public:
	COrganPipeModel*	m_pOrganPipeModel;

	CString				m_strSetupPath;
	CString				m_strSetupName;

	CString				m_strBrowse;
	CString				m_strPath;
	CString				m_strFileName;

// Dialog Data
	//{{AFX_DATA(CFilesPropPage)
	enum { IDD = IDD_GUI_PPAGE_FILES };
	CEdit	m_EditFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilesPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFilesPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnBrowse();
	afx_msg void OnChangeFilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FilesPropPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
