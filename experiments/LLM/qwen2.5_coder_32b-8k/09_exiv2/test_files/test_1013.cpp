#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "minoltamn_int.cpp"



using namespace Exiv2::Internal;



TEST(ltrimTest_1013, NormalOperation_RemovesLeadingSpaces_1013) {

    std::string input = "   Hello World";

    std::string expectedOutput = "Hello World";

    EXPECT_EQ(expectedOutput, ltrim(input));

}



TEST(ltrimTest_1013, BoundaryCondition_EmptyString_1013) {

    std::string input = "";

    std::string expectedOutput = "";

    EXPECT_EQ(expectedOutput, ltrim(input));

}



TEST(ltrimTest_1013, NormalOperation_RemovesLeadingTabsAndSpaces_1013) {

    std::string input = "\t  \nHello World";

    std::string expectedOutput = "Hello World";

    EXPECT_EQ(expectedOutput, ltrim(input));

}



TEST(ltrimTest_1013, BoundaryCondition_StringWithoutLeadingWhitespace_1013) {

    std::string input = "Hello World";

    std::string expectedOutput = "Hello World";

    EXPECT_EQ(expectedOutput, ltrim(input));

}



TEST(ltrimTest_1013, NormalOperation_RemovesAllCharactersIfAllAreTrimmed_1013) {

    std::string input = " \t\n\r\f\v";

    std::string expectedOutput = "";

    EXPECT_EQ(expectedOutput, ltrim(input));

}
