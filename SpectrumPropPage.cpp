// SpectrumPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "SpectrumPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrumPropPage property page

IMPLEMENT_DYNCREATE(CSpectrumPropPage, CPropertyPage)

CSpectrumPropPage::CSpectrumPropPage() : CPropertyPage(CSpectrumPropPage::IDD)
{
	//{{AFX_DATA_INIT(CSpectrumPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
	m_bLogScale = FALSE;
}

CSpectrumPropPage::~CSpectrumPropPage()
{
}

void CSpectrumPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumPropPage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrumPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSpectrumPropPage)
	ON_BN_CLICKED(IDC_CHECK_LOG, OnCheckLogScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumPropPage message handlers

BOOL CSpectrumPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();

	if(m_pOrganPipeModel->m_bModifiedSpectrum)
	{
		CWaitCursor WaitCursor;

		ASSERT(m_pOrganPipeModel != NULL);
		CWavFileOut* pWavFileOut = m_pOrganPipeModel->GetPtrWavFileOut();

		long i;
		MY_FLOAT fData;
		
		fData = m_pOrganPipeModel->m_pAsr->GetAttackTime();
		fData /= (MY_FLOAT) 1000.0;
		fData /= (MY_FLOAT) ONE_OVER_SRATE;
		int nOffset = (int) fData;

#define	FFT_SIZE	1024

		m_FFT.Clear();
		m_FFT.SetSize(FFT_SIZE);

		for(i = 0; i < FFT_SIZE; i++)
		{
			fData = (MY_FLOAT)(1.0 + (pWavFileOut->m_fData[0][nOffset + i]));
			m_FFT.Add(fData);
		}
		m_FFT.PerformFFT();

		MY_FLOAT fValue;
		for(i = 0; i < FFT_SIZE; i++)
		{
			if(i == 0)
				fValue = 0;
			else
				fValue = 100 * m_FFT.GetOutPower(i);

			// Normalize between 100 and 0
			if(fValue > 100.0)
			{
				fValue = 100.0;
			}
			if(fValue < 1.0)
			{
				fValue = 0.0;
			}

			if(m_bLogScale)
			{
				if(fValue != 0)
				{
					fValue = 50 * log10(fValue);
				}
				else
				{
					fValue = 0;
				}
			}
			m_FftEditCtrl.SetData(i, fValue);
		}
	
		m_FftEditCtrl.Invalidate();
	}

	m_pOrganPipeModel->m_bModifiedSpectrum = FALSE;

	return CPropertyPage::OnSetActive();
}

BOOL CSpectrumPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL CSpectrumPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	ASSERT(m_pOrganPipeModel != NULL);

	CRect rect;
	GetDlgItem(IDC_FFTEDITCTRL)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_FftEditCtrl.SubclassDlgItem(IDC_FFTEDITCTRL, this);
	m_FftEditCtrl.SetN(FFT_SIZE);
	m_FftEditCtrl.Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpectrumPropPage::OnCheckLogScale() 
{
	// TODO: Add your control notification handler code here
	m_pOrganPipeModel->m_bModifiedSpectrum = TRUE;
	if(m_bLogScale)
	{
		m_bLogScale = FALSE;
	}
	else
	{
		m_bLogScale = TRUE;
	}
	OnSetActive();
}
