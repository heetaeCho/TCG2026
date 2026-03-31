#include <gtest/gtest.h>
#include <string>
#include <functional>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// =============================================================================
// Test fixture
// =============================================================================
class InvokeTest_380 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Normal operation tests
// =============================================================================

// Test that invoke with a void-returning lambda returns ok with Matched
TEST_F(InvokeTest_380, VoidLambdaReturnsOkMatched_380) {
    bool called = false;
    auto lambda = [&called](std::string const& arg) {
        called = true;
    };
    
    std::string arg = "test";
    auto result = invoke(lambda, arg);
    
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultBase::Ok);
    EXPECT_TRUE(called);
}

// Test that the argument is correctly passed to the lambda
TEST_F(InvokeTest_380, ArgumentPassedCorrectly_380) {
    std::string receivedArg;
    auto lambda = [&receivedArg](std::string const& arg) {
        receivedArg = arg;
    };
    
    std::string arg = "hello_world";
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedArg, "hello_world");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with integer argument type
TEST_F(InvokeTest_380, IntegerArgument_380) {
    int receivedValue = 0;
    auto lambda = [&receivedValue](int const& arg) {
        receivedValue = arg;
    };
    
    int arg = 42;
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedValue, 42);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with empty string argument
TEST_F(InvokeTest_380, EmptyStringArgument_380) {
    std::string receivedArg = "non-empty";
    auto lambda = [&receivedArg](std::string const& arg) {
        receivedArg = arg;
    };
    
    std::string arg = "";
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedArg, "");
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that result type is Matched (ParseResultType::Matched)
TEST_F(InvokeTest_380, ResultIsMatched_380) {
    auto lambda = [](std::string const&) {};
    
    std::string arg = "test";
    auto result = invoke(lambda, arg);
    
    // The result should be ok, which means it's truthy
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test invoke with a lambda that modifies external state
TEST_F(InvokeTest_380, LambdaModifiesExternalState_380) {
    int counter = 0;
    auto lambda = [&counter](int const& arg) {
        counter += arg;
    };
    
    int arg = 5;
    invoke(lambda, arg);
    EXPECT_EQ(counter, 5);
    
    invoke(lambda, arg);
    EXPECT_EQ(counter, 10);
}

// Test with double argument type
TEST_F(InvokeTest_380, DoubleArgument_380) {
    double receivedValue = 0.0;
    auto lambda = [&receivedValue](double const& arg) {
        receivedValue = arg;
    };
    
    double arg = 3.14;
    auto result = invoke(lambda, arg);
    
    EXPECT_DOUBLE_EQ(receivedValue, 3.14);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with bool argument type
TEST_F(InvokeTest_380, BoolArgument_380) {
    bool receivedValue = false;
    auto lambda = [&receivedValue](bool const& arg) {
        receivedValue = arg;
    };
    
    bool arg = true;
    auto result = invoke(lambda, arg);
    
    EXPECT_TRUE(receivedValue);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that invoke can be called multiple times with same lambda
TEST_F(InvokeTest_380, MultipleInvocations_380) {
    std::vector<std::string> received;
    auto lambda = [&received](std::string const& arg) {
        received.push_back(arg);
    };
    
    invoke(lambda, std::string("first"));
    invoke(lambda, std::string("second"));
    invoke(lambda, std::string("third"));
    
    ASSERT_EQ(received.size(), 3u);
    EXPECT_EQ(received[0], "first");
    EXPECT_EQ(received[1], "second");
    EXPECT_EQ(received[2], "third");
}

// Test with a no-op lambda (does nothing)
TEST_F(InvokeTest_380, NoOpLambda_380) {
    auto lambda = [](std::string const&) {
        // intentionally empty
    };
    
    std::string arg = "test";
    auto result = invoke(lambda, arg);
    
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that error message is empty for ok result
TEST_F(InvokeTest_380, OkResultHasEmptyErrorMessage_380) {
    auto lambda = [](std::string const&) {};
    
    std::string arg = "test";
    auto result = invoke(lambda, arg);
    
    EXPECT_TRUE(result.errorMessage().empty());
}

// =============================================================================
// Boundary condition tests
// =============================================================================

// Test with very long string argument
TEST_F(InvokeTest_380, VeryLongStringArgument_380) {
    std::string receivedArg;
    auto lambda = [&receivedArg](std::string const& arg) {
        receivedArg = arg;
    };
    
    std::string arg(10000, 'x');
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedArg.size(), 10000u);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with zero integer argument
TEST_F(InvokeTest_380, ZeroIntegerArgument_380) {
    int receivedValue = -1;
    auto lambda = [&receivedValue](int const& arg) {
        receivedValue = arg;
    };
    
    int arg = 0;
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedValue, 0);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with negative integer argument
TEST_F(InvokeTest_380, NegativeIntegerArgument_380) {
    int receivedValue = 0;
    auto lambda = [&receivedValue](int const& arg) {
        receivedValue = arg;
    };
    
    int arg = -999;
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(receivedValue, -999);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with a struct as argument type
TEST_F(InvokeTest_380, CustomStructArgument_380) {
    struct MyStruct {
        int x;
        std::string name;
    };
    
    MyStruct received{0, ""};
    auto lambda = [&received](MyStruct const& arg) {
        received = arg;
    };
    
    MyStruct arg{42, "hello"};
    auto result = invoke(lambda, arg);
    
    EXPECT_EQ(received.x, 42);
    EXPECT_EQ(received.name, "hello");
    EXPECT_TRUE(static_cast<bool>(result));
}
