#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// ==================== Tests for convertInto with int ====================

TEST(ConvertIntoTest_374, IntConversion_ValidPositiveInteger_374) {
    int target = 0;
    auto result = convertInto(std::string("42"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 42);
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

TEST(ConvertIntoTest_374, IntConversion_ValidNegativeInteger_374) {
    int target = 0;
    auto result = convertInto(std::string("-17"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, -17);
}

TEST(ConvertIntoTest_374, IntConversion_Zero_374) {
    int target = 999;
    auto result = convertInto(std::string("0"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 0);
}

TEST(ConvertIntoTest_374, IntConversion_InvalidString_374) {
    int target = 0;
    auto result = convertInto(std::string("not_a_number"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(target, 0); // target should remain unchanged or be in failed state
    EXPECT_FALSE(result.errorMessage().empty());
}

TEST(ConvertIntoTest_374, IntConversion_EmptyString_374) {
    int target = 42;
    auto result = convertInto(std::string(""), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(result.errorMessage().empty());
}

TEST(ConvertIntoTest_374, IntConversion_FloatingPointToInt_374) {
    int target = 0;
    auto result = convertInto(std::string("3.14"), target);
    // stringstream >> int will read "3" and stop at '.', which may or may not fail
    // The stream won't fail, it just reads 3
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 3);
}

// ==================== Tests for convertInto with double ====================

TEST(ConvertIntoTest_374, DoubleConversion_ValidPositiveDouble_374) {
    double target = 0.0;
    auto result = convertInto(std::string("3.14"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(target, 3.14);
}

TEST(ConvertIntoTest_374, DoubleConversion_ValidNegativeDouble_374) {
    double target = 0.0;
    auto result = convertInto(std::string("-2.718"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(target, -2.718);
}

TEST(ConvertIntoTest_374, DoubleConversion_IntegerAsDouble_374) {
    double target = 0.0;
    auto result = convertInto(std::string("42"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(target, 42.0);
}

TEST(ConvertIntoTest_374, DoubleConversion_InvalidString_374) {
    double target = 0.0;
    auto result = convertInto(std::string("abc"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(result.errorMessage().empty());
}

TEST(ConvertIntoTest_374, DoubleConversion_ScientificNotation_374) {
    double target = 0.0;
    auto result = convertInto(std::string("1.5e2"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(target, 150.0);
}

TEST(ConvertIntoTest_374, DoubleConversion_ZeroDouble_374) {
    double target = 999.0;
    auto result = convertInto(std::string("0.0"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(target, 0.0);
}

// ==================== Tests for convertInto with float ====================

TEST(ConvertIntoTest_374, FloatConversion_ValidFloat_374) {
    float target = 0.0f;
    auto result = convertInto(std::string("1.5"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FLOAT_EQ(target, 1.5f);
}

TEST(ConvertIntoTest_374, FloatConversion_InvalidString_374) {
    float target = 0.0f;
    auto result = convertInto(std::string("xyz"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(result.errorMessage().empty());
}

// ==================== Tests for convertInto with unsigned int ====================

TEST(ConvertIntoTest_374, UnsignedIntConversion_ValidValue_374) {
    unsigned int target = 0;
    auto result = convertInto(std::string("100"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 100u);
}

TEST(ConvertIntoTest_374, UnsignedIntConversion_InvalidString_374) {
    unsigned int target = 0;
    auto result = convertInto(std::string("hello"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(result.errorMessage().empty());
}

// ==================== Tests for convertInto with long ====================

TEST(ConvertIntoTest_374, LongConversion_ValidLong_374) {
    long target = 0;
    auto result = convertInto(std::string("1234567890"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 1234567890L);
}

// ==================== Tests for convertInto with std::string ====================

TEST(ConvertIntoTest_374, StringConversion_SimpleString_374) {
    std::string target;
    auto result = convertInto(std::string("hello"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, "hello");
}

TEST(ConvertIntoTest_374, StringConversion_StringWithSpaces_374) {
    std::string target;
    // stringstream >> string reads until whitespace
    auto result = convertInto(std::string("hello world"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, "hello"); // Only reads first word
}

// ==================== Tests for error message content ====================

TEST(ConvertIntoTest_374, ErrorMessageContainsSourceString_374) {
    int target = 0;
    auto result = convertInto(std::string("foobar"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    // The error message should contain the source string
    EXPECT_NE(result.errorMessage().find("foobar"), std::string::npos);
}

TEST(ConvertIntoTest_374, ErrorMessageContainsUnableToConvert_374) {
    int target = 0;
    auto result = convertInto(std::string("invalid"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_NE(result.errorMessage().find("Unable to convert"), std::string::npos);
}

// ==================== Boundary tests ====================

TEST(ConvertIntoTest_374, IntConversion_MaxInt_374) {
    int target = 0;
    std::string maxIntStr = std::to_string(std::numeric_limits<int>::max());
    auto result = convertInto(maxIntStr, target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, std::numeric_limits<int>::max());
}

TEST(ConvertIntoTest_374, IntConversion_MinInt_374) {
    int target = 0;
    std::string minIntStr = std::to_string(std::numeric_limits<int>::min());
    auto result = convertInto(minIntStr, target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, std::numeric_limits<int>::min());
}

TEST(ConvertIntoTest_374, IntConversion_WhitespaceOnly_374) {
    int target = 42;
    auto result = convertInto(std::string("   "), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST(ConvertIntoTest_374, IntConversion_LeadingWhitespace_374) {
    int target = 0;
    auto result = convertInto(std::string("  123"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(target, 123);
}

TEST(ConvertIntoTest_374, DoubleConversion_EmptyString_374) {
    double target = 1.0;
    auto result = convertInto(std::string(""), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

// ==================== Tests for result type on success ====================

TEST(ConvertIntoTest_374, SuccessResultIsMatched_374) {
    int target = 0;
    auto result = convertInto(std::string("5"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    // On success, result type should indicate Ok
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

TEST(ConvertIntoTest_374, FailureResultIsFailure_374) {
    int target = 0;
    auto result = convertInto(std::string("abc"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultBase::GeneralError);
}
