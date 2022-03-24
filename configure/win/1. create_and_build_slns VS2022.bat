REM IMPORTANT: The build order is important to prevent errors

REM location is set with the current called batch location. If different, please change
SET "location=%cd%"
SET "build_folder=build"
SET "compiler_version=Visual Studio 17 2022"
SET "compiler_option=x64"

SET "build=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\msbuild.exe"
SET "params_debug=/t:build /m:8 /p:RunCodeAnalysis=false;BuildInParallel=True /v:n /property:Configuration=Debug /property:Platform=x64"
SET "params_relase=/t:build /m:8 /p:RunCodeAnalysis=false;BuildInParallel=True /v:n /property:Configuration=Release /property:Platform=x64"


REM Create a log build file
@echo "Projects build result [==0 success, >0 error]" > "build_result.txt"

REM Create CmnLib
cd "%location%\..\..\CmnLib"
call create_sln.bat
call :build_function "%build%" "%location%\..\..\CmnLib\build\CmnLib.sln" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnLib\build\INSTALL.vcxproj" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnLib\build\CmnLib.sln" "%params_relase%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnLib\build\INSTALL.vcxproj" "%params_relase%" "build_result.txt"

REM Create CmnMath
cd "%location%\..\..\CmnMath"
call create_sln.bat
call :build_function "%build%" "%location%\..\..\CmnMath\build\CmnMath.sln" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnMath\build\INSTALL.vcxproj" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnMath\build\CmnMath.sln" "%params_relase%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnMath\build\INSTALL.vcxproj" "%params_relase%" "build_result.txt"

REM Create CmnCS
cd "%location%\..\..\CmnCS"
call create_sln.bat
call :build_function "%build%" "%location%\..\..\CmnCS\build\CmnCS.sln" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnCS\build\INSTALL.vcxproj" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnCS\build\CmnCS.sln" "%params_relase%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnCS\build\INSTALL.vcxproj" "%params_relase%" "build_result.txt"

REM Create CmnIO
cd "%location%\..\..\CmnIO"
call create_sln.bat
call :build_function "%build%" "%location%\..\..\CmnIO\build\CmnIO.sln" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIO\build\INSTALL.vcxproj" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIO\build\CmnIO.sln" "%params_relase%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIO\build\INSTALL.vcxproj" "%params_relase%" "build_result.txt"

REM Create CmnIP
cd "%location%\..\..\CmnIP"
call create_sln.bat
call :build_function "%build%" "%location%\..\..\CmnIP\build\CmnIP.sln" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIP\build\INSTALL.vcxproj" "%params_debug%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIP\build\CmnIP.sln" "%params_relase%" "build_result.txt"
call :build_function "%build%" "%location%\..\..\CmnIP\build\INSTALL.vcxproj" "%params_relase%" "build_result.txt"


REM Skip the function
goto:eof

REM function to build a process
:build_function
"%~1" %~2 %~3
cd "%location%
echo "%~2" Exit Code is %errorlevel% >> %~4
goto:eof


