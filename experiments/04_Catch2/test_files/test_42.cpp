#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    std::string testString = "This is a test string.";

    const_iterator begin;

    const_iterator end;



    void SetUp() override {

        begin = const_iterator(testString);

        end = const_iterator(testString, EndTag());

    }

};



TEST_F(AnsiSkippingStringTest_42, ConstructorInitializesIteratorAtStart_42) {

    EXPECT_EQ(*begin, 'T');

}



TEST_F(AnsiSkippingStringTest_42, PostIncrementOperatorAdvancesIterator_42) {

    const_iterator it = begin;

    EXPECT_EQ(*(it++), 'T');

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest_42, PreIncrementOperatorAdvancesIterator_42) {

    const_iterator it = begin;

    EXPECT_EQ(*(++it), 'h');

}



TEST_F(AnsiSkippingStringTest_42, PostDecrementOperatorDecrementsIterator_42) {

    ++begin; // Move to second character

    const_iterator it = begin;

    EXPECT_EQ(*(it--), 'h');

    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest_42, PreDecrementOperatorDecrementsIterator_42) {

    ++begin; // Move to second character

    const_iterator it = begin;

    EXPECT_EQ(*(--it), 'T');

}



TEST_F(AnsiSkippingStringTest_42, EqualityOperatorReturnsTrueForSamePosition_42) {

    const_iterator it1 = begin;

    const_iterator it2 = begin;

    EXPECT_TRUE(it1 == it2);

}



TEST_F(AnsiSkippingStringTest_42, InequalityOperatorReturnsFalseForSamePosition_42) {

    const_iterator it1 = begin;

    const_iterator it2 = begin;

    EXPECT_FALSE(it1 != it2);

}



TEST_F(AnsiSkippingStringTest_42, EqualityOperatorReturnsFalseForDifferentPositions_42) {

    ++begin; // Move to second character

    EXPECT_TRUE(begin != begin.oneBefore());

}



TEST_F(AnsiSkippingStringTest_42, InequalityOperatorReturnsTrueForDifferentPositions_42) {

    ++begin; // Move to second character

    EXPECT_FALSE(begin == begin.oneBefore());

}



TEST_F(AnsiSkippingStringTest_42, OneBeforeReturnsIteratorToPreviousPosition_42) {

    const_iterator it = begin;

    ++it;

    EXPECT_TRUE(it.oneBefore() == begin);

}
