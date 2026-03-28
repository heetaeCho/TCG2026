#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/catch_timer.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_config.hpp"

using namespace Catch;
using ::testing::HasSubstr;
using ::testing::Not;

namespace {

// Helper to create a minimal config for testing
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class XmlReporterTestCaseEndedTest_841 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();

        // Set default expectations
        ON_CALL(*mockConfig_, showDurations())
            .WillByDefault(::testing::Return(ShowDurations::Never));
        ON_CALL(*mockConfig_, verbosity())
            .WillByDefault(::testing::Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, includeSuccessfulResults())
            .WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, defaultColourMode())
            .WillByDefault(::testing::Return(ColourMode::None));
    }

    void TearDown() override {
        // Config ownership is managed by ReporterConfig
    }

    std::unique_ptr<XmlReporter> createReporter(std::ostream& os) {
        ReporterConfig config(mockConfig_, os, ColourMode::None, {});
        return std::make_unique<XmlReporter>(std::move(config));
    }

    TestCaseInfo makeTestCaseInfo(std::string name = "TestCase") {
        return TestCaseInfo(
            ""_sr,
            {Tag("test"_sr)},
            SourceLineInfo("file.cpp", 1)
        );
    }

    MockConfig* mockConfig_;
};

TEST_F(XmlReporterTestCaseEndedTest_841, AllAssertionsPassed_SuccessIsTrue_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("PassingTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 0;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("OverallResult"));
    EXPECT_THAT(output, HasSubstr("success=\"true\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, AssertionsFailed_SuccessIsFalse_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("FailingTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 3;
    totals.assertions.failed = 2;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("OverallResult"));
    EXPECT_THAT(output, HasSubstr("success=\"false\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, SkippedAssertionsWritten_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("SkippedTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.skipped = 3;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("skips=\"3\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, StdOutWrittenWhenNotEmpty_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("StdOutTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    std::string stdOut = "Hello from stdout";
    TestCaseStats stats(tcInfo, totals, std::string(stdOut), "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("StdOut"));
    EXPECT_THAT(output, HasSubstr("Hello from stdout"));
}

TEST_F(XmlReporterTestCaseEndedTest_841, StdErrWrittenWhenNotEmpty_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("StdErrTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    std::string stdErr = "Error message here";
    TestCaseStats stats(tcInfo, totals, "", std::string(stdErr), false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("StdErr"));
    EXPECT_THAT(output, HasSubstr("Error message here"));
}

TEST_F(XmlReporterTestCaseEndedTest_841, NoStdOutElementWhenEmpty_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("NoStdOutTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("StdOut")));
}

TEST_F(XmlReporterTestCaseEndedTest_841, NoStdErrElementWhenEmpty_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("NoStdErrTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("StdErr")));
}

TEST_F(XmlReporterTestCaseEndedTest_841, DurationWrittenWhenShowDurationsAlways_841) {
    ON_CALL(*mockConfig_, showDurations())
        .WillByDefault(::testing::Return(ShowDurations::Always));

    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("DurationTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("durationInSeconds"));
}

TEST_F(XmlReporterTestCaseEndedTest_841, DurationNotWrittenWhenShowDurationsNever_841) {
    ON_CALL(*mockConfig_, showDurations())
        .WillByDefault(::testing::Return(ShowDurations::Never));

    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("NoDurationTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("durationInSeconds")));
}

TEST_F(XmlReporterTestCaseEndedTest_841, BothStdOutAndStdErrWritten_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("BothOutputTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    std::string stdOut = "stdout content";
    std::string stdErr = "stderr content";
    TestCaseStats stats(tcInfo, totals, std::string(stdOut), std::string(stdErr), false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("StdOut"));
    EXPECT_THAT(output, HasSubstr("stdout content"));
    EXPECT_THAT(output, HasSubstr("StdErr"));
    EXPECT_THAT(output, HasSubstr("stderr content"));
}

TEST_F(XmlReporterTestCaseEndedTest_841, ZeroAssertions_SuccessIsTrue_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("ZeroAssertionsTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    // All zeroes - allOk() should return true

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("success=\"true\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, FailedButOkStillSucceeds_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("FailedButOkTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.failedButOk = 2;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    // failedButOk should still count as allOk
    EXPECT_THAT(output, HasSubstr("success=\"true\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, ZeroSkipsWritten_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("ZeroSkipsTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.skipped = 0;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("skips=\"0\""));
}

TEST_F(XmlReporterTestCaseEndedTest_841, DurationNotWrittenWhenDefaultForReporter_841) {
    ON_CALL(*mockConfig_, showDurations())
        .WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));

    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("DefaultDurationTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    TestCaseStats stats(tcInfo, totals, "", "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("durationInSeconds")));
}

TEST_F(XmlReporterTestCaseEndedTest_841, StdOutWithWhitespaceIsTrimmed_841) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("TrimTest");
    reporter->testCaseStarting(tcInfo);

    Totals totals;
    totals.assertions.passed = 1;

    std::string stdOut = "  trimmed output  ";
    TestCaseStats stats(tcInfo, totals, std::string(stdOut), "", false);
    reporter->testCaseEnded(stats);

    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("StdOut"));
    EXPECT_THAT(output, HasSubstr("trimmed output"));
}

