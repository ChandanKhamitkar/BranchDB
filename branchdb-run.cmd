@echo off
echo Building BranchDB, please wait...

if not exist build mkdir build
cd build || exit /b 1

cmake .. || exit /b 1
cmake --build . || exit /b 1

echo Executing BranchDB...
cd Debug || exit /b 1
BranchDB.exe
