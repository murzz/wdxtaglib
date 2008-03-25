rem build
codeblocks.exe /na /nd /ns --rebuild ..\src\WDXTagLib.cbp --target='Release' > build_log.txt

rem should take release name from project properties somehow
set package=wdx_WDXTagLib_100

rem prepare folders
del %package% /q
rd %package%
md %package%

rem copy all files in one place
copy ..\src\WDXTagLib.wdx %package%\WDXTagLib.wdx
copy ..\doc\COPYING %package%\COPYING
copy ..\doc\COPYING.LESSER %package%\COPYING.LESSER
copy ..\doc\read_before_install.txt %package%\read_before_install.txt
copy ..\doc\readme.txt %package%\readme.txt
copy ..\lib\libtag.dll %package%\libtag.dll
copy ..\lib\msvcrt.dll %package%\msvcrt.dll

rem zip package
cd %package%
7z a -tzip ..\%package%.zip *
cd..

rem zip sources
cd..
7z a -tzip release\%package%_src.zip doc lib src release\build_release.cmd
cd release

rem clear out
del %package% /q
rd %package%
