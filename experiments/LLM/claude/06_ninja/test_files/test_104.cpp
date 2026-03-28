#include "gtest/gtest.h"
#include <string>

// Include the header that contains VisibleInputCharsIterator
// Based on the file structure, this likely lives in elide_middle.h
#include "elide_middle.h"

class VisibleInputCharsIteratorTest_104 : public ::testing::Test {
protected:
};

// Test empty string - no characters to iterate
TEST_F(VisibleInputCharsIteratorTest_104, EmptyString_104) {
  std::string input = "";
  VisibleInputCharsIterator it(input);
  EXPECT_FALSE(it.HasChar());
  EXPECT_EQ(it.VisiblePosition(), 0u);
  EXPECT_EQ(it.InputIndex(), 0u);
}

// Test simple string with no ANSI sequences
TEST_F(VisibleInputCharsIteratorTest_104, PlainString_104) {
  std::string input = "hello";
  VisibleInputCharsIterator it(input);
  
  EXPECT_TRUE(it.HasChar());
  EXPECT_EQ(it.VisiblePosition(), 0u);
  EXPECT_EQ(it.InputIndex(), 0u);
  EXPECT_TRUE(it.IsVisible());
  
  it.NextChar();
  EXPECT_TRUE(it.HasChar());
  EXPECT_EQ(it.VisiblePosition(), 1u);
  EXPECT_EQ(it.InputIndex(), 1u);
  EXPECT_TRUE(it.IsVisible());
}

// Test iterating through entire plain string
TEST_F(VisibleInputCharsIteratorTest_104, IterateEntirePlainString_104) {
  std::string input = "abc";
  VisibleInputCharsIterator it(input);
  
  size_t count = 0;
  while (it.HasChar()) {
    EXPECT_TRUE(it.IsVisible());
    EXPECT_EQ(it.VisiblePosition(), count);
    EXPECT_EQ(it.InputIndex(), count);
    it.NextChar();
    count++;
  }
  EXPECT_EQ(count, 3u);
  EXPECT_EQ(it.VisiblePosition(), 3u);
  EXPECT_FALSE(it.HasChar());
}

// Test single character string
TEST_F(VisibleInputCharsIteratorTest_104, SingleCharString_104) {
  std::string input = "x";
  VisibleInputCharsIterator it(input);
  
  EXPECT_TRUE(it.HasChar());
  EXPECT_EQ(it.VisiblePosition(), 0u);
  EXPECT_TRUE(it.IsVisible());
  
  it.NextChar();
  EXPECT_FALSE(it.HasChar());
  EXPECT_EQ(it.VisiblePosition(), 1u);
}

// Test string with ANSI escape sequence - escape chars should not be visible
TEST_F(VisibleInputCharsIteratorTest_104, StringWithAnsiSequence_104) {
  // \033[31m is a typical ANSI color code (red)
  std::string input = "\033[31mhello\033[0m";
  VisibleInputCharsIterator it(input);
  
  size_t visible_count = 0;
  size_t total_count = 0;
  while (it.HasChar()) {
    if (it.IsVisible()) {
      visible_count++;
    }
    it.NextChar();
    total_count++;
  }
  
  // "hello" has 5 visible characters
  EXPECT_EQ(it.VisiblePosition(), 5u);
  EXPECT_EQ(visible_count, 5u);
  // Total chars iterated should be the full input length
  EXPECT_EQ(total_count, input.size());
}

// Test string with ANSI sequence at the beginning
TEST_F(VisibleInputCharsIteratorTest_104, AnsiAtBeginning_104) {
  std::string input = "\033[1mtext";
  VisibleInputCharsIterator it(input);
  
  // First few chars should be non-visible (ANSI sequence)
  // Then "text" should be visible
  size_t visible_count = 0;
  while (it.HasChar()) {
    if (it.IsVisible()) {
      visible_count++;
    }
    it.NextChar();
  }
  EXPECT_EQ(visible_count, 4u);
  EXPECT_EQ(it.VisiblePosition(), 4u);
}

// Test string with only ANSI sequences, no visible content
TEST_F(VisibleInputCharsIteratorTest_104, OnlyAnsiSequences_104) {
  std::string input = "\033[31m\033[0m";
  VisibleInputCharsIterator it(input);
  
  while (it.HasChar()) {
    it.NextChar();
  }
  EXPECT_EQ(it.VisiblePosition(), 0u);
}

// Test that InputIndex tracks raw position correctly
TEST_F(VisibleInputCharsIteratorTest_104, InputIndexTracksRawPosition_104) {
  std::string input = "abcdef";
  VisibleInputCharsIterator it(input);
  
  for (size_t i = 0; i < 3; i++) {
    EXPECT_EQ(it.InputIndex(), i);
    it.NextChar();
  }
  EXPECT_EQ(it.InputIndex(), 3u);
}

// Test visible position stays consistent after ANSI sequences
TEST_F(VisibleInputCharsIteratorTest_104, VisiblePositionAfterAnsi_104) {
  std::string input = "a\033[31mb";
  VisibleInputCharsIterator it(input);
  
  // 'a' is visible
  EXPECT_TRUE(it.HasChar());
  EXPECT_TRUE(it.IsVisible());
  EXPECT_EQ(it.VisiblePosition(), 0u);
  it.NextChar();
  
  // Skip through ANSI sequence chars
  while (it.HasChar() && !it.IsVisible()) {
    it.NextChar();
  }
  
  // 'b' should have visible position 1
  if (it.HasChar()) {
    EXPECT_TRUE(it.IsVisible());
    EXPECT_EQ(it.VisiblePosition(), 1u);
  }
}

// Test with multiple ANSI sequences interspersed
TEST_F(VisibleInputCharsIteratorTest_104, MultipleAnsiSequences_104) {
  std::string input = "\033[1mA\033[31mB\033[0mC";
  VisibleInputCharsIterator it(input);
  
  size_t visible_count = 0;
  while (it.HasChar()) {
    if (it.IsVisible()) {
      visible_count++;
    }
    it.NextChar();
  }
  EXPECT_EQ(visible_count, 3u);
  EXPECT_EQ(it.VisiblePosition(), 3u);
}

// Test long plain string
TEST_F(VisibleInputCharsIteratorTest_104, LongPlainString_104) {
  std::string input(1000, 'x');
  VisibleInputCharsIterator it(input);
  
  size_t count = 0;
  while (it.HasChar()) {
    EXPECT_TRUE(it.IsVisible());
    it.NextChar();
    count++;
  }
  EXPECT_EQ(count, 1000u);
  EXPECT_EQ(it.VisiblePosition(), 1000u);
}

// Test initial state of VisiblePosition
TEST_F(VisibleInputCharsIteratorTest_104, InitialVisiblePositionIsZero_104) {
  std::string input = "test";
  VisibleInputCharsIterator it(input);
  EXPECT_EQ(it.VisiblePosition(), 0u);
}

// Test initial state of InputIndex
TEST_F(VisibleInputCharsIteratorTest_104, InitialInputIndexIsZero_104) {
  std::string input = "test";
  VisibleInputCharsIterator it(input);
  EXPECT_EQ(it.InputIndex(), 0u);
}
