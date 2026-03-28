#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QString>

#include <string>



namespace Poppler {

    QString UnicodeParsedString(const std::string &s1);

}



using namespace testing;



TEST(UnicodeParsedStringTest_1283, EmptyString_ReturnsEmptyQString_1283) {

    EXPECT_EQ(Poppler::UnicodeParsedString(""), QString());

}



TEST(UnicodeParsedStringTest_1283, StringWithUTF16BOM_ReturnsCorrectQString_1283) {

    std::string utf16LE = "\xFF\xFE" "H\x00e\x00l\x00l\x00o\x00"; // "Hello" in UTF-16 little-endian with BOM

    EXPECT_EQ(Poppler::UnicodeParsedString(utf16LE), QString("Hello"));

}



TEST(UnicodeParsedStringTest_1283, StringWithUTF16LEBOM_ReturnsCorrectQString_1283) {

    std::string utf16BE = "\xFE\xFF" "H\x00e\x00l\x00l\x00o\x00"; // "Hello" in UTF-16 big-endian with BOM

    EXPECT_EQ(Poppler::UnicodeParsedString(utf16BE), QString("Hello"));

}



TEST(UnicodeParsedStringTest_1283, StringWithoutBOM_ReturnsCorrectQString_1283) {

    std::string pdfDocEncoded = "Hello"; // Assuming this is the PDFDocEncoding for "Hello"

    EXPECT_EQ(Poppler::UnicodeParsedString(pdfDocEncoded), QString("Hello"));

}



TEST(UnicodeParsedStringTest_1283, StringWithInvalidUTF16_ReturnsEmptyQString_1283) {

    std::string invalidUtf16 = "\xFF\xFE" "H\x00e\x00l"; // Invalid UTF-16 sequence

    EXPECT_EQ(Poppler::UnicodeParsedString(invalidUtf16), QString());

}
