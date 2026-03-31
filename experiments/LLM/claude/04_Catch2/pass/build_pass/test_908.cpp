#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

namespace {

// Test fixture for warmup tests
class WarmupTest_908 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that warmup returns a positive number of iterations
TEST_F(WarmupTest_908, ReturnsPositiveIterations_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::high_resolution_clock>();
    EXPECT_GT(iterations, 0) << "warmup should return a positive number of iterations";
}

// Test that warmup returns at least the warmup_seed value
TEST_F(WarmupTest_908, ReturnsAtLeastWarmupSeed_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::high_resolution_clock>();
    EXPECT_GE(iterations, Catch::Benchmark::Detail::warmup_seed)
        << "warmup should return at least warmup_seed iterations";
}

// Test that warmup with steady_clock also works and returns positive iterations
TEST_F(WarmupTest_908, WorksWithSteadyClock_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::steady_clock>();
    EXPECT_GT(iterations, 0) << "warmup with steady_clock should return positive iterations";
}

// Test that warmup with steady_clock returns at least warmup_seed
TEST_F(WarmupTest_908, SteadyClockReturnsAtLeastWarmupSeed_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::steady_clock>();
    EXPECT_GE(iterations, Catch::Benchmark::Detail::warmup_seed)
        << "warmup with steady_clock should return at least warmup_seed iterations";
}

// Test that calling warmup multiple times produces consistent results (both positive)
TEST_F(WarmupTest_908, ConsistentResultsAcrossMultipleCalls_908) {
    int iterations1 = Catch::Benchmark::Detail::warmup<std::chrono::high_resolution_clock>();
    int iterations2 = Catch::Benchmark::Detail::warmup<std::chrono::high_resolution_clock>();
    EXPECT_GT(iterations1, 0);
    EXPECT_GT(iterations2, 0);
    // Both should be in the same general ballpark (within 10x of each other)
    // This is a sanity check that the function behaves deterministically enough
    EXPECT_GT(iterations1, iterations2 / 10);
    EXPECT_GT(iterations2, iterations1 / 10);
}

// Test that warmup_time is the expected 100 milliseconds
TEST_F(WarmupTest_908, WarmupTimeIsCorrect_908) {
    EXPECT_EQ(Catch::Benchmark::Detail::warmup_time, std::chrono::milliseconds(100));
}

// Test that warmup_seed is the expected 10000
TEST_F(WarmupTest_908, WarmupSeedIsCorrect_908) {
    EXPECT_EQ(Catch::Benchmark::Detail::warmup_seed, 10000);
}

// Test that warmup with system_clock also produces valid results
TEST_F(WarmupTest_908, WorksWithSystemClock_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::system_clock>();
    EXPECT_GT(iterations, 0) << "warmup with system_clock should return positive iterations";
    EXPECT_GE(iterations, Catch::Benchmark::Detail::warmup_seed)
        << "warmup with system_clock should return at least warmup_seed iterations";
}

// Test that the return value is a reasonable integer (not overflowed or negative)
TEST_F(WarmupTest_908, ReturnValueIsReasonable_908) {
    int iterations = Catch::Benchmark::Detail::warmup<std::chrono::high_resolution_clock>();
    // The value should be positive and within reasonable int range
    EXPECT_GT(iterations, 0);
    EXPECT_LT(iterations, std::numeric_limits<int>::max());
}

} // namespace
