echo Generate version info resource...

@echo off

rem Configuration starts here
rem ---------------------------------------------------

rem That tool should be in the PATH already. Usually it is placed in %ProgramFiles%\TortoiseSVN\bin
set subwcrev=SubWCRev.exe
set project_root=%1
set output_root=%2
set rc_remplate=%project_root%\src\VerInfo.rc.template
set rc_script=%output_root%\VerInfo.rc

rem that tool should be in the path already, usually it is placed in %MinGW%\bin
set windres=windres.exe
set libverinfo=%output_root%\libverinfo.a

rem Configuration ends here
rem ---------------------------------------------------

rem Create rc script from template
set create=%subwcrev% %project_root% %rc_remplate% %rc_script%

rem Build resource file from script
set build=%windres% %rc_script% %libverinfo%

rem Clear old stuff
del /q  %rc_script% 2>nul
del /q %libverinfo% 2>nul

rem Create new stuff
%create% && %build%

echo Done