# Microsoft Developer Studio Project File - Name="Core2Test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Core2Test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Core2Test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Core2Test.mak" CFG="Core2Test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Core2Test - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Core2Test - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Core2Test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CORE2TEST_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "Core2" /I "ivp\ivp_physics" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CORE2TEST_EXPORTS" /FR /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib psapi.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "Core2Test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CORE2TEST_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CORE2TEST_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Core2Test - Win32 Release"
# Name "Core2Test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Core2Test.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Core2"

# PROP Default_Filter ""
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core2\Common\Archetype.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CArchGroup.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CArchGroupManager.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CEqObj.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CEquip.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CEquipManager.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CObject.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CollisionGroupDesc.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\Common.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\CSimple.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\EngineObject.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\EquipDesc.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\EquipDescList.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\IBehaviorManager.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\ID_String.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\IEngineInstance.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\IVP.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\PhySys.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Common\Watchable.h
# End Source File
# End Group
# Begin Group "Freelancer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core2\Freelancer\EngineCamera.h
# End Source File
# Begin Source File

SOURCE=.\Core2\Freelancer\Freelancer.cpp
# End Source File
# Begin Source File

SOURCE=.\Core2\Freelancer\Freelancer.h
# End Source File
# End Group
# Begin Group "DALib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core2\DALib\IEngine.h
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core2\Util\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Core2\Util\Memory.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Core2\FLDefs.h
# End Source File
# Begin Source File

SOURCE=.\Core2\protos.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
