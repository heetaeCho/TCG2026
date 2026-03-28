// File: tests/make_test_invoker_tests_1043.cpp

#include <gtest/gtest.h>
#include <stdexcept>

// Include the Catch2 amalgamated header so we can access Catch::makeTestInvoker
// and the public interface Catch::ITestInvoker.
#include "catch_amalgamated.hpp"

class MakeTestInvokerTest_1043 : public ::testing::Test {
protected:
    void SetUp() override {
        counter1 = 0;
        counter2 = 0;
    }

    // Observable side effects for verification
    static int counter1;
    static int counter2;

    // Free functions that match the required signature: void()
    static void FuncInc1() { ++counter1; }
    static void FuncInc2() { ++counter2; }
    static void Thrower() { throw std::runtime_error("boom-1043"); }
};

int MakeTestInvokerTest_1043::counter1 = 0;
int MakeTestInvokerTest_1043::counter2 = 0;

// --- Tests ---

// Basic construction: returned invoker is non-null and can be invoked once.
TEST_F(MakeTestInvokerTest_1043, ReturnsNonNullAndInvokesOnce_1043) {
    auto inv = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc1);
    ASSERT_TRUE(static_cast<bool>(inv));           // non-null unique_ptr
    EXPECT_EQ(counter1, 0);
    inv->invoke();                                  // observable side effect
    EXPECT_EQ(counter1, 1);
}

// Invoking twice should call the wrapped function twice (observable via counter).
TEST_F(MakeTestInvokerTest_1043, InvokeTwiceCallsFunctionTwice_1043) {
    auto inv = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc1);
    EXPECT_EQ(counter1, 0);
    inv->invoke();
    inv->invoke();
    EXPECT_EQ(counter1, 2);
}

// Moving the unique_ptr keeps the invoker usable (observable effect still occurs).
TEST_F(MakeTestInvokerTest_1043, MoveUniquePtrKeepsInvokerUsable_1043) {
    auto inv = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc1);
    std::unique_ptr<Catch::ITestInvoker> moved = std::move(inv);
    ASSERT_FALSE(inv);                              // moved-from should be empty
    ASSERT_TRUE(static_cast<bool>(moved));          // target should hold the invoker
    moved->invoke();
    EXPECT_EQ(counter1, 1);
}

// Distinct invokers should call only their respective wrapped functions.
TEST_F(MakeTestInvokerTest_1043, DistinctInvokersAffectOnlyTheirTargets_1043) {
    auto inv1 = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc1);
    auto inv2 = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc2);

    EXPECT_EQ(counter1, 0);
    EXPECT_EQ(counter2, 0);

    inv1->invoke();
    EXPECT_EQ(counter1, 1);
    EXPECT_EQ(counter2, 0);

    inv2->invoke();
    EXPECT_EQ(counter1, 1);
    EXPECT_EQ(counter2, 1);
}

// Exceptions thrown by the wrapped function should propagate (no swallowing).
TEST_F(MakeTestInvokerTest_1043, ExceptionFromWrappedFunctionPropagates_1043) {
    auto inv = Catch::makeTestInvoker(&MakeTestInvokerTest_1043::Thrower);
    EXPECT_THROW(inv->invoke(), std::runtime_error);
}

// Sanity: makeTestInvoker returns something implementing ITestInvoker (polymorphic call).
// We only verify that we can call the public interface; we do not depend on concrete types.
TEST_F(MakeTestInvokerTest_1043, ProvidesITestInvokerInterface_1043) {
    std::unique_ptr<Catch::ITestInvoker> inv =
        Catch::makeTestInvoker(&MakeTestInvokerTest_1043::FuncInc1);
    ASSERT_TRUE(inv);
    inv->invoke();  // purely through the ITestInvoker interface
    EXPECT_EQ(counter1, 1);
}
