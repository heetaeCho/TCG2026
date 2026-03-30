#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Detail;



class TestInvokerAsFunction {

public:

    explicit TestInvokerAsFunction(void(*testAsFunction)()) : m_testAsFunction(testAsFunction) {}

    void invoke() const { m_testAsFunction(); }

private:

    void(*m_testAsFunction)();

};



TEST(TestInvokerTest_1043, MakeTestInvoker_ReturnsNonNullPointer_1043) {

    auto invoker = makeTestInvoker([](){});

    EXPECT_NE(invoker.get(), nullptr);

}



TEST(TestInvokerTest_1043, Invoke_CallsPassedInFunction_1043) {

    bool wasCalled = false;

    void testFunction() { wasCalled = true; }

    

    auto invoker = makeTestInvoker(testFunction);

    invoker->invoke();

    

    EXPECT_TRUE(wasCalled);

}



TEST(TestInvokerTest_1043, Invoke_MultipleCallsInvokePassedInFunctionMultipleTimes_1043) {

    int callCount = 0;

    void testFunction() { ++callCount; }

    

    auto invoker = makeTestInvoker(testFunction);

    invoker->invoke();

    invoker->invoke();

    

    EXPECT_EQ(callCount, 2);

}



TEST(TestInvokerTest_1043, MakeTestInvoker_WithNullFunction_ReturnsNonNullPointer_1043) {

    auto invoker = makeTestInvoker(nullptr);

    EXPECT_NE(invoker.get(), nullptr);

}



TEST(TestInvokerTest_1043, Invoke_WithNullFunction_DoesNotCrash_1043) {

    auto invoker = makeTestInvoker(nullptr);

    EXPECT_NO_THROW(invoker->invoke());

}
