#include <gtest/gtest.h>
#include <catch2/internal/catch_test_registry.hpp>
#include <catch2/interfaces/catch_interfaces_testcase.hpp>

// Tracking variables for test fixture lifecycle
static int g_constructCount = 0;
static int g_destructCount = 0;
static int g_testMethodCallCount = 0;

class MockFixture {
public:
    MockFixture() { ++g_constructCount; }
    ~MockFixture() { ++g_destructCount; }
    
    void testMethod() const {
        ++g_testMethodCallCount;
    }
    
    void anotherTestMethod() const {
        g_testMethodCallCount += 10;
    }
};

class TestInvokerFixtureTest_430 : public ::testing::Test {
protected:
    void SetUp() override {
        g_constructCount = 0;
        g_destructCount = 0;
        g_testMethodCallCount = 0;
    }
};

TEST_F(TestInvokerFixtureTest_430, ConstructorAcceptsMethodPointer_430) {
    // Test that constructor accepts a member function pointer without throwing
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    // If we get here, construction succeeded
    SUCCEED();
}

TEST_F(TestInvokerFixtureTest_430, ConstructorIsConstexprAndNoexcept_430) {
    // Verify the constructor can be used in constexpr/noexcept context
    constexpr auto ptr = &MockFixture::testMethod;
    Catch::TestInvokerFixture<MockFixture> invoker(ptr);
    SUCCEED();
}

TEST_F(TestInvokerFixtureTest_430, PrepareTestCaseCreatesFixture_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    EXPECT_EQ(g_constructCount, 0);
    invoker.prepareTestCase();
    EXPECT_EQ(g_constructCount, 1);
}

TEST_F(TestInvokerFixtureTest_430, TearDownTestCaseDestroysFixture_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    invoker.prepareTestCase();
    EXPECT_EQ(g_destructCount, 0);
    
    invoker.tearDownTestCase();
    EXPECT_EQ(g_destructCount, 1);
}

TEST_F(TestInvokerFixtureTest_430, InvokeCallsTestMethod_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    invoker.prepareTestCase();
    EXPECT_EQ(g_testMethodCallCount, 0);
    
    invoker.invoke();
    EXPECT_EQ(g_testMethodCallCount, 1);
}

TEST_F(TestInvokerFixtureTest_430, InvokeCallsCorrectMethod_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::anotherTestMethod);
    
    invoker.prepareTestCase();
    EXPECT_EQ(g_testMethodCallCount, 0);
    
    invoker.invoke();
    EXPECT_EQ(g_testMethodCallCount, 10);
}

TEST_F(TestInvokerFixtureTest_430, MultipleInvocationsCallMethodMultipleTimes_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    invoker.prepareTestCase();
    invoker.invoke();
    invoker.invoke();
    invoker.invoke();
    
    EXPECT_EQ(g_testMethodCallCount, 3);
}

TEST_F(TestInvokerFixtureTest_430, TearDownAfterTearDownIsHarmless_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    invoker.prepareTestCase();
    invoker.tearDownTestCase();
    
    int destructCountAfterFirst = g_destructCount;
    // Second teardown should be safe (resetting nullptr)
    invoker.tearDownTestCase();
    EXPECT_EQ(g_destructCount, destructCountAfterFirst);
}

TEST_F(TestInvokerFixtureTest_430, PrepareAndTearDownCycle_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    invoker.prepareTestCase();
    invoker.invoke();
    invoker.tearDownTestCase();
    
    EXPECT_EQ(g_constructCount, 1);
    EXPECT_EQ(g_destructCount, 1);
    EXPECT_EQ(g_testMethodCallCount, 1);
    
    invoker.prepareTestCase();
    invoker.invoke();
    invoker.tearDownTestCase();
    
    EXPECT_EQ(g_constructCount, 2);
    EXPECT_EQ(g_destructCount, 2);
    EXPECT_EQ(g_testMethodCallCount, 2);
}

TEST_F(TestInvokerFixtureTest_430, DestructorCleansUpFixture_430) {
    {
        Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
        invoker.prepareTestCase();
        EXPECT_EQ(g_destructCount, 0);
    }
    // Destructor of invoker should clean up the fixture
    EXPECT_EQ(g_destructCount, 1);
}

TEST_F(TestInvokerFixtureTest_430, TearDownWithoutPrepareIsSafe_430) {
    Catch::TestInvokerFixture<MockFixture> invoker(&MockFixture::testMethod);
    
    // tearDown without prepare should be safe since m_fixture is nullptr
    invoker.tearDownTestCase();
    EXPECT_EQ(g_destructCount, 0);
}
