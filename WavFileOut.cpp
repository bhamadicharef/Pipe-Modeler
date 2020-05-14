// WavFileOut.cpp : implementation file
//

#include "stdafx.h"
#include "WavFileOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWavFileOut

IMPLEMENT_DYNAMIC(CWavFileOut, CObject)

CWavFileOut::CWavFileOut()
{
	ASSERT_VALID(this);
	Clear();
}

CWavFileOut::~CWavFileOut()
{
}

void CWavFileOut::Clear()
{
	for(int i = 0; i < SRATE; i++)
	{
		for(int j = 0; j < NB_CHANNELS; j++)
		{
			m_fData[j][i] = 0.0;
		}
	}
	m_nCounter = 0;
	m_dwLength = (DWORD) SRATE;
	m_wFrequency = (WORD) SRATE;
}

/////////////////////////////////////////////////////////////////////////////
// CADSR serialization

void CWavFileOut::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);
	int i, j;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		for(i = 0; i < SRATE; i++)
		{
			for(j = 0; j < NB_CHANNELS; j++)
			{
				ar << m_fData[j][i];
			}
		}
	}
	else
	{
		// TODO: add loading code here
		for(i = 0; i < SRATE; i++)
		{
			for(j = 0; j < NB_CHANNELS; j++)
			{
				ar >> m_fData[j][i];
			}
		}
	}
}

#ifdef _DEBUG
void CWavFileOut::Dump( CDumpContext& dc ) const
{
	// Call base class function first
	CObject::Dump( dc );
//	dc	<< "ADSR: Value: " << m_Value << "\n"
//		<< "ADSR: State: " << m_State;
}
#endif
  
/////////////////////////////////////////////////////////////////////////////
// CWavFileOut Observators

/////////////////////////////////////////////////////////////////////////////
// CWavFileOut Functions

void CWavFileOut::Tick(float fSampleMain, float fSampleToneHole)
{
	ASSERT(this);
	m_fData[0][m_nCounter] = fSampleMain;
	m_fData[1][m_nCounter] = fSampleToneHole / 3;
	m_nCounter++;
	if(m_nCounter == SRATE)
	{
		m_nCounter = 0;
	}
}

void CWavFileOut::Save(CString strFilePath)
{
	CFile WAVFile;
	CFileException WAVFileException;

	if(!WAVFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite, &WAVFileException))
	{
		CString strError;
		if(WAVFileException.m_cause == CFileException::badPath)
		{
			strError.Format("Error: All or part of the path is invalid");
		}
		else if(WAVFileException.m_cause == CFileException::accessDenied)
		{
			strError.Format("Error: File Access Denied");
		}
		else
		{
			strError.Format("Error: FileException %d", WAVFileException.m_cause);
		}
		AfxMessageBox(strError);
	}
	else
	{
		CWaitCursor wait;    // display wait cursor

		char Chunk[5];
		strcpy(Chunk, "RIFF");
		WAVFile.Write(Chunk, 4);
		//TRACE("WAV: (4) RIFF written\n");

		LONG ChunkLength = (2 * m_dwLength) + 36;
		WAVFile.Write(&ChunkLength, sizeof(LONG));
		//TRACE1("WAV: (8) RIFF Chunk Length = %d\n", ChunkLength);

		strcpy(Chunk, "WAVE");
		WAVFile.Write(Chunk, 4);
		//TRACE("WAV: (4) WAVE chunck written\n");

		strcpy(Chunk, "fmt ");
		WAVFile.Write(Chunk, 4);
		//TRACE("WAV: (4) fmt chunck written\n");

		LONG FormatLength = WAVE_16BIT;
		WAVFile.Write(&FormatLength, sizeof(LONG));
		//TRACE1("WAV: (4) FormatLength = %d\n", FormatLength);

		WORD wFormatData = WAVE_FORMAT_PCM;
		WAVFile.Write(&wFormatData, sizeof(WORD));
		//TRACE1("WAV: (2) FormatData = %d\n", wFormatData);

		WORD wChannels = WAVE_MONO;
		WAVFile.Write(&wChannels, sizeof(WORD));
		//TRACE1("WAV: (2) wChannels = %d\n", wChannels);

		LONG SamplePerSec = (LONG) m_wFrequency;
		WAVFile.Write(&SamplePerSec, sizeof(LONG));
		//TRACE1("WAV: (4) SamplePerSec (Fs) = %d\n", SamplePerSec);

		LONG AvrBytesPerSec = (LONG) (m_wFrequency * wChannels * (FormatLength / 8));
		WAVFile.Write(&AvrBytesPerSec, sizeof(LONG));
		//TRACE1("WAV: (4) AvrBytesPerSec (Fs) = %d\n", AvrBytesPerSec);

		WORD wBlockAlign = (WORD) (wChannels * (FormatLength / 8));
		WAVFile.Write(&wBlockAlign, sizeof(WORD));
		//TRACE1("WAV: (2) wBlockAlign = %d\n", wBlockAlign);

		WORD wFormatSpecific = (WORD)(8 * (FormatLength / 8));
		WAVFile.Write(&wFormatSpecific, sizeof(WORD));
		//TRACE1("WAV: (2) wFormatSpecific = %d\n", wFormatSpecific);

		strcpy(Chunk, "data");
		WAVFile.Write(Chunk, 4);
		//TRACE("WAV: (4) data chunck written\n");

		LONG DataLengthBytes = (LONG) (m_dwLength * (FormatLength / 8));
		WAVFile.Write(&DataLengthBytes, sizeof(LONG));
		//TRACE1("WAV: (4) DataLengthBytes = %d\n", DataLengthBytes);

		WORD wData[88200];
		for(DWORD i = 0; i < m_dwLength; i++)
		{
			wData[i] = 0;
		}
/*
		float fDataPos, fMax = 0.0;
		for(i = 0; i < m_dwLength; i++)
		{
			fDataPos = (float) fabs(m_fData[i]);
			if(fDataPos > fMax)
				fMax = fDataPos;
		}
		fMax = 1 / fMax;
		for(i = 0; i < m_dwLength; i++)
		{
			m_fData[i] *= fMax;
		}
*/
		// First conversion to WORDs then save big block into file
		// Sequencial saving do not work... why ?
		float fData = 0;
		int nData = 0;
		for(int i = 0; i < m_dwLength; i++)
		{
			nData = (int) floor(m_fData[0][i] * 32767.0);
			wData[i] = (WORD) nData;
			//wData = (WORD) (i);
			//wData += (WORD) ((float)((m_fData[i++] + 1) * 32767.0));
			//TRACE("Data =[%d] %d\n", i, wData);
			//WAVFile.Write(&wData, sizeof(WORD));
		}
		WAVFile.Write((WORD*)wData, DataLengthBytes);
		WAVFile.Close();
	}
}

