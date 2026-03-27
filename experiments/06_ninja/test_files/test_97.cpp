#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class definition is as follows based on the partial code provided:

struct AnsiColorSequenceIterator {

    private: 

        size_t cur_start_ = 0; 

        size_t cur_end_ = 0; 

        const char * input_; 

        const char * input_end_; 



    public: 

        AnsiColorSequenceIterator(const std::string& input) : input_(input.data()), input_end_(input_ + input.size()) {}

        bool HasSequence() const;

        size_t SequenceStart() const { return cur_start_; }

        size_t SequenceEnd() const { return cur_end_; }

        size_t SequenceSize() const { return cur_end_ - cur_start_; }

        bool SequenceContains(size_t input_index) const;

        bool NextSequence();

        void Reset();



    private: 

        bool FindNextSequenceFrom(const char* from);

};



// Test fixture

class AnsiColorSequenceIteratorTest : public ::testing::Test {

protected:

    std::string test_input = "\033[1mBold Text\033[0m";

    AnsiColorSequenceIterator iterator;



    AnsiColorSequenceIteratorTest() : iterator(test_input) {}

};



// Normal operation tests

TEST_F(AnsiColorSequenceIteratorTest_97, HasSequence_ReturnsTrueForValidInput_97) {

    EXPECT_TRUE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceStart_ReturnsCorrectValue_97) {

    ASSERT_TRUE(iterator.NextSequence());

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceEnd_ReturnsCorrectValue_97) {

    ASSERT_TRUE(iterator.NextSequence());

    EXPECT_EQ(iterator.SequenceEnd(), 4); // "\033[1m" is 4 characters long

}



TEST_F(AnsiColorSequenceIteratorTest_97, NextSequence_MovesToNextSequence_97) {

    ASSERT_TRUE(iterator.NextSequence()); // Move to first sequence

    ASSERT_TRUE(iterator.NextSequence()); // Move to second sequence

    EXPECT_EQ(iterator.SequenceStart(), 15);

    EXPECT_EQ(iterator.SequenceEnd(), 19); // "\033[0m" is 4 characters long

}



TEST_F(AnsiColorSequenceIteratorTest_97, Reset_AllowsRestartingIteration_97) {

    ASSERT_TRUE(iterator.NextSequence()); // Move to first sequence

    iterator.Reset();

    ASSERT_TRUE(iterator.NextSequence()); // Should be able to move to the first sequence again

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



// Boundary condition tests

TEST_F(AnsiColorSequenceIteratorTest_97, HasSequence_ReturnsFalseForEmptyInput_97) {

    AnsiColorSequenceIterator empty_iterator("");

    EXPECT_FALSE(empty_iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceStart_ReturnsZeroForNoSequence_97) {

    AnsiColorSequenceIterator no_sequence_iterator("Plain Text");

    EXPECT_EQ(no_sequence_iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceEnd_ReturnsZeroForNoSequence_97) {

    AnsiColorSequenceIterator no_sequence_iterator("Plain Text");

    EXPECT_EQ(no_sequence_iterator.SequenceEnd(), 0);

}



// Exceptional or error cases

TEST_F(AnsiColorSequenceIteratorTest_97, NextSequence_ReturnsFalseAtEndOfSequences_97) {

    ASSERT_TRUE(iterator.NextSequence()); // Move to first sequence

    ASSERT_TRUE(iterator.NextSequence()); // Move to second sequence

    EXPECT_FALSE(iterator.NextSequence()); // No more sequences

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceContains_ReturnsTrueForIndexInSequence_97) {

    ASSERT_TRUE(iterator.NextSequence());

    EXPECT_TRUE(iterator.SequenceContains(1)); // Index 1 is within "\033[1m"

}



TEST_F(AnsiColorSequenceIteratorTest_97, SequenceContains_ReturnsFalseForIndexOutsideSequence_97) {

    ASSERT_TRUE(iterator.NextSequence());

    EXPECT_FALSE(iterator.SequenceContains(5)); // Index 5 is not within "\033[1m"

}
