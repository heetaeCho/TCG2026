#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"

namespace {

class ConsoleReporterTest_762 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDescription returns the expected string
TEST_F(ConsoleReporterTest_762, GetDescription_ReturnsExpectedString_762) {
    std::string description = Catch::ConsoleReporter::getDescription();
    EXPECT_EQ(description, "Reports test results as plain lines of text");
}

// Test that getDescription returns a non-empty string
TEST_F(ConsoleReporterTest_762, GetDescription_ReturnsNonEmptyString_762) {
    std::string description = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that getDescription is consistent across multiple calls
TEST_F(ConsoleReporterTest_762, GetDescription_IsConsistentAcrossMultipleCalls_762) {
    std::string first = Catch::ConsoleReporter::getDescription();
    std::string second = Catch::ConsoleReporter::getDescription();
    EXPECT_EQ(first, second);
}

// Test construction and basic operations with a ReporterConfig
class ConsoleReporterWithConfigTest_762 : public ::testing::Test {
protected:
    std::stringstream stream_;
    
    Catch::ReporterConfig makeConfig() {
        // Create a minimal config for the reporter
        // We need a valid IConfig and stream
        static const char* argv[] = {"test"};
        Catch::Session session;
        auto& config = session.config();
        
        auto configPtr = session.configData();
        return Catch::ReporterConfig(
            dynamic_cast<Catch::IConfig const*>(&config),
            Catch::Detail::make_unique<std::ostream>(stream_.rdbuf()),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );
    }
};

// Test that ConsoleReporter can be constructed and destroyed without issues
TEST_F(ConsoleReporterTest_762, GetDescription_ContainsPlainText_762) {
    std::string description = Catch::ConsoleReporter::getDescription();
    EXPECT_THAT(description, ::testing::HasSubstr("plain lines of text"));
}

// Test that getDescription contains "test results"
TEST_F(ConsoleReporterTest_762, GetDescription_ContainsTestResults_762) {
    std::string description = Catch::ConsoleReporter::getDescription();
    EXPECT_THAT(description, ::testing::HasSubstr("test results"));
}

// Test that getDescription contains "Reports"
TEST_F(ConsoleReporterTest_762, GetDescription_ContainsReports_762) {
    std::string description = Catch::ConsoleReporter::getDescription();
    EXPECT_THAT(description, ::testing::HasSubstr("Reports"));
}

} // anonymous namespace
