// Filter.h : header file
//

#ifndef __FILTER_H_
#define __FILTER_H_

#include "TKObject.h"

#define FILTER_MAX		2

class CFilter : public CTKObject
{

	DECLARE_DYNAMIC(CFilter)

// Construction
public:
	CFilter();

// Attributes
public:

protected:
	MY_FLOAT	m_fGain;
	MY_FLOAT*	m_pfInputs;				// x(n), x(n-1), ...
	MY_FLOAT*	m_pfOutputs;			// y(n), y(n-1), ...
	MY_FLOAT	m_fLastOutput;			// y(n) = output

// Operations
public:
	MY_FLOAT LastOut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilter)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilter();
#ifdef _DEBUG
	void Dump(CDumpContext& dc) const;
#endif

};

#endif __FILTER_H_

/////////////////////////////////////////////////////////////////////////////
