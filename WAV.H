// WAV.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WAV file defs

#ifndef __WAVE_H_
#define __WAVE_H_

#define WAVE_MONO					1
#define WAVE_STEREO					2

#define WAVE_8BIT					8
#define WAVE_16BIT					16
#define WAVE_32BIT					32

#define WAVE_FORMAT_UNKNOWN			0x0000
#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM				0x0001
#endif
#define WAVE_FORMAT_ADPCM			0x0002
#define WAVE_FORMAT_ALAW			0x0006
#define WAVE_FORMAT_MULAW			0x0007
#define WAVE_FORMAT_OKI_ADPCM		0x0010
#define WAVE_FORMAT_DIGISTD			0x0015
#define WAVE_FORMAT_DIGIFIX			0x0016
#define IBM_FORMAT_MULAW			0x0101
#define IBM_FORMAT_ALAW				0x0102
#define IBM_FORMAT_ADPCM			0x0103

#endif

/////////////////////////////////////////////////////////////////////////////
