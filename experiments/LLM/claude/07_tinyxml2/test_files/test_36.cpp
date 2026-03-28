#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <cstring>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== IsWhiteSpace Tests ====================

TEST(XMLUtilTest_36, IsWhiteSpace_Space_36) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_36, IsWhiteSpace_Tab_36) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_Newline_36) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_CarriageReturn_36) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_RegularChar_36) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_NullChar_36) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_Digit_36) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST(XMLUtilTest_36, IsWhiteSpace_UTF8Continuation_36) {
    // UTF-8 continuation bytes have the pattern 10xxxxxx (0x80–0xBF)
    EXPECT_FALSE(XMLUtil::IsWhiteSpace(static_cast<char>(0x80)));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace(static_cast<char>(0xBF)));
}

// ==================== IsUTF8Continuation Tests ====================

TEST(XMLUtilTest_36, IsUTF8Continuation_ContinuationByte_36) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST(XMLUtilTest_36, IsUTF8Continuation_NonContinuationByte_36) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('\0'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
}

// ==================== IsNameStartChar Tests ====================

TEST(XMLUtilTest_36, IsNameStartChar_Letter_36) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST(XMLUtilTest_36, IsNameStartChar_Underscore_36) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_36, IsNameStartChar_Colon_36) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_36, IsNameStartChar_Digit_36) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST(XMLUtilTest_36, IsNameStartChar_Hyphen_36) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST(XMLUtilTest_36, IsNameStartChar_Dot_36) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

// ==================== IsNameChar Tests ====================

TEST(XMLUtilTest_36, IsNameChar_Letter_36) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST(XMLUtilTest_36, IsNameChar_Digit_36) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST(XMLUtilTest_36, IsNameChar_Hyphen_36) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_36, IsNameChar_Dot_36) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_36, IsNameChar_Space_36) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

TEST(XMLUtilTest_36, IsNameChar_Exclamation_36) {
    EXPECT_FALSE(XMLUtil::IsNameChar('!'));
}

// ==================== IsPrefixHex Tests ====================

TEST(XMLUtilTest_36, IsPrefixHex_Valid_36) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilTest_36, IsPrefixHex_Invalid_36) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("x01"));
}

TEST(XMLUtilTest_36, IsPrefixHex_TooShort_36) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

// ==================== StringEqual Tests ====================

TEST(XMLUtilTest_36, StringEqual_EqualStrings_36) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_36, StringEqual_DifferentStrings_36) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_36, StringEqual_PartialMatch_36) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello", 5));
}

TEST(XMLUtilTest_36, StringEqual_BothNull_36) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilTest_36, StringEqual_OneNull_36) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilTest_36, StringEqual_EmptyStrings_36) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilTest_36, StringEqual_NCharZero_36) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

// ==================== SkipWhiteSpace Tests ====================

TEST(XMLUtilTest_36, SkipWhiteSpace_LeadingSpaces_36) {
    const char* input = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_36, SkipWhiteSpace_NoWhiteSpace_36) {
    const char* input = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_36, SkipWhiteSpace_AllWhiteSpace_36) {
    const char* input = "   ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST(XMLUtilTest_36, SkipWhiteSpace_NewlineIncrementsLineNum_36) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST(XMLUtilTest_36, SkipWhiteSpace_NullLineNum_36) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_36, SkipWhiteSpace_NullInput_36) {
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST(XMLUtilTest_36, SkipWhiteSpace_MutableVersion_36) {
    char input[] = "  hello";
    int lineNum = 1;
    char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

// ==================== ReadBOM Tests ====================

TEST(XMLUtilTest_36, ReadBOM_WithBOM_36) {
    const char bom[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(*result, '<');
}

TEST(XMLUtilTest_36, ReadBOM_WithoutBOM_36) {
    const char* input = "<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_36, ReadBOM_NullInput_36) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

TEST(XMLUtilTest_36, ConvertUTF32ToUTF8_ASCII_36) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST(XMLUtilTest_36, ConvertUTF32ToUTF8_TwoByteChar_36) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(length, 2);
}

TEST(XMLUtilTest_36, ConvertUTF32ToUTF8_ThreeByteChar_36) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // €
    EXPECT_EQ(length, 3);
}

TEST(XMLUtilTest_36, ConvertUTF32ToUTF8_FourByteChar_36) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀
    EXPECT_EQ(length, 4);
}

// ==================== ToStr Tests ====================

TEST(XMLUtilTest_36, ToStr_Int_36) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_36, ToStr_IntNegative_36) {
    char buffer[64];
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-123");
}

TEST(XMLUtilTest_36, ToStr_IntZero_36) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST(XMLUtilTest_36, ToStr_Unsigned_36) {
    char buffer[64];
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_36, ToStr_BoolTrue_36) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST(XMLUtilTest_36, ToStr_BoolFalse_36) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST(XMLUtilTest_36, ToStr_Float_36) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    // Just verify it produces something parseable
    float val;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_NEAR(val, 3.14f, 0.01f);
}

TEST(XMLUtilTest_36, ToStr_Double_36) {
    char buffer[64];
    XMLUtil::ToStr(3.14159265358979, buffer, sizeof(buffer));
    double val;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_NEAR(val, 3.14159265358979, 1e-10);
}

TEST(XMLUtilTest_36, ToStr_Int64_36) {
    char buffer[64];
    int64_t v = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    int64_t parsed;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(parsed, v);
}

TEST(XMLUtilTest_36, ToStr_UInt64_36) {
    char buffer[64];
    uint64_t v = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    uint64_t parsed;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(parsed, v);
}

// ==================== ToInt Tests ====================

TEST(XMLUtilTest_36, ToInt_Valid_36) {
    int value;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(value, 123);
}

TEST(XMLUtilTest_36, ToInt_Negative_36) {
    int value;
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(value, -456);
}

TEST(XMLUtilTest_36, ToInt_Invalid_36) {
    int value;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilTest_36, ToInt_Null_36) {
    int value;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilTest_36, ToInt_EmptyString_36) {
    int value;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ==================== ToUnsigned Tests ====================

TEST(XMLUtilTest_36, ToUnsigned_Valid_36) {
    unsigned int value;
    EXPECT_TRUE(XMLUtil::ToUnsigned("789", &value));
    EXPECT_EQ(value, 789u);
}

TEST(XMLUtilTest_36, ToUnsigned_Invalid_36) {
    unsigned int value;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST(XMLUtilTest_36, ToUnsigned_Null_36) {
    unsigned int value;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ==================== ToBool Tests ====================

TEST(XMLUtilTest_36, ToBool_True_36) {
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_36, ToBool_False_36) {
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_36, ToBool_One_36) {
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_36, ToBool_Zero_36) {
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_36, ToBool_Invalid_36) {
    bool value;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilTest_36, ToBool_Null_36) {
    bool value;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ==================== ToFloat Tests ====================

TEST(XMLUtilTest_36, ToFloat_Valid_36) {
    float value;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST(XMLUtilTest_36, ToFloat_Invalid_36) {
    float value;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST(XMLUtilTest_36, ToFloat_Null_36) {
    float value;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ==================== ToDouble Tests ====================

TEST(XMLUtilTest_36, ToDouble_Valid_36) {
    double value;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159", &value));
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

TEST(XMLUtilTest_36, ToDouble_Invalid_36) {
    double value;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST(XMLUtilTest_36, ToDouble_Null_36) {
    double value;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ==================== ToInt64 Tests ====================

TEST(XMLUtilTest_36, ToInt64_Valid_36) {
    int64_t value;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, INT64_MAX);
}

TEST(XMLUtilTest_36, ToInt64_Negative_36) {
    int64_t value;
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(value, -100);
}

TEST(XMLUtilTest_36, ToInt64_Invalid_36) {
    int64_t value;
    EXPECT_FALSE(XMLUtil::ToInt64("notanumber", &value));
}

TEST(XMLUtilTest_36, ToInt64_Null_36) {
    int64_t value;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ==================== ToUnsigned64 Tests ====================

TEST(XMLUtilTest_36, ToUnsigned64_Valid_36) {
    uint64_t value;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, UINT64_MAX);
}

TEST(XMLUtilTest_36, ToUnsigned64_Invalid_36) {
    uint64_t value;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("notanumber", &value));
}

TEST(XMLUtilTest_36, ToUnsigned64_Null_36) {
    uint64_t value;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ==================== SetBoolSerialization Tests ====================

TEST(XMLUtilTest_36, SetBoolSerialization_Custom_36) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_36, SetBoolSerialization_ResetToDefault_36) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ==================== GetCharacterRef Tests ====================

TEST(XMLUtilTest_36, GetCharacterRef_DecimalRef_36) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_36, GetCharacterRef_HexRef_36) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_36, GetCharacterRef_NotARef_36) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ==================== Roundtrip Tests ====================

TEST(XMLUtilTest_36, Roundtrip_Int_36) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    int value;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MAX);
}

TEST(XMLUtilTest_36, Roundtrip_Int_Min_36) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    int value;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MIN);
}

TEST(XMLUtilTest_36, Roundtrip_Bool_36) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}
