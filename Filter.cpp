// Filter.cpp : implementation file
//

#include "stdafx.h"
#include "Filter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilter

IMPLEMENT_DYNAMIC(CFilter, CObject)

CFilter::CFilter()
{
	ASSERT_VALID(this);
	//TRACE("INFOS: New CFilter\n");
}


CFilter::~CFilter()
{
	//TRACE("INFOS: Delete CFilter\n");
}

#ifdef _DEBUG
void CFilter::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "Test Dump: " <<
//		<< "Midi LowKey:   " << m_cLowKey << "\n"
//		<< "Midi HighKey:  " << m_cHighKey;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilter Observators

/////////////////////////////////////////////////////////////////////////////
// CFilter Functions

MY_FLOAT CFilter::LastOut()
{
	return m_fLastOutput;
}

/////////////////////////////////////////////////////////////////////////////
// CFilter serialization

void CFilter::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		//TRACE("INFOS: Save CModel\n");
		// TODO: add storing code here
		//ar << m_Value;		//
	}
	else
	{
		//TRACE("INFOS: Load CModel\n");
		// TODO: add loading code here
		//ar >> m_Value;		//
	}
#ifdef _DEBUG
	//TRACE("INFOS: CFilter: \n");
#endif
}

