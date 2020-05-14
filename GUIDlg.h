#if !defined(AFX_GUIDLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_GUIDLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GUIDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg

class CGUIDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CGUIDlg)

// Construction
public:
	CGUIDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGUIDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CString*	m_pstrCaption;

protected:
	CImageList	m_imageTab;
	CFont		m_fontEdit;

	// Logo
	CFont 		m_fontLogo;
	CString		m_LogoText;

// Operations
public:
	void	AutoArrangeButtons();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUIDlg)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLogoFont(CString Name, int nHeight = 24, int nWeight = FW_BOLD,
		BYTE bItalic = true, BYTE bUnderline = false);
	void SetLogoText(CString Text);
	virtual ~CGUIDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGUIDlg)
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
