#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test that repeat() works with a simple lambda
TEST(RepeatTest_897, RepeatWithLambda_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { ++counter; });
    
    // The repeater should be callable with a count
    rep(5);
    EXPECT_EQ(counter, 5);
}

// Test that repeat() works with zero iterations
TEST(RepeatTest_897, RepeatWithZeroIterations_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { ++counter; });
    
    rep(0);
    EXPECT_EQ(counter, 0);
}

// Test that repeat() works with a single iteration
TEST(RepeatTest_897, RepeatWithSingleIteration_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { ++counter; });
    
    rep(1);
    EXPECT_EQ(counter, 1);
}

// Test that repeat() works with a large number of iterations
TEST(RepeatTest_897, RepeatWithLargeIterations_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { ++counter; });
    
    rep(10000);
    EXPECT_EQ(counter, 10000);
}

// Test that repeat() can be called multiple times
TEST(RepeatTest_897, RepeatCalledMultipleTimes_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { ++counter; });
    
    rep(3);
    EXPECT_EQ(counter, 3);
    
    rep(2);
    EXPECT_EQ(counter, 5);
}

// Test that repeat() preserves the function's side effects correctly
TEST(RepeatTest_897, RepeatPreservesSideEffects_897) {
    std::vector<int> values;
    int i = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&values, &i]() { values.push_back(i++); });
    
    rep(5);
    ASSERT_EQ(values.size(), 5u);
    for (int j = 0; j < 5; ++j) {
        EXPECT_EQ(values[j], j);
    }
}

// Test that repeat() works with a stateful functor
TEST(RepeatTest_897, RepeatWithStatefulFunctor_897) {
    struct Counter {
        int& count;
        void operator()() { ++count; }
    };
    
    int count = 0;
    auto rep = Catch::Benchmark::Detail::repeat(Counter{count});
    
    rep(7);
    EXPECT_EQ(count, 7);
}

// Test that the return type of repeat() is repeater with decayed type
TEST(RepeatTest_897, RepeatReturnTypeIsRepeater_897) {
    auto lambda = []() {};
    auto rep = Catch::Benchmark::Detail::repeat(lambda);
    
    // Verify the type is repeater<decay_t<decltype(lambda)>>
    using expected_type = Catch::Benchmark::Detail::repeater<std::decay_t<decltype(lambda)>>;
    bool is_same = std::is_same<decltype(rep), expected_type>::value;
    EXPECT_TRUE(is_same);
}

// Test repeat with an rvalue lambda
TEST(RepeatTest_897, RepeatWithRvalueLambda_897) {
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&counter]() { counter += 2; });
    
    rep(4);
    EXPECT_EQ(counter, 8);
}

// Test that repeat works with a function that modifies external state in a specific pattern
TEST(RepeatTest_897, RepeatAccumulationPattern_897) {
    int sum = 0;
    int call_number = 0;
    auto rep = Catch::Benchmark::Detail::repeat([&sum, &call_number]() { 
        call_number++;
        sum += call_number; 
    });
    
    rep(4);
    // sum should be 1+2+3+4 = 10
    EXPECT_EQ(sum, 10);
    EXPECT_EQ(call_number, 4);
}
