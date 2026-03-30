// File: ./TestProjects/ninja/tests/visible_input_chars_iterator_test_105.cc

#include "gtest/gtest.h"

// Directly include the implementation to access internal helper structs
// (AnsiColorSequenceIterator, VisibleInputCharsIterator).
#include "elide_middle.cc"

class VisibleInputCharsIteratorTest_105 : public ::testing::Test {};

// Normal operation: no ANSI sequences -> every character is visible and
// visible position should match the input index.
TEST_F(VisibleInputCharsIteratorTest_105,
       AllCharsVisibleWhenNoAnsiSequences_105) {
  const std::string input = "hello world";
  VisibleInputCharsIterator iter(input);

  size_t steps = 0;
  while (iter.HasChar()) {
    const size_t index = iter.InputIndex();
    EXPECT_LT(index, input.size());
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(index, iter.VisiblePosition());
    iter.NextChar();
    ++steps;
  }

  EXPECT_EQ(steps, input.size());
}

// Normal operation with ANSI color sequences: characters that belong to
// color sequences must be invisible, others visible, and visible positions
// must follow the documented example behavior.
TEST_F(VisibleInputCharsIteratorTest_105,
       AnsiColorSequencesInvisibleAndPositionsCorrect_105) {
  // "abcd" + "\x1b[31m" + "efgh" + "\x1b[0m" + "ijk"
  const std::string input = "abcd\x1b[31mefgh\x1b[0mijk";

  struct ExpectedCharInfo {
    size_t input_index;
    size_t visible_pos;
    bool is_visible;
  };

  const ExpectedCharInfo expected[] = {
      // input_index, visible_pos, is_visible
      {0, 0, true},   // 'a'
      {1, 1, true},   // 'b'
      {2, 2, true},   // 'c'
      {3, 3, true},   // 'd'
      {4, 4, false},  // ESC
      {5, 4, false},  // '['
      {6, 4, false},  // '3'
      {7, 4, false},  // '1'
      {8, 4, false},  // 'm'
      {9, 4, true},   // 'e'
      {10, 5, true},  // 'f'
      {11, 6, true},  // 'g'
      {12, 7, true},  // 'h'
      {13, 8, false}, // ESC
      {14, 8, false}, // '['
      {15, 8, false}, // '0'
      {16, 8, false}, // 'm'
      {17, 8, true},  // 'i'
      {18, 9, true},  // 'j'
      {19, 10, true}, // 'k'
  };

  constexpr size_t kExpectedCount = sizeof(expected) / sizeof(expected[0]);
  ASSERT_EQ(input.size(), kExpectedCount);

  VisibleInputCharsIterator iter(input);
  size_t i = 0;

  while (iter.HasChar()) {
    ASSERT_LT(i, kExpectedCount);

    EXPECT_EQ(expected[i].input_index, iter.InputIndex());
    EXPECT_EQ(expected[i].visible_pos, iter.VisiblePosition());
    EXPECT_EQ(expected[i].is_visible, iter.IsVisible());

    iter.NextChar();
    ++i;
  }

  EXPECT_EQ(i, kExpectedCount);
}

// Boundary condition: empty input string -> iterator has no characters.
TEST_F(VisibleInputCharsIteratorTest_105, EmptyInputHasNoChars_105) {
  const std::string input;
  VisibleInputCharsIterator iter(input);

  EXPECT_FALSE(iter.HasChar());
}

// Boundary / exceptional-like case: ESC followed by a non-'[' character.
// This is *not* a color sequence, so all characters (including ESC) must be
// treated as visible by IsVisible().
TEST_F(VisibleInputCharsIteratorTest_105,
       InvalidEscapeSequenceCharactersRemainVisible_105) {
  const std::string input = "ab\x1bXcd";  // ESC 'X' -> not "[", so no color seq.
  VisibleInputCharsIterator iter(input);

  size_t steps = 0;
  while (iter.HasChar()) {
    const size_t index = iter.InputIndex();
    ASSERT_LT(index, input.size());

    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(index, iter.VisiblePosition());

    iter.NextChar();
    ++steps;
  }

  EXPECT_EQ(steps, input.size());
}

// Boundary / incomplete ANSI sequence case: ESC '[' + parameters but no 'm'.
// According to the implementation, this is not recognized as a color sequence,
// so all characters remain visible.
TEST_F(VisibleInputCharsIteratorTest_105,
       IncompleteColorSequenceAtEndTreatedAsVisible_105) {
  const std::string input = "ab\x1b[31";  // No terminating 'm'
  VisibleInputCharsIterator iter(input);

  size_t steps = 0;
  while (iter.HasChar()) {
    const size_t index = iter.InputIndex();
    ASSERT_LT(index, input.size());

    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(index, iter.VisiblePosition());

    iter.NextChar();
    ++steps;
  }

  EXPECT_EQ(steps, input.size());
}
