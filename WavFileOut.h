// WavFileOut.h : header file
//

#ifndef __WavFileOut_H_
#define __WavFileOut_H_

#include "TKObject.h"
#include "Wav.h"

#define	NB_CHANNELS	2

class CWavFileOut : public CTKObject
{
	DECLARE_DYNAMIC(CWavFileOut)
	
// Construction
public:
	CWavFileOut();
	virtual void Serialize(CArchive& ar);

	void Clear();

// Attributes
protected:  

// Operators 
public:
	void	Tick(float fSampleMain, float fSampleToneHole);
	void	Save(CString strFileName);

// Implementation
public:
	virtual	~CWavFileOut();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

	float	m_fData[2][44100];

protected:  
	long	m_nCounter;
	DWORD	m_dwLength;
	WORD	m_wFrequency;

};

#endif __WavFileOut_H_

/////////////////////////////////////////////////////////////////////////////
