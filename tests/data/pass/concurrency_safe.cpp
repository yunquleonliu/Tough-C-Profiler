// Test file for correct concurrency patterns
// 正确并发模式测试文件
// @tcc

#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

// GOOD: Atomic counter for thread-safe increment
// 良好：原子计数器用于线程安全递增
std::atomic<int> safe_counter{0};

class SafeCounter {
public:
    void increment() {
        count_.fetch_add(1, std::memory_order_relaxed);
    }
    
    int get() const {
        return count_.load(std::memory_order_relaxed);
    }
    
private:
    std::atomic<int> count_{0};
};

class MutexProtectedData {
public:
    void setValue(int val) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ = val;
    }
    
    int getValue() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }
    
private:
    mutable std::mutex mutex_;
    int value_ = 0;
};

// GOOD: Capturing by value / 良好：按值捕获
void safeThreadCapture() {
    int data = 42;
    
    std::thread t([data]() {  // Safe: copy / 安全：拷贝
        int local = data;
        // Use local copy / 使用本地拷贝
    });
    
    t.join();
}

// GOOD: Each thread works independently / 良好：每个线程独立工作
void safeThreads() {
    SafeCounter counter;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();  // Atomic operation
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
}

// GOOD: Thread-local storage / 良好：线程局部存储
thread_local int thread_specific_data = 0;

int main() {
    safeThreadCapture();
    safeThreads();
    return 0;
}
