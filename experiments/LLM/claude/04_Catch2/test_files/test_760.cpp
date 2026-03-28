#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_console_colour.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>

namespace {

// Since TablePrinter is an internal detail of Catch2's console reporter,
// we test it through the ConsoleReporter's public interface where possible.

class ConsoleReporterTest_760 : public ::testing::Test {
protected:
    void SetUp() override {
        stream_ = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<std::ostringstream> stream_;
};

// Test that ConsoleReporter can be instantiated with valid config
TEST_F(ConsoleReporterTest_760, CanBeInstantiated_760) {
    // Create a minimal Catch2 configuration
    Catch::ConfigData configData;
    configData.showDurations = Catch::ShowDurations::Never;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    
    EXPECT_NO_THROW({
        Catch::ConsoleReporter reporter(reporterConfig);
    });
}

// Test that ConsoleReporter produces output for test run start
TEST_F(ConsoleReporterTest_760, TestRunStartProducesOutput_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    EXPECT_NO_THROW(reporter.testRunStarting(runInfo));
}

// Test that ConsoleReporter handles test case starting
TEST_F(ConsoleReporterTest_760, TestCaseStartDoesNotThrow_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestCaseInfo testInfo("", {"test_name", "[tag]"}, {"file.cpp", 1});
    EXPECT_NO_THROW(reporter.testCaseStarting(testInfo));
}

// Test that ConsoleReporter handles section starting
TEST_F(ConsoleReporterTest_760, SectionStartDoesNotThrow_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::SectionInfo sectionInfo({"file.cpp", 1}, "section_name");
    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo));
}

// Test that ConsoleReporter handles test run ended and produces summary output
TEST_F(ConsoleReporterTest_760, TestRunEndedProducesOutput_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.testCases.passed = 1;
    totals.assertions.passed = 1;
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_NO_THROW(reporter.testRunEnded(stats));
    
    std::string output = oss.str();
    // After a test run ends, there should be some output (summary)
    EXPECT_FALSE(output.empty());
}

// Test that ConsoleReporter can report multiple test cases without error
TEST_F(ConsoleReporterTest_760, MultipleTestCasesDoNotThrow_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter.testRunStarting(runInfo);
    
    for (int i = 0; i < 5; ++i) {
        std::string name = "test_" + std::to_string(i);
        Catch::TestCaseInfo testInfo("", {name, "[tag]"}, {"file.cpp", static_cast<std::size_t>(i + 1)});
        EXPECT_NO_THROW(reporter.testCaseStarting(testInfo));
    }
}

// Test with zero totals (boundary condition)
TEST_F(ConsoleReporterTest_760, ZeroTotalsTestRunEnded_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_NO_THROW(reporter.testRunEnded(stats));
}

// Test with aborting flag set
TEST_F(ConsoleReporterTest_760, AbortingTestRunEnded_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.testCases.failed = 1;
    Catch::TestRunStats stats(runInfo, totals, true /* aborting */);
    
    EXPECT_NO_THROW(reporter.testRunEnded(stats));
}

// Test with failed assertions
TEST_F(ConsoleReporterTest_760, FailedAssertionsInOutput_760) {
    Catch::ConfigData configData;
    Catch::Config config(configData);
    
    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss);
    Catch::ConsoleReporter reporter(reporterConfig);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.testCases.failed = 3;
    totals.assertions.failed = 5;
    Catch::TestRunStats stats(runInfo, totals, false);
    
    reporter.testRunEnded(stats);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

}  // namespace
