// SineWave.cpp : implementation file
//

#include "stdafx.h"
#include "SineWave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSineWave

IMPLEMENT_DYNAMIC(CSineWave, CObject)

CSineWave::CSineWave(CString strFileName)
{
	ASSERT_VALID(this);
    long i;
    short temp;
	CFile SinWaveFile;
	CFileException SinWaveFileE;

	if(!SinWaveFile.Open(strFileName, CFile::modeRead , &SinWaveFileE))
	{
		AfxMessageBox("File could not be opened " , MB_OK | MB_ICONSTOP);
		ASSERT(FALSE);
	}
	else
	{
		i = 0;
		while(SinWaveFile.Read(&temp, 2))
		{
			i++;
		}
		m_nLength = i;
		SinWaveFile.Seek(0, CFile::begin);
		m_pfData = (MY_FLOAT *) malloc(MY_FLOAT_SIZE * (m_nLength + 1));
		i = 0;
		while(SinWaveFile.Read(&temp, 2))
		{
            temp = SwapShort(temp);
			m_pfData[i] = temp;
			i++;
		}
		m_pfData[m_nLength] = m_pfData[0];
		SinWaveFile.Close();

		m_fTime = (MY_FLOAT) 0.0;
		m_fPhaseOffset = (MY_FLOAT) 0.0;
		m_fRate = (MY_FLOAT) 1.0;
		m_fLastOutput = (MY_FLOAT) 0.0;
	}
}

short CSineWave::SwapShort(short inf)
{
	short o;
	unsigned char *inp,*outp; 
	inp=(unsigned char *)&inf; 
	outp=(unsigned char *)&o;
	outp[0]=inp[1]; outp[1]=inp[0];
	return(o);
}

CSineWave::~CSineWave()
{
	free(m_pfData);
}

void CSineWave :: Reset()
{
    m_fTime = (MY_FLOAT) 0.0;
    m_fLastOutput = (MY_FLOAT) 0.0;
}

void CSineWave::Normalize()
{
    this->Normalize((MY_FLOAT) 1.0);
}

void CSineWave::Normalize(MY_FLOAT fNewPeak)
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

void CSineWave::Serialize(CArchive& ar)
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
void CSineWave::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CSineWave Observators

/////////////////////////////////////////////////////////////////////////////
// CSineWave Functions

void CSineWave::SetRate(MY_FLOAT fRate)
{
    m_fRate = fRate;
}

void CSineWave::SetFreq(MY_FLOAT fFreq)
{
    m_fRate = (MY_FLOAT) m_nLength * (MY_FLOAT) ONE_OVER_SRATE * fFreq;
	//TRACE("NewRate = %f\n", m_fRate);
}

void CSineWave::AddTime(MY_FLOAT fTime)
{
	m_fTime += fTime;
}

void CSineWave::AddPhase(MY_FLOAT fAngle)
{
	m_fTime += m_nLength * fAngle;
}

void CSineWave::AddPhaseOffset(MY_FLOAT fAngle)
{
	m_fPhaseOffset = m_nLength * fAngle;
}

MY_FLOAT CSineWave::Tick()
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
		while(m_fTime >= m_nLength)
		{
			m_fTime -= m_nLength;
		}
		while(m_fTime < 0.0)
		{
			m_fTime += m_nLength;
		}
	}

	nTemp = (long) fTempTime;
	fAlpha = fTempTime - (MY_FLOAT) nTemp;
	m_fLastOutput = m_pfData[nTemp];
	m_fLastOutput =	m_fLastOutput +
					(fAlpha * (m_pfData[nTemp+1] -
					m_fLastOutput));

	return m_fLastOutput;
}

MY_FLOAT CSineWave::LastOut()
{
	return m_fLastOutput;
}



