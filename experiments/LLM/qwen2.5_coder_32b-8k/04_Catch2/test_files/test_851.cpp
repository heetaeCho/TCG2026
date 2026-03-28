#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_streaming_base.hpp"



using namespace Catch;



class StreamingReporterBaseTest_851 : public ::testing::Test {

protected:

    StreamingReporterBase* reporter;

    TestRunInfo testRunInfo;



    StreamingReporterBaseTest_851() : testRunInfo(StringRef("SampleTestRun")) {}



    void SetUp() override {

        ReporterConfig config; // Assuming default configuration for testing purposes

        reporter = new StreamingReporterBase(std::move(config));

    }



    void TearDown() override {

        delete reporter;

    }

};



TEST_F(StreamingReporterBaseTest_851, TestRunStartingSetsCurrentTestRunInfo_851) {

    reporter->testRunStarting(testRunInfo);

    EXPECT_EQ(reporter->currentTestRunInfo.name, testRunInfo.name);

}



TEST_F(StreamingReporterBaseTest_851, TestRunStartingWithEmptyNameSetsDefault_851) {

    TestRunInfo emptyTestRunInfo(StringRef(""));

    reporter->testRunStarting(emptyTestRunInfo);

    EXPECT_EQ(reporter->currentTestRunInfo.name, "test run has not started yet"_sr);

}



TEST_F(StreamingReporterBaseTest_851, TestRunEndingDoesNotThrowException_851) {

    TestRunStats stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->testRunEnded(stats));

}



TEST_F(StreamingReporterBaseTest_851, BenchmarkPreparingDoesNotThrowException_851) {

    EXPECT_NO_THROW(reporter->benchmarkPreparing(StringRef("BenchmarkName")));

}



TEST_F(StreamingReporterBaseTest_851, BenchmarkStartingDoesNotThrowException_851) {

    BenchmarkInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

}



TEST_F(StreamingReporterBaseTest_851, BenchmarkEndedDoesNotThrowException_851) {

    BenchmarkStats<> stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->benchmarkEnded(stats));

}



TEST_F(StreamingReporterBaseTest_851, BenchmarkFailedDoesNotThrowException_851) {

    EXPECT_NO_THROW(reporter->benchmarkFailed(StringRef("BenchmarkFailureMessage")));

}



TEST_F(StreamingReporterBaseTest_851, FatalErrorEncounteredDoesNotThrowException_851) {

    EXPECT_NO_THROW(reporter->fatalErrorEncountered(StringRef("FatalErrorMessage")));

}



TEST_F(StreamingReporterBaseTest_851, NoMatchingTestCasesDoesNotThrowException_851) {

    EXPECT_NO_THROW(reporter->noMatchingTestCases(StringRef("UnmatchedSpec")));

}



TEST_F(StreamingReporterBaseTest_851, ReportInvalidTestSpecDoesNotThrowException_851) {

    EXPECT_NO_THROW(reporter->reportInvalidTestSpec(StringRef("InvalidArgument")));

}



TEST_F(StreamingReporterBaseTest_851, TestCaseStartingDoesNotThrowException_851) {

    TestCaseInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->testCaseStarting(info));

}



TEST_F(StreamingReporterBaseTest_851, TestCasePartialStartingDoesNotThrowException_851) {

    TestCaseInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->testCasePartialStarting(info, 0));

}



TEST_F(StreamingReporterBaseTest_851, SectionStartingDoesNotThrowException_851) {

    SectionInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->sectionStarting(info));

}



TEST_F(StreamingReporterBaseTest_851, AssertionStartingDoesNotThrowException_851) {

    AssertionInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->assertionStarting(info));

}



TEST_F(StreamingReporterBaseTest_851, AssertionEndedDoesNotThrowException_851) {

    AssertionStats stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->assertionEnded(stats));

}



TEST_F(StreamingReporterBaseTest_851, SectionEndedDoesNotThrowException_851) {

    SectionStats stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->sectionEnded(stats));

}



TEST_F(StreamingReporterBaseTest_851, TestCasePartialEndedDoesNotThrowException_851) {

    TestCaseStats stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->testCasePartialEnded(stats, 0));

}



TEST_F(StreamingReporterBaseTest_851, TestCaseEndedDoesNotThrowException_851) {

    TestCaseStats stats; // Assuming default stats for testing purposes

    EXPECT_NO_THROW(reporter->testCaseEnded(stats));

}



TEST_F(StreamingReporterBaseTest_851, SkipTestDoesNotThrowException_851) {

    TestCaseInfo info; // Assuming default info for testing purposes

    EXPECT_NO_THROW(reporter->skipTest(info));

}
