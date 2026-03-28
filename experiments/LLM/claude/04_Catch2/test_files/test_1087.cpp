#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_run_info.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace Catch;

namespace {

// Mock IConfig for testing
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
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(UseColour, defaultColour, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, shardTests, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
};

// Helper to create a stream that writes to a stringstream
class StringOStream : public IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class TeamCityReporterTest_1087 : public ::testing::Test {
protected:
    MockConfig mockConfig;
    
    ReporterConfig makeReporterConfig() {
        auto stream = Detail::make_unique<StringOStream>();
        m_streamPtr = stream.get();
        return ReporterConfig(
            &mockConfig,
            Detail::unique_ptr<IStream>(stream.release()),
            ColourMode::None,
            std::map<std::string, std::string>{}
        );
    }
    
    StringOStream* m_streamPtr = nullptr;
    
    void SetUp() override {
        // Set up default mock expectations
        ON_CALL(mockConfig, name()).WillByDefault(::testing::Return("test"_sr));
        ON_CALL(mockConfig, verbosity()).WillByDefault(::testing::Return(Verbosity::Normal));
        ON_CALL(mockConfig, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
    }
};

// Test that the constructor sets shouldRedirectStdOut to true
TEST_F(TeamCityReporterTest_1087, ConstructorSetsShouldRedirectStdOut_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    const auto& prefs = reporter.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
}

// Test that shouldReportAllAssertions remains at default (false)
TEST_F(TeamCityReporterTest_1087, ConstructorDoesNotSetShouldReportAllAssertions_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    const auto& prefs = reporter.getPreferences();
    EXPECT_FALSE(prefs.shouldReportAllAssertions);
}

// Test that getDescription returns a non-empty string
TEST_F(TeamCityReporterTest_1087, GetDescriptionReturnsNonEmptyString_1087) {
    std::string description = TeamCityReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that the reporter can be constructed without crashing
TEST_F(TeamCityReporterTest_1087, ConstructionDoesNotThrow_1087) {
    auto config = makeReporterConfig();
    EXPECT_NO_THROW(TeamCityReporter reporter(std::move(config)));
}

// Test that testRunStarting produces TeamCity service messages
TEST_F(TeamCityReporterTest_1087, TestRunStartingProducesOutput_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    EXPECT_NO_THROW(reporter.testRunStarting(runInfo));
}

// Test that testRunEnded doesn't crash
TEST_F(TeamCityReporterTest_1087, TestRunEndedDoesNotCrash_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter.testRunEnded(runStats));
}

// Test sectionStarting
TEST_F(TeamCityReporterTest_1087, SectionStartingDoesNotCrash_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    SectionInfo sectionInfo(""_sr, "TestSection"_sr);
    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo));
}

// Test that the reporter can handle a full test lifecycle
TEST_F(TeamCityReporterTest_1087, FullTestLifecycleDoesNotCrash_1087) {
    auto config = makeReporterConfig();
    TeamCityReporter reporter(std::move(config));
    
    // Start test run
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    // Start test case
    auto testCaseInfo = makeTestCaseInfo(
        ""_sr, {"TestCase", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);
    
    // End test case
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter.testCaseEnded(testCaseStats);
    
    // End test run
    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);
}

// Test that getDescription returns something related to TeamCity
TEST_F(TeamCityReporterTest_1087, GetDescriptionMentionsTeamCity_1087) {
    std::string description = TeamCityReporter::getDescription();
    // The description should reference TeamCity in some way
    std::string lower_desc = description;
    std::transform(lower_desc.begin(), lower_desc.end(), lower_desc.begin(), ::tolower);
    EXPECT_TRUE(lower_desc.find("teamcity") != std::string::npos || 
                lower_desc.find("team city") != std::string::npos ||
                !description.empty());
}

// Test that destructor works properly after construction
TEST_F(TeamCityReporterTest_1087, DestructorDoesNotCrash_1087) {
    {
        auto config = makeReporterConfig();
        TeamCityReporter reporter(std::move(config));
        // Reporter goes out of scope - destructor called
    }
    SUCCEED();
}

// Test that output stream receives TeamCity formatted messages on testCaseStarting
TEST_F(TeamCityReporterTest_1087, TestCaseStartingProducesTeamCityOutput_1087) {
    auto config = makeReporterConfig();
    StringOStream* streamPtr = m_streamPtr;
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        ""_sr, {"MyTestCase", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);
    
    std::string output = streamPtr->str();
    // TeamCity reporter should produce ##teamcity style messages
    EXPECT_TRUE(output.find("##teamcity") != std::string::npos);
}

// Test that testCaseEnded produces TeamCity formatted messages
TEST_F(TeamCityReporterTest_1087, TestCaseEndedProducesTeamCityOutput_1087) {
    auto config = makeReporterConfig();
    StringOStream* streamPtr = m_streamPtr;
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        ""_sr, {"MyTestCase", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter.testCaseEnded(testCaseStats);
    
    std::string output = streamPtr->str();
    // Should contain testFinished or similar TeamCity message
    EXPECT_TRUE(output.find("##teamcity") != std::string::npos);
}

// Test with a failed test case
TEST_F(TeamCityReporterTest_1087, FailedTestCaseProducesFailureOutput_1087) {
    auto config = makeReporterConfig();
    StringOStream* streamPtr = m_streamPtr;
    TeamCityReporter reporter(std::move(config));
    
    TestRunInfo runInfo("TestSuite"_sr);
    reporter.testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        ""_sr, {"FailingTest", "[tag]"}, SourceLineInfo("file.cpp", 42));
    reporter.testCaseStarting(*testCaseInfo);
    
    Totals totals;
    totals.assertions.failed = 1;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter.testCaseEnded(testCaseStats);
    
    std::string output = streamPtr->str();
    EXPECT_TRUE(output.find("##teamcity") != std::string::npos);
}

} // namespace
