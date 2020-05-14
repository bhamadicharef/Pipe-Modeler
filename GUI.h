// GUI.h : main header file for the GUI application
//

#if !defined(AFX_GUI_H__D17EA806_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_GUI_H__D17EA806_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "mmsystem.h"
#include "HyperLink.h"
#include "SBDestination.h"

#include "TKObject.h"
#include "Model.h"
#include "OrganPipeModel.h"

#include "WaveEditCtrlEx.h"
#include "PipeEditCtrl.h"
#include "PipeEditCtrl2.h"
#include "CurveEditCtrl.h"
#include "WaveEditCtrl.h"

#include "FftEditCtrl.h"
#include "FFT.h"

#include "FirstPropPage.h"
#include "ExcitationPropPage.h"
#include "OtherPropPage.h"
#include "NonLinearPropPage.h"
#include "LinearPropPage.h"
#include "OutputPropPage.h"
#include "WaveformPropPage.h"
#include "SpectrumPropPage.h"
#include "FilesPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CGUIApp:
// See GUI.cpp for the implementation of this class
//

class CGUIApp : public CWinApp
{
public:
	CGUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_H__D17EA806_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
