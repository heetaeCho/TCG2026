#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    std::string testString = "This is a test string with \x1b[31mansi\x1b[0m codes.";

};



TEST_F(AnsiSkippingStringTest, ConstructorInitializesIterator_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it(ansiString);



    EXPECT_EQ(*it, 'T');

}



TEST_F(AnsiSkippingStringTest, IteratorAdvancesCorrectly_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it(ansiString);



    ++it;

    EXPECT_EQ(*it, 'h');



    it++;

    EXPECT_EQ(*it, 'i');

}



TEST_F(AnsiSkippingStringTest, IteratorDoesNotAdvanceBeyondEnd_1047) {

    std::string singleCharString = "A";

    AnsiSkippingString ansiString(singleCharString);

    AnsiSkippingString::const_iterator it(ansiString);



    ++it;

    EXPECT_EQ(it != ansiString.end(), false);

}



TEST_F(AnsiSkippingStringTest, IteratorComparesEqual_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it1(ansiString);

    AnsiSkippingString::const_iterator it2(ansiString);



    EXPECT_EQ(it1 == it2, true);

}



TEST_F(AnsiSkippingStringTest, IteratorComparesNotEqual_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it1(ansiString);

    AnsiSkippingString::const_iterator it2(ansiString);



    ++it2;

    EXPECT_EQ(it1 != it2, true);

}



TEST_F(AnsiSkippingStringTest, IteratorComparesLessThanOrEqual_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it1(ansiString);

    AnsiSkippingString::const_iterator it2(ansiString);



    EXPECT_EQ(it1 <= it2, true);



    ++it2;

    EXPECT_EQ(it1 <= it2, true);



    ++it1;

    EXPECT_EQ(it1 <= it2, true);



    ++it1;

    EXPECT_EQ(it1 <= it2, false);

}



TEST_F(AnsiSkippingStringTest, IteratorDereferencesCorrectly_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it(ansiString);



    EXPECT_EQ(*it, 'T');

    ++it;

    EXPECT_EQ(*it, 'h');

}



TEST_F(AnsiSkippingStringTest, IteratorHandlesEndTag_1047) {

    AnsiSkippingString ansiString(testString);

    AnsiSkippingString::const_iterator it(ansiString, AnsiSkippingString::const_iterator::EndTag());



    EXPECT_EQ(it == ansiString.end(), true);

}



TEST_F(AnsiSkippingStringTest, IteratorSkipsAnsiCodes_1047) {

    std::string stringWithAnsi = "This is \x1b[31mred\x1b[0m text.";

    AnsiSkippingString ansiString(stringWithAnsi);

    AnsiSkippingString::const_iterator it(ansiString);



    for (size_t i = 0; i < 8; ++i) {

        ++it;

    }

    EXPECT_EQ(*it, 'r');



    for (size_t i = 0; i < 3; ++i) {

        ++it;

    }

    EXPECT_EQ(*it, 't');

}
