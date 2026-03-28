#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_tap.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



class TAPReporterTest : public ::testing::Test {

protected:

    MockIConfig mockConfig;

    Detail::unique_ptr<IStream> mockStream = Detail::make_unique<MockIStream>();

    ReporterConfig config{&mockConfig, CATCH_MOVE(mockStream), ColourMode::None, {}};

    TAPReporter reporter{CATCH_MOVE(config)};

};



TEST_F(TAPReporterTest_1086, ConstructorSetsShouldReportAllAssertionsToTrue_1086) {

    EXPECT_TRUE(reporter.getPreferences().shouldReportAllAssertions);

}



TEST_F(TAPReporterTest_1086, TestRunStartingDoesNotThrow_1086) {

    TestRunInfo testRunInfo{"Sample Test Run"};

    EXPECT_NO_THROW(reporter.testRunStarting(testRunInfo));

}



TEST_F(TAPReporterTest_1086, NoMatchingTestCasesDoesNotThrow_1086) {

    StringRef unmatchedSpec = "No matching spec";

    EXPECT_NO_THROW(reporter.noMatchingTestCases(unmatchedSpec));

}



TEST_F(TAPReporterTest_1086, AssertionEndedDoesNotThrow_1086) {

    AssertionStats assertionStats;

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(TAPReporterTest_1086, TestRunEndedDoesNotThrow_1086) {

    TestRunStats testRunStats;

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}
