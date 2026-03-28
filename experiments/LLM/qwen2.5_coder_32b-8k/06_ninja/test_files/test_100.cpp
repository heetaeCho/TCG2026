#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "elide_middle.cc"  // Adjust the include path as necessary



class AnsiColorSequenceIteratorTest : public ::testing::Test {

protected:

    void SetUp() override {

        iterator = std::make_unique<AnsiColorSequenceIterator>("");

    }



    std::unique_ptr<AnsiColorSequenceIterator> iterator;

};



TEST_F(AnsiColorSequenceIteratorTest_100, EmptyInput_NoSequences_100) {

    ASSERT_FALSE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_100, SingleNonSequenceCharacter_NoSequences_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("a");

    ASSERT_FALSE(iterator->HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_100, SimpleSequence_NextFindsSequence_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31m");

    EXPECT_TRUE(iterator->NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_100, MultipleSequences_AllFound_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31ma\033[32m");

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_FALSE(iterator->NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_100, ResetAfterEnd_ReturnsToStart_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31m");

    EXPECT_TRUE(iterator->NextSequence());

    iterator->Reset();

    EXPECT_TRUE(iterator->NextSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_100, BoundaryCondition_StartOfInput_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31ma");

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_EQ(iterator->SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_100, BoundaryCondition_EndOfInput_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("a\033[31m");

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_EQ(iterator->SequenceEnd(), 8); // Assuming \033[31m is 7 chars long

}



TEST_F(AnsiColorSequenceIteratorTest_100, SequenceContains_CheckInside_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31ma");

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_TRUE(iterator->SequenceContains(5)); // Assuming 'a' is at index 7

}



TEST_F(AnsiColorSequenceIteratorTest_100, SequenceContains_CheckOutside_100) {

    iterator = std::make_unique<AnsiColorSequenceIterator>("\033[31ma");

    EXPECT_TRUE(iterator->NextSequence());

    EXPECT_FALSE(iterator->SequenceContains(8)); // Assuming 'a' is at index 7

}
