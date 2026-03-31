#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToStr Tests
// ============================================================

class XMLUtilToStrTest_168 : public ::testing::Test {
protected:
    char buffer[256];
};

// --- ToStr(int) ---

TEST_F(XMLUtilToStrTest_168, ToStrInt_Positive_168) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt_Negative_168) {
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ("-100", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt_Zero_168) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt_MaxValue_168) {
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt_MinValue_168) {
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

// --- ToStr(unsigned int) ---

TEST_F(XMLUtilToStrTest_168, ToStrUnsigned_Positive_168) {
    XMLUtil::ToStr(123u, buffer, sizeof(buffer));
    EXPECT_STREQ("123", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrUnsigned_Zero_168) {
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrUnsigned_MaxValue_168) {
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

// --- ToStr(bool) ---

TEST_F(XMLUtilToStrTest_168, ToStrBool_True_168) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrBool_False_168) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// --- ToStr(float) ---

TEST_F(XMLUtilToStrTest_168, ToStrFloat_Positive_168) {
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(3.14f, parsed, 1e-5f);
}

TEST_F(XMLUtilToStrTest_168, ToStrFloat_Zero_168) {
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrFloat_Negative_168) {
    XMLUtil::ToStr(-2.5f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(-2.5f, parsed, 1e-5f);
}

// --- ToStr(double) ---

TEST_F(XMLUtilToStrTest_168, ToStrDouble_Positive_168) {
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(3.141592653589793, parsed, 1e-10);
}

TEST_F(XMLUtilToStrTest_168, ToStrDouble_Zero_168) {
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrDouble_Negative_168) {
    XMLUtil::ToStr(-1.23456789, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(-1.23456789, parsed, 1e-10);
}

// --- ToStr(int64_t) ---

TEST_F(XMLUtilToStrTest_168, ToStrInt64_Positive_168) {
    XMLUtil::ToStr((int64_t)1234567890123LL, buffer, sizeof(buffer));
    EXPECT_STREQ("1234567890123", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt64_Negative_168) {
    XMLUtil::ToStr((int64_t)-1234567890123LL, buffer, sizeof(buffer));
    EXPECT_STREQ("-1234567890123", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrInt64_Zero_168) {
    XMLUtil::ToStr((int64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

// --- ToStr(uint64_t) ---

TEST_F(XMLUtilToStrTest_168, ToStrUint64_Positive_168) {
    XMLUtil::ToStr((uint64_t)9876543210ULL, buffer, sizeof(buffer));
    EXPECT_STREQ("9876543210", buffer);
}

TEST_F(XMLUtilToStrTest_168, ToStrUint64_Zero_168) {
    XMLUtil::ToStr((uint64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

// ============================================================
// ToInt / ToUnsigned / ToBool / ToFloat / ToDouble / ToInt64 / ToUnsigned64 Tests
// ============================================================

class XMLUtilFromStrTest_168 : public ::testing::Test {};

// --- ToInt ---

TEST_F(XMLUtilFromStrTest_168, ToInt_ValidPositive_168) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilFromStrTest_168, ToInt_ValidNegative_168) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilFromStrTest_168, ToInt_ValidZero_168) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilFromStrTest_168, ToInt_Invalid_168) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToInt_NullStr_168) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_168, ToInt_EmptyStr_168) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// --- ToUnsigned ---

TEST_F(XMLUtilFromStrTest_168, ToUnsigned_Valid_168) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(123u, value);
}

TEST_F(XMLUtilFromStrTest_168, ToUnsigned_Invalid_168) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToUnsigned_NullStr_168) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// --- ToBool ---

TEST_F(XMLUtilFromStrTest_168, ToBool_True_168) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_168, ToBool_False_168) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_168, ToBool_One_168) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_168, ToBool_Zero_168) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_168, ToBool_Invalid_168) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToBool_NullStr_168) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// --- ToFloat ---

TEST_F(XMLUtilFromStrTest_168, ToFloat_Valid_168) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 1e-5f);
}

TEST_F(XMLUtilFromStrTest_168, ToFloat_Negative_168) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_NEAR(-2.5f, value, 1e-5f);
}

TEST_F(XMLUtilFromStrTest_168, ToFloat_Invalid_168) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("xyz", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToFloat_NullStr_168) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// --- ToDouble ---

TEST_F(XMLUtilFromStrTest_168, ToDouble_Valid_168) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.141592653589793", &value));
    EXPECT_NEAR(3.141592653589793, value, 1e-12);
}

TEST_F(XMLUtilFromStrTest_168, ToDouble_Invalid_168) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToDouble_NullStr_168) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// --- ToInt64 ---

TEST_F(XMLUtilFromStrTest_168, ToInt64_Valid_168) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(1234567890123LL, value);
}

TEST_F(XMLUtilFromStrTest_168, ToInt64_Negative_168) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-9876543210", &value));
    EXPECT_EQ(-9876543210LL, value);
}

TEST_F(XMLUtilFromStrTest_168, ToInt64_Invalid_168) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToInt64_NullStr_168) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// --- ToUnsigned64 ---

TEST_F(XMLUtilFromStrTest_168, ToUnsigned64_Valid_168) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("9876543210", &value));
    EXPECT_EQ(9876543210ULL, value);
}

TEST_F(XMLUtilFromStrTest_168, ToUnsigned64_Invalid_168) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilFromStrTest_168, ToUnsigned64_NullStr_168) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilBOMTest_168 : public ::testing::Test {};

TEST_F(XMLUtilBOMTest_168, ReadBOM_WithBOM_168) {
    const char bom[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3);
}

TEST_F(XMLUtilBOMTest_168, ReadBOM_WithoutBOM_168) {
    const char* noBom = "<root/>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, noBom);
}

TEST_F(XMLUtilBOMTest_168, ReadBOM_NullPointer_168) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilWhiteSpaceTest_168 : public ::testing::Test {};

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_Space_168) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_Tab_168) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_Newline_168) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_CarriageReturn_168) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_LetterA_168) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_Digit_168) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilWhiteSpaceTest_168, IsWhiteSpace_NullChar_168) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_168 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_LeadingSpaces_168) {
    const char* str = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(result, str + 3);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_NoSpaces_168) {
    const char* str = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(result, str);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_AllSpaces_168) {
    const char* str = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(result, str + 3);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_MixedWhitespace_168) {
    const char* str = " \t\n\rX";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(*result, 'X');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_Null_168) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_168, SkipWhiteSpace_CountsNewlines_168) {
    const char* str = "\n\n\nX";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ(*result, 'X');
    EXPECT_EQ(lineNum, 4);
}

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_168 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_168, StringEqual_SameStrings_168) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_DifferentStrings_168) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_PartialMatch_168) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello", 5));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_BothNull_168) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_OneNull_168) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_EmptyStrings_168) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_168, StringEqual_DifferentLengths_168) {
    EXPECT_FALSE(XMLUtil::StringEqual("hi", "hello"));
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_168 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_168, IsNameStartChar_Letter_168) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameStartChar_Underscore_168) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameStartChar_Colon_168) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameStartChar_Digit_168) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameStartChar_Hyphen_168) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameChar_Letter_168) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameChar_Digit_168) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameChar_Hyphen_168) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameChar_Dot_168) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_168, IsNameChar_Space_168) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilPrefixHexTest_168 : public ::testing::Test {};

TEST_F(XMLUtilPrefixHexTest_168, IsPrefixHex_ValidLower_168) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
}

TEST_F(XMLUtilPrefixHexTest_168, IsPrefixHex_ValidUpper_168) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilPrefixHexTest_168, IsPrefixHex_NotHex_168) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilPrefixHexTest_168, IsPrefixHex_JustZero_168) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

class XMLUtilUTF8Test_168 : public ::testing::Test {};

TEST_F(XMLUtilUTF8Test_168, IsUTF8Continuation_ValidContinuationByte_168) {
    // Continuation bytes are 0x80-0xBF (10xxxxxx)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilUTF8Test_168, IsUTF8Continuation_NotContinuation_168) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x7F));
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilConvertUTF32Test_168 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_168, ConvertASCII_168) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32Test_168, ConvertTwoByte_168) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32Test_168, ConvertThreeByte_168) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32Test_168, ConvertFourByte_168) {
    char output[8] = {0};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(length, 4);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilBoolSerializationTest_168 : public ::testing::Test {
protected:
    char buffer[256];
    
    void TearDown() override {
        // Reset to default
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilBoolSerializationTest_168, CustomBoolSerialization_168) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
}

TEST_F(XMLUtilBoolSerializationTest_168, ResetToDefault_168) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// GetCharacterRef Tests
// ============================================================

class XMLUtilCharacterRefTest_168 : public ::testing::Test {};

TEST_F(XMLUtilCharacterRefTest_168, DecimalCharRef_168) {
    char value[8] = {0};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilCharacterRefTest_168, HexCharRef_168) {
    char value[8] = {0};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilCharacterRefTest_168, InvalidCharRef_168) {
    char value[8] = {0};
    int length = 0;
    const char* input = "not a ref";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// Roundtrip tests (ToStr -> To*)
// ============================================================

class XMLUtilRoundtripTest_168 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilRoundtripTest_168, IntRoundtrip_168) {
    int original = 12345;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_168, FloatRoundtrip_168) {
    float original = 1.23456f;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_NEAR(original, parsed, 1e-5f);
}

TEST_F(XMLUtilRoundtripTest_168, DoubleRoundtrip_168) {
    double original = 1.234567890123;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double parsed = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_NEAR(original, parsed, 1e-10);
}

TEST_F(XMLUtilRoundtripTest_168, BoolTrueRoundtrip_168) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool parsed = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_TRUE(parsed);
}

TEST_F(XMLUtilRoundtripTest_168, BoolFalseRoundtrip_168) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool parsed = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_FALSE(parsed);
}

TEST_F(XMLUtilRoundtripTest_168, Int64Roundtrip_168) {
    int64_t original = 9876543210123LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_168, Uint64Roundtrip_168) {
    uint64_t original = 18446744073709551000ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}
