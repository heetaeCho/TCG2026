#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;



class CumulativeReporterBaseTest_860 : public ::testing::Test {

protected:

    ReporterConfig config;

    CumulativeReporterBase reporter;



    CumulativeReporterBaseTest_860() : reporter(CATCH_MOVE(config)) {}



    TestCaseStats createTestCaseStats(const std::string& name, const std::string& stdout = "", const std::string& stderr = "", bool aborting = false) {

        TestCaseInfo testInfo(name, "", 0, "");

        Totals totals;

        return TestCaseStats(testInfo, totals, CATCH_MOVE(stdout), CATCH_MOVE(stderr), aborting);

    }

};



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_StoresTestCaseNode_860) {

    auto testCaseStats = createTestCaseStats("Test Case 1", "stdout content", "stderr content");

    reporter.testCaseEnded(testCaseStats);



    ASSERT_EQ(reporter.m_testCases.size(), 1);

    EXPECT_EQ(reporter.m_testCases[0]->value.stdOut, "stdout content");

    EXPECT_EQ(reporter.m_testCases[0]->value.stdErr, "stderr content");

}



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_AssertsOnNonEmptySectionStack_860) {

    reporter.m_sectionStack.push_back(nullptr);



    auto testCaseStats = createTestCaseStats("Test Case 1");

    EXPECT_DEATH(reporter.testCaseEnded(testCaseStats), ".*assertion failed: m_sectionStack.size() == 0.*");

}



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_AssertsOnNullDeepestSection_860) {

    reporter.m_deepestSection = nullptr;



    auto testCaseStats = createTestCaseStats("Test Case 1");

    EXPECT_DEATH(reporter.testCaseEnded(testCaseStats), ".*assertion failed: m_deepestSection.*");

}



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_UpdatesDeepestSectionOutput_860) {

    reporter.m_deepestSection = new SectionNode(SectionStats());



    auto testCaseStats = createTestCaseStats("Test Case 1", "stdout content", "stderr content");

    reporter.testCaseEnded(testCaseStats);



    EXPECT_EQ(reporter.m_deepestSection->stats.stdOut, "stdout content");

    EXPECT_EQ(reporter.m_deepestSection->stats.stdErr, "stderr content");



    delete reporter.m_deepestSection;

}



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_HandlesEmptyStdoutAndStderr_860) {

    auto testCaseStats = createTestCaseStats("Test Case 1", "", "");

    reporter.testCaseEnded(testCaseStats);



    ASSERT_EQ(reporter.m_testCases.size(), 1);

    EXPECT_EQ(reporter.m_testCases[0]->value.stdOut, "");

    EXPECT_EQ(reporter.m_testCases[0]->value.stdErr, "");

}



TEST_F(CumulativeReporterBaseTest_860, TestCaseEnded_HandlesAbortingTestCase_860) {

    auto testCaseStats = createTestCaseStats("Test Case 1", "", "", true);

    reporter.testCaseEnded(testCaseStats);



    ASSERT_EQ(reporter.m_testCases.size(), 1);

    EXPECT_TRUE(reporter.m_testCases[0]->value.aborting);

}
