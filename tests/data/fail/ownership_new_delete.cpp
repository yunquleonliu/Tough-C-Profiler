// Test file for ownership rule violations
// 所有权规则违规测试文件
// This should trigger TCC-OWN-001 and TCC-OWN-002 errors
// 这应该触发 TCC-OWN-001 和 TCC-OWN-002 错误
// @tcc

class TestClass {
public:
    TestClass(int val) : value(val) {}
    int value;
};

// BAD: Using new operator / 错误：使用 new 操作符
TestClass* createWithNew() {
    return new TestClass(42);  // TCC-OWN-001 error
}

// BAD: Using delete operator / 错误：使用 delete 操作符
void deleteObject(TestClass* obj) {
    delete obj;  // TCC-OWN-002 error
}

int main() {
    TestClass* obj = createWithNew();  // TCC-OWN-001
    deleteObject(obj);                  // TCC-OWN-002
    return 0;
}
