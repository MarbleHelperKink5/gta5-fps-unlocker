# Build helper for GtaV-Optimizer (Windows / PowerShell)
param(
    [string]$Config = "Release"
)

$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot

Write-Host "[*] Configuring CMake ($Config)..."
cmake -B "$root/build" -S $root -DCMAKE_BUILD_TYPE=$Config

Write-Host "[*] Building..."
cmake --build "$root/build" --config $Config

Write-Host "[*] Running tests..."
ctest --test-dir "$root/build" --output-on-failure

Write-Host "[+] Done. Binary at build/$Config/gta5-optimizer.exe"