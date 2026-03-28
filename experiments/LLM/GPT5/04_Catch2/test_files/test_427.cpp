// File: test_testinvokerasmethod_427.cpp
#include <gtest/gtest.h>
#include <stdexcept>

// Include the real interface under test.
// Adjust the include path to match your project layout.
#include "catch2/internal/catch_test_registry.hpp"

namespace {

// --- Helpers for observable side-effects (no peeking into internals) ---

struct CounterC {
    static int& Calls() { static int calls = 0; return calls; }
    static void Reset() { Calls() = 0; }
    void testMethod() { ++Calls(); }
};

struct AnotherCounterC {
    static int& Calls() { static int calls = 0; return calls; }
    static void Reset() { Calls() = 0; }
    void doWork() { ++Calls(); }
};

struct ThrowerC {
    void boom() { throw std::runtime_error("boom"); }
};

// Common fixture to reset counters where relevant.
struct TestInvokerAsMethodTest_427 : ::testing::Test {
    void SetUp() override {
        CounterC::Reset();
        AnotherCounterC::Reset();
    }
};

} // namespace

// -------------------- Tests --------------------

TEST_F(TestInvokerAsMethodTest_427, Invoke_CallsBoundMethodOnce_427) {
    Catch::TestInvokerAsMethod<CounterC> invoker(&CounterC::testMethod);

    invoker.invoke();

    EXPECT_EQ(CounterC::Calls(), 1) << "invoke() should call the bound method exactly once";
}

TEST_F(TestInvokerAsMethodTest_427, Invoke_MultipleTimes_CallsEachTime_427) {
    Catch::TestInvokerAsMethod<CounterC> invoker(&CounterC::testMethod);

    invoker.invoke();
    invoker.invoke();
    invoker.invoke();

    EXPECT_EQ(CounterC::Calls(), 3) << "Repeated invoke() calls should trigger the method each time";
}

TEST_F(TestInvokerAsMethodTest_427, WorksWithDifferentClassTypes_427) {
    Catch::TestInvokerAsMethod<AnotherCounterC> invoker(&AnotherCounterC::doWork);

    invoker.invoke();
    invoker.invoke();

    EXPECT_EQ(AnotherCounterC::Calls(), 2)
        << "Template should work with different classes/method names of matching signature";
}

TEST_F(TestInvokerAsMethodTest_427, Invoke_PropagatesExceptionFromMethod_427) {
    Catch::TestInvokerAsMethod<ThrowerC> invoker(&ThrowerC::boom);

    EXPECT_THROW(invoker.invoke(), std::runtime_error)
        << "Exceptions thrown by the bound method should propagate out of invoke()";
}

// Optional: If you support death tests and want to assert behavior with nullptr.
// This checks an observable failure rather than any internal detail.
// Note: Only include if your environment supports death tests reliably.
#if GTEST_HAS_DEATH_TEST
TEST_F(TestInvokerAsMethodTest_427, Invoke_WithNullMemberPointer_Death_427) {
    // Construct with a null member function pointer. Behavior is undefined in general,
    // but from the public interface perspective we can assert that invoking is a fatal error.
    using C = CounterC;
    void (C::*nullPtr)() = nullptr;
    Catch::TestInvokerAsMethod<C> invoker(nullPtr);

    EXPECT_DEATH(invoker.invoke(), ".*")
        << "Invoking with a null member function pointer should cause a fatal error";
}
#endif
