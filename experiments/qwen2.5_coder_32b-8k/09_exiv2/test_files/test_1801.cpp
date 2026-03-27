#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/futils.cpp"



namespace {



TEST(urlencodeTest_1801, NormalOperation_1801) {

    EXPECT_EQ(Exiv2::urlencode("HelloWorld"), "HelloWorld");

}



TEST(urlencodeTest_1801, SpacesAreEncodedAsPlus_1801) {

    EXPECT_EQ(Exiv2::urlencode("Hello World"), "Hello+World");

}



TEST(urlencodeTest_1801, SpecialCharactersArePercentEncoded_1801) {

    EXPECT_EQ(Exiv2::urlencode("Hello!@#$%^&*()World"), "Hello%21%40%23%24%25%5E%26%2A%28%29World");

}



TEST(urlencodeTest_1801, PercentSignIsEncoded_1801) {

    EXPECT_EQ(Exiv2::urlencode("Hello%World"), "Hello%25World");

}



TEST(urlencodeTest_1801, BoundaryConditionEmptyString_1801) {

    EXPECT_EQ(Exiv2::urlencode(""), "");

}



TEST(urlencodeTest_1801, BoundaryConditionSingleCharacterAlnum_1801) {

    EXPECT_EQ(Exiv2::urlencode("A"), "A");

}



TEST(urlencodeTest_1801, BoundaryConditionSingleCharacterSpace_1801) {

    EXPECT_EQ(Exiv2::urlencode(" "), "+");

}



TEST(urlencodeTest_1801, BoundaryConditionSingleSpecialCharacter_1801) {

    EXPECT_EQ(Exiv2::urlencode("!"), "%21");

}



TEST(urlencodeTest_1801, LongString_1801) {

    std::string longString(_MAX_PATH, 'a');

    std::string expected(_MAX_PATH, 'a');

    EXPECT_EQ(Exiv2::urlencode(longString), expected);

}



} // namespace
