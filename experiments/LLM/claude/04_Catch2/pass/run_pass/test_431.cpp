#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to include the header under test
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// Since we're testing TestInvokerFixture which is a template class that creates
// fixtures and invokes test methods, we need to create test fixture classes.

namespace {

// Track whether methods were called
static bool g_invokeWasCalled = false;
static bool g_prepareWasCalled = false;
static bool g_tearDownWasCalled = false;
static int g_invokeCallCount = 0;

// A simple test fixture class for testing TestInvokerFixture
class SimpleFixture {
public:
    SimpleFixture() = default;
    virtual ~SimpleFixture() = default;

    void testMethod() const {
        g_invokeWasCalled = true;
        g_invokeCallCount++;
    }

    void anotherTestMethod() const {
        // Different method to verify correct method pointer is used
        g_invokeCallCount += 10;
    }
};

// A fixture that throws during the test method
class ThrowingFixture {
public:
    ThrowingFixture() = default;
    virtual ~ThrowingFixture() = default;

    void throwingMethod() const {
        throw std::runtime_error("test exception");
    }
};

// A fixture that modifies state to verify it's properly constructed
class StatefulFixture {
public:
    static int s_constructCount;
    static int s_destructCount;

    StatefulFixture() { s_constructCount++; }
    virtual ~StatefulFixture() { s_destructCount++; }

    void testMethod() const {
        g_invokeWasCalled = true;
    }
};

int StatefulFixture::s_constructCount = 0;
int StatefulFixture::s_destructCount = 0;

} // anonymous namespace

class TestInvokerFixtureTest_431 : public ::testing::Test {
protected:
    void SetUp() override {
        g_invokeWasCalled = false;
        g_prepareWasCalled = false;
        g_tearDownWasCalled = false;
        g_invokeCallCount = 0;
        StatefulFixture::s_constructCount = 0;
        StatefulFixture::s_destructCount = 0;
    }
};

// Test that TestInvokerFixture can be constructed with a method pointer
TEST_F(TestInvokerFixtureTest_431, ConstructWithMethodPointer_431) {
    // Should not throw during construction
    EXPECT_NO_THROW({
        Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::testMethod);
    });
}

// Test that invoke calls the correct test method on the fixture
TEST_F(TestInvokerFixtureTest_431, InvokeCallsTestMethod_431) {
    Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::testMethod);
    
    // prepareTestCase should set up the fixture
    invoker.prepareTestCase();
    
    EXPECT_FALSE(g_invokeWasCalled);
    invoker.invoke();
    EXPECT_TRUE(g_invokeWasCalled);
    EXPECT_EQ(g_invokeCallCount, 1);
    
    invoker.tearDownTestCase();
}

// Test that the correct method pointer is used (not some other method)
TEST_F(TestInvokerFixtureTest_431, InvokeCallsCorrectMethod_431) {
    Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::anotherTestMethod);
    
    invoker.prepareTestCase();
    invoker.invoke();
    
    // anotherTestMethod adds 10, not 1
    EXPECT_EQ(g_invokeCallCount, 10);
    
    invoker.tearDownTestCase();
}

// Test that prepareTestCase can be called without error
TEST_F(TestInvokerFixtureTest_431, PrepareTestCase_431) {
    Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::testMethod);
    
    EXPECT_NO_THROW(invoker.prepareTestCase());
    
    invoker.tearDownTestCase();
}

// Test that tearDownTestCase can be called without error
TEST_F(TestInvokerFixtureTest_431, TearDownTestCase_431) {
    Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::testMethod);
    
    invoker.prepareTestCase();
    EXPECT_NO_THROW(invoker.tearDownTestCase());
}

// Test that prepareTestCase creates the fixture (stateful check)
TEST_F(TestInvokerFixtureTest_431, PrepareCreatesFixture_431) {
    Catch::TestInvokerFixture<StatefulFixture> invoker(&StatefulFixture::testMethod);
    
    EXPECT_EQ(StatefulFixture::s_constructCount, 0);
    invoker.prepareTestCase();
    EXPECT_GE(StatefulFixture::s_constructCount, 1);
    
    invoker.tearDownTestCase();
}

// Test that tearDownTestCase destroys the fixture
TEST_F(TestInvokerFixtureTest_431, TearDownDestroysFixture_431) {
    Catch::TestInvokerFixture<StatefulFixture> invoker(&StatefulFixture::testMethod);
    
    invoker.prepareTestCase();
    int countBeforeTearDown = StatefulFixture::s_destructCount;
    invoker.tearDownTestCase();
    EXPECT_GT(StatefulFixture::s_destructCount, countBeforeTearDown);
}

// Test that invoke can be called multiple times (if prepare sets up fixture once)
TEST_F(TestInvokerFixtureTest_431, MultipleInvocations_431) {
    Catch::TestInvokerFixture<SimpleFixture> invoker(&SimpleFixture::testMethod);
    
    invoker.prepareTestCase();
    invoker.invoke();
    invoker.invoke();
    
    EXPECT_EQ(g_invokeCallCount, 2);
    
    invoker.tearDownTestCase();
}

// Test the full lifecycle: prepare -> invoke -> tearDown
TEST_F(TestInvokerFixtureTest_431, FullLifecycle_431) {
    Catch::TestInvokerFixture<StatefulFixture> invoker(&StatefulFixture::testMethod);
    
    // Prepare
    invoker.prepareTestCase();
    EXPECT_GE(StatefulFixture::s_constructCount, 1);
    
    // Invoke
    invoker.invoke();
    EXPECT_TRUE(g_invokeWasCalled);
    
    // Tear down
    int destructsBefore = StatefulFixture::s_destructCount;
    invoker.tearDownTestCase();
    EXPECT_GT(StatefulFixture::s_destructCount, destructsBefore);
}

// Test that a throwing test method propagates the exception through invoke
TEST_F(TestInvokerFixtureTest_431, InvokeWithThrowingMethod_431) {
    Catch::TestInvokerFixture<ThrowingFixture> invoker(&ThrowingFixture::throwingMethod);
    
    invoker.prepareTestCase();
    
    EXPECT_THROW(invoker.invoke(), std::runtime_error);
    
    invoker.tearDownTestCase();
}

// Test constexpr construction (compile-time check essentially)
TEST_F(TestInvokerFixtureTest_431, ConstexprConstruction_431) {
    // The constructor is marked constexpr and noexcept
    constexpr auto methodPtr = &SimpleFixture::testMethod;
    Catch::TestInvokerFixture<SimpleFixture> invoker(methodPtr);
    
    // Just verify it compiles and doesn't throw
    SUCCEED();
}
