#include <gtest/gtest.h>

#include "exiv2/types.hpp"



class StringToTest : public ::testing::Test {

protected:

    bool ok;

};



TEST_F(StringToTest_35, ConvertValidInteger_35) {

    std::string input = "123";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 123);

}



TEST_F(StringToTest_35, ConvertNegativeInteger_35) {

    std::string input = "-456";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, -456);

}



TEST_F(StringToTest_35, ConvertValidDouble_35) {

    std::string input = "123.45";

    double result = Exiv2::stringTo<double>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_DOUBLE_EQ(result, 123.45);

}



TEST_F(StringToTest_35, ConvertInvalidString_35) {

    std::string input = "abc";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0); // Default value for failed conversion

}



TEST_F(StringToTest_35, ConvertEmptyString_35) {

    std::string input = "";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0); // Default value for failed conversion

}



TEST_F(StringToTest_35, ConvertTrailingCharacters_35) {

    std::string input = "123abc";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0); // Default value for failed conversion

}



TEST_F(StringToTest_35, ConvertLeadingSpacesInteger_35) {

    std::string input = "   456";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 456);

}



TEST_F(StringToTest_35, ConvertTrailingSpacesInteger_35) {

    std::string input = "789   ";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 789);

}



TEST_F(StringToTest_35, ConvertLeadingAndTrailingSpacesInteger_35) {

    std::string input = "   101   ";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 101);

}



TEST_F(StringToTest_35, ConvertMixedSpacesAndValidInteger_35) {

    std::string input = "   202abc";

    int result = Exiv2::stringTo<int>(input, ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0); // Default value for failed conversion

}
