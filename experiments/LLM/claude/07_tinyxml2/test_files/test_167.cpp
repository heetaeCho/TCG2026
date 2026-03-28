#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>
#include <cmath>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToStr(bool) Tests
// ============================================================

TEST(XMLUtilToStrBool_167, TrueValue_167) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST(XMLUtilToStrBool_167, FalseValue_167) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// ToStr(int) Tests
// ============================================================

TEST(XMLUtilToStrInt_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrInt_167, PositiveValue_167) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST(XMLUtilToStrInt_167, NegativeValue_167) {
    char buffer[64];
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ("-123", buffer);
}

TEST(XMLUtilToStrInt_167, MaxInt_167) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilToStrInt_167, MinInt_167) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(unsigned int) Tests
// ============================================================

TEST(XMLUtilToStrUnsigned_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr((unsigned int)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrUnsigned_167, MaxUnsigned_167) {
    char buffer[64];
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(float) Tests
// ============================================================

TEST(XMLUtilToStrFloat_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    // Should produce some string representation of 0
    float parsed = std::stof(buffer);
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST(XMLUtilToStrFloat_167, PositiveFloat_167) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(3.14f, parsed, 0.001f);
}

TEST(XMLUtilToStrFloat_167, NegativeFloat_167) {
    char buffer[64];
    XMLUtil::ToStr(-2.5f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(-2.5f, parsed, 0.001f);
}

// ============================================================
// ToStr(double) Tests
// ============================================================

TEST(XMLUtilToStrDouble_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_DOUBLE_EQ(0.0, parsed);
}

TEST(XMLUtilToStrDouble_167, PositiveDouble_167) {
    char buffer[64];
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(3.141592653589793, parsed, 1e-10);
}

TEST(XMLUtilToStrDouble_167, NegativeDouble_167) {
    char buffer[64];
    XMLUtil::ToStr(-1.23456789, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(-1.23456789, parsed, 1e-6);
}

// ============================================================
// ToStr(int64_t) Tests
// ============================================================

TEST(XMLUtilToStrInt64_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr((int64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrInt64_167, LargePositive_167) {
    char buffer[64];
    int64_t v = INT64_MAX;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)v);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilToStrInt64_167, LargeNegative_167) {
    char buffer[64];
    int64_t v = INT64_MIN;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)v);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(uint64_t) Tests
// ============================================================

TEST(XMLUtilToStrUint64_167, Zero_167) {
    char buffer[64];
    XMLUtil::ToStr((uint64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrUint64_167, MaxValue_167) {
    char buffer[64];
    uint64_t v = UINT64_MAX;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%llu", (unsigned long long)v);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToInt Tests
// ============================================================

TEST(XMLUtilToInt_167, ValidPositive_167) {
    int value = 0;
    bool result = XMLUtil::ToInt("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42, value);
}

TEST(XMLUtilToInt_167, ValidNegative_167) {
    int value = 0;
    bool result = XMLUtil::ToInt("-100", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-100, value);
}

TEST(XMLUtilToInt_167, ValidZero_167) {
    int value = -1;
    bool result = XMLUtil::ToInt("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST(XMLUtilToInt_167, InvalidString_167) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToInt_167, NullString_167) {
    int value = 0;
    bool result = XMLUtil::ToInt(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToInt_167, EmptyString_167) {
    int value = 0;
    bool result = XMLUtil::ToInt("", &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToUnsigned Tests
// ============================================================

TEST(XMLUtilToUnsigned_167, ValidPositive_167) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42u, value);
}

TEST(XMLUtilToUnsigned_167, ValidZero_167) {
    unsigned int value = 1;
    bool result = XMLUtil::ToUnsigned("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST(XMLUtilToUnsigned_167, InvalidString_167) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("xyz", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToUnsigned_167, NullString_167) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToBool Tests
// ============================================================

TEST(XMLUtilToBool_167, TrueString_167) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST(XMLUtilToBool_167, FalseString_167) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST(XMLUtilToBool_167, NumericOne_167) {
    bool value = false;
    bool result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST(XMLUtilToBool_167, NumericZero_167) {
    bool value = true;
    bool result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST(XMLUtilToBool_167, InvalidString_167) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToBool_167, NullString_167) {
    bool value = false;
    bool result = XMLUtil::ToBool(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToBool_167, EmptyString_167) {
    bool value = false;
    bool result = XMLUtil::ToBool("", &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToFloat Tests
// ============================================================

TEST(XMLUtilToFloat_167, ValidPositive_167) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST(XMLUtilToFloat_167, ValidNegative_167) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("-2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(-2.5f, value, 0.001f);
}

TEST(XMLUtilToFloat_167, ValidZero_167) {
    float value = 1.0f;
    bool result = XMLUtil::ToFloat("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST(XMLUtilToFloat_167, InvalidString_167) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToFloat_167, NullString_167) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToDouble Tests
// ============================================================

TEST(XMLUtilToDouble_167, ValidPositive_167) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("3.141592653589793", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.141592653589793, value, 1e-10);
}

TEST(XMLUtilToDouble_167, ValidNegative_167) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("-1.5", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(-1.5, value);
}

TEST(XMLUtilToDouble_167, InvalidString_167) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("xyz", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToDouble_167, NullString_167) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToInt64 Tests
// ============================================================

TEST(XMLUtilToInt64_167, ValidPositive_167) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9999999999", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(9999999999LL, value);
}

TEST(XMLUtilToInt64_167, ValidNegative_167) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("-9999999999", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-9999999999LL, value);
}

TEST(XMLUtilToInt64_167, ValidZero_167) {
    int64_t value = 1;
    bool result = XMLUtil::ToInt64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST(XMLUtilToInt64_167, InvalidString_167) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("abc", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToInt64_167, NullString_167) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToUnsigned64 Tests
// ============================================================

TEST(XMLUtilToUnsigned64_167, ValidPositive_167) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(UINT64_MAX, value);
}

TEST(XMLUtilToUnsigned64_167, ValidZero_167) {
    uint64_t value = 1;
    bool result = XMLUtil::ToUnsigned64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST(XMLUtilToUnsigned64_167, InvalidString_167) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilToUnsigned64_167, NullString_167) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

TEST(XMLUtilSetBoolSerialization_167, CustomBoolStrings_167) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilSetBoolSerialization_167, ResetToDefault_167) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// ReadBOM Tests
// ============================================================

TEST(XMLUtilReadBOM_167, NoBOM_167) {
    bool hasBOM = true;
    const char* input = "<xml>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST(XMLUtilReadBOM_167, WithBOM_167) {
    bool hasBOM = false;
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char input[] = "\xEF\xBB\xBF<xml>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

TEST(XMLUtilIsWhiteSpace_167, Space_167) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilIsWhiteSpace_167, Tab_167) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilIsWhiteSpace_167, Newline_167) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilIsWhiteSpace_167, CarriageReturn_167) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilIsWhiteSpace_167, NonWhiteSpace_167) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilIsWhiteSpace_167, NullChar_167) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

TEST(XMLUtilSkipWhiteSpace_167, LeadingSpaces_167) {
    const char* input = "   hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('h', *result);
}

TEST(XMLUtilSkipWhiteSpace_167, NoWhiteSpace_167) {
    const char* input = "hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(input, result);
}

TEST(XMLUtilSkipWhiteSpace_167, NewlineIncrementsLine_167) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('h', *result);
    EXPECT_EQ(3, lineNum);
}

TEST(XMLUtilSkipWhiteSpace_167, NullLineNumPtr_167) {
    const char* input = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ('h', *result);
}

// ============================================================
// StringEqual Tests
// ============================================================

TEST(XMLUtilStringEqual_167, EqualStrings_167) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilStringEqual_167, UnequalStrings_167) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilStringEqual_167, PartialCompare_167) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST(XMLUtilStringEqual_167, BothNull_167) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilStringEqual_167, OneNull_167) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilStringEqual_167, EmptyStrings_167) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

// ============================================================
// IsNameStartChar Tests
// ============================================================

TEST(XMLUtilIsNameStartChar_167, Letter_167) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST(XMLUtilIsNameStartChar_167, Underscore_167) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilIsNameStartChar_167, Colon_167) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilIsNameStartChar_167, Digit_167) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST(XMLUtilIsNameStartChar_167, Space_167) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
}

// ============================================================
// IsNameChar Tests
// ============================================================

TEST(XMLUtilIsNameChar_167, Letter_167) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST(XMLUtilIsNameChar_167, Digit_167) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST(XMLUtilIsNameChar_167, Hyphen_167) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilIsNameChar_167, Dot_167) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilIsNameChar_167, Space_167) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

TEST(XMLUtilIsPrefixHex_167, HexPrefix_167) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilIsPrefixHex_167, NoHexPrefix_167) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

TEST(XMLUtilIsUTF8Continuation_167, ContinuationByte_167) {
    // Continuation bytes are 10xxxxxx (0x80 - 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST(XMLUtilIsUTF8Continuation_167, NonContinuationByte_167) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

TEST(XMLUtilConvertUTF32ToUTF8_167, AsciiCharacter_167) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST(XMLUtilConvertUTF32ToUTF8_167, TwoByteCharacter_167) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(2, length);
}

TEST(XMLUtilConvertUTF32ToUTF8_167, ThreeByteCharacter_167) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length); // 中
    EXPECT_EQ(3, length);
}

TEST(XMLUtilConvertUTF32ToUTF8_167, FourByteCharacter_167) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // Emoji
    EXPECT_EQ(4, length);
}

// ============================================================
// GetCharacterRef Tests
// ============================================================

TEST(XMLUtilGetCharacterRef_167, DecimalRef_167) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilGetCharacterRef_167, HexRef_167) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

// ============================================================
// Roundtrip tests: ToStr -> ToXxx
// ============================================================

TEST(XMLUtilRoundtrip_167, IntRoundtrip_167) {
    char buffer[64];
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(12345, value);
}

TEST(XMLUtilRoundtrip_167, DoubleRoundtrip_167) {
    char buffer[64];
    XMLUtil::ToStr(1.23456789, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(1.23456789, value, 1e-6);
}

TEST(XMLUtilRoundtrip_167, BoolTrueRoundtrip_167) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilRoundtrip_167, BoolFalseRoundtrip_167) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilRoundtrip_167, Int64Roundtrip_167) {
    char buffer[64];
    int64_t original = 9223372036854775807LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST(XMLUtilRoundtrip_167, Uint64Roundtrip_167) {
    char buffer[64];
    uint64_t original = 18446744073709551615ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST(XMLUtilRoundtrip_167, FloatRoundtrip_167) {
    char buffer[64];
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &value));
    EXPECT_FLOAT_EQ(1.5f, value);
}
