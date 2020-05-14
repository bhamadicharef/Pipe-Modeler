// OtherPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "OtherPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherPropPage property page

IMPLEMENT_DYNCREATE(COtherPropPage, CPropertyPage)

COtherPropPage::COtherPropPage() : CPropertyPage(COtherPropPage::IDD)
{
	//{{AFX_DATA_INIT(COtherPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COtherPropPage::~COtherPropPage()
{
}

void COtherPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherPropPage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(COtherPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherPropPage message handlers

BOOL COtherPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();
	return CPropertyPage::OnSetActive();
}

BOOL COtherPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL COtherPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

