#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"



class VisibleInputCharsIteratorTest : public ::testing::Test {

protected:

    std::string input = "Hello, World!";

    VisibleInputCharsIterator iterator;



    VisibleInputCharsIteratorTest() : iterator(input) {}

};



TEST_F(VisibleInputCharsIteratorTest_102, HasChar_ReturnsTrueForNonEmptyString_102) {

    EXPECT_TRUE(iterator.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_102, HasChar_ReturnsFalseAfterReachingEnd_102) {

    while (iterator.HasChar()) {

        iterator.NextChar();

    }

    EXPECT_FALSE(iterator.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_102, InputIndex_IncreasesWithNextChar_102) {

    size_t initial_index = iterator.InputIndex();

    iterator.NextChar();

    EXPECT_EQ(initial_index + 1, iterator.InputIndex());

}



TEST_F(VisibleInputCharsIteratorTest_102, VisiblePosition_IncreasesWithNextCharIfVisible_102) {

    size_t initial_visible_pos = iterator.VisiblePosition();

    while (iterator.HasChar() && !iterator.IsVisible()) {

        iterator.NextChar();

    }

    if (iterator.HasChar()) {

        iterator.NextChar();

        EXPECT_EQ(initial_visible_pos + 1, iterator.VisiblePosition());

    }

}



TEST_F(VisibleInputCharsIteratorTest_102, IsVisible_ReturnsTrueForNonAnsiCharacters_102) {

    while (iterator.HasChar() && !iterator.IsVisible()) {

        iterator.NextChar();

    }

    EXPECT_TRUE(iterator.IsVisible());

}



TEST_F(VisibleInputCharsIteratorTest_102, NextChar_DoesNotCrashAtEndOfInput_102) {

    while (iterator.HasChar()) {

        iterator.NextChar();

    }

    // This should not cause any issues

    iterator.NextChar();

}
