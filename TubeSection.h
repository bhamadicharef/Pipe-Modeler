// TubeSection.h : header file
// 

#ifndef __TubeSection_H_
#define __TubeSection_H_

#include "DLineL.h"

class CTubeSection : public CObject
{
	DECLARE_DYNAMIC(CTubeSection)
	
// Construction
public:
	CTubeSection();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fLength;

	CDLineL*	m_pUpperDLineL;
	CDLineL*	m_pLowerDLineL;

	MY_FLOAT	m_fOutputLeft;
	MY_FLOAT	m_fOutputRight;
	
// Operators 
public:

// Implementation
public:
	virtual	~CTubeSection();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		SetLength(MY_FLOAT fLength);
	MY_FLOAT	GetLength() { return this->m_fLength; };

	void		Clear();
	void		Tick(MY_FLOAT fInputLeft, MY_FLOAT fInputRight);
	MY_FLOAT	LastOutLeft() { return m_fOutputLeft; };
	MY_FLOAT	LastOutRight() { return m_fOutputRight; };
};

#endif

/////////////////////////////////////////////////////////////////////////////
