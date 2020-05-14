// OnePole.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OnePole.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnePole

IMPLEMENT_DYNAMIC(COnePole, CFilter)

COnePole::COnePole() : CFilter()
{
	ASSERT_VALID(this);
    m_fPoleCoeff = (MY_FLOAT) 0.9;
    m_fGain = (MY_FLOAT) 1.0;
    m_fSGain = (MY_FLOAT) 0.1;
    m_pfOutputs = (MY_FLOAT *) malloc(MY_FLOAT_SIZE);
    m_pfOutputs[0] = (MY_FLOAT) 0.0;
}

COnePole::~COnePole()
{
    free(m_pfOutputs);
}

/////////////////////////////////////////////////////////////////////////////
// COnePole serialization

void COnePole::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fPoleCoeff;
		ar << m_fSGain;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fPoleCoeff;
		ar >> m_fSGain;
	}
}

#ifdef _DEBUG
void COnePole::Dump( CDumpContext& dc ) const
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
// COnePole Observators

/////////////////////////////////////////////////////////////////////////////
// COnePole Functions

void COnePole::Clear()
{
	ASSERT(this);
    m_pfOutputs[0] = 0.0;
    m_fLastOutput = (MY_FLOAT) 0.0;
}

void COnePole::SetPole(MY_FLOAT fPole)
{
    m_fPoleCoeff = fPole;
	// Normalize gain to 1.0 max
    if(m_fPoleCoeff > 0.0)
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 - m_fPoleCoeff);
	}
    else
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 + m_fPoleCoeff);
	}
}

void COnePole::SetGain(MY_FLOAT fGain)
{
	ASSERT(this);
    m_fGain = fGain;
	// Normalize gain to 1.0 max
    if(m_fPoleCoeff > 0.0)
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 - m_fPoleCoeff);
	}
    else
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 + m_fPoleCoeff);
	}
}

MY_FLOAT COnePole::Tick(MY_FLOAT fSample)
{
	// y(n) = x(n) * Gain + PoleCoef * y(n-1)
    m_pfOutputs[0] = (m_fSGain * fSample) + (m_fPoleCoeff * m_pfOutputs[0]);
    m_fLastOutput = m_pfOutputs[0];
    return m_fLastOutput;
}

MY_FLOAT COnePole::LastOut()
{
    return m_fLastOutput;
}
