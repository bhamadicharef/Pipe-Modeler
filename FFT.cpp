// FFT.cpp : implementation file
//
/* Performs a Fast Fourier Transform
 *
 * Based on the pseudo-code algorithm on
 * page 794 of 
 * Introduction to Algorithms
 * ISBN# 0-262-03141-8
 * 1990-MIT
 *
 * Optimizations and optimization ideas from 
 * various sources
 *
 * 1  Bit-Reverse-Copy(a,A)
 * 2  n=length[a]
 * 3  for s=1 to lg(n)
 * 4    m=2^s
 * 5    w(m)=e^(2i/m)
 * 6    w=1
 * 7    for j=0 to m/2-1
 * 8      for k=j to n-1 by m
 * 9        t=wA[k+m/2]
 * 10       u=A[k]
 * 11       A[k]=u+t
 * 12       A[k+m/2]=u-t
 * 13     w=w*w(m)
 * 14 return A
 *
 */

#include "stdafx.h"
#include "FFT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFFT

IMPLEMENT_DYNAMIC(CFFT, CObject)

CFFT::CFFT()
{
	ASSERT_VALID(this);
	Clear();
}

CFFT::~CFFT()
{
}

void CFFT::Clear()
{
	int i;

	m_nInput_pointer = 0;
	m_nTotalPoints = 0;
	m_nlogPoints = 0;
	m_nSqrtPoints = 0;
	m_nOutput_pointer = 0;
	m_nSamplingRate = 0;
	for(i = 0; i < FFT_MAX; i++)
	{
		m_nBitReverse[i]	= 0;
		m_fReal_in[i]		= (MY_FLOAT) 0.0;
		m_fImag_in[i]		= (MY_FLOAT) 0.0;
		m_fAr[i]			= (MY_FLOAT) 0.0;
		m_fAi[i]			= (MY_FLOAT) 0.0;
	}
	for(i = 0; i < FFT_MAX+1; i++)
	{
		m_fAlpha1[i]	= (MY_FLOAT) 0.0;
		m_fBeta1[i]		= (MY_FLOAT) 0.0;
		m_fAlpha2[i]	= (MY_FLOAT) 0.0;
		m_fBeta2[i]		= (MY_FLOAT) 0.0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CFFT::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar << m_ReleaseRate;
	}
	else
	{
		// TODO: add loading code here
		//ar >> m_ReleaseRate;
	}
}

#ifdef _DEBUG
void CFFT::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CFFT Observators

/////////////////////////////////////////////////////////////////////////////
// CFFT Functions

MY_FLOAT CFFT::GetOutPower(int nFreq)
{
	float total1 = (float)(sqrt(m_fAr[nFreq]*m_fAr[nFreq] + m_fAi[nFreq]*m_fAi[nFreq]));
	float fValue = 100 * (total1) / m_nTotalPoints / 4; // / 256 / 4;
	//	TRACE("Power[%d] = %f\n", nFreq, ret);
	return fValue;
}

void CFFT::SetSize(int nSize)
{
	m_nTotalPoints = nSize;

	int nPoints = nSize;

	int nSqrtPoints = (int) sqrt((double) nPoints);

	double nLogPoints = 0;
	nPoints--;
	while(nPoints != 0)
	{
		nPoints >>= 1;
		nLogPoints++;
	}

	// pre-compute bit reverse indexes
	nPoints = nSize;
	int rev = 0;
	int halfPoints = nPoints / 2;
    for (int i = 0; i < nPoints - 1; i++)
    {
        m_nBitReverse[i] = rev;
        int mask = halfPoints;
        // add 1 backwards
        while (rev >= mask)
        {
            rev -= mask; // turn off this bit
            mask >>= 1;
        }
        rev += mask;
    }
    m_nBitReverse[nPoints - 1] = nPoints - 1;

	//pre-compute sin and cos values
	for(int c = 0; c <= nPoints; c++)
	{
		double deltaangle = 2.0 * 3.1415926 / (double)c;
		m_fAlpha1[c] = (MY_FLOAT)(2.0 * sin((double)(0.5 * deltaangle)) *
										sin((double)(0.5 * deltaangle)));
		m_fBeta1[c] = (MY_FLOAT) sin((double)(deltaangle));
		deltaangle = -2.0 * 3.1415926 / (double)c;
		m_fAlpha2[c] = (MY_FLOAT)(2.0 * sin((double)(0.5 * deltaangle)) *
										sin((double)(0.5 * deltaangle)));
		m_fBeta2[c] = (MY_FLOAT) sin((double)(deltaangle));
	}

	m_nSamplingRate = m_nTotalPoints * 2;
	m_nInput_pointer = 0;
	m_nOutput_pointer = 0;
}

/* Add - put data in the FFT buffer to be processed */
void CFFT::Add(MY_FLOAT x)
{
	m_fReal_in[m_nInput_pointer] = x;
	m_fImag_in[m_nInput_pointer] = 0;
	m_nInput_pointer++;
};

int CFFT::NumberOfBitsNeeded(int nPowerOfTwo)
{
	int i;
 	for(i = 0; ; i++)
	{
		if(nPowerOfTwo & (1 << i))
		{
			return i;
		}
	}
}

void CFFT::PerformFFT()
{
	int NumSamples = m_nTotalPoints;

	int NumBits;    /* Number of bits needed to store indices */
	int i, k, km2, n;
	int m, m2;

	MY_FLOAT alpha, beta; //used to compute w(m)
	MY_FLOAT delta_w;
	MY_FLOAT tr, ti;      // t real, t imaginary 
	MY_FLOAT wr, wi;      // w real, w imaginary

	NumBits = NumberOfBitsNeeded(NumSamples);

	// Simultaneous data copy and bit-reversal ordering 
	for(i = 0; i < NumSamples; i++ )
	{
		m_fAr[m_nBitReverse[i]] = m_fReal_in[i];
		m_fAi[m_nBitReverse[i]] = m_fImag_in[i];
	}

	// Do the FFT itself...

	m2 = 1;
	for ( m = 2; m <= NumSamples; m <<= 1 )
	{
		alpha	= m_fAlpha1[m]; //2*(sin(PI/m))^2
		beta	= m_fBeta1[m]; //sin(2PI/m)

		for(i = 0; i < NumSamples; i += m)
		{
			wr = 1.0;   // w=1
			wi = 0.0;   

			for(k = i, n = 0; n < m2; k++, n++)
			{
				km2 = k + m2;

				// t=wA[k+m/2]
				tr = wr*m_fAr[km2] - wi*m_fAi[km2];
				ti = wr*m_fAi[km2] + wi*m_fAr[km2];

				// u = A[k]
				// A[k+m/2] = u-t
				m_fAr[km2] = m_fAr[k] - tr;
				m_fAi[km2] = m_fAi[k] - ti;

				// A[k]= u + t;
				m_fAr[k] += tr;
				m_fAi[k] += ti;

				//w = w * w(m)
				delta_w = alpha*wr + beta*wi;
				wi -= (alpha*wi - beta*wr);
				wr -= delta_w;
			}
		}
		m2 = m;
	}
    // reset pointers
	m_nOutput_pointer = 0;
	m_nInput_pointer = 0;
}

