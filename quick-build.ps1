# Tough C Quick Start Script
# Tough C 快速启动脚本
# Windows PowerShell version / Windows PowerShell 版本

Write-Host "╔════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  Tough C Profiler - Quick Build / 快速构建                 ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Check prerequisites / 检查先决条件
Write-Host "Checking prerequisites... / 检查先决条件..." -ForegroundColor Yellow

# Check CMake
$cmake = Get-Command cmake -ErrorAction SilentlyContinue
if (-not $cmake) {
    Write-Host "✗ CMake not found. Please install CMake 3.20+." -ForegroundColor Red
    Write-Host "✗ 未找到 CMake。请安装 CMake 3.20+。" -ForegroundColor Red
    exit 1
}
Write-Host "✓ CMake found: $($cmake.Version)" -ForegroundColor Green

# Check for LLVM/Clang
$clang = Get-Command clang -ErrorAction SilentlyContinue
if (-not $clang) {
    Write-Host "⚠ Clang not in PATH. Make sure LLVM/Clang is installed." -ForegroundColor Yellow
    Write-Host "⚠ Clang 不在 PATH 中。请确保已安装 LLVM/Clang。" -ForegroundColor Yellow
}
else {
    Write-Host "✓ Clang found: $($clang.Source)" -ForegroundColor Green
}

Write-Host ""

# Create build directory / 创建构建目录
Write-Host "Creating build directory... / 创建构建目录..." -ForegroundColor Yellow
if (Test-Path "build") {
    Write-Host "Build directory exists, cleaning... / 构建目录已存在，清理中..." -ForegroundColor Yellow
    Remove-Item -Recurse -Force "build"
}
New-Item -ItemType Directory -Path "build" | Out-Null
Write-Host "✓ Build directory created / 构建目录已创建" -ForegroundColor Green
Write-Host ""

# Configure / 配置
Write-Host "Configuring with CMake... / 使用 CMake 配置..." -ForegroundColor Yellow
Set-Location "build"
cmake .. -DCMAKE_BUILD_TYPE=Release -DTCC_BUILD_TESTS=ON -DTCC_BUILD_EXAMPLES=ON

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ CMake configuration failed / CMake 配置失败" -ForegroundColor Red
    Set-Location ..
    exit 1
}
Write-Host "✓ Configuration complete / 配置完成" -ForegroundColor Green
Write-Host ""

# Build / 构建
Write-Host "Building... / 构建中..." -ForegroundColor Yellow
cmake --build . --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ Build failed / 构建失败" -ForegroundColor Red
    Set-Location ..
    exit 1
}
Write-Host "✓ Build complete / 构建完成" -ForegroundColor Green
Write-Host ""

# Test / 测试
Write-Host "Running tests... / 运行测试..." -ForegroundColor Yellow
ctest -C Release --output-on-failure

if ($LASTEXITCODE -ne 0) {
    Write-Host "⚠ Some tests failed / 部分测试失败" -ForegroundColor Yellow
}
else {
    Write-Host "✓ All tests passed / 所有测试通过" -ForegroundColor Green
}
Write-Host ""

Set-Location ..

# Summary / 总结
Write-Host "╔════════════════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║  Build Complete! / 构建完成！                               ║" -ForegroundColor Green
Write-Host "╚════════════════════════════════════════════════════════════╝" -ForegroundColor Green
Write-Host ""
Write-Host "Executable location / 可执行文件位置:" -ForegroundColor Cyan
Write-Host "  build\src\Release\tcc-check.exe" -ForegroundColor White
Write-Host ""
Write-Host "To install / 安装:" -ForegroundColor Cyan
Write-Host "  cmake --install build --prefix <install_path>" -ForegroundColor White
Write-Host ""
Write-Host "To test examples / 测试示例:" -ForegroundColor Cyan
Write-Host "  .\build\src\Release\tcc-check.exe examples\01_smart_pointers.tcc" -ForegroundColor White
Write-Host ""
Write-Host "For more information / 更多信息:" -ForegroundColor Cyan
Write-Host "  See BUILD.md and PROJECT_STRUCTURE.md" -ForegroundColor White
Write-Host ""
