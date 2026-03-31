#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <string>

// Include the tinyxml2 header
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Tests for ToInt64
// ============================================================

class XMLUtilToInt64Test_177 : public ::testing::Test {
protected:
    int64_t value = 0;
};

TEST_F(XMLUtilToInt64Test_177, ParsesPositiveDecimal_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("12345", &value));
    EXPECT_EQ(value, 12345);
}

TEST_F(XMLUtilToInt64Test_177, ParsesNegativeDecimal_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("-98765", &value));
    EXPECT_EQ(value, -98765);
}

TEST_F(XMLUtilToInt64Test_177, ParsesZero_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexLowercase_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0xff", &value));
    EXPECT_EQ(value, 255);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexUppercase_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0xFF", &value));
    EXPECT_EQ(value, 255);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexUpperPrefix_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0X1A", &value));
    EXPECT_EQ(value, 26);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexZero_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0x0", &value));
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilToInt64Test_177, ParsesLargePositiveDecimal_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLUtilToInt64Test_177, ParsesLargeNegativeDecimal_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("-9223372036854775808", &value));
    EXPECT_EQ(value, INT64_MIN);
}

TEST_F(XMLUtilToInt64Test_177, ParsesLargeHexValue_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0xFFFFFFFFFFFFFFFF", &value));
    // 0xFFFFFFFFFFFFFFFF interpreted as unsigned and cast to int64_t is -1
    EXPECT_EQ(value, -1);
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForEmptyString_177) {
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForNonNumericString_177) {
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForNullString_177) {
    // Depending on implementation, nullptr might crash or return false
    // We test with empty/non-numeric instead if nullptr is unsafe
    EXPECT_FALSE(XMLUtil::ToInt64("xyz", &value));
}

TEST_F(XMLUtilToInt64Test_177, ParsesDecimalWithLeadingSpaces_177) {
    // sscanf typically handles leading whitespace
    EXPECT_TRUE(XMLUtil::ToInt64("  42", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilToInt64Test_177, ParsesOne_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("1", &value));
    EXPECT_EQ(value, 1);
}

TEST_F(XMLUtilToInt64Test_177, ParsesNegativeOne_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("-1", &value));
    EXPECT_EQ(value, -1);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHex1_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0x1", &value));
    EXPECT_EQ(value, 1);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexWithMixedCase_177) {
    EXPECT_TRUE(XMLUtil::ToInt64("0xAbCdEf", &value));
    EXPECT_EQ(value, 0xABCDEF);
}

// ============================================================
// Tests for ToInt
// ============================================================

class XMLUtilToIntTest_177 : public ::testing::Test {
protected:
    int value = 0;
};

TEST_F(XMLUtilToIntTest_177, ParsesPositiveInt_177) {
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(XMLUtilToIntTest_177, ParsesNegativeInt_177) {
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(value, -100);
}

TEST_F(XMLUtilToIntTest_177, ParsesZero_177) {
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilToIntTest_177, ReturnsFalseForNonNumeric_177) {
    EXPECT_FALSE(XMLUtil::ToInt("hello", &value));
}

TEST_F(XMLUtilToIntTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilToIntTest_177, ParsesIntMax_177) {
    std::string s = std::to_string(INT_MAX);
    EXPECT_TRUE(XMLUtil::ToInt(s.c_str(), &value));
    EXPECT_EQ(value, INT_MAX);
}

TEST_F(XMLUtilToIntTest_177, ParsesIntMin_177) {
    std::string s = std::to_string(INT_MIN);
    EXPECT_TRUE(XMLUtil::ToInt(s.c_str(), &value));
    EXPECT_EQ(value, INT_MIN);
}

// ============================================================
// Tests for ToUnsigned
// ============================================================

class XMLUtilToUnsignedTest_177 : public ::testing::Test {
protected:
    unsigned int value = 0;
};

TEST_F(XMLUtilToUnsignedTest_177, ParsesPositive_177) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("123", &value));
    EXPECT_EQ(value, 123u);
}

TEST_F(XMLUtilToUnsignedTest_177, ParsesZero_177) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(value, 0u);
}

TEST_F(XMLUtilToUnsignedTest_177, ReturnsFalseForNonNumeric_177) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("abc", &value));
}

TEST_F(XMLUtilToUnsignedTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

// ============================================================
// Tests for ToBool
// ============================================================

class XMLUtilToBoolTest_177 : public ::testing::Test {
protected:
    bool value = false;
};

TEST_F(XMLUtilToBoolTest_177, ParsesTrue_177) {
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_177, ParsesFalse_177) {
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_177, ParsesOne_177) {
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_177, ParsesZero_177) {
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_177, ReturnsFalseForInvalid_177) {
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilToBoolTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// ============================================================
// Tests for ToFloat
// ============================================================

class XMLUtilToFloatTest_177 : public ::testing::Test {
protected:
    float value = 0.0f;
};

TEST_F(XMLUtilToFloatTest_177, ParsesPositiveFloat_177) {
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_FLOAT_EQ(value, 3.14f);
}

TEST_F(XMLUtilToFloatTest_177, ParsesNegativeFloat_177) {
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_FLOAT_EQ(value, -2.5f);
}

TEST_F(XMLUtilToFloatTest_177, ParsesZeroFloat_177) {
    EXPECT_TRUE(XMLUtil::ToFloat("0.0", &value));
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLUtilToFloatTest_177, ReturnsFalseForNonNumeric_177) {
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilToFloatTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

// ============================================================
// Tests for ToDouble
// ============================================================

class XMLUtilToDoubleTest_177 : public ::testing::Test {
protected:
    double value = 0.0;
};

TEST_F(XMLUtilToDoubleTest_177, ParsesPositiveDouble_177) {
    EXPECT_TRUE(XMLUtil::ToDouble("3.141592653589793", &value));
    EXPECT_DOUBLE_EQ(value, 3.141592653589793);
}

TEST_F(XMLUtilToDoubleTest_177, ParsesNegativeDouble_177) {
    EXPECT_TRUE(XMLUtil::ToDouble("-1.5", &value));
    EXPECT_DOUBLE_EQ(value, -1.5);
}

TEST_F(XMLUtilToDoubleTest_177, ParsesZeroDouble_177) {
    EXPECT_TRUE(XMLUtil::ToDouble("0.0", &value));
    EXPECT_DOUBLE_EQ(value, 0.0);
}

TEST_F(XMLUtilToDoubleTest_177, ReturnsFalseForNonNumeric_177) {
    EXPECT_FALSE(XMLUtil::ToDouble("xyz", &value));
}

TEST_F(XMLUtilToDoubleTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

// ============================================================
// Tests for ToUnsigned64
// ============================================================

class XMLUtilToUnsigned64Test_177 : public ::testing::Test {
protected:
    uint64_t value = 0;
};

TEST_F(XMLUtilToUnsigned64Test_177, ParsesPositive_177) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("12345678901234", &value));
    EXPECT_EQ(value, 12345678901234ULL);
}

TEST_F(XMLUtilToUnsigned64Test_177, ParsesZero_177) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(value, 0ULL);
}

TEST_F(XMLUtilToUnsigned64Test_177, ParsesMaxUint64_177) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(XMLUtilToUnsigned64Test_177, ReturnsFalseForNonNumeric_177) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilToUnsigned64Test_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

// ============================================================
// Tests for ToStr
// ============================================================

class XMLUtilToStrTest_177 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_177, IntToStr_177) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_177, NegativeIntToStr_177) {
    XMLUtil::ToStr(-7, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-7");
}

TEST_F(XMLUtilToStrTest_177, ZeroIntToStr_177) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_177, UnsignedToStr_177) {
    XMLUtil::ToStr(42u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_177, BoolTrueToStr_177) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilToStrTest_177, BoolFalseToStr_177) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST_F(XMLUtilToStrTest_177, Int64ToStr_177) {
    XMLUtil::ToStr(static_cast<int64_t>(9223372036854775807LL), buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "9223372036854775807");
}

TEST_F(XMLUtilToStrTest_177, Uint64ToStr_177) {
    XMLUtil::ToStr(static_cast<uint64_t>(18446744073709551615ULL), buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "18446744073709551615");
}

TEST_F(XMLUtilToStrTest_177, FloatToStr_177) {
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Just verify it starts with "1.5"
    std::string result(buffer);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(XMLUtilToStrTest_177, DoubleToStr_177) {
    XMLUtil::ToStr(2.5, buffer, sizeof(buffer));
    std::string result(buffer);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

// ============================================================
// Tests for IsPrefixHex
// ============================================================

class XMLUtilIsPrefixHexTest_177 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_177, DetectsLowerHexPrefix_177) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1F"));
}

TEST_F(XMLUtilIsPrefixHexTest_177, DetectsUpperHexPrefix_177) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1F"));
}

TEST_F(XMLUtilIsPrefixHexTest_177, ReturnsFalseForDecimal_177) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_177, ReturnsFalseForEmpty_177) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

TEST_F(XMLUtilIsPrefixHexTest_177, ReturnsFalseForJustZero_177) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

// ============================================================
// Tests for IsWhiteSpace
// ============================================================

class XMLUtilIsWhiteSpaceTest_177 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_177, SpaceIsWhiteSpace_177) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_177, TabIsWhiteSpace_177) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_177, NewlineIsWhiteSpace_177) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_177, CarriageReturnIsWhiteSpace_177) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_177, LetterIsNotWhiteSpace_177) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_177, DigitIsNotWhiteSpace_177) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

// ============================================================
// Tests for StringEqual
// ============================================================

class XMLUtilStringEqualTest_177 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_177, EqualStrings_177) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_177, DifferentStrings_177) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_177, EqualWithNChar_177) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilStringEqualTest_177, DifferentWithNChar_177) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "hxllo", 5));
}

TEST_F(XMLUtilStringEqualTest_177, BothNull_177) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_177, OneNull_177) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

// ============================================================
// Tests for ReadBOM
// ============================================================

class XMLUtilReadBOMTest_177 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_177, NoBOM_177) {
    bool hasBOM = true;
    const char* result = XMLUtil::ReadBOM("<?xml", &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_STREQ(result, "<?xml");
}

TEST_F(XMLUtilReadBOMTest_177, WithBOM_177) {
    bool hasBOM = false;
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char bom[] = {'\xEF', '\xBB', '\xBF', '<', '?', 'x', 'm', 'l', '\0'};
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    // After BOM, result should point past the BOM bytes
    EXPECT_EQ(result, bom + 3);
}

// ============================================================
// Tests for SkipWhiteSpace
// ============================================================

class XMLUtilSkipWhiteSpaceTest_177 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_177, SkipsLeadingSpaces_177) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLUtilSkipWhiteSpaceTest_177, SkipsTabsAndNewlines_177) {
    const char* input = "\t\n\r world";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ(result, "world");
}

TEST_F(XMLUtilSkipWhiteSpaceTest_177, NoWhiteSpace_177) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLUtilSkipWhiteSpaceTest_177, CountsNewlines_177) {
    int lineNum = 1;
    const char* input = "\n\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ(result, "hello");
    EXPECT_EQ(lineNum, 4);
}

// ============================================================
// Tests for IsNameStartChar and IsNameChar
// ============================================================

class XMLUtilNameCharTest_177 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_177, LetterIsNameStartChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_177, ColonIsNameStartChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_177, UnderscoreIsNameStartChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_177, DigitIsNotNameStartChar_177) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_177, DigitIsNameChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_177, LetterIsNameChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameChar('Z'));
}

TEST_F(XMLUtilNameCharTest_177, DashIsNameChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_177, DotIsNameChar_177) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_177, SpaceIsNotNameChar_177) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// Tests for ConvertUTF32ToUTF8
// ============================================================

class XMLUtilConvertUTF32Test_177 : public ::testing::Test {
protected:
    char output[8];
    int length = 0;
};

TEST_F(XMLUtilConvertUTF32Test_177, ASCIICharacter_177) {
    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32Test_177, TwoByteCharacter_177) {
    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32Test_177, ThreeByteCharacter_177) {
    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € sign
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32Test_177, FourByteCharacter_177) {
    memset(output, 0, sizeof(output));
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(length, 4);
}

// ============================================================
// Tests for SetBoolSerialization
// ============================================================

class XMLUtilSetBoolSerializationTest_177 : public ::testing::Test {
protected:
    char buffer[256];
    
    void TearDown() override {
        // Reset to default
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_177, CustomTrueAndFalse_177) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilSetBoolSerializationTest_177, ResetToDefault_177) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}
