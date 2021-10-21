@echo off
set cmake_exe="%CMAKE_HOME%\bin\cmake"
set dest_dir="%cd%\win_vsproj"
::%cmake_exe% -G "Visual Studio 10 2010" -A Win32 -S . -B %dest_dir%
%cmake_exe% -G "Visual Studio 15 2017" -A Win32 -S . -B %dest_dir%

pause