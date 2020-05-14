// GUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGUIApp

BEGIN_MESSAGE_MAP(CGUIApp, CWinApp)
	//{{AFX_MSG_MAP(CGUIApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUIApp construction

CGUIApp::CGUIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGUIApp object

CGUIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGUIApp initialization

BOOL CGUIApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	COrganPipeModel		m_OrganPipeModel;
	m_OrganPipeModel.m_Polynomial.SetCook();

	CGUIDlg		GUIDlg("Pipe Modeler");

//	GUIDlg.m_pstrCaption = (CString*) &m_strCaption;

	CFilesPropPage		m_FilesPropPage;
	char strLocalPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, strLocalPath);

	m_FilesPropPage.m_strBrowse.Format("%s", strLocalPath);
	m_FilesPropPage.m_strFileName.Format("FluteModel");
	m_FilesPropPage.m_strPath.Format("%s\\%s.wav",	m_FilesPropPage.m_strBrowse,
													m_FilesPropPage.m_strFileName);
	m_FilesPropPage.m_strSetupPath.Format("Setup.opm");
	m_FilesPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;
	
	CExcitationPropPage	m_ExcitationPropPage;
	m_ExcitationPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;
	m_ExcitationPropPage.m_pFilesPropPage = (CFilesPropPage*) &m_FilesPropPage;
	//m_ExcitationPropPage.m_pstrPath = (CString*) &m_FilesPropPage.m_strPath;

	CNonLinearPropPage	m_NonLinearPropPage;
	m_NonLinearPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;

	CLinearPropPage		m_LinearPropPage;
	m_LinearPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;

	COutputPropPage		m_OutputPropPage;
	m_OutputPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;

	CSpectrumPropPage	m_SpectrumPropPage;
	m_SpectrumPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;

	CWaveFormPropPage	m_WaveFormPropPage;
	m_WaveFormPropPage.m_pOrganPipeModel = (COrganPipeModel*) &m_OrganPipeModel;

	//GUIDlg.SetLogoText("PC-Based Flute Modeling");
	GUIDlg.SetLogoText("Pipe Modeler");

	GUIDlg.AddPage(&m_ExcitationPropPage);
	GUIDlg.AddPage(&m_NonLinearPropPage);
	GUIDlg.AddPage(&m_LinearPropPage);
	GUIDlg.AddPage(&m_OutputPropPage);
	GUIDlg.AddPage(&m_SpectrumPropPage);
	GUIDlg.AddPage(&m_WaveFormPropPage);
	GUIDlg.AddPage(&m_FilesPropPage);

	GUIDlg.SetActivePage(&m_ExcitationPropPage);
	
	// Only one ligne of TabControl
	GUIDlg.EnableStackedTabs(FALSE);

	int nResponse = GUIDlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
