#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"  // Adjust include path as necessary



using ::testing::Eq;



class VisibleInputCharsIteratorTest : public ::testing::Test {

protected:

    std::string test_input = "Hello, World!";

    VisibleInputCharsIterator iterator{test_input};

};



TEST_F(VisibleInputCharsIteratorTest_103, InitialStateHasChar_103) {

    EXPECT_TRUE(iterator.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_103, InitialStateInputIndex_103) {

    EXPECT_EQ(iterator.InputIndex(), 0);

}



TEST_F(VisibleInputCharsIteratorTest_103, NextCharAdvancesIndex_103) {

    iterator.NextChar();

    EXPECT_EQ(iterator.InputIndex(), 1);

}



TEST_F(VisibleInputCharsIteratorTest_103, EndStateHasNoChar_103) {

    for (size_t i = 0; i < test_input.size(); ++i) {

        iterator.NextChar();

    }

    EXPECT_FALSE(iterator.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_103, EndStateInputIndexMatchesSize_103) {

    for (size_t i = 0; i < test_input.size(); ++i) {

        iterator.NextChar();

    }

    EXPECT_EQ(iterator.InputIndex(), test_input.size());

}



TEST_F(VisibleInputCharsIteratorTest_103, BoundaryConditionSingleCharacterString_103) {

    VisibleInputCharsIterator single_char_iterator{"A"};

    EXPECT_TRUE(single_char_iterator.HasChar());

    EXPECT_EQ(single_char_iterator.InputIndex(), 0);

    single_char_iterator.NextChar();

    EXPECT_FALSE(single_char_iterator.HasChar());

    EXPECT_EQ(single_char_iterator.InputIndex(), 1);

}



TEST_F(VisibleInputCharsIteratorTest_103, BoundaryConditionEmptyString_103) {

    VisibleInputCharsIterator empty_string_iterator{""};

    EXPECT_FALSE(empty_string_iterator.HasChar());

    EXPECT_EQ(empty_string_iterator.InputIndex(), 0);

    empty_string_iterator.NextChar(); // Should not change state

    EXPECT_FALSE(empty_string_iterator.HasChar());

    EXPECT_EQ(empty_string_iterator.InputIndex(), 0);

}
