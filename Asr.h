// Asr.h : header file
//

#ifndef __Asr_H_
#define __Asr_H_

#define		ASR_ATTACK		0
#define		ASR_SUSTAIN		1
#define		ASR_RELEASE		2
#define		ASR_STOP		3

#include "TKObject.h"

class CAsr : public CTKObject
{
	DECLARE_DYNAMIC(CAsr)
	
// Construction
public:
	CAsr();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	int			m_nState;
	BOOL		m_bExp;

	MY_FLOAT	m_fAttack;
	int			m_nSustain;
	int			m_nCount;
	MY_FLOAT	m_fRelease;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	void		Init();

	MY_FLOAT	GetAttackTime();
	MY_FLOAT	GetSustainTime();
	MY_FLOAT	GetReleaseTime();
	
	void		SetAttack(MY_FLOAT fAttack);
	void		SetAttackTime(MY_FLOAT fAttackTimeMSec);
	void		SetSustain(int nSustain);
	void		SetSustainTime(MY_FLOAT fSustainTimeMSec);
	void		SetRelease(MY_FLOAT fRelease);
	void		SetReleaseTime(MY_FLOAT fReleaseTimeMSec);

	void		SetLinear();
	void		SetExp();

	MY_FLOAT	Tick();
	MY_FLOAT	LastOut();

public:	
	virtual	~CAsr();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __Asr_H_

/////////////////////////////////////////////////////////////////////////////
