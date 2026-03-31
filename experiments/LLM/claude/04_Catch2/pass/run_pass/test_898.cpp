#include <gtest/gtest.h>
#include <string>
#include <functional>

// Minimal reproduction of the necessary macros and types from Catch2
#ifndef CATCH_FORWARD
#define CATCH_FORWARD(x) static_cast<decltype(x)&&>(x)
#endif

namespace Catch {
namespace Benchmark {
namespace Detail {

template <typename Result>
struct CompleteInvoker {
public:
    template <typename Fun, typename... Args>
    static Result invoke(Fun&& fun, Args&&... args) {
        return CATCH_FORWARD(fun)(CATCH_FORWARD(args)...);
    }
};

} // namespace Detail
} // namespace Benchmark
} // namespace Catch

// ============================================================
// Test Fixtures and Tests
// ============================================================

class CompleteInvokerTest_898 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: invoking a simple function that returns an int
TEST_F(CompleteInvokerTest_898, InvokeReturnsIntFromLambda_898) {
    auto func = []() -> int { return 42; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func);
    EXPECT_EQ(result, 42);
}

// Test: invoking a function with arguments that returns an int
TEST_F(CompleteInvokerTest_898, InvokeWithArgumentsReturnsSum_898) {
    auto func = [](int a, int b) -> int { return a + b; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, 10, 20);
    EXPECT_EQ(result, 30);
}

// Test: invoking a function that returns a string
TEST_F(CompleteInvokerTest_898, InvokeReturnsString_898) {
    auto func = [](const std::string& prefix, int num) -> std::string {
        return prefix + std::to_string(num);
    };
    std::string result = Catch::Benchmark::Detail::CompleteInvoker<std::string>::invoke(func, std::string("val_"), 5);
    EXPECT_EQ(result, "val_5");
}

// Test: invoking a function that returns a double
TEST_F(CompleteInvokerTest_898, InvokeReturnsDouble_898) {
    auto func = [](double a, double b) -> double { return a * b; };
    double result = Catch::Benchmark::Detail::CompleteInvoker<double>::invoke(func, 3.0, 4.5);
    EXPECT_DOUBLE_EQ(result, 13.5);
}

// Test: invoking a function that returns a bool (true case)
TEST_F(CompleteInvokerTest_898, InvokeReturnsBoolTrue_898) {
    auto func = [](int x) -> bool { return x > 0; };
    bool result = Catch::Benchmark::Detail::CompleteInvoker<bool>::invoke(func, 5);
    EXPECT_TRUE(result);
}

// Test: invoking a function that returns a bool (false case)
TEST_F(CompleteInvokerTest_898, InvokeReturnsBoolFalse_898) {
    auto func = [](int x) -> bool { return x > 0; };
    bool result = Catch::Benchmark::Detail::CompleteInvoker<bool>::invoke(func, -1);
    EXPECT_FALSE(result);
}

// Test: invoking with a std::function wrapper
TEST_F(CompleteInvokerTest_898, InvokeWithStdFunction_898) {
    std::function<int(int, int)> func = [](int a, int b) -> int { return a - b; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, 100, 30);
    EXPECT_EQ(result, 70);
}

// Test: invoking a function with no arguments
TEST_F(CompleteInvokerTest_898, InvokeNoArgs_898) {
    auto func = []() -> std::string { return "hello"; };
    std::string result = Catch::Benchmark::Detail::CompleteInvoker<std::string>::invoke(func);
    EXPECT_EQ(result, "hello");
}

// Test: invoking a function that throws an exception
TEST_F(CompleteInvokerTest_898, InvokeThrowsException_898) {
    auto func = []() -> int { throw std::runtime_error("test error"); };
    EXPECT_THROW(
        Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func),
        std::runtime_error
    );
}

// Test: invoking with rvalue arguments (move semantics)
TEST_F(CompleteInvokerTest_898, InvokeWithRvalueArguments_898) {
    auto func = [](std::string s) -> std::string { return s + " world"; };
    std::string result = Catch::Benchmark::Detail::CompleteInvoker<std::string>::invoke(func, std::string("hello"));
    EXPECT_EQ(result, "hello world");
}

// Test: invoking a function pointer
TEST_F(CompleteInvokerTest_898, InvokeWithFunctionPointer_898) {
    struct Helper {
        static int add(int a, int b) { return a + b; }
    };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(&Helper::add, 7, 8);
    EXPECT_EQ(result, 15);
}

// Test: invoking a functor object
TEST_F(CompleteInvokerTest_898, InvokeWithFunctorObject_898) {
    struct Multiplier {
        int factor;
        int operator()(int x) const { return x * factor; }
    };
    Multiplier m{3};
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(m, 7);
    EXPECT_EQ(result, 21);
}

// Test: invoking with multiple arguments of different types
TEST_F(CompleteInvokerTest_898, InvokeWithMixedArgTypes_898) {
    auto func = [](int a, double b, const std::string& c) -> std::string {
        return std::to_string(a) + "_" + std::to_string(static_cast<int>(b)) + "_" + c;
    };
    std::string result = Catch::Benchmark::Detail::CompleteInvoker<std::string>::invoke(func, 1, 2.0, std::string("three"));
    EXPECT_EQ(result, "1_2_three");
}

// Test: boundary - invoking with zero values
TEST_F(CompleteInvokerTest_898, InvokeWithZeroValues_898) {
    auto func = [](int a) -> int { return a; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, 0);
    EXPECT_EQ(result, 0);
}

// Test: boundary - invoking with max int
TEST_F(CompleteInvokerTest_898, InvokeWithMaxInt_898) {
    auto func = [](int a) -> int { return a; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, std::numeric_limits<int>::max());
    EXPECT_EQ(result, std::numeric_limits<int>::max());
}

// Test: boundary - invoking with min int
TEST_F(CompleteInvokerTest_898, InvokeWithMinInt_898) {
    auto func = [](int a) -> int { return a; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, std::numeric_limits<int>::min());
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

// Test: invoking a stateful lambda that captures by value
TEST_F(CompleteInvokerTest_898, InvokeStatefulLambdaCaptureByValue_898) {
    int captured = 10;
    auto func = [captured](int x) -> int { return x + captured; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func, 5);
    EXPECT_EQ(result, 15);
}

// Test: invoking a stateful lambda that captures by reference
TEST_F(CompleteInvokerTest_898, InvokeStatefulLambdaCaptureByRef_898) {
    int counter = 0;
    auto func = [&counter]() -> int { counter++; return counter; };
    int result = Catch::Benchmark::Detail::CompleteInvoker<int>::invoke(func);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(counter, 1);
}

// Test: invoking returns a unique_ptr (move-only type)
TEST_F(CompleteInvokerTest_898, InvokeReturnsMoveOnlyType_898) {
    auto func = [](int val) -> std::unique_ptr<int> {
        return std::make_unique<int>(val);
    };
    auto result = Catch::Benchmark::Detail::CompleteInvoker<std::unique_ptr<int>>::invoke(func, 99);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 99);
}

// Test: invoking with empty string argument
TEST_F(CompleteInvokerTest_898, InvokeWithEmptyString_898) {
    auto func = [](const std::string& s) -> size_t { return s.size(); };
    size_t result = Catch::Benchmark::Detail::CompleteInvoker<size_t>::invoke(func, std::string(""));
    EXPECT_EQ(result, 0u);
}
