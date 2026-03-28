#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"

using namespace Catch;
using ::testing::StrictMock;
using ::testing::InSequence;

class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
    MOCK_METHOD(void, invoke, (), (const, override));
    ~MockTestInvoker() override = default;
};

class TestCaseHandleTest_283 : public ::testing::Test {
protected:
    void SetUp() override {
        mockInvoker = new StrictMock<MockTestInvoker>();
    }

    void TearDown() override {
        delete mockInvoker;
    }

    StrictMock<MockTestInvoker>* mockInvoker = nullptr;
};

TEST_F(TestCaseHandleTest_283, TearDownTestCase_CallsInvokerTearDown_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(1);
    
    handle.tearDownTestCase();
}

TEST_F(TestCaseHandleTest_283, PrepareTestCase_CallsInvokerPrepare_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(1);
    
    handle.prepareTestCase();
}

TEST_F(TestCaseHandleTest_283, Invoke_CallsInvokerInvoke_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, invoke()).Times(1);
    
    handle.invoke();
}

TEST_F(TestCaseHandleTest_283, GetTestCaseInfo_ReturnsProvidedInfo_283) {
    TestCaseInfo info("", {"test_name", "test_tag"}, {"source_file.cpp", 42});
    TestCaseHandle handle(&info, mockInvoker);
    
    const TestCaseInfo& retrieved = handle.getTestCaseInfo();
    
    EXPECT_EQ(&retrieved, &info);
}

TEST_F(TestCaseHandleTest_283, PrepareAndTearDown_CalledInSequence_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    {
        InSequence seq;
        EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(1);
        EXPECT_CALL(*mockInvoker, invoke()).Times(1);
        EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(1);
    }
    
    handle.prepareTestCase();
    handle.invoke();
    handle.tearDownTestCase();
}

TEST_F(TestCaseHandleTest_283, MultipleTearDownCalls_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(3);
    
    handle.tearDownTestCase();
    handle.tearDownTestCase();
    handle.tearDownTestCase();
}

TEST_F(TestCaseHandleTest_283, MultiplePrepareTestCaseCalls_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(2);
    
    handle.prepareTestCase();
    handle.prepareTestCase();
}

TEST_F(TestCaseHandleTest_283, MultipleInvokeCalls_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, invoke()).Times(2);
    
    handle.invoke();
    handle.invoke();
}

TEST_F(TestCaseHandleTest_283, ConstHandle_CanCallTearDown_283) {
    const TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(1);
    
    handle.tearDownTestCase();
}

TEST_F(TestCaseHandleTest_283, ConstHandle_CanCallPrepare_283) {
    const TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(1);
    
    handle.prepareTestCase();
}

TEST_F(TestCaseHandleTest_283, ConstHandle_CanCallInvoke_283) {
    const TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, invoke()).Times(1);
    
    handle.invoke();
}

TEST_F(TestCaseHandleTest_283, ConstHandle_CanGetTestCaseInfo_283) {
    TestCaseInfo info("", {"test_name", "test_tag"}, {"source_file.cpp", 10});
    const TestCaseHandle handle(&info, mockInvoker);
    
    const TestCaseInfo& retrieved = handle.getTestCaseInfo();
    
    EXPECT_EQ(&retrieved, &info);
}

TEST_F(TestCaseHandleTest_283, ConstructWithNullInfo_TearDownStillWorks_283) {
    TestCaseHandle handle(nullptr, mockInvoker);
    
    EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(1);
    
    handle.tearDownTestCase();
}
