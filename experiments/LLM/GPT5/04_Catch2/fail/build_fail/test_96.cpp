// File: symbol_test_96.cpp
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <cctype>

// Include the header under test
// Adjust the include path as needed for your project layout.
#include "Catch2/src/catch2/catch_tostring.hpp"

// Optional fixture for organization/consistency
class SymbolTest_96 : public ::testing::Test {};

// Normal operation: returns the expected character
TEST_F(SymbolTest_96, ReturnsExpectedChar_96) {
    char c = Catch::symbol();
    EXPECT_EQ('p', c);
}

// Normal operation: consistent across multiple calls
TEST_F(SymbolTest_96, ConsistentAcrossCalls_96) {
    constexpr int kCalls = 10;
    for (int i = 0; i < kCalls; ++i) {
        EXPECT_EQ('p', Catch::symbol());
    }
}

// Boundary-ish observable property: return is a printable ASCII character
TEST_F(SymbolTest_96, IsPrintableAscii_96) {
    unsigned char uc = static_cast<unsigned char>(Catch::symbol());
    EXPECT_NE('\0', Catch::symbol());
    EXPECT_TRUE(std::isprint(uc));
}

// Robustness: concurrent calls (no shared state expected for a free function)
TEST_F(SymbolTest_96, ThreadSafety_SimpleParallelCalls_96) {
    constexpr int kThreads = 8;
    std::vector<std::thread> threads;
    std::atomic<int> ok_count{0};

    threads.reserve(kThreads);
    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([&ok_count]() {
            if (Catch::symbol() == 'p') {
                ++ok_count;
            }
        });
    }
    for (auto& t : threads) t.join();

    EXPECT_EQ(kThreads, ok_count.load());
}
