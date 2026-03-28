#include <gtest/gtest.h>
#include <sstream>
#include <limits>
#include <type_traits>

// Include the header under test
#include "yaml-cpp/node/convert.h"

// ============================================================
// Tests for unsigned char variant of ConvertStreamTo
// ============================================================

class ConvertStreamToUnsignedChar_605 : public ::testing::Test {
protected:
    unsigned char result{};
};

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_Zero_605) {
    std::stringstream ss("0");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_TypicalPositive_605) {
    std::stringstream ss("42");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_MaxUnsignedChar_605) {
    std::stringstream ss(std::to_string(std::numeric_limits<unsigned char>::max()));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<unsigned char>::max());
}

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_MinUnsignedChar_605) {
    // min for unsigned char is 0
    std::stringstream ss(std::to_string(std::numeric_limits<unsigned char>::min()));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<unsigned char>::min());
}

TEST_F(ConvertStreamToUnsignedChar_605, BoundaryAboveMax_605) {
    int aboveMax = static_cast<int>(std::numeric_limits<unsigned char>::max()) + 1;
    std::stringstream ss(std::to_string(aboveMax));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, BoundaryNegativeValue_605) {
    std::stringstream ss("-1");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, BoundaryLargeNegativeValue_605) {
    std::stringstream ss("-200");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, BoundaryLargePositiveValue_605) {
    std::stringstream ss("1000");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_EmptyStream_605) {
    std::stringstream ss("");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_NonNumericInput_605) {
    std::stringstream ss("abc");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_NumberFollowedByChars_605) {
    std::stringstream ss("42abc");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_FloatingPointValue_605) {
    std::stringstream ss("3.14");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_WithTrailingWhitespace_605) {
    std::stringstream ss("100   ");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 100);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_LeadingWhitespace_605) {
    // noskipws is used, so leading whitespace should cause failure
    std::stringstream ss("  42");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, ErrorCase_OnlyWhitespace_605) {
    std::stringstream ss("   ");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToUnsignedChar_605, NormalValue_255_605) {
    std::stringstream ss("255");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 255);
}

TEST_F(ConvertStreamToUnsignedChar_605, BoundaryValue_256_605) {
    std::stringstream ss("256");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

// ============================================================
// Tests for signed char variant of ConvertStreamTo
// ============================================================

class ConvertStreamToSignedChar_605 : public ::testing::Test {
protected:
    signed char result{};
};

TEST_F(ConvertStreamToSignedChar_605, NormalValue_Zero_605) {
    std::stringstream ss("0");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 0);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_PositiveTypical_605) {
    std::stringstream ss("42");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 42);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_NegativeTypical_605) {
    std::stringstream ss("-42");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -42);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryValue_MaxSignedChar_605) {
    std::stringstream ss(std::to_string(std::numeric_limits<signed char>::max()));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<signed char>::max());
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryValue_MinSignedChar_605) {
    std::stringstream ss(std::to_string(std::numeric_limits<signed char>::min()));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, std::numeric_limits<signed char>::min());
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryAboveMax_605) {
    int aboveMax = static_cast<int>(std::numeric_limits<signed char>::max()) + 1; // 128
    std::stringstream ss(std::to_string(aboveMax));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryBelowMin_605) {
    int belowMin = static_cast<int>(std::numeric_limits<signed char>::min()) - 1; // -129
    std::stringstream ss(std::to_string(belowMin));
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryLargePositive_605) {
    std::stringstream ss("1000");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryLargeNegative_605) {
    std::stringstream ss("-1000");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_EmptyStream_605) {
    std::stringstream ss("");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_NonNumeric_605) {
    std::stringstream ss("xyz");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_NumberFollowedByChars_605) {
    std::stringstream ss("10xyz");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_FloatingPoint_605) {
    std::stringstream ss("1.5");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_WithTrailingWhitespace_605) {
    std::stringstream ss("50   ");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 50);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_LeadingWhitespace_605) {
    std::stringstream ss("  50");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_127_605) {
    std::stringstream ss("127");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 127);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_Minus128_605) {
    std::stringstream ss("-128");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -128);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryValue_128_605) {
    std::stringstream ss("128");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, BoundaryValue_Minus129_605) {
    std::stringstream ss("-129");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, NormalValue_NegativeWithTrailingSpace_605) {
    std::stringstream ss("-100  ");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -100);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_OnlyWhitespace_605) {
    std::stringstream ss("   ");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    EXPECT_FALSE(ok);
}

TEST_F(ConvertStreamToSignedChar_605, ErrorCase_PlusSign_605) {
    // '+' sign before number: depends on stream parsing
    std::stringstream ss("+50");
    bool ok = YAML::conversion::ConvertStreamTo(ss, result);
    // The standard stream should parse +50 as 50
    if (ok) {
        EXPECT_EQ(result, 50);
    }
    // Either outcome is acceptable based on implementation
}
