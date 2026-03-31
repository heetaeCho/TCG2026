#include "gtest/gtest.h"
#include <string>

// Forward declaration based on the known interface
struct AnsiColorSequenceIterator {
private:
    size_t cur_start_ = 0;
    size_t cur_end_ = 0;
    const char* input_;
    const char* input_end_;

public:
    AnsiColorSequenceIterator(const std::string& input);
    bool HasSequence() const;
    size_t SequenceStart() const;
    size_t SequenceEnd() const;
    size_t SequenceSize() const;
    bool SequenceContains(size_t input_index) const;
    bool NextSequence();
    void Reset();

private:
    bool FindNextSequenceFrom(const char* from);
};

// Include the actual implementation
#include "elide_middle.cc"

class AnsiColorSequenceIteratorTest_97 : public ::testing::Test {
protected:
};

// Test with empty string - no sequences expected
TEST_F(AnsiColorSequenceIteratorTest_97, EmptyString_HasNoSequence_97) {
    std::string input = "";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
}

// Test with a string containing no ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_97, NoAnsiSequences_HasNoSequence_97) {
    std::string input = "Hello World";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
}

// Test with a simple ANSI color sequence (e.g., ESC[31m for red)
TEST_F(AnsiColorSequenceIteratorTest_97, SimpleAnsiSequence_HasSequence_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    EXPECT_TRUE(iter.HasSequence());
}

// Test SequenceStart returns correct position for first sequence
TEST_F(AnsiColorSequenceIteratorTest_97, SimpleAnsiSequence_SequenceStartIsZero_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_EQ(0u, iter.SequenceStart());
}

// Test SequenceEnd returns correct position
TEST_F(AnsiColorSequenceIteratorTest_97, SimpleAnsiSequence_SequenceEndCorrect_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    // ESC[31m is 5 characters: \033 [ 3 1 m
    EXPECT_EQ(5u, iter.SequenceEnd());
}

// Test SequenceSize returns correct size
TEST_F(AnsiColorSequenceIteratorTest_97, SimpleAnsiSequence_SequenceSizeCorrect_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_EQ(5u, iter.SequenceSize());
}

// Test NextSequence finds the second sequence
TEST_F(AnsiColorSequenceIteratorTest_97, TwoSequences_NextSequenceFindsSecond_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_TRUE(iter.NextSequence());
    // Second sequence starts at position 10 (after "\033[31m" + "Hello")
    EXPECT_EQ(10u, iter.SequenceStart());
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_97, SingleSequence_NextSequenceReturnsFalse_97) {
    std::string input = "\033[31m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_FALSE(iter.NextSequence());
}

// Test SequenceContains for index within sequence
TEST_F(AnsiColorSequenceIteratorTest_97, SequenceContains_IndexWithinSequence_97) {
    std::string input = "\033[31mHello";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_TRUE(iter.SequenceContains(0));
    EXPECT_TRUE(iter.SequenceContains(2));
    EXPECT_TRUE(iter.SequenceContains(4));
}

// Test SequenceContains for index outside sequence
TEST_F(AnsiColorSequenceIteratorTest_97, SequenceContains_IndexOutsideSequence_97) {
    std::string input = "\033[31mHello";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_FALSE(iter.SequenceContains(5));
    EXPECT_FALSE(iter.SequenceContains(6));
}

// Test Reset brings iterator back to first sequence
TEST_F(AnsiColorSequenceIteratorTest_97, Reset_ReturnsToFirstSequence_97) {
    std::string input = "\033[31mHello\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    size_t first_start = iter.SequenceStart();
    size_t first_end = iter.SequenceEnd();

    iter.NextSequence();
    iter.Reset();

    ASSERT_TRUE(iter.HasSequence());
    EXPECT_EQ(first_start, iter.SequenceStart());
    EXPECT_EQ(first_end, iter.SequenceEnd());
}

// Test with sequence in the middle of string
TEST_F(AnsiColorSequenceIteratorTest_97, SequenceInMiddle_CorrectStartPosition_97) {
    std::string input = "Hi\033[31mWorld";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_EQ(2u, iter.SequenceStart());
}

// Test with multiple sequences - iterate through all
TEST_F(AnsiColorSequenceIteratorTest_97, MultipleSequences_IterateAll_97) {
    std::string input = "\033[31mRed\033[32mGreen\033[0m";
    AnsiColorSequenceIterator iter(input);

    int count = 0;
    if (iter.HasSequence()) {
        count++;
        while (iter.NextSequence()) {
            count++;
        }
    }
    EXPECT_EQ(3, count);
}

// Test with only escape character but not a valid sequence
TEST_F(AnsiColorSequenceIteratorTest_97, IncompleteEscape_NoSequence_97) {
    std::string input = "\033Hello";
    AnsiColorSequenceIterator iter(input);
    // An incomplete escape is not a valid ANSI sequence
    EXPECT_FALSE(iter.HasSequence());
}

// Test reset on empty string
TEST_F(AnsiColorSequenceIteratorTest_97, Reset_EmptyString_97) {
    std::string input = "";
    AnsiColorSequenceIterator iter(input);
    iter.Reset();
    EXPECT_FALSE(iter.HasSequence());
}

// Test with ESC[ but no terminator
TEST_F(AnsiColorSequenceIteratorTest_97, EscBracketNoTerminator_NoSequence_97) {
    std::string input = "\033[123";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
}

// Test SequenceEnd after NextSequence
TEST_F(AnsiColorSequenceIteratorTest_97, NextSequence_SequenceEndUpdated_97) {
    std::string input = "\033[31mHi\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    size_t first_end = iter.SequenceEnd();

    ASSERT_TRUE(iter.NextSequence());
    size_t second_end = iter.SequenceEnd();

    EXPECT_GT(second_end, first_end);
}

// Test with ANSI reset sequence
TEST_F(AnsiColorSequenceIteratorTest_97, ResetSequence_Found_97) {
    std::string input = "\033[0m";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    EXPECT_EQ(0u, iter.SequenceStart());
    EXPECT_EQ(4u, iter.SequenceEnd());
    EXPECT_EQ(4u, iter.SequenceSize());
}

// Test SequenceContains at boundary
TEST_F(AnsiColorSequenceIteratorTest_97, SequenceContains_AtBoundary_97) {
    std::string input = "\033[0mText";
    AnsiColorSequenceIterator iter(input);
    ASSERT_TRUE(iter.HasSequence());
    // Last index of sequence should be contained
    EXPECT_TRUE(iter.SequenceContains(iter.SequenceEnd() - 1));
    // First index after sequence should not be contained
    EXPECT_FALSE(iter.SequenceContains(iter.SequenceEnd()));
}
