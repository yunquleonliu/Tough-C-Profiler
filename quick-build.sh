#!/bin/bash
# Tough C Quick Start Script
# Tough C 快速启动脚本
# Linux/macOS Bash version / Linux/macOS Bash 版本

set -e

echo "╔════════════════════════════════════════════════════════════╗"
echo "║  Tough C Profiler - Quick Build / 快速构建                 ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

# Check prerequisites / 检查先决条件
echo "Checking prerequisites... / 检查先决条件..."

# Check CMake
if ! command -v cmake &> /dev/null; then
    echo "✗ CMake not found. Please install CMake 3.20+."
    echo "✗ 未找到 CMake。请安装 CMake 3.20+。"
    exit 1
fi
echo "✓ CMake found: $(cmake --version | head -n1)"

# Check for LLVM/Clang
if ! command -v clang &> /dev/null; then
    echo "⚠ Clang not in PATH. Make sure LLVM/Clang is installed."
    echo "⚠ Clang 不在 PATH 中。请确保已安装 LLVM/Clang。"
else
    echo "✓ Clang found: $(clang --version | head -n1)"
fi

echo ""

# Create build directory / 创建构建目录
echo "Creating build directory... / 创建构建目录..."
if [ -d "build" ]; then
    echo "Build directory exists, cleaning... / 构建目录已存在，清理中..."
    rm -rf build
fi
mkdir build
echo "✓ Build directory created / 构建目录已创建"
echo ""

# Configure / 配置
echo "Configuring with CMake... / 使用 CMake 配置..."
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DTCC_BUILD_TESTS=ON -DTCC_BUILD_EXAMPLES=ON

echo "✓ Configuration complete / 配置完成"
echo ""

# Build / 构建
echo "Building... / 构建中..."
cmake --build . --config Release

echo "✓ Build complete / 构建完成"
echo ""

# Test / 测试
echo "Running tests... / 运行测试..."
if ctest -C Release --output-on-failure; then
    echo "✓ All tests passed / 所有测试通过"
else
    echo "⚠ Some tests failed / 部分测试失败"
fi
echo ""

cd ..

# Summary / 总结
echo "╔════════════════════════════════════════════════════════════╗"
echo "║  Build Complete! / 构建完成！                               ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""
echo "Executable location / 可执行文件位置:"
echo "  build/src/tcc-check"
echo ""
echo "To install / 安装:"
echo "  sudo cmake --install build --prefix /usr/local"
echo ""
echo "To test examples / 测试示例:"
echo "  ./build/src/tcc-check examples/01_smart_pointers.tcc"
echo ""
echo "For more information / 更多信息:"
echo "  See BUILD.md and PROJECT_STRUCTURE.md"
echo ""
