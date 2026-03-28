#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// IsNameStartChar tests
// ============================================================

TEST(XMLUtilTest_38, IsNameStartChar_Underscore_38) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST(XMLUtilTest_38, IsNameStartChar_Colon_38) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST(XMLUtilTest_38, IsNameStartChar_LowercaseLetters_38) {
    for (char c = 'a'; c <= 'z'; ++c) {
        EXPECT_TRUE(XMLUtil::IsNameStartChar(static_cast<unsigned char>(c)));
    }
}

TEST(XMLUtilTest_38, IsNameStartChar_UppercaseLetters_38) {
    for (char c = 'A'; c <= 'Z'; ++c) {
        EXPECT_TRUE(XMLUtil::IsNameStartChar(static_cast<unsigned char>(c)));
    }
}

TEST(XMLUtilTest_38, IsNameStartChar_DigitShouldFail_38) {
    for (char c = '0'; c <= '9'; ++c) {
        EXPECT_FALSE(XMLUtil::IsNameStartChar(static_cast<unsigned char>(c)));
    }
}

TEST(XMLUtilTest_38, IsNameStartChar_DotShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

TEST(XMLUtilTest_38, IsNameStartChar_HyphenShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST(XMLUtilTest_38, IsNameStartChar_SpaceShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
}

TEST(XMLUtilTest_38, IsNameStartChar_HighBitSet_38) {
    // Characters with high bit set (>= 0x80) should be valid name start chars (UTF-8 continuation/start bytes)
    EXPECT_TRUE(XMLUtil::IsNameStartChar(0xC0));
    EXPECT_TRUE(XMLUtil::IsNameStartChar(0xFF));
}

// ============================================================
// IsNameChar tests
// ============================================================

TEST(XMLUtilTest_38, IsNameChar_Letters_38) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST(XMLUtilTest_38, IsNameChar_Digits_38) {
    for (char c = '0'; c <= '9'; ++c) {
        EXPECT_TRUE(XMLUtil::IsNameChar(static_cast<unsigned char>(c)));
    }
}

TEST(XMLUtilTest_38, IsNameChar_Dot_38) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST(XMLUtilTest_38, IsNameChar_Hyphen_38) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST(XMLUtilTest_38, IsNameChar_Underscore_38) {
    EXPECT_TRUE(XMLUtil::IsNameChar('_'));
}

TEST(XMLUtilTest_38, IsNameChar_Colon_38) {
    EXPECT_TRUE(XMLUtil::IsNameChar(':'));
}

TEST(XMLUtilTest_38, IsNameChar_SpaceShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

TEST(XMLUtilTest_38, IsNameChar_ExclamationShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameChar('!'));
}

TEST(XMLUtilTest_38, IsNameChar_AtShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameChar('@'));
}

TEST(XMLUtilTest_38, IsNameChar_NullShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsNameChar('\0'));
}

// ============================================================
// IsWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_38, IsWhiteSpace_Space_38) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST(XMLUtilTest_38, IsWhiteSpace_Tab_38) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST(XMLUtilTest_38, IsWhiteSpace_Newline_38) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST(XMLUtilTest_38, IsWhiteSpace_CarriageReturn_38) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST(XMLUtilTest_38, IsWhiteSpace_LetterShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST(XMLUtilTest_38, IsWhiteSpace_NullShouldFail_38) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// StringEqual tests
// ============================================================

TEST(XMLUtilTest_38, StringEqual_SameStrings_38) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST(XMLUtilTest_38, StringEqual_DifferentStrings_38) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST(XMLUtilTest_38, StringEqual_EmptyStrings_38) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST(XMLUtilTest_38, StringEqual_OneEmpty_38) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", ""));
}

TEST(XMLUtilTest_38, StringEqual_NCharLimited_38) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello earth", 5));
}

TEST(XMLUtilTest_38, StringEqual_NCharDifference_38) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hallo", 5));
}

TEST(XMLUtilTest_38, StringEqual_BothNull_38) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST(XMLUtilTest_38, StringEqual_OneNull_38) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

// ============================================================
// IsPrefixHex tests
// ============================================================

TEST(XMLUtilTest_38, IsPrefixHex_ValidHexPrefix_38) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST(XMLUtilTest_38, IsPrefixHex_NoPrefix_38) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST(XMLUtilTest_38, IsPrefixHex_JustZero_38) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST(XMLUtilTest_38, IsPrefixHex_EmptyString_38) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

// ============================================================
// IsUTF8Continuation tests
// ============================================================

TEST(XMLUtilTest_38, IsUTF8Continuation_ContinuationByte_38) {
    // UTF-8 continuation bytes are 10xxxxxx (0x80-0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST(XMLUtilTest_38, IsUTF8Continuation_NonContinuationByte_38) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('a'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('\0'));
}

// ============================================================
// SkipWhiteSpace tests
// ============================================================

TEST(XMLUtilTest_38, SkipWhiteSpace_LeadingSpaces_38) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST(XMLUtilTest_38, SkipWhiteSpace_NoWhiteSpace_38) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_38, SkipWhiteSpace_AllWhiteSpace_38) {
    const char* input = "   \t\n";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, '\0');
}

TEST(XMLUtilTest_38, SkipWhiteSpace_NullInput_38) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST(XMLUtilTest_38, SkipWhiteSpace_CountsNewlines_38) {
    int lineNum = 1;
    const char* input = "\n\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 4);
}

TEST(XMLUtilTest_38, SkipWhiteSpace_MutableVersion_38) {
    char input[] = "   hello";
    char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

// ============================================================
// ReadBOM tests
// ============================================================

TEST(XMLUtilTest_38, ReadBOM_WithBOM_38) {
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    const char input[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(*result, '<');
}

TEST(XMLUtilTest_38, ReadBOM_WithoutBOM_38) {
    const char* input = "<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST(XMLUtilTest_38, ReadBOM_NullInput_38) {
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// ToStr / ToInt tests
// ============================================================

TEST(XMLUtilTest_38, ToStr_Int_38) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST(XMLUtilTest_38, ToStr_NegativeInt_38) {
    char buffer[64];
    XMLUtil::ToStr(-7, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-7");
}

TEST(XMLUtilTest_38, ToStr_Zero_38) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST(XMLUtilTest_38, ToStr_Unsigned_38) {
    char buffer[64];
    XMLUtil::ToStr(123u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "123");
}

TEST(XMLUtilTest_38, ToStr_BoolTrue_38) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST(XMLUtilTest_38, ToStr_BoolFalse_38) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST(XMLUtilTest_38, ToStr_Float_38) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    // Just check it starts with "3.14"
    EXPECT_TRUE(strstr(buffer, "3.14") != nullptr);
}

TEST(XMLUtilTest_38, ToStr_Double_38) {
    char buffer[64];
    XMLUtil::ToStr(3.14159, buffer, sizeof(buffer));
    EXPECT_TRUE(strstr(buffer, "3.14") != nullptr);
}

TEST(XMLUtilTest_38, ToStr_Int64_38) {
    char buffer[64];
    int64_t val = 9223372036854775807LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "9223372036854775807");
}

TEST(XMLUtilTest_38, ToStr_UInt64_38) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "18446744073709551615");
}

// ============================================================
// ToInt tests
// ============================================================

TEST(XMLUtilTest_38, ToInt_ValidString_38) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(value, 42);
}

TEST(XMLUtilTest_38, ToInt_NegativeValue_38) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-10", &value));
    EXPECT_EQ(value, -10);
}

TEST(XMLUtilTest_38, ToInt_InvalidString_38) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST(XMLUtilTest_38, ToInt_NullString_38) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST(XMLUtilTest_38, ToInt_EmptyString_38) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ============================================================
// ToUnsigned tests
// ============================================================

TEST(XMLUtilTest_38, ToUnsigned_ValidString_38) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &value));
    EXPECT_EQ(value, 42u);
}

TEST(XMLUtilTest_38, ToUnsigned_InvalidString_38) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST(XMLUtilTest_38, ToUnsigned_NullString_38) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ============================================================
// ToBool tests
// ============================================================

TEST(XMLUtilTest_38, ToBool_TrueString_38) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_38, ToBool_FalseString_38) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_38, ToBool_One_38) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST(XMLUtilTest_38, ToBool_Zero_38) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST(XMLUtilTest_38, ToBool_InvalidString_38) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST(XMLUtilTest_38, ToBool_NullString_38) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ============================================================
// ToFloat tests
// ============================================================

TEST(XMLUtilTest_38, ToFloat_ValidString_38) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST(XMLUtilTest_38, ToFloat_InvalidString_38) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST(XMLUtilTest_38, ToFloat_NullString_38) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ============================================================
// ToDouble tests
// ============================================================

TEST(XMLUtilTest_38, ToDouble_ValidString_38) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159", &value));
    EXPECT_NEAR(value, 3.14159, 0.00001);
}

TEST(XMLUtilTest_38, ToDouble_InvalidString_38) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST(XMLUtilTest_38, ToDouble_NullString_38) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ============================================================
// ToInt64 tests
// ============================================================

TEST(XMLUtilTest_38, ToInt64_ValidString_38) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST(XMLUtilTest_38, ToInt64_NegativeValue_38) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(value, -100LL);
}

TEST(XMLUtilTest_38, ToInt64_InvalidString_38) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST(XMLUtilTest_38, ToInt64_NullString_38) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ============================================================
// ToUnsigned64 tests
// ============================================================

TEST(XMLUtilTest_38, ToUnsigned64_ValidString_38) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST(XMLUtilTest_38, ToUnsigned64_InvalidString_38) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST(XMLUtilTest_38, ToUnsigned64_NullString_38) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// ConvertUTF32ToUTF8 tests
// ============================================================

TEST(XMLUtilTest_38, ConvertUTF32ToUTF8_ASCIIChar_38) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST(XMLUtilTest_38, ConvertUTF32ToUTF8_TwoByteChar_38) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xA9, output, &length); // copyright symbol
    EXPECT_EQ(length, 2);
}

TEST(XMLUtilTest_38, ConvertUTF32ToUTF8_ThreeByteChar_38) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // Euro sign
    EXPECT_EQ(length, 3);
}

TEST(XMLUtilTest_38, ConvertUTF32ToUTF8_FourByteChar_38) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(length, 4);
}

// ============================================================
// GetCharacterRef tests
// ============================================================

TEST(XMLUtilTest_38, GetCharacterRef_DecimalRef_38) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_38, GetCharacterRef_HexRef_38) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST(XMLUtilTest_38, GetCharacterRef_InvalidRef_38) {
    char value[8] = {};
    int length = 0;
    const char* input = "not a ref";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// SetBoolSerialization tests
// ============================================================

TEST(XMLUtilTest_38, SetBoolSerialization_Custom_38) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST(XMLUtilTest_38, SetBoolSerialization_ResetToDefault_38) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}
