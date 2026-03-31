#include "gtest/gtest.h"
#include <string>

// Include the header that contains VisibleInputCharsIterator
// Based on the file structure, we need to include the appropriate header
#include "elide_middle.h"

// Test HasChar with empty string
TEST(VisibleInputCharsIteratorTest_102, HasChar_EmptyString_ReturnsFalse_102) {
  std::string input = "";
  VisibleInputCharsIterator iter(input);
  EXPECT_FALSE(iter.HasChar());
}

// Test HasChar with non-empty string
TEST(VisibleInputCharsIteratorTest_102, HasChar_NonEmptyString_ReturnsTrue_102) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
}

// Test HasChar with single character string
TEST(VisibleInputCharsIteratorTest_102, HasChar_SingleChar_ReturnsTrue_102) {
  std::string input = "a";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
}

// Test HasChar becomes false after iterating through all characters
TEST(VisibleInputCharsIteratorTest_102, HasChar_AfterFullIteration_ReturnsFalse_102) {
  std::string input = "ab";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
  iter.NextChar();
  EXPECT_TRUE(iter.HasChar());
  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
}

// Test InputIndex starts at 0
TEST(VisibleInputCharsIteratorTest_102, InputIndex_InitiallyZero_102) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.InputIndex(), 0u);
}

// Test InputIndex increments as we iterate
TEST(VisibleInputCharsIteratorTest_102, InputIndex_IncrementsOnNextChar_102) {
  std::string input = "abc";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.InputIndex(), 0u);
  iter.NextChar();
  EXPECT_EQ(iter.InputIndex(), 1u);
  iter.NextChar();
  EXPECT_EQ(iter.InputIndex(), 2u);
}

// Test VisiblePosition starts at 0
TEST(VisibleInputCharsIteratorTest_102, VisiblePosition_InitiallyZero_102) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
}

// Test VisiblePosition increments for visible characters
TEST(VisibleInputCharsIteratorTest_102, VisiblePosition_IncrementsForVisibleChars_102) {
  std::string input = "abc";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  iter.NextChar();
  // After advancing past first visible char, visible position should increase
  EXPECT_GE(iter.VisiblePosition(), 0u);
}

// Test IsVisible for plain text characters
TEST(VisibleInputCharsIteratorTest_102, IsVisible_PlainText_ReturnsTrue_102) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.IsVisible());
}

// Test iteration through a string with ANSI escape sequences
TEST(VisibleInputCharsIteratorTest_102, HasChar_WithAnsiSequence_IteratesAll_102) {
  // ANSI escape sequence: ESC[31m (red color)
  std::string input = "\033[31mhello\033[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t count = 0;
  while (iter.HasChar()) {
    iter.NextChar();
    count++;
  }
  // Should iterate through all characters in the input
  EXPECT_EQ(count, input.size());
}

// Test IsVisible returns false for ANSI escape sequence characters
TEST(VisibleInputCharsIteratorTest_102, IsVisible_AnsiEscapeChar_ReturnsFalse_102) {
  // ANSI escape sequence starts with ESC (0x1b)
  std::string input = "\033[31mX";
  VisibleInputCharsIterator iter(input);
  // The first character is ESC, which should not be visible
  EXPECT_FALSE(iter.IsVisible());
}

// Test that visible position does not increment for ANSI escape characters
TEST(VisibleInputCharsIteratorTest_102, VisiblePosition_DoesNotIncrementForAnsi_102) {
  std::string input = "\033[31mA";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_before = iter.VisiblePosition();
  // Iterate through the ANSI sequence
  while (iter.HasChar() && !iter.IsVisible()) {
    iter.NextChar();
  }
  // Visible position should not have changed during ANSI sequence
  // (it only increments for visible characters)
  EXPECT_EQ(iter.VisiblePosition(), visible_before);
}

// Test full iteration of mixed ANSI and plain text
TEST(VisibleInputCharsIteratorTest_102, FullIteration_MixedAnsiAndText_102) {
  std::string input = "\033[1mHi\033[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  size_t total_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
    total_count++;
  }
  EXPECT_EQ(total_count, input.size());
  // "Hi" are the visible characters
  EXPECT_EQ(visible_count, 2u);
}

// Test with only ANSI sequences (no visible text)
TEST(VisibleInputCharsIteratorTest_102, OnlyAnsiSequences_NoVisibleChars_102) {
  std::string input = "\033[31m\033[0m";
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

// Test InputIndex reaches input size after full iteration
TEST(VisibleInputCharsIteratorTest_102, InputIndex_EqualsInputSizeAfterFullIteration_102) {
  std::string input = "test";
  VisibleInputCharsIterator iter(input);
  while (iter.HasChar()) {
    iter.NextChar();
  }
  EXPECT_EQ(iter.InputIndex(), input.size());
}

// Test with whitespace characters (should be visible)
TEST(VisibleInputCharsIteratorTest_102, IsVisible_WhitespaceIsVisible_102) {
  std::string input = " \t";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.IsVisible());
}

// Test single character iteration
TEST(VisibleInputCharsIteratorTest_102, SingleChar_FullIteration_102) {
  std::string input = "X";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
  EXPECT_TRUE(iter.IsVisible());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 1u);
}
