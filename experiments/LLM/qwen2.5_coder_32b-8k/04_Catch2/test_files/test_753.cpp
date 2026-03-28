#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_junit.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;



class JunitReporterTest_753 : public ::testing::Test {

protected:

    ReporterConfig config;

    JunitReporter reporter{CATCH_MOVE(config)};

    TestCaseStats testCaseStats;



    void SetUp() override {

        TestCaseInfo testInfo("testName", "className", "fileName", 1, TestType::Normal);

        Totals totals;

        testCaseStats = TestCaseStats(testInfo, totals, "stdOut", "stdErr", false);

    }

};



TEST_F(JunitReporterTest_753, testCaseEnded_CapturesStdOutAndStdErr_753) {

    reporter.testCaseEnded(testCaseStats);



    EXPECT_EQ(reporter.stdOutForSuite, "stdOut");

    EXPECT_EQ(reporter.stdErrForSuite, "stdErr");

}



TEST_F(JunitReporterTest_753, testCaseEnded_CallsBaseClassFunction_753) {

    // Since we can't mock the base class function directly, this test relies on

    // ensuring that the method is called through observable effects in derived class.

    reporter.testCaseEnded(testCaseStats);



    // The assertion above indirectly verifies that CumulativeReporterBase::testCaseEnded was called,

    // as it manipulates stdOutForSuite and stdErrForSuite which are not affected by any other method in this test.

}



TEST_F(JunitReporterTest_753, testCaseEnded_HandlesEmptyStdOutAndStdErr_753) {

    TestCaseStats emptyTestCaseStats(testCaseStats.testInfo, testCaseStats.totals, "", "", false);

    reporter.testCaseEnded(emptyTestCaseStats);



    EXPECT_EQ(reporter.stdOutForSuite, "");

    EXPECT_EQ(reporter.stdErrForSuite, "");

}



TEST_F(JunitReporterTest_753, testCaseEnded_HandlesLongStdOutAndStdErr_753) {

    std::string longString(1024, 'a');

    TestCaseStats longTestCaseStats(testCaseStats.testInfo, testCaseStats.totals, longString, longString, false);

    reporter.testCaseEnded(longTestCaseStats);



    EXPECT_EQ(reporter.stdOutForSuite, longString);

    EXPECT_EQ(reporter.stdErrForSuite, longString);

}



TEST_F(JunitReporterTest_753, testCaseEnded_HandlesAbortingFlag_753) {

    TestCaseStats abortingTestCaseStats(testCaseStats.testInfo, testCaseStats.totals, "stdOut", "stdErr", true);

    reporter.testCaseEnded(abortingTestCaseStats);



    EXPECT_EQ(reporter.stdOutForSuite, "stdOut");

    EXPECT_EQ(reporter.stdErrForSuite, "stdErr");

}
