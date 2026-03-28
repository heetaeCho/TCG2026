// File: elide_middle_iterator_test_96.cc

#include "gtest/gtest.h"
#include <string>

// The implementation lives in elide_middle.cc and defines AnsiColorSequenceIterator.
#include "elide_middle.cc"

using std::string;

TEST(AnsiColorSequenceIteratorTest_96, NoSequencesInPlainString_96) {
  string input = "abcdef";
  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceEnd(), 0u);
  EXPECT_EQ(iter.SequenceSize(), 0u);

  // SequenceContains should be false for any index when there is no sequence.
  EXPECT_FALSE(iter.SequenceContains(0u));
  EXPECT_FALSE(iter.SequenceContains(3u));
  EXPECT_FALSE(iter.SequenceContains(100u));
}

TEST(AnsiColorSequenceIteratorTest_96, SingleSimpleColorSequence_96) {
  // Indices:
  // 0:'a', 1:'b', 2:'\x1b', 3:'[', 4:'3', 5:'1', 6:'m', 7:'c'
  string input = string("ab") + "\x1b[31m" + "c";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());

  EXPECT_EQ(iter.SequenceStart(), 2u);
  EXPECT_EQ(iter.SequenceEnd(), 7u);
  EXPECT_EQ(iter.SequenceSize(), 5u);

  // Inside the sequence.
  for (size_t i = 2; i < 7; ++i) {
    EXPECT_TRUE(iter.SequenceContains(i)) << "Index " << i << " should be in sequence";
  }
  // Outside the sequence.
  EXPECT_FALSE(iter.SequenceContains(0u));
  EXPECT_FALSE(iter.SequenceContains(1u));
  EXPECT_FALSE(iter.SequenceContains(7u));
  EXPECT_FALSE(iter.SequenceContains(100u));
}

TEST(AnsiColorSequenceIteratorTest_96, MultipleSequencesWithNextSequence_96) {
  // Indices:
  // 0:'x',
  // 1:'\x1b',2:'[',3:'3',4:'1',5:'m', 6:'y',
  // 7:'\x1b',8:'[',9:'0',10:'m', 11:'z'
  string input = string("x") + "\x1b[31m" + "y" + "\x1b[0m" + "z";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());

  // First sequence \x1b[31m
  EXPECT_EQ(iter.SequenceStart(), 1u);
  EXPECT_EQ(iter.SequenceEnd(), 6u);
  EXPECT_EQ(iter.SequenceSize(), 5u);

  // Move to second sequence.
  EXPECT_TRUE(iter.NextSequence());
  ASSERT_TRUE(iter.HasSequence());

  // Second sequence \x1b[0m
  EXPECT_EQ(iter.SequenceStart(), 7u);
  EXPECT_EQ(iter.SequenceEnd(), 11u);
  EXPECT_EQ(iter.SequenceSize(), 4u);

  // After last sequence, NextSequence should report no more sequences.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceSize(), 0u);
}

TEST(AnsiColorSequenceIteratorTest_96, ResetRestartsFromFirstSequence_96) {
  string input = string("x") + "\x1b[31m" + "y" + "\x1b[0m" + "z";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 1u);

  // Advance to second sequence.
  ASSERT_TRUE(iter.NextSequence());
  EXPECT_EQ(iter.SequenceStart(), 7u);

  // Reset should bring us back to the first sequence.
  iter.Reset();
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 1u);
  EXPECT_EQ(iter.SequenceEnd(), 6u);
}

TEST(AnsiColorSequenceIteratorTest_96, IgnoresNonColorAnsiSequences_96) {
  // Contains a non-color ANSI sequence \x1b[0K and a color sequence \x1b[32m.
  // Indices:
  // 0:'a',1:'b',
  // 2:'\x1b',3:'[',4:'0',5:'K',
  // 6:'c',7:'d',
  // 8:'\x1b',9:'[',10:'3',11:'2',12:'m'
  string input = string("ab") + "\x1b[0K" + "cd" + "\x1b[32m";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());

  // The first *color* sequence should start at the second ESC (index 8).
  EXPECT_EQ(iter.SequenceStart(), 8u);
  EXPECT_EQ(iter.SequenceEnd(), 13u);
  EXPECT_EQ(iter.SequenceSize(), 5u);

  // Indices from the non-color sequence should not be considered part of the current sequence.
  EXPECT_FALSE(iter.SequenceContains(2u));
  EXPECT_FALSE(iter.SequenceContains(3u));
  EXPECT_FALSE(iter.SequenceContains(4u));
  EXPECT_FALSE(iter.SequenceContains(5u));

  // But the color sequence indices should be inside.
  for (size_t i = 8; i < 13; ++i) {
    EXPECT_TRUE(iter.SequenceContains(i)) << "Index " << i << " should be in color sequence";
  }
}

TEST(AnsiColorSequenceIteratorTest_96, IncompleteSequenceAtEndIsIgnored_96) {
  // ESC [ 3 1 with no trailing 'm' => incomplete, should be ignored.
  string input = string("ab") + "\x1b[31";
  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceEnd(), 0u);
  EXPECT_EQ(iter.SequenceSize(), 0u);

  // Reset should not change anything for a string without valid sequences.
  iter.Reset();
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), 0u);
  EXPECT_EQ(iter.SequenceEnd(), 0u);
  EXPECT_EQ(iter.SequenceSize(), 0u);
}

TEST(AnsiColorSequenceIteratorTest_96, SequenceContainsOutOfRangeIndex_96) {
  string input = string("ab") + "\x1b[31m" + "c";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());

  // Very large index should never be considered part of the sequence.
  EXPECT_FALSE(iter.SequenceContains(1000u));
}
