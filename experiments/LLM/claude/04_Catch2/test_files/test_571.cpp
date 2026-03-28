#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "catch2/reporters/catch_reporter_tap.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_context.hpp"

namespace {

class TAPReporterTest_571 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDescription returns a non-empty string
TEST_F(TAPReporterTest_571, GetDescriptionReturnsNonEmpty_571) {
    std::string desc = Catch::TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that getDescription returns the expected description
TEST_F(TAPReporterTest_571, GetDescriptionReturnsExpectedText_571) {
    std::string desc = Catch::TAPReporter::getDescription();
    EXPECT_EQ(desc, "Reports test results in TAP format, suitable for test harnesses");
}

// Test that getDescription is consistent across multiple calls
TEST_F(TAPReporterTest_571, GetDescriptionIsConsistent_571) {
    std::string desc1 = Catch::TAPReporter::getDescription();
    std::string desc2 = Catch::TAPReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}

// Test that getDescription contains "TAP" keyword
TEST_F(TAPReporterTest_571, GetDescriptionContainsTAP_571) {
    std::string desc = Catch::TAPReporter::getDescription();
    EXPECT_NE(desc.find("TAP"), std::string::npos);
}

// Test that getDescription mentions test harnesses
TEST_F(TAPReporterTest_571, GetDescriptionMentionsTestHarnesses_571) {
    std::string desc = Catch::TAPReporter::getDescription();
    EXPECT_NE(desc.find("test harnesses"), std::string::npos);
}

// Test construction and basic output for testRunStarting and testRunEnded
TEST_F(TAPReporterTest_571, ReporterCanBeConstructedAndUsed_571) {
    std::ostringstream oss;
    
    // We need to set up a minimal Catch2 config and reporter config
    // to construct a TAPReporter
    Catch::ConfigData configData;
    auto config = std::make_shared<Catch::Config>(configData);
    
    Catch::ReporterConfig reporterConfig(config.get(), oss, Catch::ColourMode::None, {});
    
    // Construct the reporter - should not throw
    EXPECT_NO_THROW({
        Catch::TAPReporter reporter(std::move(reporterConfig));
    });
}

// Test that testRunStarting and testRunEnded produce output
TEST_F(TAPReporterTest_571, TestRunProducesOutput_571) {
    std::ostringstream oss;
    
    Catch::ConfigData configData;
    auto config = std::make_shared<Catch::Config>(configData);
    
    Catch::ReporterConfig reporterConfig(config.get(), oss, Catch::ColourMode::None, {});
    Catch::TAPReporter reporter(std::move(reporterConfig));
    
    Catch::TestRunInfo testRunInfo("test_group");
    reporter.testRunStarting(testRunInfo);
    
    // Create TestRunStats to end the run
    Catch::Totals totals;
    Catch::TestRunStats testRunStats(testRunInfo, totals, false);
    reporter.testRunEnded(testRunStats);
    
    // After a complete run, there should be some output (at least the TAP plan line)
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test that noMatchingTestCases produces output
TEST_F(TAPReporterTest_571, NoMatchingTestCasesProducesOutput_571) {
    std::ostringstream oss;
    
    Catch::ConfigData configData;
    auto config = std::make_shared<Catch::Config>(configData);
    
    Catch::ReporterConfig reporterConfig(config.get(), oss, Catch::ColourMode::None, {});
    Catch::TAPReporter reporter(std::move(reporterConfig));
    
    reporter.noMatchingTestCases("nonexistent_test");
    
    std::string output = oss.str();
    // Should produce some diagnostic output about no matching test cases
    EXPECT_FALSE(output.empty());
}

// Test TAP plan line format (1..N) at end of run with zero tests
TEST_F(TAPReporterTest_571, TestRunEndedOutputsTPlanLine_571) {
    std::ostringstream oss;
    
    Catch::ConfigData configData;
    auto config = std::make_shared<Catch::Config>(configData);
    
    Catch::ReporterConfig reporterConfig(config.get(), oss, Catch::ColourMode::None, {});
    Catch::TAPReporter reporter(std::move(reporterConfig));
    
    Catch::TestRunInfo testRunInfo("test_group");
    reporter.testRunStarting(testRunInfo);
    
    Catch::Totals totals;
    Catch::TestRunStats testRunStats(testRunInfo, totals, false);
    reporter.testRunEnded(testRunStats);
    
    std::string output = oss.str();
    // TAP format should include a plan line like "1..0" for zero tests
    EXPECT_NE(output.find("1.."), std::string::npos);
}

} // namespace
