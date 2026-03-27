#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/UTF.h"

#include "./TestProjects/poppler/poppler/PDFDocEncoding.h"



// Mocking UTF16toUCS4 function for testing purposes

class MockUTF {

public:

    MOCK_STATIC_METHOD1(UTF16toUCS4, std::vector<Unicode>(const std::vector<Unicode>&));

};



using ::testing::_;



TEST(TextStringToUCS4Test_1521, EmptyStringReturnsEmptyVector_1521) {

    EXPECT_EQ(TextStringToUCS4(""), std::vector<Unicode>());

}



TEST(TextStringToUCS4Test_1521, NonUnicodeStringConvertedUsingPDFDocEncoding_1521) {

    const std::string_view input = "Hello";

    std::vector<Unicode> expected;

    for (char c : input) {

        expected.push_back(pdfDocEncoding[static_cast<unsigned char>(c)]);

    }

    EXPECT_EQ(TextStringToUCS4(input), expected);

}



TEST(TextStringToUCS4Test_1521, UnicodeBEStringConvertedCorrectly_1521) {

    std::string_view input = "\xFE\xFF\x00H\x00e\x00l\x00l\x00o"; // UTF-16 BE

    std::vector<Unicode> utf16{0x48, 0x65, 0x6C, 0x6C, 0x6F};

    std::vector<Unicode> expected = MockUTF::UTF16toUCS4(utf16);



    EXPECT_CALL(MockUTF(), UTF16toUCS4(_))

        .WillOnce(::testing::Return(expected));



    EXPECT_EQ(TextStringToUCS4(input), expected);

}



TEST(TextStringToUCS4Test_1521, UnicodeLEStringConvertedCorrectly_1521) {

    std::string_view input = "\xFF\xFEH\x00e\x00l\x00l\x00o"; // UTF-16 LE

    std::vector<Unicode> utf16{0x48, 0x65, 0x6C, 0x6C, 0x6F};

    std::vector<Unicode> expected = MockUTF::UTF16toUCS4(utf16);



    EXPECT_CALL(MockUTF(), UTF16toUCS4(_))

        .WillOnce(::testing::Return(expected));



    EXPECT_EQ(TextStringToUCS4(input), expected);

}



TEST(TextStringToUCS4Test_1521, InvalidUnicodeStringReturnsEmptyVector_1521) {

    std::string_view input = "\xFE\xFE\x00H"; // Invalid UTF-16

    EXPECT_EQ(TextStringToUCS4(input), std::vector<Unicode>());

}



TEST(TextStringToUCS4Test_1521, SingleByteNonUnicodeCharacterConvertedCorrectly_1521) {

    const std::string_view input = "A";

    std::vector<Unicode> expected{pdfDocEncoding[static_cast<unsigned char>('A')]};

    EXPECT_EQ(TextStringToUCS4(input), expected);

}



TEST(TextStringToUCS4Test_1521, SingleByteUnicodeBOMIgnored_1521) {

    const std::string_view input = "\xFE\xFF";

    EXPECT_EQ(TextStringToUCS4(input), std::vector<Unicode>());

}
