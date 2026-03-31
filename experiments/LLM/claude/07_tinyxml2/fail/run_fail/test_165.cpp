#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>
#include <cfloat>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToStr(int, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Int_Positive_165) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST(XMLUtilTest_165, ToStr_Int_Negative_165) {
    char buffer[64];
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ("-123", buffer);
}

TEST(XMLUtilTest_165, ToStr_Int_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilTest_165, ToStr_Int_MaxValue_165) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilTest_165, ToStr_Int_MinValue_165) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(unsigned int, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Unsigned_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilTest_165, ToStr_Unsigned_Positive_165) {
    char buffer[64];
    XMLUtil::ToStr(999u, buffer, sizeof(buffer));
    EXPECT_STREQ("999", buffer);
}

TEST(XMLUtilTest_165, ToStr_Unsigned_MaxValue_165) {
    char buffer[64];
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToStr(bool, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Bool_True_165) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST(XMLUtilTest_165, ToStr_Bool_False_165) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// ToStr(float, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Float_Positive_165) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(3.14f, parsed, 0.001f);
}

TEST(XMLUtilTest_165, ToStr_Float_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST(XMLUtilTest_165, ToStr_Float_Negative_165) {
    char buffer[64];
    XMLUtil::ToStr(-2.5f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(-2.5f, parsed, 0.001f);
}

// ============================================================
// ToStr(double, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Double_Positive_165) {
    char buffer[64];
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(3.141592653589793, parsed, 1e-10);
}

TEST(XMLUtilTest_165, ToStr_Double_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_DOUBLE_EQ(0.0, parsed);
}

TEST(XMLUtilTest_165, ToStr_Double_Negative_165) {
    char buffer[64];
    XMLUtil::ToStr(-1.0e10, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(-1.0e10, parsed, 1.0);
}

// ============================================================
// ToStr(int64_t, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_Int64_Positive_165) {
    char buffer[64];
    int64_t val = 1234567890123LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilTest_165, ToStr_Int64_Negative_165) {
    char buffer[64];
    int64_t val = -9876543210LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilTest_165, ToStr_Int64_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr((int64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

// ============================================================
// ToStr(uint64_t, ...) Tests
// ============================================================

TEST(XMLUtilTest_165, ToStr_UInt64_Positive_165) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%llu", (unsigned long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST(XMLUtilTest_165, ToStr_UInt64_Zero_165) {
    char buffer[64];
    XMLUtil::ToStr((uint64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

// ============================================================
// ToInt Tests
// ============================================================

TEST(XMLUtilTest_165, ToInt_ValidPositive_165) {
    int value = 0;
    bool result = XMLUtil::ToInt("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42, value);
}

TEST(XMLUtilTest_165, ToInt_ValidNegative_165) {
    int value = 0;
    bool result = XMLUtil::ToInt("-100", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-100, value);
}

TEST(XMLUtilTest_165, ToInt_Zero_165) {
    int value = -1;
    bool result = XMLUtil::ToInt("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST(XMLUtilTest_165, ToInt_InvalidString_165) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToInt_NullString_165) {
    int value = 0;
    bool result = XMLUtil::ToInt(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToInt_EmptyString_165) {
    int value = 0;
    bool result = XMLUtil::ToInt("", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToInt_HexPrefix_165) {
    int value = 0;
    bool result = XMLUtil::ToInt("0x1A", &value);
    // Hex may or may not be supported; just check it doesn't crash
    // If it returns true, the value should be 26
    if (result) {
        EXPECT_EQ(26, value);
    }
}

// ============================================================
// ToUnsigned Tests
// ============================================================

TEST(XMLUtilTest_165, ToUnsigned_ValidPositive_165) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("255", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(255u, value);
}

TEST(XMLUtilTest_165, ToUnsigned_Zero_165) {
    unsigned int value = 1;
    bool result = XMLUtil::ToUnsigned("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST(XMLUtilTest_165, ToUnsigned_Invalid_165) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("xyz", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToUnsigned_Null_165) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToBool Tests
// ============================================================

TEST(XMLUtilTest_165, ToBool_TrueString_165) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_165, ToBool_FalseString_165) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_165, ToBool_One_165) {
    bool value = false;
    bool result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_165, ToBool_Zero_165) {
    bool value = true;
    bool result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_165, ToBool_InvalidString_165) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToBool_NullString_165) {
    bool value = false;
    bool result = XMLUtil::ToBool(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToBool_EmptyString_165) {
    bool value = false;
    bool result = XMLUtil::ToBool("", &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToFloat Tests
// ============================================================

TEST(XMLUtilTest_165, ToFloat_ValidPositive_165) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST(XMLUtilTest_165, ToFloat_ValidNegative_165) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("-2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(-2.5f, value, 0.001f);
}

TEST(XMLUtilTest_165, ToFloat_Zero_165) {
    float value = 1.0f;
    bool result = XMLUtil::ToFloat("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST(XMLUtilTest_165, ToFloat_Invalid_165) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("not_a_number", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToFloat_Null_165) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToDouble Tests
// ============================================================

TEST(XMLUtilTest_165, ToDouble_ValidPositive_165) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("3.141592653589793", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.141592653589793, value, 1e-12);
}

TEST(XMLUtilTest_165, ToDouble_ValidNegative_165) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("-1.5e10", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(-1.5e10, value, 1.0);
}

TEST(XMLUtilTest_165, ToDouble_Invalid_165) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("hello", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToDouble_Null_165) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToInt64 Tests
// ============================================================

TEST(XMLUtilTest_165, ToInt64_ValidPositive_165) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("1234567890123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1234567890123LL, value);
}

TEST(XMLUtilTest_165, ToInt64_ValidNegative_165) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("-9876543210", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-9876543210LL, value);
}

TEST(XMLUtilTest_165, ToInt64_Invalid_165) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("abc", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToInt64_Null_165) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToUnsigned64 Tests
// ============================================================

TEST(XMLUtilTest_165, ToUnsigned64_ValidPositive_165) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(18446744073709551615ULL, value);
}

TEST(XMLUtilTest_165, ToUnsigned64_Zero_165) {
    uint64_t value = 1;
    bool result = XMLUtil::ToUnsigned64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0ULL, value);
}

TEST(XMLUtilTest_165, ToUnsigned64_Invalid_165) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("not_a_number", &value);
    EXPECT_FALSE(result);
}

TEST(XMLUtilTest_165, ToUnsigned64_Null_165) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ReadBOM Tests
// ============================================================

TEST(XMLUtilTest_165, ReadBOM_NoBOM_165) {
    bool hasBOM = true;
    const char* input = "Hello";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST(XMLUtilTest_165, ReadBOM_WithBOM_165) {
    bool hasBOM = false;
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char input[] = "\xEF\xBB\xBFHello";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

TEST(XMLUtilTest_165, ReadBOM_NullPointer_165) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    // Should handle null gracefully
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

TEST(XMLUtilTest_165, IsWhiteSpace_Space_165) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_165, IsWhiteSpace_Tab_165) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_165, IsWhiteSpace_Newline_165) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_165, IsWhiteSpace_CarriageReturn_165) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_165, IsWhiteSpace_Letter_165) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilTest_165, IsWhiteSpace_Digit_165) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST(XMLUtilTest_165, IsWhiteSpace_NullChar_165) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

TEST(XMLUtilTest_165, SkipWhiteSpace_LeadingSpaces_165) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST(XMLUtilTest_165, SkipWhiteSpace_NoSpaces_165) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST(XMLUtilTest_165, SkipWhiteSpace_AllSpaces_165) {
    const char* input = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("", result);
}

TEST(XMLUtilTest_165, SkipWhiteSpace_MixedWhitespace_165) {
    const char* input = " \t\n\rtest";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("test", result);
}

TEST(XMLUtilTest_165, SkipWhiteSpace_CountsNewlines_165) {
    const char* input = "\n\n\ntest";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("test", result);
    EXPECT_EQ(4, lineNum);
}

TEST(XMLUtilTest_165, SkipWhiteSpace_NullInput_165) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// StringEqual Tests
// ============================================================

TEST(XMLUtilTest_165, StringEqual_EqualStrings_165) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_165, StringEqual_DifferentStrings_165) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_165, StringEqual_WithNChar_165) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST(XMLUtilTest_165, StringEqual_WithNChar_Different_165) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hallo", 5));
}

TEST(XMLUtilTest_165, StringEqual_BothNull_165) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilTest_165, StringEqual_OneNull_165) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilTest_165, StringEqual_EmptyStrings_165) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilTest_165, StringEqual_EmptyAndNonEmpty_165) {
    EXPECT_FALSE(XMLUtil::StringEqual("", "hello"));
}

// ============================================================
// IsNameStartChar Tests
// ============================================================

TEST(XMLUtilTest_165, IsNameStartChar_Letter_165) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST(XMLUtilTest_165, IsNameStartChar_Underscore_165) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_165, IsNameStartChar_Colon_165) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_165, IsNameStartChar_Digit_165) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST(XMLUtilTest_165, IsNameStartChar_Hyphen_165) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST(XMLUtilTest_165, IsNameStartChar_Dot_165) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

// ============================================================
// IsNameChar Tests
// ============================================================

TEST(XMLUtilTest_165, IsNameChar_Letter_165) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST(XMLUtilTest_165, IsNameChar_Digit_165) {
    EXPECT_TRUE(XMLUtil::IsNameChar('5'));
}

TEST(XMLUtilTest_165, IsNameChar_Hyphen_165) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_165, IsNameChar_Dot_165) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_165, IsNameChar_Space_165) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

TEST(XMLUtilTest_165, IsPrefixHex_Valid_165) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilTest_165, IsPrefixHex_Invalid_165) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST(XMLUtilTest_165, IsPrefixHex_JustZero_165) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

TEST(XMLUtilTest_165, IsUTF8Continuation_ContinuationByte_165) {
    // Continuation bytes are 10xxxxxx (0x80 to 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST(XMLUtilTest_165, IsUTF8Continuation_NonContinuationByte_165) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

TEST(XMLUtilTest_165, ConvertUTF32ToUTF8_ASCII_165) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST(XMLUtilTest_165, ConvertUTF32ToUTF8_TwoByte_165) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST(XMLUtilTest_165, ConvertUTF32ToUTF8_ThreeByte_165) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(3, length);
}

TEST(XMLUtilTest_165, ConvertUTF32ToUTF8_FourByte_165) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(4, length);
}

// ============================================================
// GetCharacterRef Tests
// ============================================================

TEST(XMLUtilTest_165, GetCharacterRef_DecimalRef_165) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilTest_165, GetCharacterRef_HexRef_165) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilTest_165, GetCharacterRef_NotARef_165) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

TEST(XMLUtilTest_165, SetBoolSerialization_Custom_165) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_165, SetBoolSerialization_ResetToDefault_165) {
    XMLUtil::SetBoolSerialization("yes", "no");
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

TEST(XMLUtilTest_165, Roundtrip_Int_165) {
    char buffer[64];
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(12345, value);
}

TEST(XMLUtilTest_165, Roundtrip_Double_165) {
    char buffer[64];
    XMLUtil::ToStr(2.718281828459045, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(2.718281828459045, value, 1e-10);
}

TEST(XMLUtilTest_165, Roundtrip_Int64_165) {
    char buffer[64];
    int64_t original = 9223372036854775807LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST(XMLUtilTest_165, Roundtrip_Bool_True_165) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_165, Roundtrip_Bool_False_165) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}
