#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

namespace {

class JunitReporterTest_749 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDescription returns a non-empty string
TEST_F(JunitReporterTest_749, GetDescriptionReturnsNonEmptyString_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that getDescription returns the expected description mentioning XML and junitreport
TEST_F(JunitReporterTest_749, GetDescriptionContainsXMLReference_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_NE(description.find("XML"), std::string::npos);
}

// Test that getDescription mentions junitreport target
TEST_F(JunitReporterTest_749, GetDescriptionContainsJunitReportReference_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_NE(description.find("junitreport"), std::string::npos);
}

// Test that getDescription mentions Ant
TEST_F(JunitReporterTest_749, GetDescriptionContainsAntReference_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_NE(description.find("Ant"), std::string::npos);
}

// Test that getDescription returns the exact expected string
TEST_F(JunitReporterTest_749, GetDescriptionReturnsExactExpectedString_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_EQ(description, "Reports test results in an XML format that looks like Ant's junitreport target");
}

// Test that getDescription is consistent across multiple calls
TEST_F(JunitReporterTest_749, GetDescriptionIsConsistentAcrossMultipleCalls_749) {
    std::string description1 = Catch::JunitReporter::getDescription();
    std::string description2 = Catch::JunitReporter::getDescription();
    EXPECT_EQ(description1, description2);
}

// Test that getDescription mentions "Reports"
TEST_F(JunitReporterTest_749, GetDescriptionStartsWithReports_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_EQ(description.substr(0, 7), "Reports");
}

// Test description mentions "test results"
TEST_F(JunitReporterTest_749, GetDescriptionMentionsTestResults_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_NE(description.find("test results"), std::string::npos);
}

// Test that description has reasonable length
TEST_F(JunitReporterTest_749, GetDescriptionHasReasonableLength_749) {
    std::string description = Catch::JunitReporter::getDescription();
    EXPECT_GT(description.size(), 10u);
    EXPECT_LT(description.size(), 500u);
}

} // anonymous namespace
