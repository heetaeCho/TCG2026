#include <gtest/gtest.h>
#include <string>

// Include the header that declares AnsiColorSequenceIterator
// Based on the file structure, we need to include the appropriate header
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_100 : public ::testing::Test {
protected:
};

// Test with empty string - no sequences should be found
TEST_F(AnsiColorSequenceIteratorTest_100, EmptyString_NoSequences_100) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test with a string containing no ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_100, NoAnsiSequences_100) {
  std::string input = "Hello, World!";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test with a single ANSI color sequence (e.g., ESC[31m for red)
TEST_F(AnsiColorSequenceIteratorTest_100, SingleAnsiSequence_100) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_GT(iter.SequenceSize(), 0u);
}

// Test NextSequence finds additional sequences
TEST_F(AnsiColorSequenceIteratorTest_100, MultipleSequences_NextSequence_100) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  
  // Try to find the next sequence (the reset sequence \033[0m)
  bool found_next = iter.NextSequence();
  if (found_next) {
    EXPECT_GT(iter.SequenceStart(), first_start);
    EXPECT_GT(iter.SequenceEnd(), first_end);
  }
}

// Test SequenceContains for positions within and outside a sequence
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceContains_InsideSequence_100) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    size_t start = iter.SequenceStart();
    size_t end = iter.SequenceEnd();
    
    // Positions within the sequence should return true
    for (size_t i = start; i < end; ++i) {
      EXPECT_TRUE(iter.SequenceContains(i));
    }
    
    // Position after the sequence should return false
    if (end < input.size()) {
      EXPECT_FALSE(iter.SequenceContains(end));
    }
  }
}

// Test SequenceSize matches SequenceEnd - SequenceStart
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceSizeConsistency_100) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
  }
}

// Test Reset goes back to the first sequence
TEST_F(AnsiColorSequenceIteratorTest_100, Reset_ReturnsToFirstSequence_100) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    size_t original_start = iter.SequenceStart();
    size_t original_end = iter.SequenceEnd();
    
    // Advance if possible
    iter.NextSequence();
    
    // Reset
    iter.Reset();
    
    // After reset, should be at the first sequence again if HasSequence
    if (iter.HasSequence()) {
      EXPECT_EQ(iter.SequenceStart(), original_start);
      EXPECT_EQ(iter.SequenceEnd(), original_end);
    }
  }
}

// Test with ANSI sequence at the beginning of string
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceAtBeginning_100) {
  std::string input = "\033[1mBold text";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
}

// Test with ANSI sequence in the middle of string
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceInMiddle_100) {
  std::string input = "Hello\033[32mGreen";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 5u);
}

// Test with ANSI sequence at the end of string
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceAtEnd_100) {
  std::string input = "Hello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 5u);
}

// Test NextSequence returns false when no more sequences exist
TEST_F(AnsiColorSequenceIteratorTest_100, NextSequence_ReturnsFalseWhenExhausted_100) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    // Keep calling NextSequence until it returns false
    int count = 0;
    while (iter.NextSequence()) {
      count++;
      // Safety: prevent infinite loop in test
      if (count > 100) break;
    }
    // After exhaustion, NextSequence should have returned false
    EXPECT_LE(count, 100);
  }
}

// Test with multiple ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_100, MultipleSequences_IterateAll_100) {
  std::string input = "\033[31mRed\033[32mGreen\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  int sequence_count = 0;
  if (iter.HasSequence()) {
    sequence_count = 1;
    while (iter.NextSequence()) {
      sequence_count++;
      if (sequence_count > 100) break; // safety
    }
  }
  // We expect 3 ANSI sequences in this string
  EXPECT_EQ(sequence_count, 3);
}

// Test with only an ANSI sequence and no other text
TEST_F(AnsiColorSequenceIteratorTest_100, OnlyAnsiSequence_100) {
  std::string input = "\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceEnd(), input.size());
  EXPECT_EQ(iter.SequenceSize(), input.size());
  EXPECT_FALSE(iter.NextSequence());
}

// Test SequenceContains with index outside any sequence
TEST_F(AnsiColorSequenceIteratorTest_100, SequenceContains_OutsideSequence_100) {
  std::string input = "AB\033[31mCD";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    // Index 0 and 1 should be outside the sequence (they are 'A' and 'B')
    EXPECT_FALSE(iter.SequenceContains(0));
    EXPECT_FALSE(iter.SequenceContains(1));
  }
}

// Test with incomplete/malformed ANSI escape - just ESC character
TEST_F(AnsiColorSequenceIteratorTest_100, IncompleteEscape_JustEsc_100) {
  std::string input = "\033";
  AnsiColorSequenceIterator iter(input);
  // An incomplete escape may or may not be recognized - just verify no crash
  // and behavior is consistent
  bool has = iter.HasSequence();
  if (has) {
    EXPECT_LE(iter.SequenceEnd(), input.size());
  }
}

// Test with string containing ESC but not a valid sequence
TEST_F(AnsiColorSequenceIteratorTest_100, EscWithoutBracket_100) {
  std::string input = "\033Hello";
  AnsiColorSequenceIterator iter(input);
  // May or may not find a sequence - just ensure no crash
  bool has = iter.HasSequence();
  (void)has; // suppress unused warning
}

// Test NextSequence after no initial sequence returns false properly
TEST_F(AnsiColorSequenceIteratorTest_100, NextSequence_NoInitialSequence_100) {
  std::string input = "plain text";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test sequences are iterated in order (start positions are increasing)
TEST_F(AnsiColorSequenceIteratorTest_100, SequencesInOrder_100) {
  std::string input = "\033[1mBold\033[31mRed\033[0mNormal";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    size_t prev_start = iter.SequenceStart();
    while (iter.NextSequence()) {
      EXPECT_GT(iter.SequenceStart(), prev_start);
      prev_start = iter.SequenceStart();
    }
  }
}

// Test Reset after full iteration allows re-iteration
TEST_F(AnsiColorSequenceIteratorTest_100, ResetAfterFullIteration_100) {
  std::string input = "\033[31mRed\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  // First pass - count sequences
  int first_count = 0;
  if (iter.HasSequence()) {
    first_count = 1;
    while (iter.NextSequence()) first_count++;
  }
  
  // Reset
  iter.Reset();
  
  // Second pass - count sequences again
  int second_count = 0;
  if (iter.HasSequence()) {
    second_count = 1;
    while (iter.NextSequence()) second_count++;
  }
  
  EXPECT_EQ(first_count, second_count);
}

// Test with complex ANSI sequence (multiple parameters)
TEST_F(AnsiColorSequenceIteratorTest_100, ComplexAnsiSequence_100) {
  std::string input = "\033[1;31;40mColorful";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_GT(iter.SequenceSize(), 0u);
}
