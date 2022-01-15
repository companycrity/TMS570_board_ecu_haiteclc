@echo off

REM ********************************** RUN CCT *********************************

%CD%\..\..\Tools\CCT\cct -NoSort %1.out


REM ******************************* RUN apmem.vbs ******************************

cscript //NoLogo %CD%\..\..\Tools\Postbuild\apmem.vbs %CD%\..\..\Tools\AsrProject\Config\ECUC\EPS.ecuc.arxml %CD%\%1.map
