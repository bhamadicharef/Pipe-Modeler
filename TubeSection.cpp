// TubeSection.cpp : implementation file
//

#include "stdafx.h"
#include "TubeSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTubeSection

IMPLEMENT_DYNAMIC(CTubeSection, CObject)

CTubeSection::CTubeSection()
{
	ASSERT_VALID(this);

	//                UpperDLineL
	// fLeftInput  >-[___________] -> m_fRightOutput
	//
	//                LowerDLineL
	// fLeftOutput <-[___________] -< m_fRightInput
	//

	m_pUpperDLineL = new CDLineL(DLINEL_MAX);
	m_pLowerDLineL = new CDLineL(DLINEL_MAX);
	m_fLength = DLINEL_MAX;
	this->Clear();
}

CTubeSection::~CTubeSection()
{
	delete m_pUpperDLineL;
	delete m_pLowerDLineL;
}

void CTubeSection::Clear()
{
	m_pUpperDLineL->Clear();
	m_pLowerDLineL->Clear();
	m_fOutputLeft = (MY_FLOAT) 0.0;
	m_fOutputRight = (MY_FLOAT) 0.0;
}
/////////////////////////////////////////////////////////////////////////////
// CTubeSection serialization

void CTubeSection::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fLength;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fLength;
	}
}

#ifdef _DEBUG
void CTubeSection::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "TubeSection: Value: " << m_Value << "\n"
//		<< "TubeSection: Target: " << m_Target << "\n"
//		<< "TubeSection: Rate: " << m_Rate << "\n"
//		<< "TubeSection: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CTubeSection Observators

/////////////////////////////////////////////////////////////////////////////
// CTubeSection Functions

void CTubeSection::SetLength(MY_FLOAT fLength)
{
	ASSERT_VALID(this);
	ASSERT(fLength >= 0);
	ASSERT(fLength < 1000);
	m_pUpperDLineL->SetDelay(fLength / 2);
	m_pLowerDLineL->SetDelay(fLength / 2);
	m_fLength = fLength;
}

void CTubeSection::Tick(MY_FLOAT fInputLeft, MY_FLOAT fInputRight)
{
	ASSERT_VALID(this);

	//                UpperDLineL
	// fLeftInput  >-[___________] -> m_fRightOutput
	//
	//                LowerDLineL
	// fLeftOutput <-[___________] -< m_fRightInput
	//

	if(m_fLength == 0.0)
	{
		m_fOutputRight = fInputLeft;
		m_fOutputLeft =	fInputRight;
	}
	else
	{
		m_fOutputRight =	m_pUpperDLineL->Tick(fInputLeft);
		m_fOutputLeft =		m_pLowerDLineL->Tick(fInputRight);
	}
}

/*

  TEST

  	CTubeSection TubeSection;

	TubeSection.SetLength(16);
	MY_FLOAT fTempLeft, fTempRight;

	fTempRight = (MY_FLOAT) 0.0;

	for(int i = 0; i < 100; i++ )
	{
		TubeSection.Tick((MY_FLOAT) i, (MY_FLOAT) (100 - i));
		TRACE("-> %f [    ] -> %f\n", fTempLeft, TubeSection.LastRightOut());
		TRACE("<- %f [    ] <- %f\n\n", TubeSection.LastLeftOut(), fTempRight);
	}

*/

