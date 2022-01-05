@echo off

set PATH_ORIG=%PATH%

set PATH=.;%UGII_ROOT_DIR%;%PATH_ORIG%
"..\..\..\..\..\Framework\bin\Win64\AnsRegSvr32.exe" /u %1\DSPlugInUGCOM.dll