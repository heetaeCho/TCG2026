#include "catch_amalgamated.hpp"
#include <gtest/gtest.h>

// Global tracking variables for test functions
static bool g_functionCalled = false;
static int g_callCount = 0;

static void testFunction() {
    g_functionCalled = true;
    g_callCount++;
}

static void anotherTestFunction() {
    g_callCount += 10;
}

static void noopFunction() {
    // Does nothing
}

class MakeTestInvokerTest_1043 : public ::testing::Test {
protected:
    void SetUp() override {
        g_functionCalled = false;
        g_callCount = 0;
    }
};

// Test that makeTestInvoker returns a non-null unique_ptr
TEST_F(MakeTestInvokerTest_1043, ReturnsNonNullPointer_1043) {
    auto invoker = Catch::makeTestInvoker(testFunction);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test that invoking the invoker calls the wrapped function
TEST_F(MakeTestInvokerTest_1043, InvokeCallsWrappedFunction_1043) {
    auto invoker = Catch::makeTestInvoker(testFunction);
    ASSERT_NE(invoker.get(), nullptr);
    
    EXPECT_FALSE(g_functionCalled);
    invoker->invoke();
    EXPECT_TRUE(g_functionCalled);
}

// Test that invoking increments the call count correctly
TEST_F(MakeTestInvokerTest_1043, InvokeCallsFunctionExactlyOnce_1043) {
    auto invoker = Catch::makeTestInvoker(testFunction);
    ASSERT_NE(invoker.get(), nullptr);
    
    EXPECT_EQ(g_callCount, 0);
    invoker->invoke();
    EXPECT_EQ(g_callCount, 1);
}

// Test that multiple invocations call the function multiple times
TEST_F(MakeTestInvokerTest_1043, MultipleInvocationsCallFunctionMultipleTimes_1043) {
    auto invoker = Catch::makeTestInvoker(testFunction);
    ASSERT_NE(invoker.get(), nullptr);
    
    invoker->invoke();
    invoker->invoke();
    invoker->invoke();
    EXPECT_EQ(g_callCount, 3);
}

// Test that different function pointers create independent invokers
TEST_F(MakeTestInvokerTest_1043, DifferentFunctionsCreateIndependentInvokers_1043) {
    auto invoker1 = Catch::makeTestInvoker(testFunction);
    auto invoker2 = Catch::makeTestInvoker(anotherTestFunction);
    
    ASSERT_NE(invoker1.get(), nullptr);
    ASSERT_NE(invoker2.get(), nullptr);
    
    invoker1->invoke();
    EXPECT_EQ(g_callCount, 1);
    
    invoker2->invoke();
    EXPECT_EQ(g_callCount, 11);
}

// Test with a no-op function
TEST_F(MakeTestInvokerTest_1043, NoopFunctionDoesNotAffectState_1043) {
    auto invoker = Catch::makeTestInvoker(noopFunction);
    ASSERT_NE(invoker.get(), nullptr);
    
    invoker->invoke();
    EXPECT_FALSE(g_functionCalled);
    EXPECT_EQ(g_callCount, 0);
}

// Test that two invokers wrapping the same function are independent objects
TEST_F(MakeTestInvokerTest_1043, TwoInvokersForSameFunctionAreIndependent_1043) {
    auto invoker1 = Catch::makeTestInvoker(testFunction);
    auto invoker2 = Catch::makeTestInvoker(testFunction);
    
    ASSERT_NE(invoker1.get(), nullptr);
    ASSERT_NE(invoker2.get(), nullptr);
    EXPECT_NE(invoker1.get(), invoker2.get());
    
    invoker1->invoke();
    EXPECT_EQ(g_callCount, 1);
    
    invoker2->invoke();
    EXPECT_EQ(g_callCount, 2);
}

// Test with a lambda-compatible function (static function via lambda)
static void lambdaLikeFunction() {
    g_callCount += 100;
}

TEST_F(MakeTestInvokerTest_1043, WorksWithStaticFunction_1043) {
    auto invoker = Catch::makeTestInvoker(lambdaLikeFunction);
    ASSERT_NE(invoker.get(), nullptr);
    
    invoker->invoke();
    EXPECT_EQ(g_callCount, 100);
}
