// WaveFormPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "WaveFormPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveFormPropPage property page

IMPLEMENT_DYNCREATE(CWaveFormPropPage, CPropertyPage)

CWaveFormPropPage::CWaveFormPropPage() : CPropertyPage(CWaveFormPropPage::IDD)
{
	//{{AFX_DATA_INIT(CWaveFormPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
	m_bSustain = TRUE;
	m_bZeroCrossing = TRUE;
}

CWaveFormPropPage::~CWaveFormPropPage()
{
}

void CWaveFormPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveFormPropPage)
	DDX_Control(pDX, IDC_SLIDER_LENGTH, m_SliderWaveformLength);
	DDX_Control(pDX, IDC_CHECK_ZEROCROSSING, m_BtnZeroCrossing);
	DDX_Control(pDX, IDC_CHECK_SUSTAIN, m_BtnSustain);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaveFormPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CWaveFormPropPage)
	ON_BN_CLICKED(IDC_CHECK_SUSTAIN, OnCheckSustain)
	ON_BN_CLICKED(IDC_CHECK_ZEROCROSSING, OnCheckZeroCrossing)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveFormPropPage message handlers

BOOL CWaveFormPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();

	if(m_bSustain)
	{
		m_BtnSustain.SetCheck(1);
	}
	else
	{
		m_BtnSustain.SetCheck(0);
	}

	if(m_bZeroCrossing)
	{
		m_BtnZeroCrossing.SetCheck(1);
	}
	else
	{
		m_BtnZeroCrossing.SetCheck(0);
	}

	if(m_pOrganPipeModel->m_bModifiedWaveform)
	{
		CWaitCursor WaitCursor;

		ASSERT(m_pOrganPipeModel != NULL);
		CWavFileOut* pWavFileOut = m_pOrganPipeModel->GetPtrWavFileOut();
		
		long i;
		float fData;

#define SCALE_FACTOR	1

		int nOffset = 0;
		if(m_bSustain)
		{
			fData = m_pOrganPipeModel->m_pAsr->GetAttackTime();
			fData /= (MY_FLOAT) 1000.0;
			fData /= (MY_FLOAT) ONE_OVER_SRATE;
			nOffset = (int)(fData * 2);
		}
		//TRACE("Offset = %d\n", nOffset);

		if(m_bZeroCrossing)
		{
			while(	(pWavFileOut->m_fData[0][nOffset] > 0) ||
					(pWavFileOut->m_fData[0][nOffset+1] < 0))
			{
				nOffset++;
			}
		}

		//m_WaveEditCtrl.Clear();
		for(i = 0; i < m_WaveEditCtrl.GetN(); i++)
		{
			//j = (int)((i * SCALE_FACTOR) + nOffset);
			fData = pWavFileOut->m_fData[0][nOffset + i];
			m_WaveEditCtrl.SetData(0, i, fData);

			fData = pWavFileOut->m_fData[1][nOffset + i];
			m_WaveEditCtrl.SetData(1, i, fData);
		}
		m_WaveEditCtrl.Invalidate();
	}

	m_pOrganPipeModel->m_bModifiedWaveform = FALSE;

	return CPropertyPage::OnSetActive();
}

BOOL CWaveFormPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnKillActive();
}

BOOL CWaveFormPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	ASSERT(m_pOrganPipeModel != NULL);

	CRect rect;
	GetDlgItem(IDC_WAVEEDITCTRL)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_WaveEditCtrl.SubclassDlgItem(IDC_WAVEEDITCTRL, this);
	m_WaveEditCtrl.SetN(WAVE_SIZE_MAX);
	m_WaveEditCtrl.Invalidate();

	m_SliderWaveformLength.SetRange(1, 5);
	m_SliderWaveformLength.SetPos(1);
	m_WaveEditCtrl.SetN(WAVE_SIZE_MAX * m_SliderWaveformLength.GetPos() / 4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaveFormPropPage::OnCheckSustain() 
{
	// TODO: Add your control notification handler code here
	m_pOrganPipeModel->m_bModifiedWaveform = TRUE;
	if(m_bSustain)
	{
		m_bSustain = FALSE;
	}
	else
	{
		m_bSustain = TRUE;
	}
	OnSetActive();
}

void CWaveFormPropPage::OnCheckZeroCrossing() 
{
	// TODO: Add your control notification handler code here
	m_pOrganPipeModel->m_bModifiedWaveform = TRUE;
	if(m_bZeroCrossing )
	{
		m_bZeroCrossing = FALSE;
	}
	else
	{
		m_bZeroCrossing = TRUE;
	}
	OnSetActive();
}

void CWaveFormPropPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSliderCtrl;
	pSliderCtrl = (CSliderCtrl*) pScrollBar;
	int nSliderValue = pSliderCtrl->GetPos();

	switch(nSBCode)
	{
		case TB_BOTTOM:
		case TB_TOP:
		case TB_LINEUP:
		case TB_LINEDOWN:
		case TB_PAGEUP:
		case TB_PAGEDOWN:
		case TB_THUMBTRACK:
		case TB_THUMBPOSITION:
		//case TB_ENDTRACK:
			{
				//////////////////////////////////////////////////////////////////////////////
				// 
				if(pSliderCtrl == GetDlgItem(IDC_SLIDER_LENGTH))
				{
					m_pOrganPipeModel->m_bModifiedWaveform = TRUE;
					m_WaveEditCtrl.SetN(WAVE_SIZE_MAX * nSliderValue);
					OnSetActive();
				}
			}
			break;
		default:
			break;
	}
	Invalidate();

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
