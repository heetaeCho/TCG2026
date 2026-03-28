#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// ToBool Tests
// ============================================================

class XMLUtilToBoolTest_174 : public ::testing::Test {
protected:
    bool value;
    bool result;
};

// --- String "true" variants ---

TEST_F(XMLUtilToBoolTest_174, ToBool_LowercaseTrue_174) {
    result = XMLUtil::ToBool("true", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_TitleCaseTrue_174) {
    result = XMLUtil::ToBool("True", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_UppercaseTrue_174) {
    result = XMLUtil::ToBool("TRUE", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

// --- String "false" variants ---

TEST_F(XMLUtilToBoolTest_174, ToBool_LowercaseFalse_174) {
    result = XMLUtil::ToBool("false", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_TitleCaseFalse_174) {
    result = XMLUtil::ToBool("False", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_UppercaseFalse_174) {
    result = XMLUtil::ToBool("FALSE", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

// --- Numeric values ---

TEST_F(XMLUtilToBoolTest_174, ToBool_IntegerZero_174) {
    result = XMLUtil::ToBool("0", &value);
    EXPECT_TRUE(result);
    EXPECT_FALSE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_IntegerOne_174) {
    result = XMLUtil::ToBool("1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_IntegerNegativeOne_174) {
    result = XMLUtil::ToBool("-1", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_IntegerLargePositive_174) {
    result = XMLUtil::ToBool("42", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_IntegerLargeNegative_174) {
    result = XMLUtil::ToBool("-100", &value);
    EXPECT_TRUE(result);
    EXPECT_TRUE(value);
}

// --- Invalid strings ---

TEST_F(XMLUtilToBoolTest_174, ToBool_EmptyString_174) {
    result = XMLUtil::ToBool("", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_RandomString_174) {
    result = XMLUtil::ToBool("hello", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_MixedCaseTrUe_174) {
    result = XMLUtil::ToBool("tRuE", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_MixedCaseFaLsE_174) {
    result = XMLUtil::ToBool("fAlSe", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_NullString_174) {
    result = XMLUtil::ToBool(nullptr, &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToBoolTest_174, ToBool_TrueWithTrailingSpace_174) {
    // "true " is not exactly "true", behavior depends on StringEqual
    result = XMLUtil::ToBool("true ", &value);
    // The string might not match "true" exactly, but could parse as int fails too
    // We just check it doesn't crash; result may be false
    // Not asserting specific value since behavior depends on internal StringEqual
}

TEST_F(XMLUtilToBoolTest_174, ToBool_WhitespaceOnly_174) {
    result = XMLUtil::ToBool("   ", &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToInt Tests
// ============================================================

class XMLUtilToIntTest_174 : public ::testing::Test {
protected:
    int value;
    bool result;
};

TEST_F(XMLUtilToIntTest_174, ToInt_Zero_174) {
    result = XMLUtil::ToInt("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilToIntTest_174, ToInt_PositiveNumber_174) {
    result = XMLUtil::ToInt("12345", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 12345);
}

TEST_F(XMLUtilToIntTest_174, ToInt_NegativeNumber_174) {
    result = XMLUtil::ToInt("-9876", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, -9876);
}

TEST_F(XMLUtilToIntTest_174, ToInt_InvalidString_174) {
    result = XMLUtil::ToInt("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToIntTest_174, ToInt_EmptyString_174) {
    result = XMLUtil::ToInt("", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToIntTest_174, ToInt_NullString_174) {
    result = XMLUtil::ToInt(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToUnsigned Tests
// ============================================================

class XMLUtilToUnsignedTest_174 : public ::testing::Test {
protected:
    unsigned int value;
    bool result;
};

TEST_F(XMLUtilToUnsignedTest_174, ToUnsigned_Zero_174) {
    result = XMLUtil::ToUnsigned("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 0u);
}

TEST_F(XMLUtilToUnsignedTest_174, ToUnsigned_PositiveNumber_174) {
    result = XMLUtil::ToUnsigned("54321", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 54321u);
}

TEST_F(XMLUtilToUnsignedTest_174, ToUnsigned_InvalidString_174) {
    result = XMLUtil::ToUnsigned("xyz", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToUnsignedTest_174, ToUnsigned_NullString_174) {
    result = XMLUtil::ToUnsigned(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToFloat Tests
// ============================================================

class XMLUtilToFloatTest_174 : public ::testing::Test {
protected:
    float value;
    bool result;
};

TEST_F(XMLUtilToFloatTest_174, ToFloat_Zero_174) {
    result = XMLUtil::ToFloat("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLUtilToFloatTest_174, ToFloat_PositiveFloat_174) {
    result = XMLUtil::ToFloat("3.14", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 3.14f, 0.001f);
}

TEST_F(XMLUtilToFloatTest_174, ToFloat_NegativeFloat_174) {
    result = XMLUtil::ToFloat("-2.5", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, -2.5f, 0.001f);
}

TEST_F(XMLUtilToFloatTest_174, ToFloat_InvalidString_174) {
    result = XMLUtil::ToFloat("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToFloatTest_174, ToFloat_NullString_174) {
    result = XMLUtil::ToFloat(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToDouble Tests
// ============================================================

class XMLUtilToDoubleTest_174 : public ::testing::Test {
protected:
    double value;
    bool result;
};

TEST_F(XMLUtilToDoubleTest_174, ToDouble_Zero_174) {
    result = XMLUtil::ToDouble("0.0", &value);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(value, 0.0);
}

TEST_F(XMLUtilToDoubleTest_174, ToDouble_PositiveDouble_174) {
    result = XMLUtil::ToDouble("2.718281828", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, 2.718281828, 1e-9);
}

TEST_F(XMLUtilToDoubleTest_174, ToDouble_NegativeDouble_174) {
    result = XMLUtil::ToDouble("-1.41421356", &value);
    EXPECT_TRUE(result);
    EXPECT_NEAR(value, -1.41421356, 1e-8);
}

TEST_F(XMLUtilToDoubleTest_174, ToDouble_InvalidString_174) {
    result = XMLUtil::ToDouble("abc", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToDoubleTest_174, ToDouble_NullString_174) {
    result = XMLUtil::ToDouble(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToInt64 Tests
// ============================================================

class XMLUtilToInt64Test_174 : public ::testing::Test {
protected:
    int64_t value;
    bool result;
};

TEST_F(XMLUtilToInt64Test_174, ToInt64_Zero_174) {
    result = XMLUtil::ToInt64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 0);
}

TEST_F(XMLUtilToInt64Test_174, ToInt64_LargePositive_174) {
    result = XMLUtil::ToInt64("9223372036854775807", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLUtilToInt64Test_174, ToInt64_LargeNegative_174) {
    result = XMLUtil::ToInt64("-9223372036854775808", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, INT64_MIN);
}

TEST_F(XMLUtilToInt64Test_174, ToInt64_InvalidString_174) {
    result = XMLUtil::ToInt64("notanumber", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToInt64Test_174, ToInt64_NullString_174) {
    result = XMLUtil::ToInt64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToUnsigned64 Tests
// ============================================================

class XMLUtilToUnsigned64Test_174 : public ::testing::Test {
protected:
    uint64_t value;
    bool result;
};

TEST_F(XMLUtilToUnsigned64Test_174, ToUnsigned64_Zero_174) {
    result = XMLUtil::ToUnsigned64("0", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 0u);
}

TEST_F(XMLUtilToUnsigned64Test_174, ToUnsigned64_LargeValue_174) {
    result = XMLUtil::ToUnsigned64("18446744073709551615", &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(XMLUtilToUnsigned64Test_174, ToUnsigned64_InvalidString_174) {
    result = XMLUtil::ToUnsigned64("invalid", &value);
    EXPECT_FALSE(result);
}

TEST_F(XMLUtilToUnsigned64Test_174, ToUnsigned64_NullString_174) {
    result = XMLUtil::ToUnsigned64(nullptr, &value);
    EXPECT_FALSE(result);
}

// ============================================================
// ToStr Tests
// ============================================================

class XMLUtilToStrTest_174 : public ::testing::Test {
protected:
    char buffer[256];
};

TEST_F(XMLUtilToStrTest_174, ToStr_Int_Positive_174) {
    XMLUtil::ToStr(42, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "42");
}

TEST_F(XMLUtilToStrTest_174, ToStr_Int_Negative_174) {
    XMLUtil::ToStr(-7, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "-7");
}

TEST_F(XMLUtilToStrTest_174, ToStr_Int_Zero_174) {
    XMLUtil::ToStr(0, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "0");
}

TEST_F(XMLUtilToStrTest_174, ToStr_Unsigned_174) {
    XMLUtil::ToStr(100u, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "100");
}

TEST_F(XMLUtilToStrTest_174, ToStr_BoolTrue_174) {
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
}

TEST_F(XMLUtilToStrTest_174, ToStr_BoolFalse_174) {
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

TEST_F(XMLUtilToStrTest_174, ToStr_Float_174) {
    XMLUtil::ToStr(1.5f, buffer, sizeof(buffer));
    // Should contain some representation of 1.5
    float parsed;
    EXPECT_TRUE(XMLUtil::ToFloat(buffer, &parsed));
    EXPECT_NEAR(parsed, 1.5f, 0.001f);
}

TEST_F(XMLUtilToStrTest_174, ToStr_Double_174) {
    XMLUtil::ToStr(2.718281828, buffer, sizeof(buffer));
    double parsed;
    EXPECT_TRUE(XMLUtil::ToDouble(buffer, &parsed));
    EXPECT_NEAR(parsed, 2.718281828, 1e-6);
}

TEST_F(XMLUtilToStrTest_174, ToStr_Int64_174) {
    XMLUtil::ToStr((int64_t)123456789012345LL, buffer, sizeof(buffer));
    int64_t parsed;
    EXPECT_TRUE(XMLUtil::ToInt64(buffer, &parsed));
    EXPECT_EQ(parsed, 123456789012345LL);
}

TEST_F(XMLUtilToStrTest_174, ToStr_UInt64_174) {
    XMLUtil::ToStr((uint64_t)18446744073709551610ULL, buffer, sizeof(buffer));
    uint64_t parsed;
    EXPECT_TRUE(XMLUtil::ToUnsigned64(buffer, &parsed));
    EXPECT_EQ(parsed, 18446744073709551610ULL);
}

// ============================================================
// StringEqual Tests
// ============================================================

class XMLUtilStringEqualTest_174 : public ::testing::Test {};

TEST_F(XMLUtilStringEqualTest_174, StringEqual_SameStrings_174) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_DifferentStrings_174) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_BothNull_174) {
    EXPECT_TRUE(XMLUtil::StringEqual(nullptr, nullptr));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_OneNull_174) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", nullptr));
    EXPECT_FALSE(XMLUtil::StringEqual(nullptr, "hello"));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_EmptyStrings_174) {
    EXPECT_TRUE(XMLUtil::StringEqual("", ""));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_WithNChar_174) {
    EXPECT_TRUE(XMLUtil::StringEqual("hello world", "hello there", 5));
}

TEST_F(XMLUtilStringEqualTest_174, StringEqual_WithNCharDifferent_174) {
    EXPECT_FALSE(XMLUtil::StringEqual("hello", "helly", 5));
}

// ============================================================
// IsWhiteSpace Tests
// ============================================================

class XMLUtilIsWhiteSpaceTest_174 : public ::testing::Test {};

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_Space_174) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace(' '));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_Tab_174) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\t'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_Newline_174) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\n'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_CarriageReturn_174) {
    EXPECT_TRUE(XMLUtil::IsWhiteSpace('\r'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_Letter_174) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('A'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_Digit_174) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('5'));
}

TEST_F(XMLUtilIsWhiteSpaceTest_174, IsWhiteSpace_NullChar_174) {
    EXPECT_FALSE(XMLUtil::IsWhiteSpace('\0'));
}

// ============================================================
// IsNameStartChar / IsNameChar Tests
// ============================================================

class XMLUtilNameCharTest_174 : public ::testing::Test {};

TEST_F(XMLUtilNameCharTest_174, IsNameStartChar_Letter_174) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));
    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameStartChar_Underscore_174) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameStartChar_Colon_174) {
    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameStartChar_Digit_174) {
    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameChar_Digit_174) {
    EXPECT_TRUE(XMLUtil::IsNameChar('0'));
    EXPECT_TRUE(XMLUtil::IsNameChar('9'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameChar_Hyphen_174) {
    EXPECT_TRUE(XMLUtil::IsNameChar('-'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameChar_Dot_174) {
    EXPECT_TRUE(XMLUtil::IsNameChar('.'));
}

TEST_F(XMLUtilNameCharTest_174, IsNameChar_Space_174) {
    EXPECT_FALSE(XMLUtil::IsNameChar(' '));
}

// ============================================================
// IsPrefixHex Tests
// ============================================================

class XMLUtilIsPrefixHexTest_174 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_174, IsPrefixHex_Valid_174) {
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(XMLUtil::IsPrefixHex("0X1A"));
}

TEST_F(XMLUtilIsPrefixHexTest_174, IsPrefixHex_Invalid_174) {
    EXPECT_FALSE(XMLUtil::IsPrefixHex("123"));
    EXPECT_FALSE(XMLUtil::IsPrefixHex("x12"));
}

// ============================================================
// ReadBOM Tests
// ============================================================

class XMLUtilReadBOMTest_174 : public ::testing::Test {};

TEST_F(XMLUtilReadBOMTest_174, ReadBOM_NoBOM_174) {
    bool hasBOM = true;
    const char* input = "<root/>";
    const char* result = XMLUtil::ReadBOM(input, &hasBOM);
    EXPECT_FALSE(hasBOM);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilReadBOMTest_174, ReadBOM_WithUTF8BOM_174) {
    bool hasBOM = false;
    const char bom[] = "\xEF\xBB\xBF<root/>";
    const char* result = XMLUtil::ReadBOM(bom, &hasBOM);
    EXPECT_TRUE(hasBOM);
    EXPECT_EQ(result, bom + 3);  // Should skip the 3-byte BOM
}

// ============================================================
// SetBoolSerialization Tests
// ============================================================

class XMLUtilSetBoolSerializationTest_174 : public ::testing::Test {
protected:
    char buffer[256];
    
    void TearDown() override {
        // Reset to defaults
        XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_174, SetBoolSerialization_CustomValues_174) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "yes");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "no");
}

TEST_F(XMLUtilSetBoolSerializationTest_174, SetBoolSerialization_ResetToDefaults_174) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
    XMLUtil::ToStr(true, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "true");
    XMLUtil::ToStr(false, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "false");
}

// ============================================================
// SkipWhiteSpace Tests
// ============================================================

class XMLUtilSkipWhiteSpaceTest_174 : public ::testing::Test {};

TEST_F(XMLUtilSkipWhiteSpaceTest_174, SkipWhiteSpace_NoWhiteSpace_174) {
    const char* input = "hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(result, input);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_174, SkipWhiteSpace_LeadingSpaces_174) {
    const char* input = "   hello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_EQ(result, input + 3);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_174, SkipWhiteSpace_MixedWhiteSpace_174) {
    const char* input = " \t\n\rhello";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ(result, "hello");
}

TEST_F(XMLUtilSkipWhiteSpaceTest_174, SkipWhiteSpace_AllWhiteSpace_174) {
    const char* input = "   ";
    const char* result = XMLUtil::SkipWhiteSpace(input, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(XMLUtilSkipWhiteSpaceTest_174, SkipWhiteSpace_CountsNewlines_174) {
    const char* input = "\n\n\nhello";
    int lineNum = 1;
    const char* result = XMLUtil::SkipWhiteSpace(input, &lineNum);
    EXPECT_STREQ(result, "hello");
    EXPECT_EQ(lineNum, 4);
}

// ============================================================
// ConvertUTF32ToUTF8 Tests
// ============================================================

class XMLUtilConvertUTF32ToUTF8Test_174 : public ::testing::Test {};

TEST_F(XMLUtilConvertUTF32ToUTF8Test_174, ConvertASCII_174) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x41, output, &length);  // 'A'
    EXPECT_EQ(length, 1);
    EXPECT_EQ(output[0], 'A');
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_174, ConvertTwoByteChar_174) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0xC9, output, &length);  // É
    EXPECT_EQ(length, 2);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_174, ConvertThreeByteChar_174) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x20AC, output, &length);  // € sign
    EXPECT_EQ(length, 3);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_174, ConvertFourByteChar_174) {
    char output[8] = {};
    int length = 0;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600, output, &length);  // emoji
    EXPECT_EQ(length, 4);
}
