// Tough C Profiler - File Detection
// Tough C 分析器 - 文件检测
//
// Detects if a file should be analyzed by TCC
// 检测文件是否应该被 TCC 分析

#pragma once

#include <string>
#include <optional>

namespace tcc {

// TCC configuration from file / 从文件读取的 TCC 配置
struct TCCConfig {
    bool enabled = false;           // Is TCC enabled / TCC 是否启用
    bool ownershipChecks = true;    // Check ownership rules / 检查所有权规则
    bool lifetimeChecks = true;     // Check lifetime rules / 检查生命周期规则
    bool concurrencyChecks = true;  // Check concurrency rules / 检查并发规则
};

// File detector / 文件检测器
class FileDetector {
public:
    // Check if file should be analyzed / 检查文件是否应该被分析
    // Method 1: .tcc extension / 方法1：.tcc 扩展名
    // Method 2: // @tcc annotation in file / 方法2：文件中的 // @tcc 注解
    static bool shouldAnalyze(const std::string& filename);
    
    // Parse TCC configuration from file / 从文件解析 TCC 配置
    static std::optional<TCCConfig> parseConfig(const std::string& filename);
    
private:
    // Check file extension / 检查文件扩展名
    static bool hasTCCExtension(const std::string& filename);
    
    // Check for annotation in file / 检查文件中的注解
    static bool hasTCCAnnotation(const std::string& filename);
    
    // Parse annotation config / 解析注解配置
    static TCCConfig parseAnnotation(const std::string& content);
};

} // namespace tcc
