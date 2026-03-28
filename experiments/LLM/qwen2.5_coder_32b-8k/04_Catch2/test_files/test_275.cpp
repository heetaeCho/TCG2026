#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



using namespace Catch;



TEST(StringMakerSignedCharTest_275, ConvertNewlineCharacter_275) {

    signed char value = '\n';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'\\n'");

}



TEST(StringMakerSignedCharTest_275, ConvertCarriageReturnCharacter_275) {

    signed char value = '\r';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'\\r'");

}



TEST(StringMakerSignedCharTest_275, ConvertFormFeedCharacter_275) {

    signed char value = '\f';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'\\f'");

}



TEST(StringMakerSignedCharTest_275, ConvertTabCharacter_275) {

    signed char value = '\t';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'\\t'");

}



TEST(StringMakerSignedCharTest_275, ConvertNullCharacter_275) {

    signed char value = '\0';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "0");

}



TEST(StringMakerSignedCharTest_275, ConvertSpaceCharacter_275) {

    signed char value = ' ';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "' '");

}



TEST(StringMakerSignedCharTest_275, ConvertNonPrintableAsciiCharacter_275) {

    signed char value = 1; // Example of a non-printable ASCII character

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "1");

}



TEST(StringMakerSignedCharTest_275, ConvertPrintableAsciiCharacter_275) {

    signed char value = 'A';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'A'");

}
