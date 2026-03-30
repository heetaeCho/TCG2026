#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo & testInfo), (override));

    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo & testInfo, uint64_t partNumber), (override));

    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats & testCaseStats, uint64_t partNumber), (override));

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats & testCaseStats), (override));

};



class MockITestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, invoke, (), (const override));

};



class RunContextTest_494 : public ::testing::Test {

protected:

    NiceMock<MockIEventListener> mockReporter;

    NiceMock<MockITestInvoker> mockInvoker;

    TestCaseInfo testCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{__FILE__, __LINE__}};

    TestCaseHandle testCaseHandle{&testCaseInfo, &mockInvoker};

    Totals initialTotals;



    std::unique_ptr<IConfig> config = IConfig::makeDefaultConfig();

    RunContext runContext{config.get(), std::make_unique<MockIEventListener>(config.get())};



    void SetUp() override {

        initialTotals.testCases.passed = 0;

        initialTotals.testCases.failed = 0;



        // Setup mock expectations that are common across tests

        EXPECT_CALL(mockReporter, testCaseStarting(testCaseInfo));

        EXPECT_CALL(mockReporter, testCasePartialStarting(testCaseInfo, testing::_))

            .WillOnce(testing::Return());

        EXPECT_CALL(mockReporter, testCasePartialEnded(testing::_, testing::_))

            .WillOnce(testing::Return());

    }

};



TEST_F(RunContextTest_494, RunTest_SuccessfulRun_494) {

    // Arrange

    Totals expectedTotals = initialTotals;

    expectedTotals.testCases.passed = 1;



    // Act

    Totals result = runContext.runTest(testCaseHandle);



    // Assert

    EXPECT_EQ(result.testCases.passed, expectedTotals.testCases.passed);

}



TEST_F(RunContextTest_494, RunTest_UnsuccessfulRun_494) {

    // Arrange

    ON_CALL(mockInvoker, invoke()).WillByDefault(testing::Invoke([](){

        CATCH_INTERNAL_ERROR("Forcing test failure");

    }));

    Totals expectedTotals = initialTotals;

    expectedTotals.testCases.failed = 1;



    // Act

    Totals result = runContext.runTest(testCaseHandle);



    // Assert

    EXPECT_EQ(result.testCases.failed, expectedTotals.testCases.failed);

}



TEST_F(RunContextTest_494, RunTest_ExpectedToFailButPassed_494) {

    // Arrange

    testCaseInfo.okToFail(false);

    testCaseInfo.expectedToFail(true);



    Totals expectedTotals = initialTotals;

    expectedTotals.testCases.failed = 1;



    // Act

    Totals result = runContext.runTest(testCaseHandle);



    // Assert

    EXPECT_EQ(result.assertions.failed, 1u);

}



TEST_F(RunContextTest_494, RunTest_MultipleRunsUntilSuccess_494) {

    // Arrange

    int runCount = 0;

    ON_CALL(mockInvoker, invoke()).WillByDefault(testing::Invoke([this, &runCount]() mutable {

        if (++runCount < 3) {

            CATCH_INTERNAL_ERROR("Forcing test failure");

        }

    }));



    Totals expectedTotals = initialTotals;

    expectedTotals.testCases.passed = 1;



    // Act

    Totals result = runContext.runTest(testCaseHandle);



    // Assert

    EXPECT_EQ(result.testCases.passed, expectedTotals.testCases.passed);

}



TEST_F(RunContextTest_494, RunTest_ReportedOutput_494) {

    // Arrange

    std::string stdoutExpected = "stdout";

    std::string stderrExpected = "stderr";



    ON_CALL(mockInvoker, invoke()).WillByDefault(testing::Invoke([this, &stdoutExpected, &stderrExpected]() mutable {

        std::cout << stdoutExpected;

        std::cerr << stderrExpected;

    }));



    // Act

    Totals result = runContext.runTest(testCaseHandle);



    // Assert

    EXPECT_EQ(result.testCases.passed, 1u);

}
