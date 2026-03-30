#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_test_invoker.hpp"



using namespace Catch;

using ::testing::StrictMock;



class MockITestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, prepareTestCase, (), (override));

    MOCK_METHOD(void, tearDownTestCase, (), (override));

    MOCK_METHOD(void, invoke, (), (const, override));

};



class TestCaseHandleTest_284 : public ::testing::Test {

protected:

    MockITestInvoker mock_invoker;

    TestCaseInfo test_info; // Assuming TestCaseInfo can be default constructed

    TestCaseHandle handle{&test_info, &mock_invoker};

};



TEST_F(TestCaseHandleTest_284, PrepareTestCaseInvokesPrepareOnInvoker_284) {

    EXPECT_CALL(mock_invoker, prepareTestCase());

    handle.prepareTestCase();

}



TEST_F(TestCaseHandleTest_284, TearDownTestCaseInvokesTearDownOnInvoker_284) {

    EXPECT_CALL(mock_invoker, tearDownTestCase());

    handle.tearDownTestCase();

}



TEST_F(TestCaseHandleTest_284, InvokeCallsInvokeOnInvoker_284) {

    EXPECT_CALL(mock_invoker, invoke());

    handle.invoke();

}



TEST_F(TestCaseHandleTest_284, GetTestCaseInfoReturnsReferenceToInfo_284) {

    const TestCaseInfo& returned_info = handle.getTestCaseInfo();

    EXPECT_EQ(&returned_info, &test_info);

}
