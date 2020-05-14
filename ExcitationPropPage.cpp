// ExcitationPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "ExcitationPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcitationPropPage property page

IMPLEMENT_DYNCREATE(CExcitationPropPage, CPropertyPage)

CExcitationPropPage::CExcitationPropPage() : CPropertyPage(CExcitationPropPage::IDD)
{
	//{{AFX_DATA_INIT(CExcitationPropPage)
	m_bExp = FALSE;
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
	m_pWaveFormPropPage = NULL;
}

CExcitationPropPage::~CExcitationPropPage()
{
}

void CExcitationPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcitationPropPage)
	DDX_Control(pDX, IDC_SLIDER_ATTACK, m_SliderAttack);
	DDX_Control(pDX, IDC_SLIDER_SUSTAIN, m_SliderSustain);
	DDX_Control(pDX, IDC_SLIDER_RELEASE, m_SliderRelease);
	DDX_Check(pDX, IDC_CHECK_EXP, m_bExp);
	DDX_Control(pDX, IDC_SLIDER_NOISEGAIN, m_SliderNoiseGain);
	DDX_Control(pDX, IDC_SLIDER_MAXPRESSURE, m_SliderMaxPressure);
	DDX_Control(pDX, IDC_SLIDER_VIBRATOGAIN, m_SliderVibratoGain);
	DDX_Control(pDX, IDC_SLIDER_VIBRATOFREQ, m_SliderVibratoFreq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExcitationPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CExcitationPropPage)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcitationPropPage message handlers

BOOL CExcitationPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_strPlayPath.Empty();

#define SLIDER_ATTACK_MAX		500
#define SLIDER_SUSTAIN_MAX		1000
#define SLIDER_RELEASE_MAX		500
	
	m_SliderAttack.SetRange(0, SLIDER_ATTACK_MAX - 1);
	m_SliderSustain.SetRange(0, SLIDER_SUSTAIN_MAX - 1);
	m_SliderRelease.SetRange(0, SLIDER_RELEASE_MAX - 1);

	// Breath Noise and Maximum Pressure
	m_SliderNoiseGain.SetRange(0, SLIDER_MAX);
	m_SliderMaxPressure.SetRange(0, (int)(SLIDER_MAX * 0.2));

	m_SliderVibratoGain.SetRange(0, SLIDER_MAX);
	m_SliderVibratoFreq.SetRange(0, SLIDER_MAX);

	m_pOrganPipeModel->SetFrequency((MY_FLOAT) 880.0);
	m_pOrganPipeModel->Clear();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CExcitationPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();

	/////////////////////////////////////////////////////////////////////////////////
	// ASR Attack
	m_SliderAttack.SetPos((int)(SLIDER_ATTACK_MAX - m_pOrganPipeModel->m_pAsr->GetAttackTime()));
	UpdateText(IDC_TEXT_ATTACK, "Attack", m_pOrganPipeModel->m_pAsr->GetAttackTime(), "msec");

	// ASR Sustain
	m_SliderSustain.SetPos((int)(SLIDER_SUSTAIN_MAX - m_pOrganPipeModel->m_pAsr->GetSustainTime()));
	UpdateText(IDC_TEXT_SUSTAIN, "Sustain", m_pOrganPipeModel->m_pAsr->GetSustainTime(), "msec");

	// ASR Release
	m_SliderRelease.SetPos((int)(SLIDER_RELEASE_MAX - m_pOrganPipeModel->m_pAsr->GetReleaseTime()));
	UpdateText(IDC_TEXT_RELEASE, "Release", m_pOrganPipeModel->m_pAsr->GetReleaseTime(), "msec");

	CheckDlgButton(IDC_CHECK_EXP, m_bExp);

	/////////////////////////////////////////////////////////////////////////////////
	//
	// Breath Noise
	m_SliderNoiseGain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetNoiseGain())));
	UpdateText(IDC_TEXT_NOISEGAIN, "NoiseGain", m_pOrganPipeModel->GetNoiseGain(), "");

	m_SliderMaxPressure.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetMaxPressure())));
	UpdateText(IDC_TEXT_MAXPRESSURE, "MaxPressure", m_pOrganPipeModel->GetMaxPressure(), "");

	/////////////////////////////////////////////////////////////////////////////////
	//
	// Vibrato Gain
	m_SliderVibratoGain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetVibratoGain())));
	UpdateText(IDC_TEXT_VIBRATOGAIN, "VibratoGain", m_pOrganPipeModel->GetVibratoGain(), "");

	// Vibrato Frequency
	m_SliderVibratoFreq.SetPos((int)(SLIDER_MAX - m_pOrganPipeModel->GetVibratoFrequency() + 5.0));
	UpdateText(IDC_TEXT_VIBRATOFREQ, "VibratoFreq", m_pOrganPipeModel->GetVibratoFrequency(), "Hz");
	
	return CPropertyPage::OnSetActive();
}

void CExcitationPropPage::UpdateText(int nID, CString strName, float fValue, CString strUnit) 
{
	CString str;
	float fValue1;
	fValue1 = fValue - (float)(((int)(fValue)));
	if(fValue1 == 0.0)
	{
		str.Format("%s\n%4.0f %s", strName, fValue, strUnit);
	}
	else
	{
		str.Format("%s\n%4.3f %s", strName, fValue, strUnit);
	}
	ASSERT(nID);
	SetDlgItemText(nID, str);
}

BOOL CExcitationPropPage::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWaitCursor wait;    // display wait cursor
	MY_FLOAT fData;

	ASSERT(m_pOrganPipeModel != NULL);
	ASSERT(m_pFilesPropPage != NULL);

	m_strPlayPath = m_pFilesPropPage->GetPlayPath();

	CTime t = CTime::GetCurrentTime();

	m_pOrganPipeModel->Clear();
	m_pOrganPipeModel->m_pAsr->Init();

	for(long i = 0; i < SRATE; i++)
	{
		fData = m_pOrganPipeModel->Tick();
		//TRACE("PluckOut = %f\n", fData);
	}
	m_pOrganPipeModel->SaveWavFile(m_strPlayPath);

	m_pOrganPipeModel->m_bModifiedWaveform= TRUE;
	m_pOrganPipeModel->m_bModifiedSpectrum = TRUE;

	//TRACE("\n\n");

	CTimeSpan ts = t - CTime::GetCurrentTime();
	//CString string = ts.Format("PC-Based Flute Modeling [%Ss]" );
	CString string = ts.Format("Pipe Modeler [%Ss]" );
	GetParent()->SetWindowText(string);

	BOOL bOk = FALSE;
	// found the resource, play it
	CWaitCursor WaitCursor;
	bOk = sndPlaySound(m_strPlayPath, SND_ASYNC | SND_NODEFAULT);
	if(!bOk)
	{
		AfxMessageBox("Cannot play sound");
	}
	return CPropertyPage::OnApply();
}

void CExcitationPropPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSliderCtrl;
	pSliderCtrl = (CSliderCtrl*) pScrollBar;
	float fSliderValue = (MY_FLOAT)(pSliderCtrl->GetPos());
	//TRACE("OutputSlider = %f\n", nSliderValue);

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
				// Asr Control
				//
				if(pSliderCtrl == GetDlgItem(IDC_SLIDER_ATTACK))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_ATTACK_MAX - fSliderValue);
					m_pOrganPipeModel->m_pAsr->SetAttackTime((MY_FLOAT) fSliderValue);
					UpdateText(IDC_TEXT_ATTACK, "Attack", fSliderValue, "msec");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_SUSTAIN))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_SUSTAIN_MAX - fSliderValue);
					m_pOrganPipeModel->m_pAsr->SetSustainTime((MY_FLOAT) fSliderValue);	// 0.5 sec
					UpdateText(IDC_TEXT_SUSTAIN, "Sustain", fSliderValue, "msec");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_RELEASE))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_RELEASE_MAX - fSliderValue);
					m_pOrganPipeModel->m_pAsr->SetReleaseTime((MY_FLOAT) fSliderValue);
					UpdateText(IDC_TEXT_RELEASE, "Release", fSliderValue, "msec");
				}
				//////////////////////////////////////////////////////////////////////////////
				// 
				// Input noise Pressure
				// 
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NOISEGAIN))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetNoiseGain(fSliderValue);
					UpdateText(IDC_TEXT_NOISEGAIN, "NoiseGain", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_MAXPRESSURE))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetMaxPressure(fSliderValue);
					UpdateText(IDC_TEXT_MAXPRESSURE, "MaxPressure", fSliderValue, "");
				}
				//////////////////////////////////////////////////////////////////////////////
				// 
				// Input Vibrato Pressure
				// 
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_VIBRATOGAIN))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					fSliderValue /= (MY_FLOAT)(10);
					m_pOrganPipeModel->SetVibratoGain(fSliderValue);
					UpdateText(IDC_TEXT_VIBRATOGAIN, "VibratoGain", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_VIBRATOFREQ))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					fSliderValue *= (MY_FLOAT)(50);
					fSliderValue += (MY_FLOAT)(5);
					m_pOrganPipeModel->SetVibratoFrequency(fSliderValue);
					UpdateText(IDC_TEXT_VIBRATOFREQ, "VibratoFreq", fSliderValue, "Hz");
				}
			}
		default:
			break;
	}
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}
