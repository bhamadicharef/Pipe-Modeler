// LoopWave.cpp : implementation file
//

#include "stdafx.h"
#include "LoopWave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoopWave

IMPLEMENT_DYNAMIC(CLoopWave, CObject)

CLoopWave::CLoopWave(int nWaveType /* = LOOP_WAVE_SIN */, int nLength /* = 256 */)
{
	ASSERT_VALID(this);
    long i;

	ASSERT(nWaveType >= LOOP_WAVE_SIN);
	ASSERT(nWaveType <= LOOP_WAVE_NOISE);
	m_nWaveType = nWaveType;

	ASSERT(nLength > 16);
	ASSERT(nLength <= 2048);
	m_nLength = nLength;

	m_pfData = (MY_FLOAT*) malloc(MY_FLOAT_SIZE * (m_nLength + 1));

	switch(m_nWaveType)
	{
		case LOOP_WAVE_SIN:
			{
				for(i = 0; i <= m_nLength; i++)
				{
					m_pfData[i] = (MY_FLOAT) sin((TWO_PI * i) / m_nLength);
					//TRACE("SinData[%d] = %f\n", i, m_pfData[i]);
				}
			}
			break;
		case LOOP_WAVE_SAW:
			{

			    for(i = 0; i <= m_nLength; i++)
				{
					m_pfData[i] = (MY_FLOAT) i / m_nLength;
					//TRACE("SinData[%d] = %f\n", i, m_pfData[i]);
				}
			}
			break;
		default:
			break;
	}
	m_pfData[m_nLength] = m_pfData[0];

	m_fTime = (MY_FLOAT) 0.0;
	m_fPhaseOffset = (MY_FLOAT) 0.0;
	m_fRate = (MY_FLOAT) 1.0;
	m_fLastOutput = (MY_FLOAT) 0.0;
}

CLoopWave::~CLoopWave()
{
	free(m_pfData);
}

void CLoopWave :: Reset()
{
    m_fTime = (MY_FLOAT) 0.0;
    m_fLastOutput = (MY_FLOAT) 0.0;
}

void CLoopWave::Normalize()
{
    this->Normalize((MY_FLOAT) 1.0);
}

void CLoopWave::Normalize(MY_FLOAT fNewPeak)
{
    long i;
    MY_FLOAT fMax = (MY_FLOAT) 0.0;
    for(i = 0; i <= m_nLength; i++)
	{
		if(fabs(m_pfData[i]) > fMax)
		{
			fMax = (MY_FLOAT) fabs((double) m_pfData[i]);
		}
	}
	if(fMax > 0.0)
	{
		fMax = (MY_FLOAT) 1.0 / fMax;
	}
	fMax *= fNewPeak;
    for(i = 0; i <= m_nLength; i++)
	{
	    m_pfData[i] *= fMax;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CLoopWave::Serialize(CArchive& ar)
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
void CLoopWave::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CLoopWave Observators

MY_FLOAT CLoopWave::GetFrequency()
{
    return m_fFrequency;
}

/////////////////////////////////////////////////////////////////////////////
// CLoopWave Functions

void CLoopWave::SetRate(MY_FLOAT fRate)
{
    m_fRate = fRate;
}

void CLoopWave::SetFrequency(MY_FLOAT fFreq)
{
	m_fFrequency = fFreq;
    m_fRate = (MY_FLOAT) m_nLength * (MY_FLOAT) ONE_OVER_SRATE * fFreq;
	//TRACE("NewRate = %f\n", m_fRate);
}

void CLoopWave::AddTime(MY_FLOAT fTime)
{
	m_fTime += fTime;
	//TRACE("NewTime = %f\n", m_fTime);
}

void CLoopWave::AddPhase(MY_FLOAT fAngle)
{
	m_fTime += m_nLength * fAngle;
	//TRACE("NewTime = %f\n", m_fTime);
}

void CLoopWave::AddPhaseOffset(MY_FLOAT fAngle)
{
	ASSERT(fAngle >= -1.0);
	ASSERT(fAngle <= 1.0);
	m_fPhaseOffset = m_nLength * fAngle;
}

MY_FLOAT CLoopWave::Tick()
{
	long nTemp;
	MY_FLOAT fTempTime, fAlpha;

	m_fTime += m_fRate;                          /*  Update current time    */

	while(m_fTime >= m_nLength)
	{
		m_fTime -= m_nLength;
	}
	while(m_fTime < 0.0)
	{
		m_fTime += m_nLength;
	}

	fTempTime = m_fTime;

	if(m_fPhaseOffset != 0.0)
	{
		fTempTime += m_fPhaseOffset;
		while(fTempTime >= m_nLength)
		{
			fTempTime -= m_nLength;
		}
		while(fTempTime < 0.0)
		{
			fTempTime += m_nLength;
		}
	}

	nTemp = (long) fTempTime;
	fAlpha = fTempTime - (MY_FLOAT) nTemp;			// fAlpha = fractional part
	m_fLastOutput = m_pfData[nTemp];
	m_fLastOutput =	m_fLastOutput +
					(fAlpha * (m_pfData[nTemp+1] -
					m_fLastOutput));

	return m_fLastOutput;
}

MY_FLOAT CLoopWave::LastOut()
{
	return m_fLastOutput;
}



