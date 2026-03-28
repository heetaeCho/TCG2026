#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include <thread>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// A mock clock that returns controlled time points
struct MockClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<MockClock, duration>;
    static const bool is_steady = true;

    static inline std::vector<time_point> time_points;
    static inline size_t call_index = 0;

    static time_point now() {
        if (call_index < time_points.size()) {
            return time_points[call_index++];
        }
        // Fallback: return epoch
        return time_point(duration(0));
    }

    static void reset(const std::vector<int64_t>& nanoseconds) {
        time_points.clear();
        call_index = 0;
        for (auto ns : nanoseconds) {
            time_points.push_back(time_point(duration(ns)));
        }
    }
};

class ResolutionTest_907 : public ::testing::Test {
protected:
    void SetUp() override {
        MockClock::time_points.clear();
        MockClock::call_index = 0;
    }

    void TearDown() override {
        MockClock::time_points.clear();
        MockClock::call_index = 0;
    }
};

// Test that resolution with k=1 returns exactly 1 delta
TEST_F(ResolutionTest_907, SingleDelta_907) {
    MockClock::reset({100, 200});  // 2 points -> 1 delta

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(1);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0], 100.0);
}

// Test that resolution with k=0 returns an empty vector
TEST_F(ResolutionTest_907, ZeroK_ReturnsEmpty_907) {
    MockClock::reset({100});  // 1 point -> 0 deltas

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(0);

    EXPECT_TRUE(result.empty());
}

// Test that resolution with k=5 returns exactly 5 deltas
TEST_F(ResolutionTest_907, MultipleDeltasCount_907) {
    MockClock::reset({0, 10, 30, 60, 100, 150});  // 6 points -> 5 deltas

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(5);

    ASSERT_EQ(result.size(), 5u);
}

// Test that resolution computes correct delta values
TEST_F(ResolutionTest_907, CorrectDeltaValues_907) {
    MockClock::reset({0, 10, 30, 60, 100, 150});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(5);

    ASSERT_EQ(result.size(), 5u);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
    EXPECT_DOUBLE_EQ(result[1], 20.0);
    EXPECT_DOUBLE_EQ(result[2], 30.0);
    EXPECT_DOUBLE_EQ(result[3], 40.0);
    EXPECT_DOUBLE_EQ(result[4], 50.0);
}

// Test that identical timestamps produce zero deltas
TEST_F(ResolutionTest_907, IdenticalTimestampsProduceZeroDeltas_907) {
    MockClock::reset({100, 100, 100, 100});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(3);

    ASSERT_EQ(result.size(), 3u);
    for (const auto& delta : result) {
        EXPECT_DOUBLE_EQ(delta, 0.0);
    }
}

// Test that resolution with k=1 and equal timestamps gives zero
TEST_F(ResolutionTest_907, SingleZeroDelta_907) {
    MockClock::reset({500, 500});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(1);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
}

// Test with uniformly spaced time points
TEST_F(ResolutionTest_907, UniformSpacing_907) {
    MockClock::reset({0, 100, 200, 300});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(3);

    ASSERT_EQ(result.size(), 3u);
    for (const auto& delta : result) {
        EXPECT_DOUBLE_EQ(delta, 100.0);
    }
}

// Test with large time values
TEST_F(ResolutionTest_907, LargeTimeValues_907) {
    int64_t base = 1000000000LL;  // 1 second in nanoseconds
    MockClock::reset({base, base + 1000000, base + 3000000});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(2);

    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 1000000.0);
    EXPECT_DOUBLE_EQ(result[1], 2000000.0);
}

// Test with a single nanosecond difference
TEST_F(ResolutionTest_907, SingleNanosecondDifference_907) {
    MockClock::reset({0, 1});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(1);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
}

// Test that the result is a vector of doubles
TEST_F(ResolutionTest_907, ReturnTypeIsVectorOfDoubles_907) {
    MockClock::reset({0, 50, 100});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(2);

    // Verify it's a vector<double> by checking values as doubles
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(typeid(result), typeid(std::vector<double>));
}

// Test with non-monotonic clock values (timestamps that can go backwards)
TEST_F(ResolutionTest_907, NonMonotonicTimestamps_907) {
    MockClock::reset({100, 50, 200});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(2);

    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], -50.0);
    EXPECT_DOUBLE_EQ(result[1], 150.0);
}

// Test with larger k value
TEST_F(ResolutionTest_907, LargerK_907) {
    std::vector<int64_t> timepoints;
    int k = 10;
    for (int i = 0; i <= k; ++i) {
        timepoints.push_back(static_cast<int64_t>(i) * 5);
    }
    MockClock::reset(timepoints);

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(k);

    ASSERT_EQ(result.size(), static_cast<size_t>(k));
    for (const auto& delta : result) {
        EXPECT_DOUBLE_EQ(delta, 5.0);
    }
}

// Test using the system high_resolution_clock (integration-style test)
TEST_F(ResolutionTest_907, SystemClockReturnsNonEmptyForPositiveK_907) {
    auto result = Catch::Benchmark::Detail::resolution<std::chrono::high_resolution_clock>(3);

    ASSERT_EQ(result.size(), 3u);
    // Each delta should be non-negative (clock should not go backwards on a steady clock)
    for (const auto& delta : result) {
        EXPECT_GE(delta, 0.0);
    }
}

// Test with varying deltas
TEST_F(ResolutionTest_907, VaryingDeltas_907) {
    MockClock::reset({0, 1, 3, 6, 10, 15, 21});

    auto result = Catch::Benchmark::Detail::resolution<MockClock>(6);

    ASSERT_EQ(result.size(), 6u);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
    EXPECT_DOUBLE_EQ(result[3], 4.0);
    EXPECT_DOUBLE_EQ(result[4], 5.0);
    EXPECT_DOUBLE_EQ(result[5], 6.0);
}
