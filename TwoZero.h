// TwoZero.h : header file
//

#ifndef __TwoZero_H_
#define __TwoZero_H_

#include "Filter.h"

class CTwoZero : public CFilter
{
	DECLARE_DYNAMIC(CTwoZero)
	
// Construction
public:
	CTwoZero();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fZeroCoef[2];

// Operators 
public:

// Implementation
public:
	virtual	~CTwoZero();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		Clear();
	void		SetZeroCoef(int nCoef, MY_FLOAT fCoefValue);
	void		SetGain(MY_FLOAT fGain);

	MY_FLOAT	Tick(MY_FLOAT fSample);

};

#endif // __TwoZero_H_

/////////////////////////////////////////////////////////////////////////////
