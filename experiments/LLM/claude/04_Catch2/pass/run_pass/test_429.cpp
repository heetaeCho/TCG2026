#include <gtest/gtest.h>
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// A simple fixture class to track lifecycle and method invocations
struct TrackingFixture {
    static int constructCount;
    static int destructCount;
    static int invokeCount;

    static void reset() {
        constructCount = 0;
        destructCount = 0;
        invokeCount = 0;
    }

    TrackingFixture() { ++constructCount; }
    ~TrackingFixture() { ++destructCount; }

    void testMethod() const { ++invokeCount; }
};

int TrackingFixture::constructCount = 0;
int TrackingFixture::destructCount = 0;
int TrackingFixture::invokeCount = 0;

// A fixture that throws during construction
struct ThrowingConstructFixture {
    ThrowingConstructFixture() { throw std::runtime_error("construction failed"); }
    void testMethod() const {}
};

// A fixture that throws during the test method
struct ThrowingMethodFixture {
    static int constructCount;
    static void reset() { constructCount = 0; }

    ThrowingMethodFixture() { ++constructCount; }
    void testMethod() const { throw std::runtime_error("method failed"); }
};

int ThrowingMethodFixture::constructCount = 0;

// A fixture with multiple methods
struct MultiMethodFixture {
    static int methodACount;
    static int methodBCount;

    static void reset() {
        methodACount = 0;
        methodBCount = 0;
    }

    void methodA() const { ++methodACount; }
    void methodB() const { ++methodBCount; }
};

int MultiMethodFixture::methodACount = 0;
int MultiMethodFixture::methodBCount = 0;

class TestInvokerFixtureTest_429 : public ::testing::Test {
protected:
    void SetUp() override {
        TrackingFixture::reset();
        ThrowingMethodFixture::reset();
        MultiMethodFixture::reset();
    }
};

TEST_F(TestInvokerFixtureTest_429, ConstructorAcceptsMethodPointer_429) {
    // Should be constructible with a const member function pointer
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    // No crash, no exception — just verify construction is valid
    SUCCEED();
}

TEST_F(TestInvokerFixtureTest_429, ConstructorIsNoexcept_429) {
    EXPECT_TRUE(noexcept(Catch::TestInvokerFixture<TrackingFixture>(&TrackingFixture::testMethod)));
}

TEST_F(TestInvokerFixtureTest_429, PrepareTestCaseCreatesFixture_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    EXPECT_EQ(TrackingFixture::constructCount, 0);

    invoker.prepareTestCase();

    EXPECT_EQ(TrackingFixture::constructCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, InvokeCallsTestMethod_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    invoker.prepareTestCase();

    EXPECT_EQ(TrackingFixture::invokeCount, 0);
    invoker.invoke();
    EXPECT_EQ(TrackingFixture::invokeCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, InvokeCalledMultipleTimes_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    invoker.prepareTestCase();

    invoker.invoke();
    invoker.invoke();
    invoker.invoke();

    EXPECT_EQ(TrackingFixture::invokeCount, 3);
}

TEST_F(TestInvokerFixtureTest_429, TearDownTestCaseDestroysFixture_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    invoker.prepareTestCase();
    EXPECT_EQ(TrackingFixture::destructCount, 0);

    invoker.tearDownTestCase();

    EXPECT_EQ(TrackingFixture::destructCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, FullLifecycle_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);

    invoker.prepareTestCase();
    EXPECT_EQ(TrackingFixture::constructCount, 1);

    invoker.invoke();
    EXPECT_EQ(TrackingFixture::invokeCount, 1);

    invoker.tearDownTestCase();
    EXPECT_EQ(TrackingFixture::destructCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, PrepareTestCaseCalledTwiceCreatesNewFixture_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);

    invoker.prepareTestCase();
    EXPECT_EQ(TrackingFixture::constructCount, 1);

    invoker.prepareTestCase();
    EXPECT_EQ(TrackingFixture::constructCount, 2);
    // The old fixture should have been destroyed when replaced
    EXPECT_GE(TrackingFixture::destructCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, DifferentMethodsCanBeInvoked_429) {
    Catch::TestInvokerFixture<MultiMethodFixture> invokerA(&MultiMethodFixture::methodA);
    Catch::TestInvokerFixture<MultiMethodFixture> invokerB(&MultiMethodFixture::methodB);

    invokerA.prepareTestCase();
    invokerB.prepareTestCase();

    invokerA.invoke();
    EXPECT_EQ(MultiMethodFixture::methodACount, 1);
    EXPECT_EQ(MultiMethodFixture::methodBCount, 0);

    invokerB.invoke();
    EXPECT_EQ(MultiMethodFixture::methodACount, 1);
    EXPECT_EQ(MultiMethodFixture::methodBCount, 1);
}

TEST_F(TestInvokerFixtureTest_429, PrepareTestCaseThrowsIfFixtureConstructorThrows_429) {
    Catch::TestInvokerFixture<ThrowingConstructFixture> invoker(&ThrowingConstructFixture::testMethod);
    EXPECT_THROW(invoker.prepareTestCase(), std::runtime_error);
}

TEST_F(TestInvokerFixtureTest_429, InvokeThrowsIfMethodThrows_429) {
    Catch::TestInvokerFixture<ThrowingMethodFixture> invoker(&ThrowingMethodFixture::testMethod);
    invoker.prepareTestCase();
    EXPECT_THROW(invoker.invoke(), std::runtime_error);
}

TEST_F(TestInvokerFixtureTest_429, TearDownAfterTearDownIsHarmless_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    invoker.prepareTestCase();
    invoker.tearDownTestCase();
    // Second teardown should not crash (fixture already null)
    EXPECT_NO_THROW(invoker.tearDownTestCase());
}

TEST_F(TestInvokerFixtureTest_429, TearDownWithoutPrepareIsHarmless_429) {
    Catch::TestInvokerFixture<TrackingFixture> invoker(&TrackingFixture::testMethod);
    // No prepareTestCase called
    EXPECT_NO_THROW(invoker.tearDownTestCase());
    EXPECT_EQ(TrackingFixture::destructCount, 0);
}
