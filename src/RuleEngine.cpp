// Tough C Profiler - Rule Engine Implementation
// Tough C 分析器 - 规则引擎实现

#include "tcc/RuleEngine.h"

namespace tcc {

RuleEngine::RuleEngine() {
    // Constructor / 构造函数
}

void RuleEngine::initializeDefaultRules() {
    // TODO: Register default rules / 待实现：注册默认规则
    // This will be implemented in Phase 3-5
    // 这将在阶段3-5中实现
    
    // For MVP placeholder / MVP占位符
    // - Ownership rules will be added in Phase 3
    // - Lifetime rules will be added in Phase 4  
    // - Concurrency rules will be added in Phase 5
    
    // - 所有权规则将在阶段3添加
    // - 生命周期规则将在阶段4添加
    // - 并发规则将在阶段5添加
}

void RuleEngine::addRule(std::unique_ptr<Rule> rule) {
    rules_.push_back(std::move(rule));
}

void RuleEngine::analyze(clang::ASTContext& context, DiagnosticEngine& diagnostics) {
    // Run all enabled rules / 运行所有启用的规则
    for (const auto& rule : rules_) {
        // Check if rule category is enabled / 检查规则类别是否启用
        if (!isCategoryEnabled(rule->getCategory())) {
            continue;
        }
        
        // Execute rule / 执行规则
        rule->check(context, diagnostics);
    }
}

void RuleEngine::enableCategory(RuleCategory category, bool enabled) {
    switch (category) {
        case RuleCategory::Ownership:
            ownershipEnabled_ = enabled;
            break;
        case RuleCategory::Lifetime:
            lifetimeEnabled_ = enabled;
            break;
        case RuleCategory::Concurrency:
            concurrencyEnabled_ = enabled;
            break;
        default:
            break;
    }
}

bool RuleEngine::isCategoryEnabled(RuleCategory category) const {
    switch (category) {
        case RuleCategory::Ownership:
            return ownershipEnabled_;
        case RuleCategory::Lifetime:
            return lifetimeEnabled_;
        case RuleCategory::Concurrency:
            return concurrencyEnabled_;
        default:
            return false;
    }
}

size_t RuleEngine::getRuleCount() const {
    return rules_.size();
}

size_t RuleEngine::getActiveRuleCount() const {
    size_t count = 0;
    for (const auto& rule : rules_) {
        if (isCategoryEnabled(rule->getCategory())) {
            ++count;
        }
    }
    return count;
}

} // namespace tcc
