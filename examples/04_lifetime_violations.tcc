// Tough C Example - Lifetime Violations (Should Fail)
// Tough C 示例 - 生命周期违规（应该失败）
// @tcc

#include <string>
#include <vector>

// BAD: Returning reference to local / 错误：返回局部变量的引用
const std::string& getBadString() {
    std::string local = "temporary";
    return local;  // TCC ERROR: Returning reference to local variable
                   // TCC 错误：返回局部变量的引用
}  // 'local' is destroyed here / 'local' 在此处销毁

// BAD: Returning pointer to local / 错误：返回局部变量的指针
int* getBadPointer() {
    int value = 42;
    return &value;  // TCC ERROR: Returning pointer to local variable
                    // TCC 错误：返回局部变量的指针
}

class Container {
public:
    // BAD: Storing raw pointer / 错误：存储原始指针
    void addItem(int* item) {
        items_.push_back(item);  // TCC ERROR: Storing raw pointer
                                 // TCC 错误：存储原始指针
    }
    
private:
    std::vector<int*> items_;  // TCC ERROR: Container of raw pointers
                               // TCC 错误：原始指针的容器
};

int main() {
    // These will create dangling references / 这些将创建悬空引用
    const std::string& bad1 = getBadString();  // Dangling! / 悬空！
    int* bad2 = getBadPointer();  // Dangling! / 悬空！
    
    return 0;
}

// This file should trigger TCC errors:
// 此文件应该触发 TCC 错误：
// 1. Returning reference to local variable / 返回局部变量的引用
// 2. Returning pointer to local variable / 返回局部变量的指针
// 3. Container storing raw pointers / 存储原始指针的容器
//
// Fix: Use value semantics or smart pointers
// 修复：使用值语义或智能指针
