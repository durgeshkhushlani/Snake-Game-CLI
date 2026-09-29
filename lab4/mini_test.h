#pragma once
#include <iostream>
#include <string>

static int g_tests_run = 0;
static int g_tests_failed = 0;

#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)

#define TEST_CASE(name) \
    void CONCAT(TEST_FUNC_, __LINE__)(); \
    struct CONCAT(TEST_RUNNER_, __LINE__) { \
        CONCAT(TEST_RUNNER_, __LINE__)() { \
            g_tests_run++; \
            std::cout << "[ RUN  ] " << name << std::endl; \
            CONCAT(TEST_FUNC_, __LINE__)(); \
        } \
    } CONCAT(test_runner_instance_, __LINE__); \
    void CONCAT(TEST_FUNC_, __LINE__)()

#define CHECK(cond) \
    if (!(cond)) { \
        g_tests_failed++; \
        std::cout << "  [FAIL] " << #cond << " at line " << __LINE__ << std::endl; \
    } else { \
        std::cout << "  [PASS] " << #cond << std::endl; \
    }

struct TestSummaryPrinter {
    ~TestSummaryPrinter() {
        std::cout << "\n===== " << g_tests_run << " test(s) run, "
                  << g_tests_failed << " failed =====" << std::endl;
    }
};
static TestSummaryPrinter test_summary_printer_instance;