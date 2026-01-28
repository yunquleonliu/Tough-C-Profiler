// Test file for raw pointer containers
// 原始指针容器测试文件
// @tcc

#include <vector>
#include <list>

class Data {
public:
    Data(int val) : value_(val) {}
    int value_;
};

// BAD: vector of raw pointers / 错误：原始指针的 vector
std::vector<Data*> rawPointerVector;  // TCC-LIFE-003 error

// BAD: list of raw pointers / 错误：原始指针的 list
std::list<int*> rawPointerList;  // TCC-LIFE-003 error

class Container {
public:
    // BAD: member container of raw pointers / 错误：原始指针的成员容器
    std::vector<Data*> items_;  // TCC-LIFE-003 error
};

void processData() {
    // BAD: local container of raw pointers / 错误：原始指针的局部容器
    std::vector<Data*> localItems;  // TCC-LIFE-003 error
    
    // Unclear lifetime - who owns these?
    // 生命周期不明确 - 谁拥有这些？
    localItems.push_back(new Data(1));  // Also TCC-OWN-001
    localItems.push_back(new Data(2));  // Also TCC-OWN-001
}

int main() {
    processData();
    return 0;
}
