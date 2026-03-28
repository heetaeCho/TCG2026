#include <catch2/internal/catch_test_registry.hpp>
#include <catch2/internal/catch_test_case_registry_impl.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

#include <gtest/gtest.h>

// Test fixture classes used as collaborators
namespace {

static int g_constructCount = 0;
static int g_destructCount = 0;
static int g_invokeCount = 0;

struct SimpleFixture {
    SimpleFixture() { ++g_constructCount; }
    ~SimpleFixture() { ++g_destructCount; }
    void testMethod() const { ++g_invokeCount; }
};

static int g_anotherInvokeCount = 0;

struct AnotherFixture {
    void anotherTest() const { ++g_anotherInvokeCount; }
};

static int g_multiMethodCall1 = 0;
static int g_multiMethodCall2 = 0;

struct MultiMethodFixture {
    void method1() const { ++g_multiMethodCall1; }
    void method2() const { ++g_multiMethodCall2; }
};

static bool g_emptyInvoked = false;

struct EmptyFixture {
    void doNothing() const { g_emptyInvoked = true; }
};

struct StatefulFixture {
    static int g_value;
    StatefulFixture() { g_value = 42; }
    void checkValue() const {
        // Just increment to show invocation happened
        g_value += 1;
    }
};
int StatefulFixture::g_value = 0;

} // anonymous namespace

class MakeTestInvokerFixtureTest_432 : public ::testing::Test {
protected:
    void SetUp() override {
        g_constructCount = 0;
        g_destructCount = 0;
        g_invokeCount = 0;
        g_anotherInvokeCount = 0;
        g_multiMethodCall1 = 0;
        g_multiMethodCall2 = 0;
        g_emptyInvoked = false;
        StatefulFixture::g_value = 0;
    }
};

TEST_F(MakeTestInvokerFixtureTest_432, ReturnsNonNullPointer_432) {
    auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
    EXPECT_NE(invoker.get(), nullptr);
}

TEST_F(MakeTestInvokerFixtureTest_432, InvokeCallsTestMethod_432) {
    auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
    ASSERT_EQ(g_invokeCount, 0);
    invoker->invoke();
    EXPECT_EQ(g_invokeCount, 1);
}

TEST_F(MakeTestInvokerFixtureTest_432, InvokeConstructsAndDestructsFixture_432) {
    auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
    ASSERT_EQ(g_constructCount, 0);
    ASSERT_EQ(g_destructCount, 0);
    invoker->invoke();
    EXPECT_GE(g_constructCount, 1);
    EXPECT_GE(g_destructCount, 1);
}

TEST_F(MakeTestInvokerFixtureTest_432, MultipleInvocationsCallMethodMultipleTimes_432) {
    auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
    invoker->invoke();
    invoker->invoke();
    invoker->invoke();
    EXPECT_EQ(g_invokeCount, 3);
}

TEST_F(MakeTestInvokerFixtureTest_432, DifferentFixtureClass_432) {
    auto invoker = Catch::makeTestInvokerFixture(&AnotherFixture::anotherTest);
    ASSERT_EQ(g_anotherInvokeCount, 0);
    invoker->invoke();
    EXPECT_EQ(g_anotherInvokeCount, 1);
}

TEST_F(MakeTestInvokerFixtureTest_432, DifferentMethodsSameFixture_432) {
    auto invoker1 = Catch::makeTestInvokerFixture(&MultiMethodFixture::method1);
    auto invoker2 = Catch::makeTestInvokerFixture(&MultiMethodFixture::method2);
    
    invoker1->invoke();
    EXPECT_EQ(g_multiMethodCall1, 1);
    EXPECT_EQ(g_multiMethodCall2, 0);
    
    invoker2->invoke();
    EXPECT_EQ(g_multiMethodCall1, 1);
    EXPECT_EQ(g_multiMethodCall2, 1);
}

TEST_F(MakeTestInvokerFixtureTest_432, EmptyMethodInvocation_432) {
    auto invoker = Catch::makeTestInvokerFixture(&EmptyFixture::doNothing);
    invoker->invoke();
    EXPECT_TRUE(g_emptyInvoked);
}

TEST_F(MakeTestInvokerFixtureTest_432, FixtureConstructorRunsBeforeMethod_432) {
    auto invoker = Catch::makeTestInvokerFixture(&StatefulFixture::checkValue);
    ASSERT_EQ(StatefulFixture::g_value, 0);
    invoker->invoke();
    // Constructor sets to 42, method adds 1 -> 43
    EXPECT_EQ(StatefulFixture::g_value, 43);
}

TEST_F(MakeTestInvokerFixtureTest_432, EachInvocationCreatesNewFixture_432) {
    auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
    invoker->invoke();
    int constructsAfterFirst = g_constructCount;
    invoker->invoke();
    EXPECT_GT(g_constructCount, constructsAfterFirst);
}

TEST_F(MakeTestInvokerFixtureTest_432, DestroyInvokerWithoutInvoking_432) {
    {
        auto invoker = Catch::makeTestInvokerFixture(&SimpleFixture::testMethod);
        // Let it go out of scope without invoking
    }
    EXPECT_EQ(g_invokeCount, 0);
    EXPECT_EQ(g_constructCount, 0);
}
