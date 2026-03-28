#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"  // Adjust the include path as necessary



class VisibleInputCharsIteratorTest : public ::testing::Test {

protected:

    std::string test_input;

    VisibleInputCharsIterator* iterator;



    void SetUp() override {

        test_input = "Hello \033[1mWorld\033[0m!";  // Example input with ANSI escape codes

        iterator = new VisibleInputCharsIterator(test_input);

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(VisibleInputCharsIteratorTest_104, InitialStateHasChar_104) {

    EXPECT_TRUE(iterator->HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_104, InitialStateVisiblePositionZero_104) {

    EXPECT_EQ(iterator->VisiblePosition(), 0);

}



TEST_F(VisibleInputCharsIteratorTest_104, InitialStateInputIndexZero_104) {

    EXPECT_EQ(iterator->InputIndex(), 0);

}



TEST_F(VisibleInputCharsIteratorTest_104, NextCharAdvancesInputIndex_104) {

    iterator->NextChar();

    EXPECT_EQ(iterator->InputIndex(), 1);

}



TEST_F(VisibleInputCharsIteratorTest_104, NextCharAdvancesVisiblePositionForVisibleChar_104) {

    iterator->NextChar();  // 'H'

    EXPECT_EQ(iterator->VisiblePosition(), 1);

}



TEST_F(VisibleInputCharsIteratorTest_104, NextCharDoesNotAdvanceVisiblePositionForAnsiCode_104) {

    for (int i = 0; i < 2; ++i) {  // Move through "Hello "

        iterator->NextChar();

    }

    EXPECT_EQ(iterator->VisiblePosition(), 6);

    iterator->NextChar();  // First character of ANSI code

    EXPECT_EQ(iterator->VisiblePosition(), 6);

}



TEST_F(VisibleInputCharsIteratorTest_104, EndOfInputHasNoChar_104) {

    while (iterator->HasChar()) {

        iterator->NextChar();

    }

    EXPECT_FALSE(iterator->HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_104, IsVisibleReturnsTrueForRegularCharacter_104) {

    EXPECT_TRUE(iterator->IsVisible());  // 'H'

}



TEST_F(VisibleInputCharsIteratorTest_104, IsVisibleReturnsFalseForAnsiCode_104) {

    for (int i = 0; i < 6; ++i) {  // Move through "Hello "

        iterator->NextChar();

    }

    EXPECT_FALSE(iterator->IsVisible());  // First character of ANSI code

}



TEST_F(VisibleInputCharsIteratorTest_104, IsVisibleReturnsTrueAfterAnsiCode_104) {

    for (int i = 0; i < 6; ++i) {  // Move through "Hello "

        iterator->NextChar();

    }

    while (!iterator->IsVisible()) {

        iterator->NextChar();  // Skip ANSI code

    }

    EXPECT_TRUE(iterator->IsVisible());  // 'W'

}
