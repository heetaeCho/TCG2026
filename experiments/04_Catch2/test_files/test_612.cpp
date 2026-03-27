#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_612 : public ::testing::Test {

protected:

    void SetUp() override {

        testString = "Hello\x1b[31mWorld\x1bm";

    }



    std::string testString;

};



TEST_F(AnsiSkippingStringTest_612, ConstructorFromString_612) {

    AnsiSkippingString ans(testString);

    EXPECT_EQ(ans.size(), 11); // Size should be the length of the original string

}



TEST_F(AnsiSkippingStringTest_612, ConstructorFromRValueString_612) {

    std::string rvalueString = testString;

    AnsiSkippingString ans(std::move(rvalueString));

    EXPECT_EQ(ans.size(), 11); // Size should be the length of the original string

}



TEST_F(AnsiSkippingStringTest_612, SubstringWithoutAnsiCodes_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    std::advance(begin, 5);

    auto end = ans.end();

    std::advance(end, -1); // Move end one before the last character to exclude 'm'

    EXPECT_EQ(ans.substring(begin, end), "World");

}



TEST_F(AnsiSkippingStringTest_612, SubstringWithEntireString_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.end();

    std::advance(end, -1); // Move end one before the last character to exclude 'm'

    EXPECT_EQ(ans.substring(begin, end), "HelloWorld");

}



TEST_F(AnsiSkippingStringTest_612, SubstringEmptyRange_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.begin(); // Same as begin

    EXPECT_EQ(ans.substring(begin, end), "");

}



TEST_F(AnsiSkippingStringTest_612, SubstringSingleCharacter_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    std::advance(begin, 7); // Move to 'W'

    auto end = ans.begin();

    std::advance(end, 8); // Move to after 'W'

    EXPECT_EQ(ans.substring(begin, end), "W");

}



TEST_F(AnsiSkippingStringTest_612, SubstringBoundaryConditionStart_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.begin();

    std::advance(end, 1); // Move to after 'H'

    EXPECT_EQ(ans.substring(begin, end), "H");

}



TEST_F(AnsiSkippingStringTest_612, SubstringBoundaryConditionEnd_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.end();

    std::advance(begin, -2); // Move to before 'm'

    auto end = ans.end();

    std::advance(end, -1); // Move to the last character

    EXPECT_EQ(ans.substring(begin, end), "m");

}



TEST_F(AnsiSkippingStringTest_612, SubstringEntireWithSentinelReplaced_612) {

    AnsiSkippingString ans(testString);

    auto begin = ans.begin();

    auto end = ans.end();

    std::advance(end, -1); // Move end one before the last character to exclude 'm'

    EXPECT_EQ(ans.substring(begin, end), "HelloWorld");

}
