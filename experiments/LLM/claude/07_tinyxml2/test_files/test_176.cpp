#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== ToDouble Tests ====================

class XMLUtilToDoubleTest_176 : public ::testing::Test {
protected:
    double value;
};

TEST_F(XMLUtilToDoubleTest_176, ValidPositiveDouble_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("3.14", &value));
    EXPECT_DOUBLE_EQ(3.14, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidNegativeDouble_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("-2.718", &value));
    EXPECT_DOUBLE_EQ(-2.718, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("0.0", &value));
    EXPECT_DOUBLE_EQ(0.0, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidIntegerAsDouble_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("42", &value));
    EXPECT_DOUBLE_EQ(42.0, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidScientificNotation_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("1.5e10", &value));
    EXPECT_DOUBLE_EQ(1.5e10, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidNegativeScientificNotation_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("-3.0e-5", &value));
    EXPECT_DOUBLE_EQ(-3.0e-5, value);
}

TEST_F(XMLUtilToDoubleTest_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

TEST_F(XMLUtilToDoubleTest_176, InvalidNonNumericString_176) {
    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));
}

TEST_F(XMLUtilToDoubleTest_176, ValidVerySmallDouble_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("0.000000001", &value));
    EXPECT_DOUBLE_EQ(0.000000001, value);
}

TEST_F(XMLUtilToDoubleTest_176, ValidVeryLargeDouble_176) {
    EXPECT_TRUE(XMLUtil::ToDouble("1.7976931348623157e+308", &value));
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, value);
}

// ==================== ToInt Tests ====================

class XMLUtilToIntTest_176 : public ::testing::Test {
protected:
    int value;
};

TEST_F(XMLUtilToIntTest_176, ValidPositiveInt_176) {
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(123, value);
}

TEST_F(XMLUtilToIntTest_176, ValidNegativeInt_176) {
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(-456, value);
}

TEST_F(XMLUtilToIntTest_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToIntTest_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilToIntTest_176, InvalidNonNumeric_176) {
    EXPECT_FALSE(XMLUtil::ToInt("xyz", &value));
}

TEST_F(XMLUtilToIntTest_176, ValidMaxInt_176) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MAX);
    EXPECT_TRUE(XMLUtil::ToInt(buf, &value));
    EXPECT_EQ(INT_MAX, value);
}

TEST_F(XMLUtilToIntTest_176, ValidMinInt_176) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MIN);
    EXPECT_TRUE(XMLUtil::ToInt(buf, &value));
    EXPECT_EQ(INT_MIN, value);
}

// ==================== ToUnsigned Tests ====================

class XMLUtilToUnsignedTest_176 : public ::testing::Test {
protected:
    unsigned int value;
};

TEST_F(XMLUtilToUnsignedTest_176, ValidUnsigned_176) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("12345", &value));
    EXPECT_EQ(12345u, value);
}

TEST_F(XMLUtilToUnsignedTest_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsignedTest_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

TEST_F(XMLUtilToUnsignedTest_176, InvalidNonNumeric_176) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

// ==================== ToBool Tests ====================

class XMLUtilToBoolTest_176 : public ::testing::Test {
protected:
    bool value;
};

TEST_F(XMLUtilToBoolTest_176, ValidTrue_176) {
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_176, ValidFalse_176) {
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_176, ValidOne_176) {
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_176, InvalidString_176) {
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilToBoolTest_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// ==================== ToFloat Tests ====================

class XMLUtilToFloatTest_176 : public ::testing::Test {
protected:
    float value;
};

TEST_F(XMLUtilToFloatTest_176, ValidPositiveFloat_176) {
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_176, ValidNegativeFloat_176) {
    EXPECT_TRUE(XMLUtil::ToFloat("-1.5", &value));
    EXPECT_FLOAT_EQ(-1.5f, value);
}

TEST_F(XMLUtilToFloatTest_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToFloat("0.0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

TEST_F(XMLUtilToFloatTest_176, InvalidNonNumeric_176) {
    EXPECT_FALSE(XMLUtil::ToFloat("hello", &value));
}

// ==================== ToInt64 Tests ====================

class XMLUtilToInt64Test_176 : public ::testing::Test {
protected:
    int64_t value;
};

TEST_F(XMLUtilToInt64Test_176, ValidPositive_176) {
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(INT64_MAX, value);
}

TEST_F(XMLUtilToInt64Test_176, ValidNegative_176) {
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilToInt64Test_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToInt64Test_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

TEST_F(XMLUtilToInt64Test_176, InvalidNonNumeric_176) {
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

// ==================== ToUnsigned64 Tests ====================

class XMLUtilToUnsigned64Test_176 : public ::testing::Test {
protected:
    uint64_t value;
};

TEST_F(XMLUtilToUnsigned64Test_176, ValidPositive_176) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilToUnsigned64Test_176, ValidZero_176) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsigned64Test_176, InvalidEmptyString_176) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

TEST_F(XMLUtilToUnsigned64Test_176, InvalidNonNumeric_176) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &value));
}

// ==================== ToStr Tests ====================

class XMLUtilToStrTest_176 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_176, IntToStr_176) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_176, NegativeIntToStr_176) {
    XMLUtil::ToStr(-10, buffer, sizeof(buffer));
    EXPECT_STREQ("-10", buffer);
}

TEST_F(XMLUtilToStrTest_176, ZeroIntToStr_176) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_176, UnsignedToStr_176) {
    XMLUtil::ToStr((unsigned int)100, buffer, sizeof(buffer));
    EXPECT_STREQ("100", buffer);
}

TEST_F(XMLUtilToStrTest_176, BoolTrueToStr_176) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_176, BoolFalseToStr_176) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_176, FloatToStr_176) {
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Just verify it parses back correctly
    float parsed;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_FLOAT_EQ(1.5f, parsed);
}

TEST_F(XMLUtilToStrTest_176, DoubleToStr_176) {
    XMLUtil::ToStr(3.14, buffer, sizeof(buffer));
    double parsed;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_DOUBLE_EQ(3.14, parsed);
}

TEST_F(XMLUtilToStrTest_176, Int64ToStr_176) {
    XMLUtil::ToStr((int64_t)1234567890123LL, buffer, sizeof(buffer));
    EXPECT_STREQ("1234567890123", buffer);
}

TEST_F(XMLUtilToStrTest_176, Uint64ToStr_176) {
    XMLUtil::ToStr((uint64_t)9876543210ULL, buffer, sizeof(buffer));
    EXPECT_STREQ("9876543210", buffer);
}

// ==================== ReadBOM Tests ====================

class XMLUtilReadBOMTest_176 : public ::testing::Test {
protected:
    bool hasBOM;
};

TEST_F(XMLUtilReadBOMTest_176, NoBOM_176) {
    const char* input = "Hello";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilReadBOMTest_176, WithBOM_176) {
    const char input[] = "\xEF\xBB\xBFHello";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

TEST_F(XMLUtilReadBOMTest_176, EmptyStringNoBOM_176) {
    const char* input = "";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
}

// ==================== IsWhiteSpace Tests ====================

TEST(XMLUtilIsWhiteSpaceTest_176, Space_176) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilIsWhiteSpaceTest_176, Tab_176) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilIsWhiteSpaceTest_176, Newline_176) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilIsWhiteSpaceTest_176, CarriageReturn_176) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilIsWhiteSpaceTest_176, NonWhitespace_176) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST(XMLUtilIsWhiteSpaceTest_176, Digit_176) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('5'));
}

// ==================== SkipWhiteSpace Tests ====================

TEST(XMLUtilSkipWhiteSpaceTest_176, SkipsLeadingSpaces_176) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST(XMLUtilSkipWhiteSpaceTest_176, NoLeadingSpaces_176) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST(XMLUtilSkipWhiteSpaceTest_176, AllWhiteSpace_176) {
    const char* input = "   \t\n";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("", result);
}

TEST(XMLUtilSkipWhiteSpaceTest_176, CountsNewlines_176) {
    int lineNum = 1;
    const char* input = "\n\n  hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(3, lineNum);
}

TEST(XMLUtilSkipWhiteSpaceTest_176, NullReturnsZero_176) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(nullptr, result);
}

// ==================== StringEqual Tests ====================

TEST(XMLUtilStringEqualTest_176, EqualStrings_176) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilStringEqualTest_176, DifferentStrings_176) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilStringEqualTest_176, PartialMatch_176) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
}

TEST(XMLUtilStringEqualTest_176, BothNull_176) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilStringEqualTest_176, OneNull_176) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilStringEqualTest_176, EmptyStrings_176) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

// ==================== IsNameStartChar / IsNameChar Tests ====================

TEST(XMLUtilIsNameStartCharTest_176, Letter_176) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
}

TEST(XMLUtilIsNameStartCharTest_176, Underscore_176) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilIsNameStartCharTest_176, Colon_176) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilIsNameStartCharTest_176, Digit_176) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST(XMLUtilIsNameCharTest_176, Digit_176) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST(XMLUtilIsNameCharTest_176, Letter_176) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
}

TEST(XMLUtilIsNameCharTest_176, Dot_176) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilIsNameCharTest_176, Hyphen_176) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilIsNameCharTest_176, Space_176) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ==================== IsPrefixHex Tests ====================

TEST(XMLUtilIsPrefixHexTest_176, ValidHexPrefix_176) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilIsPrefixHexTest_176, NoHexPrefix_176) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST(XMLUtilIsPrefixHexTest_176, JustZero_176) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

TEST(XMLUtilConvertUTF32ToUTF8Test_176, AsciiChar_176) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST(XMLUtilConvertUTF32ToUTF8Test_176, TwoByteChar_176) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(2, length);
}

TEST(XMLUtilConvertUTF32ToUTF8Test_176, ThreeByteChar_176) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length); // 中
    EXPECT_EQ(3, length);
}

TEST(XMLUtilConvertUTF32ToUTF8Test_176, FourByteChar_176) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(4, length);
}

// ==================== SetBoolSerialization Tests ====================

TEST(XMLUtilSetBoolSerializationTest_176, CustomBoolSerialization_176) {
    char buffer[256];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ==================== Round-trip Tests ====================

TEST(XMLUtilRoundTripTest_176, IntRoundTrip_176) {
    char buffer[256];
    int original = -99999;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int parsed;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST(XMLUtilRoundTripTest_176, DoubleRoundTrip_176) {
    char buffer[256];
    double original = 1.23456789012345;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double parsed;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_DOUBLE_EQ(original, parsed);
}

TEST(XMLUtilRoundTripTest_176, Int64RoundTrip_176) {
    char buffer[256];
    int64_t original = 9223372036854775807LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t parsed;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST(XMLUtilRoundTripTest_176, Uint64RoundTrip_176) {
    char buffer[256];
    uint64_t original = 18446744073709551615ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t parsed;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}
