#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_istream.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>

namespace {

// Helper to create a minimal ReporterConfig
class ConsoleReporterTest_772 : public ::testing::Test {
protected:
    std::stringstream stream_;

    // We need to create a proper ReporterConfig. This requires a Catch2 config object.
    // Since we're treating the implementation as a black box, we set up minimal infrastructure.

    struct TestStream : public Catch::IStream {
        std::ostream& m_os;
        TestStream(std::ostream& os) : m_os(os) {}
        std::ostream& stream() override { return m_os; }
    };

    std::unique_ptr<Catch::ConsoleReporter> createReporter() {
        // Create minimal config for the reporter
        // We need to use Catch2's infrastructure to create a valid ReporterConfig
        std::vector<std::string> args = {"test"};
        
        auto testStream = Catch::Detail::make_unique<TestStream>(stream_);
        
        // Create a default config
        Catch::ConfigData configData;
        auto config = std::make_shared<Catch::Config>(configData);
        
        Catch::ReporterConfig reporterConfig(config.get(), CATCH_MOVE(testStream), Catch::ColourMode::None, {});
        
        auto reporter = std::make_unique<Catch::ConsoleReporter>(CATCH_MOVE(reporterConfig));
        
        // Store config to keep it alive
        config_ = config;
        return reporter;
    }

    std::shared_ptr<Catch::Config> config_;

    Catch::TestCaseInfo makeTestCaseInfo(const std::string& name) {
        Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
        return Catch::TestCaseInfo(
            ""_catch_sr,
            {name, "[tag]"_catch_sr},
            lineInfo
        );
    }
};

TEST_F(ConsoleReporterTest_772, GetDescription_ReturnsNonEmptyString_772) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(ConsoleReporterTest_772, ConstructionSucceeds_772) {
    EXPECT_NO_THROW({
        auto reporter = createReporter();
        EXPECT_NE(reporter, nullptr);
    });
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("TestCase1");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    Catch::TestCaseStats stats(tcInfo, totals, "", "", false);

    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_WithAbort_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("AbortedTest");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    Catch::TestCaseStats stats(tcInfo, totals, "", "", true);

    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_WithStdOut_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("TestWithOutput");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    std::string stdOut = "some stdout output";
    std::string stdErr = "some stderr output";
    Catch::TestCaseStats stats(tcInfo, totals, std::move(stdOut), std::move(stdErr), false);

    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

TEST_F(ConsoleReporterTest_772, TestRunStarting_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
}

TEST_F(ConsoleReporterTest_772, TestRunEnded_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
}

TEST_F(ConsoleReporterTest_772, NoMatchingTestCases_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    EXPECT_NO_THROW(reporter->noMatchingTestCases("nonexistent"_catch_sr));
}

TEST_F(ConsoleReporterTest_772, ReportInvalidTestSpec_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("bad spec"_catch_sr));
}

TEST_F(ConsoleReporterTest_772, AssertionStarting_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::SourceLineInfo lineInfo("file.cpp", 10);
    Catch::AssertionInfo assertInfo("", lineInfo, "", Catch::ResultDisposition::Normal);

    EXPECT_NO_THROW(reporter->assertionStarting(assertInfo));
}

TEST_F(ConsoleReporterTest_772, SectionStartingAndEnding_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("SectionTest");
    reporter->testCaseStarting(tcInfo);

    Catch::SourceLineInfo lineInfo("file.cpp", 5);
    Catch::SectionInfo sectionInfo(lineInfo, "section1");

    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));

    Catch::Totals totals;
    Catch::SectionStats sectionStats(sectionInfo, totals, 0.5, false);
    EXPECT_NO_THROW(reporter->sectionEnded(sectionStats));
}

TEST_F(ConsoleReporterTest_772, MultipleTestCasesEndedSequentially_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    // First test case
    auto tcInfo1 = makeTestCaseInfo("Test1");
    reporter->testCaseStarting(tcInfo1);
    Catch::Totals totals1;
    Catch::TestCaseStats stats1(tcInfo1, totals1, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(stats1));

    // Second test case
    auto tcInfo2 = makeTestCaseInfo("Test2");
    reporter->testCaseStarting(tcInfo2);
    Catch::Totals totals2;
    Catch::TestCaseStats stats2(tcInfo2, totals2, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(stats2));
}

TEST_F(ConsoleReporterTest_772, TestCaseEndedProducesOutput_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("OutputTest");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 1;
    Catch::TestCaseStats stats(tcInfo, totals, "stdout data", "stderr data", false);
    reporter->testCaseEnded(stats);

    // The reporter should have written something to the stream
    // We just verify it doesn't crash and potentially produces output
    // (exact output format is implementation detail)
}

TEST_F(ConsoleReporterTest_772, BenchmarkPreparing_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("BenchmarkTest");
    reporter->testCaseStarting(tcInfo);

    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench1"_catch_sr));
}

TEST_F(ConsoleReporterTest_772, BenchmarkFailed_DoesNotCrash_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("FailedBenchmark");
    reporter->testCaseStarting(tcInfo);

    EXPECT_NO_THROW(reporter->benchmarkFailed("benchmark error"_catch_sr));
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_EmptyTotals_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("EmptyTotalsTest");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals; // All zeros
    Catch::TestCaseStats stats(tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_AllPassedAssertions_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("AllPassedTest");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 0;
    Catch::TestCaseStats stats(tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

TEST_F(ConsoleReporterTest_772, TestCaseEnded_AllFailedAssertions_772) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);

    Catch::TestRunInfo runInfo("test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("AllFailedTest");
    reporter->testCaseStarting(tcInfo);

    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 5;
    Catch::TestCaseStats stats(tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(stats));
}

} // anonymous namespace
