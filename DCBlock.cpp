// DCBlock.cpp : implementation file
//

#include "stdafx.h"
#include "DCBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDCBlock

IMPLEMENT_DYNAMIC(CDCBlock, CFilter)

CDCBlock::CDCBlock()
{
	ASSERT_VALID(this);
    m_pfInputs = (MY_FLOAT *) malloc(MY_FLOAT_SIZE);
    m_pfOutputs = (MY_FLOAT *) malloc(MY_FLOAT_SIZE);
    Clear();
}

CDCBlock::~CDCBlock()
{
    free(m_pfInputs);
    free(m_pfOutputs);
}

/////////////////////////////////////////////////////////////////////////////
// CDCBlock serialization

void CDCBlock::Serialize(CArchive& ar)
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
void CDCBlock::Dump( CDumpContext& dc ) const
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
// CDCBlock Observators

/////////////////////////////////////////////////////////////////////////////
// CDCBlock Functions

void CDCBlock::Clear()
{
    m_pfInputs[0]	= (MY_FLOAT) 0.0;
    m_pfOutputs[0]	= (MY_FLOAT) 0.0;
    m_fLastOutput	= (MY_FLOAT) 0.0;
}

MY_FLOAT CDCBlock::Tick(MY_FLOAT fSample)
{
    m_pfOutputs[0] = fSample - m_pfInputs[0] + ((MY_FLOAT) 0.99 * m_pfOutputs[0]);
    m_pfInputs[0] = fSample;
    m_fLastOutput = m_pfOutputs[0];
    return m_fLastOutput;
}

MY_FLOAT CDCBlock::LastOut()
{
    return m_fLastOutput;
}
