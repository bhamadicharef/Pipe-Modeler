// Adsr.h : header file
//

#ifndef __ADSR_H_
#define __ADSR_H_

#define	ADSR_ATTACK		0
#define	ADSR_DECAY		1
#define	ADSR_SUSTAIN	2
#define	ADSR_RELEASE	3
#define	ADSR_STOP		4

#include "TKObject.h"

class CAdsr : public CTKObject
{
	DECLARE_DYNAMIC(CAdsr)
	
// Construction
public:
	CAdsr();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	int			m_nState;

	MY_FLOAT	m_fAttack;
	MY_FLOAT	m_fDecay;
	MY_FLOAT	m_fSustainLevel;
	int			m_nSustain;
	int			m_nCount;
	MY_FLOAT	m_fRelease;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	MY_FLOAT	Tick();
	MY_FLOAT	LastOut();
	void		Init();
	
	void		SetAttack(MY_FLOAT fAttack);
	void		SetAttackTime(MY_FLOAT fAttackTimeMSec);
	void		SetDecay(MY_FLOAT fDecay);
	void		SetDecayTime(MY_FLOAT fDecayTimeMSec);
	void		SetSustainLevel(MY_FLOAT fSustainLevel);
	void		SetSustain(int nSustain);
	void		SetSustainTime(MY_FLOAT fSustainTimeMSec);
	void		SetRelease(MY_FLOAT fRelease);
	void		SetReleaseTime(MY_FLOAT fReleaseTimeMSec);

	void		SetAllTimes(MY_FLOAT fAttackTimeMSec,
							MY_FLOAT fDecayTimeMSec,
							MY_FLOAT fSustainTimeMSec,
							MY_FLOAT fReleaseTimeMSec);

public:	
	virtual	~CAdsr();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __ADSR_H_

/////////////////////////////////////////////////////////////////////////////
