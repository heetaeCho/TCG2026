#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_tap.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.h"



using namespace Catch;



class TAPReporterTest_571 : public ::testing::Test {

protected:

    ReporterConfig config;

    TestRunInfo testInfo{"test_suite", "test_name"};

    StringRef unmatchedSpec{"unmatched_spec"};

    AssertionStats assertionStats{AssertionResult{}, "", ""};

    TestRunStats testRunStats{TestRunNode{}, 0, 0};



    TAPReporter reporter{CATCH_MOVE(config)};

};



TEST_F(TAPReporterTest_571, GetDescription_ReturnsCorrectString_571) {

    EXPECT_EQ(TAPReporter::getDescription(), "Reports test results in TAP format, suitable for test harnesses");

}



TEST_F(TAPReporterTest_571, TestRunStarting_DoesNotThrowOnValidInput_571) {

    EXPECT_NO_THROW(reporter.testRunStarting(testInfo));

}



TEST_F(TAPReporterTest_571, NoMatchingTestCases_DoesNotThrowOnValidInput_571) {

    EXPECT_NO_THROW(reporter.noMatchingTestCases(unmatchedSpec));

}



TEST_F(TAPReporterTest_571, AssertionEnded_DoesNotThrowOnValidInput_571) {

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(TAPReporterTest_571, TestRunEnded_DoesNotThrowOnValidInput_571) {

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}
