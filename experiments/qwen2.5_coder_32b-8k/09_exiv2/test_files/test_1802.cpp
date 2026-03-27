#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "./TestProjects/exiv2/src/futils.cpp"



using namespace Exiv2;



// Test fixture for urldecode function

class UrlDecodeTest_1802 : public ::testing::Test {

protected:

    std::string testString;

};



TEST_F(UrlDecodeTest_1802, NormalOperation_1802) {

    testString = "Hello%20World%21";

    urldecode(testString);

    EXPECT_EQ("Hello World!", testString);

}



TEST_F(UrlDecodeTest_1802, NoEncoding_1802) {

    testString = "NoEncodingHere";

    urldecode(testString);

    EXPECT_EQ("NoEncodingHere", testString);

}



TEST_F(UrlDecodeTest_1802, PlusSignHandling_1802) {

    testString = "Hello+World";

    urldecode(testString);

    EXPECT_EQ("Hello World", testString);

}



TEST_F(UrlDecodeTest_1802, MixedEncoding_1802) {

    testString = "A%2B%20B%25C";

    urldecode(testString);

    EXPECT_EQ("A+B %C", testString);

}



TEST_F(UrlDecodeTest_1802, BoundaryCondition_EmptyString_1802) {

    testString = "";

    urldecode(testString);

    EXPECT_EQ("", testString);

}



TEST_F(UrlDecodeTest_1802, BoundaryCondition_SingleCharacterEncoded_1802) {

    testString = "%41";

    urldecode(testString);

    EXPECT_EQ("A", testString);

}



TEST_F(UrlDecodeTest_1802, BoundaryCondition_SinglePlusSign_1802) {

    testString = "+";

    urldecode(testString);

    EXPECT_EQ(" ", testString);

}



TEST_F(UrlDecodeTest_1802, ErrorHandling_IncompleteHexSequence_1802) {

    testString = "%4";

    urldecode(testString);

    EXPECT_EQ("%4", testString);

}



TEST_F(UrlDecodeTest_1802, ErrorHandling_NonHexCharacters_1802) {

    testString = "%G7";

    urldecode(testString);

    EXPECT_EQ("%G7", testString);

}
