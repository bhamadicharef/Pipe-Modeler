// FilesPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "FilesPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesPropPage property page

IMPLEMENT_DYNCREATE(CFilesPropPage, CPropertyPage)

CFilesPropPage::CFilesPropPage() : CPropertyPage(CFilesPropPage::IDD)
{
	//{{AFX_DATA_INIT(CFilesPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
}

CFilesPropPage::~CFilesPropPage()
{
}

void CFilesPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilesPropPage)
	DDX_Control(pDX, IDC_FILENAME, m_EditFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilesPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFilesPropPage)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_FILENAME, OnChangeFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesPropPage message handlers

BOOL CFilesPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();
	return CPropertyPage::OnSetActive();
}

BOOL CFilesPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL CFilesPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	ASSERT(IDC_FILENAME);
	CEdit* pEdit = (CEdit*) GetDlgItem(IDC_FILENAME);
	pEdit->SetWindowText((LPCTSTR) m_strFileName);

	SetDlgItemText(IDC_TEXT_BROWSE, m_strPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CFilesPropPage::GetPlayPath()
{
	ASSERT(this);
	return m_strPath;
}

void CFilesPropPage::OnLoad() 
{
	// TODO: Add your control notification handler code here
	CString strSetupFile;
	CString strFileName;

	strSetupFile.Empty();
	strFileName.Empty();

	CFile SetupFile;
	CFileException SetupFileE;

	CString strSetupFilter = "OrganPipeModel Files (*.opm)|*.opm|";
	CFileDialog FileDialog(TRUE, "opm", strFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // | OFN_EXPLORER,
							strSetupFilter, NULL);
	
	// case new fresh gui
	if(FileDialog.DoModal() == IDOK)
	{
		m_strSetupPath = FileDialog.GetPathName();
		m_strSetupName = FileDialog.GetFileTitle();

		if(!SetupFile.Open(m_strSetupPath /* m_strSetupPath */, CFile::modeRead , &SetupFileE))
		{
			AfxMessageBox("File could not be opened " , MB_OK | MB_ICONSTOP);
			ASSERT(FALSE);
		}
		else
		{
			CArchive Archive(&SetupFile, CArchive::load);
			ASSERT(m_pOrganPipeModel != NULL);
			m_pOrganPipeModel->Serialize(Archive);
			Archive.Close();
			SetupFile.Close();
			//Init();
		}

		// Only at the end change the caption
		m_strCaption.Format("OrganPipe1 - %s", strFileName);
		SetWindowText(m_strCaption);
	}
}

void CFilesPropPage::OnSave() 
{
	// TODO: Add your control notification handler code here
	m_strSetupPath.Empty();
	m_strSetupName.Format("Noname.opm");

	CFile SetupFile;
	CFileException SetupFileE;

	CString strSetupFilter = "OrganPipeModel Files (*.opm)|*.opm|";
	CFileDialog FileDialog(FALSE, "opm", m_strSetupName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // | OFN_EXPLORER,
							strSetupFilter, NULL);
	
	// case new fresh gui
	if(FileDialog.DoModal() == IDOK)
	{
		m_strSetupPath = FileDialog.GetPathName();
		m_strSetupName = FileDialog.GetFileTitle();

		if(!SetupFile.Open(m_strSetupPath /* m_strSetupPath */, CFile::modeCreate | CFile::modeWrite, &SetupFileE))
		{
			AfxMessageBox("File could not be opened " , MB_OK | MB_ICONSTOP);
			ASSERT(FALSE);
		}
		else
		{
			CArchive Archive(&SetupFile, CArchive::store);
			ASSERT(m_pOrganPipeModel != NULL);
			m_pOrganPipeModel->Serialize(Archive);
			Archive.Close();
			SetupFile.Close();
		}

		// Only at the end change the caption
		m_strCaption.Format("OrganPipe1 - %s", m_strSetupName);
		SetWindowText(m_strCaption);
	}
	
}

void CFilesPropPage::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CSBDestination sb(m_hWnd, IDS_BFF_TITLE);
	sb.SetFlags(BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT);
	sb.SetInitialSelection(m_strBrowse);
	if(sb.SelectFolder())
	{
		m_strBrowse.Format("%s", sb.GetSelectedFolder());
		m_strPath.Format("%s\\%s.wav", m_strBrowse, m_strFileName);
		SetDlgItemText(IDC_TEXT_BROWSE, m_strPath);
		TRACE("Path = %s\n", m_strPath);
		UpdateData(FALSE);
	}
}

void CFilesPropPage::OnChangeFilename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	ASSERT(IDC_FILENAME);
	CString strFileName;
	CEdit* pEdit = (CEdit*) GetDlgItem(IDC_FILENAME);
	pEdit->GetWindowText(strFileName);
	if(!strFileName.IsEmpty())
	{
		m_strFileName.Format("%s", strFileName);
		m_strPath.Format("%s\\%s.wav", m_strBrowse, m_strFileName);
		SetDlgItemText(IDC_TEXT_BROWSE, m_strPath);
	}
	else
	{
		AfxMessageBox("Empty File name" , MB_OK | MB_ICONSTOP);
			ASSERT(FALSE);
	}
}
