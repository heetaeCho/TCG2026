#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== ReadBOM Tests ====================

class XMLUtilReadBOMTest_162 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_162, DetectsBOMPresent_162) {
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    const char input[] = {(char)0xEF, (char)0xBB, (char)0xBF, 'H', 'e', 'l', 'l', 'o', '\0'};
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, input + 3);
}

TEST_F(XMLUtilReadBOMTest_162, NoBOMPresent_162) {
    const char* input = "Hello World";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_162, BOMOnlyNoContent_162) {
    const char input[] = {(char)0xEF, (char)0xBB, (char)0xBF, '\0'};
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, input + 3);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilReadBOMTest_162, PartialBOM_FirstByteOnly_162) {
    const char input[] = {(char)0xEF, 'A', 'B', '\0'};
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_162, PartialBOM_TwoBytesOnly_162) {
    const char input[] = {(char)0xEF, (char)0xBB, 'X', '\0'};
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_162, EmptyStringNoBOM_162) {
    const char* input = "";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

// ==================== ToStr / ToInt Tests ====================

class XMLUtilToStrTest_162 : public ::testing::Test {};

TEST_F(XMLUtilToStrTest_162, IntToStr_Positive_162) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_162, IntToStr_Negative_162) {
    char buffer[64];
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-100");
}

TEST_F(XMLUtilToStrTest_162, IntToStr_Zero_162) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_162, UnsignedToStr_162) {
    char buffer[64];
    XMLUtil::ToStr((unsigned int)12345, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "12345");
}

TEST_F(XMLUtilToStrTest_162, BoolToStr_True_162) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilToStrTest_162, BoolToStr_False_162) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST_F(XMLUtilToStrTest_162, FloatToStr_162) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(parsed, 3.14f, 0.01f);
}

TEST_F(XMLUtilToStrTest_162, DoubleToStr_162) {
    char buffer[64];
    XMLUtil::ToStr(2.71828, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(parsed, 2.71828, 0.0001);
}

TEST_F(XMLUtilToStrTest_162, Int64ToStr_162) {
    char buffer[64];
    int64_t val = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "9223372036854775807");
}

TEST_F(XMLUtilToStrTest_162, Uint64ToStr_162) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "18446744073709551615");
}

// ==================== ToInt / ToUnsigned / ToBool etc. Tests ====================

class XMLUtilParseTest_162 : public ::testing::Test {};

TEST_F(XMLUtilParseTest_162, ToInt_ValidPositive_162) {
    int value = 0;
    bool result = XMLUtil::ToInt("123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 123);
}

TEST_F(XMLUtilParseTest_162, ToInt_ValidNegative_162) {
    int value = 0;
    bool result = XMLUtil::ToInt("-456", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, -456);
}

TEST_F(XMLUtilParseTest_162, ToInt_InvalidString_162) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToInt_EmptyString_162) {
    int value = 0;
    bool result = XMLUtil::ToInt("", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToInt_NullString_162) {
    int value = 0;
    bool result = XMLUtil::ToInt(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned_Valid_162) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("789", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 789u);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned_Invalid_162) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("xyz", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned_Null_162) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToBool_TrueString_162) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_162, ToBool_FalseString_162) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_162, ToBool_One_162) {
    bool value = false;
    bool result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_162, ToBool_Zero_162) {
    bool value = true;
    bool result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_162, ToBool_Invalid_162) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToBool_Null_162) {
    bool value = false;
    bool result = XMLUtil::ToBool(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToFloat_Valid_162) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST_F(XMLUtilParseTest_162, ToFloat_Invalid_162) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToFloat_Null_162) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToDouble_Valid_162) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("2.71828", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 2.71828, 0.00001);
}

TEST_F(XMLUtilParseTest_162, ToDouble_Invalid_162) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("xyz", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToDouble_Null_162) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToInt64_Valid_162) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST_F(XMLUtilParseTest_162, ToInt64_Invalid_162) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToInt64_Null_162) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned64_Valid_162) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned64_Invalid_162) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("notnum", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilParseTest_162, ToUnsigned64_Null_162) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ==================== Utility function tests ====================

class XMLUtilMiscTest_162 : public ::testing::Test {};

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_Space_162) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_Tab_162) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_Newline_162) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_CarriageReturn_162) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_NotWhitespace_162) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilMiscTest_162, IsWhiteSpace_NullChar_162) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_SameStrings_162) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_DifferentStrings_162) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_WithNChar_162) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_BothNull_162) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_OneNull_162) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilMiscTest_162, StringEqual_EmptyStrings_162) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilMiscTest_162, IsNameStartChar_Letter_162) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilMiscTest_162, IsNameStartChar_Underscore_162) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilMiscTest_162, IsNameStartChar_Colon_162) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilMiscTest_162, IsNameStartChar_Digit_162) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST_F(XMLUtilMiscTest_162, IsNameChar_Digit_162) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilMiscTest_162, IsNameChar_Letter_162) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilMiscTest_162, IsNameChar_Hyphen_162) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilMiscTest_162, IsNameChar_Dot_162) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilMiscTest_162, IsNameChar_Space_162) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

TEST_F(XMLUtilMiscTest_162, IsPrefixHex_ValidHex_162) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilMiscTest_162, IsPrefixHex_NotHex_162) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("abc"));
}

TEST_F(XMLUtilMiscTest_162, IsUTF8Continuation_162) {
    // UTF-8 continuation byte: 10xxxxxx (0x80 to 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
}

// ==================== SkipWhiteSpace Tests ====================

class XMLUtilSkipWhiteSpaceTest_162 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_162, SkipsLeadingSpaces_162) {
    const char* input = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_162, SkipsTabsAndSpaces_162) {
    const char* input = " \t \t hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_162, CountsNewlines_162) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_162, NoWhitespace_162) {
    const char* input = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(result, input);
    EXPECT_EQ(lineNum, 1);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_162, AllWhitespace_162) {
    const char* input = "   ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_162, NullLineNum_162) {
    const char* input = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

class XMLUtilConvertUTF32Test_162 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_162, ASCIIChar_162) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32Test_162, TwoByteChar_162) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32Test_162, ThreeByteChar_162) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length); // 中
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32Test_162, FourByteChar_162) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(length, 4);
}

TEST_F(XMLUtilConvertUTF32Test_162, NullCharacter_162) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0, output, &length);
    EXPECT_EQ(length, 0);
}

// ==================== SetBoolSerialization Tests ====================

class XMLUtilBoolSerializationTest_162 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilBoolSerializationTest_162, CustomBoolStrings_162) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilBoolSerializationTest_162, ResetToDefault_162) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ==================== GetCharacterRef Tests ====================

class XMLUtilGetCharacterRefTest_162 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_162, DecimalCharRef_162) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_162, HexCharRef_162) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_162, NotACharRef_162) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ==================== Roundtrip Tests ====================

class XMLUtilRoundtripTest_162 : public ::testing::Test {};

TEST_F(XMLUtilRoundtripTest_162, IntRoundtrip_162) {
    char buffer[64];
    int original = 42;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &parsed));
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLUtilRoundtripTest_162, DoubleRoundtrip_162) {
    char buffer[64];
    double original = 3.14159265358979;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double parsed = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_NEAR(parsed, original, 1e-10);
}

TEST_F(XMLUtilRoundtripTest_162, Int64Roundtrip_162) {
    char buffer[64];
    int64_t original = -9223372036854775807LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLUtilRoundtripTest_162, Uint64Roundtrip_162) {
    char buffer[64];
    uint64_t original = 12345678901234567890ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLUtilRoundtripTest_162, FloatRoundtrip_162) {
    char buffer[64];
    float original = 1.5f;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_FLOAT_EQ(parsed, original);
}

TEST_F(XMLUtilRoundtripTest_162, BoolRoundtripTrue_162) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool parsed = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_TRUE(parsed);
}

TEST_F(XMLUtilRoundtripTest_162, BoolRoundtripFalse_162) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool parsed = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_FALSE(parsed);
}
