// OneZero.h : header file
//

#ifndef __OneZero_H_
#define __OneZero_H_

#include "Filter.h"

class COneZero : public CFilter
{
	DECLARE_DYNAMIC(COneZero)
	
// Construction
public:
	COneZero();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fZeroCoeff;
	MY_FLOAT	m_fSGain;

// Operators 
public:

// Implementation
public:
	virtual	~COneZero();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		Clear();
	void		SetZero(MY_FLOAT fZero);
	void		SetGain(MY_FLOAT fGain);
	MY_FLOAT	Tick(MY_FLOAT fSample);
	MY_FLOAT	LastOut();

};

#endif // __OneZero_H_

/////////////////////////////////////////////////////////////////////////////
