#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <memory>

#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// Test the static getDescription method
TEST(TeamCityReporterTest_572, GetDescription_ReturnsExpectedString_572) {
    std::string description = Catch::TeamCityReporter::getDescription();
    EXPECT_FALSE(description.empty());
    EXPECT_EQ(description, "Reports test results as TeamCity service messages");
}

TEST(TeamCityReporterTest_572, GetDescription_IsNotEmpty_572) {
    std::string description = Catch::TeamCityReporter::getDescription();
    EXPECT_GT(description.size(), 0u);
}

TEST(TeamCityReporterTest_572, GetDescription_ContainsTeamCity_572) {
    std::string description = Catch::TeamCityReporter::getDescription();
    EXPECT_NE(description.find("TeamCity"), std::string::npos);
}

TEST(TeamCityReporterTest_572, GetDescription_ContainsServiceMessages_572) {
    std::string description = Catch::TeamCityReporter::getDescription();
    EXPECT_NE(description.find("service messages"), std::string::npos);
}

TEST(TeamCityReporterTest_572, GetDescription_ConsistentAcrossCalls_572) {
    std::string desc1 = Catch::TeamCityReporter::getDescription();
    std::string desc2 = Catch::TeamCityReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}

TEST(TeamCityReporterTest_572, GetDescription_ExactMatch_572) {
    std::string expected = "Reports test results as TeamCity service messages";
    std::string actual = Catch::TeamCityReporter::getDescription();
    EXPECT_EQ(expected, actual);
}
