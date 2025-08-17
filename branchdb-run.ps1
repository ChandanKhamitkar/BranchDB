Write-Output "Building BranchDB, please wait..."

New-Item -ItemType Directory -Force -Path build | Out-Null
Set-Location build

cmake .. 
if ($LASTEXITCODE -ne 0) { exit 1 }

cmake --build .
if ($LASTEXITCODE -ne 0) { exit 1 }

Write-Output "Executing BranchDB..."
Set-Location Debug
Start-Process -NoNewWindow -Wait ./BranchDB.exe
