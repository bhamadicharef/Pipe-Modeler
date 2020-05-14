// TwoZero.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TwoZero.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTwoZero

IMPLEMENT_DYNAMIC(CTwoZero, CFilter)

CTwoZero::CTwoZero() : CFilter()
{
	ASSERT_VALID(this);
    m_pfInputs = (MY_FLOAT *) malloc(2 * MY_FLOAT_SIZE);
    m_fZeroCoef[0] = (MY_FLOAT) 0.0;
    m_fZeroCoef[1] = (MY_FLOAT) 0.0;
    m_fGain = (MY_FLOAT) 1.0;
	this->Clear();
}

CTwoZero::~CTwoZero()
{
    free(m_pfInputs);
}

/////////////////////////////////////////////////////////////////////////////
// CTwoZero serialization

void CTwoZero::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fZeroCoef[0];
		ar << m_fZeroCoef[1];
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fZeroCoef[0];
		ar >> m_fZeroCoef[1];
	}
}

#ifdef _DEBUG
void CTwoZero::Dump( CDumpContext& dc ) const
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
// CTwoZero Observators

/////////////////////////////////////////////////////////////////////////////
// CTwoZero Functions

void CTwoZero::Clear()
{
    m_pfInputs[0] = (MY_FLOAT) 0.0;
    m_pfInputs[1] = (MY_FLOAT) 0.0;
    m_fLastOutput = (MY_FLOAT) 0.0;
}

void CTwoZero::SetZeroCoef(int nCoef, MY_FLOAT fCoefValue)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < 2);
    m_fZeroCoef[nCoef] = fCoefValue;
}

void CTwoZero::SetGain(MY_FLOAT fGain)
{
    m_fGain = fGain;
}

MY_FLOAT CTwoZero::Tick(MY_FLOAT fSample)
{
	m_fLastOutput = m_fZeroCoef[0] * m_pfInputs[0];
	m_fLastOutput += m_fZeroCoef[1] * m_pfInputs[1];
	m_pfInputs[1] = m_pfInputs[0];
	m_pfInputs[0] = m_fGain * fSample;
    m_fLastOutput += m_pfInputs[0];
    return m_fLastOutput;
}

