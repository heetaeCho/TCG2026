#include <gtest/gtest.h>
#include <string>

// Include the header for the class under test
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_99 : public ::testing::Test {
protected:
};

// Test SequenceContains with no ANSI sequences in the string
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsNoSequences_99) {
  std::string input = "hello world";
  AnsiColorSequenceIterator iter(input);
  // With no sequences, cur_start_ and cur_end_ should both be 0,
  // so SequenceContains should return false for any index
  EXPECT_FALSE(iter.SequenceContains(0));
  EXPECT_FALSE(iter.SequenceContains(1));
  EXPECT_FALSE(iter.SequenceContains(5));
  EXPECT_FALSE(iter.SequenceContains(10));
}

// Test SequenceContains on empty string
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsEmptyString_99) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.SequenceContains(0));
  EXPECT_FALSE(iter.SequenceContains(1));
}

// Test SequenceContains with an ANSI escape sequence
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsWithAnsiSequence_99) {
  // \033[31m is a typical ANSI color sequence (red)
  std::string input = "hello \033[31mworld\033[0m";
  AnsiColorSequenceIterator iter(input);

  // Before calling NextSequence, default start/end are 0, so SequenceContains(0) 
  // would depend on whether 0 >= 0 && 0 < 0 which is false
  EXPECT_FALSE(iter.SequenceContains(0));

  // Find the first sequence
  if (iter.HasSequence()) {
    size_t start = iter.SequenceStart();
    size_t end = iter.SequenceEnd();

    // Indices within the sequence should return true
    for (size_t i = start; i < end; ++i) {
      EXPECT_TRUE(iter.SequenceContains(i));
    }

    // Index just before the sequence start should return false (if start > 0)
    if (start > 0) {
      EXPECT_FALSE(iter.SequenceContains(start - 1));
    }

    // Index at end should return false (half-open interval)
    EXPECT_FALSE(iter.SequenceContains(end));

    // Index well beyond should return false
    EXPECT_FALSE(iter.SequenceContains(input.size() + 10));
  }
}

// Test HasSequence with no ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_99, HasSequenceNoAnsi_99) {
  std::string input = "plain text";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

// Test HasSequence with ANSI sequence present
TEST_F(AnsiColorSequenceIteratorTest_99, HasSequenceWithAnsi_99) {
  std::string input = "\033[31mred\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
}

// Test NextSequence iterates through multiple sequences
TEST_F(AnsiColorSequenceIteratorTest_99, NextSequenceMultipleSequences_99) {
  std::string input = "\033[31mhello\033[0m \033[32mworld\033[0m";
  AnsiColorSequenceIterator iter(input);

  int count = 0;
  if (iter.HasSequence()) {
    count++;
    while (iter.NextSequence()) {
      count++;
    }
  }
  // There should be 4 ANSI sequences: \033[31m, \033[0m, \033[32m, \033[0m
  EXPECT_EQ(count, 4);
}

// Test SequenceSize returns the length of the current sequence
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceSizeCorrect_99) {
  // \033[31m is 5 characters: ESC [ 3 1 m
  std::string input = "\033[31mtext";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    size_t size = iter.SequenceSize();
    EXPECT_EQ(size, iter.SequenceEnd() - iter.SequenceStart());
    EXPECT_GT(size, 0u);
  }
}

// Test Reset resets the iterator state
TEST_F(AnsiColorSequenceIteratorTest_99, ResetResetsIterator_99) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    size_t first_start = iter.SequenceStart();

    // Advance to next
    iter.NextSequence();

    // Reset and check we're back at the beginning
    iter.Reset();

    if (iter.HasSequence()) {
      EXPECT_EQ(iter.SequenceStart(), first_start);
    }
  }
}

// Test SequenceContains boundary: index exactly at start
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsBoundaryAtStart_99) {
  std::string input = "\033[31mtext";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    size_t start = iter.SequenceStart();
    EXPECT_TRUE(iter.SequenceContains(start));
  }
}

// Test SequenceContains boundary: index exactly at end - 1
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsBoundaryAtLastChar_99) {
  std::string input = "\033[31mtext";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    size_t end = iter.SequenceEnd();
    EXPECT_TRUE(iter.SequenceContains(end - 1));
    EXPECT_FALSE(iter.SequenceContains(end));
  }
}

// Test SequenceContains with sequence not at beginning of string
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsMidString_99) {
  std::string input = "prefix\033[31mcolored\033[0msuffix";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    size_t start = iter.SequenceStart();
    // "prefix" is 6 chars, so sequence should start at index 6
    EXPECT_EQ(start, 6u);
    EXPECT_FALSE(iter.SequenceContains(5));
    EXPECT_TRUE(iter.SequenceContains(6));
  }
}

// Test with only escape character but no complete sequence
TEST_F(AnsiColorSequenceIteratorTest_99, IncompleteEscapeSequence_99) {
  std::string input = "hello\033world";
  AnsiColorSequenceIterator iter(input);
  // An incomplete escape sequence may or may not be detected
  // We just verify it doesn't crash
  bool has = iter.HasSequence();
  if (has) {
    iter.SequenceStart();
    iter.SequenceEnd();
    iter.SequenceSize();
  }
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_99, NextSequenceReturnsFalseAtEnd_99) {
  std::string input = "\033[31mtext\033[0m";
  AnsiColorSequenceIterator iter(input);

  if (iter.HasSequence()) {
    // There are two sequences, iterate through them
    bool found_next = iter.NextSequence();
    if (found_next) {
      // After the last sequence, NextSequence should return false
      bool more = iter.NextSequence();
      EXPECT_FALSE(more);
    }
  }
}

// Test SequenceContains with SIZE_MAX as index
TEST_F(AnsiColorSequenceIteratorTest_99, SequenceContainsMaxIndex_99) {
  std::string input = "\033[31mtest\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.SequenceContains(SIZE_MAX));
}

// Test with string containing only ANSI sequences and no visible text
TEST_F(AnsiColorSequenceIteratorTest_99, OnlyAnsiSequences_99) {
  std::string input = "\033[31m\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());

  if (iter.HasSequence()) {
    size_t start1 = iter.SequenceStart();
    size_t end1 = iter.SequenceEnd();
    EXPECT_LT(start1, end1);

    for (size_t i = start1; i < end1; ++i) {
      EXPECT_TRUE(iter.SequenceContains(i));
    }
  }
}
