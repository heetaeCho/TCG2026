#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    const std::string testString = "This is a test string with some ansi escapes \x1b[31mred\x1b[0m and \x1b[32mgreen\x1b[0m.";

};



TEST_F(AnsiSkippingStringTest, ConstructorInitializesCorrectly_37) {

    const_iterator it(testString);

    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest, OperatorStarReturnsCurrentChar_37) {

    const_iterator it(testString);

    EXPECT_EQ(*it, 'T');

    ++it;

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest, OperatorIncrementAdvancesIterator_37) {

    const_iterator it(testString);

    EXPECT_EQ(*it, 'T');

    ++it;

    EXPECT_EQ(*it, 'h');

    it++;

    EXPECT_EQ(*it, 'i');

}



TEST_F(AnsiSkippingStringTest, OperatorDecrementMovesBackIterator_37) {

    const_iterator it(testString.begin() + 5); // Move to the space after "This"

    --it;

    EXPECT_EQ(*it, 's');

    it--;

    EXPECT_EQ(*it, 'i');

}



TEST_F(AnsiSkippingStringTest, OperatorEqualityComparesIterators_37) {

    const_iterator it1(testString);

    const_iterator it2(testString);

    EXPECT_TRUE(it1 == it2);



    ++it1;

    EXPECT_FALSE(it1 == it2);

}



TEST_F(AnsiSkippingStringTest, OperatorInequalityComparesIterators_37) {

    const_iterator it1(testString);

    const_iterator it2(testString);

    EXPECT_FALSE(it1 != it2);



    ++it1;

    EXPECT_TRUE(it1 != it2);

}



TEST_F(AnsiSkippingStringTest, OperatorLessThanEqualComparesIterators_37) {

    const_iterator it1(testString);

    const_iterator it2(testString);

    EXPECT_TRUE(it1 <= it2);



    ++it1;

    EXPECT_FALSE(it1 <= it2);



    --it1;

    EXPECT_TRUE(it1 <= it2);

}



TEST_F(AnsiSkippingStringTest, OneBeforeReturnsPreviousIterator_37) {

    const_iterator it(testString.begin() + 5); // Move to the space after "This"

    const_iterator prev = it.oneBefore();

    EXPECT_EQ(*prev, 's');

}
