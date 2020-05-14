// JetTable.h : header file
//

#ifndef __JetTable_H_
#define __JetTable_H_

#include "TKObject.h"

class CJetTable : public CTKObject
{
	DECLARE_DYNAMIC(CJetTable)
	
// Construction
public:
	CJetTable();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fLastOutput;

// Operators 
public:

// Implementation
public:
	virtual	~CJetTable();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
	MY_FLOAT	Tick(MY_FLOAT fSample);
	MY_FLOAT	LastOut();

};

#endif __JetTable_H_

/////////////////////////////////////////////////////////////////////////////
