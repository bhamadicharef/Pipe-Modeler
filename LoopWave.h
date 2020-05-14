// LoopWave.h : header file
//

#ifndef __LoopWave_H_
#define __LoopWave_H_

#include "TKObject.h"

#define	LOOP_WAVE_SIN	0
#define	LOOP_WAVE_TRI	1
#define	LOOP_WAVE_SAW	2
#define	LOOP_WAVE_SQR	3
#define	LOOP_WAVE_NOISE	4

class CLoopWave : public CTKObject
{
	DECLARE_DYNAMIC(CLoopWave)
	
// Construction
public:
	CLoopWave(int nType = LOOP_WAVE_SIN, int nLength = 256);
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
    long		m_nLength;
	long		m_nWaveType;

    MY_FLOAT*	m_pfData;
    MY_FLOAT	m_fFrequency;
    MY_FLOAT	m_fRate;
    MY_FLOAT	m_fTime;
    MY_FLOAT	m_fPhaseOffset;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	virtual	~CLoopWave();

    void		Reset();
    void		Normalize();
    void		Normalize(MY_FLOAT fNewPeak);
	short		SwapShort(short inf);
    void		SetRate(MY_FLOAT fRate);
    void		SetFrequency(MY_FLOAT fFreq);
    MY_FLOAT	GetFrequency();
    void		AddTime(MY_FLOAT fTime);
    void		AddPhase(MY_FLOAT fAngle);
    void		AddPhaseOffset(MY_FLOAT fAngle);

    MY_FLOAT Tick();
    MY_FLOAT LastOut();

#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

};

#endif __LoopWave_H_

/////////////////////////////////////////////////////////////////////////////
