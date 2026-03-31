#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the tinyxml2 header
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLUtilGetCharacterRefTest_164 : public ::testing::Test {
protected:
    char value[32];
    int length;

    void SetUp() override {
        memset(value, 0, sizeof(value));
        length = 0;
    }
};

// Test: Simple decimal character reference &#65; (character 'A')
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalCharRefA_164) {
    const char* input = "&#65;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    // 'A' is U+0041, which is 65 decimal, single byte in UTF-8
    EXPECT_EQ(value[0], 'A');
    EXPECT_EQ(length, 1);
    // Result should point past the semicolon
    EXPECT_EQ(result, input + 5);
}

// Test: Hexadecimal character reference &#x41; (character 'A')
TEST_F(XMLUtilGetCharacterRefTest_164, HexCharRefA_164) {
    const char* input = "&#x41;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(value[0], 'A');
    EXPECT_EQ(length, 1);
    EXPECT_EQ(result, input + 6);
}

// Test: Decimal character reference &#0; (null character - code point 0)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalCharRefZero_164) {
    const char* input = "&#0;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    // Code point 0 - behavior depends on ConvertUTF32ToUTF8
    // It might return a valid result or not
    if (result != nullptr) {
        EXPECT_EQ(result, input + 4);
    }
}

// Test: Hex character reference &#x0; (null character)
TEST_F(XMLUtilGetCharacterRefTest_164, HexCharRefZero_164) {
    const char* input = "&#x0;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    if (result != nullptr) {
        EXPECT_EQ(result, input + 5);
    }
}

// Test: Decimal reference for a 2-byte UTF-8 character &#169; (copyright symbol ©, U+00A9)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalTwoByteUTF8_164) {
    const char* input = "&#169;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(result, input + 6);
}

// Test: Decimal reference for a 3-byte UTF-8 character &#8364; (euro sign €, U+20AC)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalThreeByteUTF8_164) {
    const char* input = "&#8364;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(result, input + 7);
}

// Test: Hex reference for a 4-byte UTF-8 character &#x1F600; (U+1F600, emoji)
TEST_F(XMLUtilGetCharacterRefTest_164, HexFourByteUTF8_164) {
    const char* input = "&#x1F600;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 4);
    EXPECT_EQ(result, input + 9);
}

// Test: Maximum valid code point &#x10FFFF;
TEST_F(XMLUtilGetCharacterRefTest_164, HexMaxCodePoint_164) {
    const char* input = "&#x10FFFF;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(result, input + 10);
}

// Test: Code point exceeding max &#x110000; should return null
TEST_F(XMLUtilGetCharacterRefTest_164, HexExceedsMaxCodePoint_164) {
    const char* input = "&#x110000;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Very large decimal code point exceeding max should return null
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalExceedsMaxCodePoint_164) {
    const char* input = "&#1114112;"; // 0x110000 = 1114112
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Missing semicolon in decimal reference
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalMissingSemicolon_164) {
    const char* input = "&#65";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Missing semicolon in hex reference
TEST_F(XMLUtilGetCharacterRefTest_164, HexMissingSemicolon_164) {
    const char* input = "&#x41";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Invalid hex digit in hex reference
TEST_F(XMLUtilGetCharacterRefTest_164, HexInvalidDigit_164) {
    const char* input = "&#xGG;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Invalid character in decimal reference
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalInvalidDigit_164) {
    const char* input = "&#6a;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Not a character reference (no '#'), should return p+1
TEST_F(XMLUtilGetCharacterRefTest_164, NotCharacterRef_164) {
    const char* input = "&amp;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, input + 1);
    EXPECT_EQ(length, 0);
}

// Test: Empty after &#x (no digits before semicolon)
TEST_F(XMLUtilGetCharacterRefTest_164, HexEmptyAfterX_164) {
    const char* input = "&#x;";
    // q starts at p+3, which is ';'. strchr finds it immediately.
    // Then the while loop: *q != 'x' but q is at ';', digit parsing fails.
    // Actually wait: q = p+3 = ';', then strchr(q, ';') = q = p+3
    // delta = q-p = 3, --q => q = p+2 = 'x', *q == terminator => loop ends
    // ucs = 0, ConvertUTF32ToUTF8(0, ...) 
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    // Depends on how ConvertUTF32ToUTF8 handles code point 0
    // Could be nullptr or valid
    if (result != nullptr) {
        EXPECT_EQ(result, input + 4);
    }
}

// Test: Empty after &# (no digits)  
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalEmptyContent_164) {
    const char* input = "&#;";
    // q = p+2 = ';', strchr finds it, delta = 2, --q => q = p+1 = '#' = terminator
    // ucs = 0
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    if (result != nullptr) {
        EXPECT_EQ(result, input + 3);
    }
}

// Test: Hex with lowercase letters &#xab;
TEST_F(XMLUtilGetCharacterRefTest_164, HexLowercase_164) {
    const char* input = "&#xab;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(result, input + 6);
}

// Test: Hex with uppercase letters &#xAB;
TEST_F(XMLUtilGetCharacterRefTest_164, HexUppercase_164) {
    const char* input = "&#xAB;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(result, input + 6);
}

// Test: Hex with mixed case &#xAbCd;
TEST_F(XMLUtilGetCharacterRefTest_164, HexMixedCase_164) {
    const char* input = "&#xAbCd;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(result, input + 8);
}

// Test: Decimal single digit &#9; (tab character)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalSingleDigit_164) {
    const char* input = "&#9;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], '\t');
    EXPECT_EQ(result, input + 4);
}

// Test: Decimal &#10; (newline character)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalNewline_164) {
    const char* input = "&#10;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], '\n');
    EXPECT_EQ(result, input + 5);
}

// Test: Decimal &#13; (carriage return)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalCarriageReturn_164) {
    const char* input = "&#13;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], '\r');
    EXPECT_EQ(result, input + 5);
}

// Test: Hex &#xA; (newline)
TEST_F(XMLUtilGetCharacterRefTest_164, HexNewline_164) {
    const char* input = "&#xA;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], '\n');
    EXPECT_EQ(result, input + 5);
}

// Test: &#x with null terminator right after x
TEST_F(XMLUtilGetCharacterRefTest_164, HexNullAfterX_164) {
    const char input[] = {'&', '#', 'x', '\0'};
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: &# with null terminator right after #
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalNullAfterHash_164) {
    const char input[] = {'&', '#', '\0'};
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    // *(p+2) is '\0', which is falsy, so the outer if fails
    // Falls through to return p + 1
    EXPECT_EQ(result, input + 1);
}

// Test: Decimal value &#97; ('a')
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalLowercaseA_164) {
    const char* input = "&#97;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'a');
    EXPECT_EQ(result, input + 5);
}

// Test: Hex &#x61; ('a')
TEST_F(XMLUtilGetCharacterRefTest_164, HexLowercaseA_164) {
    const char* input = "&#x61;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'a');
    EXPECT_EQ(result, input + 6);
}

// Test: Verify decimal and hex produce same result for same code point
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalHexEquivalence_164) {
    char value1[32] = {0};
    char value2[32] = {0};
    int length1 = 0, length2 = 0;

    const char* input1 = "&#255;";
    const char* input2 = "&#xFF;";

    const char* result1 = XMLUtil::GetCharacterRef(input1, value1, &length1);
    const char* result2 = XMLUtil::GetCharacterRef(input2, value2, &length2);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(length1, length2);
    EXPECT_EQ(memcmp(value1, value2, length1), 0);
}

// Test: Boundary - code point 127 (DEL, single byte)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary127_164) {
    const char* input = "&#127;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(result, input + 6);
}

// Test: Boundary - code point 128 (first 2-byte UTF-8)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary128_164) {
    const char* input = "&#128;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(result, input + 6);
}

// Test: Boundary - code point 2047 (last 2-byte UTF-8, U+07FF)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary2047_164) {
    const char* input = "&#2047;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 2);
    EXPECT_EQ(result, input + 7);
}

// Test: Boundary - code point 2048 (first 3-byte UTF-8, U+0800)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary2048_164) {
    const char* input = "&#2048;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(result, input + 7);
}

// Test: Boundary - code point 65535 (last 3-byte UTF-8, U+FFFF)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary65535_164) {
    const char* input = "&#65535;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(result, input + 8);
}

// Test: Boundary - code point 65536 (first 4-byte UTF-8, U+10000)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalBoundary65536_164) {
    const char* input = "&#65536;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 4);
    EXPECT_EQ(result, input + 8);
}

// Test: Very large number exceeding max code point in decimal
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalVeryLargeNumber_164) {
    const char* input = "&#99999999;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Letter 'a' in decimal digits should fail
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalWithLetterFails_164) {
    const char* input = "&#1a2;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Hex with letter g should fail
TEST_F(XMLUtilGetCharacterRefTest_164, HexWithInvalidLetterG_164) {
    const char* input = "&#x1g;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    EXPECT_EQ(result, nullptr);
}

// Test: Input string "&" followed by non-hash character
TEST_F(XMLUtilGetCharacterRefTest_164, AmpersandNonHash_164) {
    const char* input = "&a;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    // *(p+1) != '#', so it falls to return p + 1
    EXPECT_EQ(result, input + 1);
    EXPECT_EQ(length, 0);
}

// Test: Decimal &#32; (space character)
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalSpace_164) {
    const char* input = "&#32;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], ' ');
    EXPECT_EQ(result, input + 5);
}

// Test: Hex &#x20; (space character)
TEST_F(XMLUtilGetCharacterRefTest_164, HexSpace_164) {
    const char* input = "&#x20;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], ' ');
    EXPECT_EQ(result, input + 6);
}

// Test: Multi-digit decimal &#12345;
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalMultiDigit_164) {
    const char* input = "&#12345;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(length, 0);
    EXPECT_EQ(result, input + 8);
}

// Test: Hex leading zeros &#x0041;
TEST_F(XMLUtilGetCharacterRefTest_164, HexLeadingZeros_164) {
    const char* input = "&#x0041;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
    EXPECT_EQ(result, input + 8);
}

// Test: Decimal leading zeros &#0065;
TEST_F(XMLUtilGetCharacterRefTest_164, DecimalLeadingZeros_164) {
    const char* input = "&#0065;";
    const char* result = XMLUtil::GetCharacterRef(input, value, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
    EXPECT_EQ(result, input + 7);
}
