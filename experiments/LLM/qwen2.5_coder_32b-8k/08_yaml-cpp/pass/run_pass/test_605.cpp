#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <sstream>



using namespace YAML::conversion;



TEST(ConvertStreamToTest_605, ValidUnsignedCharConversion_605) {

    std::stringstream stream("255");

    unsigned char result;

    EXPECT_TRUE(ConvertStreamTo(stream, result));

    EXPECT_EQ(result, 255);

}



TEST(ConvertStreamToTest_605, ValidSignedCharConversion_605) {

    std::stringstream stream("-128");

    signed char result;

    EXPECT_TRUE(ConvertStreamTo(stream, result));

    EXPECT_EQ(result, -128);

}



TEST(ConvertStreamToTest_605, OutOfRangeUnsignedChar_605) {

    std::stringstream stream("256");

    unsigned char result;

    EXPECT_FALSE(ConvertStreamTo(stream, result));

}



TEST(ConvertStreamToTest_605, OutOfRangeSignedChar_605) {

    std::stringstream stream("-129");

    signed char result;

    EXPECT_FALSE(ConvertStreamTo(stream, result));

}



TEST(ConvertStreamToTest_605, EmptyString_605) {

    std::stringstream stream("");

    unsigned char result;

    EXPECT_FALSE(ConvertStreamTo(stream, result));

}



TEST(ConvertStreamToTest_605, NonNumericInput_605) {

    std::stringstream stream("abc");

    signed char result;

    EXPECT_FALSE(ConvertStreamTo(stream, result));

}



TEST(ConvertStreamToTest_605, LeadingWhitespace_605) {

    std::stringstream stream(" 127");

    signed char result;

    EXPECT_TRUE(ConvertStreamTo(stream, result));

    EXPECT_EQ(result, 127);

}



TEST(ConvertStreamToTest_605, TrailingWhitespace_605) {

    std::stringstream stream("127 ");

    signed char result;

    EXPECT_TRUE(ConvertStreamTo(stream, result));

    EXPECT_EQ(result, 127);

}



TEST(ConvertStreamToTest_605, BothWhitespaces_605) {

    std::stringstream stream(" 127 ");

    signed char result;

    EXPECT_TRUE(ConvertStreamTo(stream, result));

    EXPECT_EQ(result, 127);

}
