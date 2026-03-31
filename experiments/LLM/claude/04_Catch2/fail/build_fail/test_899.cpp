#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// Test helpers
static int g_callCount = 0;
static int g_lastValue = 0;

void resetGlobals() {
    g_callCount = 0;
    g_lastValue = 0;
}

void voidNoArgs() {
    g_callCount++;
}

void voidOneArg(int x) {
    g_callCount++;
    g_lastValue = x;
}

void voidTwoArgs(int x, int y) {
    g_callCount++;
    g_lastValue = x + y;
}

int intNoArgs() {
    g_callCount++;
    return 42;
}

int intOneArg(int x) {
    g_callCount++;
    return x * 2;
}

class InvokeTest_899 : public ::testing::Test {
protected:
    void SetUp() override {
        resetGlobals();
    }
};

// Test: invoke with a void function taking no arguments
TEST_F(InvokeTest_899, VoidFunctionNoArgs_899) {
    auto result = Catch::Benchmark::Detail::invoke(voidNoArgs);
    (void)result; // CompleteType_t<void> should be returned
    EXPECT_EQ(g_callCount, 1);
}

// Test: invoke with a void function taking one argument
TEST_F(InvokeTest_899, VoidFunctionOneArg_899) {
    Catch::Benchmark::Detail::invoke(voidOneArg, 7);
    EXPECT_EQ(g_callCount, 1);
    EXPECT_EQ(g_lastValue, 7);
}

// Test: invoke with a void function taking two arguments
TEST_F(InvokeTest_899, VoidFunctionTwoArgs_899) {
    Catch::Benchmark::Detail::invoke(voidTwoArgs, 3, 5);
    EXPECT_EQ(g_callCount, 1);
    EXPECT_EQ(g_lastValue, 8);
}

// Test: invoke with a void lambda taking no arguments
TEST_F(InvokeTest_899, VoidLambdaNoArgs_899) {
    bool called = false;
    Catch::Benchmark::Detail::invoke([&called]() { called = true; });
    EXPECT_TRUE(called);
}

// Test: invoke with a void lambda taking one argument
TEST_F(InvokeTest_899, VoidLambdaOneArg_899) {
    int captured = 0;
    Catch::Benchmark::Detail::invoke([&captured](int x) { captured = x; }, 42);
    EXPECT_EQ(captured, 42);
}

// Test: invoke with a void lambda taking multiple arguments
TEST_F(InvokeTest_899, VoidLambdaMultipleArgs_899) {
    int sum = 0;
    Catch::Benchmark::Detail::invoke([&sum](int a, int b, int c) { sum = a + b + c; }, 1, 2, 3);
    EXPECT_EQ(sum, 6);
}

// Test: invoke with a mutable lambda
TEST_F(InvokeTest_899, VoidMutableLambda_899) {
    int counter = 0;
    auto lambda = [&counter]() mutable { counter++; };
    Catch::Benchmark::Detail::invoke(lambda);
    EXPECT_EQ(counter, 1);
}

// Test: invoke called multiple times
TEST_F(InvokeTest_899, MultipleInvocations_899) {
    int counter = 0;
    auto lambda = [&counter]() { counter++; };
    Catch::Benchmark::Detail::invoke(lambda);
    Catch::Benchmark::Detail::invoke(lambda);
    Catch::Benchmark::Detail::invoke(lambda);
    EXPECT_EQ(counter, 3);
}

// Test: invoke with a function that has side effects on references
TEST_F(InvokeTest_899, SideEffectsOnReferences_899) {
    int value = 10;
    Catch::Benchmark::Detail::invoke([](int& v) { v = 20; }, std::ref(value));
    EXPECT_EQ(value, 20);
}

// Test: invoke returns CompleteType_t<void> (should be default constructible)
TEST_F(InvokeTest_899, ReturnTypeIsComplete_899) {
    auto result = Catch::Benchmark::Detail::invoke([]() {});
    // The result should be a CompleteType_t<void> which is a complete type
    // We just verify it compiles and is usable
    (void)result;
    SUCCEED();
}

// Test: invoke with a std::function
TEST_F(InvokeTest_899, StdFunction_899) {
    bool invoked = false;
    std::function<void()> fn = [&invoked]() { invoked = true; };
    Catch::Benchmark::Detail::invoke(fn);
    EXPECT_TRUE(invoked);
}

// Test: invoke with functor object
TEST_F(InvokeTest_899, FunctorObject_899) {
    struct Functor {
        int* target;
        void operator()(int val) const { *target = val; }
    };
    int result = 0;
    Functor f{&result};
    Catch::Benchmark::Detail::invoke(f, 99);
    EXPECT_EQ(result, 99);
}

// Test: invoke with rvalue lambda
TEST_F(InvokeTest_899, RvalueLambda_899) {
    int captured = 0;
    Catch::Benchmark::Detail::invoke([&captured](int x) { captured = x; }, 55);
    EXPECT_EQ(captured, 55);
}

// Test: invoke with zero as argument (boundary)
TEST_F(InvokeTest_899, BoundaryZeroArg_899) {
    Catch::Benchmark::Detail::invoke(voidOneArg, 0);
    EXPECT_EQ(g_callCount, 1);
    EXPECT_EQ(g_lastValue, 0);
}

// Test: invoke with negative arguments (boundary)
TEST_F(InvokeTest_899, BoundaryNegativeArgs_899) {
    Catch::Benchmark::Detail::invoke(voidTwoArgs, -5, -10);
    EXPECT_EQ(g_callCount, 1);
    EXPECT_EQ(g_lastValue, -15);
}

// Test: invoke with large arguments (boundary)
TEST_F(InvokeTest_899, BoundaryLargeArgs_899) {
    int result = 0;
    Catch::Benchmark::Detail::invoke([&result](int x) { result = x; }, INT_MAX);
    EXPECT_EQ(result, INT_MAX);
}

// Test: invoke with string arguments
TEST_F(InvokeTest_899, StringArguments_899) {
    std::string captured;
    Catch::Benchmark::Detail::invoke([&captured](const std::string& s) { captured = s; }, std::string("hello"));
    EXPECT_EQ(captured, "hello");
}

// Test: invoke with move-only type argument
TEST_F(InvokeTest_899, MoveOnlyArgument_899) {
    std::unique_ptr<int> ptr;
    Catch::Benchmark::Detail::invoke([&ptr](std::unique_ptr<int> p) { ptr = std::move(p); }, std::make_unique<int>(123));
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 123);
}

// Test: invoke with exception-throwing function
TEST_F(InvokeTest_899, ThrowingFunction_899) {
    EXPECT_THROW(
        Catch::Benchmark::Detail::invoke([]() { throw std::runtime_error("test error"); }),
        std::runtime_error
    );
}

// Test: invoke ensures function is actually called (not just compiled)
TEST_F(InvokeTest_899, EnsureFunctionExecution_899) {
    std::vector<int> values;
    Catch::Benchmark::Detail::invoke([&values](int a, int b) {
        values.push_back(a);
        values.push_back(b);
    }, 10, 20);
    ASSERT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
}
