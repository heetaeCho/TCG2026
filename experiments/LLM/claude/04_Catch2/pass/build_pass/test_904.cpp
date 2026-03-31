#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// Use a simple clock for testing
using TestClock = std::chrono::steady_clock;

class MeasureOneTest_904 : public ::testing::Test {
protected:
};

// Test that measure_one returns the correct number of iterations
TEST_F(MeasureOneTest_904, ReturnsCorrectIterationCount_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 42; });
    };
    
    int iters = 10;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, iters);
}

// Test with single iteration
TEST_F(MeasureOneTest_904, SingleIteration_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 1; });
    };
    
    int iters = 1;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, 1);
}

// Test that elapsed time is non-negative
TEST_F(MeasureOneTest_904, ElapsedTimeIsNonNegative_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 0; });
    };
    
    int iters = 5;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test that the function result is captured
TEST_F(MeasureOneTest_904, CapturesFunctionResult_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 42; });
    };
    
    int iters = 3;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    // The result should exist and iterations should be correct
    EXPECT_EQ(result.iterations, 3);
}

// Test with a function that does some measurable work
TEST_F(MeasureOneTest_904, MeasuresElapsedTimeForWork_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() {
            volatile int sum = 0;
            for (int i = 0; i < 1000; ++i) {
                sum += i;
            }
            return sum;
        });
    };
    
    int iters = 10;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, 10);
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with zero iterations (boundary condition)
TEST_F(MeasureOneTest_904, ZeroIterations_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 0; });
    };
    
    int iters = 0;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, 0);
}

// Test with large iteration count
TEST_F(MeasureOneTest_904, LargeIterationCount_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 1; });
    };
    
    int iters = 100000;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, 100000);
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with a lambda that returns void via measure
TEST_F(MeasureOneTest_904, VoidMeasureFunction_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() {
            volatile int x = 1;
            (void)x;
        });
    };
    
    int iters = 5;
    auto result = measure_one<TestClock>(fun, iters, std::true_type{});
    
    EXPECT_EQ(result.iterations, 5);
}

// Test that multiple calls produce consistent iteration counts
TEST_F(MeasureOneTest_904, ConsistentIterationCounts_904) {
    auto fun = [](Chronometer meter) {
        meter.measure([]() { return 99; });
    };
    
    for (int i = 1; i <= 10; ++i) {
        auto result = measure_one<TestClock>(fun, i, std::true_type{});
        EXPECT_EQ(result.iterations, i);
    }
}
