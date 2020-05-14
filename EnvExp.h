// EnvExp.h : header file
//

#ifndef __ENVEXP_H_
#define __ENVEXP_H_

#define		ENV_EXP_DECAY		0
#define		ENV_EXP_STOP		1

#include "TKObject.h"

class CEnvExp : public CTKObject
{
	DECLARE_DYNAMIC(CEnvExp)
	
// Construction
public:
	CEnvExp();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	int			m_nState;
	MY_FLOAT	m_fStartLevel;
	MY_FLOAT	m_fDecay;
	MY_FLOAT	m_fStopLevel;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	MY_FLOAT	Tick();
	MY_FLOAT	LastOut();
	void		Init();
	
	void		SetStartLevel(MY_FLOAT fStartLevel);
	MY_FLOAT	GetStartLevel();

	void		SetDecay(MY_FLOAT fDecay);
	void		SetDecayTime(MY_FLOAT fDecayTimeMSec);

	void		SetStopLevel(MY_FLOAT fStopLevel);
	MY_FLOAT	GetStopLevel();

public:	
	virtual	~CEnvExp();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __EnvExp_H_

/////////////////////////////////////////////////////////////////////////////
