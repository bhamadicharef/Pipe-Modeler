// OrganPipeModel.h : header file
//

#ifndef __OrganPipeModel_H_
#define __OrganPipeModel_H_

#include "TKObject.h"
#include "Model.h"

#include "Noise.h"
#include "Adsr.h"
#include "Asr.h"
#include "EnvExp.h"
#include "LoopWave.h"

#include "JetTable.h"
#include "Polynomial.h"

#include "Filter.h"
#include "OnePole.h"
#include "OneZero.h"
#include "DLineL.h"
#include "DCBlock.h"

#include "Junction.h"
#include "TubeSection.h"
#include "ToneHoleJunction.h"

#include "WavFileOut.h"

class COrganPipeModel : public CModel
{
	DECLARE_DYNAMIC(COrganPipeModel)
	
// Construction
public:
	COrganPipeModel(MY_FLOAT fLowestFrequency = 440.0);
	virtual void Serialize(CArchive& ar);

// Attributes
public:
	CAdsr*			m_pAdsr;
	CAsr*			m_pAsr;
	CPolynomial		m_Polynomial;
protected:
	CNoise*			m_pNoise;
	CDCBlock*		m_pDCBlock2;
	CDLineL*		m_pJetDelayLine;
	CDLineL*		m_pBoreDelayLine;
	CJetTable*		m_pJetTable;
	COnePole*		m_pFilter;
	CDCBlock*		m_pDCBlock;
	CLoopWave*		m_pVibrato;

//	CJunction*			m_pJunction;

	CToneHoleJunction*	m_pToneHoleJunction[NB_TH_JUNCTIONS];
	CJunction*			m_pJunction[NB_JUNCTIONS];
	CTubeSection*		m_pTube[NB_TUBES];

	// Control signals
	MY_FLOAT		m_fLastFrequency;
	MY_FLOAT		m_fFrequency;
	//MY_FLOAT		m_fAmplitude;

	MY_FLOAT		m_fNoiseGain;
	MY_FLOAT		m_fMaxPressure;
	MY_FLOAT		m_fVibratoGain;
	MY_FLOAT		m_fVibratoFrequency;
	MY_FLOAT		m_fJetReflection;
	MY_FLOAT		m_fEndReflection;
	MY_FLOAT		m_fJetRatio;

	MY_FLOAT		m_fOutputToneHole1;
	MY_FLOAT		m_fOutputToneHole2;
	MY_FLOAT		m_fOutputToneHole3;
	MY_FLOAT		m_fOutputBore;

	MY_FLOAT		m_fToneHole1Gain;
	MY_FLOAT		m_fToneHole2Gain;
	MY_FLOAT		m_fToneHole3Gain;
	MY_FLOAT		m_fBoreGain;
	
	MY_FLOAT		m_fOutputGain;

public:
	void			Clear();
	virtual void	SetFrequency(MY_FLOAT fFrequency);
	void			SetJetDelay(MY_FLOAT fJetDelay);

	void			SetNoiseGain(MY_FLOAT fNoiseGain);
	void			SetMaxPressure(MY_FLOAT fMaxPressure);
	void			SetVibratoGain(MY_FLOAT fVibratoGain);
	void			SetVibratoFrequency(MY_FLOAT fVibratoFrequency);
	void			SetJetReflection(MY_FLOAT fJetReflection);
	void			SetEndReflection(MY_FLOAT fEndReflection);
	void			SetBoreGain(MY_FLOAT fBoreGain);
	void			SetToneHole1Gain(MY_FLOAT fToneHole1Gain);
	void			SetToneHole2Gain(MY_FLOAT fToneHole2Gain);
	void			SetToneHole3Gain(MY_FLOAT fToneHole3Gain);

	MY_FLOAT		GetFrequency();
	MY_FLOAT		GetNoiseGain();
	MY_FLOAT		GetMaxPressure();
	MY_FLOAT		GetVibratoGain();
	MY_FLOAT		GetVibratoFrequency();
	MY_FLOAT		GetJetReflection();
	MY_FLOAT		GetEndReflection();
	MY_FLOAT		GetBoreGain();
	MY_FLOAT		GetToneHole1Gain();
	MY_FLOAT		GetToneHole2Gain();
	MY_FLOAT		GetToneHole3Gain();

	// 2 Tubes
	void			SetLengthTube(int nWhichTube, MY_FLOAT fLength);
	void			SetJunctionDiameterLeft(MY_FLOAT fDiameterLeft);
	void			SetJunctionDiameterRight(MY_FLOAT fDiameterRight);

	// Tonehole Junction
	void			SetJunctionDiameterBore(	int nWhichToneHoleJunc,
												MY_FLOAT fDiameter);
	void			SetJunctionDiameterToneHole(	int nWhichToneHoleJunc,
													MY_FLOAT fDiameter);

	MY_FLOAT		GetLengthTube(int nWhichTube);
	MY_FLOAT		GetJunctionDiameterLeft();
	MY_FLOAT		GetJunctionDiameterRight();
	MY_FLOAT		GetJunctionDiameterBore(int nWhichToneHoleJunc);
	MY_FLOAT		GetJunctionDiameterToneHole(int nWhichToneHoleJunc);

	// 2 Tubes
	virtual void	NoteOn(MY_FLOAT fFrequency, MY_FLOAT fAmplitude);
	virtual void	NoteOff(MY_FLOAT fAmplitude);

	MY_FLOAT		Tick();
	MY_FLOAT		LastOut();

	// Save one sec of sound
	void	SaveWavFile(CString strFileName);

// Operators 
public:
	BOOL	m_bModifiedWaveform;
	BOOL	m_bModifiedSpectrum;

// Implementation
public:
	virtual	~COrganPipeModel();
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif	
};

#endif __OrganPipeModel_H_

/////////////////////////////////////////////////////////////////////////////
