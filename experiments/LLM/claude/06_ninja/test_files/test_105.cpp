#include "gtest/gtest.h"
#include <string>

// Include the header or source that defines the classes
// Based on the file structure, we need to include the relevant header
#include "elide_middle.h"

// If the header doesn't exist separately, we might need to include the .cc
// This depends on the build setup

class AnsiColorSequenceIteratorTest_105 : public ::testing::Test {
protected:
};

class VisibleInputCharsIteratorTest_105 : public ::testing::Test {
protected:
};

// ==========================================
// AnsiColorSequenceIterator Tests
// ==========================================

TEST_F(AnsiColorSequenceIteratorTest_105, EmptyString_105) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_105, NoAnsiSequences_105) {
  std::string input = "Hello, World!";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_105, SingleAnsiSequence_105) {
  // ANSI escape sequence: ESC[31m (red color)
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  // The sequence should end after 'm'
  EXPECT_GT(iter.SequenceEnd(), iter.SequenceStart());
  EXPECT_GT(iter.SequenceSize(), 0u);
}

TEST_F(AnsiColorSequenceIteratorTest_105, SequenceContainsInsideSequence_105) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  size_t start = iter.SequenceStart();
  size_t end = iter.SequenceEnd();
  // Indices within the sequence should be contained
  for (size_t i = start; i < end; ++i) {
    EXPECT_TRUE(iter.SequenceContains(i));
  }
  // Index after the sequence should not be contained (if only one sequence)
  if (end < input.size()) {
    EXPECT_FALSE(iter.SequenceContains(end));
  }
}

TEST_F(AnsiColorSequenceIteratorTest_105, SequenceContainsOutsideSequence_105) {
  std::string input = "Hi\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  // Index 0 and 1 ('H' and 'i') should not be in the sequence
  EXPECT_FALSE(iter.SequenceContains(0));
  EXPECT_FALSE(iter.SequenceContains(1));
}

TEST_F(AnsiColorSequenceIteratorTest_105, MultipleSequences_105) {
  std::string input = "\033[31mRed\033[32mGreen\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  EXPECT_LT(first_start, first_end);
  
  EXPECT_TRUE(iter.NextSequence());
  size_t second_start = iter.SequenceStart();
  size_t second_end = iter.SequenceEnd();
  EXPECT_LT(second_start, second_end);
  EXPECT_GE(second_start, first_end);
  
  EXPECT_TRUE(iter.NextSequence());
  size_t third_start = iter.SequenceStart();
  size_t third_end = iter.SequenceEnd();
  EXPECT_LT(third_start, third_end);
  EXPECT_GE(third_start, second_end);
  
  // No more sequences
  EXPECT_FALSE(iter.NextSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_105, Reset_105) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  size_t first_start = iter.SequenceStart();
  
  iter.NextSequence();
  
  iter.Reset();
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), first_start);
}

TEST_F(AnsiColorSequenceIteratorTest_105, NextSequenceOnEmpty_105) {
  std::string input = "Hello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_105, SequenceSizeConsistency_105) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceSize(), iter.SequenceEnd() - iter.SequenceStart());
}

// ==========================================
// VisibleInputCharsIterator Tests
// ==========================================

TEST_F(VisibleInputCharsIteratorTest_105, EmptyString_105) {
  std::string input = "";
  VisibleInputCharsIterator iter(input);
  EXPECT_FALSE(iter.HasChar());
}

TEST_F(VisibleInputCharsIteratorTest_105, PlainTextAllVisible_105) {
  std::string input = "Hello";
  VisibleInputCharsIterator iter(input);
  
  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(iter.InputIndex(), count);
    EXPECT_EQ(iter.VisiblePosition(), count);
    iter.NextChar();
    count++;
  }
  EXPECT_EQ(count, 5u);
}

TEST_F(VisibleInputCharsIteratorTest_105, AnsiCharsNotVisible_105) {
  // ESC[31m is an ANSI sequence, characters within it should not be visible
  std::string input = "\033[31mHello";
  VisibleInputCharsIterator iter(input);
  
  bool found_invisible = false;
  bool found_visible = false;
  
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      found_visible = true;
    } else {
      found_invisible = true;
    }
    iter.NextChar();
  }
  
  EXPECT_TRUE(found_invisible);
  EXPECT_TRUE(found_visible);
}

TEST_F(VisibleInputCharsIteratorTest_105, VisiblePositionSkipsAnsi_105) {
  // ESC[31m is typically 5 bytes: \033 [ 3 1 m
  std::string input = "\033[31mAB";
  VisibleInputCharsIterator iter(input);
  
  size_t max_visible_pos = 0;
  size_t visible_count = 0;
  
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      max_visible_pos = iter.VisiblePosition();
      visible_count++;
    }
    iter.NextChar();
  }
  
  // "AB" should be the only visible characters
  EXPECT_EQ(visible_count, 2u);
}

TEST_F(VisibleInputCharsIteratorTest_105, InputIndexMonotonicallyIncreases_105) {
  std::string input = "\033[31mHello\033[0mWorld";
  VisibleInputCharsIterator iter(input);
  
  size_t prev_index = 0;
  bool first = true;
  
  while (iter.HasChar()) {
    size_t cur = iter.InputIndex();
    if (!first) {
      EXPECT_GT(cur, prev_index);
    }
    prev_index = cur;
    first = false;
    iter.NextChar();
  }
}

TEST_F(VisibleInputCharsIteratorTest_105, SingleCharString_105) {
  std::string input = "A";
  VisibleInputCharsIterator iter(input);
  
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());
  
  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
}

TEST_F(VisibleInputCharsIteratorTest_105, OnlyAnsiSequence_105) {
  std::string input = "\033[31m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  
  // No visible characters, only ANSI sequence
  EXPECT_EQ(visible_count, 0u);
}

TEST_F(VisibleInputCharsIteratorTest_105, MultipleAnsiSequencesWithText_105) {
  std::string input = "\033[1m\033[31mHi\033[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  
  // Only "Hi" should be visible = 2 visible characters
  EXPECT_EQ(visible_count, 2u);
}

TEST_F(VisibleInputCharsIteratorTest_105, VisiblePositionStartsAtZero_105) {
  std::string input = "Test";
  VisibleInputCharsIterator iter(input);
  
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.VisiblePosition(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_105, InputIndexStartsAtZero_105) {
  std::string input = "Test";
  VisibleInputCharsIterator iter(input);
  
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_105, LongStringTraversal_105) {
  std::string input = "abcdefghijklmnopqrstuvwxyz";
  VisibleInputCharsIterator iter(input);
  
  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(iter.InputIndex(), count);
    EXPECT_EQ(iter.VisiblePosition(), count);
    iter.NextChar();
    count++;
  }
  EXPECT_EQ(count, 26u);
}

TEST_F(VisibleInputCharsIteratorTest_105, AnsiAtEnd_105) {
  std::string input = "Hello\033[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  
  EXPECT_EQ(visible_count, 5u);  // "Hello"
}

TEST_F(VisibleInputCharsIteratorTest_105, AnsiAtBeginning_105) {
  std::string input = "\033[0mHello";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  
  EXPECT_EQ(visible_count, 5u);  // "Hello"
}

TEST_F(VisibleInputCharsIteratorTest_105, ConsecutiveAnsiSequences_105) {
  std::string input = "\033[1m\033[31m\033[42m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  
  EXPECT_EQ(visible_count, 0u);
}
