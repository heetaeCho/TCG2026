#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class definition is in a header file named elide_middle.h

#include "elide_middle.h"



class AnsiColorSequenceIteratorTest_170 : public ::testing::Test {

protected:

    std::string input;

    AnsiColorSequenceIterator* iterator;



    void SetUp() override {

        input = "\x1b[31mHello\x1b[0m World";

        iterator = new AnsiColorSequenceIterator(input);

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(AnsiColorSequenceIteratorTest_170, HasSequenceInitiallyTrue_170) {

    EXPECT_TRUE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_170, SequenceStartReturnsCorrectValue_170) {

    EXPECT_EQ(iterator->SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_170, SequenceEndReturnsCorrectValue_170) {

    EXPECT_EQ(iterator->SequenceEnd(), 5); // \x1b[31m is 5 characters

}



TEST_F(AnsiColorSequenceIteratorTest_170, SequenceSizeReturnsCorrectValue_170) {

    EXPECT_EQ(iterator->SequenceSize(), 5);

}



TEST_F(AnsiColorSequenceIteratorTest_170, SequenceContainsWorksForContainedIndex_170) {

    EXPECT_TRUE(iterator->SequenceContains(2));

}



TEST_F(AnsiColorSequenceIteratorTest_170, SequenceContainsWorksForNonContainedIndex_170) {

    EXPECT_FALSE(iterator->SequenceContains(6)); // 'H' is at index 6

}



TEST_F(AnsiColorSequenceIteratorTest_170, NextSequenceMovesToNext_170) {

    iterator->NextSequence();

    EXPECT_EQ(iterator->SequenceStart(), 12); // \x1b[0m starts at index 12

    EXPECT_EQ(iterator->SequenceEnd(), 16);

}



TEST_F(AnsiColorSequenceIteratorTest_170, NextSequenceReturnsFalseWhenNoMoreSequences_170) {

    iterator->NextSequence(); // Move to \x1b[0m

    EXPECT_FALSE(iterator->NextSequence()); // No more sequences

}



TEST_F(AnsiColorSequenceIteratorTest_170, ResetResetsToInitialPosition_170) {

    iterator->NextSequence(); // Move to \x1b[0m

    iterator->Reset();

    EXPECT_EQ(iterator->SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_170, HasSequenceFalseWhenNoSequences_170) {

    input = "Hello World";

    delete iterator;

    iterator = new AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_170, BoundaryConditionSingleSequence_170) {

    input = "\x1b[31m";

    delete iterator;

    iterator = new AnsiColorSequenceIterator(input);

    EXPECT_TRUE(iterator->HasSequence());

    EXPECT_EQ(iterator->SequenceStart(), 0);

    EXPECT_EQ(iterator->SequenceEnd(), 5);

}



TEST_F(AnsiColorSequenceIteratorTest_170, BoundaryConditionEmptyString_170) {

    input = "";

    delete iterator;

    iterator = new AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator->HasSequence());

}
