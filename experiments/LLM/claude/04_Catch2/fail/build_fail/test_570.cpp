#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal config for the reporter
class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    unsigned int rngSeed() const override { return 0; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getReporterSpecs() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override {
        return std::chrono::milliseconds(100);
    }
    std::ostream& stream() const override {
        static std::ostringstream oss;
        return oss;
    }
    bool isFiltered() const override { return false; }
    bool includeSuccessfulResults() const override { return false; }
};

// Helper function to create a ReporterConfig
ReporterConfig makeReporterConfig(std::ostream& os) {
    static auto config = std::make_shared<MockConfig>();
    return ReporterConfig(config.get(), os, ColourMode::None, {});
}

} // anonymous namespace

class SonarQubeReporterTest_570 : public ::testing::Test {
protected:
    std::ostringstream oss;
    
    std::unique_ptr<SonarQubeReporter> createReporter() {
        auto config = makeReporterConfig(oss);
        return std::make_unique<SonarQubeReporter>(std::move(config));
    }
};

TEST_F(SonarQubeReporterTest_570, GetDescription_ReturnsNonEmptyString_570) {
    std::string desc = SonarQubeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(SonarQubeReporterTest_570, ConstructorDoesNotThrow_570) {
    EXPECT_NO_THROW(createReporter());
}

TEST_F(SonarQubeReporterTest_570, TestRunStartingProducesOutput_570) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
    // After testRunStarting, some XML should be started
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(SonarQubeReporterTest_570, TestRunStartingContainsXmlDeclaration_570) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    std::string output = oss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("<?xml"));
}

TEST_F(SonarQubeReporterTest_570, TestRunStartingContainsTestExecutions_570) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    std::string output = oss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("testExecutions"));
}

TEST_F(SonarQubeReporterTest_570, FullTestRunProducesValidXml_570) {
    auto reporter = createReporter();
    
    // Start the test run
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    // Create a simple test case
    TestCaseInfo testCaseInfo(
        "", {"test_case_name", "[tag]"}, {"test_file.cpp", 10});
    
    reporter->testCaseStarting(testCaseInfo);
    
    SectionInfo sectionInfo({"test_file.cpp", 10}, "test_case_name");
    reporter->sectionStarting(sectionInfo);
    
    // Create assertion info
    AssertionInfo assertionInfo(
        "test_expr", {"test_file.cpp", 10}, "REQUIRE");
    
    // Create a passing assertion result
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertionInfo, std::move(resultData));
    
    Counts counts;
    counts.passed = 1;
    AssertionStats assertionStats(result, {}, counts);
    reporter->assertionEnded(assertionStats);
    
    SectionStats sectionStats(sectionInfo, counts, 0.1, false);
    reporter->sectionEnded(sectionStats);
    
    TestCaseStats testCaseStats(testCaseInfo, {counts, 0.1}, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    // End the test run
    Totals totals;
    totals.assertions = counts;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_THAT(output, ::testing::HasSubstr("testExecutions"));
}

TEST_F(SonarQubeReporterTest_570, EmptyTestRunProducesOutput_570) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("empty_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(SonarQubeReporterTest_570, OutputContainsVersionAttribute_570) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    std::string output = oss.str();
    EXPECT_THAT(output, ::testing::HasSubstr("version"));
}

TEST_F(SonarQubeReporterTest_570, FailedAssertionInTestRun_570) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    TestCaseInfo testCaseInfo(
        "", {"failing_test", "[tag]"}, {"test_file.cpp", 20});
    
    reporter->testCaseStarting(testCaseInfo);
    
    SectionInfo sectionInfo({"test_file.cpp", 20}, "failing_test");
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertionInfo(
        "x == 5", {"test_file.cpp", 25}, "REQUIRE");
    
    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertionInfo, std::move(resultData));
    
    Counts counts;
    counts.failed = 1;
    AssertionStats assertionStats(result, {}, counts);
    reporter->assertionEnded(assertionStats);
    
    SectionStats sectionStats(sectionInfo, counts, 0.05, false);
    reporter->sectionEnded(sectionStats);
    
    TestCaseStats testCaseStats(testCaseInfo, {counts, 0.05}, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    Totals totals;
    totals.assertions = counts;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain failure information
    EXPECT_THAT(output, ::testing::HasSubstr("failure"));
}

TEST_F(SonarQubeReporterTest_570, MultipleTestCasesInRun_570) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("multi_test_run");
    reporter->testRunStarting(runInfo);
    
    // First test case
    {
        TestCaseInfo testCaseInfo(
            "", {"test1", "[tag]"}, {"file1.cpp", 10});
        reporter->testCaseStarting(testCaseInfo);
        SectionInfo sectionInfo({"file1.cpp", 10}, "test1");
        reporter->sectionStarting(sectionInfo);
        
        Counts counts;
        counts.passed = 1;
        SectionStats sectionStats(sectionInfo, counts, 0.01, false);
        reporter->sectionEnded(sectionStats);
        TestCaseStats testCaseStats(testCaseInfo, {counts, 0.01}, "", "", false);
        reporter->testCaseEnded(testCaseStats);
    }
    
    // Second test case
    {
        TestCaseInfo testCaseInfo(
            "", {"test2", "[tag]"}, {"file2.cpp", 20});
        reporter->testCaseStarting(testCaseInfo);
        SectionInfo sectionInfo({"file2.cpp", 20}, "test2");
        reporter->sectionStarting(sectionInfo);
        
        Counts counts;
        counts.passed = 1;
        SectionStats sectionStats(sectionInfo, counts, 0.02, false);
        reporter->sectionEnded(sectionStats);
        TestCaseStats testCaseStats(testCaseInfo, {counts, 0.02}, "", "", false);
        reporter->testCaseEnded(testCaseStats);
    }
    
    Totals totals;
    totals.assertions.passed = 2;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Output should reference the test file names
    EXPECT_THAT(output, ::testing::HasSubstr("file"));
}

TEST_F(SonarQubeReporterTest_570, OutputContainsClosingTag_570) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = oss.str();
    // Should have closing testExecutions tag
    EXPECT_THAT(output, ::testing::HasSubstr("</testExecutions>"));
}

TEST_F(SonarQubeReporterTest_570, NoMatchingTestCasesDoesNotThrow_570) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->noMatchingTestCases("some_spec"));
}

TEST_F(SonarQubeReporterTest_570, ReportInvalidTestSpecDoesNotThrow_570) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("invalid_spec"));
}

TEST_F(SonarQubeReporterTest_570, SkipTestDoesNotThrow_570) {
    auto reporter = createReporter();
    TestCaseInfo testCaseInfo(
        "", {"skipped_test", "[skip]"}, {"skip_file.cpp", 1});
    EXPECT_NO_THROW(reporter->skipTest(testCaseInfo));
}

TEST_F(SonarQubeReporterTest_570, GetDescriptionContent_570) {
    std::string desc = SonarQubeReporter::getDescription();
    // The description should mention SonarQube in some form
    // This is a reasonable expectation for a SonarQube reporter
    EXPECT_THAT(desc, ::testing::AnyOf(
        ::testing::HasSubstr("SonarQube"),
        ::testing::HasSubstr("sonarqube"),
        ::testing::HasSubstr("Sonar")));
}
