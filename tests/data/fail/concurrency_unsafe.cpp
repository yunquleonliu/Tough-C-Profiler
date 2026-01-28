// Test file for concurrency violations
// 并发违规测试文件
// @tcc

#include <thread>
#include <vector>

// BAD: Global mutable counter without synchronization
// 错误：全局可变计数器没有同步
int global_counter = 0;  // TCC-CONC-001 warning

// BAD: Static mutable state / 错误：静态可变状态
static int shared_value = 0;  // TCC-CONC-001 warning

class UnsafeCounter {
public:
    void increment() {
        ++count_;  // Data race! / 数据竞争！
    }
    
    int get() const { return count_; }
    
private:
    int count_ = 0;  // Shared mutable without protection
};

// BAD: Capturing non-const reference in thread lambda
// 错误：在线程 lambda 中捕获非 const 引用
void badThreadCapture() {
    int data = 0;
    
    std::thread t([&data]() {  // TCC-CONC-002 error
        data = 42;  // Race condition / 竞态条件
    });
    
    data = 100;  // Race with thread / 与线程竞态
    t.join();
}

// BAD: Multiple threads modifying without sync
// 错误：多个线程修改而没有同步
void unsafeThreads() {
    UnsafeCounter counter;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {  // TCC-CONC-002
            for (int j = 0; j < 1000; ++j) {
                counter.increment();  // Data race!
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    badThreadCapture();
    unsafeThreads();
    return 0;
}
