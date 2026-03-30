#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    std::string testString = "Sample text \033[1;34mwith ANSI codes\033[0m";

};



TEST_F(AnsiSkippingStringTest_NormalOperation_1092, ConstructorWithLvalue_1092) {

    AnsiSkippingString ans(testString);

    EXPECT_EQ(ans.size(), testString.length() - 5); // Subtracting the length of ANSI escape codes

}



TEST_F(AnsiSkippingStringTest_NormalOperation_1092, ConstructorWithRvalue_1092) {

    std::string rvalueStr = "Another sample \033[32mgreen text\033[0m";

    AnsiSkippingString ans(std::move(rvalueStr));

    EXPECT_EQ(ans.size(), 23); // Length of the string without ANSI codes

}



TEST_F(AnsiSkippingStringTest_BoundaryConditions_1092, EmptyString_1092) {

    std::string emptyString = "";

    AnsiSkippingString ans(emptyString);

    EXPECT_EQ(ans.size(), 0);

}



TEST_F(AnsiSkippingStringTest_BoundaryConditions_1092, OnlyANSICodes_1092) {

    std::string ansiOnly = "\033[1;34m\033[0m";

    AnsiSkippingString ans(ansiOnly);

    EXPECT_EQ(ans.size(), 0);

}



TEST_F(AnsiSkippingStringTest_ExceptionalCases_1092, InvalidANSICodes_1092) {

    std::string invalidAnsi = "Text with \033[ invalid code";

    AnsiSkippingString ans(invalidAnsi);

    EXPECT_EQ(ans.size(), 18); // Length of the string without the incomplete ANSI code

}



TEST_F(AnsiSkippingStringTest_NormalOperation_1092, SubstringWithIterator_1092) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.end();

    std::string result = ans.substring(begin, end);

    EXPECT_EQ(result, "Sample text with ANSI codes");

}



TEST_F(AnsiSkippingStringTest_NormalOperation_1092, SubstringWithIteratorPartial_1092) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    std::advance(begin, 7); // Move iterator to the start of "text"

    auto end = begin;

    std::advance(end, 4); // Move iterator to the end of "text"

    std::string result = ans.substring(begin, end);

    EXPECT_EQ(result, "text");

}



TEST_F(AnsiSkippingStringTest_NormalOperation_1092, BeginEndIteratorEquality_1092) {

    AnsiSkippingString ans(testString);

    EXPECT_EQ(ans.begin(), ans.end());

}



TEST_F(AnsiSkippingStringTest_ExceptionalCases_1092, IteratorPastEnd_1092) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.end();

    std::advance(begin, 100); // Move iterator far past the end

    EXPECT_EQ(ans.substring(begin, end), "");

}
