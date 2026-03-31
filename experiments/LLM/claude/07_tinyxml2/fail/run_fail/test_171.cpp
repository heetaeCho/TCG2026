#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <cstring>
#include <cmath>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================================
// ToStr tests
// ============================================================================

class XMLUtilToStrTest_171 : public ::testing::Test {
protected:
    char buffer[256];
};

// --- ToStr(int) ---

TEST_F(XMLUtilToStrTest_171, ToStrInt_Zero_171) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt_Positive_171) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt_Negative_171) {
    XMLUtil::ToStr(-123, buffer, sizeof(buffer));
    EXPECT_STREQ("-123", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt_MaxValue_171) {
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt_MinValue_171) {
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

// --- ToStr(unsigned int) ---

TEST_F(XMLUtilToStrTest_171, ToStrUnsigned_Zero_171) {
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrUnsigned_Positive_171) {
    XMLUtil::ToStr(12345u, buffer, sizeof(buffer));
    EXPECT_STREQ("12345", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrUnsigned_MaxValue_171) {
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

// --- ToStr(bool) ---

TEST_F(XMLUtilToStrTest_171, ToStrBool_True_171) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrBool_False_171) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// --- ToStr(float) ---

TEST_F(XMLUtilToStrTest_171, ToStrFloat_Zero_171) {
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    // Should produce some representation of 0
    float parsed = std::stof(buffer);
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST_F(XMLUtilToStrTest_171, ToStrFloat_Positive_171) {
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(3.14f, parsed, 0.001f);
}

TEST_F(XMLUtilToStrTest_171, ToStrFloat_Negative_171) {
    XMLUtil::ToStr(-2.5f, buffer, sizeof(buffer));
    float parsed = std::stof(buffer);
    EXPECT_NEAR(-2.5f, parsed, 0.001f);
}

// --- ToStr(double) ---

TEST_F(XMLUtilToStrTest_171, ToStrDouble_Zero_171) {
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_DOUBLE_EQ(0.0, parsed);
}

TEST_F(XMLUtilToStrTest_171, ToStrDouble_Positive_171) {
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(3.141592653589793, parsed, 1e-10);
}

TEST_F(XMLUtilToStrTest_171, ToStrDouble_Negative_171) {
    XMLUtil::ToStr(-100.5, buffer, sizeof(buffer));
    double parsed = std::stod(buffer);
    EXPECT_NEAR(-100.5, parsed, 1e-10);
}

// --- ToStr(int64_t) ---

TEST_F(XMLUtilToStrTest_171, ToStrInt64_Zero_171) {
    XMLUtil::ToStr(static_cast<int64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt64_Positive_171) {
    XMLUtil::ToStr(static_cast<int64_t>(9876543210LL), buffer, sizeof(buffer));
    EXPECT_STREQ("9876543210", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt64_Negative_171) {
    XMLUtil::ToStr(static_cast<int64_t>(-9876543210LL), buffer, sizeof(buffer));
    EXPECT_STREQ("-9876543210", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt64_Max_171) {
    XMLUtil::ToStr(INT64_MAX, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)INT64_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrInt64_Min_171) {
    XMLUtil::ToStr(INT64_MIN, buffer, sizeof(buffer));
    char expected[64];
    snprintf(expected, sizeof(expected), "%lld", (long long)INT64_MIN);
    EXPECT_STREQ(expected, buffer);
}

// --- ToStr(uint64_t) ---

TEST_F(XMLUtilToStrTest_171, ToStrUint64_Zero_171) {
    XMLUtil::ToStr(static_cast<uint64_t>(0), buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrUint64_Positive_171) {
    XMLUtil::ToStr(static_cast<uint64_t>(18446744073709551615ULL), buffer, sizeof(buffer));
    EXPECT_STREQ("18446744073709551615", buffer);
}

TEST_F(XMLUtilToStrTest_171, ToStrUint64_SmallValue_171) {
    XMLUtil::ToStr(static_cast<uint64_t>(42), buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

// ============================================================================
// ToInt / ToUnsigned / ToBool / ToFloat / ToDouble / ToInt64 / ToUnsigned64
// ============================================================================

class XMLUtilFromStrTest_171 : public ::testing::Test {};

// --- ToInt ---

TEST_F(XMLUtilFromStrTest_171, ToInt_ValidPositive_171) {
    int value = 0;
    bool result = XMLUtil::ToInt("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt_ValidNegative_171) {
    int value = 0;
    bool result = XMLUtil::ToInt("-100", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt_Zero_171) {
    int value = -1;
    bool result = XMLUtil::ToInt("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt_InvalidString_171) {
    int value = 0;
    bool result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToInt_NullString_171) {
    int value = 0;
    bool result = XMLUtil::ToInt(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToInt_EmptyString_171) {
    int value = 0;
    bool result = XMLUtil::ToInt("", &value);
    EXPECT_FALSE(result);
}

// --- ToUnsigned ---

TEST_F(XMLUtilFromStrTest_171, ToUnsigned_ValidPositive_171) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(123u, value);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned_Zero_171) {
    unsigned int value = 1;
    bool result = XMLUtil::ToUnsigned("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned_InvalidString_171) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned("xyz", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned_NullString_171) {
    unsigned int value = 0;
    bool result = XMLUtil::ToUnsigned(nullptr, &value);
    EXPECT_FALSE(result);
}

// --- ToBool ---

TEST_F(XMLUtilFromStrTest_171, ToBool_TrueString_171) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_171, ToBool_FalseString_171) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_171, ToBool_One_171) {
    bool value = false;
    bool result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_171, ToBool_ZeroString_171) {
    bool value = true;
    bool result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_171, ToBool_InvalidString_171) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToBool_NullString_171) {
    bool value = false;
    bool result = XMLUtil::ToBool(nullptr, &value);
    EXPECT_FALSE(result);
}

// --- ToFloat ---

TEST_F(XMLUtilFromStrTest_171, ToFloat_ValidPositive_171) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.14f, value, 0.01f);
}

TEST_F(XMLUtilFromStrTest_171, ToFloat_ValidNegative_171) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("-2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(-2.5f, value, 0.01f);
}

TEST_F(XMLUtilFromStrTest_171, ToFloat_Zero_171) {
    float value = 1.0f;
    bool result = XMLUtil::ToFloat("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilFromStrTest_171, ToFloat_InvalidString_171) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToFloat_NullString_171) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat(nullptr, &value);
    EXPECT_FALSE(result);
}

// --- ToDouble ---

TEST_F(XMLUtilFromStrTest_171, ToDouble_ValidPositive_171) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("3.141592653589793", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(3.141592653589793, value, 1e-12);
}

TEST_F(XMLUtilFromStrTest_171, ToDouble_ValidNegative_171) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("-100.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(-100.5, value, 1e-10);
}

TEST_F(XMLUtilFromStrTest_171, ToDouble_Zero_171) {
    double value = 1.0;
    bool result = XMLUtil::ToDouble("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(0.0, value);
}

TEST_F(XMLUtilFromStrTest_171, ToDouble_InvalidString_171) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToDouble_NullString_171) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble(nullptr, &value);
    EXPECT_FALSE(result);
}

// --- ToInt64 ---

TEST_F(XMLUtilFromStrTest_171, ToInt64_ValidPositive_171) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9876543210", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(9876543210LL, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt64_ValidNegative_171) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("-9876543210", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-9876543210LL, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt64_Zero_171) {
    int64_t value = 1;
    bool result = XMLUtil::ToInt64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilFromStrTest_171, ToInt64_InvalidString_171) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToInt64_NullString_171) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64(nullptr, &value);
    EXPECT_FALSE(result);
}

// --- ToUnsigned64 ---

TEST_F(XMLUtilFromStrTest_171, ToUnsigned64_ValidPositive_171) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned64_Zero_171) {
    uint64_t value = 1;
    bool result = XMLUtil::ToUnsigned64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned64_SmallValue_171) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42u, value);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned64_InvalidString_171) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilFromStrTest_171, ToUnsigned64_NullString_171) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================================
// ReadBOM tests
// ============================================================================

class XMLUtilBOMTest_171 : public ::testing::Test {};

TEST_F(XMLUtilBOMTest_171, ReadBOM_WithBOM_171) {
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char withBom[] = "\xEF\xBB\xBF<root/>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(withBom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(withBom + 3, result);
}

TEST_F(XMLUtilBOMTest_171, ReadBOM_WithoutBOM_171) {
    const char noBom[] = "<root/>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(noBom, result);
}

TEST_F(XMLUtilBOMTest_171, ReadBOM_EmptyString_171) {
    const char empty[] = "";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(empty, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(empty, result);
}

// ============================================================================
// IsWhiteSpace tests
// ============================================================================

class XMLUtilWhiteSpaceTest_171 : public ::testing::Test {};

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_Space_171) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_Tab_171) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_Newline_171) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_CarriageReturn_171) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_Letter_171) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_Digit_171) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilWhiteSpaceTest_171, IsWhiteSpace_NullChar_171) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================================
// SkipWhiteSpace tests
// ============================================================================

class XMLUtilSkipWhiteSpaceTest_171 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_LeadingSpaces_171) {
    const char* str = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_NoWhiteSpace_171) {
    const char* str = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ(str, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_MixedWhiteSpace_171) {
    const char* str = " \t\n\rhello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_AllWhiteSpace_171) {
    const char* str = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_STREQ("", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_WithLineCounter_171) {
    int lineNum = 1;
    const char* str = "\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(3, lineNum);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_171, SkipWhiteSpace_NullPointer_171) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(nullptr, result);
}

// ============================================================================
// StringEqual tests
// ============================================================================

class XMLUtilStringEqualTest_171 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_171, StringEqual_SameStrings_171) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_DifferentStrings_171) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_PartialMatch_171) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_PartialNoMatch_171) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world", 5));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_EmptyStrings_171) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_BothNull_171) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_OneNull_171) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_171, StringEqual_ZeroLength_171) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

// ============================================================================
// IsNameStartChar / IsNameChar tests
// ============================================================================

class XMLUtilNameCharTest_171 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_171, IsNameStartChar_Letter_171) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameStartChar_Underscore_171) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameStartChar_Colon_171) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameStartChar_Digit_171) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameStartChar_Space_171) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
}

TEST_F(XMLUtilNameCharTest_171, IsNameChar_Letter_171) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameChar_Digit_171) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameChar_Hyphen_171) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameChar_Dot_171) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_171, IsNameChar_Space_171) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================================
// IsPrefixHex tests
// ============================================================================

class XMLUtilIsPrefixHexTest_171 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_171, IsPrefixHex_ValidHex_171) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_171, IsPrefixHex_NotHex_171) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST_F(XMLUtilIsPrefixHexTest_171, IsPrefixHex_JustZero_171) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================================
// IsUTF8Continuation tests
// ============================================================================

class XMLUtilUTF8Test_171 : public ::testing::Test {};

TEST_F(XMLUtilUTF8Test_171, IsUTF8Continuation_ContinuationByte_171) {
    // Continuation bytes are 10xxxxxx (0x80 - 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST_F(XMLUtilUTF8Test_171, IsUTF8Continuation_ASCIIByte_171) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('\0'));
}

// ============================================================================
// ConvertUTF32ToUTF8 tests
// ============================================================================

class XMLUtilConvertUTF32Test_171 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_171, ConvertUTF32_ASCII_171) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32Test_171, ConvertUTF32_TwoByteChar_171) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // Latin small letter e with acute: É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32Test_171, ConvertUTF32_ThreeByteChar_171) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // Euro sign
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32Test_171, ConvertUTF32_FourByteChar_171) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // Grinning face emoji
    EXPECT_EQ(4, length);
}

// ============================================================================
// SetBoolSerialization tests
// ============================================================================

class XMLUtilBoolSerializationTest_171 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilBoolSerializationTest_171, CustomBoolSerialization_171) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
}

TEST_F(XMLUtilBoolSerializationTest_171, ResetBoolSerialization_171) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================================
// GetCharacterRef tests
// ============================================================================

class XMLUtilGetCharacterRefTest_171 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_171, GetCharacterRef_DecimalRef_171) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_171, GetCharacterRef_HexRef_171) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

// ============================================================================
// Roundtrip tests (ToStr -> ToXxx)
// ============================================================================

class XMLUtilRoundtripTest_171 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilRoundtripTest_171, IntRoundtrip_171) {
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(12345, value);
}

TEST_F(XMLUtilRoundtripTest_171, UnsignedRoundtrip_171) {
    XMLUtil::ToStr(4000000000u, buffer, sizeof(buffer));
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &value));
    EXPECT_EQ(4000000000u, value);
}

TEST_F(XMLUtilRoundtripTest_171, BoolTrueRoundtrip_171) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilRoundtripTest_171, BoolFalseRoundtrip_171) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilRoundtripTest_171, DoubleRoundtrip_171) {
    double original = 3.141592653589793;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(original, value, 1e-12);
}

TEST_F(XMLUtilRoundtripTest_171, Int64Roundtrip_171) {
    int64_t original = 9876543210LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_171, Uint64Roundtrip_171) {
    uint64_t original = 18446744073709551615ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}
