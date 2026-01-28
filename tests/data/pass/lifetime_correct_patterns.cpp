// Test file for correct lifetime patterns
// 正确生命周期模式测试文件
// @tcc

#include <memory>
#include <string>
#include <vector>
#include <functional>

class Data {
public:
    Data(int val) : value_(val) {}
    int getValue() const { return value_; }
private:
    int value_;
};

// GOOD: Return by value / 良好：按值返回
std::string getString() {
    std::string local = "safe";
    return local;  // Move or copy, but safe
}

// GOOD: Return unique_ptr / 良好：返回 unique_ptr
std::unique_ptr<Data> createData(int val) {
    return std::make_unique<Data>(val);
}

// GOOD: Return reference to parameter / 良好：返回参数的引用
const std::string& getLonger(const std::string& a, const std::string& b) {
    return a.length() > b.length() ? a : b;
}

// GOOD: Container of smart pointers / 良好：智能指针的容器
class SafeContainer {
public:
    void addItem(std::unique_ptr<Data> item) {
        items_.push_back(std::move(item));
    }
    
    const std::vector<std::unique_ptr<Data>>& getItems() const {
        return items_;
    }
    
private:
    std::vector<std::unique_ptr<Data>> items_;  // Safe lifetime
};

// GOOD: Using reference_wrapper for clarity / 良好：使用 reference_wrapper 以保持清晰
class WidgetWrapper {
public:
    WidgetWrapper(std::string& name) : name_(name) {}
    
    std::string& getName() { return name_.get(); }
    
private:
    std::reference_wrapper<std::string> name_;  // Clear reference semantics
};

// GOOD: Store by value / 良好：按值存储
class ValueHolder {
public:
    ValueHolder(std::string name) : name_(std::move(name)) {}
    
    const std::string& getName() const { return name_; }
    
private:
    std::string name_;  // Owns the value
};

int main() {
    // All lifetimes are clear / 所有生命周期都是明确的
    auto str = getString();
    auto data = createData(42);
    
    std::string a = "hello";
    std::string b = "world";
    const std::string& longer = getLonger(a, b);
    
    SafeContainer container;
    container.addItem(std::make_unique<Data>(1));
    container.addItem(std::make_unique<Data>(2));
    
    ValueHolder holder("safe");
    
    return 0;
}
