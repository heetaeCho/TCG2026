// File: tap_reporter_get_description_tests_571.cpp
#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_tap.hpp"

using namespace ::testing;

class TAPReporterTest_571 : public Test {};

// Verifies the function returns the exact, documented description string.
TEST_F(TAPReporterTest_571, ReturnsExactDescription_571) {
    const std::string expected =
        "Reports test results in TAP format, suitable for test harnesses";
    EXPECT_EQ(expected, Catch::TAPReporter::getDescription());
}

// Ensures the description is non-empty (basic sanity / observable behavior).
TEST_F(TAPReporterTest_571, DescriptionIsNotEmpty_571) {
    const auto desc = Catch::TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Ensures the description mentions "TAP" (format identifier appears in text).
TEST_F(TAPReporterTest_571, DescriptionMentionsTAP_571) {
    const auto desc = Catch::TAPReporter::getDescription();
    EXPECT_NE(std::string::npos, desc.find("TAP"));
}

// Calling the static function repeatedly should be deterministic and not throw.
TEST_F(TAPReporterTest_571, DescriptionStableAcrossCalls_571) {
    std::string first, second;
    EXPECT_NO_THROW(first  = Catch::TAPReporter::getDescription());
    EXPECT_NO_THROW(second = Catch::TAPReporter::getDescription());
    EXPECT_EQ(first, second);
}
