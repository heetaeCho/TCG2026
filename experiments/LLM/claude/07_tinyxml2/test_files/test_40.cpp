#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <cstdint>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_40 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_40, SamePointerReturnsTrue_40) {
    const char* s = "hello";
    EXPECT_TRUE(XMLUtil::StringEqual(s, s));
}

TEST_F(XMLUtilStringEqualTest_40, EqualStringsReturnTrue_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_40, DifferentStringsReturnFalse_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_40, EmptyStringsAreEqual_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_40, EmptyAndNonEmptyNotEqual_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("", "a"));
}

TEST_F(XMLUtilStringEqualTest_40, PartialCompareWithNChar_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "help", 3));
}

TEST_F(XMLUtilStringEqualTest_40, PartialCompareFailsWhenDifferent_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "help", 4));
}

TEST_F(XMLUtilStringEqualTest_40, NCharZeroAlwaysTrue_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
}

TEST_F(XMLUtilStringEqualTest_40, NCharOneComparesFirstChar_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "axyz", 1));
    EXPECT_FALSE(XMLUtil::StringEqual("abc", "xyz", 1));
}

TEST_F(XMLUtilStringEqualTest_40, DefaultNCharComparesFullString_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("complete", "complete"));
    EXPECT_FALSE(XMLUtil::StringEqual("complete", "completes"));
}

TEST_F(XMLUtilStringEqualTest_40, LongerNCharThanStringLength_40) {
    // strncmp with nChar larger than actual string length should still work
    EXPECT_TRUE(XMLUtil::StringEqual("hi", "hi", 100));
    EXPECT_FALSE(XMLUtil::StringEqual("hi", "ho", 100));
}

TEST_F(XMLUtilStringEqualTest_40, PrefixMatchWithDifferentLengths_40) {
    // "hello" and "hello world" match for first 5 chars
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
}

// ============================================================
// ToStr / ToInt / ToUnsigned / ToBool / ToFloat / ToDouble / ToInt64 / ToUnsigned64
// ============================================================

class XMLUtilConversionTest_40 : public ::testing::Test {};

TEST_F(XMLUtilConversionTest_40, ToStrInt_40) {
    char buf[64];
    XMLUtil::ToStr(42, buf, sizeof(buf));
    EXPECT_STREQ("42", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrIntNegative_40) {
    char buf[64];
    XMLUtil::ToStr(-7, buf, sizeof(buf));
    EXPECT_STREQ("-7", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrIntZero_40) {
    char buf[64];
    XMLUtil::ToStr(0, buf, sizeof(buf));
    EXPECT_STREQ("0", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrUnsigned_40) {
    char buf[64];
    XMLUtil::ToStr(123u, buf, sizeof(buf));
    EXPECT_STREQ("123", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrBoolTrue_40) {
    char buf[64];
    XMLUtil::ToStr(true, buf, sizeof(buf));
    EXPECT_STREQ("true", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrBoolFalse_40) {
    char buf[64];
    XMLUtil::ToStr(false, buf, sizeof(buf));
    EXPECT_STREQ("false", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrFloat_40) {
    char buf[64];
    XMLUtil::ToStr(1.5f, buf, sizeof(buf));
    // Should contain "1.5" at minimum
    EXPECT_NE(nullptr, strstr(buf, "1.5"));
}

TEST_F(XMLUtilConversionTest_40, ToStrDouble_40) {
    char buf[64];
    XMLUtil::ToStr(3.14, buf, sizeof(buf));
    EXPECT_NE(nullptr, strstr(buf, "3.14"));
}

TEST_F(XMLUtilConversionTest_40, ToStrInt64_40) {
    char buf[64];
    int64_t val = 9876543210LL;
    XMLUtil::ToStr(val, buf, sizeof(buf));
    EXPECT_STREQ("9876543210", buf);
}

TEST_F(XMLUtilConversionTest_40, ToStrUint64_40) {
    char buf[64];
    uint64_t val = 18446744073709551615ULL;
    XMLUtil::ToStr(val, buf, sizeof(buf));
    EXPECT_STREQ("18446744073709551615", buf);
}

TEST_F(XMLUtilConversionTest_40, ToIntValid_40) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilConversionTest_40, ToIntNegative_40) {
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt("-10", &value));
    EXPECT_EQ(-10, value);
}

TEST_F(XMLUtilConversionTest_40, ToIntInvalid_40) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("abc", &value));
}

TEST_F(XMLUtilConversionTest_40, ToIntNullStr_40) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToUnsignedValid_40) {
    unsigned int value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned("100", &value));
    EXPECT_EQ(100u, value);
}

TEST_F(XMLUtilConversionTest_40, ToUnsignedInvalid_40) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilConversionTest_40, ToUnsignedNull_40) {
    unsigned int value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToBoolTrue_40) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_40, ToBoolFalse_40) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_40, ToBool1_40) {
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilConversionTest_40, ToBool0_40) {
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilConversionTest_40, ToBoolInvalid_40) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilConversionTest_40, ToBoolNull_40) {
    bool value = false;
    EXPECT_FALSE(XMLUtil::ToBool(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToFloatValid_40) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST_F(XMLUtilConversionTest_40, ToFloatInvalid_40) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("notanumber", &value));
}

TEST_F(XMLUtilConversionTest_40, ToFloatNull_40) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToDoubleValid_40) {
    double value = 0.0;
    EXPECT_TRUE(XMLUtil::ToDouble("2.718281828", &value));
    EXPECT_NEAR(2.718281828, value, 1e-9);
}

TEST_F(XMLUtilConversionTest_40, ToDoubleInvalid_40) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("notadouble", &value));
}

TEST_F(XMLUtilConversionTest_40, ToDoubleNull_40) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToInt64Valid_40) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("9876543210", &value));
    EXPECT_EQ(9876543210LL, value);
}

TEST_F(XMLUtilConversionTest_40, ToInt64Negative_40) {
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64("-9876543210", &value));
    EXPECT_EQ(-9876543210LL, value);
}

TEST_F(XMLUtilConversionTest_40, ToInt64Invalid_40) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilConversionTest_40, ToInt64Null_40) {
    int64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToInt64(nullptr, &value));
}

TEST_F(XMLUtilConversionTest_40, ToUnsigned64Valid_40) {
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(18446744073709551615ULL, value);
}

TEST_F(XMLUtilConversionTest_40, ToUnsigned64Invalid_40) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("xyz", &value));
}

TEST_F(XMLUtilConversionTest_40, ToUnsigned64Null_40) {
    uint64_t value = 0;
    EXPECT_FALSE(XMLUtil::ToUnsigned64(nullptr, &value));
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilWhiteSpaceTest_40 : public ::testing::Test {};

TEST_F(XMLUtilWhiteSpaceTest_40, SpaceIsWhiteSpace_40) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilWhiteSpaceTest_40, TabIsWhiteSpace_40) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilWhiteSpaceTest_40, NewlineIsWhiteSpace_40) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilWhiteSpaceTest_40, CarriageReturnIsWhiteSpace_40) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilWhiteSpaceTest_40, LetterIsNotWhiteSpace_40) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilWhiteSpaceTest_40, DigitIsNotWhiteSpace_40) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilWhiteSpaceTest_40, NullCharIsNotWhiteSpace_40) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_40 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_40, LetterIsNameStartChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_40, UnderscoreIsNameStartChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_40, ColonIsNameStartChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_40, DigitIsNotNameStartChar_40) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_40, DotIsNotNameStartChar_40) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('.'));
}

TEST_F(XMLUtilNameCharTest_40, HyphenIsNotNameStartChar_40) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

TEST_F(XMLUtilNameCharTest_40, DigitIsNameChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_40, LetterIsNameChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilNameCharTest_40, HyphenIsNameChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_40, DotIsNameChar_40) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_40, SpaceIsNotNameChar_40) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilIsPrefixHexTest_40 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_40, ValidHexPrefix_40) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_40, NotHexPrefix_40) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("x12"));
}

TEST_F(XMLUtilIsPrefixHexTest_40, JustZero_40) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST_F(XMLUtilIsPrefixHexTest_40, ZeroXOnly_40) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x"));
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

class XMLUtilUTF8Test_40 : public ::testing::Test {};

TEST_F(XMLUtilUTF8Test_40, ContinuationByte_40) {
    // UTF-8 continuation bytes are 10xxxxxx (0x80 - 0xBF)
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST_F(XMLUtilUTF8Test_40, NonContinuationByte_40) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x00)));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xC0)));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_40 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_40, SkipsLeadingSpaces_40) {
    const char* str = "   hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('h', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, SkipsTabsAndNewlines_40) {
    const char* str = "\t\n\r world";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('w', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, NoWhiteSpace_40) {
    const char* str = "hello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ(str, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, AllWhiteSpace_40) {
    const char* str = "   ";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('\0', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, NewlineIncrementsLineNum_40) {
    const char* str = "\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('h', *result);
    EXPECT_EQ(3, lineNum);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, NullLineNum_40) {
    const char* str = "  hello";
    const char* result = XMLUtil::SkipWhiteSpace(str, nullptr);
    EXPECT_EQ('h', *result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, NullPointerReturnsNull_40) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_40, MutableVersion_40) {
    char str[] = "  hello";
    int lineNum = 1;
    char* result = XMLUtil::SkipWhiteSpace(str, &lineNum);
    EXPECT_EQ('h', *result);
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilReadBOMTest_40 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_40, NoBOM_40) {
    const char* str = "hello";
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(str, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(str, result);
}

TEST_F(XMLUtilReadBOMTest_40, WithBOM_40) {
    // UTF-8 BOM: EF BB BF
    const char str[] = "\xEF\xBB\xBFhello";
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM(str, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ('h', *result);
}

TEST_F(XMLUtilReadBOMTest_40, NullPointer_40) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM(nullptr, &hasBOM);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilUTF32ToUTF8Test_40 : public ::testing::Test {};

TEST_F(XMLUtilUTF32ToUTF8Test_40, ASCIICharacter_40) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilUTF32ToUTF8Test_40, TwoByteCharacter_40) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x00E9, output, &length); // 'é'
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilUTF32ToUTF8Test_40, ThreeByteCharacter_40) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x4E2D, output, &length); // '中'
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilUTF32ToUTF8Test_40, FourByteCharacter_40) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(4, length);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilBoolSerializationTest_40 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to default
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilBoolSerializationTest_40, CustomBoolSerialization_40) {
    XMLUtil::SetBoolSerialization("yes", "no");
    char buf[64];
    XMLUtil::ToStr(true, buf, sizeof(buf));
    EXPECT_STREQ("yes", buf);
    XMLUtil::ToStr(false, buf, sizeof(buf));
    EXPECT_STREQ("no", buf);
}

TEST_F(XMLUtilBoolSerializationTest_40, ResetToDefault_40) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    char buf[64];
    XMLUtil::ToStr(true, buf, sizeof(buf));
    EXPECT_STREQ("true", buf);
    XMLUtil::ToStr(false, buf, sizeof(buf));
    EXPECT_STREQ("false", buf);
}

// ============================================================
// GetCharacterRef Tests
// ============================================================

class XMLUtilGetCharacterRefTest_40 : public ::testing::Test {};

TEST_F(XMLUtilGetCharacterRefTest_40, DecimalCharRef_40) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#65;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_40, HexCharRef_40) {
    char value[8] = {};
    int length = 0;
    const char* input = "&#x41;rest";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', value[0]);
}

TEST_F(XMLUtilGetCharacterRefTest_40, NotACharRef_40) {
    char value[8] = {};
    int length = 0;
    const char* input = "hello";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(nullptr, result);
}

// ============================================================
// Roundtrip Tests (ToStr -> To*)
// ============================================================

class XMLUtilRoundtripTest_40 : public ::testing::Test {};

TEST_F(XMLUtilRoundtripTest_40, IntRoundtrip_40) {
    char buf[64];
    XMLUtil::ToStr(INT_MAX, buf, sizeof(buf));
    int value = 0;
    EXPECT_TRUE(XMLUtil::ToInt(buf, &value));
    EXPECT_EQ(INT_MAX, value);
}

TEST_F(XMLUtilRoundtripTest_40, DoubleRoundtrip_40) {
    char buf[64];
    XMLUtil::ToStr(1.23456789012345, buf, sizeof(buf));
    double value = 0;
    EXPECT_TRUE(XMLUtil::ToDouble(buf, &value));
    EXPECT_NEAR(1.23456789012345, value, 1e-10);
}

TEST_F(XMLUtilRoundtripTest_40, Int64Roundtrip_40) {
    char buf[64];
    int64_t original = INT64_MAX;
    XMLUtil::ToStr(original, buf, sizeof(buf));
    int64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToInt64(buf, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_40, Uint64Roundtrip_40) {
    char buf[64];
    uint64_t original = UINT64_MAX;
    XMLUtil::ToStr(original, buf, sizeof(buf));
    uint64_t value = 0;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buf, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_40, BoolTrueRoundtrip_40) {
    char buf[64];
    XMLUtil::ToStr(true, buf, sizeof(buf));
    bool value = false;
    EXPECT_TRUE(XMLUtil::ToBool(buf, &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilRoundtripTest_40, BoolFalseRoundtrip_40) {
    char buf[64];
    XMLUtil::ToStr(false, buf, sizeof(buf));
    bool value = true;
    EXPECT_TRUE(XMLUtil::ToBool(buf, &value));
    EXPECT_FALSE(value);
}

// ============================================================
// Edge Cases for ToInt with whitespace / empty string
// ============================================================

class XMLUtilEdgeCaseTest_40 : public ::testing::Test {};

TEST_F(XMLUtilEdgeCaseTest_40, ToIntEmptyString_40) {
    int value = 0;
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilEdgeCaseTest_40, ToDoubleEmptyString_40) {
    double value = 0.0;
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

TEST_F(XMLUtilEdgeCaseTest_40, ToFloatZero_40) {
    float value = -1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilEdgeCaseTest_40, ToIntZeroString_40) {
    int value = -1;
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilEdgeCaseTest_40, StringEqualDifferentLengthStrings_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("short", "shorter"));
    EXPECT_FALSE(XMLUtil::StringEqual("shorter", "short"));
}

TEST_F(XMLUtilEdgeCaseTest_40, StringEqualWithIntMax_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("test", "test", INT_MAX));
}
