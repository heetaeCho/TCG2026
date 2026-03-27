#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_run_context.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;



class MockTestCaseInfo : public TestCaseInfo {

public:

    MOCK_METHOD(const std::string&, name, (), const);

};



class MockTestCaseHandle : public TestCaseHandle {

public:

    MockTestCaseHandle(TestCaseInfo* info, ITestInvoker* invoker) 

        : TestCaseHandle(info, invoker) {}



    MOCK_METHOD(const TestCaseInfo &, getTestCaseInfo, (), const, override);

};



TEST_F(RunContextTest_508, GetCurrentTestName_ReturnsEmptyStringWhenNoActiveTestCase_508) {

    RunContext runContext(nullptr, nullptr);

    EXPECT_EQ(runContext.getCurrentTestName(), "");

}



TEST_F(RunContextTest_508, GetCurrentTestName_ReturnsCorrectTestNameWhenActiveTestCaseSet_508) {

    auto mockInfo = std::make_unique<MockTestCaseInfo>();

    EXPECT_CALL(*mockInfo, name()).WillOnce(::testing::Return("SampleTest"));



    auto mockHandle = std::make_unique<MockTestCaseHandle>(mockInfo.get(), nullptr);

    EXPECT_CALL(*mockHandle, getTestCaseInfo()).WillRepeatedly(::testing::ReturnRef(*mockInfo));



    RunContext runContext(nullptr, nullptr);

    runContext.m_activeTestCase = mockHandle.get();



    EXPECT_EQ(runContext.getCurrentTestName(), "SampleTest");

}



TEST_F(RunContextTest_508, GetCurrentTestName_ReturnsConsistentResultsMultipleCalls_508) {

    auto mockInfo = std::make_unique<MockTestCaseInfo>();

    EXPECT_CALL(*mockInfo, name()).WillRepeatedly(::testing::Return("ConsistentTest"));



    auto mockHandle = std::make_unique<MockTestCaseHandle>(mockInfo.get(), nullptr);

    EXPECT_CALL(*mockHandle, getTestCaseInfo()).WillRepeatedly(::testing::ReturnRef(*mockInfo));



    RunContext runContext(nullptr, nullptr);

    runContext.m_activeTestCase = mockHandle.get();



    EXPECT_EQ(runContext.getCurrentTestName(), "ConsistentTest");

    EXPECT_EQ(runContext.getCurrentTestName(), "ConsistentTest");

}
