// Test file for raw owning pointer pattern
// 原始所有权指针模式测试文件
// @tcc

class Resource {
public:
    Resource(int value) : data_(value) {}
    int getData() const { return data_; }
private:
    int data_;
};

// WARNING: Function name suggests ownership transfer
// 警告：函数名暗示所有权转移
Resource* createResource(int value) {  // TCC-OWN-004 warning
    return new Resource(value);  // Also TCC-OWN-001 error
}

// WARNING: "make" suggests ownership / 警告："make" 暗示所有权
Resource* makeResource() {  // TCC-OWN-004 warning
    return new Resource(42);  // TCC-OWN-001 error
}

// WARNING: "alloc" suggests ownership / 警告："alloc" 暗示所有权
Resource* allocResource() {  // TCC-OWN-004 warning
    return new Resource(100);  // TCC-OWN-001 error
}

// OK: Name doesn't suggest ownership (but still gets error for 'new')
// 可以：名字不暗示所有权（但仍然因为 'new' 而出错）
Resource* getResource() {
    return new Resource(200);  // TCC-OWN-001 error (but not TCC-OWN-004)
}

int main() {
    Resource* r1 = createResource(1);
    Resource* r2 = makeResource();
    Resource* r3 = allocResource();
    
    delete r1;  // TCC-OWN-002 error
    delete r2;  // TCC-OWN-002 error
    delete r3;  // TCC-OWN-002 error
    
    return 0;
}
