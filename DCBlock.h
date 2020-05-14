// DCBlock.h : header file
//

#ifndef __DCBLOCK_H_
#define __DCBLOCK_H_

#include "Filter.h"

class CDCBlock : public CFilter
{
	DECLARE_DYNAMIC(CDCBlock)
	
// Construction
public:
	CDCBlock();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  

// Operators 
public:

// Implementation
public:
	virtual	~CDCBlock();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		Clear();
	MY_FLOAT	Tick(MY_FLOAT sample);
	MY_FLOAT	LastOut();

};

#endif // __DCBLOCK_H_

/////////////////////////////////////////////////////////////////////////////
