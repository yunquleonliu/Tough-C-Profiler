// Tough C Profiler - AST Visitor Implementation
// Tough C 分析器 - AST 访问者实现

#include "tcc/ASTVisitor.h"
#include "tcc/OwnershipRules.h"

#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>

namespace tcc {

bool TCCASTVisitor::VisitFunctionDecl(clang::FunctionDecl* decl) {
    if (!decl || !isInMainFile(decl->getLocation())) {
        return true;
    }
    
    // Function declarations are checked by specific rules
    // 函数声明由特定规则检查
    return true;
}

bool TCCASTVisitor::VisitVarDecl(clang::VarDecl* decl) {
    if (!decl || !isInMainFile(decl->getLocation())) {
        return true;
    }
    
    // Variable declarations are checked by specific rules
    // 变量声明由特定规则检查
    return true;
}

bool TCCASTVisitor::VisitCXXNewExpr(clang::CXXNewExpr* expr) {
    if (!expr || !isInMainFile(expr->getLocation())) {
        return true;
    }
    
    // Found a 'new' expression - let rules handle it
    // 发现 'new' 表达式 - 让规则处理
    for (const auto& rule : rules_) {
        if (auto* ownershipRule = dynamic_cast<ForbidNewRule*>(rule.get())) {
            ownershipRule->checkNewExpr(expr, context_, diagnostics_);
        }
    }
    
    return true;
}

bool TCCASTVisitor::VisitCXXDeleteExpr(clang::CXXDeleteExpr* expr) {
    if (!expr || !isInMainFile(expr->getLocation())) {
        return true;
    }
    
    // Found a 'delete' expression - let rules handle it
    // 发现 'delete' 表达式 - 让规则处理
    for (const auto& rule : rules_) {
        if (auto* ownershipRule = dynamic_cast<ForbidDeleteRule*>(rule.get())) {
            ownershipRule->checkDeleteExpr(expr, context_, diagnostics_);
        }
    }
    
    return true;
}

bool TCCASTVisitor::VisitReturnStmt(clang::ReturnStmt* stmt) {
    if (!stmt || !isInMainFile(stmt->getReturnLoc())) {
        return true;
    }
    
    // Return statements are checked by lifetime rules
    // return 语句由生命周期规则检查
    return true;
}

bool TCCASTVisitor::VisitLambdaExpr(clang::LambdaExpr* expr) {
    if (!expr || !isInMainFile(expr->getLocation())) {
        return true;
    }
    
    // Lambda expressions are checked by concurrency rules
    // Lambda 表达式由并发规则检查
    return true;
}

bool TCCASTVisitor::VisitCXXConstructExpr(clang::CXXConstructExpr* expr) {
    if (!expr || !isInMainFile(expr->getLocation())) {
        return true;
    }
    
    // Check for std::thread construction
    // 检查 std::thread 构造
    const auto* ctorDecl = expr->getConstructor();
    if (!ctorDecl) {
        return true;
    }
    
    const auto* recordDecl = ctorDecl->getParent();
    if (!recordDecl) {
        return true;
    }
    
    // Thread construction is checked by concurrency rules
    // 线程构造由并发规则检查
    return true;
}

SourceLocation TCCASTVisitor::getSourceLocation(clang::SourceLocation loc) const {
    if (loc.isInvalid()) {
        return SourceLocation();
    }
    
    const auto& sm = context_.getSourceManager();
    auto presumedLoc = sm.getPresumedLoc(loc);
    
    return SourceLocation(
        presumedLoc.getFilename(),
        presumedLoc.getLine(),
        presumedLoc.getColumn()
    );
}

bool TCCASTVisitor::isInMainFile(clang::SourceLocation loc) const {
    if (loc.isInvalid()) {
        return false;
    }
    
    const auto& sm = context_.getSourceManager();
    return sm.isInMainFile(loc);
}

} // namespace tcc
