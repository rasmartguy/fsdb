set DOWNLOAD_DIR=C:\downloads
mkdir %DOWNLOAD_DIR%

rem set DEP_DOWNLOAD_URL=http://example.com/file.7z
rem mkdir %DOWNLOAD_DIR%\dep
rem appveyor DownloadFile %DEP_DOWNLOAD_URL% -FileName %DOWNLOAD_DIR%\dep\file.7z
rem 7z e -y %DOWNLOAD_DIR%\dep\file.7z -o%DOWNLOAD_DIR%\dep
rem set PATH=$DOWNLOAD_DIR%\dep;%PATH%

del "c:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
del "c:\Program Files (x86)\MSBuild\4.0\Microsoft.Common.targets\ImportAfter'Xamarin.Common.targets"

