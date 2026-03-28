// File: tests/get_formatted_duration_817_tests.cpp

#include <gtest/gtest.h>
#include <string>
#include <limits>

// We treat the implementation as a black box.
// If there's a public header, include it instead of this forward decl.
// #include "catch2/reporters/catch_reporter_helpers.hpp"
namespace Catch {
    std::string getFormattedDuration(double duration);
}

// Alias for brevity
using Catch::getFormattedDuration;

// ----------------------
// Normal operation cases
// ----------------------

TEST(GetFormattedDurationTest_817, FormatsWithThreeDecimals_817) {
    // Exact 3-decimal formatting for a simple value
    EXPECT_EQ(getFormattedDuration(2.0), "2.000");
    EXPECT_EQ(getFormattedDuration(0.5), "0.500");
}

TEST(GetFormattedDurationTest_817, RoundsHalfUp_817) {
    // Checks standard rounding at the 4th decimal
    EXPECT_EQ(getFormattedDuration(1.2346), "1.235");
    EXPECT_EQ(getFormattedDuration(1.2345), "1.235");
    EXPECT_EQ(getFormattedDuration(1.2344), "1.234");
}

TEST(GetFormattedDurationTest_817, HandlesNegativeValues_817) {
    // Negative number formatting and rounding
    EXPECT_EQ(getFormattedDuration(-3.14159), "-3.142");
    EXPECT_EQ(getFormattedDuration(-2.0), "-2.000");
}

// ----------------------
// Boundary-ish behaviors
// ----------------------

TEST(GetFormattedDurationTest_817, SmallValuesClampByRounding_817) {
    // Values that should round to zero at 3 decimals
    EXPECT_EQ(getFormattedDuration(0.0004), "0.000");
    EXPECT_EQ(getFormattedDuration(-0.0004), "-0.000"); // sign should be preserved by printf-style formatting
}

TEST(GetFormattedDurationTest_817, SmallValuesRoundUpToOneThousandth_817) {
    // Values that should round up to 0.001 or down to -0.001
    EXPECT_EQ(getFormattedDuration(0.0005), "0.001");
    EXPECT_EQ(getFormattedDuration(-0.0005), "-0.001");
}

TEST(GetFormattedDurationTest_817, LargeIntegerPortionPreserved_817) {
    // Large magnitude with rounding across decimal boundary
    // 123456789.98765 -> rounds to 123456790.000
    EXPECT_EQ(getFormattedDuration(123456789.98765), "123456790.000");
}

TEST(GetFormattedDurationTest_817, ZeroFormatsConsistently_817) {
    // Explicit zero should always produce 3 decimals
    EXPECT_EQ(getFormattedDuration(0.0), "0.000");
}

TEST(GetFormattedDurationTest_817, ManyDecimalPlacesStillThreeOut_817) {
    // Long fractional part should still output exactly 3 decimals
    EXPECT_EQ(getFormattedDuration(1.000000000123), "1.000");
    EXPECT_EQ(getFormattedDuration(9.9999999), "10.000");
}

// ----------------------
// Resilience (observable only)
// ----------------------

TEST(GetFormattedDurationTest_817, DoesNotAppendExtraCharacters_817) {
    // Make sure the returned string length matches the expected format for a few samples
    // (observable property: exactly 3 digits after the decimal; sign if negative)
    const auto s1 = getFormattedDuration(42.12345);    // "42.123"
    const auto s2 = getFormattedDuration(-0.00049);    // "-0.000"
    const auto s3 = getFormattedDuration(1000.0);      // "1000.000"

    EXPECT_NE(s1.find('.'), std::string::npos);
    EXPECT_EQ(s1.size() - s1.find('.') - 1, 3u);

    EXPECT_NE(s2.find('.'), std::string::npos);
    EXPECT_EQ(s2.size() - s2.find('.') - 1, 3u);
    EXPECT_EQ(s2[0], '-');

    EXPECT_NE(s3.find('.'), std::string::npos);
    EXPECT_EQ(s3.size() - s3.find('.') - 1, 3u);
}
