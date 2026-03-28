// File: elide_middle_visible_input_chars_iterator_test_104.cc

#include "gtest/gtest.h"

#include "elide_middle.cc"  // Provides VisibleInputCharsIterator.

#include <cctype>
#include <string>
#include <vector>

class VisibleInputCharsIteratorTest_104 : public ::testing::Test {};

// Empty input: iterator should immediately report no characters.
TEST_F(VisibleInputCharsIteratorTest_104, EmptyStringHasNoChars_104) {
  std::string input;
  VisibleInputCharsIterator iter(input);

  EXPECT_FALSE(iter.HasChar());
  // For completeness, these should remain at their initial positions.
  EXPECT_EQ(0u, iter.InputIndex());
  EXPECT_EQ(0u, iter.VisiblePosition());
}

// Input without any ANSI sequences: all chars visible and visible position
// should match the input index.
TEST_F(VisibleInputCharsIteratorTest_104,
       NoAnsi_AllCharsVisibleAndPositionsIncrease_104) {
  std::string input = "abcd";
  VisibleInputCharsIterator iter(input);

  size_t expected_index = 0;
  while (iter.HasChar()) {
    EXPECT_EQ(expected_index, iter.InputIndex());
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(expected_index, iter.VisiblePosition());

    iter.NextChar();
    ++expected_index;
  }

  EXPECT_EQ(input.size(), expected_index);
  // After consuming all visible chars, visible position should equal size.
  EXPECT_EQ(input.size(), iter.VisiblePosition());
}

// Input with ANSI color sequences in the middle: visible positions for
// alphabetic characters should be continuous and unaffected by ANSI bytes.
TEST_F(VisibleInputCharsIteratorTest_104,
       WithAnsi_VisiblePositionsSkipColorSequences_104) {
  // "ab" + red color on + "cd" + reset + "ef"
  std::string input = "ab\x1b[31mcd\x1b[0mef";

  VisibleInputCharsIterator iter(input);

  std::vector<char> letters;
  std::vector<size_t> visible_positions;
  std::vector<bool> visible_flags;

  while (iter.HasChar()) {
    char c = input[iter.InputIndex()];
    if (std::isalpha(static_cast<unsigned char>(c))) {
      letters.push_back(c);
      visible_positions.push_back(iter.VisiblePosition());
      visible_flags.push_back(iter.IsVisible());
    }
    iter.NextChar();
  }

  // We only care about alphabetic characters; ANSI bytes are implementation
  // details of the escape sequences.
  std::vector<char> expected_letters = {'a', 'b', 'c', 'd', 'e', 'f'};
  ASSERT_EQ(expected_letters.size(), letters.size());
  EXPECT_EQ(expected_letters, letters);

  std::vector<size_t> expected_positions = {0, 1, 2, 3, 4, 5};
  ASSERT_EQ(expected_positions.size(), visible_positions.size());
  EXPECT_EQ(expected_positions, visible_positions);

  // All alphabetic characters must be visible.
  for (bool v : visible_flags) {
    EXPECT_TRUE(v);
  }
}

// ANSI sequences at the beginning and end should not contribute to visible
// positions; first visible char should start at position 0.
TEST_F(VisibleInputCharsIteratorTest_104,
       LeadingAndTrailingAnsiVisiblePositions_104) {
  // red on + "abc" + reset
  std::string input = "\x1b[31mabc\x1b[0m";

  VisibleInputCharsIterator iter(input);

  std::vector<char> letters;
  std::vector<size_t> visible_positions;
  std::vector<bool> visible_flags;

  while (iter.HasChar()) {
    char c = input[iter.InputIndex()];
    if (std::isalpha(static_cast<unsigned char>(c))) {
      letters.push_back(c);
      visible_positions.push_back(iter.VisiblePosition());
      visible_flags.push_back(iter.IsVisible());
    }
    iter.NextChar();
  }

  std::vector<char> expected_letters = {'a', 'b', 'c'};
  ASSERT_EQ(expected_letters.size(), letters.size());
  EXPECT_EQ(expected_letters, letters);

  std::vector<size_t> expected_positions = {0, 1, 2};
  ASSERT_EQ(expected_positions.size(), visible_positions.size());
  EXPECT_EQ(expected_positions, visible_positions);

  for (bool v : visible_flags) {
    EXPECT_TRUE(v);
  }
}

// Input consisting only of ANSI color sequences: no visible characters
// should be reported, but the iterator should still traverse all chars.
TEST_F(VisibleInputCharsIteratorTest_104,
       AllAnsi_NoVisibleCharacters_104) {
  std::string input = "\x1b[31m\x1b[0m";

  VisibleInputCharsIterator iter(input);

  bool any_visible = false;
  size_t count = 0;

  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      any_visible = true;
    }
    ++count;
    iter.NextChar();
  }

  EXPECT_FALSE(any_visible);
  EXPECT_EQ(input.size(), count);
}
