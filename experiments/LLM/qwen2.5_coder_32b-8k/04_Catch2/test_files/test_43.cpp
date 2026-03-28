#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_43 : public ::testing::Test {

protected:

    const std::string testString = "Hello, World!";

    AnsiSkippingString::const_iterator begin;

    AnsiSkippingString::const_iterator end;



    void SetUp() override {

        begin = AnsiSkippingString::const_iterator(testString);

        end = AnsiSkippingString::const_iterator(testString, AnsiSkippingString::EndTag());

    }

};



TEST_F(AnsiSkippingStringTest_43, ConstructorInitializesIteratorToBeginning_43) {

    EXPECT_EQ(*begin, 'H');

}



TEST_F(AnsiSkippingStringTest_43, EndConstructorSetsIteratorToEnd_43) {

    EXPECT_EQ(end.m_it, testString.end());

}



TEST_F(AnsiSkippingStringTest_43, PreIncrementOperatorMovesToNextCharacter_43) {

    ++begin;

    EXPECT_EQ(*begin, 'e');

}



TEST_F(AnsiSkippingStringTest_43, PostIncrementOperatorMovesToNextCharacter_43) {

    auto oldBegin = begin++;

    EXPECT_EQ(*oldBegin, 'H');

    EXPECT_EQ(*begin, 'e');

}



TEST_F(AnsiSkippingStringTest_43, PreDecrementOperatorMovesToPreviousCharacter_43) {

    ++begin;

    --begin;

    EXPECT_EQ(*begin, 'H');

}



TEST_F(AnsiSkippingStringTest_43, PostDecrementOperatorMovesToPreviousCharacter_43) {

    ++begin;

    auto oldBegin = begin--;

    EXPECT_EQ(*oldBegin, 'e');

    EXPECT_EQ(*begin, 'H');

}



TEST_F(AnsiSkippingStringTest_43, EqualityOperatorReturnsTrueForSameIterator_43) {

    EXPECT_TRUE(begin == begin);

}



TEST_F(AnsiSkippingStringTest_43, InequalityOperatorReturnsFalseForSameIterator_43) {

    EXPECT_FALSE(begin != begin);

}



TEST_F(AnsiSkippingStringTest_43, EqualityOperatorReturnsFalseForDifferentIterators_43) {

    ++begin;

    EXPECT_FALSE(begin == end);

}



TEST_F(AnsiSkippingStringTest_43, InequalityOperatorReturnsTrueForDifferentIterators_43) {

    ++begin;

    EXPECT_TRUE(begin != end);

}



TEST_F(AnsiSkippingStringTest_43, LessThanOrEqualToOperatorReturnsTrueForEqualIterators_43) {

    EXPECT_TRUE(begin <= begin);

}



TEST_F(AnsiSkippingStringTest_43, LessThanOrEqualToOperatorReturnsTrueForLesserIterator_43) {

    EXPECT_TRUE(begin <= end);

}



TEST_F(AnsiSkippingStringTest_43, LessThanOrEqualToOperatorReturnsFalseForGreaterIterator_43) {

    ++begin;

    EXPECT_FALSE(end <= begin);

}
