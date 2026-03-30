#include <gtest/gtest.h>

#include <catch2/internal/catch_string_manip.hpp>



class TrimTest_592 : public ::testing::Test {

protected:

    using StringManip = Catch;

};



TEST_F(TrimTest_592, TrimEmptyString_592) {

    std::string input = "";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "");

}



TEST_F(TrimTest_592, TrimNoWhitespace_592) {

    std::string input = "Hello";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "Hello");

}



TEST_F(TrimTest_592, TrimLeadingWhitespace_592) {

    std::string input = "   Hello";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "Hello");

}



TEST_F(TrimTest_592, TrimTrailingWhitespace_592) {

    std::string input = "Hello   ";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "Hello");

}



TEST_F(TrimTest_592, TrimBothWhitespace_592) {

    std::string input = "   Hello   ";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "Hello");

}



TEST_F(TrimTest_592, TrimAllWhitespace_592) {

    std::string input = "     ";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "");

}



TEST_F(TrimTest_592, TrimMixedWhitespaceCharacters_592) {

    std::string input = "\t\n\r Hello \n\t\r";

    std::string result = StringManip::trim(input);

    EXPECT_EQ(result, "Hello");

}
