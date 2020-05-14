// OrganPipeModel.cpp : implementation file
//

#include "stdafx.h"
#include "OrganPipeModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrganPipeModel

IMPLEMENT_DYNAMIC(COrganPipeModel, CObject)

COrganPipeModel::COrganPipeModel(MY_FLOAT fLowestFrequency /* = 440 */)
{
	ASSERT_VALID(this);

	int i;
	long length;

	length = (long) (SRATE / fLowestFrequency + 1);
	m_pBoreDelayLine = new CDLineL(length);
	length >>= 1;
	m_pJetDelayLine = new CDLineL(length);

	m_pNoise = new CNoise;
	m_pAdsr = new CAdsr;
	m_pAsr = new CAsr;
	m_pFilter = new COnePole;
	m_pJetTable = new CJetTable;
	m_pDCBlock = new CDCBlock;
	m_pDCBlock2 = new CDCBlock;

	m_pVibrato = new CLoopWave();
/*
	// OF  14/04/99

	// Very defensive new object allocation
	m_pJunction = NULL;
	m_pJunction = new CJunction;
	if(m_pJunction != NULL)
		ASSERT(FALSE)
*/
	for(i = 0; i < NB_JUNCTIONS; i++)
	{
		m_pJunction[i] = new CJunction;
		m_pJunction[i]->SetDiameterLeft((MY_FLOAT) 0.25);
		m_pJunction[i]->SetDiameterRight((MY_FLOAT) 0.5);
	}

	
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_pToneHoleJunction[i] = new CToneHoleJunction;
		m_pToneHoleJunction[i]->SetDiameterBore((MY_FLOAT) 0.25);
		m_pToneHoleJunction[i]->SetDiameterToneHole((MY_FLOAT) 0.5);
	}
	
	m_pToneHoleJunction[1]->SetDiameterToneHole((MY_FLOAT) 0.0);
	m_pToneHoleJunction[2]->SetDiameterToneHole((MY_FLOAT) 0.0);

	for(i = 0; i < NB_TUBES; i++)
	{
		m_pTube[i] = new CTubeSection;
		m_pTube[i]->SetLength((MY_FLOAT) 0.25 * 256.0);
	}

	m_fToneHole1Gain = (MY_FLOAT) 0.85;
	m_fToneHole2Gain = (MY_FLOAT) 0.85;
	m_fToneHole3Gain = (MY_FLOAT) 0.85;
	m_fBoreGain = (MY_FLOAT) 0.85;

	this->Clear();

	//m_pBoreDelayLine->SetDelay((MY_FLOAT) 100.0);
	m_pJetDelayLine->SetDelay((MY_FLOAT) 49.0);

	m_pFilter->SetPole((MY_FLOAT) 0.7 -
			((MY_FLOAT) 0.1 * (MY_FLOAT) 22050.0 / (MY_FLOAT) SRATE));
	m_pFilter->SetGain((MY_FLOAT) -1.0);


	m_fVibratoFrequency = (MY_FLOAT) 5.925;
	m_pVibrato->SetFrequency(m_fVibratoFrequency);
	m_pVibrato->Normalize();

	//m_pAdsr->SetAllTimes((MY_FLOAT) 250, (MY_FLOAT) 250, (MY_FLOAT) 250, (MY_FLOAT) 250);
	//m_pAdsr->SetDecay((MY_FLOAT) 0.5);

	m_pAsr->SetAttackTime((MY_FLOAT) 50);
	m_pAsr->SetSustainTime((MY_FLOAT) 250);
	m_pAsr->SetReleaseTime((MY_FLOAT) 100);

	m_fNoiseGain = (MY_FLOAT) 0.3;
	m_fMaxPressure = (MY_FLOAT) 0.95;

	m_fEndReflection = (MY_FLOAT) 0.5;
	m_fJetReflection = (MY_FLOAT) 0.5;
	m_fVibratoGain = (MY_FLOAT) 0.05;
	// ??
	m_fJetRatio = (MY_FLOAT) 0.5; //0.32;

	m_fOutputGain = (MY_FLOAT) 0.6;

	m_bModifiedWaveform = FALSE;
	m_bModifiedSpectrum = FALSE;
}

COrganPipeModel::~COrganPipeModel()
{
	int i;

	delete m_pNoise;
	delete m_pAdsr;
	delete m_pAsr;
	delete m_pJetDelayLine;
	delete m_pBoreDelayLine;
	delete m_pFilter;
	delete m_pDCBlock;
	delete m_pDCBlock2;
	delete m_pJetTable;
	delete m_pVibrato;

	for(i = 0; i < NB_JUNCTIONS; i++)
	{
		delete m_pJunction[i];
	}

	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		delete m_pToneHoleJunction[i];
	}
	for(i = 0; i < NB_TUBES; i++)
	{
		delete m_pTube[i];
	}
}

void COrganPipeModel::Clear()
{
	int i;

	m_pJetDelayLine->Clear();
	m_pBoreDelayLine->Clear();
	m_pFilter->Clear();
	m_pDCBlock->Clear();
	m_WavFileOut.Clear();
	m_Polynomial.Clear();
	// Clear Bore consisting of 2 Tubes and a Junction
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_pToneHoleJunction[i]->Clear();
	}
	for(i = 0; i < NB_JUNCTIONS; i++)
	{
		m_pJunction[i]->Clear();
	}
	for(i = 0; i < NB_TUBES; i++)
	{
		m_pTube[i]->Clear();
	}
	
	m_fOutputToneHole1 = (MY_FLOAT) 0.0;
	m_fOutputToneHole2 = (MY_FLOAT) 0.0;
	m_fOutputToneHole3 = (MY_FLOAT) 0.0;
	m_fOutputBore = (MY_FLOAT) 0.0;
}


/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void COrganPipeModel::Serialize(CArchive& ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_fLastFrequency;
		ar << m_fFrequency;
		ar << m_fNoiseGain;
		ar << m_fMaxPressure;
		ar << m_fVibratoGain;
		ar << m_fVibratoFrequency;
		ar << m_fJetReflection;
		ar << m_fEndReflection;
		ar << m_fJetRatio;
		ar << m_fOutputGain;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_fLastFrequency;
		ar >> m_fFrequency;
		ar >> m_fNoiseGain;
		ar >> m_fMaxPressure;
		ar >> m_fVibratoGain;
		ar >> m_fVibratoFrequency;
		ar >> m_fJetReflection;
		ar >> m_fEndReflection;
		ar >> m_fJetRatio;
		ar >> m_fOutputGain;
	}
	m_pAsr->Serialize(ar);
	m_pJetDelayLine->Serialize(ar);
	m_pBoreDelayLine->Serialize(ar);
	m_pFilter->Serialize(ar);
	m_pDCBlock->Serialize(ar);
	m_Polynomial.Serialize(ar);

	// Serialise Bore consisting of 2 Tubes and a Junction
	for(i = 0; i < NB_TH_JUNCTIONS; i++)
	{
		m_pToneHoleJunction[i]->Serialize(ar);
	}
	for(i = 0; i < NB_JUNCTIONS; i++)
	{
		m_pJunction[i]->Serialize(ar);
	}
	for(i = 0; i < NB_TUBES; i++)
	{
		m_pTube[i]->Serialize(ar);
	}
}

#ifdef _DEBUG
void COrganPipeModel::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// COrganPipeModel Observators

MY_FLOAT COrganPipeModel::GetFrequency()
{
	//TRACE("Frequency = %f\n", m_fFrequency);
	return m_fFrequency;
}

MY_FLOAT COrganPipeModel::GetNoiseGain()
{
	//TRACE("NoiseGain = %f\n", m_fNoiseGain);
	return m_fNoiseGain;
}

MY_FLOAT COrganPipeModel::GetMaxPressure()
{
	//TRACE("MaxPressure = %f\n", m_fMaxPressure);
	return m_fMaxPressure;
}

MY_FLOAT COrganPipeModel::GetVibratoGain()
{
	//TRACE("VibratoGain = %f\n", m_fVibratoGain);
	return m_fVibratoGain;
}

MY_FLOAT COrganPipeModel::GetVibratoFrequency()
{
	//TRACE("VibratoFreq = %f\n", m_fVibratoFrequency);
	return m_fVibratoFrequency;
}

MY_FLOAT COrganPipeModel::GetEndReflection()
{
	//TRACE("EndReflection = %f\n", m_fEndReflection);
	return m_fEndReflection;
}

MY_FLOAT COrganPipeModel::GetJetReflection()
{
	//TRACE("JetReflection = %f\n", m_fJetReflection);
	return m_fJetReflection;
}

MY_FLOAT COrganPipeModel::GetBoreGain()
{
	//TRACE("GetOutputGain = %f\n", m_fOutputGain);
	return m_fBoreGain;
}

MY_FLOAT COrganPipeModel::GetToneHole1Gain()
{
	//TRACE("GetOutputGain = %f\n", m_fOutputGain);
	return m_fToneHole1Gain;
}

MY_FLOAT COrganPipeModel::GetToneHole2Gain()
{
	//TRACE("GetOutputGain = %f\n", m_fOutputGain);
	return m_fToneHole2Gain;
}

MY_FLOAT COrganPipeModel::GetToneHole3Gain()
{
	//TRACE("GetOutputGain = %f\n", m_fOutputGain);
	return m_fToneHole3Gain;
}


/////////////////////////////////////////////////////////////////////////////

void COrganPipeModel::SetLengthTube(int nWhichTube, MY_FLOAT fLength)
{
	ASSERT(m_pTube[nWhichTube] != NULL);
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	m_pTube[nWhichTube]->SetLength(fLength);
}

void COrganPipeModel::SetJunctionDiameterLeft(MY_FLOAT fDiameterLeft)
{
	ASSERT(m_pJunction != NULL);
	m_pJunction[0]->SetDiameterLeft(fDiameterLeft);
}

void COrganPipeModel::SetJunctionDiameterRight(MY_FLOAT fDiameterRight)
{
	ASSERT(m_pJunction != NULL);
	m_pJunction[0]->SetDiameterRight(fDiameterRight);
}

void COrganPipeModel::SetJunctionDiameterBore(	int nWhichToneHoleJunc,
												MY_FLOAT fDiameter)
{
	ASSERT(m_pToneHoleJunction[nWhichToneHoleJunc] != NULL);
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	m_pToneHoleJunction[nWhichToneHoleJunc]->SetDiameterBore(fDiameter);
}

void COrganPipeModel::SetJunctionDiameterToneHole(	int nWhichToneHoleJunc,
													MY_FLOAT fDiameter)
{
	ASSERT(m_pToneHoleJunction[nWhichToneHoleJunc] != NULL);
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	m_pToneHoleJunction[nWhichToneHoleJunc]->SetDiameterToneHole(fDiameter);
}

////////////////////////////////////////////////////////////////////////////////////

MY_FLOAT COrganPipeModel::GetLengthTube(int nWhichTube)
{
	ASSERT(m_pTube[nWhichTube] != NULL);
	ASSERT(nWhichTube >= 0);
	ASSERT(nWhichTube < NB_TUBES);
	return m_pTube[nWhichTube]->GetLength();
}

MY_FLOAT COrganPipeModel::GetJunctionDiameterBore(int nWhichToneHoleJunc)
{
	ASSERT(m_pToneHoleJunction[nWhichToneHoleJunc] != NULL);
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	return m_pToneHoleJunction[nWhichToneHoleJunc]->GetDiameterBore();
}

MY_FLOAT COrganPipeModel::GetJunctionDiameterToneHole(int nWhichToneHoleJunc)
{
	ASSERT(m_pToneHoleJunction[nWhichToneHoleJunc] != NULL);
	ASSERT(nWhichToneHoleJunc >= 0);
	ASSERT(nWhichToneHoleJunc < NB_TH_JUNCTIONS);
	return m_pToneHoleJunction[nWhichToneHoleJunc]->GetDiameterToneHole();
}

/////////////////////////////////////////////////////////////////////////////
// COrganPipeModel Functions

void COrganPipeModel::NoteOn(MY_FLOAT fFrequency, MY_FLOAT fAmplitude)
{
}

void COrganPipeModel::NoteOff(MY_FLOAT fAmplitude)
{
}

/////////////////////////////////////////////////////////////////////////////

void COrganPipeModel::SetFrequency(MY_FLOAT fFrequency)
{
	m_fFrequency = fFrequency;
	m_fLastFrequency = fFrequency * (MY_FLOAT) 0.66666;
	//TRACE("Frequency (Hz)= %f\n", m_fFrequency);
	MY_FLOAT fDelay;
	fDelay = (MY_FLOAT) SRATE / m_fLastFrequency - (MY_FLOAT) 2.0;
	//TRACE("Delay = %f\n", fDelay);
	//m_pBoreDelayLine->SetDelay(fDelay);
	// BHC JT TODO

	for(int i = 0; i < NB_TUBES; i++)
	{
		m_pTube[i]->SetLength(fDelay / NB_TUBES);
	}
	m_pJetDelayLine->SetDelay(fDelay * m_fJetRatio);
}

void COrganPipeModel::SetJetDelay(MY_FLOAT fJetRatio)
{
	MY_FLOAT fTemp;
	fTemp = ((MY_FLOAT) SRATE / m_fLastFrequency) - (MY_FLOAT) 2.0;
	m_fJetRatio = fJetRatio;
	m_pJetDelayLine->SetDelay(fTemp * m_fJetRatio);
	//TRACE("New JetRatio = %f\n", m_fJetRatio);
}

void COrganPipeModel::SetNoiseGain(MY_FLOAT fNoiseGain)
{
	ASSERT(fNoiseGain >= 0);
	ASSERT(fNoiseGain <= 1.0);
	m_fNoiseGain = fNoiseGain;
	//TRACE("New NoiseGain  = %f\n", m_fNoiseGain);
}

void COrganPipeModel::SetMaxPressure(MY_FLOAT fMaxPressure)
{
	m_fMaxPressure = fMaxPressure;
	//TRACE("New MaxPressure = %f\n", m_fMaxPressure);
}

void COrganPipeModel::SetVibratoGain(MY_FLOAT fVibratoGain)
{
	m_fVibratoGain = fVibratoGain;
//	TRACE("New VibratoGain  = %f\n", m_fVibratoGain);
}

void COrganPipeModel::SetVibratoFrequency(MY_FLOAT fVibratoFrequency)
{
	m_fVibratoFrequency = fVibratoFrequency;
	m_pVibrato->SetFrequency(m_fVibratoFrequency);
	//TRACE("New VibratoFreq  = %f\n", m_fVibratoFrequency);
}

void COrganPipeModel::SetJetReflection(MY_FLOAT fJetReflection)
{
	ASSERT(fJetReflection >= 0);
	ASSERT(fJetReflection <= 1.0);
	m_fJetReflection = fJetReflection;
	//TRACE("New JetReflection = %f\n", m_fJetReflection);
}

void COrganPipeModel::SetEndReflection(MY_FLOAT fEndReflection)
{
	ASSERT(fEndReflection >= 0);
	ASSERT(fEndReflection <= 1.0);
	m_fEndReflection = fEndReflection;
	//TRACE("New JetReflection = %f\n", m_fEndReflection);
}

void COrganPipeModel::SetBoreGain(MY_FLOAT fBoreGain)
{
	ASSERT(fBoreGain >= 0);
	ASSERT(fBoreGain <= 1.0);
	m_fBoreGain = fBoreGain;
	//TRACE("New OutputGain = %f\n", m_fOutputGain);
}

void COrganPipeModel::SetToneHole1Gain(MY_FLOAT fToneHole1Gain)
{
	ASSERT(fToneHole1Gain >= 0);
	ASSERT(fToneHole1Gain <= 1.0);
	m_fToneHole1Gain = fToneHole1Gain;
}

void COrganPipeModel::SetToneHole2Gain(MY_FLOAT fToneHole2Gain)
{
	ASSERT(fToneHole2Gain >= 0);
	ASSERT(fToneHole2Gain <= 1.0);
	m_fToneHole2Gain = fToneHole2Gain;
}

void COrganPipeModel::SetToneHole3Gain(MY_FLOAT fToneHole3Gain)
{
	ASSERT(fToneHole3Gain >= 0);
	ASSERT(fToneHole3Gain <= 1.0);
	m_fToneHole3Gain = fToneHole3Gain;
}

/////////////////////////////////////////////////////////////////////////////

MY_FLOAT COrganPipeModel::Tick()
{
	MY_FLOAT fTemp = (MY_FLOAT) 0.0;
	MY_FLOAT fPressureDiff = (MY_FLOAT) 0.0;
	MY_FLOAT fRandPressure = (MY_FLOAT) 0.0;
	MY_FLOAT fBreathPressure = (MY_FLOAT) 0.0;

//	fBreathPressure = m_fMaxPressure * m_pAdsr->Tick();
	fBreathPressure = m_fMaxPressure * m_pAsr->Tick();
	fRandPressure = m_fNoiseGain * m_pNoise->Tick();
	fRandPressure += m_fVibratoGain * m_pVibrato->Tick();
	fRandPressure *= fBreathPressure;

	m_pFilter->Tick(m_pTube[3]->LastOutRight());
//	fTemp = m_pFilter->Tick(m_pBoreDelayLine->LastOut());
	fTemp = m_pDCBlock->Tick(m_pTube[0]->LastOutLeft());

	fPressureDiff = fBreathPressure + fRandPressure - (fTemp * m_fJetReflection);
	fPressureDiff = m_pJetDelayLine->Tick(fPressureDiff);
	fPressureDiff = m_Polynomial.Tick(fPressureDiff) + (m_fEndReflection * fTemp);
//	fPressureDiff = m_pJetTable->Tick(fPressureDiff) + (m_fEndReflection * fTemp);

/*
	m_pTube1->Tick(fPressureDiff, m_pJunction->LastOutLeft());
	m_pJunction->Tick(m_pTube1->LastOutRight(), m_pTube2->LastOutLeft());
	m_pTube2->Tick(m_pJunction->LastOutRight(), m_pFilter->LastOut());
*/
	m_pTube[0]->Tick(	fPressureDiff,
						m_pToneHoleJunction[0]->LastOutLeft());

/*
	for(int i = 0; i < NB_TH_JUNCTIONS - 1; i++)
	{
		m_pToneHoleJunction[i]->Tick(	m_pTube[i]->LastOutRight(),
										m_pTube[i+1]->LastOutLeft(),
										0);
		
		m_pTube[i+1]->Tick(	m_pToneHoleJunction[i]->LastOutRight(),
							m_pToneHoleJunction[i+1]->LastOutLeft());
	}
*/
	
	m_pToneHoleJunction[0]->Tick(	m_pTube[0]->LastOutRight(),
									m_pTube[1]->LastOutLeft(),
									0);
	
	m_pTube[1]->Tick(	m_pToneHoleJunction[0]->LastOutRight(),
						m_pToneHoleJunction[1]->LastOutLeft());
	
	m_pToneHoleJunction[1]->Tick(	m_pTube[1]->LastOutRight(),
									m_pTube[2]->LastOutLeft(),
									0);

	m_pTube[2]->Tick(	m_pToneHoleJunction[1]->LastOutRight(),
						m_pToneHoleJunction[2]->LastOutLeft());
	
	m_pToneHoleJunction[2]->Tick(	m_pTube[2]->LastOutRight(),
									m_pTube[3]->LastOutLeft(),
									0);

	m_pTube[3]->Tick(	m_pToneHoleJunction[2]->LastOutRight(),
						m_pFilter->LastOut());


	m_fOutputBore = m_fOutputGain * m_pDCBlock2->Tick((MY_FLOAT) 0.3 * m_pFilter->LastOut());
	m_fOutputToneHole1 = m_fToneHole1Gain * m_pToneHoleJunction[0]->LastOutToneHole();
	m_fOutputToneHole2 = m_fToneHole2Gain * m_pToneHoleJunction[1]->LastOutToneHole();
	m_fOutputToneHole3 = m_fToneHole3Gain * m_pToneHoleJunction[2]->LastOutToneHole();

	m_fLastOutput = (m_fOutputBore + m_fOutputToneHole1 + m_fOutputToneHole2 + m_fOutputToneHole3) / 4;
	m_WavFileOut.Tick(m_fLastOutput, m_fOutputToneHole1);

	return m_fLastOutput;
}

MY_FLOAT COrganPipeModel::LastOut()
{
	return m_fLastOutput;
}

void COrganPipeModel::SaveWavFile(CString strFileName)
{
	m_WavFileOut.Save(strFileName);
}

