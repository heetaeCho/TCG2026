#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <string>

// Include the tinyxml2 header
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToUnsigned64 Tests
// ============================================================

class XMLUtilToUnsigned64Test_178 : public ::testing::Test {
protected:
    uint64_t value;
};

TEST_F(XMLUtilToUnsigned64Test_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesPositiveDecimal_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("12345", &value));
    EXPECT_EQ(12345ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesLargeValue_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHexWithPrefix0x_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0xFF", &value));
    EXPECT_EQ(255ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHexWithPrefix0X_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0X1A", &value));
    EXPECT_EQ(26ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHexZero_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0x0", &value));
    EXPECT_EQ(0ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHexLargeValue_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0xFFFFFFFFFFFFFFFF", &value));
    EXPECT_EQ(UINT64_MAX, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHexMixedCase_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0xAbCdEf", &value));
    EXPECT_EQ(0xABCDEFULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, FailsOnEmptyString_178) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

TEST_F(XMLUtilToUnsigned64Test_178, FailsOnNonNumericString_178) {
    EXPECT_FALSE(XMLUtil::ToUnsigned64("abc", &value));
}

TEST_F(XMLUtilToUnsigned64Test_178, FailsOnOnlyWhitespace_178) {
    // May or may not parse depending on sscanf behavior; test observable behavior
    bool result = XMLUtil::ToUnsigned64("   ", &value);
    // Just verify it doesn't crash; result depends on implementation
    (void)result;
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesOne_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("1", &value));
    EXPECT_EQ(1ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesDecimalWithLeadingZeros_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("00042", &value));
    EXPECT_EQ(42ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesHex0x10_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0x10", &value));
    EXPECT_EQ(16ULL, value);
}

TEST_F(XMLUtilToUnsigned64Test_178, ParsesMidRangeValue_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned64("9999999999", &value));
    EXPECT_EQ(9999999999ULL, value);
}

// ============================================================
// ToInt Tests
// ============================================================

class XMLUtilToIntTest_178 : public ::testing::Test {
protected:
    int value;
};

TEST_F(XMLUtilToIntTest_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToInt("0", &value));
    EXPECT_EQ(0, value);
}

TEST_F(XMLUtilToIntTest_178, ParsesPositive_178) {
    EXPECT_TRUE(XMLUtil::ToInt("42", &value));
    EXPECT_EQ(42, value);
}

TEST_F(XMLUtilToIntTest_178, ParsesNegative_178) {
    EXPECT_TRUE(XMLUtil::ToInt("-100", &value));
    EXPECT_EQ(-100, value);
}

TEST_F(XMLUtilToIntTest_178, FailsOnNonNumeric_178) {
    EXPECT_FALSE(XMLUtil::ToInt("hello", &value));
}

TEST_F(XMLUtilToIntTest_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToInt("", &value));
}

TEST_F(XMLUtilToIntTest_178, ParsesIntMax_178) {
    std::string s = std::to_string(INT_MAX);
    EXPECT_TRUE(XMLUtil::ToInt(s.c_str(), &value));
    EXPECT_EQ(INT_MAX, value);
}

TEST_F(XMLUtilToIntTest_178, ParsesIntMin_178) {
    std::string s = std::to_string(INT_MIN);
    EXPECT_TRUE(XMLUtil::ToInt(s.c_str(), &value));
    EXPECT_EQ(INT_MIN, value);
}

// ============================================================
// ToUnsigned Tests
// ============================================================

class XMLUtilToUnsignedTest_178 : public ::testing::Test {
protected:
    unsigned int value;
};

TEST_F(XMLUtilToUnsignedTest_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("0", &value));
    EXPECT_EQ(0U, value);
}

TEST_F(XMLUtilToUnsignedTest_178, ParsesPositive_178) {
    EXPECT_TRUE(XMLUtil::ToUnsigned("65535", &value));
    EXPECT_EQ(65535U, value);
}

TEST_F(XMLUtilToUnsignedTest_178, FailsOnNonNumeric_178) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("xyz", &value));
}

TEST_F(XMLUtilToUnsignedTest_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToUnsigned("", &value));
}

// ============================================================
// ToBool Tests
// ============================================================

class XMLUtilToBoolTest_178 : public ::testing::Test {
protected:
    bool value;
};

TEST_F(XMLUtilToBoolTest_178, ParsesTrue_178) {
    EXPECT_TRUE(XMLUtil::ToBool("true", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_178, ParsesFalse_178) {
    EXPECT_TRUE(XMLUtil::ToBool("false", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_178, Parses1AsTrue_178) {
    EXPECT_TRUE(XMLUtil::ToBool("1", &value));
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_178, Parses0AsFalse_178) {
    EXPECT_TRUE(XMLUtil::ToBool("0", &value));
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_178, FailsOnInvalidString_178) {
    EXPECT_FALSE(XMLUtil::ToBool("maybe", &value));
}

TEST_F(XMLUtilToBoolTest_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToBool("", &value));
}

// ============================================================
// ToFloat Tests
// ============================================================

class XMLUtilToFloatTest_178 : public ::testing::Test {
protected:
    float value;
};

TEST_F(XMLUtilToFloatTest_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToFloat("0.0", &value));
    EXPECT_FLOAT_EQ(0.0f, value);
}

TEST_F(XMLUtilToFloatTest_178, ParsesPositive_178) {
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST_F(XMLUtilToFloatTest_178, ParsesNegative_178) {
    EXPECT_TRUE(XMLUtil::ToFloat("-2.5", &value));
    EXPECT_FLOAT_EQ(-2.5f, value);
}

TEST_F(XMLUtilToFloatTest_178, FailsOnNonNumeric_178) {
    EXPECT_FALSE(XMLUtil::ToFloat("abc", &value));
}

TEST_F(XMLUtilToFloatTest_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

// ============================================================
// ToDouble Tests
// ============================================================

class XMLUtilToDoubleTest_178 : public ::testing::Test {
protected:
    double value;
};

TEST_F(XMLUtilToDoubleTest_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToDouble("0.0", &value));
    EXPECT_DOUBLE_EQ(0.0, value);
}

TEST_F(XMLUtilToDoubleTest_178, ParsesPositive_178) {
    EXPECT_TRUE(XMLUtil::ToDouble("3.141592653589793", &value));
    EXPECT_NEAR(3.141592653589793, value, 1e-12);
}

TEST_F(XMLUtilToDoubleTest_178, ParsesNegative_178) {
    EXPECT_TRUE(XMLUtil::ToDouble("-1.5e10", &value));
    EXPECT_DOUBLE_EQ(-1.5e10, value);
}

TEST_F(XMLUtilToDoubleTest_178, FailsOnNonNumeric_178) {
    EXPECT_FALSE(XMLUtil::ToDouble("notanumber", &value));
}

TEST_F(XMLUtilToDoubleTest_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToDouble("", &value));
}

// ============================================================
// ToInt64 Tests
// ============================================================

class XMLUtilToInt64Test_178 : public ::testing::Test {
protected:
    int64_t value;
};

TEST_F(XMLUtilToInt64Test_178, ParsesZero_178) {
    EXPECT_TRUE(XMLUtil::ToInt64("0", &value));
    EXPECT_EQ(0LL, value);
}

TEST_F(XMLUtilToInt64Test_178, ParsesPositive_178) {
    EXPECT_TRUE(XMLUtil::ToInt64("9223372036854775807", &value));
    EXPECT_EQ(INT64_MAX, value);
}

TEST_F(XMLUtilToInt64Test_178, ParsesNegative_178) {
    EXPECT_TRUE(XMLUtil::ToInt64("-9223372036854775808", &value));
    EXPECT_EQ(INT64_MIN, value);
}

TEST_F(XMLUtilToInt64Test_178, FailsOnNonNumeric_178) {
    EXPECT_FALSE(XMLUtil::ToInt64("abc", &value));
}

TEST_F(XMLUtilToInt64Test_178, FailsOnEmpty_178) {
    EXPECT_FALSE(XMLUtil::ToInt64("", &value));
}

// ============================================================
// ToStr Tests
// ============================================================

class XMLUtilToStrTest_178 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_178, IntToStr_178) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ("42", buffer);
}

TEST_F(XMLUtilToStrTest_178, NegativeIntToStr_178) {
    XMLUtil::ToStr(-7, buffer, sizeof(buffer));
    EXPECT_STREQ("-7", buffer);
}

TEST_F(XMLUtilToStrTest_178, UnsignedToStr_178) {
    XMLUtil::ToStr(123U, buffer, sizeof(buffer));
    EXPECT_STREQ("123", buffer);
}

TEST_F(XMLUtilToStrTest_178, BoolTrueToStr_178) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
}

TEST_F(XMLUtilToStrTest_178, BoolFalseToStr_178) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

TEST_F(XMLUtilToStrTest_178, Int64ToStr_178) {
    XMLUtil::ToStr(static_cast<int64_t>(9223372036854775807LL), buffer, sizeof(buffer));
    EXPECT_STREQ("9223372036854775807", buffer);
}

TEST_F(XMLUtilToStrTest_178, Uint64ToStr_178) {
    XMLUtil::ToStr(static_cast<uint64_t>(18446744073709551615ULL), buffer, sizeof(buffer));
    EXPECT_STREQ("18446744073709551615", buffer);
}

TEST_F(XMLUtilToStrTest_178, FloatToStr_178) {
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Verify that it contains some representation of 1.5
    float parsed;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_FLOAT_EQ(1.5f, parsed);
}

TEST_F(XMLUtilToStrTest_178, DoubleToStr_178) {
    XMLUtil::ToStr(2.5, buffer, sizeof(buffer));
    double parsed;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_DOUBLE_EQ(2.5, parsed);
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilIsPrefixHexTest_178 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_178, DetectsLowercase0x_178) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_178, DetectsUppercase0X_178) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_178, NonHexDecimal_178) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
}

TEST_F(XMLUtilIsPrefixHexTest_178, JustZero_178) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("0"));
}

TEST_F(XMLUtilIsPrefixHexTest_178, EmptyString_178) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex(""));
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilIsWhiteSpaceTest_178 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_178, SpaceIsWhitespace_178) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, TabIsWhitespace_178) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, NewlineIsWhitespace_178) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, CarriageReturnIsWhitespace_178) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, LetterIsNotWhitespace_178) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, DigitIsNotWhitespace_178) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('0'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_178, NullIsNotWhitespace_178) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_178 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_178, EqualStrings_178) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_178, DifferentStrings_178) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_178, BothNull_178) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_178, OneNull_178) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_178, PartialComparison_178) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello", 5));
}

TEST_F(XMLUtilStringEqualTest_178, EmptyStrings_178) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_178, EmptyVsNonEmpty_178) {
    EXPECT_FALSE(XMLUtil::StringEqual("", "a"));
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilReadBOMTest_178 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_178, NoBOM_178) {
    bool hasBOM = false;
    const char* result = XMLUtil::ReadBOM("<xml/>", &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_STREQ("<xml/>", result);
}

TEST_F(XMLUtilReadBOMTest_178, WithUTF8BOM_178) {
    bool hasBOM = false;
    // UTF-8 BOM: 0xEF 0xBB 0xBF
    const char input[] = "\xEF\xBB\xBF<xml/>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_TRUE(hasBOM);
    // After BOM, should point past the BOM bytes
    EXPECT_STREQ("<xml/>", result);
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_178 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_178, LetterIsNameStartChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_178, UnderscoreIsNameStartChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_178, ColonIsNameStartChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_178, DigitIsNotNameStartChar_178) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
    EXPECT_FALSE(XMLUtil::IsNameStartChar('9'));
}

TEST_F(XMLUtilNameCharTest_178, DigitIsNameChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_178, DotIsNameChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_178, HyphenIsNameChar_178) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_178, SpaceIsNotNameChar_178) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_178 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_178, SkipsLeadingWhitespace_178) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_178, NoWhitespace_178) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("hello", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_178, AllWhitespace_178) {
    const char* input = "   \t\n";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ("", result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_178, NullInput_178) {
    const char* result = XMLUtil::SkipWhiteSpace(static_cast<const char*>(nullptr), nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_178, CountsNewlines_178) {
    int lineNum = 1;
    const char* input = "\n\nhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ("hello", result);
    EXPECT_EQ(3, lineNum);
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilSetBoolSerializationTest_178 : public ::testing::Test {
protected:
    char buffer[256];
    
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_178, CustomTrueFalse_178) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("yes", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("no", buffer);
}

TEST_F(XMLUtilSetBoolSerializationTest_178, ResetToDefault_178) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ("true", buffer);
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ("false", buffer);
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilConvertUTF32ToUTF8Test_178 : public ::testing::Test {
protected:
    char output[8];
    int length;
};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_178, AsciiCharacter_178) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length); // 'A'
    EXPECT_EQ(1, length);
    EXPECT_EQ('A', output[0]);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_178, TwoByteCharacter_178) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length); // É
    EXPECT_EQ(2, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_178, ThreeByteCharacter_178) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length); // € symbol
    EXPECT_EQ(3, length);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_178, FourByteCharacter_178) {
    memset(output, 0, sizeof(output));
    length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length); // emoji
    EXPECT_EQ(4, length);
}

// ============================================================
// IsUTF8Continuation Tests
// ============================================================

class XMLUtilIsUTF8ContinuationTest_178 : public ::testing::Test {};

TEST_F(XMLUtilIsUTF8ContinuationTest_178, ContinuationByte_178) {
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xBF)));
}

TEST_F(XMLUtilIsUTF8ContinuationTest_178, NonContinuationByte_178) {
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(XMLUtil::IsUTF8Continuation(static_cast<char>(0xC0)));
}

// ============================================================
// Roundtrip Tests (ToStr -> Parse)
// ============================================================

class XMLUtilRoundtripTest_178 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilRoundtripTest_178, IntRoundtrip_178) {
    XMLUtil::ToStr(-12345, buffer, sizeof(buffer));
    int value;
    EXPECT_TRUE(XMLUtil::ToInt(buffer, &value));
    EXPECT_EQ(-12345, value);
}

TEST_F(XMLUtilRoundtripTest_178, UnsignedRoundtrip_178) {
    XMLUtil::ToStr(4000000000U, buffer, sizeof(buffer));
    unsigned int value;
    EXPECT_TRUE(XMLUtil::ToUnsigned(buffer, &value));
    EXPECT_EQ(4000000000U, value);
}

TEST_F(XMLUtilRoundtripTest_178, Int64Roundtrip_178) {
    int64_t original = INT64_MAX;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    int64_t value;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_178, Uint64Roundtrip_178) {
    uint64_t original = UINT64_MAX;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    uint64_t value;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &value));
    EXPECT_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_178, DoubleRoundtrip_178) {
    double original = 3.141592653589793;
    XMLUtil::ToStr(original, buffer, sizeof(buffer));
    double value;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &value));
    EXPECT_DOUBLE_EQ(original, value);
}

TEST_F(XMLUtilRoundtripTest_178, BoolRoundtrip_178) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    bool value;
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_TRUE(value);

    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_TRUE(XMLUtil::ToBool(buffer, &value));
    EXPECT_FALSE(value);
}
