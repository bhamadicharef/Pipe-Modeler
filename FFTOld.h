#ifndef FFT_H
#define FFT_H

class FFT
{
public:
	FFT ();
	~FFT ();
	void SetSize(int size);
	void Add(short x);
	void SetParameters( int samp_rate );
	void Perform_FFT(void);
	int  Get_Out_Power(int x);
private:
	int input_pointer;
	int total_points;
	int logPoints, sqrtPoints;
	int output_pointer;
	int sampling_rate;
	int bit_reverse[32768];
	double real_in[32768], Ar[32768];
	double imag_in[32768], Ai[32768];
	double alpha1[32768+1], beta1[32768+1];
	double alpha2[32768+1], beta2[32768+1];
};
#endif
