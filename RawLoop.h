#ifndef __RAWLOOP_H_
#define __RAWLOOP_H_

#include "TKObject.h"

class RawLoop : public CTKObject
{
	DECLARE_DYNAMIC(CRawLoop)

// Construction
public:
	CRawLoop();
	virtual void Serialize(CArchive& ar);

    long length;
    MY_FLOAT*	m_pfData;
    MY_FLOAT	m_fRate;
    MY_FLOAT	m_fTime;
    MY_FLOAT	m_fPhaseOffset;
    MY_FLOAT	m_fLastOutput;

public:
    RawLoop(char *fileName);
    ~RawLoop();
    void reset();
    void normalize();
    void normalize(MY_FLOAT newPeak);
    void setRate(MY_FLOAT aRate);
    void setFreq(MY_FLOAT aFreq);    
    void addTime(MY_FLOAT aTime);
    void addPhase(MY_FLOAT anAngle);
    void addPhaseOffset(MY_FLOAT anAngle);
    MY_FLOAT tick();
    MY_FLOAT lastOut();
};

#endif
