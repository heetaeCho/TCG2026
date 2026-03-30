#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"



using namespace Catch;

using ::testing::Return;



class TestCaseHandleTest : public ::testing::Test {

protected:

    TestCaseInfo testCaseInfo;

    MockITestInvoker mockInvoker;



    TestCaseHandle handle{&testCaseInfo, &mockInvoker};

};



// Test normal operation

TEST_F(TestCaseHandleTest_285, GetTestCaseInfoReturnsCorrectInfo_285) {

    EXPECT_EQ(&handle.getTestCaseInfo(), &testCaseInfo);

}



// Test external interactions

TEST_F(TestCaseHandleTest_285, PrepareTestCaseInvokesCorrectMethod_285) {

    EXPECT_CALL(mockInvoker, prepareTestCase());

    handle.prepareTestCase();

}



TEST_F(TestCaseHandleTest_285, TearDownTestCaseInvokesCorrectMethod_285) {

    EXPECT_CALL(mockInvoker, tearDownTestCase());

    handle.tearDownTestCase();

}



TEST_F(TestCaseHandleTest_285, InvokeCallsTheCorrectMethod_285) {

    EXPECT_CALL(mockInvoker, invoke());

    handle.invoke();

}

```



```cpp

// Mock class for ITestInvoker to be used in tests

class MockITestInvoker : public ITestInvoker {

public:

    MOCK_CONST_METHOD0(prepareTestCase, void());

    MOCK_CONST_METHOD0(tearDownTestCase, void());

    MOCK_CONST_METHOD0(invoke, void());

};
