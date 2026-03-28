#include "catch2/reporters/catch_reporter_tap.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <string>
#include <map>
#include <vector>

using namespace Catch;

namespace {

// A simple IConfig mock/stub
class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    TestSpec const& testSpec() const override { static TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    std::vector<ReporterSpec> const& getReporterSpecs() const override {
        static std::vector<ReporterSpec> v;
        return v;
    }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> v;
        return v;
    }
    unsigned int rngSeed() const override { return 0; }
    UseColour getUseColour() const override { return UseColour::Auto; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool isOutputRedirected() const override { return false; }
    bool shouldSortTestCases() const override { return false; }
};

// A string-stream based IStream
class StringIStream : public IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class TAPReporterTest_1086 : public ::testing::Test {
protected:
    MockConfig config;

    ReporterConfig makeReporterConfig() {
        auto stream = Detail::make_unique<StringIStream>();
        m_streamPtr = stream.get();
        return ReporterConfig(
            &config,
            Detail::unique_ptr<IStream>(stream.release()),
            ColourMode::None,
            std::map<std::string, std::string>{}
        );
    }

    StringIStream* m_streamPtr = nullptr;
};

// Test that TAPReporter can be constructed successfully
TEST_F(TAPReporterTest_1086, ConstructionSucceeds_1086) {
    ASSERT_NO_THROW({
        TAPReporter reporter(makeReporterConfig());
    });
}

// Test that TAPReporter sets shouldReportAllAssertions preference to true
TEST_F(TAPReporterTest_1086, ShouldReportAllAssertionsIsTrue_1086) {
    TAPReporter reporter(makeReporterConfig());
    EXPECT_TRUE(reporter.getPreferences().shouldReportAllAssertions);
}

// Test that shouldRedirectStdOut remains default (false)
TEST_F(TAPReporterTest_1086, ShouldRedirectStdOutIsFalse_1086) {
    TAPReporter reporter(makeReporterConfig());
    EXPECT_FALSE(reporter.getPreferences().shouldRedirectStdOut);
}

// Test that getDescription returns a non-empty string
TEST_F(TAPReporterTest_1086, GetDescriptionReturnsNonEmpty_1086) {
    std::string desc = TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test testRunStarting does not throw
TEST_F(TAPReporterTest_1086, TestRunStartingDoesNotThrow_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("TestSuite"_sr);
    ASSERT_NO_THROW(reporter.testRunStarting(runInfo));
}

// Test noMatchingTestCases does not throw
TEST_F(TAPReporterTest_1086, NoMatchingTestCasesDoesNotThrow_1086) {
    TAPReporter reporter(makeReporterConfig());
    ASSERT_NO_THROW(reporter.noMatchingTestCases("someSpec"_sr));
}

// Test noMatchingTestCases produces output containing the unmatched spec
TEST_F(TAPReporterTest_1086, NoMatchingTestCasesProducesOutput_1086) {
    TAPReporter reporter(makeReporterConfig());
    reporter.noMatchingTestCases("nonexistent_test"_sr);
    std::string output = m_streamPtr->str();
    // TAP reporter should produce some output about no matching test cases
    EXPECT_FALSE(output.empty());
}

// Test testRunEnded does not throw
TEST_F(TAPReporterTest_1086, TestRunEndedDoesNotThrow_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 0;
    totals.testCases.passed = 2;
    totals.testCases.failed = 0;
    TestRunStats runStats(runInfo, totals, false);

    ASSERT_NO_THROW(reporter.testRunEnded(runStats));
}

// Test testRunEnded produces output with test plan
TEST_F(TAPReporterTest_1086, TestRunEndedProducesOutput_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 3;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_streamPtr->str();
    // TAP output should contain "1.." indicating a test plan
    EXPECT_NE(output.find("1.."), std::string::npos);
}

// Test assertionEnded with a passing assertion
TEST_F(TAPReporterTest_1086, AssertionEndedPassingProducesOk_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);

    // Create a test case and start it
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        "test_name"_sr, SourceLineInfo("file.cpp", 10),
        Tag{}, TestCaseProperties::None
    );

    // We need a proper AssertionStats - build minimal ones
    AssertionInfo assertionInfo;
    assertionInfo.macroName = "REQUIRE"_sr;
    assertionInfo.lineInfo = SourceLineInfo("file.cpp", 15);

    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));

    std::vector<MessageInfo> infoMessages;
    Counts counts;
    counts.passed = 1;
    AssertionStats assertionStats(result, infoMessages, counts);

    ASSERT_NO_THROW(reporter.assertionEnded(assertionStats));

    std::string output = m_streamPtr->str();
    // TAP: passing assertions should produce "ok" lines
    EXPECT_NE(output.find("ok"), std::string::npos);
}

// Test assertionEnded with a failing assertion
TEST_F(TAPReporterTest_1086, AssertionEndedFailingProducesNotOk_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);

    AssertionInfo assertionInfo;
    assertionInfo.macroName = "REQUIRE"_sr;
    assertionInfo.lineInfo = SourceLineInfo("file.cpp", 20);

    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));

    std::vector<MessageInfo> infoMessages;
    Counts counts;
    counts.failed = 1;
    AssertionStats assertionStats(result, infoMessages, counts);

    ASSERT_NO_THROW(reporter.assertionEnded(assertionStats));

    std::string output = m_streamPtr->str();
    // TAP: failing assertions should produce "not ok" lines
    EXPECT_NE(output.find("not ok"), std::string::npos);
}

// Test with zero totals
TEST_F(TAPReporterTest_1086, TestRunEndedWithZeroTotals_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("EmptySuite"_sr);
    reporter.testRunStarting(runInfo);

    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_streamPtr->str();
    // Should produce plan with 0 tests: "1..0"
    EXPECT_NE(output.find("1..0"), std::string::npos);
}

// Test multiple noMatchingTestCases calls
TEST_F(TAPReporterTest_1086, MultipleNoMatchingTestCases_1086) {
    TAPReporter reporter(makeReporterConfig());
    reporter.noMatchingTestCases("spec1"_sr);
    reporter.noMatchingTestCases("spec2"_sr);
    std::string output = m_streamPtr->str();
    EXPECT_FALSE(output.empty());
}

// Test that testRunEnded with aborting flag does not crash
TEST_F(TAPReporterTest_1086, TestRunEndedAbortingDoesNotThrow_1086) {
    TAPReporter reporter(makeReporterConfig());
    TestRunInfo runInfo("AbortedSuite"_sr);
    reporter.testRunStarting(runInfo);

    Totals totals;
    totals.assertions.failed = 1;
    totals.testCases.failed = 1;
    TestRunStats runStats(runInfo, totals, true);

    ASSERT_NO_THROW(reporter.testRunEnded(runStats));
}

} // anonymous namespace
