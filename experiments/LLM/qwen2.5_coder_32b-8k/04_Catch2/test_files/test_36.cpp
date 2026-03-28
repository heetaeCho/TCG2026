#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest_36 : public ::testing::Test {

protected:

    std::string testString = "Hello, world!";

    AnsiSkippingString ansiSkippingString = AnsiSkippingString(testString);

    AnsiSkippingString::const_iterator begin;

    AnsiSkippingString::const_iterator end;



    void SetUp() override {

        begin = ansiSkippingString.begin();

        end = ansiSkippingString.end();

    }

};



TEST_F(AnsiSkippingStringTest_36, DereferenceOperatorReturnsCorrectCharacter_36) {

    EXPECT_EQ(*begin, 'H');

}



TEST_F(AnsiSkippingStringTest_36, PostIncrementOperatorAdvancesIterator_36) {

    auto current = begin;

    auto next = begin++;

    EXPECT_EQ(*next, 'H');

    EXPECT_EQ(*current, 'e');

}



TEST_F(AnsiSkippingStringTest_36, PreIncrementOperatorAdvancesIterator_36) {

    auto& next = ++begin;

    EXPECT_EQ(*next, 'e');

}



TEST_F(AnsiSkippingStringTest_36, PostDecrementOperatorMovesIteratorBackward_36) {

    ++begin; // Move to 'e'

    auto current = begin;

    auto prev = begin--;

    EXPECT_EQ(*prev, 'e');

    EXPECT_EQ(*current, 'H');

}



TEST_F(AnsiSkippingStringTest_36, PreDecrementOperatorMovesIteratorBackward_36) {

    ++begin; // Move to 'e'

    auto& prev = --begin;

    EXPECT_EQ(*prev, 'H');

}



TEST_F(AnsiSkippingStringTest_36, EqualityOperatorsWorkCorrectly_36) {

    auto otherBegin = ansiSkippingString.begin();

    EXPECT_TRUE(begin == otherBegin);

    EXPECT_FALSE(begin != otherBegin);



    ++otherBegin; // Move to 'e'

    EXPECT_FALSE(begin == otherBegin);

    EXPECT_TRUE(begin != otherBegin);

}



TEST_F(AnsiSkippingStringTest_36, LessThanOrEqualToOperatorWorksCorrectly_36) {

    auto otherBegin = ansiSkippingString.begin();

    EXPECT_TRUE(begin <= otherBegin);



    ++otherBegin; // Move to 'e'

    EXPECT_TRUE(begin <= otherBegin);

    EXPECT_FALSE(otherBegin <= begin);

}



TEST_F(AnsiSkippingStringTest_36, OneBeforeReturnsIteratorToPreviousLineStart_36) {

    // This test assumes that the string does not contain any line breaks

    auto oneBefore = begin.oneBefore();

    EXPECT_EQ(oneBefore, begin); // Since there's no previous line start



    ++begin; // Move to 'e'

    oneBefore = begin.oneBefore();

    EXPECT_EQ(*oneBefore, 'H');

}



TEST_F(AnsiSkippingStringTest_36, IteratorAtEndIsEqualToEndIterator_36) {

    while (begin != end) {

        ++begin;

    }

    EXPECT_TRUE(begin == end);

}
