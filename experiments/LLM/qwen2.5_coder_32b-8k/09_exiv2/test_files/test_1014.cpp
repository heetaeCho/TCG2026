#include <gtest/gtest.h>

#include <string>



namespace Exiv2 { namespace Internal {

    static std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");

} }



class RtrimTest : public ::testing::Test {

protected:

    std::string testString;

};



TEST_F(RtrimTest_1014, NormalOperation_1014) {

    testString = "test string   ";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("test string", testString);

}



TEST_F(RtrimTest_1014, NoTrailingWhitespace_1014) {

    testString = "teststring";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("teststring", testString);

}



TEST_F(RtrimTest_1014, AllWhitespace_1014) {

    testString = "     ";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("", testString);

}



TEST_F(RtrimTest_1014, MixedCharacters_1014) {

    testString = "a b c d e f g   ";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("a b c d e f g", testString);

}



TEST_F(RtrimTest_1014, DifferentWhitespaceChars_1014) {

    testString = "test string\t\n\r\f\v";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("test string", testString);

}



TEST_F(RtrimTest_1014, EmptyString_1014) {

    testString = "";

    Exiv2::Internal::rtrim(testString);

    EXPECT_EQ("", testString);

}
