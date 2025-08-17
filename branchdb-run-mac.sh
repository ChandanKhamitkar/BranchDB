#!/bin/bash
# chmod +x branchdb-run-mac.sh

echo "Building BranchDB for macOS, please wait..."
mkdir -p build
cd build || exit 1

cmake .. || exit 1
cmake --build . || exit 1

echo "Executing BranchDB..."
cd Debug || exit 1
exec ./BranchDB
