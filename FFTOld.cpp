#include "StdAfx.h"
#include <math.h>
#include "FFT.h"

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

#define PI 3.1415926

/* ReverseBits - Reverses "index", assuming that it is
 * a "NumBits"-length number
 */
unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
	unsigned i, rev;

	for(i = rev = 0; i < NumBits; i++ )
	{
		rev = (rev << 1) | (index & 1);
		index >>= 1;
	}
	return rev;
}


/* Determine how many bits long a number is
 */
unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
	unsigned i;
 	for ( i=0; ; i++ )
	{
		if(PowerOfTwo & (1 << i))
		{
			return i;
		}
	}
}

FFT::FFT()
{};

FFT::~FFT()
{};

void FFT::SetSize(int size)
{
	total_points=size;
	int Points=size;
	sqrtPoints = (int)sqrt((double)Points);

    // calculate long base 2 of Points
    logPoints = 0;
    Points--;
    while (Points != 0)
      {Points >>= 1; logPoints++;}

	// pre-compute bit reverse indexes
	Points=size;
	int rev = 0;
	int halfPoints = Points/2;
    for (int i = 0; i < Points - 1; i++)
    {
        bit_reverse[i] = rev;
        int mask = halfPoints;
        // add 1 backwards
        while (rev >= mask)
        {
            rev -= mask; // turn off this bit
            mask >>= 1;
        }
        rev += mask;
    }
    bit_reverse[Points-1] = Points-1;

	//pre-compute sin and cos values
	for (int c=0;c<=Points;c++)
	{
		double deltaangle = 2.0 * 3.1415926 / (double)c;
		alpha1[c] = 2.0 * sin(0.5 * deltaangle) * sin(0.5 * deltaangle);
		beta1[c] = sin(deltaangle);
		deltaangle = -2.0 * 3.1415926 / (double)c;
		alpha2[c] = 2.0 * sin(0.5 * deltaangle) * sin(0.5 * deltaangle);
		beta2[c] = sin(deltaangle);
	}

	sampling_rate=total_points*2;
	input_pointer=0;
	output_pointer=0;
};

void FFT::SetParameters( int samp_rate )
{};

/* Add - put data in the FFT buffer to be processed */
void FFT::Add(short x)
{
	real_in[input_pointer] = (double)x;
	imag_in[input_pointer] = 0;
	input_pointer++;
};

/* Perform the FFT on the data items in the FFT buffer
 */
void FFT::Perform_FFT(void)
{
   unsigned NumSamples=total_points;
  
   unsigned NumBits;    /* Number of bits needed to store indices */
   unsigned i, k, km2, n;
   unsigned m, m2;

   double alpha, beta; //used to compute w(m)
   double delta_w;
   double tr, ti;      // t real, t imaginary 
   double wr, wi;      // w real, w imaginary
   
   NumBits = NumberOfBitsNeeded ( NumSamples );

   // Simultaneous data copy and bit-reversal ordering 
   for ( i=0; i < NumSamples; i++ )
   {
      Ar[bit_reverse[i]] = real_in[i];
      Ai[bit_reverse[i]] = imag_in[i];
   }


   /*
   **   Do the FFT itself...
   */
   m2 = 1;
   for ( m = 2; m <= NumSamples; m <<= 1 )
   {
	alpha=alpha1[m]; //2*(sin(PI/m))^2
	beta =beta1 [m]; //sin(2PI/m)

    for ( i=0; i < NumSamples; i += m )
     {
       wr = 1.0;   // w=1
       wi = 0.0;   

	   for ( k=i, n=0; n < m2; k++, n++ )
		{
           km2 = k + m2;
		   
		   // t=wA[k+m/2]
           tr = wr*Ar[km2] - wi*Ai[km2];
           ti = wr*Ai[km2] + wi*Ar[km2];

		   //u=A[k]
		   //A[k+m/2]=u-t
           Ar[km2] = Ar[k] - tr;
           Ai[km2] = Ai[k] - ti;

		   //A[k]=u+t;
           Ar[k] += tr;
           Ai[k] += ti;

		   //w=w*w(m)
           delta_w = alpha*wr + beta*wi;
           wi -= (alpha*wi - beta*wr);
           wr -= delta_w;
		}
	 }
	m2 = m;
	}
    // reset pointers
	output_pointer = 0;
	input_pointer = 0;
};

int FFT::Get_Out_Power(int x)
{
	long total1 = (long)(sqrt(Ar[x]*Ar[x] + Ai[x]*Ai[x]));
	long ret = 100 * (total1) / total_points / 256 / 4;
	if(ret > 100)
	{
		ret = 100;
	}
	return ret;
}

