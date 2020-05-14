// FirstPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "FirstPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstPropPage property page

IMPLEMENT_DYNCREATE(CFirstPropPage, CPropertyPage)

CFirstPropPage::CFirstPropPage() : CPropertyPage(CFirstPropPage::IDD)
{
	//{{AFX_DATA_INIT(CFirstPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFirstPropPage::~CFirstPropPage()
{
}

void CFirstPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstPropPage)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFirstPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFirstPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstPropPage message handlers

BOOL CFirstPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFirstPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();
	return CPropertyPage::OnSetActive();
}

BOOL CFirstPropPage::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i = 0;
	i++;
	return CPropertyPage::OnApply();
}
