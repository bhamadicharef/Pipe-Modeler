// Noise.cpp : implementation file
//

#include "stdafx.h"
#include "Noise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoise

IMPLEMENT_DYNAMIC(CNoise, CObject)

CNoise::CNoise()
{
	ASSERT_VALID(this);
	CTime t = CTime::GetCurrentTime();
	srand(t.GetSecond());
	m_fLastOutput = 0.0;
}

CNoise::~CNoise()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CNoise::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar << m_ReleaseRate;
	}
	else
	{
		// TODO: add loading code here
		//ar >> m_ReleaseRate;
	}
}

#ifdef _DEBUG
void CNoise::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CNoise Observators

/////////////////////////////////////////////////////////////////////////////
// CNoise Functions

MY_FLOAT CNoise::Tick()
{
	// RAND_MAX = 0x7FFF;
    m_fLastOutput = (MY_FLOAT) rand();
	m_fLastOutput -= (MY_FLOAT) RAND_MAX_OVER_TWO;
    m_fLastOutput *= (MY_FLOAT) ONE_OVER_RANDLIMIT;
	return m_fLastOutput;
}

MY_FLOAT CNoise::LastOut()
{
	return m_fLastOutput;
}

