// TKObject.h : header file
//

#ifndef __TKOBJECT_H_
#define __TKOBJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class CTKObject : public CObject
{
	DECLARE_DYNAMIC(CTKObject)
	
// Construction
public:
	CTKObject();
	virtual void Serialize(CArchive& ar);

// Attributes
public:
    int m_MIDI_ModWheel;	// Controller # 1
    int m_MIDI_Ctrl1;		// Breath Pressure
    int m_MIDI_Ctrl2;		// Foot Control
    int m_MIDI_Ctrl3;		// Expression Pedal
    int m_MIDI_AfterTouch;	// Channel Pressure -> new controller

// Operators 
public:

// Implementation
public:
	virtual	~CTKObject();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

#define __WIN95_REALTIME_

#define __SRATE_44100_

// SRATE here is 48000, others are derived accordingly
#ifdef __SRATE_48000_

#define SRATE			48000.0						// Hertz
#define SRATE_OVER_TWO	24000.0
#define ONE_OVER_SRATE	0.00002083333333			// Second

#endif
	
// SRATE here is 44100, others are derived accordingly
#ifdef __SRATE_44100_

#define SRATE			44100.0
#define SRATE_OVER_TWO	22050.0
#define ONE_OVER_SRATE	0.00002267573696

#endif

// SRATE here is 22050, others are derived accordingly
#ifdef __SRATE_22050_

#define SRATE			22050.0
#define SRATE_OVER_TWO	11025.0
#define ONE_OVER_SRATE	0.00004535147392

#endif


// SRATE here is 32000, others are derived accordingly
#ifdef __SRATE_32000_

#define SRATE			32000.0
#define SRATE_OVER_TWO	16000.0
#define ONE_OVER_SRATE	0.00003125

#endif

// SRATE here is 8000, others are derived accordingly
#ifdef __SRATE_8000_

#define SRATE			8000.0
#define SRATE_OVER_TWO	4000.0
#define ONE_OVER_SRATE	0.00012500000000

#endif

// Yer Basic Trigonometric constants
#define PI					3.14159265359
#define TWO_PI				6.28318530718
#define ONE_OVER_TWO_PI		0.15915494309

#define SPEED_OF_SOUND		340				// Meter per Second

#define DIAMETER_BORE		0.0095
#define DIAMETER_TONEHOLE	0.008

// States for Envelopes, etc.
#define	ATTACK		0
#define DECAY		1
#define SUSTAIN		2
#define RELEASE		3

// Machine dependent stuff, possibly useful for optimization
// for example, changing double to float here increases
// performance (speed) by a whopping 4-6% on 486-flavor machines
// BUT!! a change from float to double here increases speed by
// 30% or so on SGI machines


#define MY_FLOAT      float
#define MY_FLOAT_SIZE 4

/*
#define MY_FLOAT      double
#define MY_FLOAT_SIZE 8
*/

// MIDI definitions (this is 1/128)
#define NORM_7 0.0078125

};

#endif

/////////////////////////////////////////////////////////////////////////////

