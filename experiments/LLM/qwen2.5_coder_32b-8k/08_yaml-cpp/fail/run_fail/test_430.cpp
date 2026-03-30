#include <gtest/gtest.h>

#include "fptostring.cpp"  // Assuming the header file is the same as the source file



using namespace YAML::detail::fp_formatting;



class ConvertToCharsTest_430 : public ::testing::Test {

protected:

    char buffer[25];

};



TEST_F(ConvertToCharsTest_430, NormalOperation_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value);

    EXPECT_EQ(result, 4);

    EXPECT_STREQ(buffer, "1234");

}



TEST_F(ConvertToCharsTest_430, WidthLessThanValueDigits_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value, 3);

    EXPECT_EQ(result, 4);

    EXPECT_STREQ(buffer, "1234");

}



TEST_F(ConvertToCharsTest_430, WidthEqualToValueDigits_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value, 4);

    EXPECT_EQ(result, 4);

    EXPECT_STREQ(buffer, "1234");

}



TEST_F(ConvertToCharsTest_430, WidthGreaterThanValueDigits_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value, 6);

    EXPECT_EQ(result, 6);

    EXPECT_STREQ(buffer, "001234");

}



TEST_F(ConvertToCharsTest_430, ZeroValue_430) {

    size_t value = 0;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value);

    EXPECT_EQ(result, 1);

    EXPECT_STREQ(buffer, "0");

}



TEST_F(ConvertToCharsTest_430, LargeValue_430) {

    size_t value = 9876543210;

    int result = ConvertToChars(buffer, buffer + sizeof(buffer), value);

    EXPECT_EQ(result, 10);

    EXPECT_STREQ(buffer, "9876543210");

}



TEST_F(ConvertToCharsTest_430, BufferTooSmallForWidth_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + 5, value, 10);

    EXPECT_EQ(result, -1);

}



TEST_F(ConvertToCharsTest_430, BufferSizeExactlyTwenty_430) {

    size_t value = 9876543210;

    int result = ConvertToChars(buffer, buffer + 20, value);

    EXPECT_EQ(result, 10);

    EXPECT_STREQ(buffer, "9876543210");

}



TEST_F(ConvertToCharsTest_430, BufferSizeLessThanTwenty_430) {

    size_t value = 1234;

    int result = ConvertToChars(buffer, buffer + 19, value);

    EXPECT_EQ(result, -1);

}
