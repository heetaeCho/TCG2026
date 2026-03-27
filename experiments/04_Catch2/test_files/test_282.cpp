#include <gtest/gtest.h>

#include "catch2/catch_test_case_info.hpp"

#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"



using namespace Catch;



class MockTestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, prepareTestCase, (), (override));

    MOCK_METHOD(void, tearDownTestCase, (), (override));

    MOCK_METHOD(const void, invoke, (), (const, override));

};



class TestCaseHandleTest_282 : public ::testing::Test {

protected:

    MockTestInvoker mock_invoker;

    TestCaseInfo test_info;

    TestCaseHandle test_case_handle;



    TestCaseHandleTest_282() : test_case_handle(&test_info, &mock_invoker) {}

};



TEST_F(TestCaseHandleTest_282, PrepareTestCaseInvokesMock_282) {

    EXPECT_CALL(mock_invoker, prepareTestCase());

    test_case_handle.prepareTestCase();

}



TEST_F(TestCaseHandleTest_282, TearDownTestCaseInvokesMock_282) {

    EXPECT_CALL(mock_invoker, tearDownTestCase());

    test_case_handle.tearDownTestCase();

}



TEST_F(TestCaseHandleTest_282, InvokeCallsInvokerInvoke_282) {

    EXPECT_CALL(mock_invoker, invoke());

    test_case_handle.invoke();

}
