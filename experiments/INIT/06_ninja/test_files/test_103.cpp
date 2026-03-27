// File: elide_middle_visible_input_chars_iterator_test_103.cc

#include <string>
#include <vector>

#include "gtest/gtest.h"

// Depending on your build layout, you may instead include a header that
// provides VisibleInputCharsIterator. For this kata-style setup, we assume
// the struct is available from elide_middle.cc.
#include "elide_middle.cc"

// Test suite name and each test name include TEST_ID (103) as requested.

TEST(VisibleInputCharsIteratorTest_103, EmptyInput_HasNoChar_103) {
  std::string input;
  VisibleInputCharsIterator iter(input);

  // For empty input, iterator should report no characters.
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(0u, iter.InputIndex());
  EXPECT_EQ(0u, iter.VisiblePosition());
}

TEST(VisibleInputCharsIteratorTest_103, NoAnsi_AllVisiblePositionsMatchIndex_103) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);

  // Without any ANSI sequences, every character is visible and
  // VisiblePosition should match the current InputIndex for each step.
  size_t step = 0;
  while (iter.HasChar()) {
    EXPECT_EQ(step, iter.InputIndex()) << "InputIndex mismatch at step " << step;
    EXPECT_TRUE(iter.IsVisible()) << "Character at index " << step << " should be visible";
    EXPECT_EQ(step, iter.VisiblePosition())
        << "VisiblePosition should equal InputIndex when there are no ANSI sequences";
    iter.NextChar();
    ++step;
  }

  EXPECT_EQ(input.size(), step);
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(input.size(), iter.InputIndex());
  EXPECT_EQ(input.size(), iter.VisiblePosition());
}

TEST(VisibleInputCharsIteratorTest_103, OnlyAnsiSequences_NoVisibleChars_103) {
  // Two ANSI color sequences, no visible characters.
  const char esc = '\x1b';
  std::string input;
  input += esc;
  input += "[31m";  // \x1b[31m
  input += esc;
  input += "[0m";   // \x1b[0m

  VisibleInputCharsIterator iter(input);

  // All characters belong to ANSI sequences, so:
  // - IsVisible() should always be false
  // - VisiblePosition() should remain 0 for the whole traversal.
  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_FALSE(iter.IsVisible()) << "No character in a pure ANSI string should be visible";
    EXPECT_EQ(0u, iter.VisiblePosition())
        << "VisiblePosition should remain 0 when there are no visible characters";
    iter.NextChar();
    ++count;
  }

  EXPECT_EQ(input.size(), count);
  EXPECT_EQ(input.size(), iter.InputIndex());
}

TEST(VisibleInputCharsIteratorTest_103, StringWithAnsiSequences_VisibilityAndPositions_103) {
  // Input layout:
  // indices:  0   1   2   3   4   5   6    7   8   9  10  11  12  13  14
  // chars :  'a' 'b' ESC '[' '3' '1' 'm' 'c' 'd' ESC '[' '0' 'm' 'e' 'f'
  //
  // Visible characters: indices 0,1,7,8,13,14.
  // For each index k, VisiblePosition(k) = number of visible chars with index < k.
  const char esc = '\x1b';
  std::string input;
  input += "ab";
  input += esc;
  input += "[31m";
  input += "cd";
  input += esc;
  input += "[0m";
  input += "ef";

  ASSERT_EQ(15u, input.size());  // sanity check for the expectations below

  // Expected visibility per input index.
  std::vector<bool> expected_visible = {
      true,  // 0: 'a'
      true,  // 1: 'b'
      false, // 2: ESC
      false, // 3: '['
      false, // 4: '3'
      false, // 5: '1'
      false, // 6: 'm'
      true,  // 7: 'c'
      true,  // 8: 'd'
      false, // 9: ESC
      false, // 10: '['
      false, // 11: '0'
      false, // 12: 'm'
      true,  // 13: 'e'
      true   // 14: 'f'
  };

  // Expected visible positions (0-based) for each input index.
  // Computed as: count of visible indices < k.
  std::vector<size_t> expected_visible_pos = {
      0, // k=0: none before
      1, // k=1: {0}
      2, // k=2: {0,1}
      2, // k=3: {0,1}
      2, // k=4: {0,1}
      2, // k=5: {0,1}
      2, // k=6: {0,1}
      2, // k=7: {0,1}
      3, // k=8: {0,1,7}
      4, // k=9: {0,1,7,8}
      4, // k=10
      4, // k=11
      4, // k=12
      4, // k=13
      5  // k=14: {0,1,7,8,13}
  };

  VisibleInputCharsIterator iter(input);

  size_t step = 0;
  while (iter.HasChar()) {
    ASSERT_LT(step, expected_visible.size());

    EXPECT_EQ(step, iter.InputIndex()) << "InputIndex should advance sequentially";
    EXPECT_EQ(expected_visible_pos[step], iter.VisiblePosition())
        << "Unexpected VisiblePosition at input index " << step;
    EXPECT_EQ(expected_visible[step], iter.IsVisible())
        << "Unexpected IsVisible at input index " << step;

    iter.NextChar();
    ++step;
  }

  EXPECT_EQ(expected_visible.size(), step);
  EXPECT_EQ(input.size(), iter.InputIndex());
}

TEST(VisibleInputCharsIteratorTest_103, InvalidEscapeSequence_TreatedAsVisible_103) {
  // ESC not followed by '[' should *not* form a color sequence.
  const char esc = '\x1b';
  std::string input;
  input += "ab";
  input += esc;
  input += "xx";  // Not a valid color sequence
  input += "cd";

  VisibleInputCharsIterator iter(input);

  // Since there is no valid ANSI color sequence, all characters
  // should be visible and VisiblePosition should track InputIndex.
  size_t step = 0;
  while (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible())
        << "Invalid escape sequence characters should still be treated as visible";
    EXPECT_EQ(step, iter.InputIndex());
    EXPECT_EQ(step, iter.VisiblePosition())
        << "VisiblePosition should equal InputIndex when no ANSI sequences are detected";
    iter.NextChar();
    ++step;
  }

  EXPECT_EQ(input.size(), step);
}
