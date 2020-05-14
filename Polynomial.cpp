// Polynomial.cpp : implementation file
//

#include "stdafx.h"
#include "Polynomial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolynomial

IMPLEMENT_DYNAMIC(CPolynomial, CObject)

CPolynomial::CPolynomial()
{
	ASSERT_VALID(this);
	m_nN = 8;
	for(int i = 0; i < m_nN; i++)
	{
		m_fCoef[i] = 0.0;
		m_fOldCoef[i] = m_fCoef[i];
	}
	m_fCoef[1] = 1.0;
	m_fOldCoef[1] = m_fCoef[1];
}

CPolynomial::~CPolynomial()
{
}

void CPolynomial::Clear()
{
//	this->ClearCoefs();
//	this->ClearOldCoefs();
}

void CPolynomial::ClearCoefs()
{
	for(int i = 0; i < this->GetN(); i++)
	{
		m_fCoef[i] = 0.0;
	}
}

void CPolynomial::ClearOldCoefs()
{
	for(int i = 0; i < this->GetN(); i++)
	{
		m_fOldCoef[i] = 0.0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPolynomial serialization

void CPolynomial::Serialize(CArchive& ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nN;
		for(i = 0; i < m_nN; i++)
		{
			ar << m_fCoef[i];
			ar << m_fOldCoef[i];
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nN;
		for(i = 0; i < m_nN; i++)
		{
			ar >> m_fCoef[i];
			ar >> m_fOldCoef[i];
		}
	}
}

#ifdef _DEBUG
void CPolynomial::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "Polynomial: Value: " << m_Value << "\n"
//		<< "Polynomial: Target: " << m_Target << "\n"
//		<< "Polynomial: Rate: " << m_Rate << "\n"
//		<< "Polynomial: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CPolynomial Observators

/////////////////////////////////////////////////////////////////////////////
// CPolynomial Functions

void CPolynomial::SetN(int nN)
{
	ASSERT(nN > 0);
	ASSERT(nN <= 8);
	m_nN = nN;
	this->Clear();
}

int CPolynomial::GetN()
{
	return m_nN;
}

float CPolynomial::GetCoef(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fCoef[nCoef]);
}

float CPolynomial::GetOldCoef(int nCoef)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	return (m_fOldCoef[nCoef]);
}

void CPolynomial::SetCoef(int nCoef, float fValue)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	ASSERT(fValue >= -1.0);
	ASSERT(fValue <= 1.0);
	m_fCoef[nCoef] = fValue;
}

void CPolynomial::SetOldCoef(int nCoef, float fValue)
{
	ASSERT(nCoef >= 0);
	ASSERT(nCoef < m_nN);
	ASSERT(fValue >= -1.0);
	ASSERT(fValue <= 1.0);
	m_fOldCoef[nCoef] = fValue;
}

void CPolynomial::SetLinear()
{
	this->ClearCoefs();
	// Slit Function
	this->SetCoef(1, (float) 1.0);
}

void CPolynomial::SetSlit()
{
	this->ClearCoefs();
	// Slit Function
	this->SetCoef(1, (float) -0.57);
	this->SetCoef(2, (float) -0.0);
	this->SetCoef(3, (float) 0.69);
//	this->SetCoef(1, (float) -0.433);
//	this->SetCoef(2, (float) -0.582);
//	this->SetCoef(3, (float) -0.164);
}

void CPolynomial::SetCook()
{
	this->ClearCoefs();
	// Slit Function
	this->SetCoef(1, (float) -1.0);
	this->SetCoef(3, (float) 1.0);
}

///////////////////////////////////////////////////////////////////////////

float CPolynomial::Tick(float fValue)
{
//	ASSERT(fValue >= -2.0);
//	ASSERT(fValue <= 2.0);
	float fResult;
	fResult =	m_fCoef[0] + fValue *
				(m_fCoef[1] + fValue *
				(m_fCoef[2] + fValue *
				(m_fCoef[3] + fValue *
				(m_fCoef[4] + fValue *
				(m_fCoef[5] + fValue *
				(m_fCoef[6] + (fValue *
				m_fCoef[7])))))));
	if(fResult > 1.0)
	{
		fResult = 1.0;
	}
	if(fResult < -1.0)
	{
		fResult = -1.0;
	}	return fResult;
}

float CPolynomial::TickOld(float fValue)
{
	ASSERT(fValue >= -1.0);
	ASSERT(fValue <= 1.0);
	float fResult;
	fResult =	m_fOldCoef[0] + fValue *
				(m_fOldCoef[1] + fValue *
				(m_fOldCoef[2] + fValue *
				(m_fOldCoef[3] + fValue *
				(m_fOldCoef[4] + fValue *
				(m_fOldCoef[5] + fValue *
				(m_fOldCoef[6] + (fValue *
				m_fOldCoef[7])))))));
	if(fResult > 1.0)
	{
		fResult = 1.0;
	}
	if(fResult < -1.0)
	{
		fResult = -1.0;
	}
	return fResult;
}

