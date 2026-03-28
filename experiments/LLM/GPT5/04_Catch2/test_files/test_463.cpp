// File: tests/catch_debugger_isDebuggerActive_test.cpp

#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

// Forward declaration from the production code (no internal peeking).
namespace Catch {
    bool isDebuggerActive();
}

// Test suite name must include TEST_ID per requirement.
class CatchDebuggerTest_463 : public ::testing::Test {};

// [Smoke] The function should be callable without throwing or crashing.
TEST_F(CatchDebuggerTest_463, CallDoesNotThrow_463) {
    // Even if /proc/self/status doesn't exist (e.g., non-Linux), the function
    // should simply return false rather than throwing.
    EXPECT_NO_THROW({
        (void)Catch::isDebuggerActive();
    });
}

// [Determinism] Multiple calls within the same process should be consistent.
// We do not assert a specific value (true/false); only that it doesn't fluctuate.
TEST_F(CatchDebuggerTest_463, RepeatedCallsReturnConsistentValue_463) {
    const bool first = Catch::isDebuggerActive();
    const bool second = Catch::isDebuggerActive();
    const bool third = Catch::isDebuggerActive();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// [Concurrency] Concurrent calls should all agree with a single-threaded call.
// This checks thread-safety from the public API perspective.
TEST_F(CatchDebuggerTest_463, ConcurrentCallsAreConsistent_463) {
    const bool expected = Catch::isDebuggerActive();

    constexpr int kThreads = 8;
    std::vector<std::thread> threads;
    std::vector<bool> results(kThreads, !expected); // init to opposite just to be sure

    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([i, &results]() {
            results[i] = Catch::isDebuggerActive();
        });
    }
    for (auto& t : threads) t.join();

    for (bool v : results) {
        EXPECT_EQ(v, expected);
    }
}

// [Basic Contract] The return value must be a valid boolean, and calling
// it many times should not degrade or change the observable behavior.
TEST_F(CatchDebuggerTest_463, ManyCallsRemainStable_463) {
    const bool expected = Catch::isDebuggerActive();
    for (int i = 0; i < 100; ++i) {
        bool v = Catch::isDebuggerActive();
        EXPECT_EQ(v, expected);
    }
}
