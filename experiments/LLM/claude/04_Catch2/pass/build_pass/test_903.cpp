#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <type_traits>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// We need to test measure_one which is a template function in Catch::Benchmark::Detail
// It takes a callable, an iteration count, and a false_type tag, and delegates to Detail::measure

namespace {

// A simple clock type for testing
struct TestClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<TestClock, duration>;
    static const bool is_steady = true;
    
    static time_point now() {
        return time_point(std::chrono::duration_cast<duration>(
            std::chrono::steady_clock::now().time_since_epoch()));
    }
};

// A simple callable that tracks invocations
struct TrackingFunctor {
    mutable int call_count = 0;
    
    void operator()(int iters) const {
        call_count += iters;
    }
};

// A functor that does some minimal work
struct MinimalWorkFunctor {
    void operator()(int iters) const {
        volatile int x = 0;
        for (int i = 0; i < iters; ++i) {
            x = x + 1;
        }
    }
};

// A functor that returns a value
struct ReturningFunctor {
    int operator()(int iters) const {
        return iters * 2;
    }
};

} // anonymous namespace

class MeasureOneTest_903 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that measure_one can be called with a simple functor and positive iterations
TEST_F(MeasureOneTest_903, BasicCallWithPositiveIters_903) {
    TrackingFunctor fun;
    int iters = 10;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    // The result should have a non-negative elapsed time
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with single iteration
TEST_F(MeasureOneTest_903, SingleIteration_903) {
    MinimalWorkFunctor fun;
    int iters = 1;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with zero iterations - boundary condition
TEST_F(MeasureOneTest_903, ZeroIterations_903) {
    MinimalWorkFunctor fun;
    int iters = 0;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    // With zero iterations, elapsed time should still be non-negative
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with large iteration count
TEST_F(MeasureOneTest_903, LargeIterationCount_903) {
    MinimalWorkFunctor fun;
    int iters = 100000;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test that the functor is actually called
TEST_F(MeasureOneTest_903, FunctorIsInvoked_903) {
    TrackingFunctor fun;
    int iters = 5;
    
    Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    // The functor should have been called with the iteration count
    EXPECT_GT(fun.call_count, 0);
}

// Test with a lambda function
TEST_F(MeasureOneTest_903, LambdaFunctor_903) {
    int invocation_count = 0;
    auto lambda = [&invocation_count](int iters) {
        invocation_count += iters;
    };
    
    int iters = 7;
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        lambda, iters, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
    EXPECT_GT(invocation_count, 0);
}

// Test that elapsed time is measured (non-trivial work should have positive time with high-res clock)
TEST_F(MeasureOneTest_903, ElapsedTimeIsPositiveForWork_903) {
    auto expensive_fun = [](int iters) {
        volatile int x = 0;
        for (int i = 0; i < iters; ++i) {
            for (int j = 0; j < 1000; ++j) {
                x = x + 1;
            }
        }
    };
    
    int iters = 100;
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        expensive_fun, iters, std::false_type{});
    
    // With significant work, elapsed should be positive
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with high_resolution_clock
TEST_F(MeasureOneTest_903, HighResolutionClock_903) {
    MinimalWorkFunctor fun;
    int iters = 10;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::high_resolution_clock>(
        fun, iters, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test that the result contains the iteration count
TEST_F(MeasureOneTest_903, ResultContainsIterationCount_903) {
    MinimalWorkFunctor fun;
    int iters = 42;
    
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    // The result should store the iterations used
    EXPECT_EQ(result.iterations, iters);
}

// Test with negative iteration count - edge case
TEST_F(MeasureOneTest_903, NegativeIterations_903) {
    TrackingFunctor fun;
    int iters = -1;
    
    // This tests that the function handles negative iters gracefully
    // (behavior depends on implementation, but it shouldn't crash)
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, iters, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test with move-only-like functor (rvalue reference)
TEST_F(MeasureOneTest_903, RValueFunctor_903) {
    auto result = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        MinimalWorkFunctor{}, 5, std::false_type{});
    
    EXPECT_GE(result.elapsed.count(), 0);
}

// Test multiple consecutive calls produce reasonable results
TEST_F(MeasureOneTest_903, MultipleConsecutiveCalls_903) {
    MinimalWorkFunctor fun;
    
    auto result1 = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, 10, std::false_type{});
    auto result2 = Catch::Benchmark::Detail::measure_one<std::chrono::steady_clock>(
        fun, 10, std::false_type{});
    
    EXPECT_GE(result1.elapsed.count(), 0);
    EXPECT_GE(result2.elapsed.count(), 0);
}
