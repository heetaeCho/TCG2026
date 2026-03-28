// File: automake_reporter_getdescription_tests_564.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/reporters/catch_reporter_automake.hpp"

using Catch::AutomakeReporter;

class AutomakeReporterTest_564 : public ::testing::Test {};

// Verifies the function returns the exact documented description.
TEST_F(AutomakeReporterTest_564, ReturnsExactDescription_564) {
    const std::string expected =
        "Reports test results in the format of Automake .trs files";
    EXPECT_EQ(AutomakeReporter::getDescription(), expected);
}

// Basic sanity: result is non-empty and readable (observable behavior).
TEST_F(AutomakeReporterTest_564, ReturnsNonEmptyString_564) {
    const auto desc = AutomakeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Ensures no accidental leading/trailing whitespace characters.
TEST_F(AutomakeReporterTest_564, NoLeadingOrTrailingWhitespace_564) {
    const auto desc = AutomakeReporter::getDescription();
    ASSERT_FALSE(desc.empty());

    // Check first and last characters are not whitespace
    EXPECT_NE(desc.front(), ' ');
    EXPECT_NE(desc.back(),  ' ');
    EXPECT_NE(desc.front(), '\t');
    EXPECT_NE(desc.back(),  '\t');
    EXPECT_NE(desc.front(), '\n');
    EXPECT_NE(desc.back(),  '\n');
    EXPECT_NE(desc.front(), '\r');
    EXPECT_NE(desc.back(),  '\r');
}

// The description should contain clear Automake/TRS hints (robustness check).
TEST_F(AutomakeReporterTest_564, ContainsAutomakeAndTrsKeywords_564) {
    const auto desc = AutomakeReporter::getDescription();
    EXPECT_NE(desc.find("Automake"), std::string::npos);
    EXPECT_NE(desc.find(".trs"),     std::string::npos);
}

// Idempotence: multiple calls should return the same value, and returned strings
// are independent copies (mutating the copy should not affect future calls).
TEST_F(AutomakeReporterTest_564, StableAcrossCallsAndIndependentCopy_564) {
    const auto first  = AutomakeReporter::getDescription();
    auto second = AutomakeReporter::getDescription();

    EXPECT_EQ(first, second);

    // Mutate our local copy and ensure a fresh call still equals the original.
    second += " (modified)";
    const auto third = AutomakeReporter::getDescription();
    EXPECT_EQ(first, third);
}
