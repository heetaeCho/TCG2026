#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <cstring>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToStr(int, ...) tests
// ============================================================

TEST(XMLUtilToStrInt_170, PositiveValue_170) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST(XMLUtilToStrInt_170, NegativeValue_170) {
    char buffer[64];
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ("-123", buffer);
}

TEST(XMLUtilToStrInt_170, ZeroValue_170) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrInt_170, MaxInt_170) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilToStrInt_170, MinInt_170) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(unsigned int, ...) tests
// ============================================================

TEST(XMLUtilToStrUnsigned_170, PositiveValue_170) {
    char buffer[64];
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST(XMLUtilToStrUnsigned_170, ZeroValue_170) {
    char buffer[64];
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrUnsigned_170, MaxUnsigned_170) {
    char buffer[64];
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(bool, ...) tests
// ============================================================

TEST(XMLUtilToStrBool_170, TrueValue_170) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST(XMLUtilToStrBool_170, FalseValue_170) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// ToStr(float, ...) tests
// ============================================================

TEST(XMLUtilToStrFloat_170, PositiveFloat_170) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    // Just verify it's parseable back
    float val = 0;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_NEAR(3.14f, val, 0.001f);
}

TEST(XMLUtilToStrFloat_170, ZeroFloat_170) {
    char buffer[64];
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    float val = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_FLOAT_EQ(0.0f, val);
}

TEST(XMLUtilToStrFloat_170, NegativeFloat_170) {
    char buffer[64];
    XMLUtil::ToStr(-2.5f, buffer, sizeof(buffer));
    float val = 0;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_NEAR(-2.5f, val, 0.001f);
}

// ============================================================
// ToStr(double, ...) tests
// ============================================================

TEST(XMLUtilToStrDouble_170, PositiveDouble_170) {
    char buffer[64];
    XMLUtil::ToStr(3.14159265358979, buffer, sizeof(buffer));
    double val = 0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_NEAR(3.14159265358979, val, 1e-10);
}

TEST(XMLUtilToStrDouble_170, ZeroDouble_170) {
    char buffer[64];
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double val = 1.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_DOUBLE_EQ(0.0, val);
}

// ============================================================
// ToStr(int64_t, ...) tests
// ============================================================

TEST(XMLUtilToStrInt64_170, PositiveValue_170) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<int64_t>(1234567890123LL), buffer, sizeof(buffer));
    EXPECT_STREQ("1234567890123", buffer);
}

TEST(XMLUtilToStrInt64_170, NegativeValue_170) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<int64_t>(-1234567890123LL), buffer, sizeof(buffer));
    EXPECT_STREQ("-1234567890123", buffer);
}

TEST(XMLUtilToStrInt64_170, ZeroValue_170) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<int64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrInt64_170, MaxInt64_170) {
    char buffer[64];
    XMLUtil::ToStr(INT64_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)INT64_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilToStrInt64_170, MinInt64_170) {
    char buffer[64];
    XMLUtil::ToStr(INT64_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)INT64_MIN);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(uint64_t, ...) tests
// ============================================================

TEST(XMLUtilToStrUint64_170, PositiveValue_170) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<uint64_t>(9876543210ULL), buffer, sizeof(buffer));
    EXPECT_STREQ("9876543210", buffer);
}

TEST(XMLUtilToStrUint64_170, ZeroValue_170) {
    char buffer[64];
    XMLUtil::ToStr(static_cast<uint64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilToStrUint64_170, MaxUint64_170) {
    char buffer[64];
    XMLUtil::ToStr(UINT64_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%llu", (unsigned long long)UINT64_MAX);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToInt tests
// ============================================================

TEST(XMLUtilToInt_170, ValidPositive_170) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST(XMLUtilToInt_170, ValidNegative_170) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-99", &value));
    EXPECT_EQ(-99, value);
}

TEST(XMLUtilToInt_170, ValidZero_170) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST(XMLUtilToInt_170, InvalidString_170) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilToInt_170, NullString_170) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilToInt_170, EmptyString_170) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST(XMLUtilToInt_170, HexPrefix_170) {
    int value = 0;
    bool result = XMLUtil::ToInt("0x1A", &value);
    // Whether hex is supported depends on implementation; just check no crash
    (void)result;
}

// ============================================================
// ToUnsigned tests
// ============================================================

TEST(XMLUtilToUnsigned_170, ValidPositive_170) {
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &value));
    EXPECT_EQ(42u, value);
}

TEST(XMLUtilToUnsigned_170, ValidZero_170) {
    unsigned value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0u, value);
}

TEST(XMLUtilToUnsigned_170, InvalidString_170) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST(XMLUtilToUnsigned_170, NullString_170) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ============================================================
// ToBool tests
// ============================================================

TEST(XMLUtilToBool_170, TrueString_170) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilToBool_170, FalseString_170) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilToBool_170, NumericOne_170) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilToBool_170, NumericZero_170) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilToBool_170, InvalidString_170) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilToBool_170, NullString_170) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST(XMLUtilToBool_170, EmptyString_170) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// ============================================================
// ToFloat tests
// ============================================================

TEST(XMLUtilToFloat_170, ValidPositive_170) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.01f);
}

TEST(XMLUtilToFloat_170, ValidNegative_170) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_NEAR(-2.5f, value, 0.01f);
}

TEST(XMLUtilToFloat_170, ValidZero_170) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST(XMLUtilToFloat_170, InvalidString_170) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST(XMLUtilToFloat_170, NullString_170) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ============================================================
// ToDouble tests
// ============================================================

TEST(XMLUtilToDouble_170, ValidPositive_170) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159265358979", &value));
    EXPECT_NEAR(3.14159265358979, value, 1e-10);
}

TEST(XMLUtilToDouble_170, ValidNegative_170) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("-100.5", &value));
    EXPECT_NEAR(-100.5, value, 0.01);
}

TEST(XMLUtilToDouble_170, InvalidString_170) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("notanumber", &value));
}

TEST(XMLUtilToDouble_170, NullString_170) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ============================================================
// ToInt64 tests
// ============================================================

TEST(XMLUtilToInt64_170, ValidPositive_170) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(1234567890123LL, value);
}

TEST(XMLUtilToInt64_170, ValidNegative_170) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-1234567890123", &value));
    EXPECT_EQ(-1234567890123LL, value);
}

TEST(XMLUtilToInt64_170, ValidZero_170) {
    int64_t value = -1;
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0, value);
}

TEST(XMLUtilToInt64_170, InvalidString_170) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST(XMLUtilToInt64_170, NullString_170) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ============================================================
// ToUnsigned64 tests
// ============================================================

TEST(XMLUtilToUnsigned64_170, ValidPositive_170) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("9876543210", &value));
    EXPECT_EQ(9876543210ULL, value);
}

TEST(XMLUtilToUnsigned64_170, ValidZero_170) {
    uint64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0ULL, value);
}

TEST(XMLUtilToUnsigned64_170, InvalidString_170) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &value));
}

TEST(XMLUtilToUnsigned64_170, NullString_170) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// ReadBOM tests
// ============================================================

TEST(XMLUtilReadBOM_170, NoBOM_170) {
    bool hasBOM = true;
    const char* input = "<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST(XMLUtilReadBOM_170, WithBOM_170) {
    bool hasBOM = false;
    // UTF-8 BOM: EF BB BF
    const char input[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

TEST(XMLUtilReadBOM_170, NullInput_170) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    // Should handle null gracefully
    (void)result;
}

// ============================================================
// IsWhiteSpace tests
// ============================================================

TEST(XMLUtilIsWhiteSpace_170, Space_170) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilIsWhiteSpace_170, Tab_170) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilIsWhiteSpace_170, Newline_170) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilIsWhiteSpace_170, CarriageReturn_170) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilIsWhiteSpace_170, NonWhitespace_170) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilIsWhiteSpace_170, Digit_170) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST(XMLUtilIsWhiteSpace_170, NullChar_170) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// SkipWhiteSpace tests
// ============================================================

TEST(XMLUtilSkipWhiteSpace_170, LeadingSpaces_170) {
    const char* input = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('h', *result);
}

TEST(XMLUtilSkipWhiteSpace_170, NoLeadingWhitespace_170) {
    const char* input = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(input, result);
}

TEST(XMLUtilSkipWhiteSpace_170, AllWhitespace_170) {
    const char* input = "   \t\n  ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('\0', *result);
}

TEST(XMLUtilSkipWhiteSpace_170, NewlineIncrementsLineNum_170) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ('h', *result);
    EXPECT_EQ(3, lineNum);
}

TEST(XMLUtilSkipWhiteSpace_170, NullLineNum_170) {
    const char* input = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ('h', *result);
}

// ============================================================
// StringEqual tests
// ============================================================

TEST(XMLUtilStringEqual_170, EqualStrings_170) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilStringEqual_170, DifferentStrings_170) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilStringEqual_170, PartialEqual_170) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
}

TEST(XMLUtilStringEqual_170, BothNull_170) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilStringEqual_170, OneNull_170) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilStringEqual_170, EmptyStrings_170) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilStringEqual_170, NCharZero_170) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

// ============================================================
// IsNameStartChar tests
// ============================================================

TEST(XMLUtilIsNameStartChar_170, Letter_170) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST(XMLUtilIsNameStartChar_170, Underscore_170) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilIsNameStartChar_170, Colon_170) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilIsNameStartChar_170, Digit_170) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST(XMLUtilIsNameStartChar_170, Hyphen_170) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

// ============================================================
// IsNameChar tests
// ============================================================

TEST(XMLUtilIsNameChar_170, Letter_170) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
}

TEST(XMLUtilIsNameChar_170, Digit_170) {
    EXPECT_TRUE(XMLUtil::IsNameChar('5'));
}

TEST(XMLUtilIsNameChar_170, Hyphen_170) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilIsNameChar_170, Dot_170) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilIsNameChar_170, Space_170) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex tests
// ============================================================

TEST(XMLUtilIsPrefixHex_170, ValidHexPrefix_170) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilIsPrefixHex_170, NotHexPrefix_170) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST(XMLUtilIsPrefixHex_170, JustZero_170) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// IsUTF8Continuation tests
// ============================================================

TEST(XMLUtilIsUTF8Continuation_170, ContinuationByte_170) {
    // UTF-8 continuation bytes are 10xxxxxx (0x80-0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST(XMLUtilIsUTF8Continuation_170, NonContinuationByte_170) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
}

// ============================================================
// ConvertUTF32ToUTF8 tests
// ============================================================

TEST(XMLUtilConvertUTF32ToUTF8_170, AsciiChar_170) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST(XMLUtilConvertUTF32ToUTF8_170, TwoByteChar_170) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST(XMLUtilConvertUTF32ToUTF8_170, ThreeByteChar_170) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(3, length);
}

TEST(XMLUtilConvertUTF32ToUTF8_170, FourByteChar_170) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(4, length);
}

TEST(XMLUtilConvertUTF32ToUTF8_170, ZeroCodepoint_170) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0, output, &length);
    // Zero codepoint - implementation dependent
    (void)length;
}

// ============================================================
// SetBoolSerialization tests
// ============================================================

TEST(XMLUtilSetBoolSerialization_170, CustomTrueFalse_170) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilSetBoolSerialization_170, ResetToDefault_170) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// GetCharacterRef tests
// ============================================================

TEST(XMLUtilGetCharacterRef_170, DecimalRef_170) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilGetCharacterRef_170, HexRef_170) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

// ============================================================
// Roundtrip tests (ToStr -> To* conversion)
// ============================================================

TEST(XMLUtilRoundTrip_170, IntRoundTrip_170) {
    char buffer[64];
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(12345, value);
}

TEST(XMLUtilRoundTrip_170, Int64RoundTrip_170) {
    char buffer[64];
    int64_t original = 9876543210123LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST(XMLUtilRoundTrip_170, Uint64RoundTrip_170) {
    char buffer[64];
    uint64_t original = 18446744073709551610ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST(XMLUtilRoundTrip_170, BoolTrueRoundTrip_170) {
    // Reset serialization to default first
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilRoundTrip_170, BoolFalseRoundTrip_170) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilRoundTrip_170, DoubleRoundTrip_170) {
    char buffer[64];
    double original = 1.23456789012345;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(original, value, 1e-10);
}
