#include <gtest/gtest.h>
#include <cmath>
#include <climits>
#include <cstdint>
#include <cfloat>
#include <cstring>

// Include the header for the class under test
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToFloat Tests
// ============================================================

class XMLUtilToFloatTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToFloatTest_175, ValidPositiveInteger_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("42", &value));
    EXPECT_FLOAT_EQ(42.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidNegativeInteger_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-42", &value));
    EXPECT_FLOAT_EQ(-42.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidPositiveFloat_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidNegativeFloat_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-3.14", &value));
    EXPECT_FLOAT_EQ(-3.14f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidZero_175) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidZeroPointZero_175) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0.0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidScientificNotation_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("1.5e2", &value));
    EXPECT_FLOAT_EQ(150.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidScientificNotationNegativeExponent_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("1.5e-2", &value));
    EXPECT_FLOAT_EQ(0.015f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidScientificNotationUpperE_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("1.5E3", &value));
    EXPECT_FLOAT_EQ(1500.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidLeadingWhitespace_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("  3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidTrailingText_175) {
    float value = 0.0f;
    // sscanf with %f should parse the leading number and succeed
    EXPECT_TRUE(XMLUtil::ToFloat("3.14abc", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_175, InvalidEmptyString_175) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

TEST_F(XMLUtilToFloatTest_175, InvalidNonNumericString_175) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilToFloatTest_175, InvalidOnlyWhitespace_175) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("   ", &value));
}

TEST_F(XMLUtilToFloatTest_175, ValidLeadingPlusSign_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("+3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidVerySmallNumber_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("1.17549e-38", &value));
    EXPECT_TRUE(value > 0.0f);
}

TEST_F(XMLUtilToFloatTest_175, ValidVeryLargeNumber_175) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.40282e+38", &value));
    EXPECT_TRUE(value > 0.0f);
}

TEST_F(XMLUtilToFloatTest_175, ValidNegativeZero_175) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-0.0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_175, ValidDecimalPointOnly_175) {
    float value = 1.0f;
    // ".5" should be parseable by sscanf
    EXPECT_TRUE(XMLUtil::ToFloat(".5", &value));
    EXPECT_FLOAT_EQ(0.5f, value);
}

// ============================================================
// ToInt Tests
// ============================================================

class XMLUtilToIntTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToIntTest_175, ValidPositiveInteger_175) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(123, value);
}

TEST_F(XMLUtilToIntTest_175, ValidNegativeInteger_175) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(-456, value);
}

TEST_F(XMLUtilToIntTest_175, ValidZero_175) {
    int value = 1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToIntTest_175, InvalidEmptyString_175) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilToIntTest_175, InvalidNonNumeric_175) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilToIntTest_175, ValidLeadingWhitespace_175) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("  42", &value));
    EXPECT_EQ(42, value);
}

// ============================================================
// ToUnsigned Tests
// ============================================================

class XMLUtilToUnsignedTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToUnsignedTest_175, ValidPositiveInteger_175) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(123u, value);
}

TEST_F(XMLUtilToUnsignedTest_175, ValidZero_175) {
    unsigned int value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsignedTest_175, InvalidNonNumeric_175) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilToUnsignedTest_175, InvalidEmptyString_175) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

// ============================================================
// ToBool Tests
// ============================================================

class XMLUtilToBoolTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToBoolTest_175, ValidTrue_175) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_175, ValidFalse_175) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_175, ValidOne_175) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_175, ValidZero_175) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_175, InvalidString_175) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilToBoolTest_175, InvalidEmptyString_175) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// ============================================================
// ToDouble Tests
// ============================================================

class XMLUtilToDoubleTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToDoubleTest_175, ValidPositiveDouble_175) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159265358979", &value));
    EXPECT_DOUBLE_EQ(3.14159265358979, value);
}

TEST_F(XMLUtilToDoubleTest_175, ValidNegativeDouble_175) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("-2.718281828", &value));
    EXPECT_DOUBLE_EQ(-2.718281828, value);
}

TEST_F(XMLUtilToDoubleTest_175, ValidZero_175) {
    double value = 1.0;
    EXPECT_TRUE(XMLUtil::ToDouble("0.0", &value));
    EXPECT_DOUBLE_EQ(0.0, value);
}

TEST_F(XMLUtilToDoubleTest_175, InvalidNonNumeric_175) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("hello", &value));
}

TEST_F(XMLUtilToDoubleTest_175, InvalidEmptyString_175) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

TEST_F(XMLUtilToDoubleTest_175, ValidScientificNotation_175) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("1.23e10", &value));
    EXPECT_DOUBLE_EQ(1.23e10, value);
}

// ============================================================
// ToInt64 Tests
// ============================================================

class XMLUtilToInt64Test_175 : public ::testing::Test {};

TEST_F(XMLUtilToInt64Test_175, ValidPositive_175) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(1234567890123LL, value);
}

TEST_F(XMLUtilToInt64Test_175, ValidNegative_175) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-1234567890123", &value));
    EXPECT_EQ(-1234567890123LL, value);
}

TEST_F(XMLUtilToInt64Test_175, ValidZero_175) {
    int64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0LL, value);
}

TEST_F(XMLUtilToInt64Test_175, InvalidNonNumeric_175) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilToInt64Test_175, InvalidEmptyString_175) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

// ============================================================
// ToUnsigned64 Tests
// ============================================================

class XMLUtilToUnsigned64Test_175 : public ::testing::Test {};

TEST_F(XMLUtilToUnsigned64Test_175, ValidPositive_175) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("9876543210", &value));
    EXPECT_EQ(9876543210ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_175, ValidZero_175) {
    uint64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_175, InvalidNonNumeric_175) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilToUnsigned64Test_175, InvalidEmptyString_175) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

// ============================================================
// ToStr Tests
// ============================================================

class XMLUtilToStrTest_175 : public ::testing::Test {};

TEST_F(XMLUtilToStrTest_175, IntToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_175, NegativeIntToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(-42, buffer, sizeof(buffer));
    EXPECT_STREQ("-42", buffer);
}

TEST_F(XMLUtilToStrTest_175, ZeroIntToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_175, UnsignedToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_175, BoolTrueToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_175, BoolFalseToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_175, FloatToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    // Verify it can be parsed back
    float val = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_NEAR(3.14f, val, 0.001f);
}

TEST_F(XMLUtilToStrTest_175, DoubleToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(3.14159265358979, buffer, sizeof(buffer));
    double val = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_NEAR(3.14159265358979, val, 1e-10);
}

TEST_F(XMLUtilToStrTest_175, Int64ToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<int64_t>(1234567890123LL), buffer, sizeof(buffer));
    int64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &val));
    EXPECT_EQ(1234567890123LL, val);
}

TEST_F(XMLUtilToStrTest_175, Uint64ToStr_175) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<uint64_t>(9876543210ULL), buffer, sizeof(buffer));
    uint64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &val));
    EXPECT_EQ(9876543210ULL, val);
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilIsWhiteSpaceTest_175 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_175, SpaceIsWhiteSpace_175) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, TabIsWhiteSpace_175) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, NewlineIsWhiteSpace_175) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, CarriageReturnIsWhiteSpace_175) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, LetterIsNotWhiteSpace_175) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, DigitIsNotWhiteSpace_175) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_175, NullIsNotWhiteSpace_175) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_175 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_175, EqualStrings_175) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_175, DifferentStrings_175) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_175, BothNull_175) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_175, OneNull_175) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_175, PartialCompareEqual_175) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helly", 4));
}

TEST_F(XMLUtilStringEqualTest_175, PartialCompareDifferent_175) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world", 3));
}

TEST_F(XMLUtilStringEqualTest_175, EmptyStrings_175) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_175, ZeroLengthCompare_175) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_175 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_175, LetterIsNameStartChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_175, UnderscoreIsNameStartChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_175, ColonIsNameStartChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_175, DigitIsNotNameStartChar_175) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_175, DigitIsNameChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_175, DashIsNameChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_175, DotIsNameChar_175) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_175, SpaceIsNotNameChar_175) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilIsPrefixHexTest_175 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_175, ValidHexPrefix_175) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_175, NotHexPrefix_175) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0a"));
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilReadBOMTest_175 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_175, NoBOM_175) {
    bool hasBOM = true;
    const char* input = "<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilReadBOMTest_175, WithUTF8BOM_175) {
    bool hasBOM = false;
    // UTF-8 BOM: EF BB BF
    const char input[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    // Result should skip past the BOM
    EXPECT_EQ(input + 3, result);
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_175 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_175, SkipsLeadingSpaces_175) {
    const char* input = "   hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('h', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_175, SkipsTabsAndNewlines_175) {
    const char* input = "\t\n\r world";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('w', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_175, NoWhiteSpace_175) {
    const char* input = "hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_175, NullInput_175) {
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), &lineNum);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_175, CountsNewlines_175) {
    const char* input = "\n\n\nhello";
    int lineNum = 1;
    XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(4, lineNum);
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilConvertUTF32ToUTF8Test_175 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_175, ASCIICharacter_175) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_175, TwoByteCharacter_175) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_175, ThreeByteCharacter_175) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // Euro sign
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_175, FourByteCharacter_175) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // Emoji
    EXPECT_EQ(4, length);
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

class XMLUtilIsUTF8ContinuationTest_175 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_175, ContinuationByte_175) {
    // Continuation bytes are 10xxxxxx (0x80-0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_175, NonContinuationByte_175) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xC0)));
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilSetBoolSerializationTest_175 : public ::testing::Test {};

TEST_F(XMLUtilSetBoolSerializationTest_175, CustomBoolSerialization_175) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLUtilSetBoolSerializationTest_175, ResetToDefault_175) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// Roundtrip Tests (ToStr -> ToXxx)
// ============================================================

class XMLUtilRoundtripTest_175 : public ::testing::Test {};

TEST_F(XMLUtilRoundtripTest_175, IntRoundtrip_175) {
    char buffer[64];
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(12345, value);
}

TEST_F(XMLUtilRoundtripTest_175, FloatRoundtrip_175) {
    char buffer[64];
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &value));
    EXPECT_FLOAT_EQ(1.5f, value);
}

TEST_F(XMLUtilRoundtripTest_175, DoubleRoundtrip_175) {
    char buffer[64];
    XMLUtil::ToStr(1.23456789012345, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(1.23456789012345, value, 1e-10);
}

TEST_F(XMLUtilRoundtripTest_175, BoolTrueRoundtrip_175) {
    char buffer[64];
    XMLUtil::SetBoolSerialization(nullptr, nullptr); // ensure default
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilRoundtripTest_175, BoolFalseRoundtrip_175) {
    char buffer[64];
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilRoundtripTest_175, Int64Roundtrip_175) {
    char buffer[64];
    int64_t original = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_175, Uint64Roundtrip_175) {
    char buffer[64];
    uint64_t original = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}
