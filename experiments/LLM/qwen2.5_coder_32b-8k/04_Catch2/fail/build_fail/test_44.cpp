#include <gtest/gtest.h>

#include <catch2/internal/catch_textflow.hpp>



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_44 : public ::testing::Test {

protected:

    std::string testString = "This is a test string with some ansi \033[1mescapes\033[0m.";

    AnsiSkippingString ansiSkippingString = AnsiSkippingString(testString);

    AnsiSkippingString::const_iterator it;



    void SetUp() override {

        it = ansiSkippingString.begin();

    }

};



TEST_F(AnsiSkippingStringTest_44, BeginAtStart_44) {

    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest_44, IncrementOperatorAdvances_44) {

    ++it;

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest_44, PostIncrementOperatorAdvances_44) {

    it++;

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest_44, DecrementOperatorRetreats_44) {

    ++it;

    --it;

    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest_44, PostDecrementOperatorRetreats_44) {

    ++it;

    it--;

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest_44, OneBeforeReturnsPreviousIterator_44) {

    ++it;

    auto prevIt = it.oneBefore();

    EXPECT_EQ(*prevIt, 'T');

}



TEST_F(AnsiSkippingStringTest_44, EqualityOperatorTrueForSamePosition_44) {

    auto it2 = ansiSkippingString.begin();

    EXPECT_TRUE(it == it2);

}



TEST_F(AnsiSkippingStringTest_44, InequalityOperatorFalseForSamePosition_44) {

    auto it2 = ansiSkippingString.begin();

    EXPECT_FALSE(it != it2);

}



TEST_F(AnsiSkippingStringTest_44, LessThanEqualOperatorTrueForSamePosition_44) {

    auto it2 = ansiSkippingString.begin();

    EXPECT_TRUE(it <= it2);

}



TEST_F(AnsiSkippingStringTest_44, LessThanEqualOperatorTrueForPreviousPosition_44) {

    ++it;

    EXPECT_TRUE(it.oneBefore() <= it);

}



TEST_F(AnsiSkippingStringTest_44, DereferenceOperatorReturnsChar_44) {

    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest_44, IteratorEndCondition_44) {

    for (; it != ansiSkippingString.end(); ++it);

    EXPECT_TRUE(it == ansiSkippingString.end());

}
