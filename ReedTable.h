// ReedTable.h : header file
//

#ifndef __ReedTable_H_
#define __ReedTable_H_

#include "TKObject.h"

class CReedTable : public CTKObject
{
	DECLARE_DYNAMIC(CReedTable)
	
// Construction
public:
	CReedTable();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fOffset;
	MY_FLOAT	m_fSlope;
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	virtual	~CReedTable();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		SetOffset(MY_FLOAT fOffset);
	void		SetSlope(MY_FLOAT fSlope);
	MY_FLOAT	Tick(MY_FLOAT fSample);
	MY_FLOAT	LastOut();

};

#endif __ReedTable_H_

/////////////////////////////////////////////////////////////////////////////
