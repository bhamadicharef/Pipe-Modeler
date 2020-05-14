// OutputPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "OutputPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputPropPage property page

IMPLEMENT_DYNCREATE(COutputPropPage, CPropertyPage)

COutputPropPage::COutputPropPage() : CPropertyPage(COutputPropPage::IDD)
{
	//{{AFX_DATA_INIT(COutputPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
}

COutputPropPage::~COutputPropPage()
{
}

void COutputPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputPropPage)
	DDX_Control(pDX, IDC_SLIDER_JETREFLECTION, m_SliderJetReflection);
	DDX_Control(pDX, IDC_SLIDER_ENDREFLECTION, m_SliderEndReflection);
	DDX_Control(pDX, IDC_SLIDER_FREQUENCY, m_SliderFrequency);
	DDX_Control(pDX, IDC_SLIDER_OUTPUTGAIN, m_SliderBoreGain);
	DDX_Control(pDX, IDC_SLIDER_OUTPUTGAINTH1, m_SliderToneHole1Gain);
	DDX_Control(pDX, IDC_SLIDER_OUTPUTGAINTH2, m_SliderToneHole2Gain);
	DDX_Control(pDX, IDC_SLIDER_OUTPUTGAINTH3, m_SliderToneHole3Gain);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COutputPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(COutputPropPage)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputPropPage message handlers

BOOL COutputPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();
	return CPropertyPage::OnSetActive();
}

BOOL COutputPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL COutputPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	m_SliderJetReflection.SetRange(0, SLIDER_MAX);
	m_SliderEndReflection.SetRange(0, SLIDER_MAX);
	m_SliderFrequency.SetRange(0, SLIDER_FREQUENCY_MAX);
	m_SliderBoreGain.SetRange(0, SLIDER_MAX);
	m_SliderToneHole1Gain.SetRange(0, SLIDER_MAX);
	m_SliderToneHole2Gain.SetRange(0, SLIDER_MAX);
	m_SliderToneHole3Gain.SetRange(0, SLIDER_MAX);

	m_SliderJetReflection.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetJetReflection())));
	UpdateText(IDC_TEXT_JETREFLECTION, "JetReflection", m_pOrganPipeModel->GetJetReflection(), "");

	m_SliderEndReflection.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetEndReflection())));
	UpdateText(IDC_TEXT_ENDREFLECTION, "EndReflection", m_pOrganPipeModel->GetEndReflection(), "");

	m_SliderFrequency.SetPos((int)(SLIDER_FREQUENCY_MAX - m_pOrganPipeModel->GetFrequency() + 100.0));
	UpdateText(IDC_TEXT_FREQUENCY, "Frequency", m_pOrganPipeModel->GetFrequency(), "Hz");

	m_SliderBoreGain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetBoreGain())));
	UpdateText(IDC_TEXT_OUTPUTGAIN, "BoreGain", m_pOrganPipeModel->GetBoreGain(), "");

	// 3 ToneHoles
	m_SliderToneHole1Gain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetToneHole1Gain())));
	UpdateText(IDC_TEXT_OUTPUTGAINTH1, "TH1Gain", m_pOrganPipeModel->GetToneHole1Gain(), "");

	m_SliderToneHole2Gain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetToneHole2Gain())));
	UpdateText(IDC_TEXT_OUTPUTGAINTH2, "TH2Gain", m_pOrganPipeModel->GetToneHole2Gain(), "");

	m_SliderToneHole3Gain.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetToneHole3Gain())));
	UpdateText(IDC_TEXT_OUTPUTGAINTH3, "TH3Gain", m_pOrganPipeModel->GetToneHole3Gain(), "");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COutputPropPage::UpdateText(int nID, CString strName, float fValue, CString strUnit) 
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
	SetDlgItemText(nID, str);
}

void COutputPropPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSliderCtrl;
	pSliderCtrl = (CSliderCtrl*) pScrollBar;
	float fSliderValue = (MY_FLOAT)(pSliderCtrl->GetPos());
	//TRACE("OutputSlider = %f\n", nSliderValue);

	ASSERT(m_pOrganPipeModel != NULL);

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
				// Reflection
				// 
				if(pSliderCtrl == GetDlgItem(IDC_SLIDER_JETREFLECTION))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetJetReflection(fSliderValue);

					m_pOrganPipeModel->SetEndReflection(1.0 - fSliderValue);
					m_SliderEndReflection.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetEndReflection())));
					UpdateText(IDC_TEXT_ENDREFLECTION, "EndReflection", m_pOrganPipeModel->GetEndReflection(), "");

					UpdateText(IDC_TEXT_JETREFLECTION, "JetReflection", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_ENDREFLECTION))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetEndReflection(fSliderValue);

					m_pOrganPipeModel->SetJetReflection(1.0 - fSliderValue);
					m_SliderJetReflection.SetPos((int)(SLIDER_MAX * (1.0 - m_pOrganPipeModel->GetJetReflection())));
					UpdateText(IDC_TEXT_JETREFLECTION, "JetReflection", m_pOrganPipeModel->GetJetReflection(), "");

					UpdateText(IDC_TEXT_ENDREFLECTION, "EndReflection", fSliderValue, "");
				}
				// 
				// 
				// 
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_FREQUENCY))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_FREQUENCY_MAX - fSliderValue);
					fSliderValue += (MY_FLOAT) 100.0;
					// Frequency = 100 Hz ... (100 Hz + SLIDER_MAX) = 300 Hz
					m_pOrganPipeModel->SetFrequency(fSliderValue);
					UpdateText(IDC_TEXT_FREQUENCY, "Frequency", fSliderValue, "Hz");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_OUTPUTGAIN))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetBoreGain(fSliderValue);
					UpdateText(IDC_TEXT_OUTPUTGAIN, "BoreGain", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_OUTPUTGAINTH1))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetToneHole1Gain(fSliderValue);
					UpdateText(IDC_TEXT_OUTPUTGAINTH1, "TH1Gain", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_OUTPUTGAINTH2))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetToneHole2Gain(fSliderValue);
					UpdateText(IDC_TEXT_OUTPUTGAINTH2, "TH2Gain", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_OUTPUTGAINTH3))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MAX - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MAX);
					m_pOrganPipeModel->SetToneHole3Gain(fSliderValue);
					UpdateText(IDC_TEXT_OUTPUTGAINTH3, "TH3Gain", fSliderValue, "");
				}
			}
		default:
			break;
	}
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}
