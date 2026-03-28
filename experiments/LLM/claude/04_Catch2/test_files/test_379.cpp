#include <gtest/gtest.h>
#include <string>
#include <functional>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Helper: We need to understand ParserResult to write meaningful tests.
// Based on Clara's typical interface, ParserResult can be constructed from
// result types. We'll use lambdas that return ParserResult.

class LambdaInvokerTest_379 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that invoke calls the lambda with the given string argument and returns its result
TEST_F(LambdaInvokerTest_379, InvokeWithStringArg_ReturnsLambdaResult_379) {
    bool lambdaCalled = false;
    std::string capturedArg;
    
    auto lambda = [&](const std::string& arg) -> ParserResult {
        lambdaCalled = true;
        capturedArg = arg;
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    auto result = LambdaInvoker::invoke(lambda, std::string("test_value"));
    
    EXPECT_TRUE(lambdaCalled);
    EXPECT_EQ(capturedArg, "test_value");
}

// Test invoke with an empty string argument
TEST_F(LambdaInvokerTest_379, InvokeWithEmptyString_379) {
    std::string capturedArg = "non-empty";
    
    auto lambda = [&](const std::string& arg) -> ParserResult {
        capturedArg = arg;
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    LambdaInvoker::invoke(lambda, std::string(""));
    
    EXPECT_EQ(capturedArg, "");
}

// Test invoke with a lambda that returns an error result
TEST_F(LambdaInvokerTest_379, InvokeWithErrorReturningLambda_379) {
    auto lambda = [](const std::string& arg) -> ParserResult {
        return ParserResult::runtimeError("some error");
    };
    
    auto result = LambdaInvoker::invoke(lambda, std::string("anything"));
    // The result should indicate an error; we verify it's not in an ok/matched state
    // by checking the type via the public interface
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test invoke with a lambda that returns ok/matched
TEST_F(LambdaInvokerTest_379, InvokeWithOkReturningLambda_379) {
    auto lambda = [](const std::string& arg) -> ParserResult {
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    auto result = LambdaInvoker::invoke(lambda, std::string("value"));
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test invoke with a lambda that returns no match
TEST_F(LambdaInvokerTest_379, InvokeWithNoMatchReturningLambda_379) {
    auto lambda = [](const std::string& arg) -> ParserResult {
        return ParserResult::ok( ParseResultType::NoMatch );
    };
    
    auto result = LambdaInvoker::invoke(lambda, std::string("value"));
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that the argument is passed correctly with special characters
TEST_F(LambdaInvokerTest_379, InvokeWithSpecialCharacters_379) {
    std::string capturedArg;
    
    auto lambda = [&](const std::string& arg) -> ParserResult {
        capturedArg = arg;
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    std::string specialStr = "hello\nworld\t!@#$%^&*()";
    LambdaInvoker::invoke(lambda, specialStr);
    
    EXPECT_EQ(capturedArg, specialStr);
}

// Test that invoke works with a very long string argument
TEST_F(LambdaInvokerTest_379, InvokeWithLongString_379) {
    std::string capturedArg;
    
    auto lambda = [&](const std::string& arg) -> ParserResult {
        capturedArg = arg;
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    std::string longStr(10000, 'x');
    LambdaInvoker::invoke(lambda, longStr);
    
    EXPECT_EQ(capturedArg, longStr);
    EXPECT_EQ(capturedArg.size(), 10000u);
}

// Test invoke with const reference lambda (stateless)
TEST_F(LambdaInvokerTest_379, InvokeWithStatelessLambda_379) {
    auto lambda = [](const std::string& arg) -> ParserResult {
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    const auto& constLambda = lambda;
    auto result = LambdaInvoker::invoke(constLambda, std::string("test"));
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that invoke correctly forwards the argument to the lambda multiple times
TEST_F(LambdaInvokerTest_379, InvokeMultipleTimes_379) {
    int callCount = 0;
    
    auto lambda = [&](const std::string& arg) -> ParserResult {
        callCount++;
        return ParserResult::ok( ParseResultType::Matched );
    };
    
    LambdaInvoker::invoke(lambda, std::string("first"));
    LambdaInvoker::invoke(lambda, std::string("second"));
    LambdaInvoker::invoke(lambda, std::string("third"));
    
    EXPECT_EQ(callCount, 3);
}
