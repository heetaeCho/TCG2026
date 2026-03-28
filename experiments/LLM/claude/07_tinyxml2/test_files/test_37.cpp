#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// IsNameStartChar tests
// ============================================================

TEST(XMLUtilTest_37, IsNameStartChar_AlphaLowercase_37) {
    for (unsigned char ch = 'a'; ch <= 'z'; ++ch) {
        EXPECT_TRUE(XMLUtil::IsNameStartChar(ch)) << "Failed for char: " << ch;
    }
}

TEST(XMLUtilTest_37, IsNameStartChar_AlphaUppercase_37) {
    for (unsigned char ch = 'A'; ch <= 'Z'; ++ch) {
        EXPECT_TRUE(XMLUtil::IsNameStartChar(ch)) << "Failed for char: " << ch;
    }
}

TEST(XMLUtilTest_37, IsNameStartChar_Colon_37) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_37, IsNameStartChar_Underscore_37) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_37, IsNameStartChar_HighByte_37) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(128));
    EXPECT_TRUE(XMLUtil::IsNameStartChar(200));
    EXPECT_TRUE(XMLUtil::IsNameStartChar(255));
}

TEST(XMLUtilTest_37, IsNameStartChar_Digit_37) {
    for (unsigned char ch = '0'; ch <= '9'; ++ch) {
        EXPECT_FALSE(XMLUtil::IsNameStartChar(ch)) << "Failed for digit: " << ch;
    }
}

TEST(XMLUtilTest_37, IsNameStartChar_SpecialChars_37) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('\t'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('\n'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('/'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('<'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('>'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('!'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('@'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('#'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar(0));
}

// ============================================================
// IsNameChar tests
// ============================================================

TEST(XMLUtilTest_37, IsNameChar_AlphaAndSpecial_37) {
    // Everything that is a name start char should also be a name char
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
    EXPECT_TRUE(XMLUtil::IsNameChar(':'));
    EXPECT_TRUE(XMLUtil::IsNameChar('_'));
    EXPECT_TRUE(XMLUtil::IsNameChar(200));
}

TEST(XMLUtilTest_37, IsNameChar_Digits_37) {
    for (unsigned char ch = '0'; ch <= '9'; ++ch) {
        EXPECT_TRUE(XMLUtil::IsNameChar(ch)) << "Failed for digit: " << ch;
    }
}

TEST(XMLUtilTest_37, IsNameChar_Hyphen_37) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_37, IsNameChar_Dot_37) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_37, IsNameChar_InvalidChars_37) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
    EXPECT_FALSE(XMLUtil::IsNameChar('\t'));
    EXPECT_FALSE(XMLUtil::IsNameChar('<'));
    EXPECT_FALSE(XMLUtil::IsNameChar('>'));
    EXPECT_FALSE(XMLUtil::IsNameChar('!'));
    EXPECT_FALSE(XMLUtil::IsNameChar('@'));
}

// ============================================================
// IsWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_37, IsWhiteSpace_Space_37) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_37, IsWhiteSpace_Tab_37) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_37, IsWhiteSpace_Newline_37) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_37, IsWhiteSpace_CarriageReturn_37) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_37, IsWhiteSpace_NonWhitespace_37) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('<'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// IsUTF8Continuation tests
// ============================================================

TEST(XMLUtilTest_37, IsUTF8Continuation_ContinuationByte_37) {
    // UTF-8 continuation bytes are 0x80-0xBF (bit pattern 10xxxxxx)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xA0));
}

TEST(XMLUtilTest_37, IsUTF8Continuation_NonContinuationByte_37) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('a'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('\0'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0xC0));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0xFF));
}

// ============================================================
// IsPrefixHex tests
// ============================================================

TEST(XMLUtilTest_37, IsPrefixHex_Valid_37) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x0"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0xFF"));
}

TEST(XMLUtilTest_37, IsPrefixHex_Invalid_37) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1234"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("x12"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0a"));
}

// ============================================================
// StringEqual tests
// ============================================================

TEST(XMLUtilTest_37, StringEqual_EqualStrings_37) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_37, StringEqual_DifferentStrings_37) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_37, StringEqual_EmptyStrings_37) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilTest_37, StringEqual_WithNChar_37) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
    EXPECT_FALSE(XMLUtil::StringEqual("hello world", "hello there", 6));
}

TEST(XMLUtilTest_37, StringEqual_NullPointers_37) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilTest_37, StringEqual_ZeroNChar_37) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

// ============================================================
// SkipWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_37, SkipWhiteSpace_LeadingSpaces_37) {
    const char* str = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_37, SkipWhiteSpace_NoWhitespace_37) {
    const char* str = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(result, str);
}

TEST(XMLUtilTest_37, SkipWhiteSpace_AllWhitespace_37) {
    const char* str = "   \t\n\r";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, '\0');
}

TEST(XMLUtilTest_37, SkipWhiteSpace_NullPtr_37) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST(XMLUtilTest_37, SkipWhiteSpace_TracksLineNumber_37) {
    const char* str = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST(XMLUtilTest_37, SkipWhiteSpace_MutableVersion_37) {
    char str[] = "  hello";
    char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, 'h');
}

// ============================================================
// ReadBOM tests
// ============================================================

TEST(XMLUtilTest_37, ReadBOM_WithBOM_37) {
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char bom[] = { (char)0xEF, (char)0xBB, (char)0xBF, '<', 'a', '>', '\0' };
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(*result, '<');
}

TEST(XMLUtilTest_37, ReadBOM_WithoutBOM_37) {
    const char* str = "<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(str, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, str);
}

TEST(XMLUtilTest_37, ReadBOM_NullPtr_37) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// ToStr / ToInt / ToUnsigned / ToBool / ToFloat / ToDouble tests
// ============================================================

TEST(XMLUtilTest_37, ToStr_Int_37) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, 64);
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_37, ToStr_IntNegative_37) {
    char buffer[64];
    XMLUtil::ToStr(-100, buffer, 64);
    EXPECT_STREQ(buffer, "-100");
}

TEST(XMLUtilTest_37, ToStr_IntZero_37) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, 64);
    EXPECT_STREQ(buffer, "0");
}

TEST(XMLUtilTest_37, ToStr_Unsigned_37) {
    char buffer[64];
    XMLUtil::ToStr((unsigned)123456, buffer, 64);
    EXPECT_STREQ(buffer, "123456");
}

TEST(XMLUtilTest_37, ToStr_BoolTrue_37) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, 64);
    EXPECT_STREQ(buffer, "true");
}

TEST(XMLUtilTest_37, ToStr_BoolFalse_37) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, 64);
    EXPECT_STREQ(buffer, "false");
}

TEST(XMLUtilTest_37, ToStr_Float_37) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, 64);
    float parsed = std::stof(buffer);
    EXPECT_NEAR(parsed, 3.14f, 0.001f);
}

TEST(XMLUtilTest_37, ToStr_Double_37) {
    char buffer[64];
    XMLUtil::ToStr(3.14159265358979, buffer, 64);
    double parsed = std::stod(buffer);
    EXPECT_NEAR(parsed, 3.14159265358979, 1e-10);
}

TEST(XMLUtilTest_37, ToStr_Int64_37) {
    char buffer[64];
    int64_t val = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(val, buffer, 64);
    EXPECT_STREQ(buffer, "9223372036854775807");
}

TEST(XMLUtilTest_37, ToStr_Uint64_37) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(val, buffer, 64);
    EXPECT_STREQ(buffer, "18446744073709551615");
}

TEST(XMLUtilTest_37, ToInt_Valid_37) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(value, 123);
}

TEST(XMLUtilTest_37, ToInt_Negative_37) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(value, -456);
}

TEST(XMLUtilTest_37, ToInt_Invalid_37) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilTest_37, ToInt_NullStr_37) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilTest_37, ToInt_Empty_37) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST(XMLUtilTest_37, ToUnsigned_Valid_37) {
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("789", &value));
    EXPECT_EQ(value, 789u);
}

TEST(XMLUtilTest_37, ToUnsigned_Invalid_37) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST(XMLUtilTest_37, ToUnsigned_NullStr_37) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST(XMLUtilTest_37, ToBool_True_37) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_37, ToBool_False_37) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_37, ToBool_One_37) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_37, ToBool_Zero_37) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_37, ToBool_Invalid_37) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilTest_37, ToBool_NullStr_37) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST(XMLUtilTest_37, ToFloat_Valid_37) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST(XMLUtilTest_37, ToFloat_Invalid_37) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST(XMLUtilTest_37, ToFloat_NullStr_37) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST(XMLUtilTest_37, ToDouble_Valid_37) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("2.718281828", &value));
    EXPECT_NEAR(value, 2.718281828, 1e-8);
}

TEST(XMLUtilTest_37, ToDouble_Invalid_37) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST(XMLUtilTest_37, ToDouble_NullStr_37) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST(XMLUtilTest_37, ToInt64_Valid_37) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, INT64_MAX);
}

TEST(XMLUtilTest_37, ToInt64_Negative_37) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-1000000000000", &value));
    EXPECT_EQ(value, -1000000000000LL);
}

TEST(XMLUtilTest_37, ToInt64_Invalid_37) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST(XMLUtilTest_37, ToInt64_NullStr_37) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST(XMLUtilTest_37, ToUnsigned64_Valid_37) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, UINT64_MAX);
}

TEST(XMLUtilTest_37, ToUnsigned64_Invalid_37) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST(XMLUtilTest_37, ToUnsigned64_NullStr_37) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// ConvertUTF32ToUTF8 tests
// ============================================================

TEST(XMLUtilTest_37, ConvertUTF32ToUTF8_ASCII_37) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST(XMLUtilTest_37, ConvertUTF32ToUTF8_TwoByte_37) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(length, 2);
}

TEST(XMLUtilTest_37, ConvertUTF32ToUTF8_ThreeByte_37) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(length, 3);
}

TEST(XMLUtilTest_37, ConvertUTF32ToUTF8_FourByte_37) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(length, 4);
}

TEST(XMLUtilTest_37, ConvertUTF32ToUTF8_Zero_37) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0, output, &length);
    // Zero should produce zero length or a null character
    EXPECT_GE(length, 0);
}

// ============================================================
// GetCharacterRef tests
// ============================================================

TEST(XMLUtilTest_37, GetCharacterRef_DecimalRef_37) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_37, GetCharacterRef_HexRef_37) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_37, GetCharacterRef_NotARef_37) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// SetBoolSerialization tests
// ============================================================

TEST(XMLUtilTest_37, SetBoolSerialization_Custom_37) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, 64);
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, 64);
    EXPECT_STREQ(buffer, "no");
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_37, SetBoolSerialization_ResetToDefault_37) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, 64);
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, 64);
    EXPECT_STREQ(buffer, "false");
}
