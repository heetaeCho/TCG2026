#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <cstring>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ==================== ToUnsigned Tests ====================

class XMLUtilToUnsignedTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToUnsignedTest_173, DecimalValue_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("42", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(42u, value);
}

TEST_F(XMLUtilToUnsignedTest_173, ZeroValue_173) {
    unsigned value = 99;
    bool result = XMLUtil::ToUnsigned("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsignedTest_173, HexValueWith0x_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("0xFF", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0xFFu, value);
}

TEST_F(XMLUtilToUnsignedTest_173, HexValueWith0X_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("0X1A", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0x1Au, value);
}

TEST_F(XMLUtilToUnsignedTest_173, MaxUnsignedDecimal_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("4294967295", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(UINT_MAX, value);
}

TEST_F(XMLUtilToUnsignedTest_173, MaxUnsignedHex_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("0xFFFFFFFF", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0xFFFFFFFFu, value);
}

TEST_F(XMLUtilToUnsignedTest_173, LargeDecimalValue_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("1000000", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1000000u, value);
}

TEST_F(XMLUtilToUnsignedTest_173, HexValueLowerCase_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("0xabcdef", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0xABCDEFu, value);
}

TEST_F(XMLUtilToUnsignedTest_173, HexValueUpperCase_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("0xABCDEF", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0xABCDEFu, value);
}

TEST_F(XMLUtilToUnsignedTest_173, HexZero_173) {
    unsigned value = 99;
    bool result = XMLUtil::ToUnsigned("0x0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

TEST_F(XMLUtilToUnsignedTest_173, SimpleOne_173) {
    unsigned value = 0;
    bool result = XMLUtil::ToUnsigned("1", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1u, value);
}

// ==================== ToInt Tests ====================

class XMLUtilToIntTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToIntTest_173, PositiveValue_173) {
    int value = 0;
    bool result = XMLUtil::ToInt("123", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(123, value);
}

TEST_F(XMLUtilToIntTest_173, NegativeValue_173) {
    int value = 0;
    bool result = XMLUtil::ToInt("-456", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-456, value);
}

TEST_F(XMLUtilToIntTest_173, ZeroValue_173) {
    int value = 99;
    bool result = XMLUtil::ToInt("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToIntTest_173, MaxInt_173) {
    int value = 0;
    bool result = XMLUtil::ToInt("2147483647", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(INT_MAX, value);
}

TEST_F(XMLUtilToIntTest_173, MinInt_173) {
    int value = 0;
    bool result = XMLUtil::ToInt("-2147483648", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(INT_MIN, value);
}

// ==================== ToBool Tests ====================

class XMLUtilToBoolTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToBoolTest_173, TrueString_173) {
    bool value = false;
    bool result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_173, FalseString_173) {
    bool value = true;
    bool result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_173, NumericOne_173) {
    bool value = false;
    bool result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_173, NumericZero_173) {
    bool value = true;
    bool result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_173, InvalidString_173) {
    bool value = false;
    bool result = XMLUtil::ToBool("maybe", &value);
    EXPECT_FALSE(result);
}

// ==================== ToFloat Tests ====================

class XMLUtilToFloatTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToFloatTest_173, PositiveFloat_173) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST_F(XMLUtilToFloatTest_173, NegativeFloat_173) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("-2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(-2.5f, value);
}

TEST_F(XMLUtilToFloatTest_173, ZeroFloat_173) {
    float value = 1.0f;
    bool result = XMLUtil::ToFloat("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_173, IntegerAsFloat_173) {
    float value = 0.0f;
    bool result = XMLUtil::ToFloat("42", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(42.0f, value);
}

// ==================== ToDouble Tests ====================

class XMLUtilToDoubleTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToDoubleTest_173, PositiveDouble_173) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("3.14159265358979", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(3.14159265358979, value);
}

TEST_F(XMLUtilToDoubleTest_173, NegativeDouble_173) {
    double value = 0.0;
    bool result = XMLUtil::ToDouble("-1.23456789", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(-1.23456789, value);
}

TEST_F(XMLUtilToDoubleTest_173, ZeroDouble_173) {
    double value = 1.0;
    bool result = XMLUtil::ToDouble("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(0.0, value);
}

// ==================== ToInt64 Tests ====================

class XMLUtilToInt64Test_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToInt64Test_173, PositiveInt64_173) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(INT64_MAX, value);
}

TEST_F(XMLUtilToInt64Test_173, NegativeInt64_173) {
    int64_t value = 0;
    bool result = XMLUtil::ToInt64("-100", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilToInt64Test_173, ZeroInt64_173) {
    int64_t value = 99;
    bool result = XMLUtil::ToInt64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, value);
}

// ==================== ToUnsigned64 Tests ====================

class XMLUtilToUnsigned64Test_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilToUnsigned64Test_173, PositiveUnsigned64_173) {
    uint64_t value = 0;
    bool result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilToUnsigned64Test_173, ZeroUnsigned64_173) {
    uint64_t value = 99;
    bool result = XMLUtil::ToUnsigned64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(0u, value);
}

// ==================== ToStr Tests ====================

class XMLUtilToStrTest_173 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_173, IntToStr_173) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_173, NegativeIntToStr_173) {
    XMLUtil::ToStr(-100, buffer, sizeof(buffer));
    EXPECT_STREQ("-100", buffer);
}

TEST_F(XMLUtilToStrTest_173, ZeroIntToStr_173) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ("0", buffer);
}

TEST_F(XMLUtilToStrTest_173, UnsignedToStr_173) {
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_173, BoolTrueToStr_173) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_173, BoolFalseToStr_173) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_173, Int64ToStr_173) {
    XMLUtil::ToStr((int64_t)123456789012345LL, buffer, sizeof(buffer));
    EXPECT_STREQ("123456789012345", buffer);
}

TEST_F(XMLUtilToStrTest_173, Uint64ToStr_173) {
    XMLUtil::ToStr((uint64_t)123456789012345ULL, buffer, sizeof(buffer));
    EXPECT_STREQ("123456789012345", buffer);
}

// ==================== IsPrefixHex Tests ====================

class XMLUtilIsPrefixHexTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilIsPrefixHexTest_173, HexPrefix0x_173) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_173, HexPrefix0X_173) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_173, NoHexPrefix_173) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_173, JustZero_173) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST_F(XMLUtilIsPrefixHexTest_173, EmptyLikePrefix_173) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("1x00"));
}

// ==================== StringEqual Tests ====================

class XMLUtilStringEqualTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilStringEqualTest_173, EqualStrings_173) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_173, DifferentStrings_173) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_173, PartialMatch_173) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello world", 5));
}

TEST_F(XMLUtilStringEqualTest_173, BothNull_173) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_173, OneNull_173) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
}

TEST_F(XMLUtilStringEqualTest_173, OtherNull_173) {
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_173, EmptyStrings_173) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

// ==================== IsWhiteSpace Tests ====================

class XMLUtilIsWhiteSpaceTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilIsWhiteSpaceTest_173, Space_173) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_173, Tab_173) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_173, Newline_173) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_173, CarriageReturn_173) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_173, NonWhiteSpace_173) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('a'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_173, DigitNotWhiteSpace_173) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

// ==================== IsNameStartChar Tests ====================

class XMLUtilIsNameStartCharTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilIsNameStartCharTest_173, LowerCaseLetter_173) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
}

TEST_F(XMLUtilIsNameStartCharTest_173, UpperCaseLetter_173) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilIsNameStartCharTest_173, Underscore_173) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilIsNameStartCharTest_173, Colon_173) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilIsNameStartCharTest_173, DigitNotStart_173) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST_F(XMLUtilIsNameStartCharTest_173, DashNotStart_173) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('-'));
}

// ==================== IsNameChar Tests ====================

class XMLUtilIsNameCharTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilIsNameCharTest_173, Letter_173) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
}

TEST_F(XMLUtilIsNameCharTest_173, Digit_173) {
    EXPECT_TRUE(XMLUtil::IsNameChar('5'));
}

TEST_F(XMLUtilIsNameCharTest_173, Dash_173) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilIsNameCharTest_173, Dot_173) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilIsNameCharTest_173, SpaceNotNameChar_173) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ==================== ReadBOM Tests ====================

class XMLUtilReadBOMTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilReadBOMTest_173, NoBOM_173) {
    bool hasBOM = true;
    const char* input = "<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(input, result);
}

TEST_F(XMLUtilReadBOMTest_173, WithUTF8BOM_173) {
    bool hasBOM = false;
    // UTF-8 BOM is EF BB BF
    const char input[] = "\xEF\xBB\xBF<?xml version=\"1.0\"?>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(input + 3, result);
}

// ==================== SkipWhiteSpace Tests ====================

class XMLUtilSkipWhiteSpaceTest_173 : public ::testing::Test {
protected:
};

TEST_F(XMLUtilSkipWhiteSpaceTest_173, SkipsSpaces_173) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_173, SkipsTabs_173) {
    const char* input = "\t\thello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_173, SkipsNewlines_173) {
    int lineNum = 1;
    const char* input = "\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(3, lineNum);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_173, NoWhiteSpace_173) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_173, NullInput_173) {
    const char* result = XMLUtil::SkipWhiteSpace((const char*)nullptr, nullptr);
    EXPECT_EQ(nullptr, result);
}

// ==================== ConvertUTF32ToUTF8 Tests ====================

class XMLUtilConvertUTF32ToUTF8Test_173 : public ::testing::Test {
protected:
    char output[8];
    int length;
};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_173, ASCIICharacter_173) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_173, TwoByteCharacter_173) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xA9, output, &length); // ©
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_173, ThreeByteCharacter_173) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // €
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_173, FourByteCharacter_173) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // 😀
    EXPECT_EQ(4, length);
}

// ==================== SetBoolSerialization Tests ====================

class XMLUtilSetBoolSerializationTest_173 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilSetBoolSerializationTest_173, CustomTrueFalse_173) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

TEST_F(XMLUtilSetBoolSerializationTest_173, ResetToDefault_173) {
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}
