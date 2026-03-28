#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.h"



class AnsiColorSequenceIteratorTest : public ::testing::Test {

protected:

    std::string input = "\033[31mHello\033[0m World";

    AnsiColorSequenceIterator iterator{input};

};



TEST_F(AnsiColorSequenceIteratorTest_101, HasSequenceInitiallyTrue_101) {

    EXPECT_TRUE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_101, SequenceStartCorrect_101) {

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_101, SequenceEndCorrect_101) {

    EXPECT_EQ(iterator.SequenceEnd(), 5); // End of "\033[31m"

}



TEST_F(AnsiColorSequenceIteratorTest_101, SequenceSizeCorrect_101) {

    EXPECT_EQ(iterator.SequenceSize(), 5); // Length of "\033[31m"

}



TEST_F(AnsiColorSequenceIteratorTest_101, NextSequenceFindsNext_101) {

    iterator.NextSequence();

    EXPECT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceStart(), 14); // Start of "\033[0m"

    EXPECT_EQ(iterator.SequenceEnd(), 18);   // End of "\033[0m"

}



TEST_F(AnsiColorSequenceIteratorTest_101, NextSequenceNoMoreSequences_101) {

    iterator.NextSequence();

    iterator.NextSequence();

    EXPECT_FALSE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_101, ResetResetsIterator_101) {

    iterator.NextSequence();

    iterator.Reset();

    EXPECT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceStart(), 0);

    EXPECT_EQ(iterator.SequenceEnd(), 5); // End of "\033[31m"

}



TEST_F(AnsiColorSequenceIteratorTest_101, SequenceContainsTrue_101) {

    EXPECT_TRUE(iterator.SequenceContains(2)); // Inside the first sequence

}



TEST_F(AnsiColorSequenceIteratorTest_101, SequenceContainsFalse_101) {

    EXPECT_FALSE(iterator.SequenceContains(6)); // After the first sequence

}



TEST_F(AnsiColorSequenceIteratorTest_101, EmptyInputNoSequences_101) {

    AnsiColorSequenceIterator empty_iterator{""};

    EXPECT_FALSE(empty_iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_101, NoAnsiCodesNoSequences_101) {

    AnsiColorSequenceIterator no_codes_iterator{"Hello World"};

    EXPECT_FALSE(no_codes_iterator.HasSequence());

}
