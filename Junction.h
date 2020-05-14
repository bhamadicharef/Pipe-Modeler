// Junction.h : header file
// 


#ifndef __Junction_H_
#define __Junction_H_

#include "TKObject.h"

#define NB_TUBES		6
#define NB_TH_JUNCTIONS	(NB_TUBES - 1)
#define NB_JUNCTIONS	(NB_TUBES - 1)

#define	LENGTH0_RATIO	1 / NB_TUBES
#define	LENGTH1_RATIO	1 / NB_TUBES
#define	LENGTH2_RATIO	1 / NB_TUBES
#define	LENGTH3_RATIO	1 / NB_TUBES
#define	LENGTH4_RATIO	1 / NB_TUBES
#define	LENGTH5_RATIO	1 / NB_TUBES

class CJunction : public CTKObject
{
	DECLARE_DYNAMIC(CJunction)
	
// Construction
public:
	CJunction();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fDiameterLeft;
	MY_FLOAT	m_fDiameterRight;

	MY_FLOAT	m_fJunctionCoef;

	MY_FLOAT	m_fOutputLeft;
	MY_FLOAT	m_fOutputRight;
	
// Operators 
public:

// Implementation
public:
	virtual	~CJunction();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		SetDiameterLeft(MY_FLOAT fDiameterLeft);
	void		SetDiameterRight(MY_FLOAT fDiameterRight);
	MY_FLOAT	GetDiameterLeft() { return m_fDiameterLeft; };
	MY_FLOAT	GetDiameterRight() { return m_fDiameterRight; };
	MY_FLOAT	GetJunctionCoef() { return m_fJunctionCoef; };

	void		Clear();
	void		CalculateJunctionCoef();
	void		Tick(MY_FLOAT fInputLeft, MY_FLOAT fInputRight);
	MY_FLOAT	LastOutLeft() { return m_fOutputLeft; };
	MY_FLOAT	LastOutRight() { return m_fOutputRight; };

};

#endif

/////////////////////////////////////////////////////////////////////////////
