#include "gtest/gtest.h"
#include <string>

// Include the necessary header or declare the structs
// Based on the provided code, these are defined in elide_middle.cc
// We need to include the appropriate header

// Forward declarations based on the partial code
struct AnsiColorSequenceIterator {
  AnsiColorSequenceIterator(const std::string& input);
  bool HasSequence() const;
  size_t SequenceStart() const;
  size_t SequenceEnd() const;
  size_t SequenceSize() const;
  bool SequenceContains(size_t input_index) const;
  bool NextSequence();
  void Reset();

private:
  size_t cur_start_ = 0;
  size_t cur_end_ = 0;
  const char* input_;
  const char* input_end_;
  bool FindNextSequenceFrom(const char* from);
};

struct VisibleInputCharsIterator {
  VisibleInputCharsIterator(const std::string& input);
  bool HasChar() const;
  size_t InputIndex() const;
  size_t VisiblePosition() const;
  bool IsVisible() const;
  void NextChar();

private:
  size_t input_size_;
  size_t input_index_ = 0;
  size_t visible_pos_ = 0;
  AnsiColorSequenceIterator ansi_iter_;
};

// If the above forward declarations cause linker issues, you'd need to include
// the actual implementation file. Uncomment the line below if needed:
// #include "elide_middle.cc"

// ==================== AnsiColorSequenceIterator Tests ====================

class AnsiColorSequenceIteratorTest_106 : public ::testing::Test {};

TEST_F(AnsiColorSequenceIteratorTest_106, EmptyString_106) {
  std::string input = "";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_106, NoAnsiSequence_106) {
  std::string input = "hello world";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_106, SingleAnsiSequence_106) {
  // ANSI escape sequence: ESC[31m (red color)
  std::string input = "\033[31mhello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  // The sequence \033[31m is 5 chars: \033, [, 3, 1, m
  EXPECT_EQ(iter.SequenceEnd(), 5u);
  EXPECT_EQ(iter.SequenceSize(), 5u);
}

TEST_F(AnsiColorSequenceIteratorTest_106, SequenceContains_106) {
  std::string input = "\033[31mhello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  // Characters within the sequence
  EXPECT_TRUE(iter.SequenceContains(0));
  EXPECT_TRUE(iter.SequenceContains(1));
  EXPECT_TRUE(iter.SequenceContains(4));
  // Character after the sequence
  EXPECT_FALSE(iter.SequenceContains(5));
  EXPECT_FALSE(iter.SequenceContains(6));
}

TEST_F(AnsiColorSequenceIteratorTest_106, MultipleAnsiSequences_106) {
  // Two ANSI sequences
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());

  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();
  EXPECT_EQ(first_start, 0u);

  bool found_next = iter.NextSequence();
  EXPECT_TRUE(found_next);
  EXPECT_GT(iter.SequenceStart(), first_end - 1);
}

TEST_F(AnsiColorSequenceIteratorTest_106, NextSequenceReturnsFalseAtEnd_106) {
  std::string input = "\033[31mhello";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  bool found_next = iter.NextSequence();
  // Only one sequence, so NextSequence should return false
  EXPECT_FALSE(found_next);
}

TEST_F(AnsiColorSequenceIteratorTest_106, Reset_106) {
  std::string input = "\033[31mhello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  size_t original_start = iter.SequenceStart();

  iter.NextSequence();
  // After advancing, SequenceStart should be different
  EXPECT_NE(iter.SequenceStart(), original_start);

  iter.Reset();
  // After reset, should be back at the first sequence
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), original_start);
}

TEST_F(AnsiColorSequenceIteratorTest_106, PlainTextNoSequence_106) {
  std::string input = "just plain text no escape";
  AnsiColorSequenceIterator iter(input);
  EXPECT_FALSE(iter.HasSequence());
}

TEST_F(AnsiColorSequenceIteratorTest_106, SequenceAtEnd_106) {
  std::string input = "hello\033[0m";
  AnsiColorSequenceIterator iter(input);
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 5u);
}

// ==================== VisibleInputCharsIterator Tests ====================

class VisibleInputCharsIteratorTest_106 : public ::testing::Test {};

TEST_F(VisibleInputCharsIteratorTest_106, EmptyString_106) {
  std::string input = "";
  VisibleInputCharsIterator iter(input);
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_106, PlainText_106) {
  std::string input = "hello";
  VisibleInputCharsIterator iter(input);
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());
}

TEST_F(VisibleInputCharsIteratorTest_106, IteratePlainText_106) {
  std::string input = "abc";
  VisibleInputCharsIterator iter(input);

  // First char 'a'
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());

  iter.NextChar();
  // Second char 'b'
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 1u);
  EXPECT_EQ(iter.VisiblePosition(), 1u);
  EXPECT_TRUE(iter.IsVisible());

  iter.NextChar();
  // Third char 'c'
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 2u);
  EXPECT_EQ(iter.VisiblePosition(), 2u);
  EXPECT_TRUE(iter.IsVisible());

  iter.NextChar();
  // Past end
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.VisiblePosition(), 3u);
}

TEST_F(VisibleInputCharsIteratorTest_106, AnsiSequenceNotVisible_106) {
  // \033[31m is an ANSI color sequence (5 chars)
  std::string input = "\033[31mhi";
  VisibleInputCharsIterator iter(input);

  // The first characters are part of ANSI sequence, not visible
  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_FALSE(iter.IsVisible());
}

TEST_F(VisibleInputCharsIteratorTest_106, VisiblePositionSkipsAnsi_106) {
  // \033[31m (5 chars) followed by "hi" (2 chars)
  std::string input = "\033[31mhi";
  VisibleInputCharsIterator iter(input);

  // Advance through ANSI sequence
  size_t visible_after_ansi = 0;
  while (iter.HasChar() && !iter.IsVisible()) {
    iter.NextChar();
  }

  // Now we should be at 'h', visible position should still be 0
  // since ANSI chars don't count as visible
  if (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(iter.VisiblePosition(), 0u);

    iter.NextChar();
    // Now at 'i'
    if (iter.HasChar()) {
      EXPECT_TRUE(iter.IsVisible());
      EXPECT_EQ(iter.VisiblePosition(), 1u);
    }
  }
}

TEST_F(VisibleInputCharsIteratorTest_106, SingleCharString_106) {
  std::string input = "x";
  VisibleInputCharsIterator iter(input);

  EXPECT_TRUE(iter.HasChar());
  EXPECT_EQ(iter.InputIndex(), 0u);
  EXPECT_EQ(iter.VisiblePosition(), 0u);
  EXPECT_TRUE(iter.IsVisible());

  iter.NextChar();
  EXPECT_FALSE(iter.HasChar());
  EXPECT_EQ(iter.VisiblePosition(), 1u);
}

TEST_F(VisibleInputCharsIteratorTest_106, OnlyAnsiSequence_106) {
  std::string input = "\033[31m";
  VisibleInputCharsIterator iter(input);

  // All chars should be non-visible
  while (iter.HasChar()) {
    EXPECT_FALSE(iter.IsVisible());
    iter.NextChar();
  }
  // Visible position should be 0 since no visible chars
  EXPECT_EQ(iter.VisiblePosition(), 0u);
}

TEST_F(VisibleInputCharsIteratorTest_106, TextBetweenAnsiSequences_106) {
  // \033[31m hello \033[0m
  std::string input = "\033[31mhello\033[0m";
  VisibleInputCharsIterator iter(input);

  size_t total_visible = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      total_visible++;
    }
    iter.NextChar();
  }
  // "hello" is 5 visible characters
  EXPECT_EQ(total_visible, 5u);
  EXPECT_EQ(iter.VisiblePosition(), 5u);
}

TEST_F(VisibleInputCharsIteratorTest_106, InputIndexTracksCorrectly_106) {
  std::string input = "abcde";
  VisibleInputCharsIterator iter(input);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_TRUE(iter.HasChar());
    EXPECT_EQ(iter.InputIndex(), i);
    iter.NextChar();
  }
  EXPECT_FALSE(iter.HasChar());
}

TEST_F(VisibleInputCharsIteratorTest_106, MultipleAnsiSequences_106) {
  // \033[1m (bold) + "A" + \033[31m (red) + "B" + \033[0m (reset)
  std::string input = "\033[1mA\033[31mB\033[0m";
  VisibleInputCharsIterator iter(input);

  size_t total_visible = 0;
  while (iter.HasChar()) {
    if (iter.IsVisible()) {
      total_visible++;
    }
    iter.NextChar();
  }
  // "A" and "B" are the only visible characters
  EXPECT_EQ(total_visible, 2u);
  EXPECT_EQ(iter.VisiblePosition(), 2u);
}

TEST_F(VisibleInputCharsIteratorTest_106, LongPlainText_106) {
  std::string input(100, 'x');
  VisibleInputCharsIterator iter(input);

  size_t count = 0;
  while (iter.HasChar()) {
    EXPECT_TRUE(iter.IsVisible());
    EXPECT_EQ(iter.VisiblePosition(), count);
    iter.NextChar();
    count++;
  }
  EXPECT_EQ(count, 100u);
  EXPECT_EQ(iter.VisiblePosition(), 100u);
}
