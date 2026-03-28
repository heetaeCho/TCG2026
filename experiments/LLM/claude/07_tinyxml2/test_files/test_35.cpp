#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== SkipWhiteSpace Tests ====================

class XMLUtilSkipWhiteSpaceTest_35 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_35, SkipSpaces_35) {
    const char* input = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 1);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, SkipTabs_35) {
    const char* input = "\t\thello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, SkipNewlines_35) {
    const char* input = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
    EXPECT_EQ(lineNum, 3);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, SkipCarriageReturn_35) {
    const char* input = "\r\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, NoWhiteSpace_35) {
    const char* input = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(result, input);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, NullPointer_35) {
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, &lineNum);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, EmptyString_35) {
    const char* input = "";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, AllWhiteSpace_35) {
    const char* input = "   \t\n  ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, MutableOverload_35) {
    char input[] = "  hello";
    int lineNum = 1;
    char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, NullLineNumPtr_35) {
    const char* input = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(*result, 'h');
}

// ==================== IsWhiteSpace Tests ====================

class XMLUtilIsWhiteSpaceTest_35 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_35, Space_35) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_35, Tab_35) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_35, Newline_35) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_35, CarriageReturn_35) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_35, NonWhiteSpace_35) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('!'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_35, NullChar_35) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ==================== IsNameStartChar Tests ====================

class XMLUtilIsNameStartCharTest_35 : public ::testing::Test {};

TEST_F(XMLUtilIsNameStartCharTest_35, Alpha_35) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilIsNameStartCharTest_35, Underscore_35) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilIsNameStartCharTest_35, Colon_35) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilIsNameStartCharTest_35, DigitNotStart_35) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilIsNameStartCharTest_35, DashNotStart_35) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLUtilIsNameStartCharTest_35, DotNotStart_35) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

// ==================== IsNameChar Tests ====================

class XMLUtilIsNameCharTest_35 : public ::testing::Test {};

TEST_F(XMLUtilIsNameCharTest_35, Alpha_35) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilIsNameCharTest_35, Digit_35) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilIsNameCharTest_35, Dash_35) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilIsNameCharTest_35, Dot_35) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilIsNameCharTest_35, Underscore_35) {
    EXPECT_TRUE(XMLUtil::IsNameChar('_'));
}

TEST_F(XMLUtilIsNameCharTest_35, Space_35) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

TEST_F(XMLUtilIsNameCharTest_35, SpecialChars_35) {
    EXPECT_FALSE(XMLUtil::IsNameChar('!'));
    EXPECT_FALSE(XMLUtil::IsNameChar('@'));
    EXPECT_FALSE(XMLUtil::IsNameChar('#'));
}

// ==================== IsPrefixHex Tests ====================

class XMLUtilIsPrefixHexTest_35 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_35, ValidHexPrefix_35) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_35, NotHexPrefix_35) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1234"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("hello"));
}

TEST_F(XMLUtilIsPrefixHexTest_35, JustZero_35) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST_F(XMLUtilIsPrefixHexTest_35, ZeroXOnly_35) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x"));
}

// ==================== StringEqual Tests ====================

class XMLUtilStringEqualTest_35 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_35, EqualStrings_35) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_35, DifferentStrings_35) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_35, PartialMatch_35) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST_F(XMLUtilStringEqualTest_35, BothNull_35) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_35, OneNull_35) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_35, EmptyStrings_35) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_35, DifferentLengths_35) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hell"));
}

TEST_F(XMLUtilStringEqualTest_35, NCharZero_35) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "world", 0));
}

// ==================== IsUTF8Continuation Tests ====================

class XMLUtilIsUTF8ContinuationTest_35 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_35, ContinuationByte_35) {
    // UTF-8 continuation bytes are 0x80-0xBF (10xxxxxx)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_35, NonContinuationByte_35) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('a'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x00));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0xC0));
}

// ==================== ReadBOM Tests ====================

class XMLUtilReadBOMTest_35 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_35, NoBOM_35) {
    const char* input = "hello";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_35, WithBOM_35) {
    const char bom[] = { (char)0xEF, (char)0xBB, (char)0xBF, 'h', 'e', 'l', 'l', 'o', '\0' };
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(*result, 'h');
}

TEST_F(XMLUtilReadBOMTest_35, NullInput_35) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(result, nullptr);
}

// ==================== ToStr / ToXxx Conversion Tests ====================

class XMLUtilConversionTest_35 : public ::testing::Test {};

TEST_F(XMLUtilConversionTest_35, ToStrInt_35) {
    char buffer[64];
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilConversionTest_35, ToStrIntNegative_35) {
    char buffer[64];
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-100");
}

TEST_F(XMLUtilConversionTest_35, ToStrIntZero_35) {
    char buffer[64];
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilConversionTest_35, ToStrUnsigned_35) {
    char buffer[64];
    XMLUtil::ToStr((unsigned)123, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "123");
}

TEST_F(XMLUtilConversionTest_35, ToStrBoolTrue_35) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilConversionTest_35, ToStrBoolFalse_35) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST_F(XMLUtilConversionTest_35, ToStrFloat_35) {
    char buffer[64];
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Just check it's parseable back
    float val = 0;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &val));
    EXPECT_FLOAT_EQ(val, 1.5f);
}

TEST_F(XMLUtilConversionTest_35, ToStrDouble_35) {
    char buffer[64];
    XMLUtil::ToStr(3.14159, buffer, sizeof(buffer));
    double val = 0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &val));
    EXPECT_DOUBLE_EQ(val, 3.14159);
}

TEST_F(XMLUtilConversionTest_35, ToStrInt64_35) {
    char buffer[64];
    int64_t big = 9223372036854775807LL;
    XMLUtil::ToStr(big, buffer, sizeof(buffer));
    int64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &val));
    EXPECT_EQ(val, big);
}

TEST_F(XMLUtilConversionTest_35, ToStrUint64_35) {
    char buffer[64];
    uint64_t big = 18446744073709551615ULL;
    XMLUtil::ToStr(big, buffer, sizeof(buffer));
    uint64_t val = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &val));
    EXPECT_EQ(val, big);
}

// ==================== ToInt Tests ====================

TEST_F(XMLUtilConversionTest_35, ToIntValid_35) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilConversionTest_35, ToIntNegative_35) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-42", &value));
    EXPECT_EQ(value, -42);
}

TEST_F(XMLUtilConversionTest_35, ToIntInvalid_35) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToIntNull_35) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_35, ToIntEmpty_35) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

// ==================== ToUnsigned Tests ====================

TEST_F(XMLUtilConversionTest_35, ToUnsignedValid_35) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("42", &value));
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLUtilConversionTest_35, ToUnsignedInvalid_35) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToUnsignedNull_35) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

// ==================== ToBool Tests ====================

TEST_F(XMLUtilConversionTest_35, ToBoolTrue_35) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_35, ToBoolFalse_35) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_35, ToBoolOne_35) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_35, ToBoolZero_35) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_35, ToBoolInvalid_35) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilConversionTest_35, ToBoolNull_35) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

// ==================== ToFloat Tests ====================

TEST_F(XMLUtilConversionTest_35, ToFloatValid_35) {
    float value = 0;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST_F(XMLUtilConversionTest_35, ToFloatInvalid_35) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToFloatNull_35) {
    float value = 0;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ==================== ToDouble Tests ====================

TEST_F(XMLUtilConversionTest_35, ToDoubleValid_35) {
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159265358979", &value));
    EXPECT_NEAR(value, 3.14159265358979, 1e-10);
}

TEST_F(XMLUtilConversionTest_35, ToDoubleInvalid_35) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToDoubleNull_35) {
    double value = 0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

// ==================== ToInt64 Tests ====================

TEST_F(XMLUtilConversionTest_35, ToInt64Valid_35) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, 9223372036854775807LL);
}

TEST_F(XMLUtilConversionTest_35, ToInt64Negative_35) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-1000000000000", &value));
    EXPECT_EQ(value, -1000000000000LL);
}

TEST_F(XMLUtilConversionTest_35, ToInt64Invalid_35) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToInt64Null_35) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

// ==================== ToUnsigned64 Tests ====================

TEST_F(XMLUtilConversionTest_35, ToUnsigned64Valid_35) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, 18446744073709551615ULL);
}

TEST_F(XMLUtilConversionTest_35, ToUnsigned64Invalid_35) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilConversionTest_35, ToUnsigned64Null_35) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

class XMLUtilUTF32Test_35 : public ::testing::Test {};

TEST_F(XMLUtilUTF32Test_35, ASCIICharacter_35) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilUTF32Test_35, TwoByteCharacter_35) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilUTF32Test_35, ThreeByteCharacter_35) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (Euro sign)
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilUTF32Test_35, FourByteCharacter_35) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // Emoji
    EXPECT_EQ(length, 4);
}

TEST_F(XMLUtilUTF32Test_35, NullCharacter_35) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0, output, &length);
    // 0 is a valid code point, should produce length 0 or handle gracefully
}

// ==================== GetCharacterRef Tests ====================

class XMLUtilGetCharacterRefTest_35 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_35, DecimalRef_35) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_35, HexRef_35) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_35, InvalidRef_35) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// ==================== SetBoolSerialization Tests ====================

class XMLUtilSetBoolSerializationTest_35 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_35, CustomBoolTrue_35) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
}

TEST_F(XMLUtilSetBoolSerializationTest_35, CustomBoolFalse_35) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilSetBoolSerializationTest_35, ResetToDefaults_35) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ==================== Mixed whitespace and newline counting ====================

class XMLUtilWhitespaceNewlineTest_35 : public ::testing::Test {};

TEST_F(XMLUtilWhitespaceNewlineTest_35, MixedWhitespaceNewlines_35) {
    const char* input = " \n \n \t text";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, 't');
    EXPECT_EQ(lineNum, 3);
}

TEST_F(XMLUtilWhitespaceNewlineTest_35, OnlyNewlines_35) {
    const char* input = "\n\n\n";
    int lineNum = 0;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_EQ(*result, '\0');
    EXPECT_EQ(lineNum, 3);
}

// ==================== Boundary / Edge case for ToInt ====================

TEST_F(XMLUtilConversionTest_35, ToIntMaxValue_35) {
    int value = 0;
    char buffer[64];
    XMLUtil::ToStr(INT_MAX, buffer, sizeof(buffer));
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MAX);
}

TEST_F(XMLUtilConversionTest_35, ToIntMinValue_35) {
    int value = 0;
    char buffer[64];
    XMLUtil::ToStr(INT_MIN, buffer, sizeof(buffer));
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(value, INT_MIN);
}

// ==================== Roundtrip tests ====================

TEST_F(XMLUtilConversionTest_35, RoundtripUnsigned_35) {
    char buffer[64];
    unsigned int original = 4294967295u;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    unsigned int parsed = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &parsed));
    EXPECT_EQ(parsed, original);
}

TEST_F(XMLUtilConversionTest_35, ToFloatZero_35) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0", &value));
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLUtilConversionTest_35, ToDoubleZero_35) {
    double value = 1.0;
    EXPECT_TRUE(XMLUtil::ToDouble("0", &value));
    EXPECT_DOUBLE_EQ(value, 0.0);
}
