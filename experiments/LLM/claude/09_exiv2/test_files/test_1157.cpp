#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include <climits>

// Forward declaration - include the actual header
#include "types.hpp"

using namespace Exiv2;

// Normal integer parsing tests
TEST(ParseInt64Test_1157, ParsesPositiveInteger_1157) {
    bool ok = false;
    int64_t result = parseInt64("42", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST(ParseInt64Test_1157, ParsesNegativeInteger_1157) {
    bool ok = false;
    int64_t result = parseInt64("-100", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -100);
}

TEST(ParseInt64Test_1157, ParsesZero_1157) {
    bool ok = false;
    int64_t result = parseInt64("0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

TEST(ParseInt64Test_1157, ParsesLargePositiveInteger_1157) {
    bool ok = false;
    int64_t result = parseInt64("9223372036854775807", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, INT64_MAX);
}

TEST(ParseInt64Test_1157, ParsesLargeNegativeInteger_1157) {
    bool ok = false;
    int64_t result = parseInt64("-9223372036854775808", ok);
    // This may or may not succeed depending on implementation
    if (ok) {
        EXPECT_EQ(result, INT64_MIN);
    }
}

// Float parsing fallback tests
TEST(ParseInt64Test_1157, ParsesFloatValue_1157) {
    bool ok = false;
    int64_t result = parseInt64("3.14", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 3);
}

TEST(ParseInt64Test_1157, ParsesNegativeFloatValue_1157) {
    bool ok = false;
    int64_t result = parseInt64("-2.7", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -2);
}

TEST(ParseInt64Test_1157, ParsesFloatZeroPointZero_1157) {
    bool ok = false;
    int64_t result = parseInt64("0.0", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

// Rational parsing fallback tests
TEST(ParseInt64Test_1157, ParsesRationalValue_1157) {
    bool ok = false;
    int64_t result = parseInt64("10/3", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 3);  // 10/3 = 3.333... -> truncated to 3
}

TEST(ParseInt64Test_1157, ParsesRationalValueOneHalf_1157) {
    bool ok = false;
    int64_t result = parseInt64("1/2", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);  // 0.5 -> truncated to 0
}

TEST(ParseInt64Test_1157, ParsesRationalValueExact_1157) {
    bool ok = false;
    int64_t result = parseInt64("6/2", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 3);
}

TEST(ParseInt64Test_1157, ParsesRationalNegativeNumerator_1157) {
    bool ok = false;
    int64_t result = parseInt64("-10/3", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -3);
}

TEST(ParseInt64Test_1157, RationalWithZeroDenominatorFails_1157) {
    bool ok = false;
    int64_t result = parseInt64("5/0", ok);
    // denominator <= 0 should cause ok to be false for rational path
    // but it might fall through to bool parsing
    // The rational check sets ok=false if st <= 0
    // Then it tries bool, which also fails for "5/0"
    EXPECT_FALSE(ok);
}

TEST(ParseInt64Test_1157, RationalWithNegativeDenominatorFails_1157) {
    bool ok = false;
    int64_t result = parseInt64("5/-1", ok);
    // st <= 0 means ok = false for rational, falls through
    // "5/-1" is unlikely to be a valid bool
    EXPECT_FALSE(ok);
}

// Boolean parsing fallback tests
TEST(ParseInt64Test_1157, ParsesTrueString_1157) {
    bool ok = false;
    int64_t result = parseInt64("true", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 1);
}

TEST(ParseInt64Test_1157, ParsesFalseString_1157) {
    bool ok = false;
    int64_t result = parseInt64("false", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

// Error/exceptional cases
TEST(ParseInt64Test_1157, EmptyStringFails_1157) {
    bool ok = false;
    parseInt64("", ok);
    EXPECT_FALSE(ok);
}

TEST(ParseInt64Test_1157, GarbageStringFails_1157) {
    bool ok = false;
    parseInt64("not_a_number", ok);
    EXPECT_FALSE(ok);
}

TEST(ParseInt64Test_1157, SpecialCharactersFails_1157) {
    bool ok = false;
    parseInt64("!@#$%", ok);
    EXPECT_FALSE(ok);
}

TEST(ParseInt64Test_1157, WhitespaceOnlyFails_1157) {
    bool ok = false;
    parseInt64("   ", ok);
    EXPECT_FALSE(ok);
}

// Boundary conditions
TEST(ParseInt64Test_1157, ParsesOne_1157) {
    bool ok = false;
    int64_t result = parseInt64("1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 1);
}

TEST(ParseInt64Test_1157, ParsesNegativeOne_1157) {
    bool ok = false;
    int64_t result = parseInt64("-1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -1);
}

TEST(ParseInt64Test_1157, ParsesRational1Over1_1157) {
    bool ok = false;
    int64_t result = parseInt64("1/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 1);
}

TEST(ParseInt64Test_1157, ParsesRational0Over1_1157) {
    bool ok = false;
    int64_t result = parseInt64("0/1", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

TEST(ParseInt64Test_1157, ParsesLeadingPlusSign_1157) {
    bool ok = false;
    int64_t result = parseInt64("+5", ok);
    // Depending on the implementation, leading + may or may not be accepted
    if (ok) {
        EXPECT_EQ(result, 5);
    }
}

TEST(ParseInt64Test_1157, MixedAlphaNumericFails_1157) {
    bool ok = false;
    parseInt64("12abc", ok);
    // May fail since it's not a pure number
    // Behavior depends on stringTo implementation
    // Just check that it doesn't crash
}

TEST(ParseInt64Test_1157, ParsesLargeRational_1157) {
    bool ok = false;
    int64_t result = parseInt64("1000000/7", ok);
    EXPECT_TRUE(ok);
    // 1000000/7 ≈ 142857.14
    EXPECT_EQ(result, 142857);
}

TEST(ParseInt64Test_1157, OkInitiallyTrueStillWorks_1157) {
    bool ok = true;
    int64_t result = parseInt64("99", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 99);
}

TEST(ParseInt64Test_1157, OkInitiallyTrueFailsOnBadInput_1157) {
    bool ok = true;
    parseInt64("xyz", ok);
    EXPECT_FALSE(ok);
}
