// File: tests/optimizer_barrier_tests_886.cpp
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>

// ---- Test double for the external collaborator ----
// We define keep_memory() inside the exact namespace so calls from
// optimizer_barrier() become observable through a counter.
// This does NOT re-implement optimizer_barrier's logic; it only observes
// its external interaction.
namespace Catch { namespace Benchmark { namespace Detail {
    static std::atomic<int> g_keep_memory_calls{0};

    // Test double: counts invocations.
    inline void keep_memory() {
        ++g_keep_memory_calls;
    }
}}}

// After the test double is available, include the header under test.
#include "Catch2/extras/catch_amalgamated.hpp"

// Test fixture to reset the observable state before each test.
class OptimizerBarrierTest_886 : public ::testing::Test {
protected:
    void SetUp() override {
        Catch::Benchmark::Detail::g_keep_memory_calls.store(0);
    }
};

TEST_F(OptimizerBarrierTest_886, CallsKeepMemoryOnceOnSingleInvocation_886) {
    using namespace Catch::Benchmark::Detail;

    EXPECT_EQ(g_keep_memory_calls.load(), 0);
    EXPECT_NO_THROW(optimizer_barrier());
    EXPECT_EQ(g_keep_memory_calls.load(), 1);
}

TEST_F(OptimizerBarrierTest_886, CallsKeepMemoryForEachInvocation_MultipleTimes_886) {
    using namespace Catch::Benchmark::Detail;

    EXPECT_EQ(g_keep_memory_calls.load(), 0);
    optimizer_barrier();
    optimizer_barrier();
    optimizer_barrier();
    EXPECT_EQ(g_keep_memory_calls.load(), 3);
}

TEST_F(OptimizerBarrierTest_886, ThreadedInvocations_CallKeepMemoryForEachCall_886) {
    using namespace Catch::Benchmark::Detail;

    constexpr int kThreads = 8;
    constexpr int kCallsPerThread = 50;
    std::vector<std::thread> threads;
    threads.reserve(kThreads);

    for (int t = 0; t < kThreads; ++t) {
        threads.emplace_back([] {
            for (int i = 0; i < kCallsPerThread; ++i) {
                optimizer_barrier();
            }
        });
    }
    for (auto& th : threads) th.join();

    EXPECT_EQ(g_keep_memory_calls.load(), kThreads * kCallsPerThread);
}

TEST_F(OptimizerBarrierTest_886, NoThrowBehavior_IsObservable_886) {
    using namespace Catch::Benchmark::Detail;

    // Verify observable no-throw behavior; also ensures the function is callable.
    EXPECT_NO_THROW(optimizer_barrier());
}
