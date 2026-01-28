# Tough C Tests / Tough C 测试
# Test suite for TCC profiler
# TCC 分析器测试套件

# Enable testing / 启用测试
enable_testing()

# Test utilities / 测试工具
set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

# Helper function to add TCC test / 添加 TCC 测试的辅助函数
function(add_tcc_test test_name source_file should_pass)
    add_test(
        NAME ${test_name}
        COMMAND tcc-check ${TEST_DATA_DIR}/${source_file}
    )
    
    if(should_pass)
        # Test should pass (exit code 0) / 测试应该通过（退出码0）
        set_tests_properties(${test_name} PROPERTIES
            PASS_REGULAR_EXPRESSION "All checks passed"
        )
    else()
        # Test should fail (exit code 1) / 测试应该失败（退出码1）
        set_tests_properties(${test_name} PROPERTIES
            WILL_FAIL TRUE
        )
    endif()
endfunction()

# Placeholder tests - will be populated in Phase 7
# 占位符测试 - 将在阶段7填充

# add_tcc_test(ownership_pass_unique_ptr "pass/ownership_unique_ptr.cpp" TRUE)
# add_tcc_test(ownership_fail_raw_new "fail/ownership_raw_new.cpp" FALSE)
