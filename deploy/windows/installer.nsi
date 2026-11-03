; CursoMusica Windows installer (NSIS)
; Owned by devops. Requirements: REQ-014 (choose install directory, ready to
; use) and REQ-013 (test builds unlock all modules).
;
; Paths are resolved relative to this script, so the build first stages the
; artefacts under dist/app/ (see build-installer.sh and the release workflow).
; makensis does not resolve "..", which is why nothing here climbs out of the
; deploy/windows directory.

Unicode true
!include "MUI2.nsh"

; NSIS resolves File/OutFile relative to different directories depending on the
; platform (the script's directory on Linux, the current directory on Windows),
; so the callers pass absolute paths with /DAPPDIR= and /DOUTDIR=. The defaults
; below are only for a quick local run from deploy/windows.
!ifndef APPDIR
!define APPDIR "dist/app"
!endif
!ifndef OUTDIR
!define OUTDIR "dist"
!endif

!define APP_NAME "CursoMusica"
; The executable keeps the JUCE PRODUCT_NAME ("Curso Musica Studio").
!define APP_EXE "Curso Musica Studio.exe"
!define APP_VERSION "0.1.0"
!define COMPANY "CursoMusica"

Name "${APP_NAME}"
; Built here, then copied to <repo>/instalador/Instalador CursoMusica.exe.
OutFile "${OUTDIR}/Instalador CursoMusica.exe"
; Default install directory; the MUI Directory page lets the user change it
; (REQ-014). InstallDir points at %ProgramFiles% by default.
InstallDir "$PROGRAMFILES64\${APP_NAME}"
InstallDirRegKey HKLM "Software\${APP_NAME}" "InstallDir"
RequestExecutionLevel admin

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY        ; <-- the user picks the install location
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "English"

Section "CursoMusica" SecMain
    SectionIn RO
    SetOutPath "$INSTDIR"

    ; Application and runtime dependencies (JUCE app + bundled libraries from
    ; ADR 0002: FluidSynth, libsndfile, SoundFont/samples). Everything needed so
    ; the app is ready to use after install (REQ-014).
    File "${APPDIR}/${APP_EXE}"

    ; Bundled runtime (SoundFont/samples/DLLs) when the build produced it; the
    ; installer still succeeds when it did not (the build passes /DRUNTIME).
!ifdef RUNTIME
    File /r "${APPDIR}/runtime/*.*"
!endif

    ; Remember the chosen directory for upgrades and uninstall.
    WriteRegStr HKLM "Software\${APP_NAME}" "InstallDir" "$INSTDIR"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayName" "${APP_NAME}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "UninstallString" "$INSTDIR\uninstall.exe"

    WriteUninstaller "$INSTDIR\uninstall.exe"

    CreateDirectory "$SMPROGRAMS\${APP_NAME}"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}"
    CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\${APP_EXE}"
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r "$INSTDIR"
    Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
    RMDir "$SMPROGRAMS\${APP_NAME}"
    Delete "$DESKTOP\${APP_NAME}.lnk"
    DeleteRegKey HKLM "Software\${APP_NAME}"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
SectionEnd
