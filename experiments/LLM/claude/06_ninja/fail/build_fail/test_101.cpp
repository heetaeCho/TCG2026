#include "gtest/gtest.h"
#include <string>

// Include the header that declares AnsiColorSequenceIterator
// Based on the file structure, we need to include the appropriate header
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_101 : public ::testing::Test {
protected:
};

// Test with empty string - no sequences expected
TEST_F(AnsiColorSequenceIteratorTest_101, EmptyString_NoSequence_101) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

// Test with string containing no ANSI escape sequences
TEST_F(AnsiColorSequenceIteratorTest_101, NoAnsiSequences_101) {
  std::string input = "Hello, World!";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

// Test with a single ANSI color sequence (e.g., \033[31m for red)
TEST_F(AnsiColorSequenceIteratorTest_101, SingleAnsiSequence_101) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_GT(iter.SequenceEnd(), iter.SequenceStart());
  EXPECT_GT(iter.SequenceSize(), 0u);
}

// Test with ANSI sequence in the middle of the string
TEST_F(AnsiColorSequenceIteratorTest_101, AnsiSequenceInMiddle_101) {
  std::string input = "Hello\033[31mWorld";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 5u);
}

// Test with multiple ANSI sequences - iteration through NextSequence
TEST_F(AnsiColorSequenceIteratorTest_101, MultipleAnsiSequences_101) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  
  EXPECT_TRUE(iter.NextSequence());
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_GT(iter.SequenceStart(), first_start);
  
  // No more sequences after the second one
  EXPECT_FALSE(iter.NextSequence());
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_101, NextSequenceReturnsFalseAtEnd_101) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test NextSequence on string with no sequences
TEST_F(AnsiColorSequenceIteratorTest_101, NextSequenceOnNoSequences_101) {
  std::string input = "No sequences here";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test SequenceSize matches End - Start
TEST_F(AnsiColorSequenceIteratorTest_101, SequenceSizeConsistency_101) {
  std::string input = "\033[31mRed";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
}

// Test SequenceContains for indices within the sequence
TEST_F(AnsiColorSequenceIteratorTest_101, SequenceContainsInsideSequence_101) {
  std::string input = "\033[31mRed";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  // The sequence starts at 0, so index 0 should be contained
  EXPECT_TRUE(iter.SequenceContains(iter.SequenceStart()));
  
  // Index just before end should be contained
  if (iter.SequenceEnd() > iter.SequenceStart()) {
    EXPECT_TRUE(iter.SequenceContains(iter.SequenceEnd() - 1));
  }
}

// Test SequenceContains for indices outside the sequence
TEST_F(AnsiColorSequenceIteratorTest_101, SequenceContainsOutsideSequence_101) {
  std::string input = "AB\033[31mCD";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  // Index before the sequence should not be contained
  EXPECT_FALSE(iter.SequenceContains(0));
  EXPECT_FALSE(iter.SequenceContains(1));
}

// Test Reset re-initializes the iterator to the first sequence
TEST_F(AnsiColorSequenceIteratorTest_101, ResetReturnsToFirstSequence_101) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  
  // Move to second sequence
  iter.NextSequence();
  EXPECT_NE(iter.SequenceStart(), first_start);
  
  // Reset should go back to first sequence
  iter.Reset();
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), first_start);
  EXPECT_EQ(iter.SequenceEnd(), first_end);
}

// Test Reset on empty string
TEST_F(AnsiColorSequenceIteratorTest_101, ResetOnEmptyString_101) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  iter.Reset();
  EXPECT_FALSE(iter.HasSequence());
}

// Test Reset on string with no sequences
TEST_F(AnsiColorSequenceIteratorTest_101, ResetOnNoSequenceString_101) {
  std::string input = "plain text";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  iter.Reset();
  EXPECT_FALSE(iter.HasSequence());
}

// Test with ANSI reset sequence \033[0m
TEST_F(AnsiColorSequenceIteratorTest_101, AnsiResetSequence_101) {
  std::string input = "\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceSize(), input.size());
}

// Test with multiple parameters in ANSI sequence (e.g., \033[1;31m bold red)
TEST_F(AnsiColorSequenceIteratorTest_101, MultiParamAnsiSequence_101) {
  std::string input = "\033[1;31mBold Red";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
}

// Test with ANSI sequence at the end of string
TEST_F(AnsiColorSequenceIteratorTest_101, AnsiSequenceAtEnd_101) {
  std::string input = "Hello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 5u);
}

// Test that SequenceEnd is within bounds of input
TEST_F(AnsiColorSequenceIteratorTest_101, SequenceEndWithinBounds_101) {
  std::string input = "\033[31m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_LE(iter.SequenceEnd(), input.size());
}

// Test iteration through three sequences
TEST_F(AnsiColorSequenceIteratorTest_101, ThreeSequencesIteration_101) {
  std::string input = "\033[31mRed\033[32mGreen\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  int count = 0;
  if (iter.HasSequence()) {
    count++;
    while (iter.NextSequence()) {
      count++;
    }
  }
  EXPECT_EQ(count, 3);
}

// Test with only escape character but incomplete sequence
TEST_F(AnsiColorSequenceIteratorTest_101, IncompleteEscapeSequence_101) {
  std::string input = "\033[";
  AnsiColorSequenceIterator iter(input);
  // Incomplete sequence - behavior depends on implementation
  // Just verify it doesn't crash
  bool has = iter.HasSequence();
  (void)has;
}

// Test with escape character alone
TEST_F(AnsiColorSequenceIteratorTest_101, EscapeCharAlone_101) {
  std::string input = "\033";
  AnsiColorSequenceIterator iter(input);
  // Just verify no crash
  bool has = iter.HasSequence();
  (void)has;
}

// Test SequenceContains at the exact boundary (end index)
TEST_F(AnsiColorSequenceIteratorTest_101, SequenceContainsAtEndBoundary_101) {
  std::string input = "\033[31mText";
  AnsiColorSequenceIterator iter(input);
  if (iter.HasSequence()) {
    // End is typically exclusive, so SequenceEnd should not be contained
    EXPECT_FALSE(iter.SequenceContains(iter.SequenceEnd()));
  }
}

// Test multiple resets
TEST_F(AnsiColorSequenceIteratorTest_101, MultipleResets_101) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  for (int i = 0; i < 3; i++) {
    iter.Reset();
    EXPECT_TRUE(iter.HasSequence());
    size_t start = iter.SequenceStart();
    EXPECT_EQ(start, 0u);
  }
}
