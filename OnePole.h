// OnePole.h : header file
//

#ifndef __ONEPOLE_H_
#define __ONEPOLE_H_

#include "Filter.h"

class COnePole : public CFilter
{
	DECLARE_DYNAMIC(COnePole)
	
// Construction
public:
	COnePole();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fPoleCoeff;
	MY_FLOAT	m_fSGain;

// Operators 
public:

// Implementation
public:
	virtual	~COnePole();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		Clear();
	void		SetPole(MY_FLOAT fPole);
	void		SetGain(MY_FLOAT fGain);
	MY_FLOAT	Tick(MY_FLOAT fSample);
	MY_FLOAT	LastOut();
};

#endif // __ONEPOLE_H_

/////////////////////////////////////////////////////////////////////////////
