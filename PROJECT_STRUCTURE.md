# Tough C Profiler - Project Structure
# Tough C 分析器 - 项目结构

## Directory Layout / 目录布局

```
Tough C Profiler/
├── .github/
│   └── workflows/
│       └── ci.yml                  # CI/CD configuration / CI/CD 配置
│
├── include/
│   └── tcc/
│       ├── Core.h                  # Core types and constants / 核心类型和常量
│       ├── Diagnostic.h            # Diagnostic system / 诊断系统
│       ├── Rule.h                  # Rule base classes / 规则基类
│       ├── FileDetector.h          # File detection / 文件检测
│       └── RuleEngine.h            # Rule orchestration / 规则编排
│
├── src/
│   ├── CMakeLists.txt              # Source build config / 源码构建配置
│   ├── main.cpp                    # CLI entry point / CLI 入口
│   ├── Diagnostic.cpp              # Diagnostic implementation / 诊断实现
│   ├── Rule.cpp                    # Rule implementation / 规则实现
│   ├── FileDetector.cpp            # File detection impl / 文件检测实现
│   └── RuleEngine.cpp              # Rule engine impl / 规则引擎实现
│
├── tests/
│   ├── CMakeLists.txt              # Test configuration / 测试配置
│   └── data/
│       ├── pass/                   # Tests that should pass / 应该通过的测试
│       └── fail/                   # Tests that should fail / 应该失败的测试
│
├── examples/
│   ├── 01_smart_pointers.tcc       # ✓ Ownership example / 所有权示例
│   ├── 02_raw_pointer_violations.tcc  # ✗ Ownership violations / 所有权违规
│   ├── 03_lifetime_safety.tcc      # ✓ Lifetime example / 生命周期示例
│   ├── 04_lifetime_violations.tcc  # ✗ Lifetime violations / 生命周期违规
│   ├── 05_thread_safety.tcc        # ✓ Concurrency example / 并发示例
│   └── 06_thread_violations.tcc    # ✗ Concurrency violations / 并发违规
│
├── Docs/
│   └── vision.md                   # Project vision / 项目愿景
│
├── CMakeLists.txt                  # Root CMake config / 根 CMake 配置
├── .gitignore                      # Git ignore rules / Git 忽略规则
├── README.md                       # Project overview / 项目概览
├── BUILD.md                        # Build instructions / 构建说明
├── Core Rule Sets.md               # Rule definitions / 规则定义
├── MVP Planning Document.md        # MVP plan / MVP 计划
├── Tough C Menifesto.md           # Philosophy / 理念
└── Working Track.md                # Progress tracking / 进度跟踪
```

## Module Overview / 模块概览

### Core System / 核心系统

| Module | Purpose / 目的 | Status / 状态 |
|--------|---------------|---------------|
| **Core.h** | Common types, constants, exit codes / 通用类型、常量、退出码 | ✓ Complete / 完成 |
| **Diagnostic** | Error collection and reporting / 错误收集和报告 | ✓ Complete / 完成 |
| **FileDetector** | Detect `.tcc` files and `@tcc` annotations / 检测 `.tcc` 文件和 `@tcc` 注解 | ✓ Complete / 完成 |
| **Rule** | Base classes for all safety rules / 所有安全规则的基类 | ✓ Complete / 完成 |
| **RuleEngine** | Orchestrate rule execution / 编排规则执行 | ✓ Complete / 完成 |

### Rule Implementation (Future Phases) / 规则实现（未来阶段）

| Rule Category | Implementation / 实现 | Phase / 阶段 |
|--------------|----------------------|-------------|
| **Ownership** | Detect `new`/`delete`, raw pointers / 检测 `new`/`delete`、原始指针 | Phase 3 |
| **Lifetime** | Detect dangling refs, local returns / 检测悬空引用、局部返回 | Phase 4 |
| **Concurrency** | Detect data races, unsafe captures / 检测数据竞争、不安全捕获 | Phase 5 |

### Build System / 构建系统

- **CMake**: Multi-platform build configuration / 多平台构建配置
- **LLVM/Clang**: AST parsing and analysis / AST 解析和分析
- **CTest**: Test framework integration / 测试框架集成

### CI/CD Pipeline / CI/CD 流水线

- **GitHub Actions**: Automated testing / 自动化测试
- **Multi-platform**: Linux, Windows, macOS / 多平台支持
- **Multi-version**: LLVM 15, 16, 17 / 多版本支持

## File Naming Conventions / 文件命名约定

### C++ Files / C++ 文件
- Headers: `CamelCase.h` in `include/tcc/`
- Sources: `CamelCase.cpp` in `src/`
- 头文件：`include/tcc/` 中的 `CamelCase.h`
- 源文件：`src/` 中的 `CamelCase.cpp`

### TCC Files / TCC 文件
- Test files: `descriptive_name.tcc`
- Example files: `##_description.tcc`
- 测试文件：`descriptive_name.tcc`
- 示例文件：`##_description.tcc`

### Documentation / 文档
- Markdown files: `Title Case.md`
- Build guide: `BUILD.md`
- Markdown 文件：`Title Case.md`
- 构建指南：`BUILD.md`

## Dependencies / 依赖

### Required / 必需
- CMake 3.20+
- C++17 compiler (GCC 9+, Clang 10+, MSVC 2019+)
- LLVM/Clang 15/16/17

### Optional / 可选
- CTest (for testing / 用于测试)
- Ninja (faster builds / 更快的构建)

## Build Artifacts / 构建产物

```
build/
├── src/
│   └── tcc-check(.exe)           # Main executable / 主可执行文件
├── compile_commands.json          # Compilation database / 编译数据库
└── Testing/                       # Test results / 测试结果
```

## Development Workflow / 开发工作流

1. **Edit source** / 编辑源码
2. **Build**: `cmake --build build`
3. **Test**: `ctest -C Release` in `build/`
4. **Install**: `cmake --install build`

## Phase Completion Status / 阶段完成状态

| Phase | Status / 状态 | Deliverables / 交付物 |
|-------|--------------|---------------------|
| Phase 1 | ✓ **Complete / 完成** | Project structure, build system, core headers / 项目结构、构建系统、核心头文件 |
| Phase 2 | Planned / 计划中 | Rule engine implementation / 规则引擎实现 |
| Phase 3 | Planned / 计划中 | Ownership rules / 所有权规则 |
| Phase 4 | Planned / 计划中 | Lifetime rules / 生命周期规则 |
| Phase 5 | Planned / 计划中 | Concurrency rules / 并发规则 |
| Phase 6 | Planned / 计划中 | CLI polish, integration / CLI 完善、集成 |
| Phase 7 | Planned / 计划中 | Comprehensive test suite / 全面测试套件 |
| Phase 8 | Planned / 计划中 | Documentation & examples / 文档和示例 |

---

**Project Philosophy / 项目理念**

This structure embodies the Tough C principle: **Safety is opt-in, power is never removed.**
此结构体现了 Tough C 原则：**安全是可选的，能力永不移除。**

Every component is designed to:
每个组件的设计目标：

- ✓ Be **reversible** / 可逆的
- ✓ Provide **clear diagnostics** / 提供清晰的诊断
- ✓ Suggest **escape paths** / 建议逃生路径
- ✓ Preserve **C++ federation promise** / 保持 C++ 联邦承诺
