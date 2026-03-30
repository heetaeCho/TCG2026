#include <gtest/gtest.h>

#include <string_view>

#include <string>



// Assuming TextStringToUtf8 and pdfDocEncoding are defined in UTF.h and PDFDocEncoding.h respectively.

extern std::string TextStringToUtf8(std::string_view textStr);

extern const Unicode pdfDocEncoding[256];



namespace {



class TextStringToUtf8Test_1531 : public ::testing::Test {

protected:

    // Setup code, if needed

};



TEST_F(TextStringToUtf8Test_1531, EmptyStringConversion_1531) {

    std::string_view input = "";

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, "");

}



TEST_F(TextStringToUtf8Test_1531, AsciiStringConversion_1531) {

    std::string_view input = "Hello";

    std::string expected_output = "Hello";

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, PdfDocEncodingConversion_1531) {

    std::string_view input = "\x00\x24"; // Null and Dollar sign in PDFDocEncoding

    std::string expected_output = "\0$";

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, UnicodeByteOrderMarkConversion_1531) {

    std::string_view input = "\xFF\xFE\x48\x00\x65\x00\x6C\x00\x6C\x00\x6F\x00"; // UTF-16 LE BOM followed by "Hello"

    std::string expected_output = "Hello";

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, InvalidUnicodeByteOrderMarkConversion_1531) {

    std::string_view input = "\xFE\xFF"; // UTF-16 BE BOM (invalid for this function)

    std::string expected_output = "\uFFFD"; // Unicode replacement character

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, BoundaryConditionSingleByte_1531) {

    std::string_view input = "\xFF"; // Last byte in PDFDocEncoding

    std::string expected_output = {static_cast<char>(pdfDocEncoding[0xFF])};

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, BoundaryConditionTwoByte_1531) {

    std::string_view input = "\x48\x00"; // 'H' in UTF-16 LE

    std::string expected_output = "H";

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



TEST_F(TextStringToUtf8Test_1531, InvalidUtf16Conversion_1531) {

    std::string_view input = "\xFF\xFE\xFF\xFF"; // UTF-16 LE BOM followed by invalid code unit

    std::string expected_output = "\uFFFD"; // Unicode replacement character

    std::string result = TextStringToUtf8(input);

    EXPECT_EQ(result, expected_output);

}



}  // namespace
