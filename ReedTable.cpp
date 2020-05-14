// ReedTable.cpp : implementation file
//

#include "stdafx.h"
#include "ReedTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReedTable

IMPLEMENT_DYNAMIC(CReedTable, CObject)

CReedTable::CReedTable()
{
	ASSERT_VALID(this);
	m_fOffset		= (MY_FLOAT) 0.6;
	m_fSlope		= (MY_FLOAT) -0.8;
	m_fLastOutput	= (MY_FLOAT) 0.0;
}

CReedTable::~CReedTable()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CReedTable::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fOffset;
		ar << m_fSlope;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fOffset;
		ar >> m_fSlope;
	}
}

#ifdef _DEBUG
void CReedTable::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CReedTable Observators

/////////////////////////////////////////////////////////////////////////////
// CReedTable Functions

void CReedTable::SetOffset(MY_FLOAT fOffset)
{
	m_fOffset = fOffset;
	//TRACE("New ReedTable Offset = %f\n", m_fOffset);
}

void CReedTable::SetSlope(MY_FLOAT fSlope)
{
	m_fSlope = fSlope;
	//TRACE("New ReedTable Slope = %f\n", m_fSlope);
}

MY_FLOAT CReedTable::Tick(MY_FLOAT fSample)
{
	m_fLastOutput = m_fOffset + (fSample * fSample);
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

MY_FLOAT CReedTable::LastOut()
{
	return m_fLastOutput;
}

