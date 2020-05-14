// Adsr.cpp : implementation file
//
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Adsr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdsr

IMPLEMENT_DYNAMIC(CAdsr, CObject)

CAdsr::CAdsr()
{
	ASSERT_VALID(this);
	Init();
}

CAdsr::~CAdsr()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CAdsr::Init()
{
	m_nState = ADSR_ATTACK;
	m_fAttack = (float) (1.0 / 20);
	m_fDecay = (float) (1.0 / 20);
	m_fSustainLevel = (float) 0.5;
	m_nSustain = 15;
	m_nCount = m_nSustain; 
	m_fRelease = (float) (1.0 / 30);
	
	m_fLastOutput = (float) 0.0;
}

void CAdsr::Serialize(CArchive& ar)
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
void CAdsr::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CAdsr Observators

/////////////////////////////////////////////////////////////////////////////
// CAdsr Functions

void CAdsr::SetAttack(MY_FLOAT fAttack)
{
	ASSERT(fAttack > 0);
	ASSERT(fAttack <= 1.0);
	m_fAttack = fAttack;
}

void CAdsr::SetAttackTime(MY_FLOAT fAttackTimeMSec)
{
	ASSERT(fAttackTimeMSec > 0);
	ASSERT(fAttackTimeMSec <= 5000);
	m_fAttack = ((float) 1000.0) / ((fAttackTimeMSec * (float)SRATE));
}

void CAdsr::SetDecay(MY_FLOAT fDecay)
{
	ASSERT(fDecay > 0);
	ASSERT(fDecay <= 1.0);
	m_fDecay = fDecay;
}

void CAdsr::SetDecayTime(MY_FLOAT fDecayTimeMSec)
{
	ASSERT(fDecayTimeMSec > 0);
	ASSERT(fDecayTimeMSec <= 5000);
	m_fDecay = ((float) 1000.0) / ((fDecayTimeMSec * (float)SRATE));
}

void CAdsr::SetSustainLevel(MY_FLOAT fSustainLevel)
{
	ASSERT(fSustainLevel > 0);
	ASSERT(fSustainLevel <= 1.0);
	m_fSustainLevel = fSustainLevel;
}

void CAdsr::SetSustain(int nSustain)
{
	ASSERT(nSustain > 0);
	ASSERT(nSustain <= SRATE);
	m_nSustain = nSustain;
}

void CAdsr::SetSustainTime(MY_FLOAT fSustainTimeMSec)
{
	ASSERT(fSustainTimeMSec > 0);
	ASSERT(fSustainTimeMSec <= 5000);
	m_nSustain = int (fSustainTimeMSec * (float)SRATE);
}

void CAdsr::SetRelease(MY_FLOAT fRelease)
{
	ASSERT(fRelease > 0);
	ASSERT(fRelease <= 1000);
	m_fRelease = fRelease;
}

void CAdsr::SetReleaseTime(MY_FLOAT fReleaseTimeMSec)
{
	ASSERT(fReleaseTimeMSec > 0);
	ASSERT(fReleaseTimeMSec <= 5000);
	m_fRelease = ((float) 1000.0) / ((fReleaseTimeMSec * (float)SRATE));
}

void CAdsr::SetAllTimes(MY_FLOAT fAttackTimeMSec,
						MY_FLOAT fDecayTimeMSec,
						MY_FLOAT fSustainTimeMSec,
						MY_FLOAT fReleaseTimeMSec)
{
	this->SetAttackTime(fAttackTimeMSec);
	this->SetDecayTime(fDecayTimeMSec);
	this->SetSustainTime(fSustainTimeMSec);
	this->SetReleaseTime(fReleaseTimeMSec);
}

////////////////////////////////////////////////////////////////

MY_FLOAT CAdsr::Tick()
{
	if(m_nState == ADSR_ATTACK)
	{
		m_fLastOutput += m_fAttack;
		if(m_fLastOutput >= 1.0)
		{
			m_fLastOutput = 1.0;
			m_nState = ADSR_DECAY;
		}
	}
	if(m_nState == ADSR_DECAY)
	{
		m_fLastOutput -= m_fDecay;
		if(m_fLastOutput < m_fSustainLevel)
		{
			m_fLastOutput = m_fSustainLevel;
			m_nState = ADSR_SUSTAIN;
		}
	}
	else if(m_nState == ADSR_SUSTAIN)
	{
		m_nCount--;
		if(m_nCount == 0)
		{
			m_nState = ADSR_RELEASE;
		}
	}
	else if(m_nState == ADSR_RELEASE)
	{
		m_fLastOutput -= m_fRelease;
		if(m_fLastOutput < 0.0)
		{
			m_fLastOutput = 0.0;
			m_nState = ADSR_STOP;
		}
	}
	else if(m_nState == ADSR_STOP)
	{
		m_fLastOutput = 0.0;
	}
	return m_fLastOutput;
}

MY_FLOAT CAdsr::LastOut()
{
	return m_fLastOutput;
}

