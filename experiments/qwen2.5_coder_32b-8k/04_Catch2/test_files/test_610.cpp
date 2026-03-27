#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_610 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string test_string = "\x1b[31mHello\x1b[0m World!";

};



TEST_F(AnsiSkippingStringTest_610, ConstructorFromLValue_610) {

    AnsiSkippingString ans(test_string);

    EXPECT_EQ(ans.size(), 12); // "Hello World!" has 12 characters without ANSI codes

}



TEST_F(AnsiSkippingStringTest_610, ConstructorFromRValue_610) {

    std::string rvalue_test_string = "\x1b[31mHello\x1b[0m World!";

    AnsiSkippingString ans(std::move(rvalue_test_string));

    EXPECT_EQ(ans.size(), 12); // "Hello World!" has 12 characters without ANSI codes

}



TEST_F(AnsiSkippingStringTest_610, BeginEndIterator_610) {

    AnsiSkippingString ans(test_string);

    auto begin = ans.begin();

    auto end = ans.end();

    EXPECT_NE(begin, end); // Check that iterators are not equal



    std::string result;

    for (auto it = begin; it != end; ++it) {

        result += *it;

    }

    EXPECT_EQ(result, "Hello World!"); // Result without ANSI codes

}



TEST_F(AnsiSkippingStringTest_610, SubstringBasic_610) {

    AnsiSkippingString ans(test_string);

    auto begin = ans.begin();

    std::advance(begin, 6); // Move to 'W'

    auto end = ans.end();



    std::string result = ans.substring(begin, end);

    EXPECT_EQ(result, "World!"); // Substring from 'W' to the end

}



TEST_F(AnsiSkippingStringTest_610, SizeBoundaryCondition_610) {

    AnsiSkippingString emptyAns("");

    EXPECT_EQ(emptyAns.size(), 0); // Empty string should have size 0



    AnsiSkippingString singleCharAns("A");

    EXPECT_EQ(singleCharAns.size(), 1); // Single character should have size 1

}



TEST_F(AnsiSkippingStringTest_610, SubstringBoundaryCondition_610) {

    AnsiSkippingString ans(test_string);

    auto begin = ans.begin();

    auto end = ans.end();



    std::string result = ans.substring(begin, begin); // Empty substring

    EXPECT_EQ(result, "");



    result = ans.substring(end, end); // Empty substring from end to end

    EXPECT_EQ(result, "");

}



TEST_F(AnsiSkippingStringTest_610, SubstringInvalidRange_610) {

    AnsiSkippingString ans(test_string);

    auto begin = ans.begin();

    std::advance(begin, 7); // Move to 'o'

    auto end = ans.end();

    std::advance(end, -2); // Move end two characters before the actual end



    EXPECT_THROW(ans.substring(end, begin), std::invalid_argument); // Invalid range

}
