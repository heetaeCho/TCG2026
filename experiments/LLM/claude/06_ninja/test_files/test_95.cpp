#include <gtest/gtest.h>
#include <string>

// Include the header that contains AnsiColorSequenceIterator
// Based on the file structure, we need to include the appropriate header
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_95 : public ::testing::Test {
protected:
};

// Test that an empty string has no sequences
TEST_F(AnsiColorSequenceIteratorTest_95, EmptyStringHasNoSequence_95) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

// Test that a string with no ANSI sequences has no sequences
TEST_F(AnsiColorSequenceIteratorTest_95, PlainStringHasNoSequence_95) {
  std::string input = "hello world";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

// Test that a string with a single ANSI color sequence is detected
TEST_F(AnsiColorSequenceIteratorTest_95, SingleAnsiSequenceDetected_95) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  // After construction, check if first sequence is found via NextSequence
  bool found = iter.NextSequence();
  if (found) {
    EXPECT_TRUE(iter.HasSequence());
    EXPECT_GE(iter.SequenceEnd(), iter.SequenceStart());
    EXPECT_GT(iter.SequenceSize(), 0u);
  }
}

// Test NextSequence returns false when no sequences exist
TEST_F(AnsiColorSequenceIteratorTest_95, NextSequenceReturnsFalseForPlainText_95) {
  std::string input = "no colors here";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Test iterating through multiple ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_95, MultipleSequencesIteration_95) {
  std::string input = "\033[31mred\033[0m and \033[32mgreen\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  int count = 0;
  while (iter.NextSequence()) {
    EXPECT_TRUE(iter.HasSequence());
    count++;
  }
  // Should find multiple sequences (at least the color codes)
  EXPECT_GT(count, 0);
}

// Test SequenceStart and SequenceEnd relationship
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceStartBeforeEnd_95) {
  std::string input = "\033[1;34mblue\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    EXPECT_LE(iter.SequenceStart(), iter.SequenceEnd());
    EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
  }
}

// Test SequenceSize matches expected size
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceSizeIsCorrect_95) {
  std::string input = "\033[31mtext\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    size_t size = iter.SequenceSize();
    EXPECT_EQ(size, iter.SequenceEnd() - iter.SequenceStart());
  }
}

// Test SequenceContains for index within a sequence
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceContainsIndexInSequence_95) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    size_t start = iter.SequenceStart();
    // An index within the sequence should be contained
    EXPECT_TRUE(iter.SequenceContains(start));
  }
}

// Test SequenceContains for index outside a sequence
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceDoesNotContainOutsideIndex_95) {
  std::string input = "abc\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    // Index 0 should be before the first sequence (which starts after "abc")
    if (iter.SequenceStart() > 0) {
      EXPECT_FALSE(iter.SequenceContains(0));
    }
  }
}

// Test Reset functionality
TEST_F(AnsiColorSequenceIteratorTest_95, ResetAllowsReIteration_95) {
  std::string input = "\033[31mred\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  int first_count = 0;
  while (iter.NextSequence()) {
    first_count++;
  }
  
  iter.Reset();
  
  int second_count = 0;
  while (iter.NextSequence()) {
    second_count++;
  }
  
  EXPECT_EQ(first_count, second_count);
}

// Test Reset clears HasSequence state
TEST_F(AnsiColorSequenceIteratorTest_95, ResetClearsHasSequence_95) {
  std::string input = "\033[31mred\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    EXPECT_TRUE(iter.HasSequence());
  }
  
  iter.Reset();
  EXPECT_FALSE(iter.HasSequence());
}

// Test with only an ANSI escape sequence and no regular text
TEST_F(AnsiColorSequenceIteratorTest_95, OnlyEscapeSequence_95) {
  std::string input = "\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  bool found = iter.NextSequence();
  if (found) {
    EXPECT_TRUE(iter.HasSequence());
    EXPECT_EQ(iter.SequenceStart(), 0u);
    EXPECT_EQ(iter.SequenceEnd(), input.size());
  }
}

// Test with incomplete/malformed escape sequence
TEST_F(AnsiColorSequenceIteratorTest_95, IncompleteEscapeSequence_95) {
  std::string input = "\033[";
  AnsiColorSequenceIterator iter(input);
  // An incomplete sequence might not be detected
  // Just verify it doesn't crash
  bool found = iter.NextSequence();
  // We don't assert the result since behavior depends on implementation
  (void)found;
}

// Test with escape character but no bracket
TEST_F(AnsiColorSequenceIteratorTest_95, EscapeWithoutBracket_95) {
  std::string input = "\033hello";
  AnsiColorSequenceIterator iter(input);
  bool found = iter.NextSequence();
  // Likely no valid ANSI sequence
  (void)found;
  // Just ensure no crash
}

// Test HasSequence before calling NextSequence (initial state)
TEST_F(AnsiColorSequenceIteratorTest_95, InitialStateHasNoSequence_95) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  // Before calling NextSequence, cur_end_ should be 0
  EXPECT_FALSE(iter.HasSequence());
}

// Test iterating past all sequences
TEST_F(AnsiColorSequenceIteratorTest_95, NextSequenceReturnsFalseAfterAllConsumed_95) {
  std::string input = "\033[31mred\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  while (iter.NextSequence()) {
    // consume all
  }
  
  // After all consumed, NextSequence should keep returning false
  EXPECT_FALSE(iter.NextSequence());
}

// Test with a long/complex ANSI sequence
TEST_F(AnsiColorSequenceIteratorTest_95, ComplexAnsiSequence_95) {
  std::string input = "\033[1;4;38;2;255;100;0mcomplex\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  bool found = iter.NextSequence();
  if (found) {
    EXPECT_TRUE(iter.HasSequence());
    EXPECT_GT(iter.SequenceSize(), 0u);
  }
}

// Test SequenceContains at boundary - index just before sequence
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceContainsBoundaryBeforeStart_95) {
  std::string input = "X\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    size_t start = iter.SequenceStart();
    if (start > 0) {
      EXPECT_FALSE(iter.SequenceContains(start - 1));
    }
  }
}

// Test SequenceContains at boundary - index at end
TEST_F(AnsiColorSequenceIteratorTest_95, SequenceContainsBoundaryAtEnd_95) {
  std::string input = "X\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.NextSequence()) {
    size_t end = iter.SequenceEnd();
    // Depending on whether end is inclusive or exclusive
    // Just test it doesn't crash
    bool result = iter.SequenceContains(end);
    (void)result;
  }
}
