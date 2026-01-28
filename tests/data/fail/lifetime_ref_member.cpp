// Test file for reference members
// 引用成员测试文件
// @tcc

#include <string>

// WARNING: Reference member without clear lifetime
// 警告：没有明确生命周期的引用成员
class WidgetRef {
public:
    WidgetRef(std::string& name) : name_(name) {}  // TCC-LIFE-004 warning
    
    const std::string& getName() const { return name_; }
    
private:
    std::string& name_;  // TCC-LIFE-004 - lifetime dependency unclear
};

// WARNING: Multiple reference members / 警告：多个引用成员
class DataHolder {
public:
    DataHolder(int& value, std::string& label)
        : value_(value), label_(label) {}  // TCC-LIFE-004 warnings
    
private:
    int& value_;          // TCC-LIFE-004
    std::string& label_;  // TCC-LIFE-004
};

int main() {
    std::string name = "test";
    WidgetRef widget(name);
    
    int value = 42;
    std::string label = "answer";
    DataHolder holder(value, label);
    
    return 0;
}
