// LinearPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "LinearPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearPropPage property page

IMPLEMENT_DYNCREATE(CLinearPropPage, CPropertyPage)

CLinearPropPage::CLinearPropPage() : CPropertyPage(CLinearPropPage::IDD)
{
	//{{AFX_DATA_INIT(CLinearPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOrganPipeModel = NULL;
}

CLinearPropPage::~CLinearPropPage()
{
}

void CLinearPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinearPropPage)
	DDX_Control(pDX, IDC_SLIDERD1, m_SliderD1);
	DDX_Control(pDX, IDC_SLIDERD2, m_SliderD2);
	DDX_Control(pDX, IDC_SLIDERD3, m_SliderD3);
	DDX_Control(pDX, IDC_SLIDERD4, m_SliderD4);
	DDX_Control(pDX, IDC_SLIDERD5, m_SliderD5);
	DDX_Control(pDX, IDC_SLIDERD6, m_SliderD6);
	DDX_Control(pDX, IDC_SLIDERL1, m_SliderL1);
	DDX_Control(pDX, IDC_SLIDERL2, m_SliderL2);
	DDX_Control(pDX, IDC_SLIDERL3, m_SliderL3);
	DDX_Control(pDX, IDC_SLIDERL4, m_SliderL4);
	DDX_Control(pDX, IDC_SLIDERL5, m_SliderL5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinearPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLinearPropPage)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinearPropPage message handlers

BOOL CLinearPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();

	MY_FLOAT fValue;

	fValue = (MY_FLOAT) LENGTH_RES - m_pOrganPipeModel->GetLengthTube(0);
	m_SliderL1.SetPos(LENGTH_RES - (int) fValue);
	fValue /= (MY_FLOAT) LENGTH_RES;
	m_PipeEditCtrl.SetLength(0, fValue);
	UpdateText(IDC_TEXT_L1, "L1", fValue, "");

	fValue = (MY_FLOAT) LENGTH_RES - m_pOrganPipeModel->GetLengthTube(1);
	m_SliderL2.SetPos(LENGTH_RES - (int) fValue);
	fValue /= (MY_FLOAT) LENGTH_RES;
	m_PipeEditCtrl.SetLength(1, fValue);
	UpdateText(IDC_TEXT_L2, "L2", fValue, "");

	fValue = (MY_FLOAT) LENGTH_RES - m_pOrganPipeModel->GetLengthTube(2);
	m_SliderL3.SetPos(LENGTH_RES - (int) fValue);
	fValue /= (MY_FLOAT) LENGTH_RES;
	m_PipeEditCtrl.SetLength(2, fValue);
	UpdateText(IDC_TEXT_L3, "L3", fValue, "");

	fValue = (MY_FLOAT) LENGTH_RES - m_pOrganPipeModel->GetLengthTube(3);
	m_SliderL4.SetPos(LENGTH_RES - (int) fValue);
	fValue /= (MY_FLOAT) LENGTH_RES;
	m_PipeEditCtrl.SetLength(3, fValue);
	UpdateText(IDC_TEXT_L4, "L4", fValue, "");

	fValue = (MY_FLOAT) LENGTH_RES - m_pOrganPipeModel->GetLengthTube(4);
	m_SliderL5.SetPos(LENGTH_RES - (int) fValue);
	fValue /= (MY_FLOAT) LENGTH_RES;
	m_PipeEditCtrl.SetLength(4, fValue);
	UpdateText(IDC_TEXT_L5, "L5", fValue, "");

	////////////////////////////////////////////////////////////////////////
	// Sliders for diameters Bore and 3 ToneHoles

	fValue = m_pOrganPipeModel->GetJunctionDiameterBore(0);
	fValue /= (MY_FLOAT) DIAMETER_TONEHOLE;
	m_SliderD1.SetPos((int) DIAMETER_RES * fValue);
	fValue *= (MY_FLOAT) DIAMETER_TONEHOLE;
	ASSERT(fValue >= 0.0);
	ASSERT(fValue <= 1.0);
	m_PipeEditCtrl.SetDiameterBore(0, fValue);
	UpdateText(IDC_TEXT_D1, "D1", fValue, "");

	fValue = m_pOrganPipeModel->GetJunctionDiameterBore(1);
	fValue /= (MY_FLOAT) DIAMETER_TONEHOLE;
	m_SliderD2.SetPos((int) DIAMETER_RES * fValue);
	m_PipeEditCtrl.SetDiameterBore(1, fValue);
	UpdateText(IDC_TEXT_D2, "D2", fValue, "");

	fValue = m_pOrganPipeModel->GetJunctionDiameterBore(2);
	fValue /= (MY_FLOAT) DIAMETER_TONEHOLE;
	m_SliderD3.SetPos((int) DIAMETER_RES * fValue);
	m_PipeEditCtrl.SetDiameterBore(2, fValue);
	UpdateText(IDC_TEXT_D3, "D3", fValue, "");

	fValue = m_pOrganPipeModel->GetJunctionDiameterBore(3);
	fValue /= (MY_FLOAT) DIAMETER_TONEHOLE;
	m_SliderD4.SetPos((int) DIAMETER_RES * fValue);
	m_PipeEditCtrl.SetDiameterBore(3, fValue);
	UpdateText(IDC_TEXT_D4, "D4", fValue, "");

	m_PipeEditCtrl.Invalidate();

	return CPropertyPage::OnSetActive();
}

BOOL CLinearPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL CLinearPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	// TODO: Add extra initialization here
	CRect rect;
	GetDlgItem(IDC_PIPEEDITCTRL)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_PipeEditCtrl.SubclassDlgItem(IDC_PIPEEDITCTRL, this);

	m_SliderL1.SetRange(1, LENGTH_RES);
	m_SliderL2.SetRange(1, LENGTH_RES);
	m_SliderL3.SetRange(1, LENGTH_RES);
	m_SliderL4.SetRange(1, LENGTH_RES);
	m_SliderL5.SetRange(1, LENGTH_RES);

	m_SliderD1.SetRange(1, DIAMETER_RES);
	m_SliderD2.SetRange(1, DIAMETER_RES);
	m_SliderD3.SetRange(1, DIAMETER_RES);
	m_SliderD4.SetRange(1, DIAMETER_RES);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CLinearPropPage::UpdateText(int nID, CString strName, float fValue, CString strUnit) 
{
	CString str;
	float fValue1;
	fValue1 = fValue - (float)(((int)(fValue)));
	if(fValue1 == 0.0)
	{
		str.Format("%s: %4.0f %s", strName, fValue, strUnit);
	}
	else
	{
		str.Format("%s: %4.3f %s", strName, fValue, strUnit);
	}
	ASSERT(nID);
	SetDlgItemText(nID, str);
}

void CLinearPropPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSliderCtrl;
	pSliderCtrl = (CSliderCtrl*) pScrollBar;
	MY_FLOAT fSliderValue = (MY_FLOAT)(pSliderCtrl->GetPos());
	MY_FLOAT fSliderValueLengthTube = fSliderValue;
	fSliderValue = (MY_FLOAT) LENGTH_RES - fSliderValue;
	fSliderValue /= (MY_FLOAT) LENGTH_RES;
	//TRACE("SliderValue %f\n", fSliderValue);

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
				if(pSliderCtrl == GetDlgItem(IDC_SLIDERL1))
				{
					m_pOrganPipeModel->SetLengthTube(0, fSliderValueLengthTube);
					m_PipeEditCtrl.SetLength(0, fSliderValue);
					UpdateText(IDC_TEXT_L1, "L1", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERL2))
				{
					m_pOrganPipeModel->SetLengthTube(1, fSliderValueLengthTube);
					m_PipeEditCtrl.SetLength(1, fSliderValue);
					UpdateText(IDC_TEXT_L2, "L2", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERL3))
				{
					m_pOrganPipeModel->SetLengthTube(2, fSliderValueLengthTube);
					m_PipeEditCtrl.SetLength(2, fSliderValue);
					UpdateText(IDC_TEXT_L3, "L3", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERL4))
				{
					m_pOrganPipeModel->SetLengthTube(3, fSliderValueLengthTube);
					m_PipeEditCtrl.SetLength(3, fSliderValue);
					UpdateText(IDC_TEXT_L4, "L4", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERL5))
				{
					m_pOrganPipeModel->SetLengthTube(4, fSliderValueLengthTube);
					m_PipeEditCtrl.SetLength(4, fSliderValue);
					UpdateText(IDC_TEXT_L5, "L5", fSliderValue, "");
				}
			}
			m_PipeEditCtrl.Invalidate();
			break;
		default:
			break;
	}
	
	//float fLength = m_pOrganPipeModel->GetLengthTube(0) +
	//					m_pOrganPipeModel->GetLengthTube(1);
	//TRACE("Length %f\n", fLength);

	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CLinearPropPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSliderCtrl;
	pSliderCtrl = (CSliderCtrl*) pScrollBar;
	MY_FLOAT fSliderValue = (MY_FLOAT)(pSliderCtrl->GetPos());
	fSliderValue /= (MY_FLOAT) DIAMETER_RES;

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
				if(pSliderCtrl == GetDlgItem(IDC_SLIDERD1))
				{
/*
					m_PipeEditCtrl.SetDiameter(0, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterLeft(fSliderValue);
*/
					m_PipeEditCtrl.SetDiameterBore(0, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterBore(0, fSliderValue);
					UpdateText(IDC_TEXT_D1, "D1", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERD2))
				{
/*
					m_PipeEditCtrl.SetDiameter(1, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterLeft(fSliderValue);
*/
					m_PipeEditCtrl.SetDiameterBore(1, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterBore(1, fSliderValue);
					UpdateText(IDC_TEXT_D2, "D2", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERD3))
				{
					m_PipeEditCtrl.SetDiameterBore(2, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterBore(2, fSliderValue);
					UpdateText(IDC_TEXT_D3, "D3", fSliderValue, "");
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERD4))
				{
					m_PipeEditCtrl.SetDiameterBore(3, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterBore(3, fSliderValue);
					UpdateText(IDC_TEXT_D4, "D4", fSliderValue, "");
				}
				//
				// D5 is the diameter of the ToneHole
				//
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDERD5))
				{
					m_PipeEditCtrl.SetDiameterBore(4, (MY_FLOAT) fSliderValue);
					m_pOrganPipeModel->SetJunctionDiameterBore(4, fSliderValue);
					UpdateText(IDC_TEXT_D5, "ToneHole", fSliderValue, "");
				}
			}
			m_PipeEditCtrl.Invalidate();
			break;
		default:
			break;
	}
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

