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
; so the callers pass absolute paths with -DAPPEXE= and -DOUTFILE=. The defaults
; below are only for a local run from the repository root.
!ifndef APPEXE
!define APPEXE "build/CursoMusica_artefacts/Release/Curso Musica Studio.exe"
!endif
!ifndef OUTFILE
!define OUTFILE "instalador/Instalador CursoMusica.exe"
!endif
!ifndef RUNTIMEDIR
!define RUNTIMEDIR "build/runtime"
!endif
!ifndef APPICON
!define APPICON "Assets/AppIcon.ico"
!endif

; Installer/uninstaller icon and the icon the shortcuts point at. NSIS resolves
; these relative to the script directory, so build-installer.sh and release.yml
; pass an absolute -DAPPICON=.
Icon "${APPICON}"
UninstallIcon "${APPICON}"
!define MUI_ICON "${APPICON}"
!define MUI_UNICON "${APPICON}"

!define APP_NAME "CursoMusica"
; The executable keeps the JUCE PRODUCT_NAME ("Curso Musica Studio").
!define APP_EXE "Curso Musica Studio.exe"
; The .ico is staged next to the .exe and used for the shortcuts, so the
; desktop/Start menu entries show the logo before the shell has indexed the exe.
!define APP_ICON "AppIcon.ico"
!define APP_VERSION "0.1.0"
!define COMPANY "CursoMusica"

Name "${APP_NAME}"
; The deliverable name the team asked for: "Instalador CursoMusica.exe".
OutFile "${OUTFILE}"
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
    File "${APPEXE}"
    File "${APPICON}"

    ; Bundled runtime (SoundFont/samples/DLLs) when the build produced it; the
    ; installer still succeeds when it did not (the build passes -DRUNTIME).
!ifdef RUNTIME
    File /r "${RUNTIMEDIR}/*.*"
!endif

    ; Remember the chosen directory for upgrades and uninstall.
    WriteRegStr HKLM "Software\${APP_NAME}" "InstallDir" "$INSTDIR"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayName" "${APP_NAME}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "UninstallString" "$INSTDIR\uninstall.exe"

    WriteUninstaller "$INSTDIR\uninstall.exe"

    CreateDirectory "$SMPROGRAMS\${APP_NAME}"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_ICON}"
    CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_ICON}"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\${APP_EXE}"
    Delete "$INSTDIR\${APP_ICON}"
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r "$INSTDIR"
    Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
    RMDir "$SMPROGRAMS\${APP_NAME}"
    Delete "$DESKTOP\${APP_NAME}.lnk"
    DeleteRegKey HKLM "Software\${APP_NAME}"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
SectionEnd
