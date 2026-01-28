// Test file for malloc/free violations
// malloc/free 违规测试文件
// @tcc

#include <cstdlib>
#include <cstring>

// BAD: Using malloc / 错误：使用 malloc
void* allocateMemory(size_t size) {
    return malloc(size);  // TCC-OWN-003 error
}

// BAD: Using calloc / 错误：使用 calloc
int* allocateArray(size_t count) {
    return static_cast<int*>(calloc(count, sizeof(int)));  // TCC-OWN-003
}

// BAD: Using realloc / 错误：使用 realloc
void* resizeMemory(void* ptr, size_t newSize) {
    return realloc(ptr, newSize);  // TCC-OWN-003
}

// BAD: Using free / 错误：使用 free
void freeMemory(void* ptr) {
    free(ptr);  // TCC-OWN-003 error
}

int main() {
    void* mem = allocateMemory(100);
    int* arr = allocateArray(10);
    
    mem = resizeMemory(mem, 200);
    
    freeMemory(mem);
    freeMemory(arr);
    
    return 0;
}
