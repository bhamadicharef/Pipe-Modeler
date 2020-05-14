// NonLinearPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "NonLinearPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNonLinearPropPage property page

IMPLEMENT_DYNCREATE(CNonLinearPropPage, CPropertyPage)

CNonLinearPropPage::CNonLinearPropPage() : CPropertyPage(CNonLinearPropPage::IDD)
{
	//{{AFX_DATA_INIT(CNonLinearPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*
	DDX_Control(pDX, IDC_SLIDER_NL8, m_SliderNonLinear8);
	DDX_Control(pDX, IDC_SLIDER_NL7, m_SliderNonLinear7);
	DDX_Control(pDX, IDC_SLIDER_NL6, m_SliderNonLinear6);
	DDX_Control(pDX, IDC_SLIDER_NL5, m_SliderNonLinear5);
	DDX_Control(pDX, IDC_SLIDER_NL4, m_SliderNonLinear4);
	DDX_Control(pDX, IDC_SLIDER_NL3, m_SliderNonLinear3);
	DDX_Control(pDX, IDC_SLIDER_NL2, m_SliderNonLinear2);
	DDX_Control(pDX, IDC_SLIDER_NL1, m_SliderNonLinear1);

*/

CNonLinearPropPage::~CNonLinearPropPage()
{
}

void CNonLinearPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNonLinearPropPage)
	DDX_Control(pDX, IDC_SLIDER_NL8, m_SliderNonLinear8);
	DDX_Control(pDX, IDC_SLIDER_NL7, m_SliderNonLinear7);
	DDX_Control(pDX, IDC_SLIDER_NL6, m_SliderNonLinear6);
	DDX_Control(pDX, IDC_SLIDER_NL5, m_SliderNonLinear5);
	DDX_Control(pDX, IDC_SLIDER_NL4, m_SliderNonLinear4);
	DDX_Control(pDX, IDC_SLIDER_NL3, m_SliderNonLinear3);
	DDX_Control(pDX, IDC_SLIDER_NL2, m_SliderNonLinear2);
	DDX_Control(pDX, IDC_SLIDER_NL1, m_SliderNonLinear1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNonLinearPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNonLinearPropPage)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_LINEAR, OnLinear)
	ON_BN_CLICKED(IDC_COOK, OnCook)
	ON_BN_CLICKED(IDC_SLIT, OnSlit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNonLinearPropPage message handlers

BOOL CNonLinearPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetModified();
	return CPropertyPage::OnSetActive();
}

BOOL CNonLinearPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	// Stop 
	return CPropertyPage::OnKillActive();
}

BOOL CNonLinearPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	CRect rect;
	GetDlgItem(IDC_CURVEEDITCTRL)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_CurveEditCtrl.SubclassDlgItem(IDC_CURVEEDITCTRL, this);

	m_CurveEditCtrl.m_pPolynomial = (CPolynomial*) &(m_pOrganPipeModel->m_Polynomial);

	m_SliderNonLinear1.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear2.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear3.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear4.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear5.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear6.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear7.SetRange(0, SLIDER_MAX);
	m_SliderNonLinear8.SetRange(0, SLIDER_MAX);

	m_CurveEditCtrl.m_pPolynomial->SetCook();
	UpdateSlidersNonLinear();
	UpdateTextNonLinear();	
	m_CurveEditCtrl.Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CNonLinearPropPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
				if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL1))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(0, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(0, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
					//TRACE("Coef(0) = %f\n", m_CurveEditCtrl.GetCoef(0));
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL2))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(1, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(1, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL3))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(2, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(2, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL4))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(3, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(3, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL5))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(4, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(4, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL6))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(5, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(5, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL7))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(6, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(6, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
				else if(pSliderCtrl == GetDlgItem(IDC_SLIDER_NL8))
				{
					fSliderValue = (MY_FLOAT)(SLIDER_MID - fSliderValue);
					fSliderValue /= (MY_FLOAT)(SLIDER_MID);
					m_pOrganPipeModel->m_Polynomial.SetCoef(7, fSliderValue);
					m_CurveEditCtrl.m_pPolynomial->SetCoef(7, fSliderValue);
					m_CurveEditCtrl.Invalidate();
					UpdateTextNonLinear();	
				}
			}
			break;
		default:
			break;
	}
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CNonLinearPropPage::UpdateSlidersNonLinear()
{
	m_SliderNonLinear1.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(0))));
	m_SliderNonLinear2.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(1))));
	m_SliderNonLinear3.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(2))));
	m_SliderNonLinear4.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(3))));
	m_SliderNonLinear5.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(4))));
	m_SliderNonLinear6.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(5))));
	m_SliderNonLinear7.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(6))));
	m_SliderNonLinear8.SetPos((int)(SLIDER_MID * (1 - m_pOrganPipeModel->m_Polynomial.GetCoef(7))));
}

void CNonLinearPropPage::UpdateTextNonLinear() 
{
	CString str;
	CString str2;
	float Coef0 = m_pOrganPipeModel->m_Polynomial.GetCoef(0);
	float Coef1 = m_pOrganPipeModel->m_Polynomial.GetCoef(1);
	float Coef2 = m_pOrganPipeModel->m_Polynomial.GetCoef(2);
	float Coef3 = m_pOrganPipeModel->m_Polynomial.GetCoef(3);
	float Coef4 = m_pOrganPipeModel->m_Polynomial.GetCoef(4);
	float Coef5 = m_pOrganPipeModel->m_Polynomial.GetCoef(5);
	float Coef6 = m_pOrganPipeModel->m_Polynomial.GetCoef(6);
	float Coef7 = m_pOrganPipeModel->m_Polynomial.GetCoef(7);
	
	str.Format("Equ: y = ");

//Coef0
	if(Coef0 != 0.0)
	{
		if(Coef0 == 1.0)
		{
			str2 = "1 ";
			str += str2;
		}
		else if(Coef0 == - 1.0)
		{
			str2 = "- 1 ";
			str += str2;
		}
		else if(Coef0 < 0.0)
		{
			str2.Format("%0.2f ", Coef0);
			str += str2;
		}
		else if(Coef0 > 0.0)
		{
			str2.Format("%0.2f ", Coef0);
			str += str2;
		}
	}

//Coef1
	if(Coef1 != 0.0)
	{
		if(Coef1 == 1.0)
		{
			if(Coef0 == 0)
			{
				str2 = "X ";
			}
			else
			{
				str2 = "+ X ";
			}
			str += str2;
		}
		else if(Coef1 == -1.0)
		{
			str2 = "- X ";
			str += str2;
		}
		else if(Coef1 < 0.0)
		{
			str2.Format("%- 0.2f X ", Coef1);
			str += str2;
		}
		else if(Coef1 > 0.0)
		{
			if(Coef0 == 0)
			{
				str2.Format("%0.2f X ", Coef1);
			}
			else
			{
				str2.Format("+ %0.2f X ", Coef1);
			}
			str += str2;
		}
	}

//Coef2
	if(Coef2 != 0.0)
	{
		if(Coef2 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0))
			{
				str2 = "X^2 ";
			}
			else
			{
				str2 = "+ X^2 ";
			}
			str += str2;
		}
		else if(Coef2 == -1.0)
		{
			str2 = "- X^2 ";
			str += str2;
		}
		else if(Coef2 < 0.0)
		{
			str2.Format("%- 0.2f X^2 ", Coef2);
			str += str2;
		}
		else if(Coef2 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0))
			{
				str2.Format("%0.2f X^2 ", Coef2);
			}
			else
			{
				str2.Format("+ %0.2f X^2 ", Coef2);
			}
			str += str2;
		}
	}

//Coef3
	if(Coef3 != 0.0)
	{
		if(Coef3 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0))
			{
				str2 = "X^3 ";
			}
			else
			{
				str2 = "+ X^3 ";
			}
			str += str2;
		}
		else if(Coef3 == -1.0)
		{
			str2 = "- X^3 ";
			str += str2;
		}
		else if(Coef3 < 0.0)
		{
			str2.Format("%- 0.2f X^3 ", Coef3);
			str += str2;
		}
		else if(Coef3 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0))
			{
				str2.Format("%0.2f X^3 ", Coef3);
			}
			else
			{
				str2.Format("+ %0.2f X^3 ", Coef3);
			}
			str += str2;
		}
	}

//Coef4
	if(Coef4 != 0.0)
	{
		if(Coef4 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0) && (Coef3 == 0.0))
			{
				str2 = "X^4 ";
			}
			else
			{
				str2 = "+ X^4 ";
			}
			str += str2;
		}
		else if(Coef4 == -1.0)
		{
			str2 = "- X^4 ";
			str += str2;
		}
		else if(Coef4 < 0.0)
		{
			str2.Format("%- 0.2f X^4 ", Coef4);
			str += str2;
		}
		else if(Coef4 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0)  && (Coef3 == 0.0))
			{
				str2.Format("%0.2f X^4 ", Coef4);
			}
			else
			{
				str2.Format("+ %0.2f X^4 ", Coef4);
			}
			str += str2;
		}
	}

//Coef5
	if(Coef5 != 0.0)
	{
		if(Coef5 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0) && (Coef3 == 0.0) && 
				(Coef4 == 0.0))
			{
				str2 = "X^5 ";
			}
			else
			{
				str2 = "+ X^5 ";
			}
			str += str2;
		}
		else if(Coef5 == -1.0)
		{
			str2 = "- X^5 ";
			str += str2;
		}
		else if(Coef5 < 0.0)
		{
			str2.Format("%- 0.2f X^5 ", Coef5);
			str += str2;
		}
		else if(Coef5 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0)  && (Coef3 == 0.0)  && 
				(Coef4 == 0.0))
			{
				str2.Format("%0.2f X^5 ", Coef5);
			}
			else
			{
				str2.Format("+ %0.2f X^5 ", Coef5);
			}
			str += str2;
		}
	}


//Coef6
	if(Coef6 != 0.0)
	{
		if(Coef6 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0) && (Coef3 == 0.0) && 
				(Coef4 == 0.0) && (Coef5 == 0.0))
			{
				str2 = "X^6 ";
			}
			else
			{
				str2 = "+ X^6 ";
			}
			str += str2;
		}
		else if(Coef6 == -1.0)
		{
			str2 = "- X^6 ";
			str += str2;
		}
		else if(Coef6 < 0.0)
		{
			str2.Format("%- 0.2f X^6 ", Coef6);
			str += str2;
		}
		else if(Coef6 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0)  && (Coef3 == 0.0)  && 
				(Coef4 == 0.0) && (Coef5 == 0.0))
			{
				str2.Format("%0.2f X^6 ", Coef6);
			}
			else
			{
				str2.Format("+ %0.2f X^6 ", Coef6);
			}
			str += str2;
		}
	}

//Coef7
	if(Coef7 != 0.0)
	{
		if(Coef7 == 1.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0) && (Coef3 == 0.0) && 
				(Coef4 == 0.0) && (Coef5 == 0.0) && (Coef6 == 0.0))
			{
				str2 = "X^7 ";
			}
			else
			{
				str2 = "+ X^7 ";
			}
			str += str2;
		}
		else if(Coef7 == -1.0)
		{
			str2 = "- X^7 ";
			str += str2;
		}
		else if(Coef7 < 0.0)
		{
			str2.Format("%- 0.2f X^7 ", Coef7);
			str += str2;
		}
		else if(Coef7 > 0.0)
		{
			if((Coef0 == 0.0) && (Coef1 == 0.0) && (Coef2 == 0.0)  && (Coef3 == 0.0)  && 
				(Coef4 == 0.0) && (Coef5 == 0.0) && (Coef6 == 0.0))
			{
				str2.Format("%0.2f X^7 ", Coef7);
			}
			else
			{
				str2.Format("+ %0.2f X^7 ", Coef7);
			}
			str += str2;
		}
	}

	if((Coef0 == 0) && (Coef1 == 0) && (Coef2 == 0) && (Coef3 == 0)  && (Coef4 == 0.0)  && 
		(Coef5 == 0.0) && (Coef6 == 0.0) && (Coef7 == 0.0))
	{
		str += "0";
	}
/*
	str.Format("Equ: y = %1.3f + %1.3fx + %1.3fx^2 + %1.3fx^3 + %1.3fx^4 + %1.3fx^5 + %1.3fx^6 + %1.3fx^7",
		m_pOrganPipeModel->m_Polynomial.GetCoef(0),
		m_pOrganPipeModel->m_Polynomial.GetCoef(1),
		m_pOrganPipeModel->m_Polynomial.GetCoef(2),
		m_pOrganPipeModel->m_Polynomial.GetCoef(3),
		m_pOrganPipeModel->m_Polynomial.GetCoef(4),
		m_pOrganPipeModel->m_Polynomial.GetCoef(5),
		m_pOrganPipeModel->m_Polynomial.GetCoef(6),
		m_pOrganPipeModel->m_Polynomial.GetCoef(7));
*/
	SetDlgItemText(IDC_TEXT, str);

}
void CNonLinearPropPage::OnLinear() 
{
	// TODO: Add your control notification handler code here
	m_CurveEditCtrl.m_pPolynomial->SetLinear();
	UpdateSlidersNonLinear();
	UpdateTextNonLinear();	
	m_CurveEditCtrl.Invalidate();
}

void CNonLinearPropPage::OnCook() 
{
	// TODO: Add your control notification handler code here
	m_CurveEditCtrl.m_pPolynomial->SetCook();
	UpdateSlidersNonLinear();
	UpdateTextNonLinear();	
	m_CurveEditCtrl.Invalidate();
}

void CNonLinearPropPage::OnSlit() 
{
	// TODO: Add your control notification handler code here
	m_CurveEditCtrl.m_pPolynomial->SetSlit();
	UpdateSlidersNonLinear();
	UpdateTextNonLinear();	
	m_CurveEditCtrl.Invalidate();
}
