#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal recreation of the ITestInvoker interface that TestInvokerAsMethod inherits from
namespace Catch {

struct ITestInvoker {
    virtual void invoke() const = 0;
    virtual ~ITestInvoker() = default;
};

template <typename C>
class TestInvokerAsMethod : public ITestInvoker {
    void (C::*m_testAsMethod)();

public:
    constexpr TestInvokerAsMethod(void (C::*testAsMethod)()) noexcept
        : m_testAsMethod(testAsMethod) {}

    void invoke() const override {
        C obj;
        (obj.*m_testAsMethod)();
    }
};

} // namespace Catch

// ---- Test helper classes ----

// A simple class to track whether its method was called
static bool g_simpleCalled = false;

class SimpleTestClass {
public:
    void testMethod() {
        g_simpleCalled = true;
    }
};

// A class that increments a global counter each time its method is called
static int g_invokeCount = 0;

class CountingTestClass {
public:
    void countMethod() {
        g_invokeCount++;
    }
};

// A class with multiple methods to verify correct method pointer is used
static int g_whichMethod = 0;

class MultiMethodClass {
public:
    void methodA() {
        g_whichMethod = 1;
    }
    void methodB() {
        g_whichMethod = 2;
    }
};

// A class that modifies its own member during the test method
static int g_constructCount = 0;

class ConstructorTrackingClass {
public:
    ConstructorTrackingClass() {
        g_constructCount++;
    }
    void testMethod() {
        // just exists to be called
    }
};

// A class that throws during its test method
class ThrowingTestClass {
public:
    void throwingMethod() {
        throw std::runtime_error("test exception");
    }
};

// A class with default constructor that sets a value, and method checks it
static bool g_defaultInitialized = false;

class DefaultInitClass {
    int m_value;
public:
    DefaultInitClass() : m_value(42) {}
    void checkInit() {
        g_defaultInitialized = (m_value == 42);
    }
};

// ---- Tests ----

class TestInvokerAsMethodTest_427 : public ::testing::Test {
protected:
    void SetUp() override {
        g_simpleCalled = false;
        g_invokeCount = 0;
        g_whichMethod = 0;
        g_constructCount = 0;
        g_defaultInitialized = false;
    }
};

TEST_F(TestInvokerAsMethodTest_427, InvokeCallsSpecifiedMethod_427) {
    Catch::TestInvokerAsMethod<SimpleTestClass> invoker(&SimpleTestClass::testMethod);
    EXPECT_FALSE(g_simpleCalled);
    invoker.invoke();
    EXPECT_TRUE(g_simpleCalled);
}

TEST_F(TestInvokerAsMethodTest_427, InvokeCanBeCalledMultipleTimes_427) {
    Catch::TestInvokerAsMethod<CountingTestClass> invoker(&CountingTestClass::countMethod);
    EXPECT_EQ(g_invokeCount, 0);
    invoker.invoke();
    EXPECT_EQ(g_invokeCount, 1);
    invoker.invoke();
    EXPECT_EQ(g_invokeCount, 2);
    invoker.invoke();
    EXPECT_EQ(g_invokeCount, 3);
}

TEST_F(TestInvokerAsMethodTest_427, InvokeCallsCorrectMethodA_427) {
    Catch::TestInvokerAsMethod<MultiMethodClass> invoker(&MultiMethodClass::methodA);
    invoker.invoke();
    EXPECT_EQ(g_whichMethod, 1);
}

TEST_F(TestInvokerAsMethodTest_427, InvokeCallsCorrectMethodB_427) {
    Catch::TestInvokerAsMethod<MultiMethodClass> invoker(&MultiMethodClass::methodB);
    invoker.invoke();
    EXPECT_EQ(g_whichMethod, 2);
}

TEST_F(TestInvokerAsMethodTest_427, EachInvokeCreatesNewObject_427) {
    Catch::TestInvokerAsMethod<ConstructorTrackingClass> invoker(&ConstructorTrackingClass::testMethod);
    EXPECT_EQ(g_constructCount, 0);
    invoker.invoke();
    EXPECT_EQ(g_constructCount, 1);
    invoker.invoke();
    EXPECT_EQ(g_constructCount, 2);
    invoker.invoke();
    EXPECT_EQ(g_constructCount, 3);
}

TEST_F(TestInvokerAsMethodTest_427, ThrowingMethodPropagatesException_427) {
    Catch::TestInvokerAsMethod<ThrowingTestClass> invoker(&ThrowingTestClass::throwingMethod);
    EXPECT_THROW(invoker.invoke(), std::runtime_error);
}

TEST_F(TestInvokerAsMethodTest_427, ObjectIsDefaultConstructedBeforeInvoke_427) {
    Catch::TestInvokerAsMethod<DefaultInitClass> invoker(&DefaultInitClass::checkInit);
    invoker.invoke();
    EXPECT_TRUE(g_defaultInitialized);
}

TEST_F(TestInvokerAsMethodTest_427, PolymorphicAccessThroughBasePointer_427) {
    Catch::TestInvokerAsMethod<SimpleTestClass> invoker(&SimpleTestClass::testMethod);
    const Catch::ITestInvoker* basePtr = &invoker;
    EXPECT_FALSE(g_simpleCalled);
    basePtr->invoke();
    EXPECT_TRUE(g_simpleCalled);
}

TEST_F(TestInvokerAsMethodTest_427, ConstructorIsConstexpr_427) {
    // Verify that the constructor can be used in a constexpr context (compile-time check)
    constexpr Catch::TestInvokerAsMethod<SimpleTestClass> invoker(&SimpleTestClass::testMethod);
    // If this compiles, the constexpr constructor works
    invoker.invoke();
    EXPECT_TRUE(g_simpleCalled);
}

TEST_F(TestInvokerAsMethodTest_427, DifferentInvokersAreIndependent_427) {
    Catch::TestInvokerAsMethod<MultiMethodClass> invokerA(&MultiMethodClass::methodA);
    Catch::TestInvokerAsMethod<MultiMethodClass> invokerB(&MultiMethodClass::methodB);

    invokerA.invoke();
    EXPECT_EQ(g_whichMethod, 1);

    invokerB.invoke();
    EXPECT_EQ(g_whichMethod, 2);

    invokerA.invoke();
    EXPECT_EQ(g_whichMethod, 1);
}
