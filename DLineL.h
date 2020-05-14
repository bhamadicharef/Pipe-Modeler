// DLineL.h : header file
//

#ifndef __DLINEL_H_
#define __DLINEL_H_

#include "Filter.h"

#define DLINEL_MAX			2048

class CDLineL : public CFilter
{
	DECLARE_DYNAMIC(CDLineL)

// Construction
public:
	CDLineL(long max_length);

// Attributes
protected:
	long		m_nInPoint;
	long		m_nOutPoint;
	long		m_nLength;
	MY_FLOAT	m_fAlpha;
	MY_FLOAT	m_fOmAlpha;

// Operations
public:
    void		Clear();
    void		SetDelay(MY_FLOAT flength);
    MY_FLOAT	Tick(MY_FLOAT fsample);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModel)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDLineL();
#ifdef _DEBUG
	void Dump(CDumpContext& dc) const;
#endif

};

#endif __DLINEL_H_

/////////////////////////////////////////////////////////////////////////////
