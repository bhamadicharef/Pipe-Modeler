// Asr.cpp : implementation file
//
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Asr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsr

IMPLEMENT_DYNAMIC(CAsr, CObject)

CAsr::CAsr()
{
	ASSERT_VALID(this);
	m_bExp = FALSE;
	Init();
}

CAsr::~CAsr()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CAsr::Init()
{
	m_nState = ASR_ATTACK;
	m_nCount = m_nSustain; 
	m_fLastOutput = (float) 0.0;
}

void CAsr::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar <<	m_nState;
		ar <<	m_bExp;
		ar <<	m_fAttack;
		ar <<	m_nSustain;
		ar <<	m_nCount;
		ar <<	m_fRelease;
	}
	else
	{
		// TODO: add loading code here
		ar >>	m_nState;
		ar >>	m_bExp;
		ar >>	m_fAttack;
		ar >>	m_nSustain;
		ar >>	m_nCount;
		ar >>	m_fRelease;
	}
}

#ifdef _DEBUG
void CAsr::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CAsr Observators

MY_FLOAT CAsr::GetAttackTime()
{
	return ((MY_FLOAT) 1000.0) / ((m_fAttack * (MY_FLOAT) SRATE));
}

MY_FLOAT CAsr::GetSustainTime()
{
	return ((MY_FLOAT)(m_nSustain * (MY_FLOAT) ONE_OVER_SRATE) * (MY_FLOAT) 1000.0);
}

MY_FLOAT CAsr::GetReleaseTime()
{
	return ((MY_FLOAT) 1000.0) / ((m_fRelease * (MY_FLOAT) SRATE));
}

/////////////////////////////////////////////////////////////////////////////
// CAsr Functions

void CAsr::SetAttack(MY_FLOAT fAttack)
{
	ASSERT(fAttack > 0);
	ASSERT(fAttack <= 1000);
	m_fAttack = fAttack;
}

void CAsr::SetAttackTime(MY_FLOAT fAttackTimeMSec)
{
/*
	if(fAttackTimeMSec == 0)
	{
		fAttackTimeMSec = 1;
	}
*/
	ASSERT(fAttackTimeMSec > 0);
	ASSERT(fAttackTimeMSec <= 5000);
	//TRACE("Asr: NewAttackTimeMSec = %f\n", fAttackTimeMSec);
	m_fAttack = ((float) 1000.0) / ((fAttackTimeMSec * (float)SRATE));
}

void CAsr::SetSustain(int nSustain)
{
	ASSERT(nSustain > 0);
	ASSERT(nSustain <= SRATE);
	m_nSustain = nSustain;
	m_nCount = m_nSustain; 
}

void CAsr::SetSustainTime(MY_FLOAT fSustainTimeMSec)
{
/*
	if(fSustainTimeMSec == 0)
	{
		fSustainTimeMSec = 1;
	}
*/
	ASSERT(fSustainTimeMSec > 0);
	ASSERT(fSustainTimeMSec <= 5000);
	//TRACE("Asr: NewSustainTimeMSec = %f\n", fSustainTimeMSec);
	m_nSustain = int((fSustainTimeMSec * (float)SRATE) / 1000);
	m_nCount = m_nSustain; 
}

void CAsr::SetRelease(MY_FLOAT fRelease)
{
	ASSERT(fRelease > 0);
	ASSERT(fRelease <= 1000);
	m_fRelease = fRelease;
}

void CAsr::SetReleaseTime(MY_FLOAT fReleaseTimeMSec)
{
/*
	if(fReleaseTimeMSec == 0)
	{
		fReleaseTimeMSec = 1;
	}
*/	
	ASSERT(fReleaseTimeMSec > 0);
	ASSERT(fReleaseTimeMSec <= 5000);
	//TRACE("Asr: NewReleaseTimeMSec = %f\n", fReleaseTimeMSec);
	m_fRelease = ((float) 1000.0) / ((fReleaseTimeMSec * (float)SRATE));
}

////////////////////////////////////////////////////////////////////////

void CAsr::SetLinear()
{
	m_bExp = FALSE;
}

void CAsr::SetExp()
{
	m_bExp = TRUE;
}

////////////////////////////////////////////////////////////////////////

MY_FLOAT CAsr::Tick()
{
	if(m_nState == ASR_ATTACK)
	{
		if(m_bExp)
		{
			m_fLastOutput += (1 - m_fLastOutput) * m_fAttack;
			// !! Never reach 1.0 !
			if(m_fLastOutput >= 0.99)
			{
				m_fLastOutput = 1.0;
				m_nState = ASR_SUSTAIN;
			}
		}
		else
		{
			m_fLastOutput += m_fAttack;
			if(m_fLastOutput >= 1.0)
			{
				m_fLastOutput = 1.0;
				m_nState = ASR_SUSTAIN;
			}
		}
	}
	else if(m_nState == ASR_SUSTAIN)
	{
		m_nCount--;
		if(m_nCount == 0)
		{
			m_nState = ASR_RELEASE;
		}
	}
	else if(m_nState == ASR_RELEASE)
	{
		if(m_bExp)
		{
			m_fLastOutput -= m_fLastOutput * m_fRelease;
			if(m_fLastOutput < 0.0)
			{
				m_fLastOutput = 0.0;
				m_nState = ASR_STOP;
			}
		}
		else
		{
			m_fLastOutput -= m_fRelease;
			if(m_fLastOutput < 0.0)
			{
				m_fLastOutput = 0.0;
				m_nState = ASR_STOP;
			}
		}
	}
	else if(m_nState == ASR_STOP)
	{
		m_nState = ASR_STOP;
		m_fLastOutput = 0.0;
	}
	return m_fLastOutput;
}

MY_FLOAT CAsr::LastOut()
{
	return m_fLastOutput;
}

