# Microsoft Developer Studio Project File - Name="GUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GUI.mak" CFG="GUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GUI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GUI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GUI - Win32 Release"
# Name "GUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Adsr.cpp
# End Source File
# Begin Source File

SOURCE=.\Asr.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DCBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\DLineL.cpp
# End Source File
# Begin Source File

SOURCE=.\EnvExp.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcitationPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FFT.cpp
# End Source File
# Begin Source File

SOURCE=.\FftEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FilesPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Filter.cpp
# End Source File
# Begin Source File

SOURCE=.\FirstPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI.cpp
# End Source File
# Begin Source File

SOURCE=.\GUI.rc
# End Source File
# Begin Source File

SOURCE=.\GUIDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\JetTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Junction.cpp
# End Source File
# Begin Source File

SOURCE=.\LinearPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\LoopWave.cpp
# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\Noise.cpp
# End Source File
# Begin Source File

SOURCE=.\NonLinearPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OnePole.cpp
# End Source File
# Begin Source File

SOURCE=.\OneZero.cpp
# End Source File
# Begin Source File

SOURCE=.\OrganPipeModel.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PipeEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PipeEditCtrl2.cpp
# End Source File
# Begin Source File

SOURCE=.\Polynomial.cpp
# End Source File
# Begin Source File

SOURCE=.\ReedTable.cpp
# End Source File
# Begin Source File

SOURCE=.\SBDestination.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectrumPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TKObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ToneHoleFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\ToneHoleJunction.cpp
# End Source File
# Begin Source File

SOURCE=.\TubeSection.cpp
# End Source File
# Begin Source File

SOURCE=.\TwoZero.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveEditCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveFormPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\WavFileOut.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Adsr.h
# End Source File
# Begin Source File

SOURCE=.\Asr.h
# End Source File
# Begin Source File

SOURCE=.\BrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=.\CurveEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DCBlock.h
# End Source File
# Begin Source File

SOURCE=.\DLineL.h
# End Source File
# Begin Source File

SOURCE=.\EnvExp.h
# End Source File
# Begin Source File

SOURCE=.\ExcitationPropPage.h
# End Source File
# Begin Source File

SOURCE=.\FFT.h
# End Source File
# Begin Source File

SOURCE=.\FftEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FilesPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Filter.h
# End Source File
# Begin Source File

SOURCE=.\FirstPropPage.h
# End Source File
# Begin Source File

SOURCE=.\GUI.h
# End Source File
# Begin Source File

SOURCE=.\GUIDlg.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\JetTable.h
# End Source File
# Begin Source File

SOURCE=.\Junction.h
# End Source File
# Begin Source File

SOURCE=.\LinearPropPage.h
# End Source File
# Begin Source File

SOURCE=.\LoopWave.h
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# Begin Source File

SOURCE=.\Noise.h
# End Source File
# Begin Source File

SOURCE=.\NonLinearPropPage.h
# End Source File
# Begin Source File

SOURCE=.\OnePole.h
# End Source File
# Begin Source File

SOURCE=.\OneZero.h
# End Source File
# Begin Source File

SOURCE=.\OrganPipeModel.h
# End Source File
# Begin Source File

SOURCE=.\OtherPropPage.h
# End Source File
# Begin Source File

SOURCE=.\OutputPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PipeEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PipeEditCtrl2.h
# End Source File
# Begin Source File

SOURCE=.\Polynomial.h
# End Source File
# Begin Source File

SOURCE=.\ReedTable.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SBDestination.h
# End Source File
# Begin Source File

SOURCE=.\SpectrumPropPage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TKObject.h
# End Source File
# Begin Source File

SOURCE=.\ToneHoleFilter.h
# End Source File
# Begin Source File

SOURCE=.\ToneHoleJunction.h
# End Source File
# Begin Source File

SOURCE=.\TubeSection.h
# End Source File
# Begin Source File

SOURCE=.\TwoZero.h
# End Source File
# Begin Source File

SOURCE=.\WaveEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\WaveEditCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\WaveFormPropPage.h
# End Source File
# Begin Source File

SOURCE=.\WavFileOut.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\GUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\GUI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\s_unilog.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetupWizard.ico
# End Source File
# Begin Source File

SOURCE=.\res\tab.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
