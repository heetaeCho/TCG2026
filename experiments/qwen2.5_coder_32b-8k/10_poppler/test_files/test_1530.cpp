#include <gtest/gtest.h>

#include <string>

#include <cstdint>



// Assuming these are defined in UTF.cc or included from another header

extern const uint32_t UCS4_MAX;

extern const uint32_t REPLACEMENT_CHAR;

extern const uint32_t UTF16_ACCEPT;

extern const uint32_t UTF16_REJECT;



std::string utf16ToUtf8(const uint16_t *utf16, int maxUtf16);



class UtfConversionTest : public ::testing::Test {

protected:

    static void SetUpTestSuite() {

        // Any global setup if needed

    }



    static void TearDownTestSuite() {

        // Any global cleanup if needed

    }

};



TEST_F(UtfConversionTest_1530, EmptyInput_1530) {

    const uint16_t utf16[] = { 0 };

    int maxUtf16 = 1;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "");

}



TEST_F(UtfConversionTest_1530, SingleAsciiChar_1530) {

    const uint16_t utf16[] = { 'A', 0 };

    int maxUtf16 = 2;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "A");

}



TEST_F(UtfConversionTest_1530, SingleBmpChar_1530) {

    const uint16_t utf16[] = { 0x0429, 0 }; // Cyrillic small letter 'щ'

    int maxUtf16 = 2;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xd1\x89");

}



TEST_F(UtfConversionTest_1530, SingleSupplementaryChar_1530) {

    const uint16_t utf16[] = { 0xD834, 0xDD1E, 0 }; // Musical symbol G clef

    int maxUtf16 = 3;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xf0\x9d\x84\x9e");

}



TEST_F(UtfConversionTest_1530, InvalidSurrogatePair_1530) {

    const uint16_t utf16[] = { 0xD834, 0xFFFE, 0 }; // Invalid surrogate pair

    int maxUtf16 = 3;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xef\xbf\xbd");

}



TEST_F(UtfConversionTest_1530, MaxUcs4Value_1530) {

    const uint16_t utf16[] = { 0xDBFF, 0xDFFF, 0 }; // U+10FFFF

    int maxUtf16 = 3;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xf4\x8f\xbf\xbf");

}



TEST_F(UtfConversionTest_1530, AboveMaxUcs4Value_1530) {

    const uint16_t utf16[] = { 0xDC00, 0xD800, 0 }; // Invalid sequence

    int maxUtf16 = 3;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xef\xbf\xbd");

}



TEST_F(UtfConversionTest_1530, MaxUtf16Length_1530) {

    const uint16_t utf16[] = { 'A', 'B', 'C' };

    int maxUtf16 = 2;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "AB");

}



TEST_F(UtfConversionTest_1530, BoundaryConditionShortBuffer_1530) {

    const uint16_t utf16[] = { 0xD834, 0xDD1E }; // Musical symbol G clef

    int maxUtf16 = 1;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xef\xbf\xbd");

}



TEST_F(UtfConversionTest_1530, IncompleteSurrogatePairAtEnd_1530) {

    const uint16_t utf16[] = { 0xD834, 0 };

    int maxUtf16 = 2;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xef\xbf\xbd");

}



TEST_F(UtfConversionTest_1530, AllReplacementChars_1530) {

    const uint16_t utf16[] = { 0xDC00, 0xD800, 0xDC00, 0 };

    int maxUtf16 = 4;

    std::string result = utf16ToUtf8(utf16, maxUtf16);

    EXPECT_EQ(result, "\xef\xbf\xbd\xe2\x98\x83");

}
