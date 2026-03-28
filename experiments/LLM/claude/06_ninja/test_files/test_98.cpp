#include "gtest/gtest.h"
#include <string>

// Forward declare or include the necessary header
// Based on the provided code, we need the AnsiColorSequenceIterator struct
// Include the actual header that declares AnsiColorSequenceIterator
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_98 : public ::testing::Test {
protected:
};

// Test SequenceSize on empty string (no sequences)
TEST_F(AnsiColorSequenceIteratorTest_98, EmptyString_NoSequence_98) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  // No sequences in empty string
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceSize());
}

// Test with no ANSI sequences present
TEST_F(AnsiColorSequenceIteratorTest_98, NoAnsiSequences_98) {
  std::string input = "hello world";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceSize());
}

// Test with a single ANSI color sequence
TEST_F(AnsiColorSequenceIteratorTest_98, SingleAnsiSequence_98) {
  // \033[31m is a typical ANSI color sequence (red)
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  // Should find the first sequence
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_GT(iter.SequenceSize(), 0u);
  EXPECT_EQ(iter.SequenceStart(), 0u);
}

// Test NextSequence to iterate through multiple sequences
TEST_F(AnsiColorSequenceIteratorTest_98, MultipleSequences_NextSequence_98) {
  std::string input = "\033[31mhello\033[0m world\033[32mtest\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  EXPECT_TRUE(iter.HasSequence());
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  size_t first_size = iter.SequenceSize();
  EXPECT_EQ(first_size, first_end - first_start);
  
  // Move to next sequence
  EXPECT_TRUE(iter.NextSequence());
  EXPECT_TRUE(iter.HasSequence());
  size_t second_start = iter.SequenceStart();
  EXPECT_GT(second_start, first_start);
}

// Test SequenceSize equals SequenceEnd minus SequenceStart
TEST_F(AnsiColorSequenceIteratorTest_98, SequenceSizeConsistency_98) {
  std::string input = "\033[1;31mbold red\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
  }
}

// Test SequenceContains
TEST_F(AnsiColorSequenceIteratorTest_98, SequenceContains_InsideSequence_98) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  ASSERT_TRUE(iter.HasSequence());
  size_t start = iter.SequenceStart();
  // An index inside the sequence should return true
  if (iter.SequenceSize() > 0) {
    EXPECT_TRUE(iter.SequenceContains(start));
  }
}

// Test SequenceContains with index outside sequence
TEST_F(AnsiColorSequenceIteratorTest_98, SequenceContains_OutsideSequence_98) {
  std::string input = "abc\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  if (iter.HasSequence()) {
    // Index 0 is 'a', which should be before the sequence
    if (iter.SequenceStart() > 0) {
      EXPECT_FALSE(iter.SequenceContains(0));
    }
  }
}

// Test Reset functionality
TEST_F(AnsiColorSequenceIteratorTest_98, Reset_ReturnsToFirstSequence_98) {
  std::string input = "\033[31mhello\033[0m world\033[32mtest\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  ASSERT_TRUE(iter.HasSequence());
  size_t first_start = iter.SequenceStart();
  
  // Advance to next
  iter.NextSequence();
  
  // Reset
  iter.Reset();
  
  // Should be back at first sequence (or initial state)
  if (iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceStart(), first_start);
  }
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_98, NextSequence_ReturnsFalseAtEnd_98) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  ASSERT_TRUE(iter.HasSequence());
  
  // Iterate until no more sequences
  bool found_next = true;
  int count = 0;
  while (found_next && count < 100) {
    found_next = iter.NextSequence();
    count++;
  }
  // Eventually NextSequence should return false
  EXPECT_FALSE(found_next);
}

// Test with only ANSI escape sequence and no regular text
TEST_F(AnsiColorSequenceIteratorTest_98, OnlyAnsiSequence_98) {
  std::string input = "\033[31m";
  AnsiColorSequenceIterator iter(input);
  
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceSize(), input.size());
}

// Test string with incomplete ANSI sequence (just ESC)
TEST_F(AnsiColorSequenceIteratorTest_98, IncompleteEscapeSequence_98) {
  std::string input = "\033";
  AnsiColorSequenceIterator iter(input);
  // Incomplete sequence may or may not be detected
  // Just verify no crash and consistent state
  if (iter.HasSequence()) {
    EXPECT_LE(iter.SequenceEnd(), input.size());
  }
}

// Test string with ESC but no bracket (not a CSI sequence)
TEST_F(AnsiColorSequenceIteratorTest_98, EscapeWithoutBracket_98) {
  std::string input = "\033Xhello";
  AnsiColorSequenceIterator iter(input);
  // This may or may not be recognized as a sequence
  // Just ensure no crash
  if (!iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceSize(), 0u);
  }
}

// Test SequenceEnd is always >= SequenceStart
TEST_F(AnsiColorSequenceIteratorTest_98, SequenceEndGreaterOrEqualStart_98) {
  std::string input = "\033[0m\033[1m\033[31m";
  AnsiColorSequenceIterator iter(input);
  
  while (iter.HasSequence()) {
    EXPECT_GE(iter.SequenceEnd(), iter.SequenceStart());
    EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
    if (!iter.NextSequence()) break;
  }
}

// Test with long ANSI sequence parameters
TEST_F(AnsiColorSequenceIteratorTest_98, LongAnsiParameters_98) {
  std::string input = "\033[38;2;255;128;0mcolored text\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_GT(iter.SequenceSize(), 0u);
}

// Test NextSequence on string with no sequences
TEST_F(AnsiColorSequenceIteratorTest_98, NextSequence_NoSequences_98) {
  std::string input = "plain text no colors";
  AnsiColorSequenceIterator iter(input);
  
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

// Test Reset on empty string
TEST_F(AnsiColorSequenceIteratorTest_98, Reset_EmptyString_98) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  iter.Reset();
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceSize(), 0u);
}

// Test multiple resets
TEST_F(AnsiColorSequenceIteratorTest_98, MultipleResets_98) {
  std::string input = "\033[31mred\033[0m";
  AnsiColorSequenceIterator iter(input);
  
  ASSERT_TRUE(iter.HasSequence());
  size_t original_start = iter.SequenceStart();
  
  iter.Reset();
  if (iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceStart(), original_start);
  }
  
  iter.Reset();
  if (iter.HasSequence()) {
    EXPECT_EQ(iter.SequenceStart(), original_start);
  }
}
