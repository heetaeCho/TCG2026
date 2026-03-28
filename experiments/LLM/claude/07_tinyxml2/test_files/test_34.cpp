#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================================
// SkipWhiteSpace Tests
// ============================================================================

class XMLUtilSkipWhiteSpaceTest_34 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_34, SkipsSpaces_34) {
    const char* input = "   hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 0);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, SkipsTabs_34) {
    const char* input = "\t\thello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 0);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, SkipsNewlinesAndIncrementsLineNum_34) {
    const char* input = "\n\nhello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 2);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, SkipsMixedWhiteSpace_34) {
    const char* input = " \t\n \n\t hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 2);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, NoWhiteSpaceAtStart_34) {
    const char* input = "hello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(result, input);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 0);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, AllWhiteSpaceEndsAtNull_34) {
    const char* input = "   ";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, NullLineNumPtr_34) {
    const char* input = "\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, EmptyString_34) {
    const char* input = "";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
    EXPECT_EQ(lineNum, 0);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, CarriageReturn_34) {
    const char* input = "\r\nhello";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 1);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_34, MutableOverload_34) {
    char input[] = "   hello";
    int lineNum = 0;
    char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 0);
}

// ============================================================================
// IsWhiteSpace Tests
// ============================================================================

class XMLUtilIsWhiteSpaceTest_34 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_34, SpaceIsWhiteSpace_34) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, TabIsWhiteSpace_34) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, NewlineIsWhiteSpace_34) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, CarriageReturnIsWhiteSpace_34) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, AlphaNotWhiteSpace_34) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, DigitNotWhiteSpace_34) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_34, NullCharNotWhiteSpace_34) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================================
// IsNameStartChar Tests
// ============================================================================

class XMLUtilIsNameStartCharTest_34 : public ::testing::Test {};

TEST_F(XMLUtilIsNameStartCharTest_34, LetterIsNameStartChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilIsNameStartCharTest_34, UnderscoreIsNameStartChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilIsNameStartCharTest_34, ColonIsNameStartChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilIsNameStartCharTest_34, DigitIsNotNameStartChar_34) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilIsNameStartCharTest_34, HyphenIsNotNameStartChar_34) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLUtilIsNameStartCharTest_34, DotIsNotNameStartChar_34) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

// ============================================================================
// IsNameChar Tests
// ============================================================================

class XMLUtilIsNameCharTest_34 : public ::testing::Test {};

TEST_F(XMLUtilIsNameCharTest_34, LetterIsNameChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilIsNameCharTest_34, DigitIsNameChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilIsNameCharTest_34, HyphenIsNameChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilIsNameCharTest_34, DotIsNameChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilIsNameCharTest_34, UnderscoreIsNameChar_34) {
    EXPECT_TRUE(XMLUtil::IsNameChar('_'));
}

TEST_F(XMLUtilIsNameCharTest_34, SpaceIsNotNameChar_34) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================================
// StringEqual Tests
// ============================================================================

class XMLUtilStringEqualTest_34 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_34, EqualStrings_34) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_34, DifferentStrings_34) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_34, EmptyStringsEqual_34) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_34, NullBothEqual_34) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_34, NullVsNonNullNotEqual_34) {
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
}

TEST_F(XMLUtilStringEqualTest_34, PartialComparisonWithNChar_34) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}

TEST_F(XMLUtilStringEqualTest_34, NCharZero_34) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "world", 0));
}

TEST_F(XMLUtilStringEqualTest_34, PrefixMatch_34) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

// ============================================================================
// IsPrefixHex Tests
// ============================================================================

class XMLUtilIsPrefixHexTest_34 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_34, ValidHexPrefix_34) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_34, NotHexPrefix_34) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1A"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0a"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST_F(XMLUtilIsPrefixHexTest_34, JustZero_34) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================================
// IsUTF8Continuation Tests
// ============================================================================

class XMLUtilIsUTF8ContinuationTest_34 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_34, ContinuationByte_34) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_34, NonContinuationByte_34) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('a'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xC0)));
}

// ============================================================================
// ToStr Tests
// ============================================================================

class XMLUtilToStrTest_34 : public ::testing::Test {};

TEST_F(XMLUtilToStrTest_34, IntToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_34, NegativeIntToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-100");
}

TEST_F(XMLUtilToStrTest_34, ZeroIntToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_34, UnsignedIntToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_34, BoolTrueToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilToStrTest_34, BoolFalseToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST_F(XMLUtilToStrTest_34, FloatToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(3.14f, buffer, sizeof(buffer));
    // Just verify it's not empty and starts with a digit
    EXPECT_GT(strlen(buffer), 0u);
}

TEST_F(XMLUtilToStrTest_34, DoubleToStr_34) {
    char buffer[64];
    XMLUtil::ToStr(3.14159, buffer, sizeof(buffer));
    EXPECT_GT(strlen(buffer), 0u);
}

TEST_F(XMLUtilToStrTest_34, Int64ToStr_34) {
    char buffer[64];
    int64_t val = 1234567890123LL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "1234567890123");
}

TEST_F(XMLUtilToStrTest_34, Uint64ToStr_34) {
    char buffer[64];
    uint64_t val = 18446744073709551615ULL;
    XMLUtil::ToStr(val, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "18446744073709551615");
}

// ============================================================================
// ToInt / ToUnsigned / ToBool / ToFloat / ToDouble / ToInt64 / ToUnsigned64
// ============================================================================

class XMLUtilFromStrTest_34 : public ::testing::Test {};

TEST_F(XMLUtilFromStrTest_34, ToIntValid_34) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilFromStrTest_34, ToIntNegative_34) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(value, -100);
}

TEST_F(XMLUtilFromStrTest_34, ToIntInvalid_34) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToIntNull_34) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsignedValid_34) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &value));
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLUtilFromStrTest_34, ToUnsignedInvalid_34) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsignedNull_34) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToBoolTrue_34) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_34, ToBoolFalse_34) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_34, ToBoolOne_34) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilFromStrTest_34, ToBoolZero_34) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilFromStrTest_34, ToBoolInvalid_34) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToBoolNull_34) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToFloatValid_34) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.01f);
}

TEST_F(XMLUtilFromStrTest_34, ToFloatInvalid_34) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToFloatNull_34) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToDoubleValid_34) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159", &value));
    EXPECT_NEAR(value, 3.14159, 0.00001);
}

TEST_F(XMLUtilFromStrTest_34, ToDoubleInvalid_34) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToDoubleNull_34) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToInt64Valid_34) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(value, 1234567890123LL);
}

TEST_F(XMLUtilFromStrTest_34, ToInt64Invalid_34) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToInt64Null_34) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsigned64Valid_34) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST_F(XMLUtilFromStrTest_34, ToUnsigned64Invalid_34) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsigned64Null_34) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================================
// ReadBOM Tests
// ============================================================================

class XMLUtilReadBOMTest_34 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_34, NoBOM_34) {
    const char* input = "hello";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_34, WithBOM_34) {
    const char input[] = "\xEF\xBB\xBFhello";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilReadBOMTest_34, EmptyStringNoBOM_34) {
    const char* input = "";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
}

// ============================================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================================

class XMLUtilConvertUTF32Test_34 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32Test_34, ASCIICharacter_34) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length);  // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32Test_34, TwoByteCharacter_34) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length);  // É
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32Test_34, ThreeByteCharacter_34) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length);  // 中
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32Test_34, FourByteCharacter_34) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length);  // 😀
    EXPECT_EQ(length, 4);
}

// ============================================================================
// SetBoolSerialization Tests
// ============================================================================

class XMLUtilSetBoolSerializationTest_34 : public ::testing::Test {
public:
    ~XMLUtilSetBoolSerializationTest_34() {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_34, CustomBoolSerialization_34) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilSetBoolSerializationTest_34, ResetToDefaults_34) {
    char buffer[64];
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ============================================================================
// GetCharacterRef Tests
// ============================================================================

class XMLUtilGetCharacterRefTest_34 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_34, DecimalCharRef_34) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_34, HexCharRef_34) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_34, NotACharRef_34) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ============================================================================
// Edge case: ToInt with empty string
// ============================================================================

TEST_F(XMLUtilFromStrTest_34, ToIntEmptyString_34) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToDoubleEmptyString_34) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToFloatEmptyString_34) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsignedEmptyString_34) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToBoolEmptyString_34) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToInt64EmptyString_34) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

TEST_F(XMLUtilFromStrTest_34, ToUnsigned64EmptyString_34) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

// ============================================================================
// Hex prefix with ToInt/ToUnsigned
// ============================================================================

TEST_F(XMLUtilFromStrTest_34, ToIntWithHexPrefix_34) {
    int value = 0;
    bool result = XMLUtil::ToInt("0xFF", &value);
    // Implementation may or may not support hex; just ensure it doesn't crash
    // If it returns true, value should be 255
    if (result) {
        EXPECT_EQ(value, 255);
    }
}

// ============================================================================
// ToStr round-trip tests
// ============================================================================

TEST_F(XMLUtilToStrTest_34, IntRoundTrip_34) {
    char buffer[64];
    XMLUtil::ToStr(12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, 12345);
}

TEST_F(XMLUtilToStrTest_34, DoubleRoundTrip_34) {
    char buffer[64];
    XMLUtil::ToStr(2.718281828, buffer, sizeof(buffer));
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_NEAR(value, 2.718281828, 1e-6);
}

TEST_F(XMLUtilToStrTest_34, BoolRoundTripTrue_34) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToStrTest_34, BoolRoundTripFalse_34) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToStrTest_34, Int64RoundTrip_34) {
    char buffer[64];
    int64_t original = -9876543210LL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(value, original);
}

TEST_F(XMLUtilToStrTest_34, Uint64RoundTrip_34) {
    char buffer[64];
    uint64_t original = 9876543210ULL;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(value, original);
}
