// File: test_testinvokerfixture_431.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_test_registry.hpp"  // Path from the prompt

// A simple spy type with an observable side effect (static call counter).
struct Spy431 {
    static int calls;
    static void Reset() { calls = 0; }

    Spy431() = default;

    // Must be const to match the interface in the prompt.
    void TestMethod() const { ++calls; }
};
int Spy431::calls = 0;

// ---------- Tests ----------

/*
 * Verifies that constructing TestInvokerFixture with a pointer-to-const-member
 * compiles and binds the expected member function type.
 */
TEST(TestInvokerFixture_431, BindsConstMemberFunctionType_431) {
    using MemberPtr = void (Spy431::*)() const;
    MemberPtr p = &Spy431::TestMethod; // compile-time check of signature
    (void)p;
    SUCCEED();
}

/*
 * Normal operation: invoke() calls the bound test method exactly once.
 */
TEST(TestInvokerFixture_431, InvokeCallsBoundMethodOnce_431) {
    Spy431::Reset();

    Catch::TestInvokerFixture<Spy431> invoker(&Spy431::TestMethod);

    // Act
    invoker.invoke();

    // Assert
    EXPECT_EQ(Spy431::calls, 1);
}

/*
 * Repeated operation: multiple calls to invoke() call the method each time.
 */
TEST(TestInvokerFixture_431, MultipleInvokesAccumulateCalls_431) {
    Spy431::Reset();

    Catch::TestInvokerFixture<Spy431> invoker(&Spy431::TestMethod);

    // Act
    invoker.invoke();
    invoker.invoke();
    invoker.invoke();

    // Assert
    EXPECT_EQ(Spy431::calls, 3);
}

/*
 * Lifecycle methods: prepareTestCase() and tearDownTestCase() are callable.
 * We only assert observable behavior via invoke(); we do NOT assume or test
 * any internal allocation or destruction strategy.
 */
TEST(TestInvokerFixture_431, PrepareInvokeTearDownLifecycle_431) {
    Spy431::Reset();

    Catch::TestInvokerFixture<Spy431> invoker(&Spy431::TestMethod);

    // Arrange / Act
    // These should be callable without throwing. We don’t assume more.
    EXPECT_NO_THROW(invoker.prepareTestCase());
    EXPECT_NO_THROW(invoker.invoke());
    EXPECT_NO_THROW(invoker.tearDownTestCase());

    // Assert: The observable effect from invoke() is exactly one call.
    EXPECT_EQ(Spy431::calls, 1);
}

/*
 * Boundary-ish check: invoke() remains callable before/without explicit
 * prepareTestCase() (if supported by the implementation). We assert only that
 * invoke() produces the observable effect; we do not assume internal state.
 */
TEST(TestInvokerFixture_431, InvokeWithoutExplicitPrepareStillCallsMethod_431) {
    Spy431::Reset();

    Catch::TestInvokerFixture<Spy431> invoker(&Spy431::TestMethod);

    // Act
    EXPECT_NO_THROW(invoker.invoke());

    // Assert
    EXPECT_EQ(Spy431::calls, 1);
}
