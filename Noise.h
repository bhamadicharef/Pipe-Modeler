// Noise.h : header file
//

#ifndef __NOISE_H_
#define __NOISE_H_

#include "TKObject.h"

#define RAND_MAX_OVER_TWO	RAND_MAX / 2
#define ONE_OVER_RANDLIMIT	1 / RAND_MAX

class CNoise : public CTKObject
{
	DECLARE_DYNAMIC(CNoise)
	
// Construction
public:
	CNoise();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fLastOutput;

// Operators 
public:
	MY_FLOAT	Tick();
	MY_FLOAT	LastOut();

// Implementation
public:
	virtual	~CNoise();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __NOISE_H_

/////////////////////////////////////////////////////////////////////////////
