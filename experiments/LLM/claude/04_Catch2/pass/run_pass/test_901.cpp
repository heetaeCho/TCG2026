#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <stdexcept>
#include <string>
#include <functional>

class UserCodeTest_901 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that user_code can invoke a simple lambda returning an int
TEST_F(UserCodeTest_901, ReturnsIntFromLambda_901) {
    auto result = Catch::Benchmark::user_code([]() -> int { return 42; });
    EXPECT_EQ(result, 42);
}

// Test that user_code can invoke a lambda returning a double
TEST_F(UserCodeTest_901, ReturnsDoubleFromLambda_901) {
    auto result = Catch::Benchmark::user_code([]() -> double { return 3.14; });
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test that user_code can invoke a lambda returning a string
TEST_F(UserCodeTest_901, ReturnsStringFromLambda_901) {
    auto result = Catch::Benchmark::user_code([]() -> std::string { return "hello"; });
    EXPECT_EQ(result, "hello");
}

// Test that user_code can invoke a lambda returning a bool
TEST_F(UserCodeTest_901, ReturnsBoolFromLambda_901) {
    auto result = Catch::Benchmark::user_code([]() -> bool { return true; });
    EXPECT_TRUE(result);
}

// Test that user_code can invoke a lambda returning zero (boundary)
TEST_F(UserCodeTest_901, ReturnsZero_901) {
    auto result = Catch::Benchmark::user_code([]() -> int { return 0; });
    EXPECT_EQ(result, 0);
}

// Test that user_code can invoke a lambda returning negative values
TEST_F(UserCodeTest_901, ReturnsNegativeValue_901) {
    auto result = Catch::Benchmark::user_code([]() -> int { return -1; });
    EXPECT_EQ(result, -1);
}

// Test that user_code can invoke a lambda returning max int (boundary)
TEST_F(UserCodeTest_901, ReturnsMaxInt_901) {
    auto result = Catch::Benchmark::user_code([]() -> int { return std::numeric_limits<int>::max(); });
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

// Test that user_code can invoke a lambda returning min int (boundary)
TEST_F(UserCodeTest_901, ReturnsMinInt_901) {
    auto result = Catch::Benchmark::user_code([]() -> int { return std::numeric_limits<int>::min(); });
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

// Test that user_code propagates exceptions thrown by the callable
TEST_F(UserCodeTest_901, PropagatesStdException_901) {
    EXPECT_THROW(
        Catch::Benchmark::user_code([]() -> int { throw std::runtime_error("test error"); }),
        std::runtime_error
    );
}

// Test that user_code propagates arbitrary exceptions
TEST_F(UserCodeTest_901, PropagatesArbitraryException_901) {
    EXPECT_THROW(
        Catch::Benchmark::user_code([]() -> int { throw 42; }),
        int
    );
}

// Test that user_code works with a function object (functor)
TEST_F(UserCodeTest_901, WorksWithFunctor_901) {
    struct MyFunctor {
        int operator()() const { return 99; }
    };
    MyFunctor f;
    auto result = Catch::Benchmark::user_code(f);
    EXPECT_EQ(result, 99);
}

// Test that user_code works with std::function
TEST_F(UserCodeTest_901, WorksWithStdFunction_901) {
    std::function<int()> fn = []() { return 77; };
    auto result = Catch::Benchmark::user_code(fn);
    EXPECT_EQ(result, 77);
}

// Test that user_code actually invokes the callable (side effect verification)
TEST_F(UserCodeTest_901, InvokesCallable_901) {
    bool invoked = false;
    Catch::Benchmark::user_code([&invoked]() { invoked = true; });
    EXPECT_TRUE(invoked);
}

// Test that user_code works with a lambda capturing values
TEST_F(UserCodeTest_901, WorksWithCapturingLambda_901) {
    int x = 10;
    int y = 20;
    auto result = Catch::Benchmark::user_code([&]() -> int { return x + y; });
    EXPECT_EQ(result, 30);
}

// Test that user_code works with mutable lambda
TEST_F(UserCodeTest_901, WorksWithMutableLambda_901) {
    int counter = 0;
    auto result = Catch::Benchmark::user_code([counter]() mutable -> int {
        counter++;
        return counter;
    });
    EXPECT_EQ(result, 1);
}

// Test that user_code returns a complex type
TEST_F(UserCodeTest_901, ReturnsComplexType_901) {
    auto result = Catch::Benchmark::user_code([]() -> std::pair<int, std::string> {
        return {42, "test"};
    });
    EXPECT_EQ(result.first, 42);
    EXPECT_EQ(result.second, "test");
}

// Test user_code with a lambda returning an empty string (boundary)
TEST_F(UserCodeTest_901, ReturnsEmptyString_901) {
    auto result = Catch::Benchmark::user_code([]() -> std::string { return ""; });
    EXPECT_EQ(result, "");
}
