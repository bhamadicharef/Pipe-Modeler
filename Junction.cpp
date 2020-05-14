// Junction.cpp : implementation file
//

#include "stdafx.h"
#include "Junction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJunction

IMPLEMENT_DYNAMIC(CJunction, CObject)

CJunction::CJunction()
{
	ASSERT_VALID(this);
	m_fDiameterLeft = (MY_FLOAT) 1.0;
	m_fDiameterRight = (MY_FLOAT) 0.5;
	CalculateJunctionCoef();
	this->Clear();
}

CJunction::~CJunction()
{
}

void CJunction::Clear()
{
	m_fOutputLeft = (MY_FLOAT) 0.0;
	m_fOutputRight = (MY_FLOAT) 0.0;
}

/////////////////////////////////////////////////////////////////////////////
// CJunction serialization

void CJunction::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fDiameterLeft;
		ar << m_fDiameterRight;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fDiameterLeft;
		ar >> m_fDiameterRight;
	}
}

#ifdef _DEBUG
void CJunction::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "Junction: Value: " << m_Value << "\n"
//		<< "Junction: Target: " << m_Target << "\n"
//		<< "Junction: Rate: " << m_Rate << "\n"
//		<< "Junction: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CJunction Observators

/////////////////////////////////////////////////////////////////////////////
// CJunction Functions

void CJunction::SetDiameterLeft(MY_FLOAT fDiameterLeft)
{
	ASSERT_VALID(this);
	ASSERT(fDiameterLeft >= 0);
	ASSERT(fDiameterLeft < 1000);
	m_fDiameterLeft = fDiameterLeft;
	CalculateJunctionCoef();
}

void CJunction::SetDiameterRight(MY_FLOAT fDiameterRight)
{
	ASSERT_VALID(this);
	ASSERT(fDiameterRight >= 0);
	ASSERT(fDiameterRight < 1000);
	m_fDiameterRight = fDiameterRight;
	CalculateJunctionCoef();
}

void CJunction::CalculateJunctionCoef()
{
	ASSERT_VALID(this);
	MY_FLOAT fDiameterLeft2 = m_fDiameterLeft * m_fDiameterLeft;
	MY_FLOAT fDiameterRight2 = m_fDiameterRight * m_fDiameterRight;
	m_fJunctionCoef =	(fDiameterLeft2 - fDiameterRight2) /
						(fDiameterLeft2 + fDiameterRight2);
	TRACE("JunctionCoef = %f\n", m_fJunctionCoef);
}

// Ref: Vesa Thesis page 39, Fig 2.8 a)
void CJunction::Tick(MY_FLOAT fInputLeft, MY_FLOAT fInputRight)
{
	ASSERT_VALID(this);
	m_fOutputRight =	(fInputLeft * (1 + m_fJunctionCoef)) - 
						(fInputRight * m_fJunctionCoef);
	m_fOutputLeft =		(fInputRight * (1 - m_fJunctionCoef)) +
						(fInputLeft * m_fJunctionCoef);
}

// Ref: Vesa Thesis page 39, Fig 2.8 b)
/*
void CJunction::TickJunction(float fLeftInput, float fRightInput)
{
	ASSERT_VALID(this);
	
	float fTemp;

	fTemp = m_fJunctionCoef * (fLeftInput - fRightInput);
	m_fRightOutput = fTemp + fLeftInput;
	m_fLeftOutput = fTemp + fRightInput;
}
*/