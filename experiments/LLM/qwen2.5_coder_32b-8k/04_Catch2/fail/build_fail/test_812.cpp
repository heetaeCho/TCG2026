#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_compact.hpp"



using namespace Catch;

using namespace testing;



class CompactReporterTest_812 : public Test {

protected:

    CompactReporter reporter;

};



TEST_F(CompactReporterTest_812, GetDescription_ReturnsExpectedString_812) {

    EXPECT_EQ(reporter.getDescription(), "Reports test results on a single line, suitable for IDEs");

}



TEST_F(CompactReporterTest_812, NoMatchingTestCases_DoesNotThrow_812) {

    StringRef unmatchedSpec("unmatched_spec");

    EXPECT_NO_THROW(reporter.noMatchingTestCases(unmatchedSpec));

}



TEST_F(CompactReporterTest_812, TestRunStarting_DoesNotThrow_812) {

    TestRunInfo testInfo;

    EXPECT_NO_THROW(reporter.testRunStarting(testInfo));

}



TEST_F(CompactReporterTest_812, AssertionEnded_DoesNotThrow_812) {

    AssertionStats assertionStats;

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(CompactReporterTest_812, SectionEnded_DoesNotThrow_812) {

    SectionStats sectionStats;

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

}



TEST_F(CompactReporterTest_812, TestRunEnded_DoesNotThrow_812) {

    TestRunStats testRunStats;

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}
