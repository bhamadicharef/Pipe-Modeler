// JetTable.cpp : implementation file
//

#include "stdafx.h"
#include "JetTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJetTable

IMPLEMENT_DYNAMIC(CJetTable, CObject)

CJetTable::CJetTable()
{
	ASSERT_VALID(this);
	m_fLastOutput = 0.0;
}

CJetTable::~CJetTable()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CJetTable::Serialize(CArchive& ar)
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
void CJetTable::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CJetTable Observators

/////////////////////////////////////////////////////////////////////////////
// CJetTable Functions

MY_FLOAT CJetTable::Tick(MY_FLOAT fSample)
{

	ASSERT(fSample <= 3.0);
	ASSERT(fSample >= -3.0);
	m_fLastOutput = ((fSample * fSample * fSample * (MY_FLOAT) 0.75) - fSample);
	if(m_fLastOutput > 1.0)
	{
		m_fLastOutput = (MY_FLOAT) 1.0;
	}
	if(m_fLastOutput < -1.0)
	{
		m_fLastOutput = (MY_FLOAT) -1.0;
	}
	return m_fLastOutput;
}

MY_FLOAT CJetTable::LastOut()
{
	return m_fLastOutput;
}

