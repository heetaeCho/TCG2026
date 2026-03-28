#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"



using ::testing::Test;



class AnsiColorSequenceIteratorTest_98 : public Test {

protected:

    std::string input;

    AnsiColorSequenceIterator* iterator;



    void SetUp() override {

        input = "\033[1mBold\033[0m";

        iterator = new AnsiColorSequenceIterator(input);

    }



    void TearDown() override {

        delete iterator;

    }

};



TEST_F(AnsiColorSequenceIteratorTest_98, InitialStateNoSequence_98) {

    EXPECT_FALSE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_98, FirstSequenceDetected_98) {

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_TRUE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_98, SequenceSizeCorrect_98) {

    iterator->NextSequence();

    EXPECT_EQ(iterator->SequenceSize(), 5); // Size of "\033[1m"

}



TEST_F(AnsiColorSequenceIteratorTest_98, SecondSequenceDetected_98) {

    iterator->NextSequence(); // Skip first sequence

    iterator->NextSequence(); // Move to second sequence

    EXPECT_TRUE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_98, SecondSequenceSizeCorrect_98) {

    iterator->NextSequence(); // Skip first sequence

    iterator->NextSequence(); // Move to second sequence

    EXPECT_EQ(iterator->SequenceSize(), 5); // Size of "\033[0m"

}



TEST_F(AnsiColorSequenceIteratorTest_98, NoMoreSequences_98) {

    iterator->NextSequence();

    iterator->NextSequence();

    EXPECT_FALSE(iterator->NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_98, ResetFindsFirstSequenceAgain_98) {

    iterator->NextSequence(); // Skip first sequence

    iterator->Reset();

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_EQ(iterator->SequenceSize(), 5); // Size of "\033[1m"

}



TEST_F(AnsiColorSequenceIteratorTest_98, SequenceContainsIndexTrue_98) {

    iterator->NextSequence();

    EXPECT_TRUE(iterator->SequenceContains(2)); // Index within "\033[1m"

}



TEST_F(AnsiColorSequenceIteratorTest_98, SequenceContainsIndexFalse_98) {

    iterator->NextSequence();

    EXPECT_FALSE(iterator->SequenceContains(6)); // Index after "\033[1m"

}



TEST_F(AnsiColorSequenceIteratorTest_98, EmptyInputNoSequences_98) {

    delete iterator;

    input = "";

    iterator = new AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator->NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_98, NoAnsiCodesNoSequences_98) {

    delete iterator;

    input = "Plain text";

    iterator = new AnsiColorSequenceIterator(input);

    EXPECT_FALSE(iterator->NextSequence());

}
