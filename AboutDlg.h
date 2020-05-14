#if !defined(AFX_ABOUTDLG_H_INCLUDED_)
#define AFX_ABOUTDLG_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_HyperLinkURL;
	CHyperLink	m_HyperLinkEmail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HYPERLINK_EMAIL, m_HyperLinkEmail);
	DDX_Control(pDX, IDC_HYPERLINK_URL, m_HyperLinkURL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#endif

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString string;

	SetWindowText("About Pipe Modeler 2.9");

	string.Format("Pipe Modeler Version 2.9");
	SetDlgItemText(IDC_APP_NAME, string);

	string.Format("Written by Brahim HAMADICHAREF, Copyright (C) 1999-2003");
	SetDlgItemText(IDC_AUTHOR, string);

	string.Format("Compiled on %s at %s", __DATE__, __TIME__);
	SetDlgItemText(IDC_COMPILATION, string);

	SetDlgItemText(IDC_HYPERLINK_EMAIL, "Email: bhamadicharef@plymouth.ac.uk");
	m_HyperLinkEmail.SetURL(_T("mailto:bhamadicharef@plymouth.ac.uk?subject=Pipe Modeler"));

	m_HyperLinkEmail.SetColours(m_HyperLinkEmail.GetLinkColour(), RGB(255,0,0));
	m_HyperLinkEmail.SetUnderline(TRUE);
	m_HyperLinkEmail.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));


	m_HyperLinkURL.SetURL(_T("http://www.tech.plym.ac.uk/spmc/brahim/"));
	SetDlgItemText(IDC_HYPERLINK_URL, "URL: http://www.tech.plym.ac.uk/spmc/brahim/");

	m_HyperLinkURL.SetColours(m_HyperLinkURL.GetLinkColour(), RGB(255,0,0));
	m_HyperLinkURL.SetUnderline(TRUE);
	m_HyperLinkURL.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
OSVERSIONINFO osv;
osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
CString WindowsPlatform;
if (GetVersionEx(&osv))
{
 // note: szCSDVersion =  service pack  release  
 CString ServiceRelease = osv.szCSDVersion;
 switch(osv.dwPlatformId)
 {
  case VER_PLATFORM_WIN32s: //Win32s on Windows 3.1.
   WindowsPlatform = "Microsoft® Windows 3.1(TM)";
  break;

  case VER_PLATFORM_WIN32_WINDOWS: //WIN32 on 95 or 98
   //determine if Win95 or Win98
   if (osv.dwMinorVersion == 0)
   {
    WindowsPlatform = "Microsoft® Windows 95(TM) " + ServiceRelease;
   }
   else
   {
    WindowsPlatform = "Microsoft® Windows 98(TM) " + ServiceRelease;
   }
  break;

  case VER_PLATFORM_WIN32_NT: //Win32 on Windows NT.
   WindowsPlatform = "Microsoft® Windows NT(TM) "  + ServiceRelease;
  break;

  default:
   AfxMessageBox("Failed to get correct Operating System.", MB_OK);  
 } //end switch
} //end if
*/
