#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/reporters/catch_reporter_sonarqube.hpp"

// Test the static getDescription method
class SonarQubeReporterTest_569 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: getDescription returns a non-empty string
TEST_F(SonarQubeReporterTest_569, GetDescriptionReturnsNonEmptyString_569) {
    std::string description = Catch::SonarQubeReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Normal operation: getDescription returns the expected description string
TEST_F(SonarQubeReporterTest_569, GetDescriptionReturnsExpectedContent_569) {
    std::string description = Catch::SonarQubeReporter::getDescription();
    EXPECT_EQ(description, "Reports test results in the Generic Test Data SonarQube XML format");
}

// Verify getDescription contains "SonarQube" keyword
TEST_F(SonarQubeReporterTest_569, GetDescriptionContainsSonarQube_569) {
    std::string description = Catch::SonarQubeReporter::getDescription();
    EXPECT_NE(description.find("SonarQube"), std::string::npos);
}

// Verify getDescription contains "XML" keyword
TEST_F(SonarQubeReporterTest_569, GetDescriptionContainsXML_569) {
    std::string description = Catch::SonarQubeReporter::getDescription();
    EXPECT_NE(description.find("XML"), std::string::npos);
}

// Verify getDescription contains "Generic Test Data" phrase
TEST_F(SonarQubeReporterTest_569, GetDescriptionContainsGenericTestData_569) {
    std::string description = Catch::SonarQubeReporter::getDescription();
    EXPECT_NE(description.find("Generic Test Data"), std::string::npos);
}

// Verify getDescription is deterministic (calling multiple times returns same result)
TEST_F(SonarQubeReporterTest_569, GetDescriptionIsDeterministic_569) {
    std::string description1 = Catch::SonarQubeReporter::getDescription();
    std::string description2 = Catch::SonarQubeReporter::getDescription();
    EXPECT_EQ(description1, description2);
}

// Verify getDescription returns a std::string type (compile-time check effectively)
TEST_F(SonarQubeReporterTest_569, GetDescriptionReturnsStdString_569) {
    auto description = Catch::SonarQubeReporter::getDescription();
    static_assert(std::is_same<decltype(description), std::string>::value,
                  "getDescription should return std::string");
    EXPECT_GT(description.size(), 0u);
}
