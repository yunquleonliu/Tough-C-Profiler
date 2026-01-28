// Test file for lifetime violations - dangling references
// 生命周期违规测试文件 - 悬空引用
// @tcc

#include <string>

// BAD: Returning reference to local / 错误：返回局部变量的引用
const std::string& getBadString() {
    std::string local = "temporary";
    return local;  // TCC-LIFE-001 error - dangling reference
}

// BAD: Returning pointer to local / 错误：返回局部变量的指针
int* getBadPointer() {
    int value = 42;
    return &value;  // TCC-LIFE-002 error - dangling pointer
}

// BAD: Returning reference to local array / 错误：返回局部数组的引用
int& getBadArrayElement() {
    int arr[10] = {0};
    return arr[0];  // TCC-LIFE-001 error
}

class Widget {
public:
    // BAD: Returning reference to temp / 错误：返回临时对象的引用
    const std::string& getTempString() {
        std::string temp = "bad";
        return temp;  // TCC-LIFE-001 error
    }
};

int main() {
    // All of these create dangling references/pointers
    // 所有这些都创建悬空引用/指针
    const std::string& str = getBadString();  // Dangling!
    int* ptr = getBadPointer();               // Dangling!
    int& ref = getBadArrayElement();          // Dangling!
    
    return 0;
}
