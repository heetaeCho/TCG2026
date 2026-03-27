// File: make_test_invoker_tests_428.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_test_registry.hpp"

namespace {

struct Dummy {
    static int counter;
    void test() { ++counter; }
};
int Dummy::counter = 0;

struct Thrower {
    void test() { throw std::runtime_error("boom"); }
};

} // namespace

// Ensures a valid invoker is produced for a simple void (C::*)() member
TEST(MakeTestInvokerTest_428, ReturnsNonNull_428) {
    auto inv = Catch::makeTestInvoker(&Dummy::test);
    ASSERT_NE(inv, nullptr);
}

// Invoking the invoker runs the bound member function on a default-constructed instance
TEST(MakeTestInvokerTest_428, InvokeCallsMember_428) {
    Dummy::counter = 0;
    auto inv = Catch::makeTestInvoker(&Dummy::test);

    inv->invoke();

    EXPECT_EQ(Dummy::counter, 1);
}

// Invoking multiple times should call the member function each time (observable side effect)
TEST(MakeTestInvokerTest_428, MultipleInvocations_428) {
    Dummy::counter = 0;
    auto inv = Catch::makeTestInvoker(&Dummy::test);

    inv->invoke();
    inv->invoke();

    EXPECT_EQ(Dummy::counter, 2);
}

// Exceptions thrown by the member function should propagate to the caller (observable via throw)
TEST(MakeTestInvokerTest_428, InvokePropagatesExceptions_428) {
    auto inv = Catch::makeTestInvoker(&Thrower::test);
    EXPECT_THROW(inv->invoke(), std::runtime_error);
}
