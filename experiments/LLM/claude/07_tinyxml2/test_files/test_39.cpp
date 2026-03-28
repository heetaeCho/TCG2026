#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== IsPrefixHex Tests ====================

class XMLUtilIsPrefixHexTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsTrueForLowercase0x_39) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsTrueForUppercase0X_39) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsFalseForDecimalNumber_39) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsFalseForEmptyString_39) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsFalseForNullPointer_39) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(nullptr));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsTrueWithLeadingWhitespace_39) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("  0x1F"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsTrueWithLeadingTab_39) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("\t0xFF"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsFalseForJustZero_39) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsFalseFor0FollowedByNonX_39) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0a"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ReturnsTrueFor0xOnly_39) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x"));
}

// ==================== IsWhiteSpace Tests ====================

class XMLUtilIsWhiteSpaceTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_39, SpaceIsWhiteSpace_39) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, TabIsWhiteSpace_39) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, NewlineIsWhiteSpace_39) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, CarriageReturnIsWhiteSpace_39) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, LetterIsNotWhiteSpace_39) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, DigitIsNotWhiteSpace_39) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_39, NullCharIsNotWhiteSpace_39) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ==================== SkipWhiteSpace Tests ====================

class XMLUtilSkipWhiteSpaceTest_39 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_39, SkipsLeadingSpaces_39) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_39, SkipsMixedWhitespace_39) {
    const char* input = " \t\n\rhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_39, NoWhitespaceToSkip_39) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_39, AllWhitespace_39) {
    const char* input = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_39, NullInput_39) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_39, TracksLineNumbers_39) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

// ==================== StringEqual Tests ====================

class XMLUtilStringEqualTest_39 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_39, EqualStrings_39) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_39, DifferentStrings_39) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_39, BothNull_39) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_39, OneNull_39) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_39, PartialCompareWithNChar_39) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilStringEqualTest_39, EmptyStrings_39) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_39, DifferentLengths_39) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hell"));
}

// ==================== IsNameStartChar Tests ====================

class XMLUtilIsNameStartCharTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsNameStartCharTest_39, LetterIsNameStartChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilIsNameStartCharTest_39, UnderscoreIsNameStartChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilIsNameStartCharTest_39, ColonIsNameStartChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilIsNameStartCharTest_39, DigitIsNotNameStartChar_39) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilIsNameStartCharTest_39, HyphenIsNotNameStartChar_39) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLUtilIsNameStartCharTest_39, DotIsNotNameStartChar_39) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

// ==================== IsNameChar Tests ====================

class XMLUtilIsNameCharTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsNameCharTest_39, LetterIsNameChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilIsNameCharTest_39, DigitIsNameChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilIsNameCharTest_39, HyphenIsNameChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilIsNameCharTest_39, DotIsNameChar_39) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilIsNameCharTest_39, SpaceIsNotNameChar_39) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ==================== IsUTF8Continuation Tests ====================

class XMLUtilIsUTF8ContinuationTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_39, ContinuationByte_39) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_39, NonContinuationByte_39) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0xC0));
}

// ==================== ToStr / ToInt Tests ====================

class XMLUtilConversionTest_39 : public ::testing::Test {};

TEST_F(XMLUtilConversionTest_39, IntToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilConversionTest_39, NegativeIntToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, -100);
}

TEST_F(XMLUtilConversionTest_39, UnsignedToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr((unsigned int)12345, buffer, sizeof(buffer));
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &value));
    EXPECT_EQ(value, 12345u);
}

TEST_F(XMLUtilConversionTest_39, BoolTrueToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_39, BoolFalseToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_39, FloatToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &value));
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLUtilConversionTest_39, DoubleToStrAndBack_39) {
    char buffer[64];
    XMLUtil::ToStr(2.71828, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(value, 2.71828, 0.0001);
}

TEST_F(XMLUtilConversionTest_39, Int64ToStrAndBack_39) {
    char buffer[64];
    int64_t input = 9223372036854775807LL;
    XMLUtil::ToStr(input, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(value, input);
}

TEST_F(XMLUtilConversionTest_39, Unsigned64ToStrAndBack_39) {
    char buffer[64];
    uint64_t input = 18446744073709551615ULL;
    XMLUtil::ToStr(input, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(value, input);
}

TEST_F(XMLUtilConversionTest_39, ToIntFailsOnInvalidString_39) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilConversionTest_39, ToIntFailsOnNull_39) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_39, ToUnsignedFailsOnInvalidString_39) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilConversionTest_39, ToBoolFailsOnInvalidString_39) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilConversionTest_39, ToFloatFailsOnInvalidString_39) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("notanumber", &value));
}

TEST_F(XMLUtilConversionTest_39, ToDoubleFailsOnInvalidString_39) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("notanumber", &value));
}

TEST_F(XMLUtilConversionTest_39, ToInt64FailsOnNull_39) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_39, ToUnsigned64FailsOnNull_39) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_39, ToBoolAcceptsTrue_39) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_39, ToBoolAcceptsFalse_39) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_39, ToBoolAccepts1_39) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_39, ToBoolAccepts0_39) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_39, ZeroIntToStr_39) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, 0);
}

// ==================== ReadBOM Tests ====================

class XMLUtilReadBOMTest_39 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_39, NoBOM_39) {
    const char* input = "<?xml version=\"1.0\"?>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_39, WithUTF8BOM_39) {
    const char bom[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3);
}

TEST_F(XMLUtilReadBOMTest_39, NullInput_39) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

class XMLUtilConvertUTF32ToUTF8Test_39 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_39, ASCIICharacter_39) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_39, TwoByteCharacter_39) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // Latin capital letter E with acute
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_39, ThreeByteCharacter_39) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // Euro sign
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_39, FourByteCharacter_39) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // Emoji
    EXPECT_EQ(length, 4);
}

// ==================== SetBoolSerialization Tests ====================

class XMLUtilSetBoolSerializationTest_39 : public ::testing::Test {};

TEST_F(XMLUtilSetBoolSerializationTest_39, CustomBoolSerialization_39) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
    // Reset to defaults
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLUtilSetBoolSerializationTest_39, DefaultBoolSerialization_39) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ==================== GetCharacterRef Tests ====================

class XMLUtilGetCharacterRefTest_39 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_39, DecimalCharRef_39) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_39, HexCharRef_39) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_39, NotACharRef_39) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}
