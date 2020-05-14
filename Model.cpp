// Model.cpp : implementation file
//

#include "stdafx.h"
#include "Model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModel

IMPLEMENT_DYNAMIC(CModel, CObject)

CModel::CModel()
{
	ASSERT_VALID(this);
}

CModel::~CModel()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CModel::Serialize(CArchive& ar)
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
void CModel::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CModel Observators

/////////////////////////////////////////////////////////////////////////////
// CModel Functions

float CModel::Tick()
{
	//TRACE("Asred Noise = %f\n", m_fLastOutput);
	m_WavFileOut.Tick(m_fLastOutput, 0);
	return m_fLastOutput;
}

MY_FLOAT CModel::LastOut()
{
	return m_fLastOutput;
}

void CModel::SaveWavFile(CString strFileName)
{
	m_WavFileOut.Save(strFileName);
}

