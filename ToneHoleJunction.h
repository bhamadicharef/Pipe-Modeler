// ToneHoleJunction.h : header file
// 


#ifndef __ToneHoleJunction_H_
#define __ToneHoleJunction_H_

#include "TKObject.h"
#include "ToneHoleFilter.h"

class CToneHoleJunction : public CTKObject
{
	DECLARE_DYNAMIC(CToneHoleJunction)
	
// Construction
public:
	CToneHoleJunction();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	MY_FLOAT	m_fDiameterBore;
	MY_FLOAT	m_fDiameterToneHole;
	MY_FLOAT	m_fHeightToneHole;			// Warning when = 0

	CToneHoleFilter*	m_pFilter;
	MY_FLOAT			m_fToneHoleCoef;			// Coef a

	MY_FLOAT	m_fOutputLeft;
	MY_FLOAT	m_fOutputRight;
	MY_FLOAT	m_fOutputToneHole;
	
// Operators 
public:

// Implementation
public:
	virtual	~CToneHoleJunction();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	void		SetDiameterBore(MY_FLOAT fDiameterBore);
	void		SetDiameterToneHole(MY_FLOAT fDiameterToneHole);
	void		SetToneHole(MY_FLOAT fDiameterToneHole);
	void		SetHeightToneHole (MY_FLOAT fHeightToneHole);
	MY_FLOAT	GetDiameterBore() { return m_fDiameterBore; };
	MY_FLOAT	GetDiameterToneHole() { return m_fDiameterToneHole; };
	MY_FLOAT	GetHeightToneHole () { return m_fHeightToneHole ; };

	void		CalculateToneHoleCoef();
	MY_FLOAT	GetToneHoleCoef() { return m_fToneHoleCoef; };

	void		Clear();
	void		Tick(	MY_FLOAT fInputLeft,
						MY_FLOAT fInputRight,
						MY_FLOAT fInputToneHole);

	MY_FLOAT	LastOutLeft() { return m_fOutputLeft; };
	MY_FLOAT	LastOutRight() { return m_fOutputRight; };
	MY_FLOAT	LastOutToneHole() { return m_fOutputToneHole; };

};

#endif

/////////////////////////////////////////////////////////////////////////////
