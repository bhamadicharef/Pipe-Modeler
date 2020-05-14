// OneZero.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OneZero.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COneZero

IMPLEMENT_DYNAMIC(COneZero, CFilter)

COneZero::COneZero() : CFilter()
{
	ASSERT_VALID(this);
    m_fGain = (MY_FLOAT) 1.0;
    m_fZeroCoeff = (MY_FLOAT) 1.0;
    m_fSGain = (MY_FLOAT) 0.5;
    m_pfInputs = (MY_FLOAT *) malloc(MY_FLOAT_SIZE);
	this->Clear();
}

COneZero::~COneZero()
{
	ASSERT(this);
    free(m_pfInputs);
}

/////////////////////////////////////////////////////////////////////////////
// COneZero serialization

void COneZero::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fZeroCoeff;
		ar << m_fSGain;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fZeroCoeff;
		ar >> m_fSGain;
	}
}

#ifdef _DEBUG
void COneZero::Dump( CDumpContext& dc ) const
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
// COneZero Observators

/////////////////////////////////////////////////////////////////////////////
// COneZero Functions

void COneZero::Clear()
{
	ASSERT(this);
    m_pfInputs[0] = (MY_FLOAT) 0.0;
    m_fLastOutput = (MY_FLOAT) 0.0;
}

void COneZero::SetZero(MY_FLOAT fZero)
{
	ASSERT(this);
    m_fZeroCoeff = fZero;
	// Normalize gain to 1.0 max
    if(m_fZeroCoeff > 0.0)
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 + m_fZeroCoeff);
	}
    else
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 - m_fZeroCoeff);
	}
}

void COneZero::SetGain(MY_FLOAT fGain)
{
	ASSERT(this);
    m_fGain = fGain;
	// Normalize gain to 1.0 max
    if(m_fZeroCoeff > 0.0)
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 + m_fZeroCoeff);
	}
    else
	{
		m_fSGain = m_fGain * ((MY_FLOAT) 1.0 - m_fZeroCoeff);
	}
}

MY_FLOAT COneZero::Tick(MY_FLOAT fSample)
{
	ASSERT(this);
	MY_FLOAT fTemp;
	fTemp = m_fSGain * fSample;
    m_fLastOutput = (m_fZeroCoeff * m_pfInputs[0]) + fTemp;
    m_pfInputs[0] = fTemp;
    return m_fLastOutput;
}

MY_FLOAT COneZero::LastOut()
{
    return m_fLastOutput;
}

