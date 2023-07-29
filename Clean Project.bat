@echo off
setlocal
:PROMPT
set /p var=Are you sure you want to clean the project? [Y/n]: || SET "var=Y"

if /I not %var%== Y exit

rmdir /q/s ".vs"
rmdir /q/s "Build"
rmdir /q/s "Binaries"
rmdir /q/s "DerivedDataCache"
rmdir /q/s "Intermediate"
rmdir /q/s "Platforms"
rmdir /q/s "Saved"

set /p var=Do you also want to delete the .sln file? [Y/n]: || SET "sln=Y"
if /I not %sln%== Y exit
del /q/s *".sln"


set /p exit=Finished. Press enter to exit. || SET "exit=Y"
if /I %exit%== Y exit
endlocal