// ToneHoleJunction.cpp : implementation file
//

#include "stdafx.h"
#include "ToneHoleJunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToneHoleJunction

IMPLEMENT_DYNAMIC(CToneHoleJunction, CObject)

CToneHoleJunction::CToneHoleJunction()
{
	ASSERT_VALID(this);
	m_pFilter = NULL;
	m_pFilter = new CToneHoleFilter;
	
	m_fDiameterBore = (MY_FLOAT) 0.0095;			// 9.5 mm
	m_fDiameterToneHole = (MY_FLOAT) 0.008;			// 8 mm
	m_fHeightToneHole = (MY_FLOAT) 0.0175;			// 17.5 mm
	//m_fDiameterToneHole = (MY_FLOAT) 0.00625;		// 6.25 mm
	//m_fHeightToneHole = (MY_FLOAT) 0.0317;		// 31.7 mm

	this->Clear();
}

CToneHoleJunction::~CToneHoleJunction()
{
	delete m_pFilter;
}

void CToneHoleJunction::Clear()
{
	m_fOutputLeft = (MY_FLOAT) 0.0;
	m_fOutputRight = (MY_FLOAT) 0.0;
	CalculateToneHoleCoef();
}

/////////////////////////////////////////////////////////////////////////////
// CToneHoleJunction serialization

void CToneHoleJunction::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fDiameterBore;
		ar << m_fDiameterToneHole;
		ar << m_fHeightToneHole;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fDiameterBore;
		ar >> m_fDiameterToneHole;
		ar >> m_fHeightToneHole;
	}
}

#ifdef _DEBUG
void CToneHoleJunction::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ToneHoleJunction: Value: " << m_Value << "\n"
//		<< "ToneHoleJunction: Target: " << m_Target << "\n"
//		<< "ToneHoleJunction: Rate: " << m_Rate << "\n"
//		<< "ToneHoleJunction: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CToneHoleJunction Observators

/////////////////////////////////////////////////////////////////////////////
// CToneHoleJunction Functions

void CToneHoleJunction::SetDiameterBore(MY_FLOAT fDiameterBore)
{
	ASSERT_VALID(this);
	ASSERT(fDiameterBore >= 0.0);
	ASSERT(fDiameterBore <= 1.0);
	m_fDiameterBore = (MY_FLOAT) DIAMETER_BORE * fDiameterBore;
//	TRACE("DiameterBore = %f\n", fDiameterBore);
	CalculateToneHoleCoef();
}

void CToneHoleJunction::SetDiameterToneHole(MY_FLOAT fDiameterToneHole)
{
	ASSERT_VALID(this);
	ASSERT(fDiameterToneHole >= 0.0);
	ASSERT(fDiameterToneHole <= 1.0);
	m_fDiameterToneHole = (MY_FLOAT) DIAMETER_TONEHOLE * fDiameterToneHole;
//	TRACE("fDiameterToneHole  = %f\n", m_fDiameterToneHole);
	CalculateToneHoleCoef();
}

void CToneHoleJunction::SetHeightToneHole(MY_FLOAT fHeightToneHole)
{
	ASSERT_VALID(this);
	ASSERT(fHeightToneHole >= 0.0);
	ASSERT(fHeightToneHole <= 1.0);
	m_fHeightToneHole = fHeightToneHole;
	CalculateToneHoleCoef();
}

void CToneHoleJunction::CalculateToneHoleCoef()
{
	ASSERT_VALID(this);

	MY_FLOAT fAreaBore;						// Ao
	fAreaBore = ((MY_FLOAT) PI * m_fDiameterBore * m_fDiameterBore) / (MY_FLOAT) 4.0;
	//TRACE("AreaBore = %f\n", fAreaBore);
	
	MY_FLOAT fAreaToneHole;					// As
	fAreaToneHole = ((MY_FLOAT) PI * m_fDiameterToneHole * m_fDiameterToneHole) / (MY_FLOAT) 4.0;
	//TRACE("AreaToneHole = %f\n", fAreaToneHole);

	MY_FLOAT fTemp = ((MY_FLOAT) 2.0 * fAreaBore * m_fHeightToneHole);

	m_fToneHoleCoef = - fTemp / (fTemp +
						(fAreaToneHole * (MY_FLOAT) ONE_OVER_SRATE * (MY_FLOAT) SPEED_OF_SOUND));
	//TRACE("ToneHoleCoef = %f\n", m_fToneHoleCoef);

	m_pFilter->Clear();
	m_pFilter->SetToneHoleCoef(m_fToneHoleCoef);
}

// Ref: Vesa Thesis page 39, Fig 2.8 a)
void CToneHoleJunction::Tick(MY_FLOAT fInputLeft, MY_FLOAT fInputRight, MY_FLOAT fInputToneHole)
{
	ASSERT_VALID(this);

	MY_FLOAT fWn = m_pFilter->Tick(fInputLeft + fInputRight + fInputToneHole);

	m_fOutputLeft = fWn + fInputRight + fInputToneHole;

	m_fOutputRight = fWn + fInputLeft + fInputToneHole;
	
	m_fOutputToneHole = (- fInputToneHole + ((MY_FLOAT) -2.0 * fWn))/3;
}

