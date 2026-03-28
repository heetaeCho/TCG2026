#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <functional>
#include <memory>

using namespace Catch::Benchmark;

class InvokeDeoptimizedTest_887 : public ::testing::Test {
protected:
};

// Test that invoke_deoptimized calls a function returning int with no args
TEST_F(InvokeDeoptimizedTest_887, CallsNoArgFunctionReturningInt_887) {
    bool called = false;
    auto fn = [&called]() -> int {
        called = true;
        return 42;
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized calls a function returning double with no args
TEST_F(InvokeDeoptimizedTest_887, CallsNoArgFunctionReturningDouble_887) {
    bool called = false;
    auto fn = [&called]() -> double {
        called = true;
        return 3.14;
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized forwards a single argument correctly
TEST_F(InvokeDeoptimizedTest_887, ForwardsSingleArgument_887) {
    int received = 0;
    auto fn = [&received](int x) -> int {
        received = x;
        return x * 2;
    };
    invoke_deoptimized(fn, 21);
    EXPECT_EQ(received, 21);
}

// Test that invoke_deoptimized forwards multiple arguments correctly
TEST_F(InvokeDeoptimizedTest_887, ForwardsMultipleArguments_887) {
    int a_received = 0;
    int b_received = 0;
    auto fn = [&a_received, &b_received](int a, int b) -> int {
        a_received = a;
        b_received = b;
        return a + b;
    };
    invoke_deoptimized(fn, 10, 20);
    EXPECT_EQ(a_received, 10);
    EXPECT_EQ(b_received, 20);
}

// Test that invoke_deoptimized works with a function returning a string
TEST_F(InvokeDeoptimizedTest_887, WorksWithStringReturn_887) {
    bool called = false;
    auto fn = [&called]() -> std::string {
        called = true;
        return "hello";
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized works with a function returning a pointer
TEST_F(InvokeDeoptimizedTest_887, WorksWithPointerReturn_887) {
    int value = 99;
    bool called = false;
    auto fn = [&called, &value]() -> int* {
        called = true;
        return &value;
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized works with move-only argument types
TEST_F(InvokeDeoptimizedTest_887, WorksWithMoveOnlyArgs_887) {
    bool called = false;
    auto fn = [&called](std::unique_ptr<int> p) -> int {
        called = true;
        return *p;
    };
    invoke_deoptimized(fn, std::make_unique<int>(42));
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized works with a plain function pointer
TEST_F(InvokeDeoptimizedTest_887, WorksWithFunctionPointer_887) {
    auto fn = [](int x) -> int { return x + 1; };
    // Should not throw or cause issues
    EXPECT_NO_THROW(invoke_deoptimized(fn, 5));
}

// Test that invoke_deoptimized works with returning bool
TEST_F(InvokeDeoptimizedTest_887, WorksWithBoolReturn_887) {
    bool called = false;
    auto fn = [&called]() -> bool {
        called = true;
        return true;
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized works with returning char
TEST_F(InvokeDeoptimizedTest_887, WorksWithCharReturn_887) {
    bool called = false;
    auto fn = [&called]() -> char {
        called = true;
        return 'A';
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized works with std::function
TEST_F(InvokeDeoptimizedTest_887, WorksWithStdFunction_887) {
    bool called = false;
    std::function<int()> fn = [&called]() -> int {
        called = true;
        return 100;
    };
    invoke_deoptimized(fn);
    EXPECT_TRUE(called);
}

// Test that invoke_deoptimized with reference arguments modifies the original
TEST_F(InvokeDeoptimizedTest_887, WorksWithReferenceArgs_887) {
    int value = 0;
    auto fn = [](int& v) -> int {
        v = 42;
        return v;
    };
    invoke_deoptimized(fn, std::ref(value));
    EXPECT_EQ(value, 42);
}
