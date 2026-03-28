// File: within_rel_matcher_describe_tests_202.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>  // For HasSubstr if you prefer; not strictly required
#include <regex>
#include <string>

// SUT header (from the prompt)
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using ::testing::HasSubstr;

namespace {

using Catch::Matchers::WithinRelMatcher;

// Small helper: regex search (not full match) for convenience.
static bool ContainsRegex(const std::string& text, const std::string& pattern) {
    return std::regex_search(text, std::regex(pattern));
}

// -- Tests --

// Verifies that describe() mentions the target value (via stringify) and the expected percent.
// Uses a regex allowing optional trailing decimals to avoid depending on exact float formatting.
TEST(WithinRelMatcherDescribeTest_202, Describe_IncludesTargetAndPercent_202) {
    const double target  = 3.14;
    const double epsilon = 0.50; // 50%

    WithinRelMatcher matcher(target, epsilon);
    const std::string d = matcher.describe();

    // Starts with the required prefix
    EXPECT_TRUE(d.rfind("and ", 0) == 0) << "describe() should start with \"and \": " << d;

    // Contains the target number (stringify formatting is implementation-defined; we check substring)
    EXPECT_NE(d.find("3.14"), std::string::npos) << "describe() should mention the target value: " << d;

    // Contains the suffix phrase
    EXPECT_NE(d.find("% of each other"), std::string::npos) << "describe() should mention \"% of each other\": " << d;

    // Check that percentage reflects epsilon * 100 (50 or 50.0 or 50.000..., etc)
    EXPECT_TRUE(ContainsRegex(d, R"(within\s+50(\.0+)?%)")) << "Percent should be 50%: " << d;
}

// Zero epsilon should produce "0%" (allowing 0.0% etc).
TEST(WithinRelMatcherDescribeTest_202, Describe_ZeroEpsilon_Shows0Percent_202) {
    const double target  = 42.5;
    const double epsilon = 0.0; // 0%

    WithinRelMatcher matcher(target, epsilon);
    const std::string d = matcher.describe();

    // Target substring presence (formatting may vary; check substring only)
    EXPECT_NE(d.find("42.5"), std::string::npos) << "describe() should mention the target value: " << d;

    // Check 0% with optional decimals
    EXPECT_TRUE(ContainsRegex(d, R"(within\s+0(\.0+)?%)")) << "Percent should be 0%: " << d;

    // Ends with exact suffix (no trailing spaces)
    EXPECT_TRUE(ContainsRegex(d, R"(% of each other$)")) << "Should end with \"% of each other\": " << d;
}

// Epsilon = 1.0 should render as ~100% (allowing 100 or 100.0...).
TEST(WithinRelMatcherDescribeTest_202, Describe_EpsilonOne_Shows100Percent_202) {
    const double target  = -7.0;
    const double epsilon = 1.0; // 100%

    WithinRelMatcher matcher(target, epsilon);
    const std::string d = matcher.describe();

    // Target substring presence (stringify(-7.0) may vary; accept "-7" or "-7.0" by checking "-7")
    EXPECT_NE(d.find("-7"), std::string::npos) << "describe() should mention the target value: " << d;

    // Check 100% with optional decimals
    EXPECT_TRUE(ContainsRegex(d, R"(within\s+100(\.0+)?%)")) << "Percent should be 100%: " << d;
}

// A fractional epsilon leading to a non-integer percent should be reflected as such (e.g., 12.5%).
// We avoid assuming an exact number of decimal places by allowing optional trailing zeros.
TEST(WithinRelMatcherDescribeTest_202, Describe_FractionalPercent_ShowsExpectedValue_202) {
    const double target  = 1.0;
    const double epsilon = 0.125; // 12.5%

    WithinRelMatcher matcher(target, epsilon);
    const std::string d = matcher.describe();

    // Target presence
    // Depending on stringify, it might be "1" or "1.0"; check "1" to be permissive.
    EXPECT_NE(d.find("1"), std::string::npos) << "describe() should mention the target value: " << d;

    // Accept "12.5%", "12.50%", "12.5000%", etc.
    EXPECT_TRUE(ContainsRegex(d, R"(within\s+12\.5(0+)?%)")) << "Percent should reflect 12.5%: " << d;
}

} // namespace
