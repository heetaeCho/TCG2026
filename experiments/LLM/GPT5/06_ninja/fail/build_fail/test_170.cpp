// File: elide_middle_ansi_iterator_test_170.cc

#include <string>

#include "gtest/gtest.h"

// Include the implementation file so we can access AnsiColorSequenceIterator.
// This struct is only defined in elide_middle.cc.
#include "elide_middle.cc"

class AnsiColorSequenceIteratorTest_170 : public ::testing::Test {};

// No ANSI escape sequences: iterator should report no sequence.
TEST_F(AnsiColorSequenceIteratorTest_170, NoAnsiSequenceInPlainString_170) {
  std::string input = "plain text without escapes";
  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());

  // SequenceContains() should be false for any index when there is no sequence.
  for (size_t i = 0; i < input.size(); ++i) {
    EXPECT_FALSE(iter.SequenceContains(i)) << "Index " << i << " should not be in sequence";
  }

  // NextSequence() should return false and keep state as "no sequence".
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());
}

// Single ANSI color sequence: start/end/size/contains should match positions.
TEST_F(AnsiColorSequenceIteratorTest_170, SingleSequencePositionsAndContains_170) {
  // "abc" + ESC "[31m" + "def"
  std::string input = std::string("abc") + "\x1b[31m" + "def";
  // Indices:
  // 0:a 1:b 2:c 3:ESC 4:'[' 5:'3' 6:'1' 7:'m' 8:d 9:e 10:f
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(3u, iter.SequenceStart());
  EXPECT_EQ(8u, iter.SequenceEnd());   // index of char *after* 'm'
  EXPECT_EQ(5u, iter.SequenceSize());  // ESC, '[', '3', '1', 'm'

  for (size_t i = 0; i < input.size(); ++i) {
    bool expected_in_sequence = (i >= 3u && i < 8u);
    EXPECT_EQ(expected_in_sequence, iter.SequenceContains(i))
        << "Mismatch at index " << i;
  }

  // After single sequence, NextSequence() should clear state.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());
  EXPECT_FALSE(iter.SequenceContains(0u));
}

// Multiple sequences: iterator should walk through each sequence correctly.
TEST_F(AnsiColorSequenceIteratorTest_170, MultipleSequencesWithNextSequence_170) {
  // "a" + ESC "[31m" + "b" + ESC "[0m" + "c"
  std::string input = std::string("a") + "\x1b[31m" + "b" + "\x1b[0m" + "c";
  // Indices:
  // 0:a
  // 1:ESC 2:'[' 3:'3' 4:'1' 5:'m'
  // 6:b
  // 7:ESC 8:'[' 9:'0' 10:'m'
  // 11:c
  AnsiColorSequenceIterator iter(input);

  // First sequence: ESC[31m
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(1u, iter.SequenceStart());
  EXPECT_EQ(6u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  // Move to second sequence: ESC[0m
  ASSERT_TRUE(iter.NextSequence());
  EXPECT_TRUE(iter.HasSequence());
  EXPECT_EQ(7u, iter.SequenceStart());
  EXPECT_EQ(11u, iter.SequenceEnd());
  EXPECT_EQ(4u, iter.SequenceSize());

  // No more sequences after second.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());

  // SequenceContains() should be false when there is no active sequence.
  for (size_t i = 0; i < input.size(); ++i) {
    EXPECT_FALSE(iter.SequenceContains(i)) << "Index " << i << " should not be in sequence";
  }
}

// Reset should restart iteration from the first sequence.
TEST_F(AnsiColorSequenceIteratorTest_170, ResetBringsIteratorBackToFirstSequence_170) {
  std::string input = std::string("a") + "\x1b[31m" + "b" + "\x1b[0m" + "c";
  AnsiColorSequenceIterator iter(input);

  // Step to second sequence.
  ASSERT_TRUE(iter.HasSequence());
  ASSERT_TRUE(iter.NextSequence());
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(7u, iter.SequenceStart());  // second sequence start

  // Reset: should jump back to first sequence.
  iter.Reset();
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(1u, iter.SequenceStart());
  EXPECT_EQ(6u, iter.SequenceEnd());
}

// Non-color / incomplete ANSI sequences should be ignored.
TEST_F(AnsiColorSequenceIteratorTest_170, IgnoresNonColorAndIncompleteSequences_170) {
  {
    // ESC not followed by '[' and also too short to form a color sequence.
    std::string input = std::string("abc") + "\x1b" + "Xdef";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
  }
  {
    // ESC '[' with parameters but no final 'm' -> incomplete color sequence.
    std::string input = std::string("abc") + "\x1b[31";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
  }
}

// Mixed: a non-color sequence should be skipped, and later valid color sequence found.
TEST_F(AnsiColorSequenceIteratorTest_170, SkipsNonColorSequenceFindsLaterColorSequence_170) {
  // First ESC[31X is not a color sequence (ends with 'X' not 'm').
  // Second ESC[32m is a valid color sequence.
  std::string input = std::string("\x1b[31X") + "\x1b[32m";
  // Indices:
  // 0:ESC 1:'[' 2:'3' 3:'1' 4:'X'
  // 5:ESC 6:'[' 7:'3' 8:'2' 9:'m'
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(5u, iter.SequenceStart());
  EXPECT_EQ(10u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  for (size_t i = 0; i < input.size(); ++i) {
    bool expected_in_sequence = (i >= 5u && i < 10u);
    EXPECT_EQ(expected_in_sequence, iter.SequenceContains(i))
        << "Mismatch at index " << i;
  }
}
