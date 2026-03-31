#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>

// Include the actual tinyxml2 header
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Tests for ConvertUTF32ToUTF8
// ============================================================

class XMLUtilConvertUTF32ToUTF8Test_163 : public ::testing::Test {
protected:
    char output[8];
    int length;

    void SetUp() override {
        memset(output, 0, sizeof(output));
        length = 0;
    }
};

// ASCII character (1 byte)
TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, SingleByteASCII_NullChar_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x00, output, &length);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0x00);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, SingleByteASCII_A_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, SingleByteASCII_MaxOneByte_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x7F, output, &length);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0x7F);
}

// 2-byte characters (0x80 - 0x7FF)
TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, TwoByte_MinBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x80, output, &length);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xC2);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0x80);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, TwoByte_MaxBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x7FF, output, &length);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xDF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBF);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, TwoByte_CentSign_163) {
    // U+00A2 = ¢ = 0xC2 0xA2
    XMLUtil::ConvertUTF32ToUTF8(0xA2, output, &length);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xC2);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xA2);
}

// 3-byte characters (0x800 - 0xFFFF)
TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, ThreeByte_MinBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x800, output, &length);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xE0);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xA0);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0x80);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, ThreeByte_MaxBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0xFFFF, output, &length);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, ThreeByte_EuroSign_163) {
    // U+20AC = € = 0xE2 0x82 0xAC
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xE2);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0x82);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xAC);
}

// 4-byte characters (0x10000 - 0x1FFFFF)
TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, FourByte_MinBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x10000, output, &length);
    EXPECT_EQ(length, 4);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xF0);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0x90);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0x80);
    EXPECT_EQ(static_cast<unsigned char>(output[3]), 0x80);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, FourByte_MaxBoundary_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x1FFFFF, output, &length);
    EXPECT_EQ(length, 4);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xF7);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(output[3]), 0xBF);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, FourByte_Emoji_163) {
    // U+1F600 = 😀 = 0xF0 0x9F 0x98 0x80
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length);
    EXPECT_EQ(length, 4);
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 0xF0);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 0x9F);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 0x98);
    EXPECT_EQ(static_cast<unsigned char>(output[3]), 0x80);
}

// Out of range - should set length to 0
TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, OutOfRange_200000_163) {
    XMLUtil::ConvertUTF32ToUTF8(0x200000, output, &length);
    EXPECT_EQ(length, 0);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, OutOfRange_VeryLarge_163) {
    XMLUtil::ConvertUTF32ToUTF8(0xFFFFFFFF, output, &length);
    EXPECT_EQ(length, 0);
}

// ============================================================
// Tests for ToStr and To* conversion functions
// ============================================================

class XMLUtilToStrTest_163 : public ::testing::Test {
protected:
    char buffer[256];

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

// ToStr(int)
TEST_F(XMLUtilToStrTest_163, ToStrInt_Zero_163) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_163, ToStrInt_Positive_163) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_163, ToStrInt_Negative_163) {
    XMLUtil::ToStr(-1, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-1");
}

TEST_F(XMLUtilToStrTest_163, ToStrInt_MaxInt_163) {
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(buffer, expected);
}

TEST_F(XMLUtilToStrTest_163, ToStrInt_MinInt_163) {
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(buffer, expected);
}

// ToStr(unsigned int)
TEST_F(XMLUtilToStrTest_163, ToStrUnsigned_Zero_163) {
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_163, ToStrUnsigned_MaxUint_163) {
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(buffer, expected);
}

// ToStr(bool)
TEST_F(XMLUtilToStrTest_163, ToStrBool_True_163) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilToStrTest_163, ToStrBool_False_163) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ToStr(float)
TEST_F(XMLUtilToStrTest_163, ToStrFloat_Zero_163) {
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    // Should contain "0" in some form
    float parsed = 0;
    sscanf(buffer, "%f", &parsed);
    EXPECT_FLOAT_EQ(parsed, 0.0f);
}

TEST_F(XMLUtilToStrTest_163, ToStrFloat_Positive_163) {
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = 0;
    sscanf(buffer, "%f", &parsed);
    EXPECT_NEAR(parsed, 3.14f, 0.001f);
}

// ToStr(double)
TEST_F(XMLUtilToStrTest_163, ToStrDouble_Zero_163) {
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = 0;
    sscanf(buffer, "%lf", &parsed);
    EXPECT_DOUBLE_EQ(parsed, 0.0);
}

TEST_F(XMLUtilToStrTest_163, ToStrDouble_Positive_163) {
    XMLUtil::ToStr(3.14159265358979, buffer, sizeof(buffer));
    double parsed = 0;
    sscanf(buffer, "%lf", &parsed);
    EXPECT_NEAR(parsed, 3.14159265358979, 1e-10);
}

// ToStr(int64_t)
TEST_F(XMLUtilToStrTest_163, ToStrInt64_Zero_163) {
    XMLUtil::ToStr(static_cast<int64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_163, ToStrInt64_Large_163) {
    int64_t val = 9223372036854775807LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    int64_t parsed = 0;
    sscanf(buffer, "%" SCNd64, &parsed);
    EXPECT_EQ(parsed, val);
}

// ToStr(uint64_t)
TEST_F(XMLUtilToStrTest_163, ToStrUint64_Zero_163) {
    XMLUtil::ToStr(static_cast<uint64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

// ============================================================
// Tests for ToInt, ToUnsigned, ToBool, ToFloat, ToDouble, ToInt64, ToUnsigned64
// ============================================================

class XMLUtilParseTest_163 : public ::testing::Test {};

// ToInt
TEST_F(XMLUtilParseTest_163, ToInt_ValidPositive_163) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilParseTest_163, ToInt_ValidNegative_163) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-7", &value));
    EXPECT_EQ(value, -7);
}

TEST_F(XMLUtilParseTest_163, ToInt_ValidZero_163) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilParseTest_163, ToInt_InvalidString_163) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilParseTest_163, ToInt_NullString_163) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilParseTest_163, ToInt_EmptyString_163) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ToUnsigned
TEST_F(XMLUtilParseTest_163, ToUnsigned_ValidPositive_163) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(value, 123u);
}

TEST_F(XMLUtilParseTest_163, ToUnsigned_InvalidString_163) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilParseTest_163, ToUnsigned_NullString_163) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ToBool
TEST_F(XMLUtilParseTest_163, ToBool_True_163) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_163, ToBool_False_163) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_163, ToBool_One_163) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_163, ToBool_Zero_163) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_163, ToBool_InvalidString_163) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilParseTest_163, ToBool_NullString_163) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ToFloat
TEST_F(XMLUtilParseTest_163, ToFloat_ValidPositive_163) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST_F(XMLUtilParseTest_163, ToFloat_ValidNegative_163) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_NEAR(value, -2.5f, 0.001f);
}

TEST_F(XMLUtilParseTest_163, ToFloat_InvalidString_163) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilParseTest_163, ToFloat_NullString_163) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ToDouble
TEST_F(XMLUtilParseTest_163, ToDouble_ValidPositive_163) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159265358979", &value));
    EXPECT_NEAR(value, 3.14159265358979, 1e-10);
}

TEST_F(XMLUtilParseTest_163, ToDouble_InvalidString_163) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST_F(XMLUtilParseTest_163, ToDouble_NullString_163) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ToInt64
TEST_F(XMLUtilParseTest_163, ToInt64_ValidPositive_163) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLUtilParseTest_163, ToInt64_ValidNegative_163) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(value, -100);
}

TEST_F(XMLUtilParseTest_163, ToInt64_InvalidString_163) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilParseTest_163, ToInt64_NullString_163) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ToUnsigned64
TEST_F(XMLUtilParseTest_163, ToUnsigned64_ValidPositive_163) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("12345678901234", &value));
    EXPECT_EQ(value, 12345678901234ULL);
}

TEST_F(XMLUtilParseTest_163, ToUnsigned64_InvalidString_163) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &value));
}

TEST_F(XMLUtilParseTest_163, ToUnsigned64_NullString_163) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// Tests for IsWhiteSpace
// ============================================================

class XMLUtilIsWhiteSpaceTest_163 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_163, Space_163) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, Tab_163) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, Newline_163) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, CarriageReturn_163) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, NonWhiteSpace_A_163) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, NonWhiteSpace_Zero_163) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_163, NullChar_163) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// Tests for StringEqual
// ============================================================

class XMLUtilStringEqualTest_163 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_163, EqualStrings_163) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_163, DifferentStrings_163) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_163, EqualWithNChar_163) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helXX", 3));
}

TEST_F(XMLUtilStringEqualTest_163, DifferentWithNChar_163) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hxllo", 3));
}

TEST_F(XMLUtilStringEqualTest_163, BothNull_163) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_163, OneNull_163) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_163, EmptyStrings_163) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_163, EmptyVsNonEmpty_163) {
    EXPECT_FALSE(XMLUtil::StringEqual("", "a"));
}

// ============================================================
// Tests for IsNameStartChar and IsNameChar
// ============================================================

class XMLUtilIsNameCharTest_163 : public ::testing::Test {};

TEST_F(XMLUtilIsNameCharTest_163, LetterIsNameStartChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
}

TEST_F(XMLUtilIsNameCharTest_163, ColonIsNameStartChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilIsNameCharTest_163, UnderscoreIsNameStartChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilIsNameCharTest_163, DigitIsNotNameStartChar_163) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilIsNameCharTest_163, DigitIsNameChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilIsNameCharTest_163, HyphenIsNameChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilIsNameCharTest_163, DotIsNameChar_163) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilIsNameCharTest_163, SpaceIsNotNameChar_163) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// Tests for IsPrefixHex
// ============================================================

class XMLUtilIsPrefixHexTest_163 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_163, ValidHexPrefix_163) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_163, NotHexPrefix_163) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_163, JustZero_163) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// Tests for IsUTF8Continuation
// ============================================================

class XMLUtilIsUTF8ContinuationTest_163 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_163, ContinuationByte_163) {
    // Continuation bytes are 10xxxxxx (0x80 - 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xA0)));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_163, NonContinuationByte_163) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x00)));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
}

// ============================================================
// Tests for ReadBOM
// ============================================================

class XMLUtilReadBOMTest_163 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_163, WithBOM_163) {
    // UTF-8 BOM: EF BB BF
    const char bom[] = "\xEF\xBB\xBF<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3); // Should skip past the BOM
}

TEST_F(XMLUtilReadBOMTest_163, WithoutBOM_163) {
    const char noBom[] = "<xml>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, noBom);
}

TEST_F(XMLUtilReadBOMTest_163, NullInput_163) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// Tests for SkipWhiteSpace
// ============================================================

class XMLUtilSkipWhiteSpaceTest_163 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_163, SkipsLeadingSpaces_163) {
    const char* str = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_163, SkipsMixedWhitespace_163) {
    const char* str = " \t\n\rhello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_163, NoWhitespace_163) {
    const char* str = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(result, str);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_163, AllWhitespace_163) {
    const char* str = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_163, NullInput_163) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_163, CountsNewlines_163) {
    const char* str = "\n\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 4);
}

// ============================================================
// Tests for SetBoolSerialization
// ============================================================

class XMLUtilSetBoolSerializationTest_163 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to default
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_163, CustomBoolStrings_163) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilSetBoolSerializationTest_163, ResetToDefault_163) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ============================================================
// Additional boundary tests for ConvertUTF32ToUTF8
// ============================================================

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, BoundaryBetween1and2Bytes_163) {
    // 0x7F should be 1 byte, 0x80 should be 2 bytes
    XMLUtil::ConvertUTF32ToUTF8(0x7F, output, &length);
    EXPECT_EQ(length, 1);

    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x80, output, &length);
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, BoundaryBetween2and3Bytes_163) {
    // 0x7FF should be 2 bytes, 0x800 should be 3 bytes
    XMLUtil::ConvertUTF32ToUTF8(0x7FF, output, &length);
    EXPECT_EQ(length, 2);

    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x800, output, &length);
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, BoundaryBetween3and4Bytes_163) {
    // 0xFFFF should be 3 bytes, 0x10000 should be 4 bytes
    XMLUtil::ConvertUTF32ToUTF8(0xFFFF, output, &length);
    EXPECT_EQ(length, 3);

    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x10000, output, &length);
    EXPECT_EQ(length, 4);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, BoundaryBetween4BytesAndInvalid_163) {
    // 0x1FFFFF should be 4 bytes, 0x200000 should be invalid
    XMLUtil::ConvertUTF32ToUTF8(0x1FFFFF, output, &length);
    EXPECT_EQ(length, 4);

    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x200000, output, &length);
    EXPECT_EQ(length, 0);
}
