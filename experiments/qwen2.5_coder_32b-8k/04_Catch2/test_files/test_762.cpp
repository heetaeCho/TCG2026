#include <gtest/gtest.h>

#include "catch_reporter_console.hpp"



using namespace Catch;



class ConsoleReporterTest_762 : public ::testing::Test {

protected:

    ReporterConfig config;

    ConsoleReporter reporter{std::move(config)};

};



TEST_F(ConsoleReporterTest_762, GetDescription_ReturnsCorrectString_762) {

    EXPECT_EQ(reporter.getDescription(), "Reports test results as plain lines of text");

}



TEST_F(ConsoleReporterTest_762, NoMatchingTestCases_DoesNotThrow_762) {

    StringRef unmatchedSpec("unmatched_spec");

    EXPECT_NO_THROW(reporter.noMatchingTestCases(unmatchedSpec));

}



TEST_F(ConsoleReporterTest_762, ReportInvalidTestSpec_DoesNotThrow_762) {

    StringRef arg("invalid_spec");

    EXPECT_NO_THROW(reporter.reportInvalidTestSpec(arg));

}



TEST_F(ConsoleReporterTest_762, AssertionStarting_DoesNotThrow_762) {

    AssertionInfo info;

    EXPECT_NO_THROW(reporter.assertionStarting(info));

}



TEST_F(ConsoleReporterTest_762, AssertionEnded_DoesNotThrow_762) {

    AssertionStats stats;

    EXPECT_NO_THROW(reporter.assertionEnded(stats));

}



TEST_F(ConsoleReporterTest_762, SectionStarting_DoesNotThrow_762) {

    SectionInfo info;

    EXPECT_NO_THROW(reporter.sectionStarting(info));

}



TEST_F(ConsoleReporterTest_762, SectionEnded_DoesNotThrow_762) {

    SectionStats stats;

    EXPECT_NO_THROW(reporter.sectionEnded(stats));

}



TEST_F(ConsoleReporterTest_762, BenchmarkPreparing_DoesNotThrow_762) {

    StringRef name("benchmark_name");

    EXPECT_NO_THROW(reporter.benchmarkPreparing(name));

}



TEST_F(ConsoleReporterTest_762, BenchmarkStarting_DoesNotThrow_762) {

    BenchmarkInfo info;

    EXPECT_NO_THROW(reporter.benchmarkStarting(info));

}



TEST_F(ConsoleReporterTest_762, BenchmarkEnded_DoesNotThrow_762) {

    BenchmarkStats<> stats;

    EXPECT_NO_THROW(reporter.benchmarkEnded(stats));

}



TEST_F(ConsoleReporterTest_762, BenchmarkFailed_DoesNotThrow_762) {

    StringRef error("benchmark_error");

    EXPECT_NO_THROW(reporter.benchmarkFailed(error));

}



TEST_F(ConsoleReporterTest_762, TestCaseEnded_DoesNotThrow_762) {

    TestCaseStats stats;

    EXPECT_NO_THROW(reporter.testCaseEnded(stats));

}



TEST_F(ConsoleReporterTest_762, TestRunStarting_DoesNotThrow_762) {

    TestRunInfo info;

    EXPECT_NO_THROW(reporter.testRunStarting(info));

}



TEST_F(ConsoleReporterTest_762, TestRunEnded_DoesNotThrow_762) {

    TestRunStats stats;

    EXPECT_NO_THROW(reporter.testRunEnded(stats));

}
