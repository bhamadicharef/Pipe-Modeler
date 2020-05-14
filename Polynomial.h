// Polynomial.h : header file
// 


#ifndef __Polynomial_H_
#define __Polynomial_H_

class CPolynomial : public CObject
{
	DECLARE_DYNAMIC(CPolynomial)
	
// Construction
public:
	CPolynomial();
	virtual void Serialize(CArchive& ar);

// Attributes
protected:  
	int			m_nN;
	float		m_fCoef[8];
	float		m_fOldCoef[8];

	float		m_fLastOut;
	
// Operators 
public:

// Implementation
public:
	virtual	~CPolynomial();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	

public:
	void		SetN(int nN);
	int			GetN();
	float		GetCoef(int nCoef);
	void		SetCoef(int nCoef, float fValue);

	void		Clear();
	void		ClearCoefs();
	void		ClearOldCoefs();


	void		SetSlit();							// y = x
	void		SetLinear();						// y = ...
	void		SetCook();							// y = x^3 - x

	float		GetOldCoef(int nCoef);
	void		SetOldCoef(int nCoef, float fValue);
	float		Tick(float fValue);
	float		TickOld(float fValue);

};

#endif

/////////////////////////////////////////////////////////////////////////////
