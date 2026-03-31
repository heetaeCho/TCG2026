#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <cstring>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// =============================================================================
// ToInt Tests
// =============================================================================

class XMLUtilToIntTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToIntTest_172, PositiveDecimalInteger_172) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilToIntTest_172, NegativeDecimalInteger_172) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilToIntTest_172, ZeroValue_172) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToIntTest_172, HexValueWithPrefix0x_172) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("0xff", &value));
    EXPECT_EQ(255, value);
}

TEST_F(XMLUtilToIntTest_172, HexValueUpperCase_172) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("0xFF", &value));
    EXPECT_EQ(255, value);
}

TEST_F(XMLUtilToIntTest_172, HexValueWith0X_172) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("0X1A", &value));
    EXPECT_EQ(26, value);
}

TEST_F(XMLUtilToIntTest_172, NullStringReturnsFalse_172) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilToIntTest_172, EmptyStringReturnsFalse_172) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilToIntTest_172, NonNumericStringReturnsFalse_172) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilToIntTest_172, MaxIntValue_172) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MAX);
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buf, &value));
    EXPECT_EQ(INT_MAX, value);
}

TEST_F(XMLUtilToIntTest_172, MinIntValue_172) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", INT_MIN);
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buf, &value));
    EXPECT_EQ(INT_MIN, value);
}

TEST_F(XMLUtilToIntTest_172, HexZero_172) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0x0", &value));
    EXPECT_EQ(0, value);
}

// =============================================================================
// ToUnsigned Tests
// =============================================================================

class XMLUtilToUnsignedTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToUnsignedTest_172, PositiveValue_172) {
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(123u, value);
}

TEST_F(XMLUtilToUnsignedTest_172, ZeroValue_172) {
    unsigned value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsignedTest_172, NullStringReturnsFalse_172) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST_F(XMLUtilToUnsignedTest_172, EmptyStringReturnsFalse_172) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

TEST_F(XMLUtilToUnsignedTest_172, NonNumericReturnsFalse_172) {
    unsigned value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilToUnsignedTest_172, MaxUnsignedValue_172) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%u", UINT_MAX);
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buf, &value));
    EXPECT_EQ(UINT_MAX, value);
}

// =============================================================================
// ToBool Tests
// =============================================================================

class XMLUtilToBoolTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToBoolTest_172, TrueString_172) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_172, FalseString_172) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_172, NumericOne_172) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_172, NumericZero_172) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_172, InvalidStringReturnsFalse_172) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilToBoolTest_172, NullStringReturnsFalse_172) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST_F(XMLUtilToBoolTest_172, EmptyStringReturnsFalse_172) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// =============================================================================
// ToFloat Tests
// =============================================================================

class XMLUtilToFloatTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToFloatTest_172, PositiveFloat_172) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_172, NegativeFloat_172) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_FLOAT_EQ(-2.5f, value);
}

TEST_F(XMLUtilToFloatTest_172, ZeroFloat_172) {
    float value = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0.0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_172, IntegerAsFloat_172) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("42", &value));
    EXPECT_FLOAT_EQ(42.0f, value);
}

TEST_F(XMLUtilToFloatTest_172, NullStringReturnsFalse_172) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST_F(XMLUtilToFloatTest_172, EmptyStringReturnsFalse_172) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

TEST_F(XMLUtilToFloatTest_172, NonNumericReturnsFalse_172) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("not_a_number", &value));
}

// =============================================================================
// ToDouble Tests
// =============================================================================

class XMLUtilToDoubleTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToDoubleTest_172, PositiveDouble_172) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("3.14159265358979", &value));
    EXPECT_DOUBLE_EQ(3.14159265358979, value);
}

TEST_F(XMLUtilToDoubleTest_172, NegativeDouble_172) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("-1.23456789", &value));
    EXPECT_DOUBLE_EQ(-1.23456789, value);
}

TEST_F(XMLUtilToDoubleTest_172, ZeroDouble_172) {
    double value = 1.0;
    EXPECT_TRUE(XMLUtil::ToDouble("0.0", &value));
    EXPECT_DOUBLE_EQ(0.0, value);
}

TEST_F(XMLUtilToDoubleTest_172, NullStringReturnsFalse_172) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST_F(XMLUtilToDoubleTest_172, EmptyStringReturnsFalse_172) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

// =============================================================================
// ToInt64 Tests
// =============================================================================

class XMLUtilToInt64Test_172 : public ::testing::Test {};

TEST_F(XMLUtilToInt64Test_172, PositiveValue_172) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("1234567890123", &value));
    EXPECT_EQ(1234567890123LL, value);
}

TEST_F(XMLUtilToInt64Test_172, NegativeValue_172) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-9876543210", &value));
    EXPECT_EQ(-9876543210LL, value);
}

TEST_F(XMLUtilToInt64Test_172, ZeroValue_172) {
    int64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0LL, value);
}

TEST_F(XMLUtilToInt64Test_172, NullStringReturnsFalse_172) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilToInt64Test_172, EmptyStringReturnsFalse_172) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

TEST_F(XMLUtilToInt64Test_172, NonNumericReturnsFalse_172) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

// =============================================================================
// ToUnsigned64 Tests
// =============================================================================

class XMLUtilToUnsigned64Test_172 : public ::testing::Test {};

TEST_F(XMLUtilToUnsigned64Test_172, PositiveValue_172) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilToUnsigned64Test_172, ZeroValue_172) {
    uint64_t value = 1;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_172, NullStringReturnsFalse_172) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

TEST_F(XMLUtilToUnsigned64Test_172, EmptyStringReturnsFalse_172) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

// =============================================================================
// ToStr Tests
// =============================================================================

class XMLUtilToStrTest_172 : public ::testing::Test {};

TEST_F(XMLUtilToStrTest_172, IntToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_172, NegativeIntToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(-7, buffer, sizeof(buffer));
    EXPECT_STREQ("-7", buffer);
}

TEST_F(XMLUtilToStrTest_172, ZeroIntToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_172, UnsignedToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(123u, buffer, sizeof(buffer));
    EXPECT_STREQ("123", buffer);
}

TEST_F(XMLUtilToStrTest_172, BoolTrueToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_172, BoolFalseToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_172, FloatToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Just verify it contains something parseable back
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_FLOAT_EQ(1.5f, parsed);
}

TEST_F(XMLUtilToStrTest_172, DoubleToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(2.718281828, buffer, sizeof(buffer));
    double parsed = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_NEAR(2.718281828, parsed, 1e-6);
}

TEST_F(XMLUtilToStrTest_172, Int64ToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(int64_t(9876543210LL), buffer, sizeof(buffer));
    int64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(9876543210LL, parsed);
}

TEST_F(XMLUtilToStrTest_172, Uint64ToStr_172) {
    char buffer[64] = {};
    XMLUtil::ToStr(uint64_t(12345678901234ULL), buffer, sizeof(buffer));
    uint64_t parsed = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(12345678901234ULL, parsed);
}

// =============================================================================
// IsPrefixHex Tests
// =============================================================================

class XMLUtilIsPrefixHexTest_172 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_172, ValidHexPrefix_0x_172) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1"));
}

TEST_F(XMLUtilIsPrefixHexTest_172, ValidHexPrefix_0X_172) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1"));
}

TEST_F(XMLUtilIsPrefixHexTest_172, NotHex_DecimalString_172) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_172, NotHex_EmptyString_172) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

TEST_F(XMLUtilIsPrefixHexTest_172, JustZero_172) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// =============================================================================
// IsWhiteSpace Tests
// =============================================================================

class XMLUtilIsWhiteSpaceTest_172 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_172, SpaceIsWhiteSpace_172) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, TabIsWhiteSpace_172) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, NewlineIsWhiteSpace_172) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, CarriageReturnIsWhiteSpace_172) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, LetterIsNotWhiteSpace_172) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, DigitIsNotWhiteSpace_172) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('5'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_172, NullIsNotWhiteSpace_172) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// =============================================================================
// StringEqual Tests
// =============================================================================

class XMLUtilStringEqualTest_172 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_172, EqualStrings_172) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_172, DifferentStrings_172) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_172, PartialCompare_172) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "helloworld", 5));
}

TEST_F(XMLUtilStringEqualTest_172, BothNull_172) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_172, OneNull_172) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_172, EmptyStringsAreEqual_172) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_172, EmptyAndNonEmpty_172) {
    EXPECT_FALSE(XMLUtil::StringEqual("", "a"));
}

// =============================================================================
// IsNameStartChar and IsNameChar Tests
// =============================================================================

class XMLUtilNameCharTest_172 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_172, LetterIsNameStartChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('A'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('z'));
}

TEST_F(XMLUtilNameCharTest_172, ColonIsNameStartChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_172, UnderscoreIsNameStartChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_172, DigitIsNotNameStartChar_172) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_172, DigitIsNameChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_172, DotIsNameChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_172, HyphenIsNameChar_172) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_172, SpaceIsNotNameChar_172) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// =============================================================================
// SkipWhiteSpace Tests
// =============================================================================

class XMLUtilSkipWhiteSpaceTest_172 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_172, SkipsLeadingSpaces_172) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_172, SkipsTabsAndNewlines_172) {
    const char* input = "\t\n\r world";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("world", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_172, NoWhiteSpaceToSkip_172) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_172, AllWhiteSpace_172) {
    const char* input = "   \t\n";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_172, NullInput_172) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_172, CountsNewlines_172) {
    const char* input = "\n\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(4, lineNum);
}

// =============================================================================
// ReadBOM Tests
// =============================================================================

class XMLUtilReadBOMTest_172 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_172, NoBOM_172) {
    const char* input = "<?xml version=\"1.0\"?>";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilReadBOMTest_172, WithUTF8BOM_172) {
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    const char bom[] = {(char)0xEF, (char)0xBB, (char)0xBF, '<', '?', 'x', 'm', 'l', '\0'};
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(bom + 3, result);
}

TEST_F(XMLUtilReadBOMTest_172, NullInput_172) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(nullptr, result);
}

// =============================================================================
// SetBoolSerialization Tests
// =============================================================================

class XMLUtilSetBoolSerializationTest_172 : public ::testing::Test {};

TEST_F(XMLUtilSetBoolSerializationTest_172, CustomBoolSerialization_172) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buffer[64] = {};
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);

    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// =============================================================================
// ConvertUTF32ToUTF8 Tests
// =============================================================================

class XMLUtilConvertUTF32ToUTF8Test_172 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_172, ASCIICharacter_172) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_172, TwoByteCharacter_172) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É (U+00C9)
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_172, ThreeByteCharacter_172) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € (U+20AC)
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_172, FourByteCharacter_172) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀 (U+1F600)
    EXPECT_EQ(4, length);
}

// =============================================================================
// IsUTF8Continuation Tests
// =============================================================================

class XMLUtilIsUTF8ContinuationTest_172 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_172, ContinuationByte_172) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0x80));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation((char)0xBF));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_172, NonContinuationByte_172) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0x41)); // 'A'
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation((char)0xC0));
}

// =============================================================================
// Roundtrip Tests: ToStr -> ToXxx
// =============================================================================

class XMLUtilRoundtripTest_172 : public ::testing::Test {};

TEST_F(XMLUtilRoundtripTest_172, IntRoundtrip_172) {
    char buffer[64];
    XMLUtil::ToStr(-12345, buffer, sizeof(buffer));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(-12345, value);
}

TEST_F(XMLUtilRoundtripTest_172, UnsignedRoundtrip_172) {
    char buffer[64];
    XMLUtil::ToStr(98765u, buffer, sizeof(buffer));
    unsigned value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &value));
    EXPECT_EQ(98765u, value);
}

TEST_F(XMLUtilRoundtripTest_172, BoolTrueRoundtrip_172) {
    char buffer[64];
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilRoundtripTest_172, BoolFalseRoundtrip_172) {
    char buffer[64];
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilRoundtripTest_172, FloatRoundtrip_172) {
    char buffer[64];
    XMLUtil::ToStr(1.23f, buffer, sizeof(buffer));
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &value));
    EXPECT_FLOAT_EQ(1.23f, value);
}

TEST_F(XMLUtilRoundtripTest_172, DoubleRoundtrip_172) {
    char buffer[256];
    XMLUtil::ToStr(1.23456789012345, buffer, sizeof(buffer));
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_DOUBLE_EQ(1.23456789012345, value);
}

TEST_F(XMLUtilRoundtripTest_172, Int64Roundtrip_172) {
    char buffer[64];
    int64_t original = 9223372036854775807LL; // INT64_MAX
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_172, Uint64Roundtrip_172) {
    char buffer[64];
    uint64_t original = 18446744073709551615ULL; // UINT64_MAX
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}
