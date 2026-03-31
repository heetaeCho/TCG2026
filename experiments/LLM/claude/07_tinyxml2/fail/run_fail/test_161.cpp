#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== ToStr Tests ====================

TEST(XMLUtilTest_161, ToStr_Int_Positive_161) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST(XMLUtilTest_161, ToStr_Int_Negative_161) {
    char buffer[64];
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ("-123", buffer);
}

TEST(XMLUtilTest_161, ToStr_Int_Zero_161) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilTest_161, ToStr_Unsigned_161) {
    char buffer[64];
    XMLUtil::ToStr((unsigned int)12345, buffer, sizeof(buffer));
    EXPECT_STREQ("12345", buffer);
}

TEST(XMLUtilTest_161, ToStr_Unsigned_Zero_161) {
    char buffer[64];
    XMLUtil::ToStr((unsigned int)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST(XMLUtilTest_161, ToStr_Bool_True_161) {
    // Reset to default serialization first
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST(XMLUtilTest_161, ToStr_Bool_False_161) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST(XMLUtilTest_161, ToStr_Float_161) {
    char buffer[64];
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Just check it's non-empty and parseable
    float val;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_FLOAT_EQ(1.5f, val);
}

TEST(XMLUtilTest_161, ToStr_Double_161) {
    char buffer[64];
    XMLUtil::ToStr(3.14159, buffer, sizeof(buffer));
    double val;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_DOUBLE_EQ(3.14159, val);
}

TEST(XMLUtilTest_161, ToStr_Int64_Positive_161) {
    char buffer[64];
    int64_t v = 9223372036854775807LL;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    int64_t parsed;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(v, parsed);
}

TEST(XMLUtilTest_161, ToStr_Int64_Negative_161) {
    char buffer[64];
    int64_t v = -9223372036854775807LL;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    int64_t parsed;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(v, parsed);
}

TEST(XMLUtilTest_161, ToStr_Uint64_161) {
    char buffer[64];
    uint64_t v = 18446744073709551615ULL;
    XMLUtil::ToStr(v, buffer, sizeof(buffer));
    uint64_t parsed;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(v, parsed);
}

// ==================== ToInt Tests ====================

TEST(XMLUtilTest_161, ToInt_Valid_161) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST(XMLUtilTest_161, ToInt_Negative_161) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST(XMLUtilTest_161, ToInt_InvalidString_161) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilTest_161, ToInt_NullString_161) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilTest_161, ToInt_EmptyString_161) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ==================== ToUnsigned Tests ====================

TEST(XMLUtilTest_161, ToUnsigned_Valid_161) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("500", &value));
    EXPECT_EQ(500u, value);
}

TEST(XMLUtilTest_161, ToUnsigned_Invalid_161) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST(XMLUtilTest_161, ToUnsigned_Null_161) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ==================== ToBool Tests ====================

TEST(XMLUtilTest_161, ToBool_True_161) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_161, ToBool_False_161) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_161, ToBool_One_161) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_161, ToBool_Zero_161) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_161, ToBool_Invalid_161) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilTest_161, ToBool_Null_161) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ==================== ToFloat Tests ====================

TEST(XMLUtilTest_161, ToFloat_Valid_161) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST(XMLUtilTest_161, ToFloat_Invalid_161) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("notfloat", &value));
}

TEST(XMLUtilTest_161, ToFloat_Null_161) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ==================== ToDouble Tests ====================

TEST(XMLUtilTest_161, ToDouble_Valid_161) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("2.71828", &value));
    EXPECT_NEAR(2.71828, value, 0.00001);
}

TEST(XMLUtilTest_161, ToDouble_Invalid_161) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("notdouble", &value));
}

TEST(XMLUtilTest_161, ToDouble_Null_161) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ==================== ToInt64 Tests ====================

TEST(XMLUtilTest_161, ToInt64_Valid_161) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(1234567890123LL, value);
}

TEST(XMLUtilTest_161, ToInt64_Invalid_161) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST(XMLUtilTest_161, ToInt64_Null_161) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ==================== ToUnsigned64 Tests ====================

TEST(XMLUtilTest_161, ToUnsigned64_Valid_161) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("9876543210", &value));
    EXPECT_EQ(9876543210ULL, value);
}

TEST(XMLUtilTest_161, ToUnsigned64_Invalid_161) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &value));
}

TEST(XMLUtilTest_161, ToUnsigned64_Null_161) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ==================== SetBoolSerialization Tests ====================

TEST(XMLUtilTest_161, SetBoolSerialization_Custom_161) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset back to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_161, SetBoolSerialization_ResetToDefault_161) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST(XMLUtilTest_161, SetBoolSerialization_CustomTrue_DefaultFalse_161) {
    XMLUtil::SetBoolSerialization("YES", nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("YES", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_161, SetBoolSerialization_DefaultTrue_CustomFalse_161) {
    XMLUtil::SetBoolSerialization(nullptr, "NO");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("NO", buffer);
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

// ==================== ReadBOM Tests ====================

TEST(XMLUtilTest_161, ReadBOM_WithBOM_161) {
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    const char bom[] = "\xEF\xBB\xBF<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3);
}

TEST(XMLUtilTest_161, ReadBOM_WithoutBOM_161) {
    const char noBom[] = "<xml>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, noBom);
}

TEST(XMLUtilTest_161, ReadBOM_NullPointer_161) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ==================== IsWhiteSpace Tests ====================

TEST(XMLUtilTest_161, IsWhiteSpace_Space_161) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_161, IsWhiteSpace_Tab_161) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_161, IsWhiteSpace_Newline_161) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_161, IsWhiteSpace_CarriageReturn_161) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_161, IsWhiteSpace_NonWhite_161) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilTest_161, IsWhiteSpace_Digit_161) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

// ==================== SkipWhiteSpace Tests ====================

TEST(XMLUtilTest_161, SkipWhiteSpace_LeadingSpaces_161) {
    const char* text = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(text, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_161, SkipWhiteSpace_NoSpaces_161) {
    const char* text = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(text, &lineNum);
    EXPECT_EQ(result, text);
}

TEST(XMLUtilTest_161, SkipWhiteSpace_WithNewlines_161) {
    const char* text = "\n\n  hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(text, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST(XMLUtilTest_161, SkipWhiteSpace_NullLineNum_161) {
    const char* text = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(text, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_161, SkipWhiteSpace_NullPointer_161) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// ==================== StringEqual Tests ====================

TEST(XMLUtilTest_161, StringEqual_EqualStrings_161) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_161, StringEqual_DifferentStrings_161) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_161, StringEqual_WithNChar_161) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST(XMLUtilTest_161, StringEqual_BothNull_161) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilTest_161, StringEqual_OneNull_161) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilTest_161, StringEqual_EmptyStrings_161) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilTest_161, StringEqual_DifferentLengths_161) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "helloworld"));
}

// ==================== IsNameStartChar Tests ====================

TEST(XMLUtilTest_161, IsNameStartChar_Letter_161) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
}

TEST(XMLUtilTest_161, IsNameStartChar_Underscore_161) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_161, IsNameStartChar_Colon_161) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_161, IsNameStartChar_Digit_161) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST(XMLUtilTest_161, IsNameStartChar_Dash_161) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

// ==================== IsNameChar Tests ====================

TEST(XMLUtilTest_161, IsNameChar_Letter_161) {
    EXPECT_TRUE(XMLUtil::IsNameChar('A'));
}

TEST(XMLUtilTest_161, IsNameChar_Digit_161) {
    EXPECT_TRUE(XMLUtil::IsNameChar('5'));
}

TEST(XMLUtilTest_161, IsNameChar_Dash_161) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_161, IsNameChar_Dot_161) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_161, IsNameChar_Space_161) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ==================== IsPrefixHex Tests ====================

TEST(XMLUtilTest_161, IsPrefixHex_Valid_161) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilTest_161, IsPrefixHex_Invalid_161) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST(XMLUtilTest_161, IsPrefixHex_JustZero_161) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ==================== IsUTF8Continuation Tests ====================

TEST(XMLUtilTest_161, IsUTF8Continuation_ContinuationByte_161) {
    // Continuation bytes are 10xxxxxx (0x80-0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST(XMLUtilTest_161, IsUTF8Continuation_NonContinuation_161) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

TEST(XMLUtilTest_161, ConvertUTF32ToUTF8_ASCII_161) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length);  // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST(XMLUtilTest_161, ConvertUTF32ToUTF8_TwoByte_161) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length);  // É = U+00C9
    EXPECT_EQ(2, length);
}

TEST(XMLUtilTest_161, ConvertUTF32ToUTF8_ThreeByte_161) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length);  // 中 = U+4E2D
    EXPECT_EQ(3, length);
}

TEST(XMLUtilTest_161, ConvertUTF32ToUTF8_FourByte_161) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length);  // 😀 = U+1F600
    EXPECT_EQ(4, length);
}

// ==================== GetCharacterRef Tests ====================

TEST(XMLUtilTest_161, GetCharacterRef_DecimalRef_161) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilTest_161, GetCharacterRef_HexRef_161) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST(XMLUtilTest_161, GetCharacterRef_Null_161) {
    char value[8] = {};
    int length = 0;
    const char* result = XMLUtil::GetCharacterRef(nullptr, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ==================== Roundtrip Tests ====================

TEST(XMLUtilTest_161, Roundtrip_Int_161) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(INT_MAX, value);
}

TEST(XMLUtilTest_161, Roundtrip_Int_Min_161) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(INT_MIN, value);
}

TEST(XMLUtilTest_161, Roundtrip_Bool_True_161) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_161, Roundtrip_Bool_False_161) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}
