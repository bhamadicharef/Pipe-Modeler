// ToneHoleFilter.h : header file
//

#ifndef __ToneHoleFilter_H_
#define __ToneHoleFilter_H_

#include "Filter.h"

class CToneHoleFilter : public CFilter
{
	DECLARE_DYNAMIC(CToneHoleFilter)
	
// Construction
public:
	CToneHoleFilter();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:
	MY_FLOAT	m_fToneHoleCoef;

// Operators 
public:

// Implementation
public:
	virtual	~CToneHoleFilter();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		Clear();
	void		SetToneHoleCoef(MY_FLOAT fCoef);
	MY_FLOAT	Tick(MY_FLOAT sample);
	MY_FLOAT	LastOut();

};

#endif // __ToneHoleFilter_H_

/////////////////////////////////////////////////////////////////////////////
