#!/bin/bash
# chmod +x branchdb-run.sh

echo "Building BranchDB, please wait..."
cd build || exit 1

cmake .. || exit 1
cmake --build . || exit 1

echo "Executing BranchDB..."
cd Debug || exit 1
exec ./BranchDB.exe  # Only final command should use exec
