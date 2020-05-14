// DLineL.cpp : implementation file
// 

#include "stdafx.h"
#include "DLineL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLineL

IMPLEMENT_DYNAMIC(CDLineL, CObject)

CDLineL::CDLineL(long max_length)
{
	ASSERT_VALID(this);
	//TRACE("INFOS: New CModel\n");
	ASSERT(max_length <= DLINEL_MAX);
    m_nLength = max_length;
    m_pfInputs = (MY_FLOAT *) malloc(m_nLength * MY_FLOAT_SIZE);
    this->Clear();
    m_nOutPoint = 0;
    m_nInPoint = m_nLength >> 1;
}

CDLineL::~CDLineL()
{
	//TRACE("INFOS: Delete CDLineL\n");
	free(m_pfInputs);
}

#ifdef _DEBUG
void CDLineL::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "Test Dump: " <<
//		<< "Midi LowKey:   " << m_cLowKey << "\n"
//		<< "Midi HighKey:  " << m_cHighKey;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLineL Observators

/////////////////////////////////////////////////////////////////////////////
// CDLineL Functions

void CDLineL::Clear()
{
	for(long i = 0; i < m_nLength; i++)
	{
		m_pfInputs[i] = 0.0;
	}
	m_fLastOutput = (MY_FLOAT) 0.0;
}

void CDLineL::SetDelay(MY_FLOAT flag)
{
	MY_FLOAT outputPointer;
	// read chases write, add 1 for interpolation
	outputPointer = m_nInPoint - flag;
	
	while (outputPointer < 0)
	{
		// modulo maximum length
		outputPointer += m_nLength;
	}
	// integer part
	m_nOutPoint = (long) outputPointer;
	// fractional part
	m_fAlpha = outputPointer - m_nOutPoint;
	// 1.0 - fractional part (more efficient)
	m_fOmAlpha = (MY_FLOAT) 1.0 - m_fAlpha;
}

// Take one, yield one
MY_FLOAT CDLineL::Tick(MY_FLOAT sample)
{
	ASSERT(this);
	ASSERT(m_pfInputs != NULL);

	// Input next sample
	m_pfInputs[m_nInPoint++] = sample;
	// Check for end condition
	if(m_nInPoint == m_nLength)
	{
		m_nInPoint -= m_nLength;
	}
	//first 1/2 of interpolation
	m_fLastOutput = m_pfInputs[m_nOutPoint++] * m_fOmAlpha;
	// Check for end condition
	if(m_nOutPoint < m_nLength)
	{
		m_fLastOutput += m_pfInputs[m_nOutPoint] * m_fAlpha;	// second 1/2 of interpolation
    }                                          
    else
	{
		// if at end ...
		m_fLastOutput += m_pfInputs[0] * m_fAlpha;		// second 1/2 of interpolation
		m_nOutPoint -= m_nLength;                             
	}
    return m_fLastOutput;
}

/////////////////////////////////////////////////////////////////////////////
// CDLineL serialization

void CDLineL::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		//TRACE("INFOS: Save CDLineL\n");
		// TODO: add storing code here
		ar << 	m_nInPoint;
		ar << 	m_nOutPoint;
		ar << 	m_nLength;
		ar << 	m_fAlpha;
		ar << 	m_fOmAlpha;
	}
	else
	{
		//TRACE("INFOS: Load CDLineL\n");
		// TODO: add loading code here
		ar >> 	m_nInPoint;
		ar >> 	m_nOutPoint;
		ar >> 	m_nLength;
		ar >> 	m_fAlpha;
		ar >> 	m_fOmAlpha;
	}
#ifdef _DEBUG
	//TRACE("INFOS: CDLineL: \n");
#endif
}

