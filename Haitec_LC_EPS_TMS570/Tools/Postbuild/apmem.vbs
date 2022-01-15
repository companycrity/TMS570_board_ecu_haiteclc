' ======================================================================================================================
'   FILE INFO
' ======================================================================================================================
' Copyright 2015 Nexteer Automotive, All Rights Reserved.
' Nexteer Confidential
'
' File Name  : apmem.vbs
' Description: This script analyzes the declared sizes of each application and compares them to actual usage
' Author     : Owen Tosh



' ======================================================================================================================
'   VERSION CONTROL
' ======================================================================================================================
' Date       Rev      Author   Change Description                                                               SCR #
' --------   -------  -------  ------------------------------------------------------------------------------  -------
' 09/04/15    1       OT       Initial version
iVersion =    1



' ======================================================================================================================
'   DESIGN NOTES
' ======================================================================================================================

' This script can be run either in GUI with no arguments, or from the command line with arguments.  It can be integrated
' into the postbuild batch file in this way.

' Command Line Usage:
'		cscript.exe apmem.vbs "C:\Path\ECUCfile.arxml" "C:\Path\Mapfile.map"

' The postbuild.bat command might look like this:
'		cscript //NoLogo %CD%\..\..\Tools\Postbuild\apmem.vbs %CD%\..\..\Tools\AsrProject\Config\ECUC\EPS.ecuc.arxml %CD%\%1.map



' ======================================================================================================================
'   FUTURE PLANS
' ======================================================================================================================

' - allow browsing for a map file if one isn't found (for some reason, this is ridiculously difficult on win7)
' - expand to measuring other configurable sizes (stacks, IRQs, OS sections, etc)



' ======================================================================================================================
'   CONFIGURATION
' ======================================================================================================================

' If the usage is lower than this percentage of the declared size, display a message (should never be more than 0.5)
fWarningSizeFactor = 0.35

' Ignore "section larger than it needs to be" messages on sections up to this size
iWarningSizeThresh = 1024

' When True, creates a debug output file - only enable for debug or development
bDebug = False



' ======================================================================================================================
'   SET UP SYSTEM OBJECTS AND PATHS
' ======================================================================================================================

Set oShl = WScript.CreateObject("WScript.Shell")
Set oFSO = WScript.CreateObject("Scripting.FileSystemObject")
Set oShlApp = WScript.CreateObject("Shell.Application")

If bDebug = True Then
	Set tsTemp = oFSO.OpenTextFile("_apmemvbsdebug.txt", 2, True)
	tsTemp.WriteLine("=============================")
	tsTemp.WriteLine("Debug dump file for apmem.vbs")
	tsTemp.WriteLine("=============================")
	tsTemp.WriteLine("Script Version " & iVersion)
	tsTemp.WriteLine("Run on " & Now())
	tsTemp.WriteLine()
End If



' ======================================================================================================================
'   SELECT FILES
' ======================================================================================================================

If LCase(Right(WScript.FullName, 11)) = "cscript.exe" Then
	
	If WScript.Arguments.Count <> 2 Then
		Report "usage: cscript.exe apmem.vbs EPS.ecuc.arxml mapfile.map"
		WScript.Quit 0
	End If
	
	Report vbCrLf & "Ap Memory Analysis - started"
	
	sEcucFile = WScript.Arguments(0)
	sMapFile = WScript.Arguments(1)
	
Else
	
	Set oFolder = oShlApp.BrowseForFolder(0, "Select project folder", &H240&)
	
	If oFolder Is Nothing Then
		WScript.Quit 0
	End If
	
	sEcucFile = oFolder.Self.Path & "\Tools\AsrProject\Config\ECUC\EPS.ecuc.arxml"
	
	bFound = False
	If oFSO.FolderExists(oFolder.Self.Path & "\SwProject\Debug") Then
		Set oFolder = oFSO.GetFolder(oFolder.Self.Path & "\SwProject\Debug")
		For Each oFile In oFolder.Files
			If LCase(Right(oFile.Name, 4)) = ".map" Then
				sMapFile = oFile.Path
				bFound = True
			End If
		Next
	End If
	
	If bFound = False Then
		ReportError "Cannot find map file - the selected folder must have a map file in it"
		WScript.Quit 1
	End If
	
End If


If bDebug = True Then
	tsTemp.WriteLine("Config file selected:")
	tsTemp.WriteLine(sEcucFile)
	tsTemp.WriteLine()
	tsTemp.WriteLine("Map file selected:")
	tsTemp.WriteLine(sMapFile)
	tsTemp.WriteLine()
End If



' ======================================================================================================================
'   OPEN FILES
' ======================================================================================================================

' Open EPS.ecuc.arxml (ECUC xml)
Set xmlEcuc = CreateObject("Microsoft.XMLDOM")
xmlEcuc.Async = "False"

If Not xmlEcuc.Load(sEcucFile) Then
	ReportError "Cannot load EPS.ecuc.arxml - is the script pointed at the right location?"
	WScript.Quit 1
End If

Set tsMapFile = oFSO.OpenTextFile(sMapFile, 1)



' ======================================================================================================================
'   PARSE XML FILE
' ======================================================================================================================

' Get list of Aps and sizes

Dim sAps()
Dim iEcuciSizes()
Dim iEcucuSizes()
ReDim sAps(0)
ReDim iEcuciSizes(0)
ReDim iEcucuSizes(0)
sAps(0) = ""
iEcuciSizes(0) = -1
iEcucuSizes(0) = -1

bNewOs = False

Set oXmlNodes = xmlEcuc.selectNodes("/AUTOSAR/TOP-LEVEL-PACKAGES/AR-PACKAGE" & _
									"/ELEMENTS/MODULE-CONFIGURATION [SHORT-NAME = 'Os']/CONTAINERS" & _
									"/CONTAINER [DEFINITION-REF = '/MICROSAR/TMS570LS3x/Os/OsApplication']/SHORT-NAME")

If oXmlNodes.length = 0 Then
	ReportError "Didn't find any aps - are you sure this is the right xml file?"
	WScript.Quit 1
End If

For Each oXmlNode in oXmlNodes
	
	Set oXmlNodesL2 = oXmlNode.selectNodes("../PARAMETER-VALUES" & _
				"/BOOLEAN-VALUE [DEFINITION-REF = '/MICROSAR/TMS570LS3x/Os/OsApplication/OsTrusted']" &_
				"/VALUE")
	
	If oXmlNodesL2.length = 1 Then
		If LCase(oXmlNodesL2.item(0).text) = "false" Then
			
			If sAps(UBound(sAps)) <> "" Then
				ReDim Preserve sAps(UBound(sAps) + 1)
				ReDim Preserve iEcuciSizes(UBound(iEcuciSizes) + 1)
				ReDim Preserve iEcucuSizes(UBound(iEcucuSizes) + 1)
				iEcuciSizes(UBound(iEcuciSizes)) = -1
				iEcucuSizes(UBound(iEcucuSizes)) = -1
			End If
			
			sAps(UBound(sAps)) = oXmlNode.text
			
			Set oXmlNodesL3 = oXmlNode.selectNodes("../PARAMETER-VALUES" & _
				"/INTEGER-VALUE [DEFINITION-REF = '/MICROSAR/TMS570LS3x/Os/OsApplication/OsApplicationProtectionRegionSize']" &_
				"/VALUE")
			
			If oXmlNodesL3.length = 1 Then
				' old OS - one size for both "i" and "u" sections
				iEcuciSizes(UBound(iEcuciSizes)) = CLng(oXmlNodesL3.item(0).text)
				iEcucuSizes(UBound(iEcucuSizes)) = iEcuciSizes(UBound(iEcuciSizes))
			Else
				' new OS - different sizes for each section
				
				Set oXmlNodesL3 = oXmlNode.selectNodes("../PARAMETER-VALUES" & _
					"/INTEGER-VALUE [DEFINITION-REF = '/MICROSAR/TMS570LS3x/Os/OsApplication/OsApplicationProtectionRegionSizeInitData']" &_
					"/VALUE")
				
				If oXmlNodesL3.length = 1 Then
					iEcuciSizes(UBound(iEcuciSizes)) = CLng(oXmlNodesL3.item(0).text)
					bNewOs = True
				End If
				
				Set oXmlNodesL3 = oXmlNode.selectNodes("../PARAMETER-VALUES" & _
					"/INTEGER-VALUE [DEFINITION-REF = '/MICROSAR/TMS570LS3x/Os/OsApplication/OsApplicationProtectionRegionSizeNoInitData']" &_
					"/VALUE")
				
				If oXmlNodesL3.length = 1 Then
					iEcucuSizes(UBound(iEcucuSizes)) = CLng(oXmlNodesL3.item(0).text)
					bNewOs = True
				End If
				
			End If
			
		End If
	End If
	
Next

If bDebug = True Then
	tsTemp.WriteLine("List of aps:")
	tsTemp.WriteLine("Index	Name	iSize	uSize")
	For i = LBound(sAps) To UBound(sAps)
		tsTemp.WriteLine(i & "	" & sAps(i) & "	" & iEcuciSizes(i) & "	" & iEcucuSizes(i))
	Next
	tsTemp.WriteLine()
End If



' ======================================================================================================================
'   PARSE MAP FILE
' ======================================================================================================================

Dim iMapiSizes()
Dim iMapuSizes()
ReDim iMapiSizes(UBound(sAps) - LBound(sAps))
ReDim iMapuSizes(UBound(sAps) - LBound(sAps))
For i = LBound(iMapiSizes) To UBound(iMapiSizes)
	iMapiSizes(i) = -1
	iMapuSizes(i) = -1
Next

Do While tsMapFile.AtEndOfStream = False
	sLine = tsMapFile.ReadLine
	If InStr(1, sLine, "_ossAppl") > 0 Then
		If InStr(1, sLine, "iDataSize") > 0 Then
			
			sSize = Left(sLine, 8)
			iSize = CLng("&h" & sSize)
			sAp = Right(sLine, Len(sLine) - InStrRev(sLine, "DataSize") - 7)
			
			For i = LBound(sAps) To UBound(sAps)
				If sAps(i) = sAp Then
					iMapiSizes(i) = iSize
				End If
			Next
			
		ElseIf InStr(1, sLine, "uDataSize") > 0 Then
			
			sSize = Left(sLine, 8)
			iSize = CLng("&h" & sSize)
			sAp = Right(sLine, Len(sLine) - InStrRev(sLine, "DataSize") - 7)
			
			For i = LBound(sAps) To UBound(sAps)
				If sAps(i) = sAp Then
					iMapuSizes(i) = iSize
				End If
			Next
			
		End If
	End If
Loop

If bDebug = True Then
	tsTemp.WriteLine("List of ap sizes from map file:")
	tsTemp.WriteLine("Index	Name	iSize	uSize")
	For i = LBound(sAps) To UBound(sAps)
		tsTemp.WriteLine(i & "	" & sAps(i) & "	" & iMapiSizes(i) & "	" & iMapuSizes(i))
	Next
	tsTemp.WriteLine()
End If

tsMapFile.Close



' ======================================================================================================================
'   DETERMINE APPROPRIATE SIZES AND VIOLATIONS
' ======================================================================================================================

iError = 0
iWarning = 0
iInfo = 0

For i = LBound(sAps) To UBound(sAps)
	
	If iEcuciSizes(i) < 0 Then
		Report "Warning: couldn't find declared size for " & sAps(i) & " init section in ECUC file"
		iWarning = iWarning + 1
	ElseIf iEcucuSizes(i) < 0 Then
		Report "Warning: couldn't find declared size for " & sAps(i) & " uninit section in ECUC file"
		iWarning = iWarning + 1
	ElseIf iMapiSizes(i) < 0 Then
		Report "Warning: couldn't find actual size for " & sAps(i) & " init section in MAP file"
		iWarning = iWarning + 1
	ElseIf iMapuSizes(i) < 0 Then
		Report "Warning: couldn't find actual size for " & sAps(i) & " uninit section in MAP file"
		iWarning = iWarning + 1
	Else
		
		If iEcuciSizes(i) < iMapiSizes(i) Then
			Report "Error: the init section for " & sAps(i) & " is too small" & vbCrLf &_
					"  Declared size: " & iEcuciSizes(i) & vbCrLf &_
					"  Required size: " & iMapiSizes(i)
			iError = iError + 1
		End If
		
		If iEcucuSizes(i) < iMapuSizes(i) Then
			Report "Error: the uninit section for " & sAps(i) & " is too small" & vbCrLf &_
					"  Declared size: " & iEcucuSizes(i) & vbCrLf &_
					"  Required size: " & iMapuSizes(i)
			iError = iError + 1
		End If
		
		If bNewOs = True Then
			
			If iEcuciSizes(i) > iWarningSizeThresh Then
				If (iEcuciSizes(i) * fWarningSizeFactor) > iMapiSizes(i) Then
					Report "Info: the init section for " & sAps(i) & " is larger than it needs to be" & vbCrLf &_
							"  Declared size: " & iEcuciSizes(i) & vbCrLf &_
							"  Actual size: " & iMapiSizes(i)
					iInfo = iInfo + 1
				End If
			End If
			
			If iEcucuSizes(i) > iWarningSizeThresh Then
				If (iEcucuSizes(i) * fWarningSizeFactor) > iMapuSizes(i) Then
					Report "Info: the uninit section for " & sAps(i) & " is larger than it needs to be" & vbCrLf &_
							"  Declared size: " & iEcucuSizes(i) & vbCrLf &_
							"  Actual size: " & iMapuSizes(i)
					iInfo = iInfo + 1
				End If
			End If
			
		Else
			
			If iEcuciSizes(i) > iWarningSizeThresh Then
				
				If iMapiSizes(i) > iMapuSizes(i) Then
					iSize = iMapiSizes(i)
				Else
					iSize = iMapuSizes(i)
				End If
				
				If (iEcuciSizes(i) * fWarningSizeFactor) > iSize Then
					Report "Info: the memory allocation for " & sAps(i) & " is larger than it needs to be" & vbCrLf &_
							"  Declared size: " & iEcuciSizes(i) & vbCrLf &_
							"  Actual size: " & iSize
					iInfo = iInfo + 1
				End If
				
			End If
			
		End If
		
	End If
	
Next



' ======================================================================================================================
'   END
' ======================================================================================================================

If bDebug = True Then
	tsTemp.Close
End If

sReport = "Ap Memory Analysis - completed with " & iError & " error"
If iError <> 1 Then
	sReport = sReport & "s"
End If

If iWarning > 0 Then
	sReport = sReport & " and " & iWarning & " warning"
	If iWarning <> 1 Then
		sReport = sReport & "s"
	End If
End If

Report sReport

WScript.Quit 0



' ======================================================================================================================
'   RightDelim - shortform for common Right() usage
' ======================================================================================================================

Private Function RightDelim(sString, sDelim)
	
	RightDelim = Right(sString, Len(sString) - InStrRev(sString, sDelim))
	
End Function



' ======================================================================================================================
'   Report - non-client-specific reporting
' ======================================================================================================================

Private Sub Report(sMsg)
	
	If LCase(Right(WScript.FullName, 11)) = "cscript.exe" Then
		WScript.StdOut.WriteLine(sMsg)
	ElseIf LCase(Right(WScript.FullName, 11)) = "wscript.exe" Then
		MsgBox sMsg, 0, "RteXml"
	End If
	
End Sub



' ======================================================================================================================
'   ReportError - non-client-specific error reporting
' ======================================================================================================================

Private Sub ReportError(sError)
	
	If LCase(Right(WScript.FullName, 11)) = "cscript.exe" Then
		WScript.StdOut.WriteLine("Error: " & sError)
	ElseIf LCase(Right(WScript.FullName, 11)) = "wscript.exe" Then
		MsgBox "Error: " & sError, 0, "RteXml"
	End If
	
End Sub
