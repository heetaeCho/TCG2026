#include <catch2/catch_all.hpp>
// If using the amalgamated header:
#include "catch_amalgamated.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <functional>
#include <stdexcept>

using namespace Catch::Benchmark::Detail;

// Test fixture
class CompleteInvokeTest_900 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Invoking a lambda that returns an int
TEST_F(CompleteInvokeTest_900, InvokeLambdaReturningInt_900) {
    auto result = complete_invoke([]() { return 42; });
    EXPECT_EQ(result, 42);
}

// Test: Invoking a lambda with arguments
TEST_F(CompleteInvokeTest_900, InvokeLambdaWithArguments_900) {
    auto result = complete_invoke([](int a, int b) { return a + b; }, 3, 4);
    EXPECT_EQ(result, 7);
}

// Test: Invoking a lambda that returns a string
TEST_F(CompleteInvokeTest_900, InvokeLambdaReturningString_900) {
    auto result = complete_invoke([]() { return std::string("hello"); });
    EXPECT_EQ(result, "hello");
}

// Test: Invoking a lambda with string arguments
TEST_F(CompleteInvokeTest_900, InvokeLambdaWithStringArgs_900) {
    auto result = complete_invoke([](const std::string& a, const std::string& b) {
        return a + b;
    }, std::string("hello"), std::string(" world"));
    EXPECT_EQ(result, "hello world");
}

// Test: Invoking a lambda that returns a double
TEST_F(CompleteInvokeTest_900, InvokeLambdaReturningDouble_900) {
    auto result = complete_invoke([]() { return 3.14; });
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test: Invoking a lambda that returns a bool
TEST_F(CompleteInvokeTest_900, InvokeLambdaReturningBool_900) {
    auto result = complete_invoke([]() { return true; });
    EXPECT_TRUE(result);
}

// Test: Invoking a function pointer
TEST_F(CompleteInvokeTest_900, InvokeFunctionPointer_900) {
    int (*func)(int, int) = [](int a, int b) -> int { return a * b; };
    auto result = complete_invoke(func, 5, 6);
    EXPECT_EQ(result, 30);
}

// Test: Invoking a std::function
TEST_F(CompleteInvokeTest_900, InvokeStdFunction_900) {
    std::function<int(int)> func = [](int x) { return x * x; };
    auto result = complete_invoke(func, 7);
    EXPECT_EQ(result, 49);
}

// Test: Invoking a void lambda (should compile and work with CompleteType_t)
TEST_F(CompleteInvokeTest_900, InvokeVoidLambda_900) {
    int side_effect = 0;
    auto result = complete_invoke([&side_effect]() { side_effect = 42; });
    EXPECT_EQ(side_effect, 42);
    // result type should be Catch::Benchmark::Detail::ChronometerModel or similar CompleteType
    // The key test is that it compiles and the side effect occurs
    (void)result;
}

// Test: Invoking a mutable lambda
TEST_F(CompleteInvokeTest_900, InvokeMutableLambda_900) {
    int counter = 0;
    auto lambda = [counter]() mutable { return ++counter; };
    auto result = complete_invoke(lambda);
    EXPECT_EQ(result, 1);
}

// Test: Invoking with move-only arguments
TEST_F(CompleteInvokeTest_900, InvokeWithRvalueArguments_900) {
    auto result = complete_invoke([](std::unique_ptr<int> p) { return *p; },
                                   std::make_unique<int>(99));
    EXPECT_EQ(result, 99);
}

// Test: Boundary - invoking with zero arguments returning zero
TEST_F(CompleteInvokeTest_900, InvokeReturningZero_900) {
    auto result = complete_invoke([]() { return 0; });
    EXPECT_EQ(result, 0);
}

// Test: Invoking with negative return value
TEST_F(CompleteInvokeTest_900, InvokeReturningNegative_900) {
    auto result = complete_invoke([]() { return -1; });
    EXPECT_EQ(result, -1);
}
