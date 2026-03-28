#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"



class AnsiColorSequenceIteratorTest_95 : public ::testing::Test {

protected:

    std::string input;

    AnsiColorSequenceIterator iterator;



    void SetUp() override {

        input = "\x1b[31mHello\x1b[0m";

        iterator = AnsiColorSequenceIterator(input);

    }

};



TEST_F(AnsiColorSequenceIteratorTest_95, HasSequence_Init_95) {

    EXPECT_TRUE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_95, SequenceStart_Init_95) {

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_95, SequenceEnd_Init_95) {

    EXPECT_EQ(iterator.SequenceEnd(), 4); // "\x1b[31m" length

}



TEST_F(AnsiColorSequenceIteratorTest_95, SequenceSize_Init_95) {

    EXPECT_EQ(iterator.SequenceSize(), 4);

}



TEST_F(AnsiColorSequenceIteratorTest_95, SequenceContains_ValidIndex_95) {

    EXPECT_TRUE(iterator.SequenceContains(0));

}



TEST_F(AnsiColorSequenceIteratorTest_95, SequenceContains_OutOfBoundsIndex_95) {

    EXPECT_FALSE(iterator.SequenceContains(10));

}



TEST_F(AnsiColorSequenceIteratorTest_95, NextSequence_Success_95) {

    EXPECT_TRUE(iterator.NextSequence());

    EXPECT_EQ(iterator.SequenceStart(), 11); // "Hello" length

    EXPECT_EQ(iterator.SequenceEnd(), 14); // "\x1b[0m" length

}



TEST_F(AnsiColorSequenceIteratorTest_95, NextSequence_EndOfSequences_95) {

    iterator.NextSequence(); // Move to the second sequence

    EXPECT_FALSE(iterator.NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_95, Reset_InitState_95) {

    iterator.NextSequence(); // Move to the second sequence

    iterator.Reset();

    EXPECT_EQ(iterator.SequenceStart(), 0);

    EXPECT_EQ(iterator.SequenceEnd(), 4);

}



TEST_F(AnsiColorSequenceIteratorTest_95, NoSequences_EmptyInput_95) {

    std::string empty_input = "";

    AnsiColorSequenceIterator empty_iterator(empty_input);

    EXPECT_FALSE(empty_iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_95, SingleSequence_NoNext_95) {

    std::string single_sequence_input = "\x1b[32m";

    AnsiColorSequenceIterator single_seq_iterator(single_sequence_input);

    EXPECT_TRUE(single_seq_iterator.HasSequence());

    EXPECT_FALSE(single_seq_iterator.NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_95, NoSequences_NoEscapes_95) {

    std::string no_escapes_input = "HelloWorld";

    AnsiColorSequenceIterator no_escape_iterator(no_escapes_input);

    EXPECT_FALSE(no_escape_iterator.HasSequence());

}
