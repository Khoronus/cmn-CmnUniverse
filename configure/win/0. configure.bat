REM Set the variable values with the default values
set path_opencv_tmp=C:/src/opencv/build

@echo off
ECHO set opencv path (i.e. %path_opencv_tmp%)
set /p path_opencv_tmp="Enter path: "

REM Saved in path_configuration.txt
@echo path_opencv %path_opencv_tmp:\=/%> ../path_configuration.txt
