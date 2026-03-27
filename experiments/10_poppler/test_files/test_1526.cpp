#include <gtest/gtest.h>

#include <string_view>

#include <u16string>



// Assuming these are defined in a header file included by UTF.cc

extern const uint32_t UTF8_ACCEPT;

extern const uint32_t UTF8_REJECT;

extern const uint32_t UCS4_MAX;

extern const uint16_t REPLACEMENT_CHAR;



std::u16string utf8ToUtf16(std::string_view utf8);



class UTFTest : public ::testing::Test {

protected:

    // Any common setup can go here

};



TEST_F(UTFTest_1526, NormalOperationLatin_1526) {

    std::string_view input = "Hello";

    std::u16string expected_output = u"Hello";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, NormalOperationUnicode_1526) {

    std::string_view input = "\xe4\xbd\xa0\xe5\xa5\xbd"; // "你好"

    std::u16string expected_output = u"\u4f60\u597d";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, BoundaryConditionEmptyString_1526) {

    std::string_view input = "";

    std::u16string expected_output = u"";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, BoundaryConditionSingleByte_1526) {

    std::string_view input = "A";

    std::u16string expected_output = u"A";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, BoundaryConditionFourByteUnicode_1526) {

    std::string_view input = "\xf0\x9f\xa4\x96"; // "🐦"

    std::u16string expected_output = u"\xd83e\udd96";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, ErrorCaseInvalidUTF8_1526) {

    std::string_view input = "\xc3\x28"; // Invalid UTF-8

    std::u16string expected_output = u"\xfffd";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, ErrorCaseMalformedSequence_1526) {

    std::string_view input = "\xf0\x9f\xa4"; // Incomplete UTF-8 sequence

    std::u16string expected_output = u"\xfffd";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, BoundaryConditionBOMHandling_1526) {

    std::string_view input = "\xef\xbb\xbfHello"; // UTF-8 BOM + "Hello"

    std::u16string expected_output = u"Hello";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}



TEST_F(UTFTest_1526, ErrorCaseUCS4MaxPlusOne_1526) {

    std::string_view input = "\xf7\xbf\xbf\xbf"; // UCS-4 max + 1

    std::u16string expected_output = u"\xfffd";

    EXPECT_EQ(utf8ToUtf16(input), expected_output);

}
