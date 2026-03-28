#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



// Assuming the class definition is included here for completeness in the test file.

struct AnsiColorSequenceIterator {

private:

    size_t cur_start_ = 0;

    size_t cur_end_ = 0;

    const char *input_;

    const char *input_end_;



public:

    AnsiColorSequenceIterator(const std::string& input) : input_(input.data()), input_end_(input_ + input.size()) {}



    bool HasSequence() const;

    size_t SequenceStart() const { return cur_start_; }

    size_t SequenceEnd() const;

    size_t SequenceSize() const;

    bool SequenceContains(size_t input_index) const;

    bool NextSequence();

    void Reset();



private:

    bool FindNextSequenceFrom(const char* from);

};



class AnsiColorSequenceIteratorTest : public ::testing::Test {

protected:

    std::string test_string = "\033[1;34mHello\033[0m";

    AnsiColorSequenceIterator iterator;

    

    AnsiColorSequenceIteratorTest() : iterator(test_string) {}

};



TEST_F(AnsiColorSequenceIteratorTest_96, HasSequence_ReturnsTrueForValidAnsiEscapeSequence_96) {

    EXPECT_TRUE(iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceStart_ReturnsCorrectStartIndex_96) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceEnd_ReturnsCorrectEndIndex_96) {

    ASSERT_TRUE(iterator.HasSequence());

    iterator.NextSequence();

    EXPECT_EQ(iterator.SequenceEnd(), 5); // End of "\033[1;34m"

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceSize_ReturnsCorrectSize_96) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_EQ(iterator.SequenceSize(), 5); // Size of "\033[1;34m"

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceContains_ReturnsTrueForIndexInsideSequence_96) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_TRUE(iterator.SequenceContains(2));

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceContains_ReturnsFalseForIndexOutsideSequence_96) {

    iterator.NextSequence();

    EXPECT_FALSE(iterator.SequenceContains(10)); // Index after the sequence

}



TEST_F(AnsiColorSequenceIteratorTest_96, NextSequence_AdvancesToNextSequence_96) {

    ASSERT_TRUE(iterator.HasSequence());

    EXPECT_TRUE(iterator.NextSequence());

    EXPECT_EQ(iterator.SequenceStart(), 13); // Start of "\033[0m"

}



TEST_F(AnsiColorSequenceIteratorTest_96, Reset_ResetsToFirstSequence_96) {

    ASSERT_TRUE(iterator.HasSequence());

    iterator.NextSequence();

    iterator.Reset();

    EXPECT_EQ(iterator.SequenceStart(), 0);

}



TEST_F(AnsiColorSequenceIteratorTest_96, HasSequence_ReturnsFalseForNoSequence_96) {

    AnsiColorSequenceIterator no_sequence_iterator("Hello");

    EXPECT_FALSE(no_sequence_iterator.HasSequence());

}



TEST_F(AnsiColorSequenceIteratorTest_96, SequenceSize_ReturnsZeroWhenNoSequence_96) {

    AnsiColorSequenceIterator no_sequence_iterator("Hello");

    EXPECT_EQ(no_sequence_iterator.SequenceSize(), 0);

}
