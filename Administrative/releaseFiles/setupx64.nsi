; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Kactus2"
!define PRODUCT_VERSION "3.11.0 64-bit"
!define PRODUCT_PUBLISHER "TUNI"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Kactus2.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor bzip2

!define MULTIUSER_EXECUTIONLEVEL Highest
!define MULTIUSER_MUI
!define MULTIUSER_INSTALLMODE_COMMANDLINE
!include "MultiUser.nsh"
!include "MUI2.nsh"
!include "x64.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "gpl2.txt"
; Multiuser page
!insertmacro MULTIUSER_PAGE_INSTALLMODE
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Kactus2.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
;!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME}"
OutFile "Kactus2SetupWin64bit.exe"
InstallDir "$PROGRAMFILES64\Kactus2"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite on
  File "..\..\x64\executable\Qt6Core.dll"
  File "..\..\x64\executable\Qt6Gui.dll"
  File "..\..\x64\executable\Qt6Help.dll"
  File "..\..\x64\executable\Qt6Network.dll"
  File "..\..\x64\executable\Qt6PrintSupport.dll"
  File "..\..\x64\executable\Qt6Sql.dll"
  File "..\..\x64\executable\Qt6Widgets.dll"
  File "..\..\x64\executable\Qt6Xml.dll"
  File "..\..\x64\executable\Qt6Svg.dll"
  File "..\..\x64\executable\libEGL.dll"
  File "..\..\x64\executable\libGLESv2.dll"
  File "..\..\x64\executable\icuin51.dll"
  File "..\..\x64\executable\icudt51.dll"
  File "..\..\x64\executable\icuuc51.dll"
  File "..\..\x64\executable\d3dcompiler_47.dll"
  File "..\..\x64\executable\IPXACTmodels.dll"
  File "..\..\PythonAPI\pythonAPI.py"
  File "..\..\PythonAPI\_pythonAPI.pyd"
  File "..\..\x64\executable\KactusAPI.dll"
  File "..\..\x64\executable\Kactus2.exe"
  File "gpl2.txt"
  File "release_notes.txt"
  File "..\..\README.md"
  File "..\..\executable\upgrade.cfg"
  File /oname=DefaultSettings.ini "DefaultSettingsWin.ini"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python310.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_asyncio.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_bz2.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_ctypes.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_decimal.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_elementtree.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_hashlib.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_lzma.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_msi.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_multiprocessing.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_overlapped.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_queue.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_socket.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_sqlite3.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_ssl.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_uuid.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\_zoneinfo.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\libcrypto-1_1.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\libffi-7.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\libssl-1_1.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\LICENSE.txt"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\pyexpat.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python.cat"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python.exe"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python3.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python310._pth"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\python310.zip"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\pythonw.exe"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\select.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\sqlite3.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\unicodedata.pyd"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\vcruntime140.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\vcruntime140_1.dll"
  File "..\..\PythonAPI\python-3.10.6-embed-amd64\winsound.pyd"

#  SetOutPath "$INSTDIR\Python"
#  SetOverwrite on

  SetOutPath "$INSTDIR\platforms"
  SetOverwrite on
  File "..\..\x64\executable\platforms\qminimal.dll"
  File "..\..\x64\executable\platforms\qwindows.dll"
  
  SetOutPath "$INSTDIR\sqldrivers"
  SetOverwrite on
  File "..\..\x64\executable\sqldrivers\qsqlite.dll"

  SetOutPath "$INSTDIR\styles"
  SetOverwrite on
  File "..\..\x64\executable\styles\qwindowsvistastyle.dll"

  SetOutPath "$INSTDIR\Plugins"
  SetOverwrite on
  File "..\..\x64\executable\Plugins\MCAPICodeGenerator.dll"
  File "..\..\x64\executable\Plugins\CppSourceAnalyzer.dll"
  File "..\..\x64\executable\Plugins\VHDLSourceAnalyzer.dll"
  File "..\..\x64\executable\Plugins\AlteraBSPGenerator.dll"
  File "..\..\x64\executable\Plugins\MemoryMapHeaderGenerator.dll"
  File "..\..\x64\executable\Plugins\PadsPartGenerator.dll"
  File "..\..\x64\executable\Plugins\QuartusPinImportPlugin.dll"
  File "..\..\x64\executable\Plugins\QuartusProjectGenerator.dll"
  File "..\..\x64\executable\Plugins\MakefileGenerator.dll"
  File "..\..\x64\executable\Plugins\ModelSimGenerator.dll"
  File "..\..\x64\executable\Plugins\VerilogGeneratorPlugin.dll"
  File "..\..\x64\executable\Plugins\VerilogImport.dll"
  File "..\..\x64\executable\Plugins\VHDLGenerator.dll"
  File "..\..\x64\executable\Plugins\VerilogIncludeImport.dll"
  File "..\..\x64\executable\Plugins\VerilogSourceAnalyzer.dll"
  File "..\..\x64\executable\Plugins\VHDLImport.dll"
  #File "..\..\x64\executable\Plugins\MemoryViewGenerator.dll"
  File "..\..\x64\executable\Plugins\LinuxDeviceTreeGenerator.dll"
  File "..\..\x64\executable\Plugins\SVDGeneratorPlugin.dll"

  SetOutPath "$INSTDIR\Help"
  SetOverwrite on
  File "..\..\Help\Kactus2Help.qhc"
  File "..\..\Help\Kactus2Help.qch"

  SetOutPath "$INSTDIR\ExampleScripts"
  SetOverwrite on
  File "..\..\PythonAPI\ExampleScripts\createComponent.py"
  File "..\..\PythonAPI\ExampleScripts\createComponentItems.py"
  File "..\..\PythonAPI\ExampleScripts\createComponentItems.py"
  File "..\..\PythonAPI\ExampleScripts\listRegisters.py"
  File "..\..\PythonAPI\ExampleScripts\parameterUsage.py"
  File "..\..\PythonAPI\ExampleScripts\verilogGenerator.py"
  
  SetOutPath "$APPDATA\TUT"
  SetOverwrite off
  File /oname=Kactus2.ini "DefaultSettingsWin.ini"
  
  SetOutPath "$INSTDIR\Library\tut.fi\global.communication\mcapi\1.063"
  SetOverwrite on
  File "Library\tut.fi\global.communication\mcapi\1.063\mcapi.1.063.xml"

  SetOutPath "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\1.063"
  SetOverwrite on
  File "Library\tut.fi\ip.swp.api\mcapi.apiDef\1.063\mcapi.apiDef.1.063.xml"

  SetOutPath "$INSTDIR\Library\tut.fi\global.communication\mcapi\2.015"
  SetOverwrite on
  File "Library\tut.fi\global.communication\mcapi\2.015\mcapi.2.015.xml"

  SetOutPath "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\2.015"
  SetOverwrite on
  File "Library\tut.fi\ip.swp.api\mcapi.apiDef\2.015\mcapi.apiDef.2.015.xml"

  SetOutPath "$INSTDIR\Library\tut.fi\global.communication\iptlm\1.1"
  SetOverwrite on
  File "Library\tut.fi\global.communication\iptlm\1.1\TLMW.1.1.xml"

  SetOutPath "$INSTDIR\Library\tut.fi\ip.swp.api\IPTLM.apidef\1.1"
  SetOverwrite on
  File "Library\tut.fi\ip.swp.api\IPTLM.apidef\1.1\TLMW.apiDef.1.1.xml"
  
  SetOutPath "$INSTDIR"
  CreateDirectory "$SMPROGRAMS\Kactus2"
  CreateShortCut "$SMPROGRAMS\Kactus2\Kactus2.lnk" "$INSTDIR\Kactus2.exe"
  CreateShortCut "$SMPROGRAMS\Kactus2\License.lnk" "$INSTDIR\gpl2.txt"
  CreateShortCut "$SMPROGRAMS\Kactus2\Release Notes.lnk" "$INSTDIR\release_notes.txt"
  CreateShortCut "$SMPROGRAMS\Kactus2\Readme.lnk" "$INSTDIR\readme.txt"
  CreateShortCut "$DESKTOP\Kactus2.lnk" "$INSTDIR\Kactus2.exe"
SectionEnd

Section "DependencySection" SEC02
  SetOutPath "$TEMP\Kactus2Installer"
  SetOverwrite ifnewer
  File "vcredist_x64.exe"
  ExecWait '"$OUTDIR\vcredist_x64.exe" /q /norestart'
  SetOutPath "$INSTDIR"
  RMDir /r "$TEMP\Kactus2Installer"
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\Kactus2\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Kactus2.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Kactus2.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function .onInit
  !insertmacro MULTIUSER_INIT
  ${IfNot} ${RunningX64}
     MessageBox MB_OK "This program requires a 64-bit version of Windows. Setup will now exit."
     Abort
  ${EndIf}
  ${DisableX64FSRedirection}
  SetRegView 64
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  !insertmacro MULTIUSER_UNINIT
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\Library\tut.fi\ip.swp.api\IPTLM.apiDef\1.1\TLMW.apiDef.1.1.xml"
  Delete "$INSTDIR\Library\tut.fi\global.communication\iptlm\1.1\TLMW.1.1.xml"
  Delete "$INSTDIR\Library\tut.fi\global.communication\mcapi\2.015\mcapi.2.015.xml"
  Delete "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\2.015\mcapi.apiDef.2.015.xml"
  Delete "$INSTDIR\Library\tut.fi\global.communication\mcapi\1.063\mcapi.1.063.xml"
  Delete "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\1.063\mcapi.apiDef.1.063.xml"
  Delete "$INSTDIR\Help\Kactus2Help.qch"
  Delete "$INSTDIR\Help\Kactus2Help.qhc"
  Delete "$INSTDIR\Plugins\SVDGeneratorPlugin.dll"
  Delete "$INSTDIR\Plugins\VHDLImport.dll"
  Delete "$INSTDIR\Plugins\LinuxDeviceTreeGenerator.dll"
  Delete "$INSTDIR\Plugins\MemoryViewGenerator.dll"
  Delete "$INSTDIR\Plugins\VerilogImport.dll"
  Delete "$INSTDIR\Plugins\VHDLGenerator.dll"
  Delete "$INSTDIR\Plugins\VerilogSourceAnalyzer.dll"
  Delete "$INSTDIR\Plugins\VerilogIncludeImport.dll"
  Delete "$INSTDIR\Plugins\VerilogGeneratorPlugin.dll"
  Delete "$INSTDIR\Plugins\MakefileGenerator.dll"
  Delete "$INSTDIR\Plugins\QuartusProjectGenerator.dll"
  Delete "$INSTDIR\Plugins\QuartusPinImportPlugin.dll"
  Delete "$INSTDIR\Plugins\PadsPartGenerator.dll"
  Delete "$INSTDIR\Plugins\ModelSimGenerator.dll"
  Delete "$INSTDIR\Plugins\MemoryMapHeaderGenerator.dll"
  Delete "$INSTDIR\Plugins\AlteraBSPGenerator.dll"
  Delete "$INSTDIR\Plugins\VHDLSourceAnalyzer.dll"
  Delete "$INSTDIR\Plugins\CppSourceAnalyzer.dll"
  Delete "$INSTDIR\Plugins\MCAPICodeGenerator.dll"
  Delete "$INSTDIR\styles\qwindowsvistastyle.dll"
  Delete "$INSTDIR\sqldrivers\qsqlite.dll"
  Delete "$INSTDIR\platforms\qminimal.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\DefaultSettings.ini"
  Delete "$INSTDIR\upgrade.cfg"
  Delete "$INSTDIR\README.md"
  Delete "$INSTDIR\release_notes.txt"
  Delete "$INSTDIR\gpl2.txt"
  Delete "$INSTDIR\Kactus2.exe"
  Delete "$INSTDIR\KactusAPI.dll"
  Delete "$INSTDIR\_pythonAPI.pyd"
  Delete "$INSTDIR\pythonAPI.py"
  Delete "$INSTDIR\IPXACTmodels.dll"
  Delete "$INSTDIR\d3dcompiler_47.dll"
  Delete "$INSTDIR\icuuc51.dll"
  Delete "$INSTDIR\icudt51.dll"
  Delete "$INSTDIR\icuin51.dll"
  Delete "$INSTDIR\libGLESv2.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\Qt6Svg.dll"
  Delete "$INSTDIR\Qt6Xml.dll"
  Delete "$INSTDIR\Qt6Widgets.dll"
  Delete "$INSTDIR\Qt6Sql.dll"
  Delete "$INSTDIR\Qt6PrintSupport.dll"
  Delete "$INSTDIR\Qt6Network.dll"
  Delete "$INSTDIR\Qt6Help.dll"
  Delete "$INSTDIR\Qt6Gui.dll"
  Delete "$INSTDIR\Qt6Core.dll"
  Delete "$INSTDIR\python310.dll"
  Delete "$INSTDIR\_asyncio.pyd"
  Delete "$INSTDIR\_bz2.pyd"
  Delete "$INSTDIR\_ctypes.pyd"
  Delete "$INSTDIR\_decimal.pyd"
  Delete "$INSTDIR\_elementtree.pyd"
  Delete "$INSTDIR\_hashlib.pyd"
  Delete "$INSTDIR\_lzma.pyd"
  Delete "$INSTDIR\_msi.pyd"
  Delete "$INSTDIR\_multiprocessing.pyd"
  Delete "$INSTDIR\_overlapped.pyd"
  Delete "$INSTDIR\_queue.pyd"
  Delete "$INSTDIR\_socket.pyd"
  Delete "$INSTDIR\_sqlite3.pyd"
  Delete "$INSTDIR\_ssl.pyd"
  Delete "$INSTDIR\_uuid.pyd"
  Delete "$INSTDIR\_zoneinfo.pyd"
  Delete "$INSTDIR\libcrypto-1_1.dll"
  Delete "$INSTDIR\libffi-7.dll"
  Delete "$INSTDIR\libssl-1_1.dll"
  Delete "$INSTDIR\LICENSE.txt"
  Delete "$INSTDIR\pyexpat.pyd"
  Delete "$INSTDIR\python.cat"
  Delete "$INSTDIR\python.exe"
  Delete "$INSTDIR\python3.dll"
  Delete "$INSTDIR\python310._pth"
  Delete "$INSTDIR\python310.zip"
  Delete "$INSTDIR\pythonw.exe"
  Delete "$INSTDIR\select.pyd"
  Delete "$INSTDIR\sqlite3.dll"
  Delete "$INSTDIR\unicodedata.pyd"
  Delete "$INSTDIR\vcruntime140.dll"
  Delete "$INSTDIR\vcruntime140_1.dll"
  Delete "$INSTDIR\winsound.pyd"

  Delete "$SMPROGRAMS\Kactus2\Uninstall.lnk"
  Delete "$DESKTOP\Kactus2.lnk"
  Delete "$SMPROGRAMS\Kactus2\Readme.lnk"
  Delete "$SMPROGRAMS\Kactus2\Release Notes.lnk"
  Delete "$SMPROGRAMS\Kactus2\License.lnk"
  Delete "$SMPROGRAMS\Kactus2\Kactus2.lnk"

  Delete "$INSTDIR\ExampleScripts\createComponent.py"
  Delete "$INSTDIR\ExampleScripts\createComponentItems.py"
  Delete "$INSTDIR\ExampleScripts\createComponentItems.py"
  Delete "$INSTDIR\ExampleScripts\listRegisters.py"
  Delete "$INSTDIR\ExampleScripts\parameterUsage.py"
  Delete "$INSTDIR\ExampleScripts\verilogGenerator.py"
  
  RMDir "$SMPROGRAMS\Kactus2"
  RMDir "$INSTDIR\Help"
  RMDir "$INSTDIR\Plugins"
  RMDir "$INSTDIR\styles"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\ExampleScripts"
  RMDir "$INSTDIR\__pycache__"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api\IPTLM.apiDef\1.1"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api\IPTLM.apiDef"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\2.015"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef\1.063"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api\mcapi.apiDef"
  RMDir "$INSTDIR\Library\tut.fi\ip.swp.api"
  RMDir "$INSTDIR\Library\tut.fi\global.communication\iptlm\1.1"
  RMDir "$INSTDIR\Library\tut.fi\global.communication\iptlm"
  RMDir "$INSTDIR\Library\tut.fi\global.communication\mcapi\2.015"
  RMDir "$INSTDIR\Library\tut.fi\global.communication\mcapi\1.063"
  RMDir "$INSTDIR\Library\tut.fi\global.communication\mcapi"
  RMDir "$INSTDIR\Library\tut.fi\global.communication"
  RMDir "$INSTDIR\Library\tut.fi"
  RMDir "$INSTDIR\Library"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd