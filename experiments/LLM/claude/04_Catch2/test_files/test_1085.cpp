#include <catch2/reporters/catch_reporter_sonarqube.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/reporters/catch_reporter_cumulative_base.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <memory>
#include <map>
#include <string>
#include <vector>

using namespace Catch;

namespace {

// A simple IStream wrapper around a stringstream
class StringIStream : public Catch::IStream {
public:
    std::ostream& stream() override { return m_ss; }
    std::stringstream m_ss;
};

// Minimal mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
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
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class SonarQubeReporterTest_1085 : public ::testing::Test {
protected:
    std::unique_ptr<MockConfig> mockConfig;
    
    void SetUp() override {
        mockConfig = std::make_unique<MockConfig>();
        // Set up default return values for commonly called methods
        ON_CALL(*mockConfig, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, warnAboutUnmatchedTestSpecs()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig, minDuration()).WillByDefault(::testing::Return(-1.0));
        ON_CALL(*mockConfig, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig, defaultColourMode()).WillByDefault(::testing::Return(ColourMode::None));
        ON_CALL(*mockConfig, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, benchmarkSamples()).WillByDefault(::testing::Return(100));
        ON_CALL(*mockConfig, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(*mockConfig, benchmarkResamples()).WillByDefault(::testing::Return(100000));
        ON_CALL(*mockConfig, benchmarkWarmupTime()).WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    }
    
    ReporterConfig makeReporterConfig() {
        auto stream = Detail::make_unique<StringIStream>();
        return ReporterConfig(
            mockConfig.get(),
            Detail::unique_ptr<IStream>(stream.release()),
            ColourMode::None,
            std::map<std::string, std::string>{}
        );
    }
    
    std::unique_ptr<SonarQubeReporter> makeReporter() {
        return std::make_unique<SonarQubeReporter>(makeReporterConfig());
    }
};

// Test: Constructor sets shouldRedirectStdOut to true
TEST_F(SonarQubeReporterTest_1085, ConstructorSetsShouldRedirectStdOut_1085) {
    auto reporter = makeReporter();
    EXPECT_TRUE(reporter->getPreferences().shouldRedirectStdOut);
}

// Test: Constructor sets shouldReportAllAssertions to false
TEST_F(SonarQubeReporterTest_1085, ConstructorSetsShouldReportAllAssertionsFalse_1085) {
    auto reporter = makeReporter();
    EXPECT_FALSE(reporter->getPreferences().shouldReportAllAssertions);
}

// Test: getDescription returns a non-empty string
TEST_F(SonarQubeReporterTest_1085, GetDescriptionReturnsNonEmptyString_1085) {
    std::string desc = SonarQubeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: Reporter can be constructed without crashing
TEST_F(SonarQubeReporterTest_1085, ConstructionDoesNotThrow_1085) {
    EXPECT_NO_THROW(makeReporter());
}

// Test: Reporter can be destroyed without crashing
TEST_F(SonarQubeReporterTest_1085, DestructionDoesNotThrow_1085) {
    auto reporter = makeReporter();
    EXPECT_NO_THROW(reporter.reset());
}

// Test: testRunStarting can be called without crashing
TEST_F(SonarQubeReporterTest_1085, TestRunStartingDoesNotThrow_1085) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("test run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
}

// Test: Multiple reporters can be constructed from different configs
TEST_F(SonarQubeReporterTest_1085, MultipleReportersCanBeConstructed_1085) {
    auto reporter1 = makeReporter();
    auto reporter2 = makeReporter();
    EXPECT_TRUE(reporter1->getPreferences().shouldRedirectStdOut);
    EXPECT_TRUE(reporter2->getPreferences().shouldRedirectStdOut);
}

// Test: Preferences are consistent across calls
TEST_F(SonarQubeReporterTest_1085, PreferencesAreConsistent_1085) {
    auto reporter = makeReporter();
    auto prefs1 = reporter->getPreferences();
    auto prefs2 = reporter->getPreferences();
    EXPECT_EQ(prefs1.shouldRedirectStdOut, prefs2.shouldRedirectStdOut);
    EXPECT_EQ(prefs1.shouldReportAllAssertions, prefs2.shouldReportAllAssertions);
}

// Test: testRunEndedCumulative can be invoked (via testRunEnded pathway)
// This tests that the XML output is generated without crash
TEST_F(SonarQubeReporterTest_1085, TestRunEndedCumulativeDoesNotCrash_1085) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("test run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
}

// Test: getDescription returns consistent results on multiple calls
TEST_F(SonarQubeReporterTest_1085, GetDescriptionIsConsistent_1085) {
    std::string desc1 = SonarQubeReporter::getDescription();
    std::string desc2 = SonarQubeReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}

// Test: Reporter inherits CumulativeReporterBase behavior - noMatchingTestCases doesn't crash
TEST_F(SonarQubeReporterTest_1085, NoMatchingTestCasesDoesNotCrash_1085) {
    auto reporter = makeReporter();
    EXPECT_NO_THROW(reporter->noMatchingTestCases("some_spec"_catch_sr));
}

// Test: Reporter inherits CumulativeReporterBase behavior - reportInvalidTestSpec doesn't crash
TEST_F(SonarQubeReporterTest_1085, ReportInvalidTestSpecDoesNotCrash_1085) {
    auto reporter = makeReporter();
    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("invalid_spec"_catch_sr));
}

} // anonymous namespace
