// EnvExp.cpp : implementation file
//
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnvExp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnvExp

IMPLEMENT_DYNAMIC(CEnvExp, CObject)

CEnvExp::CEnvExp()
{
	ASSERT_VALID(this);
	Init();
}

CEnvExp::~CEnvExp()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CEnvExp::Init()
{
	ASSERT(this);
	m_nState = ENV_EXP_DECAY;
	this->SetStartLevel((MY_FLOAT) 1.0);
	this->SetDecay((MY_FLOAT) 0.99);
	this->SetStopLevel((MY_FLOAT) 0.0);
	m_fLastOutput = (float) m_fStartLevel;
}

void CEnvExp::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << 	m_nState;
		ar << 	m_fStartLevel;
		ar << 	m_fDecay;
		ar << 	m_fStopLevel;
	}
	else
	{
		// TODO: add loading code here
		ar >> 	m_nState;
		ar >> 	m_fStartLevel;
		ar >> 	m_fDecay;
		ar >> 	m_fStopLevel;
	}
}

#ifdef _DEBUG
void CEnvExp::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CEnvExp Observators

MY_FLOAT CEnvExp::GetStartLevel()
{
	ASSERT(this);
	return m_fStartLevel;
}

MY_FLOAT CEnvExp::GetStopLevel()
{
	ASSERT(this);
	return m_fStopLevel;
}

/////////////////////////////////////////////////////////////////////////////
// CEnvExp Functions

void CEnvExp::SetStartLevel(MY_FLOAT fStartLevel)
{
	ASSERT(this);
	ASSERT(fStartLevel > 0);
	ASSERT(fStartLevel <= 1.0);
	ASSERT(m_fStopLevel < fStartLevel);
	m_fStartLevel = fStartLevel;
}

void CEnvExp::SetDecay(MY_FLOAT fDecay)
{
	ASSERT(this);
	ASSERT(fDecay > 0);
	ASSERT(fDecay < 1.0);
	m_fDecay = fDecay;
}

void CEnvExp::SetDecayTime(MY_FLOAT fDecayTimeMSec)
{
	ASSERT(this);
	ASSERT(fDecayTimeMSec > 0);
	ASSERT(fDecayTimeMSec <= 5000);
	m_fDecay = ((float) 1000.0) / ((fDecayTimeMSec * (float)SRATE));
}

void CEnvExp::SetStopLevel(MY_FLOAT fStopLevel)
{
	ASSERT(this);
	ASSERT(fStopLevel >= 0);
	ASSERT(fStopLevel < 1.0);
	ASSERT(fStopLevel < m_fStartLevel);
	m_fStopLevel = fStopLevel;
}

/////////////////////////////////////////////////////////////////////////////

MY_FLOAT CEnvExp::Tick()
{
	ASSERT(this);
	if(m_nState == ENV_EXP_DECAY)
	{
		m_fLastOutput -= m_fLastOutput *(1 - m_fDecay);
		//TRACE("EnvExp: Dec = %f\n", m_fLastOutput * (1 - m_fDecay));
		//TRACE("EnvExp: LastOut = %f\n", m_fLastOutput);
		if(m_fLastOutput < m_fStopLevel)
		{
			m_fLastOutput = m_fStopLevel;
			m_nState = ENV_EXP_STOP;
		}
	}
	else if(m_nState == ENV_EXP_STOP)
	{
		m_fLastOutput = m_fStopLevel;
	}
	return m_fLastOutput;
}

MY_FLOAT CEnvExp::LastOut()
{
	ASSERT(this);
	return m_fLastOutput;
}

