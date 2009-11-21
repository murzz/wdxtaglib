@echo off
rem Script will build WDXTagLib tag and pack binary and src packages.

rem ---------------- configuration start --------------------------------
rem TODO should take release name from project properties somehow
set package=wdx_WDXTagLib_100
set sevenzip="%ProgramFiles%\7-Zip\7z.exe"
set eclipse="%ProgramFiles%\eclipse\eclipsec.exe"
rem temporary eclipse workspace
set workspace=%tmp%\wdxtaglib_workspace
set project_name=WDXTagLib
rem TODO project root should be detected automatically
set project_root=d:\eclipse\wdxtaglib
rem set project_root=.\..
rem ---------------- configuration end ----------------------------------

rem delete workspace if exists
rd /q /s %workspace%

rem build
%eclipse% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import %project_root% -data %workspace% -cleanBuild %project_name%

rem check for build errors
if not errorlevel==0 goto error_build

rem cleanup
rd /q /s %workspace%

rem pack sources
%sevenzip% a -t7z %package%_src.7z @src_files_to_release.txt -xr@files_to_exclude.txt

rem check for pack errors
if not errorlevel==0 goto error_pack_src

rem pack binary
%sevenzip% a -t7z %package%.7z @binary_files_to_release.txt -xr@files_to_exclude.txt

rem check for pack errors
if not errorlevel==0 goto error_pack_binary

rem that's all
echo All done
goto exit

:error_build
echo Failed to build
goto exit

:error_pack_src
echo Failed to pack sources
goto exit

:error_pack_binary
echo Failed to pack binaries
goto exit

:exit