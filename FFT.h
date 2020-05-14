// FFT.h : header file
//

#ifndef __FFT_H_
#define __FFT_H_

#include "TKObject.h"

#define FFT_MAX	4096

class CFFT : public CTKObject
{
	DECLARE_DYNAMIC(CFFT)
	
// Construction
public:
	CFFT();
	virtual void Serialize(CArchive& ar);

	void		Clear();
	void		SetSize(int nSize);
	void		Add(MY_FLOAT x);
	int			NumberOfBitsNeeded(int nPowerOfTwo);
	void		SetParameters(int nSamplingRate);
	void		PerformFFT(void);
	MY_FLOAT	GetOutPower(int nFrequency);

// Attributes
protected:  

private:
	int			m_nInput_pointer;
	int			m_nTotalPoints;
	int			m_nlogPoints;
	int			m_nSqrtPoints;
	int			m_nOutput_pointer;
	int			m_nSamplingRate;

	int			m_nBitReverse[FFT_MAX];
	MY_FLOAT	m_fReal_in[FFT_MAX];
	MY_FLOAT	m_fImag_in[FFT_MAX];
	MY_FLOAT	m_fAlpha1[FFT_MAX+1];
	MY_FLOAT	m_fBeta1[FFT_MAX+1];
	MY_FLOAT	m_fAlpha2[FFT_MAX+1];
	MY_FLOAT	m_fBeta2[FFT_MAX+1];
	MY_FLOAT	m_fAr[FFT_MAX];
	MY_FLOAT	m_fAi[FFT_MAX];

// Operators 
public:

// Implementation
public:
	virtual	~CFFT();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __FFT_H_

/////////////////////////////////////////////////////////////////////////////
