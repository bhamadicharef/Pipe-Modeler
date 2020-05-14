// Model.h : header file
//

#ifndef __Model_H_
#define __Model_H_

#include "TKObject.h"
#include "WavFileOut.h"

class CModel : public CTKObject
{
	DECLARE_DYNAMIC(CModel)
	
// Construction
public:
	CModel();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:
	CWavFileOut	m_WavFileOut;

	MY_FLOAT	m_fLastOutput;

public:
	CWavFileOut*	GetPtrWavFileOut() { return ((CWavFileOut*) &m_WavFileOut); };

	MY_FLOAT	Tick();
	MY_FLOAT	LastOut();
	// Save one sec of sound
	void	SaveWavFile(CString strFileName);

// Operators 
public:

// Implementation
public:
	virtual	~CModel();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __Model_H_

/////////////////////////////////////////////////////////////////////////////
