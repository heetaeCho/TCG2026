#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"



class AnsiColorSequenceIteratorTest_99 : public ::testing::Test {

protected:

    std::string input;

    AnsiColorSequenceIterator iterator;



    void SetUp() override {

        input = "\033[31mHello\033[0m World";

        iterator = AnsiColorSequenceIterator(input);

    }

};



TEST_F(AnsiColorSequenceIteratorTest_99, HasSequence_Initial_99) {

    EXPECT_TRUE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_99, SequenceStart_Initial_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_99, SequenceEnd_Initial_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceEnd(), 5);

}



TEST_F(AnsiColorSequenceIteratorTest_99, SequenceSize_Initial_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceSize(), 5);

}



TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContains_ValidIndex_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_TRUE(iterator.SequenceContains(0));

    EXPECT_TRUE(iterator.SequenceContains(4));

}



TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContains_OutOfBounds_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_FALSE(iterator.SequenceContains(5));

    EXPECT_FALSE(iterator.SequenceContains(10));

}



TEST_F(AnsiColorSequenceIteratorTest_99, NextSequence_AfterFirst_99) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_TRUE(iterator.NextSequence());

    EXPECT_EQ(iterator.SequenceStart(), 13);

    EXPECT_EQ(iterator.SequenceEnd(), 14);

}



TEST_F(AnsiColorSequenceIteratorTest_99, NextSequence_NoMoreSequences_99) {

    ASSERT_TRUE(iterator.HasSequence());

    iterator.NextSequence();

    EXPECT_FALSE(iterator.NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_99, Reset_RestoresInitial_99) {

    ASSERT_TRUE(iterator.HasSequence());

    iterator.NextSequence();

    iterator.Reset();

    EXPECT_EQ(iterator.SequenceStart(), 0);

    EXPECT_EQ(iterator.SequenceEnd(), 5);

}



TEST_F(AnsiColorSequenceIteratorTest_99, EmptyString_NoSequences_99) {

    input = "";

    iterator = AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_99, NoAnsiCodes_NoSequences_99) {

    input = "Hello World";

    iterator = AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator.HasSequence());

}
