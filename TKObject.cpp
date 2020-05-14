// TKObject.cpp : implementation file
//
//
// This is a part of the ToolKit Classes C++ library.
//
// Author:	Brahim HAMADICHAREF
// Date:	06/03/1998
//

/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TKObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTKObject

IMPLEMENT_DYNAMIC(CTKObject, CObject)

CTKObject::CTKObject()
{
	ASSERT_VALID(this);
    m_MIDI_ModWheel		= 1;	/* Controller # 1 	*/
    m_MIDI_Ctrl1		= 2;	/* Breath Pressure 	*/
    m_MIDI_Ctrl2		= 4;	/* Foot Control    	*/
    m_MIDI_Ctrl3		= 11;	/* Expression Pedal 	*/
    m_MIDI_AfterTouch	= 128;	/* Channel Pressure -> new controller */
}

CTKObject::~CTKObject()
{
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CTKObject::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_MIDI_ModWheel;
		ar << m_MIDI_Ctrl1;
		ar << m_MIDI_Ctrl2;
		ar << m_MIDI_Ctrl3;
		ar << m_MIDI_AfterTouch;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_MIDI_ModWheel;
		ar >> m_MIDI_Ctrl1;
		ar >> m_MIDI_Ctrl2;
		ar >> m_MIDI_Ctrl3;
		ar >> m_MIDI_AfterTouch;
	}
}

#ifdef _DEBUG
void CTKObject::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: Target: " << m_Target << "\n"
//		<< "ADSR: Rate: " << m_Rate << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CTKObject Observators

/////////////////////////////////////////////////////////////////////////////
// CTKObject Functions


