#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_run_context.hpp"

#include "catch_interfaces_reporter.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockReporter : public IEventListener {

public:

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef message), (override));

    MOCK_METHOD(void, sectionEnded, (const SectionStats &sectionStats), (override));

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats &testCaseStats), (override));

    MOCK_METHOD(void, testRunEnded, (const TestRunStats &testRunStats), (override));

};



class RunContextTest : public ::testing::Test {

protected:

    MockReporter mockReporter;

    std::unique_ptr<RunContext> runContext;



    RunContextTest() : runContext(std::make_unique<RunContext>(nullptr, IEventListenerPtr(&mockReporter))) {}



    TestCaseInfo createTestCaseInfo(const SourceLineInfo& lineInfo) {

        return TestCaseInfo("TestClass", NameAndTags("testName"), lineInfo);

    }



    SectionInfo createSectionInfo(const SourceLineInfo& lineInfo) {

        return SectionInfo(lineInfo, "sectionName");

    }

};



TEST_F(RunContextTest_511, HandleFatalErrorCondition_CallsReporterMethodsCorrectly_511) {

    TestCaseInfo testCaseInfo = createTestCaseInfo(SourceLineInfo(__FILE__, __LINE__));

    runContext->m_activeTestCase = &testCaseInfo;



    SectionInfo sectionInfo = createSectionInfo(SourceLineInfo(__FILE__, __LINE__));

    runContext->m_activeSections.push_back(&sectionInfo);



    EXPECT_CALL(mockReporter, fatalErrorEncountered(_)).Times(1);

    EXPECT_CALL(mockReporter, sectionEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, testCaseEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, testRunEnded(_)).Times(1);



    runContext->handleFatalErrorCondition("Test fatal error message");

}



TEST_F(RunContextTest_511, HandleFatalErrorCondition_UpdatesTotalsCorrectly_511) {

    TestCaseInfo testCaseInfo = createTestCaseInfo(SourceLineInfo(__FILE__, __LINE__));

    runContext->m_activeTestCase = &testCaseInfo;



    SectionInfo sectionInfo = createSectionInfo(SourceLineInfo(__FILE__, __LINE__));

    runContext->m_activeSections.push_back(&sectionInfo);



    Totals initialTotals = runContext->m_totals;

    runContext->handleFatalErrorCondition("Test fatal error message");



    EXPECT_EQ(runContext->m_totals.testCases.failed, initialTotals.testCases.failed + 1);

    EXPECT_EQ(runContext->m_totals.assertions.failed, initialTotals.assertions.failed + 1);

}
