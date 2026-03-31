#include <gtest/gtest.h>
#include <chrono>
#include <type_traits>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// We need the Environment and related types from Catch::Benchmark::Detail
// These should be available through the amalgamated header

using namespace Catch::Benchmark::Detail;
using namespace Catch::Benchmark;

// Use a real clock type for testing
using SteadyClock = std::chrono::steady_clock;
using HighResClock = std::chrono::high_resolution_clock;

// Test fixture
class MeasureEnvironmentTest_911 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that measure_environment returns a valid Environment object
TEST_F(MeasureEnvironmentTest_911, ReturnsValidEnvironment_911) {
    auto env = measure_environment<SteadyClock>();
    // The environment should have been created successfully
    // We verify by checking that resolution mean is positive (non-zero duration)
    EXPECT_GT(env.clock_resolution.mean.count(), 0);
}

// Test that measure_environment returns consistent results on repeated calls (cached)
TEST_F(MeasureEnvironmentTest_911, ReturnsCachedResultOnSecondCall_911) {
    auto env1 = measure_environment<SteadyClock>();
    auto env2 = measure_environment<SteadyClock>();
    
    // Since the result is cached in a static variable, both calls should return
    // the same environment
    EXPECT_EQ(env1.clock_resolution.mean.count(), env2.clock_resolution.mean.count());
    EXPECT_EQ(env1.clock_cost.mean.count(), env2.clock_cost.mean.count());
}

// Test that clock_resolution mean is a positive value
TEST_F(MeasureEnvironmentTest_911, ClockResolutionMeanIsPositive_911) {
    auto env = measure_environment<SteadyClock>();
    EXPECT_GT(env.clock_resolution.mean.count(), 0);
}

// Test that clock_cost mean is non-negative
TEST_F(MeasureEnvironmentTest_911, ClockCostMeanIsNonNegative_911) {
    auto env = measure_environment<SteadyClock>();
    EXPECT_GE(env.clock_cost.mean.count(), 0);
}

// Test with high_resolution_clock
TEST_F(MeasureEnvironmentTest_911, WorksWithHighResolutionClock_911) {
    auto env = measure_environment<HighResClock>();
    EXPECT_GT(env.clock_resolution.mean.count(), 0);
}

// Test that repeated calls with the same clock type yield identical results (static caching)
TEST_F(MeasureEnvironmentTest_911, MultipleCallsReturnIdenticalResults_911) {
    auto env1 = measure_environment<SteadyClock>();
    auto env2 = measure_environment<SteadyClock>();
    auto env3 = measure_environment<SteadyClock>();
    
    EXPECT_EQ(env1.clock_resolution.mean.count(), env2.clock_resolution.mean.count());
    EXPECT_EQ(env2.clock_resolution.mean.count(), env3.clock_resolution.mean.count());
    EXPECT_EQ(env1.clock_cost.mean.count(), env2.clock_cost.mean.count());
    EXPECT_EQ(env2.clock_cost.mean.count(), env3.clock_cost.mean.count());
}

// Test that the resolution is reasonable (less than 1 second for modern clocks)
TEST_F(MeasureEnvironmentTest_911, ClockResolutionIsReasonable_911) {
    auto env = measure_environment<SteadyClock>();
    // Clock resolution should be less than 1 second on any modern system
    auto one_second = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::seconds(1));
    EXPECT_LT(env.clock_resolution.mean.count(), one_second.count());
}

// Test that clock cost is reasonable (less than 1 second)
TEST_F(MeasureEnvironmentTest_911, ClockCostIsReasonable_911) {
    auto env = measure_environment<SteadyClock>();
    auto one_second = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::seconds(1));
    EXPECT_LT(env.clock_cost.mean.count(), one_second.count());
}

// Test that Environment struct fields are properly populated
TEST_F(MeasureEnvironmentTest_911, EnvironmentFieldsArePopulated_911) {
    auto env = measure_environment<SteadyClock>();
    // Both clock_resolution and clock_cost should have their mean values set
    // We can't check for specific values, but we can check they exist and are reasonable
    auto res_mean = env.clock_resolution.mean;
    auto cost_mean = env.clock_cost.mean;
    
    // Resolution should be positive
    EXPECT_GT(res_mean.count(), 0);
    // Cost can be zero or positive
    EXPECT_GE(cost_mean.count(), 0);
}

// Test that the function is deterministic (same clock type always returns same cached value)
TEST_F(MeasureEnvironmentTest_911, IsDeterministicForSameClockType_911) {
    std::vector<decltype(measure_environment<SteadyClock>().clock_resolution.mean.count())> results;
    for (int i = 0; i < 10; ++i) {
        auto env = measure_environment<SteadyClock>();
        results.push_back(env.clock_resolution.mean.count());
    }
    
    for (size_t i = 1; i < results.size(); ++i) {
        EXPECT_EQ(results[0], results[i]) 
            << "Call " << i << " returned different resolution than call 0";
    }
}
