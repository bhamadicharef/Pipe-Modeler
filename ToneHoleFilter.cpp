// ToneHoleFilter.cpp : implementation file
//

#include "stdafx.h"
#include "ToneHoleFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToneHoleFilter

IMPLEMENT_DYNAMIC(CToneHoleFilter, CFilter)

CToneHoleFilter::CToneHoleFilter()
{
	ASSERT_VALID(this);
    m_pfOutputs = (MY_FLOAT *) malloc(MY_FLOAT_SIZE); 	// y(n-1)
    Clear();
}

CToneHoleFilter::~CToneHoleFilter()
{
    free(m_pfOutputs);
}

/////////////////////////////////////////////////////////////////////////////
// CToneHoleFilter serialization

void CToneHoleFilter::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar << m_Inputs[0];
	}
	else
	{
		// TODO: add loading code here
		//ar >> m_AttackRate;
	}
}

#ifdef _DEBUG
void CToneHoleFilter::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: Target: " << m_Target << "\n"
//		<< "ADSR: Rate: " << m_Rate << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CToneHoleFilter Observators

/////////////////////////////////////////////////////////////////////////////
// CToneHoleFilter Functions

void CToneHoleFilter::SetToneHoleCoef(MY_FLOAT fToneHoleCoef)
{
	ASSERT(fToneHoleCoef <= 0);
    m_fToneHoleCoef = fToneHoleCoef;
}

void CToneHoleFilter::Clear()
{
    m_pfOutputs[0]	= (MY_FLOAT) 0.0;	// y(n-1)
    m_fLastOutput	= (MY_FLOAT) 0.0;
}

MY_FLOAT CToneHoleFilter::Tick(MY_FLOAT fSample)
{
    m_pfOutputs[0] = - fSample * (1 + m_fToneHoleCoef) - (m_fToneHoleCoef * m_pfOutputs[0]);
    m_fLastOutput = m_pfOutputs[0];
    return m_fLastOutput;
}

MY_FLOAT CToneHoleFilter::LastOut()
{
    return m_fLastOutput;
}
