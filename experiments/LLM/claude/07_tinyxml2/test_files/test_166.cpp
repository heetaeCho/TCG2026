#include <gtest/gtest.h>
#include <cstring>
#include <climits>
#include <cstdint>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToStr Tests
// ============================================================

class XMLUtilToStrTest_166 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_166, ToStr_Int_Positive_166) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int_Negative_166) {
    XMLUtil::ToStr(-99, buffer, sizeof(buffer));
    EXPECT_STREQ("-99", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int_Zero_166) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int_MaxValue_166) {
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int_MinValue_166) {
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Unsigned_Zero_166) {
    XMLUtil::ToStr((unsigned)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Unsigned_Positive_166) {
    XMLUtil::ToStr((unsigned)12345, buffer, sizeof(buffer));
    EXPECT_STREQ("12345", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Unsigned_MaxValue_166) {
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Bool_True_166) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Bool_False_166) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Float_Positive_166) {
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_NEAR(3.14f, parsed, 0.01f);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Float_Zero_166) {
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Float_Negative_166) {
    XMLUtil::ToStr(-1.5f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_NEAR(-1.5f, parsed, 0.01f);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Double_Positive_166) {
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_NEAR(3.141592653589793, parsed, 1e-10);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Double_Zero_166) {
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(0.0, parsed);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Double_Negative_166) {
    XMLUtil::ToStr(-2.718281828, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_NEAR(-2.718281828, parsed, 1e-6);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int64_Positive_166) {
    int64_t val = 9223372036854775807LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int64_Negative_166) {
    int64_t val = -9223372036854775807LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Int64_Zero_166) {
    XMLUtil::ToStr((int64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Uint64_Zero_166) {
    XMLUtil::ToStr((uint64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_166, ToStr_Uint64_MaxValue_166) {
    uint64_t val = UINT64_MAX;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%llu", (unsigned long long)val);
    EXPECT_STREQ(expected, buffer);
}

// ============================================================
// ToInt / ToUnsigned / ToBool / ToFloat / ToDouble / ToInt64 / ToUnsigned64
// ============================================================

class XMLUtilParseTest_166 : public ::testing::Test {};

TEST_F(XMLUtilParseTest_166, ToInt_ValidPositive_166) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("123", &value));
    EXPECT_EQ(123, value);
}

TEST_F(XMLUtilParseTest_166, ToInt_ValidNegative_166) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-456", &value));
    EXPECT_EQ(-456, value);
}

TEST_F(XMLUtilParseTest_166, ToInt_ValidZero_166) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilParseTest_166, ToInt_InvalidString_166) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilParseTest_166, ToInt_NullString_166) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToInt_EmptyString_166) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilParseTest_166, ToUnsigned_ValidPositive_166) {
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("789", &value));
    EXPECT_EQ(789u, value);
}

TEST_F(XMLUtilParseTest_166, ToUnsigned_Zero_166) {
    unsigned value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilParseTest_166, ToUnsigned_InvalidString_166) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilParseTest_166, ToUnsigned_NullString_166) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToBool_TrueString_166) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_166, ToBool_FalseString_166) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_166, ToBool_NumericOne_166) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_166, ToBool_NumericZero_166) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_166, ToBool_InvalidString_166) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilParseTest_166, ToBool_NullString_166) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToFloat_ValidPositive_166) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST_F(XMLUtilParseTest_166, ToFloat_ValidNegative_166) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_NEAR(-2.5f, value, 0.001f);
}

TEST_F(XMLUtilParseTest_166, ToFloat_InvalidString_166) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("notanumber", &value));
}

TEST_F(XMLUtilParseTest_166, ToFloat_NullString_166) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToDouble_ValidPositive_166) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.141592653589793", &value));
    EXPECT_NEAR(3.141592653589793, value, 1e-12);
}

TEST_F(XMLUtilParseTest_166, ToDouble_ValidNegative_166) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("-1.23456789", &value));
    EXPECT_NEAR(-1.23456789, value, 1e-8);
}

TEST_F(XMLUtilParseTest_166, ToDouble_InvalidString_166) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("hello", &value));
}

TEST_F(XMLUtilParseTest_166, ToDouble_NullString_166) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToInt64_ValidPositive_166) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(INT64_MAX, value);
}

TEST_F(XMLUtilParseTest_166, ToInt64_ValidNegative_166) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilParseTest_166, ToInt64_Zero_166) {
    int64_t value = -1;
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilParseTest_166, ToInt64_InvalidString_166) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("notint", &value));
}

TEST_F(XMLUtilParseTest_166, ToInt64_NullString_166) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilParseTest_166, ToUnsigned64_ValidPositive_166) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilParseTest_166, ToUnsigned64_Zero_166) {
    uint64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilParseTest_166, ToUnsigned64_InvalidString_166) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("invalid", &value));
}

TEST_F(XMLUtilParseTest_166, ToUnsigned64_NullString_166) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilBOMTest_166 : public ::testing::Test {};

TEST_F(XMLUtilBOMTest_166, ReadBOM_NoBOM_166) {
    bool hasBOM = true;
    const char* input = "<xml>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilBOMTest_166, ReadBOM_WithBOM_166) {
    bool hasBOM = false;
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    const char input[] = "\xEF\xBB\xBF<xml>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

TEST_F(XMLUtilBOMTest_166, ReadBOM_NullPointer_166) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilWhiteSpaceTest_166 : public ::testing::Test {};

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_Space_166) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_Tab_166) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_Newline_166) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_CarriageReturn_166) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_NotWhitespace_166) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_NullChar_166) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

TEST_F(XMLUtilWhiteSpaceTest_166, IsWhiteSpace_Digit_166) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('5'));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_166 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_LeadingSpaces_166) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_NoWhiteSpace_166) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_AllWhiteSpace_166) {
    const char* input = "   \t\n";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(input + 5, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_WithLineCount_166) {
    int lineNum = 1;
    const char* input = "\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(3, lineNum);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_NullPointer_166) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_166, SkipWhiteSpace_EmptyString_166) {
    const char* input = "";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(input, result);
}

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_166 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_166, StringEqual_EqualStrings_166) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_DifferentStrings_166) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_WithNChar_166) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_WithNCharDifferent_166) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hallo", 5));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_BothNull_166) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_OneNull_166) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_EmptyStrings_166) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_166, StringEqual_DifferentLengths_166) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hello world"));
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_166 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_166, IsNameStartChar_Letter_166) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameStartChar_Underscore_166) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameStartChar_Colon_166) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameStartChar_Digit_166) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameStartChar_Space_166) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
}

TEST_F(XMLUtilNameCharTest_166, IsNameChar_Letter_166) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameChar_Digit_166) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameChar_Dash_166) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameChar_Dot_166) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_166, IsNameChar_Space_166) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilIsPrefixHexTest_166 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_166, IsPrefixHex_Valid_166) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_166, IsPrefixHex_Invalid_166) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST_F(XMLUtilIsPrefixHexTest_166, IsPrefixHex_JustZero_166) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

class XMLUtilUTF8Test_166 : public ::testing::Test {};

TEST_F(XMLUtilUTF8Test_166, IsUTF8Continuation_ContinuationByte_166) {
    // Continuation bytes have the form 10xxxxxx (0x80-0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilUTF8Test_166, IsUTF8Continuation_NotContinuation_166) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilConvertUTF32Test_166 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_166, ConvertUTF32ToUTF8_ASCII_166) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32Test_166, ConvertUTF32ToUTF8_TwoByte_166) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32Test_166, ConvertUTF32ToUTF8_ThreeByte_166) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32Test_166, ConvertUTF32ToUTF8_FourByte_166) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(4, length);
}

// ============================================================
// GetCharacterRef Tests
// ============================================================

class XMLUtilGetCharacterRefTest_166 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_166, GetCharacterRef_DecimalRef_166) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_166, GetCharacterRef_HexRef_166) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_166, GetCharacterRef_NotARef_166) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilSetBoolSerializationTest_166 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_166, CustomBoolSerialization_166) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
}

TEST_F(XMLUtilSetBoolSerializationTest_166, ResetBoolSerialization_166) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// Round-trip Tests (ToStr -> Parse)
// ============================================================

class XMLUtilRoundTripTest_166 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Int_166) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Unsigned_166) {
    XMLUtil::ToStr((unsigned)999, buffer, sizeof(buffer));
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &value));
    EXPECT_EQ(999u, value);
}

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Bool_166) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Double_166) {
    XMLUtil::ToStr(1.23456789, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(1.23456789, value, 1e-6);
}

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Int64_166) {
    int64_t original = 123456789012345LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundTripTest_166, RoundTrip_Uint64_166) {
    uint64_t original = 18446744073709551610ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}
