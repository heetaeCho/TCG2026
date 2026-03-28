#include "gtest/gtest.h"
#include "elide_middle.h"
#include <string>

class VisibleInputCharsIteratorTest_103 : public ::testing::Test {
protected:
};

TEST_F(VisibleInputCharsIteratorTest_103, EmptyString_103) {
  std::string input = "";
  VisibleInputCharsIterator iter(input);
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_103, SingleChar_103) {
  std::string input = "a";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());
  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 1u);
}

TEST_F(VisibleInputCharsIteratorTest_103, PlainTextIteration_103) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  
  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_EQ(iter.InputIndex(), count);
    EXPECT_EQ(iter.VisiblePosition(), count);
    EXPECT_TRUE(iter.IsVisible());
    iter.NextChar();
    count++;
  }
  EXPECT_EQ(count, 5u);
  EXPECT_EQ(iter.InputIndex(), 5u);
}

TEST_F(VisibleInputCharsIteratorTest_103, InputIndexStartsAtZero_103) {
  std::string input = "abc";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.InputIndex(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_103, VisiblePositionStartsAtZero_103) {
  std::string input = "abc";
  VisibleInputCharsIterator iter(input);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_103, AnsiEscapeSequenceNotVisible_103) {
  // ANSI escape sequence: ESC[31m (red color)
  std::string input = "\x1b[31mhello";
  VisibleInputCharsIterator iter(input);
  
  bool found_invisible = false;
  bool found_visible = false;
  size_t visible_count = 0;
  
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      found_visible = true;
      visible_count++;
    } else {
      found_invisible = true;
    }
    iter.NextChar();
  }
  
  EXPECT_TRUE(found_invisible);
  EXPECT_TRUE(found_visible);
  EXPECT_EQ(visible_count, 5u); // "hello" has 5 visible chars
}

TEST_F(VisibleInputCharsIteratorTest_103, AnsiSequenceDoesNotAdvanceVisiblePosition_103) {
  // ESC[0m is a reset sequence (4 bytes), followed by "ab"
  std::string input = "\x1b[0mab";
  VisibleInputCharsIterator iter(input);
  
  // Skip through ANSI sequence characters
  while (iter.HasChar() && !iter.IsVisible()) {
    EXPECT_EQ(iter.VisiblePosition(), 0u);
    iter.NextChar();
  }
  
  // Now we should be at 'a'
  EXPECT_TRUE(iter.HasChar());
  EXPECT_TRUE(iter.IsVisible());
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  iter.NextChar();
  
  // Now at 'b'
  EXPECT_TRUE(iter.HasChar());
  EXPECT_TRUE(iter.IsVisible());
  EXPECT_EQ(iter.VisiblePosition(), 1u);
  iter.NextChar();
  
  EXPECT_FALSE(iter.HasChar());
}

TEST_F(VisibleInputCharsIteratorTest_103, MultipleAnsiSequences_103) {
  // Two ANSI sequences with text between
  std::string input = "\x1b[31mhi\x1b[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t visible_count = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      visible_count++;
    }
    iter.NextChar();
  }
  EXPECT_EQ(visible_count, 2u); // "hi"
}

TEST_F(VisibleInputCharsIteratorTest_103, OnlyAnsiSequence_103) {
  std::string input = "\x1b[31m";
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

TEST_F(VisibleInputCharsIteratorTest_103, InputIndexMatchesStringLength_103) {
  std::string input = "test";
  VisibleInputCharsIterator iter(input);
  
  while (iter.HasChar()) {
    iter.NextChar();
  }
  EXPECT_EQ(iter.InputIndex(), input.size());
}

TEST_F(VisibleInputCharsIteratorTest_103, InputIndexMatchesStringLengthWithAnsi_103) {
  std::string input = "\x1b[1mtest\x1b[0m";
  VisibleInputCharsIterator iter(input);
  
  while (iter.HasChar()) {
    iter.NextChar();
  }
  EXPECT_EQ(iter.InputIndex(), input.size());
}

TEST_F(VisibleInputCharsIteratorTest_103, VisiblePositionCountsOnlyVisible_103) {
  std::string input = "\x1b[32mabc\x1b[0m";
  VisibleInputCharsIterator iter(input);
  
  size_t last_visible_pos = 0;
  bool has_visible = false;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      last_visible_pos = iter.VisiblePosition();
      has_visible = true;
    }
    iter.NextChar();
  }
  EXPECT_TRUE(has_visible);
  EXPECT_EQ(last_visible_pos, 2u); // 0, 1, 2 for "abc"
}

TEST_F(VisibleInputCharsIteratorTest_103, SingleCharString_103) {
  std::string input = "x";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());
  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
}

TEST_F(VisibleInputCharsIteratorTest_103, LongPlainText_103) {
  std::string input(100, 'a');
  VisibleInputCharsIterator iter(input);
  
  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(iter.InputIndex(), count);
    EXPECT_EQ(iter.VisiblePosition(), count);
    iter.NextChar();
    count++;
  }
  EXPECT_EQ(count, 100u);
}
