rem Script will export subversion tag, build it and pack binary and src packages.

rem ---------------- configuration start --------------------------------
rem should take release name from project properties somehow
set package=wdx_WDXTagLib_100
set sevenzip="%ProgramFiles%\7-Zip\7z.exe"
set eclipse="%ProgramFiles%\eclipse\eclipsec.exe"
set workspace=d:\eclipse
set project=WDXTagLib
rem ---------------- configuration end ----------------------------------

rem Export
rem ******************

rem Build
rem %eclipse% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data %workspace% -cleanBuild %project%

rem Pack sources
%sevenzip% a -t7z %package%_src.7z @src_files_to_release.txt

rem Pack binary
%sevenzip% a -t7z %package%.7z @binary_files_to_release.txt

echo Done