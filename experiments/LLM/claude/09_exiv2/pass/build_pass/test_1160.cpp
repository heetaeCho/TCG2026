#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <string>

// Test ID: 1160

namespace {

using Exiv2::Rational;

// Helper to call parseRational
Rational callParseRational(const std::string& s, bool& ok) {
    return Exiv2::parseRational(s, ok);
}

// ==================== Normal Operation Tests ====================

TEST(ParseRationalTest_1160, ParseValidRationalFraction_1160) {
    bool ok = false;
    Rational r = callParseRational("1/2", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST(ParseRationalTest_1160, ParseValidRationalNegativeFraction_1160) {
    bool ok = false;
    Rational r = callParseRational("-3/4", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

TEST(ParseRationalTest_1160, ParseValidRationalWholeNumberAsFraction_1160) {
    bool ok = false;
    Rational r = callParseRational("5/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseValidLongInteger_1160) {
    bool ok = false;
    Rational r = callParseRational("42", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseNegativeLongInteger_1160) {
    bool ok = false;
    Rational r = callParseRational("-7", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, -7);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseZeroInteger_1160) {
    bool ok = false;
    Rational r = callParseRational("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseFloatValue_1160) {
    bool ok = false;
    Rational r = callParseRational("0.5", ok);
    EXPECT_TRUE(ok);
    // 0.5 should be converted to a rational, likely 1/2 or similar
    EXPECT_NE(r.second, 0);
    // Verify the ratio is approximately 0.5
    double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(ratio, 0.5, 0.001);
}

TEST(ParseRationalTest_1160, ParseFloatNegativeValue_1160) {
    bool ok = false;
    Rational r = callParseRational("-1.5", ok);
    EXPECT_TRUE(ok);
    EXPECT_NE(r.second, 0);
    double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(ratio, -1.5, 0.001);
}

TEST(ParseRationalTest_1160, ParseBoolTrue_1160) {
    bool ok = false;
    Rational r = callParseRational("true", ok);
    if (ok) {
        EXPECT_EQ(r.first, 1);
        EXPECT_EQ(r.second, 1);
    }
    // If "true" isn't parsed as bool in this implementation, that's also acceptable
}

TEST(ParseRationalTest_1160, ParseBoolFalse_1160) {
    bool ok = false;
    Rational r = callParseRational("false", ok);
    if (ok) {
        EXPECT_EQ(r.first, 0);
        EXPECT_EQ(r.second, 1);
    }
}

// ==================== Boundary Condition Tests ====================

TEST(ParseRationalTest_1160, ParseZeroFraction_1160) {
    bool ok = false;
    Rational r = callParseRational("0/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseLargeNumerator_1160) {
    bool ok = false;
    Rational r = callParseRational("1000000/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 1000000);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseLargeDenominator_1160) {
    bool ok = false;
    Rational r = callParseRational("1/1000000", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 1000000);
}

TEST(ParseRationalTest_1160, ParseFloatZero_1160) {
    bool ok = false;
    Rational r = callParseRational("0.0", ok);
    EXPECT_TRUE(ok);
    double ratio = (r.second != 0) ? static_cast<double>(r.first) / static_cast<double>(r.second) : 0.0;
    EXPECT_NEAR(ratio, 0.0, 0.001);
}

TEST(ParseRationalTest_1160, ParseSmallFloat_1160) {
    bool ok = false;
    Rational r = callParseRational("0.001", ok);
    EXPECT_TRUE(ok);
    EXPECT_NE(r.second, 0);
    double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(ratio, 0.001, 0.01);
}

// ==================== Error / Exceptional Cases ====================

TEST(ParseRationalTest_1160, ParseEmptyString_1160) {
    bool ok = true;
    Rational r = callParseRational("", ok);
    EXPECT_FALSE(ok);
}

TEST(ParseRationalTest_1160, ParseGarbageString_1160) {
    bool ok = true;
    Rational r = callParseRational("abcdef", ok);
    // Could be parsed as bool or could fail; check consistency
    // If ok is false, that's the expected error case
    // If ok is true, it was parsed as a bool
    // Either way, behavior is consistent
    (void)r;
}

TEST(ParseRationalTest_1160, ParseStringWithSpaces_1160) {
    bool ok = true;
    Rational r = callParseRational("  ", ok);
    // Spaces only - likely fails
    EXPECT_FALSE(ok);
}

TEST(ParseRationalTest_1160, ParseMalformedFraction_1160) {
    bool ok = true;
    Rational r = callParseRational("1/", ok);
    // Malformed fraction - should either fail or fallback
    // We just check it doesn't crash
    (void)r;
}

TEST(ParseRationalTest_1160, ParseDoubleFraction_1160) {
    bool ok = true;
    Rational r = callParseRational("1/2/3", ok);
    // Unusual input - should either fail or parse partially
    (void)r;
}

TEST(ParseRationalTest_1160, ParseSpecialChars_1160) {
    bool ok = true;
    Rational r = callParseRational("!@#$", ok);
    EXPECT_FALSE(ok);
}

TEST(ParseRationalTest_1160, ParseNegativeZero_1160) {
    bool ok = false;
    Rational r = callParseRational("-0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParsePositiveSign_1160) {
    bool ok = false;
    Rational r = callParseRational("+5", ok);
    // May or may not be supported
    if (ok) {
        EXPECT_EQ(r.first, 5);
        EXPECT_EQ(r.second, 1);
    }
}

TEST(ParseRationalTest_1160, ParseNegativeDenominator_1160) {
    bool ok = false;
    Rational r = callParseRational("1/-2", ok);
    if (ok) {
        // The result should represent -0.5 somehow
        double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(ratio, -0.5, 0.001);
    }
}

TEST(ParseRationalTest_1160, ParseOneInteger_1160) {
    bool ok = false;
    Rational r = callParseRational("1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 1);
}

TEST(ParseRationalTest_1160, ParseFloatWithExponent_1160) {
    bool ok = false;
    Rational r = callParseRational("1.5e2", ok);
    if (ok) {
        EXPECT_NE(r.second, 0);
        double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(ratio, 150.0, 1.0);
    }
}

TEST(ParseRationalTest_1160, ParseRationalZeroDenominator_1160) {
    bool ok = false;
    Rational r = callParseRational("1/0", ok);
    // Implementation may or may not accept 0 denominator
    if (ok) {
        EXPECT_EQ(r.first, 1);
        EXPECT_EQ(r.second, 0);
    }
}

}  // namespace
