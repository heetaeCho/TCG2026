// File: elide_middle_nextchar_test_106.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "elide_middle.cc"

// Fixture for VisibleInputCharsIterator tests (TEST_ID = 106)
class VisibleInputCharsIteratorTest_106 : public ::testing::Test {
protected:
  // Helper: iterate over the whole input and check visibility / positions
  void AssertIteration(const std::string& input,
                       const std::vector<bool>& expected_visible) {
    ASSERT_EQ(input.size(), expected_visible.size());

    VisibleInputCharsIterator it(input);

    // Initial state
    EXPECT_EQ(0u, it.InputIndex());
    EXPECT_EQ(0u, it.VisiblePosition());

    size_t expected_visible_pos = 0;
    size_t step = 0;

    while (it.HasChar()) {
      ASSERT_LT(step, expected_visible.size());

      // IsVisible() should reflect whether the current input char is visible.
      EXPECT_EQ(expected_visible[step], it.IsVisible())
          << "Mismatch at input index " << step;

      // Advance one character via NextChar() – the method under test.
      if (expected_visible[step])
        ++expected_visible_pos;

      it.NextChar();
      ++step;

      // VisiblePosition() should count how many visible characters we passed.
      EXPECT_EQ(expected_visible_pos, it.VisiblePosition())
          << "Visible position mismatch after consuming index " << (step - 1);
    }

    // After consuming all characters
    EXPECT_EQ(input.size(), step);
    EXPECT_EQ(input.size(), it.InputIndex());
    EXPECT_EQ(expected_visible_pos, it.VisiblePosition());
  }
};

// 1) Empty input: HasChar() should be false, positions stay at 0.
TEST_F(VisibleInputCharsIteratorTest_106, EmptyInput_HasNoChars_106) {
  std::string input;
  VisibleInputCharsIterator it(input);

  EXPECT_FALSE(it.HasChar());
  EXPECT_EQ(0u, it.InputIndex());
  EXPECT_EQ(0u, it.VisiblePosition());
}

// 2) Plain text (no ANSI sequences):
//    NextChar() should advance InputIndex and VisiblePosition every step.
TEST_F(VisibleInputCharsIteratorTest_106, PlainText_AllCharsVisible_106) {
  std::string input = "abcde";
  // All characters are visible.
  std::vector<bool> visible_mask(input.size(), true);

  AssertIteration(input, visible_mask);
}

// 3) Text containing a single ANSI sequence in the middle:
//    "ab" + "\x1b[0m" + "cd"
//    Only 'a','b','c','d' should be visible; the escape sequence is not.
TEST_F(VisibleInputCharsIteratorTest_106,
       TextWithSingleAnsiSequence_SkipsEscape_106) {
  std::string input = std::string("ab") + "\x1b[0m" + "cd";
  // Indices:
  // 0:'a' (visible)
  // 1:'b' (visible)
  // 2:'\x1b' (escape, non-visible)
  // 3:'['   (non-visible)
  // 4:'0'   (non-visible)
  // 5:'m'   (non-visible)
  // 6:'c'   (visible)
  // 7:'d'   (visible)
  std::vector<bool> visible_mask = {
      true,  // 'a'
      true,  // 'b'
      false, // ESC
      false, // '['
      false, // '0'
      false, // 'm'
      true,  // 'c'
      true   // 'd'
  };

  AssertIteration(input, visible_mask);
}

// 4) Multiple ANSI sequences, exercising NextSequence() boundary logic:
//    "a" + "\x1b[0m" + "b" + "\x1b[0m" + "c"
//    Only 'a','b','c' are visible; all escape characters are not.
TEST_F(VisibleInputCharsIteratorTest_106,
       TextWithMultipleAnsiSequences_HandlesNextSequence_106) {
  std::string input = std::string("a") + "\x1b[0m" + "b" + "\x1b[0m" + "c";
  // Indices:
  // 0:'a' (visible)
  // 1:'\x1b' (non-visible)
  // 2:'['    (non-visible)
  // 3:'0'    (non-visible)
  // 4:'m'    (non-visible)
  // 5:'b'    (visible)
  // 6:'\x1b' (non-visible)
  // 7:'['    (non-visible)
  // 8:'0'    (non-visible)
  // 9:'m'    (non-visible)
  // 10:'c'   (visible)
  std::vector<bool> visible_mask = {
      true,  // 'a'
      false, // ESC
      false, // '['
      false, // '0'
      false, // 'm'
      true,  // 'b'
      false, // ESC
      false, // '['
      false, // '0'
      false, // 'm'
      true   // 'c'
  };

  AssertIteration(input, visible_mask);
}

// 5) ANSI sequence at the end of the string:
//    "ab" + "\x1b[0m"
//    Only 'a','b' are visible; the trailing sequence is not,
//    and NextChar() must not read past the end when it reaches SequenceEnd().
TEST_F(VisibleInputCharsIteratorTest_106,
       TextEndingWithAnsiSequence_NoExtraVisibleChars_106) {
  std::string input = std::string("ab") + "\x1b[0m";
  // Indices:
  // 0:'a' (visible)
  // 1:'b' (visible)
  // 2:'\x1b' (non-visible)
  // 3:'['    (non-visible)
  // 4:'0'    (non-visible)
  // 5:'m'    (non-visible)
  std::vector<bool> visible_mask = {
      true,  // 'a'
      true,  // 'b'
      false, // ESC
      false, // '['
      false, // '0'
      false  // 'm'
  };

  AssertIteration(input, visible_mask);
}
