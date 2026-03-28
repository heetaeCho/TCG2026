#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Include the header under test
#include "catch2/reporters/catch_reporter_automake.hpp"

// Test fixture for AutomakeReporter
class AutomakeReporterTest_564 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDescription returns a non-empty string
TEST_F(AutomakeReporterTest_564, GetDescriptionReturnsNonEmptyString_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that getDescription returns the expected description string
TEST_F(AutomakeReporterTest_564, GetDescriptionReturnsExpectedContent_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_EQ(description, "Reports test results in the format of Automake .trs files");
}

// Test that getDescription is consistent across multiple calls
TEST_F(AutomakeReporterTest_564, GetDescriptionIsConsistentAcrossCalls_564) {
    std::string description1 = Catch::AutomakeReporter::getDescription();
    std::string description2 = Catch::AutomakeReporter::getDescription();
    EXPECT_EQ(description1, description2);
}

// Test that getDescription contains "Automake" keyword
TEST_F(AutomakeReporterTest_564, GetDescriptionContainsAutomakeKeyword_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_NE(description.find("Automake"), std::string::npos);
}

// Test that getDescription contains ".trs" file format reference
TEST_F(AutomakeReporterTest_564, GetDescriptionContainsTrsFileReference_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_NE(description.find(".trs"), std::string::npos);
}

// Test that getDescription mentions "test results"
TEST_F(AutomakeReporterTest_564, GetDescriptionMentionsTestResults_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_NE(description.find("test results"), std::string::npos);
}

// Test that the returned string is a valid std::string type
TEST_F(AutomakeReporterTest_564, GetDescriptionReturnsStdString_564) {
    auto description = Catch::AutomakeReporter::getDescription();
    EXPECT_TRUE((std::is_same<decltype(description), std::string>::value));
}

// Test that getDescription has a reasonable length
TEST_F(AutomakeReporterTest_564, GetDescriptionHasReasonableLength_564) {
    std::string description = Catch::AutomakeReporter::getDescription();
    EXPECT_GT(description.length(), 10u);
    EXPECT_LT(description.length(), 500u);
}
