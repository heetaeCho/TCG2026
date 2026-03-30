#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"

#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"



using namespace Catch;

using ::testing::MockFunction;



class MockITestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, prepareTestCase, (), (override));

    MOCK_METHOD(void, tearDownTestCase, (), (override));

    MOCK_METHOD(void, invoke, (), (const, override));

};



TEST_F(TestCaseHandleTest_283, PrepareTestCaseInvokesInvokerPrepare_283) {

    MockITestInvoker mockInvoker;

    TestCaseInfo testCaseInfo;

    TestCaseHandle testCaseHandle(&testCaseInfo, &mockInvoker);



    EXPECT_CALL(mockInvoker, prepareTestCase());

    testCaseHandle.prepareTestCase();

}



TEST_F(TestCaseHandleTest_283, TearDownTestCaseInvokesInvokerTearDown_283) {

    MockITestInvoker mockInvoker;

    TestCaseInfo testCaseInfo;

    TestCaseHandle testCaseHandle(&testCaseInfo, &mockInvoker);



    EXPECT_CALL(mockInvoker, tearDownTestCase());

    testCaseHandle.tearDownTestCase();

}



TEST_F(TestCaseHandleTest_283, InvokeInvokesInvokerInvoke_283) {

    MockITestInvoker mockInvoker;

    TestCaseInfo testCaseInfo;

    TestCaseHandle testCaseHandle(&testCaseInfo, &mockInvoker);



    EXPECT_CALL(mockInvoker, invoke());

    testCaseHandle.invoke();

}



TEST_F(TestCaseHandleTest_283, GetTestCaseInfoReturnsCorrectInfo_283) {

    MockITestInvoker mockInvoker;

    TestCaseInfo testCaseInfo;

    TestCaseHandle testCaseHandle(&testCaseInfo, &mockInvoker);



    EXPECT_EQ(&testCaseInfo, &testCaseHandle.getTestCaseInfo());

}
