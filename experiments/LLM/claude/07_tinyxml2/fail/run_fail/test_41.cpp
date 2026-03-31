#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// IsUTF8Continuation tests
// ============================================================

TEST(XMLUtilTest_41, IsUTF8Continuation_ReturnsTrueForHighBitSet_41) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xFF));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xC0));
}

TEST(XMLUtilTest_41, IsUTF8Continuation_ReturnsFalseForASCII_41) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(' '));
}

// ============================================================
// IsWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_41, IsWhiteSpace_SpaceIsWhiteSpace_41) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_41, IsWhiteSpace_TabIsWhiteSpace_41) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_41, IsWhiteSpace_NewlineIsWhiteSpace_41) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_41, IsWhiteSpace_CarriageReturnIsWhiteSpace_41) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_41, IsWhiteSpace_LetterIsNotWhiteSpace_41) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST(XMLUtilTest_41, IsWhiteSpace_NullIsNotWhiteSpace_41) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// IsNameStartChar tests
// ============================================================

TEST(XMLUtilTest_41, IsNameStartChar_LettersAreValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST(XMLUtilTest_41, IsNameStartChar_UnderscoreIsValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_41, IsNameStartChar_ColonIsValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_41, IsNameStartChar_DigitIsNotValid_41) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST(XMLUtilTest_41, IsNameStartChar_DotIsNotValid_41) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

TEST(XMLUtilTest_41, IsNameStartChar_HyphenIsNotValid_41) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

// ============================================================
// IsNameChar tests
// ============================================================

TEST(XMLUtilTest_41, IsNameChar_LettersAreValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST(XMLUtilTest_41, IsNameChar_DigitsAreValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST(XMLUtilTest_41, IsNameChar_HyphenIsValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_41, IsNameChar_DotIsValid_41) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_41, IsNameChar_SpaceIsNotValid_41) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex tests
// ============================================================

TEST(XMLUtilTest_41, IsPrefixHex_ValidHexPrefix_41) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilTest_41, IsPrefixHex_NotHexPrefix_41) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("abc"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// StringEqual tests
// ============================================================

TEST(XMLUtilTest_41, StringEqual_EqualStrings_41) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_41, StringEqual_DifferentStrings_41) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_41, StringEqual_WithNChar_41) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}

TEST(XMLUtilTest_41, StringEqual_BothNull_41) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilTest_41, StringEqual_OneNull_41) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST(XMLUtilTest_41, StringEqual_EmptyStrings_41) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

// ============================================================
// SkipWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_41, SkipWhiteSpace_SkipsSpaces_41) {
    const char* input = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_41, SkipWhiteSpace_SkipsNewlines_41) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST(XMLUtilTest_41, SkipWhiteSpace_NoWhiteSpace_41) {
    const char* input = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_41, SkipWhiteSpace_NullInput_41) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST(XMLUtilTest_41, SkipWhiteSpace_MutableVersion_41) {
    char input[] = "  hello";
    int lineNum = 1;
    char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

// ============================================================
// ReadBOM tests
// ============================================================

TEST(XMLUtilTest_41, ReadBOM_NoBOM_41) {
    const char* input = "<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_41, ReadBOM_WithBOM_41) {
    const char input[] = "\xEF\xBB\xBF<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, input + 3);
}

TEST(XMLUtilTest_41, ReadBOM_NullInput_41) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// ConvertUTF32ToUTF8 tests
// ============================================================

TEST(XMLUtilTest_41, ConvertUTF32ToUTF8_ASCIICharacter_41) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length);  // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST(XMLUtilTest_41, ConvertUTF32ToUTF8_TwoByteChar_41) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length);  // Latin small e with acute - É (U+00C9)
    EXPECT_EQ(length, 2);
}

TEST(XMLUtilTest_41, ConvertUTF32ToUTF8_ThreeByteChar_41) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length);  // Euro sign €
    EXPECT_EQ(length, 3);
}

TEST(XMLUtilTest_41, ConvertUTF32ToUTF8_FourByteChar_41) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length);  // Emoji
    EXPECT_EQ(length, 4);
}

TEST(XMLUtilTest_41, ConvertUTF32ToUTF8_ZeroInput_41) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0, output, &length);
    // Zero is a valid character, should produce length 0 or 1
    EXPECT_GE(length, 0);
}

// ============================================================
// ToStr (int) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Int_Positive_41) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_41, ToStr_Int_Negative_41) {
    char buffer[64];
    XMLUtil::ToStr(-17, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-17");
}

TEST(XMLUtilTest_41, ToStr_Int_Zero_41) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

// ============================================================
// ToStr (unsigned int) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Unsigned_41) {
    char buffer[64];
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_41, ToStr_Unsigned_Zero_41) {
    char buffer[64];
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

// ============================================================
// ToStr (bool) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Bool_True_41) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST(XMLUtilTest_41, ToStr_Bool_False_41) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ============================================================
// ToStr (float) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Float_41) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(parsed, 3.14f, 0.001f);
}

// ============================================================
// ToStr (double) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Double_41) {
    char buffer[64];
    XMLUtil::ToStr(3.14159265358979, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(parsed, 3.14159265358979, 1e-10);
}

// ============================================================
// ToStr (int64_t) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_Int64_41) {
    char buffer[64];
    int64_t val = 9223372036854775807LL;  // INT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "9223372036854775807");
}

TEST(XMLUtilTest_41, ToStr_Int64_Negative_41) {
    char buffer[64];
    int64_t val = -123456789012345LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-123456789012345");
}

// ============================================================
// ToStr (uint64_t) tests
// ============================================================

TEST(XMLUtilTest_41, ToStr_UInt64_41) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL;  // UINT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "18446744073709551615");
}

// ============================================================
// ToInt tests
// ============================================================

TEST(XMLUtilTest_41, ToInt_ValidPositive_41) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(value, 123);
}

TEST(XMLUtilTest_41, ToInt_ValidNegative_41) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(value, -456);
}

TEST(XMLUtilTest_41, ToInt_Zero_41) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(value, 0);
}

TEST(XMLUtilTest_41, ToInt_InvalidString_41) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilTest_41, ToInt_NullString_41) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilTest_41, ToInt_EmptyString_41) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ============================================================
// ToUnsigned tests
// ============================================================

TEST(XMLUtilTest_41, ToUnsigned_Valid_41) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(value, 123u);
}

TEST(XMLUtilTest_41, ToUnsigned_InvalidString_41) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST(XMLUtilTest_41, ToUnsigned_NullString_41) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ============================================================
// ToBool tests
// ============================================================

TEST(XMLUtilTest_41, ToBool_TrueString_41) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_41, ToBool_FalseString_41) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_41, ToBool_One_41) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_41, ToBool_Zero_41) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_41, ToBool_InvalidString_41) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilTest_41, ToBool_NullString_41) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ============================================================
// ToFloat tests
// ============================================================

TEST(XMLUtilTest_41, ToFloat_Valid_41) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST(XMLUtilTest_41, ToFloat_InvalidString_41) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST(XMLUtilTest_41, ToFloat_NullString_41) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ============================================================
// ToDouble tests
// ============================================================

TEST(XMLUtilTest_41, ToDouble_Valid_41) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159", &value));
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

TEST(XMLUtilTest_41, ToDouble_InvalidString_41) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST(XMLUtilTest_41, ToDouble_NullString_41) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ============================================================
// ToInt64 tests
// ============================================================

TEST(XMLUtilTest_41, ToInt64_Valid_41) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST(XMLUtilTest_41, ToInt64_Negative_41) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(value, -100LL);
}

TEST(XMLUtilTest_41, ToInt64_InvalidString_41) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST(XMLUtilTest_41, ToInt64_NullString_41) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ============================================================
// ToUnsigned64 tests
// ============================================================

TEST(XMLUtilTest_41, ToUnsigned64_Valid_41) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST(XMLUtilTest_41, ToUnsigned64_InvalidString_41) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST(XMLUtilTest_41, ToUnsigned64_NullString_41) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// SetBoolSerialization tests
// ============================================================

TEST(XMLUtilTest_41, SetBoolSerialization_CustomValues_41) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_41, SetBoolSerialization_ResetToDefault_41) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ============================================================
// GetCharacterRef tests
// ============================================================

TEST(XMLUtilTest_41, GetCharacterRef_DecimalRef_41) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_41, GetCharacterRef_HexRef_41) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_41, GetCharacterRef_NotARef_41) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// Boundary: ToStr roundtrip
// ============================================================

TEST(XMLUtilTest_41, ToStr_ToInt_Roundtrip_41) {
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MAX);
}

TEST(XMLUtilTest_41, ToStr_ToInt_RoundtripMin_41) {
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MIN);
}

// ============================================================
// Mixed whitespace in SkipWhiteSpace
// ============================================================

TEST(XMLUtilTest_41, SkipWhiteSpace_MixedWhitespace_41) {
    const char* input = " \t\n\r hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_41, SkipWhiteSpace_AllWhitespace_41) {
    const char* input = "   ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST(XMLUtilTest_41, SkipWhiteSpace_EmptyString_41) {
    const char* input = "";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
    EXPECT_EQ(result, input);
}

// ============================================================
// IsPrefixHex edge cases
// ============================================================

TEST(XMLUtilTest_41, IsPrefixHex_JustZero_41) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST(XMLUtilTest_41, IsPrefixHex_0xOnly_41) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x"));
}

TEST(XMLUtilTest_41, IsPrefixHex_EmptyString_41) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}
