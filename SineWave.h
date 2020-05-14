// SineWave.h : header file
//

#ifndef __SineWave_H_
#define __SineWave_H_

#include "TKObject.h"

class CSineWave : public CTKObject
{
	DECLARE_DYNAMIC(CSineWave)
	
// Construction
public:
	CSineWave(CString strFileName);
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
    long		m_nLength;
    MY_FLOAT*	m_pfData;
    MY_FLOAT	m_fRate;
    MY_FLOAT	m_fTime;
    MY_FLOAT	m_fPhaseOffset;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	virtual	~CSineWave();

    void	Reset();
    void	Normalize();
    void	Normalize(MY_FLOAT fNewPeak);
	short	SwapShort(short inf);
    void	SetRate(MY_FLOAT fRate);
    void	SetFreq(MY_FLOAT fFreq);    
    void	AddTime(MY_FLOAT fTime);
    void	AddPhase(MY_FLOAT fAngle);
    void	AddPhaseOffset(MY_FLOAT fAngle);

    MY_FLOAT Tick();
    MY_FLOAT LastOut();

#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

};

#endif __SineWave_H_

/////////////////////////////////////////////////////////////////////////////
