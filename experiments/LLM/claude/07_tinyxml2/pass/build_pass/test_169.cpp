#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ===== ToStr Tests =====

class XMLUtilToStrTest_169 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_169, ToStrInt_Positive_169) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt_Negative_169) {
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ("-100", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt_Zero_169) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt_MaxInt_169) {
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%d", INT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt_MinInt_169) {
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%d", INT_MIN);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrUnsigned_Normal_169) {
    XMLUtil::ToStr(123u, buffer, sizeof(buffer));
    EXPECT_STREQ("123", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrUnsigned_Zero_169) {
    XMLUtil::ToStr(0u, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrUnsigned_Max_169) {
    XMLUtil::ToStr(UINT_MAX, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%u", UINT_MAX);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrBool_True_169) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrBool_False_169) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrFloat_Normal_169) {
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_FLOAT_EQ(1.5f, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrFloat_Zero_169) {
    XMLUtil::ToStr(0.0f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrFloat_Negative_169) {
    XMLUtil::ToStr(-3.14f, buffer, sizeof(buffer));
    float parsed = std::strtof(buffer, nullptr);
    EXPECT_FLOAT_EQ(-3.14f, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrDouble_Normal_169) {
    XMLUtil::ToStr(3.141592653589793, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(3.141592653589793, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrDouble_Zero_169) {
    XMLUtil::ToStr(0.0, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(0.0, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrDouble_Negative_169) {
    XMLUtil::ToStr(-2.718281828459045, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(-2.718281828459045, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrDouble_VerySmall_169) {
    XMLUtil::ToStr(1e-300, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(1e-300, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrDouble_VeryLarge_169) {
    XMLUtil::ToStr(1e300, buffer, sizeof(buffer));
    double parsed = std::strtod(buffer, nullptr);
    EXPECT_DOUBLE_EQ(1e300, parsed);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt64_Positive_169) {
    int64_t val = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt64_Negative_169) {
    int64_t val = -9223372036854775807LL - 1; // INT64_MIN
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%lld", (long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrInt64_Zero_169) {
    XMLUtil::ToStr((int64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrUint64_Normal_169) {
    uint64_t val = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    char expected[256];
    snprintf(expected, sizeof(expected), "%llu", (unsigned long long)val);
    EXPECT_STREQ(expected, buffer);
}

TEST_F(XMLUtilToStrTest_169, ToStrUint64_Zero_169) {
    XMLUtil::ToStr((uint64_t)0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

// ===== ToInt/ToUnsigned/ToBool/ToFloat/ToDouble/ToInt64/ToUnsigned64 Tests =====

class XMLUtilParseTest_169 : public ::testing::Test {};

TEST_F(XMLUtilParseTest_169, ToInt_ValidPositive_169) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilParseTest_169, ToInt_ValidNegative_169) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilParseTest_169, ToInt_ValidZero_169) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilParseTest_169, ToInt_InvalidString_169) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilParseTest_169, ToInt_NullString_169) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToInt_EmptyString_169) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilParseTest_169, ToUnsigned_ValidPositive_169) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &value));
    EXPECT_EQ(42u, value);
}

TEST_F(XMLUtilParseTest_169, ToUnsigned_InvalidString_169) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST_F(XMLUtilParseTest_169, ToUnsigned_NullString_169) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToBool_TrueString_169) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_169, ToBool_FalseString_169) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_169, ToBool_One_169) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilParseTest_169, ToBool_Zero_169) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilParseTest_169, ToBool_Invalid_169) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilParseTest_169, ToBool_Null_169) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToFloat_Valid_169) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilParseTest_169, ToFloat_Invalid_169) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilParseTest_169, ToFloat_Null_169) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToDouble_Valid_169) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.141592653589793", &value));
    EXPECT_DOUBLE_EQ(3.141592653589793, value);
}

TEST_F(XMLUtilParseTest_169, ToDouble_Invalid_169) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST_F(XMLUtilParseTest_169, ToDouble_Null_169) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToDouble_NegativeValue_169) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("-2.5", &value));
    EXPECT_DOUBLE_EQ(-2.5, value);
}

TEST_F(XMLUtilParseTest_169, ToInt64_Valid_169) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(INT64_MAX, value);
}

TEST_F(XMLUtilParseTest_169, ToInt64_Negative_169) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-42", &value));
    EXPECT_EQ(-42, value);
}

TEST_F(XMLUtilParseTest_169, ToInt64_Invalid_169) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilParseTest_169, ToInt64_Null_169) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilParseTest_169, ToUnsigned64_Valid_169) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilParseTest_169, ToUnsigned64_Zero_169) {
    uint64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilParseTest_169, ToUnsigned64_Invalid_169) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilParseTest_169, ToUnsigned64_Null_169) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ===== ReadBOM Tests =====

class XMLUtilBOMTest_169 : public ::testing::Test {};

TEST_F(XMLUtilBOMTest_169, ReadBOM_WithBOM_169) {
    const char bom[] = "\xEF\xBB\xBF<xml>";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(bom + 3, result);
}

TEST_F(XMLUtilBOMTest_169, ReadBOM_WithoutBOM_169) {
    const char* noBom = "<xml>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(noBom, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(noBom, result);
}

TEST_F(XMLUtilBOMTest_169, ReadBOM_NullPointer_169) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(nullptr, result);
}

// ===== IsWhiteSpace Tests =====

class XMLUtilWhiteSpaceTest_169 : public ::testing::Test {};

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_Space_169) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_Tab_169) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_Newline_169) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_CarriageReturn_169) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_Letter_169) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_Digit_169) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilWhiteSpaceTest_169, IsWhiteSpace_NullChar_169) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ===== SkipWhiteSpace Tests =====

class XMLUtilSkipWhiteSpaceTest_169 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_LeadingSpaces_169) {
    const char* str = "   hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('h', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_NoSpaces_169) {
    const char* str = "hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ(str, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_AllSpaces_169) {
    const char* str = "   ";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('\0', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_WithNewlines_169) {
    const char* str = "\n\n  hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('h', *result);
    EXPECT_EQ(3, lineNum);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_NullInput_169) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_169, SkipWhiteSpace_MutableVersion_169) {
    char str[] = "  test";
    int lineNum = 0;
    char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('t', *result);
}

// ===== StringEqual Tests =====

class XMLUtilStringEqualTest_169 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_169, StringEqual_SameStrings_169) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_DifferentStrings_169) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_WithNChar_169) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_BothNull_169) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_OneNull_169) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_EmptyStrings_169) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_169, StringEqual_DifferentLengths_169) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hell"));
}

// ===== IsNameStartChar Tests =====

class XMLUtilNameCharTest_169 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_169, IsNameStartChar_Letter_169) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameStartChar_Underscore_169) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameStartChar_Colon_169) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameStartChar_Digit_169) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameStartChar_Space_169) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar(' '));
}

TEST_F(XMLUtilNameCharTest_169, IsNameChar_Letter_169) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameChar_Digit_169) {
    EXPECT_TRUE(XMLUtil::IsNameChar('5'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameChar_Dot_169) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameChar_Hyphen_169) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_169, IsNameChar_Space_169) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ===== IsPrefixHex Tests =====

class XMLUtilPrefixHexTest_169 : public ::testing::Test {};

TEST_F(XMLUtilPrefixHexTest_169, IsPrefixHex_Valid0x_169) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
}

TEST_F(XMLUtilPrefixHexTest_169, IsPrefixHex_Valid0X_169) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilPrefixHexTest_169, IsPrefixHex_NotHex_169) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilPrefixHexTest_169, IsPrefixHex_JustZero_169) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ===== IsUTF8Continuation Tests =====

class XMLUtilUTF8Test_169 : public ::testing::Test {};

TEST_F(XMLUtilUTF8Test_169, IsUTF8Continuation_ContinuationByte_169) {
    // Continuation bytes are 10xxxxxx (0x80 - 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilUTF8Test_169, IsUTF8Continuation_NonContinuationByte_169) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
}

// ===== ConvertUTF32ToUTF8 Tests =====

class XMLUtilConvertUTF32Test_169 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_169, ConvertASCII_169) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32Test_169, ConvertTwoByteChar_169) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32Test_169, ConvertThreeByteChar_169) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length); // 中 (U+4E2D)
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32Test_169, ConvertFourByteChar_169) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(4, length);
}

// ===== GetCharacterRef Tests =====

class XMLUtilGetCharacterRefTest_169 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_169, DecimalCharRef_169) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_169, HexCharRef_169) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

// ===== SetBoolSerialization Tests =====

class XMLUtilBoolSerializationTest_169 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilBoolSerializationTest_169, CustomBoolSerialization_169) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
}

TEST_F(XMLUtilBoolSerializationTest_169, ResetBoolSerialization_169) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ===== Roundtrip Tests =====

class XMLUtilRoundtripTest_169 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilRoundtripTest_169, IntRoundtrip_169) {
    int original = 12345;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_169, DoubleRoundtrip_169) {
    double original = 3.141592653589793;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double parsed = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_DOUBLE_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_169, FloatRoundtrip_169) {
    float original = 2.71828f;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_FLOAT_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_169, BoolRoundtripTrue_169) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool parsed = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_TRUE(parsed);
}

TEST_F(XMLUtilRoundtripTest_169, BoolRoundtripFalse_169) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool parsed = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &parsed));
    EXPECT_FALSE(parsed);
}

TEST_F(XMLUtilRoundtripTest_169, Int64Roundtrip_169) {
    int64_t original = 9223372036854775807LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}

TEST_F(XMLUtilRoundtripTest_169, Uint64Roundtrip_169) {
    uint64_t original = 18446744073709551615ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(original, parsed);
}
