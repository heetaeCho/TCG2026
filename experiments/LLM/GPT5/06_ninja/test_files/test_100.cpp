// File: ./TestProjects/ninja/tests/elide_middle_ansi_iterator_test_100.cc

#include "gtest/gtest.h"

// Adjust include path as appropriate for your tree.
#include "src/elide_middle.cc"

class AnsiColorSequenceIteratorTest_100 : public ::testing::Test {};

// One ANSI color sequence: basic accessors and containment.
TEST_F(AnsiColorSequenceIteratorTest_100,
       SingleColorSequence_AccessorsAndContains_100) {
  // "abc" + "\x1b[31m" + "def"
  const std::string input = "abc\x1b[31mdef";

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(3u, iter.SequenceStart());   // index of '\x1b'
  EXPECT_EQ(8u, iter.SequenceEnd());     // index of 'd'
  EXPECT_EQ(5u, iter.SequenceSize());    // "\x1b[31m"

  // Contains inside range [start, end)
  EXPECT_TRUE(iter.SequenceContains(3u));
  EXPECT_TRUE(iter.SequenceContains(4u));
  EXPECT_TRUE(iter.SequenceContains(7u));

  // Outside range
  EXPECT_FALSE(iter.SequenceContains(2u));   // before start
  EXPECT_FALSE(iter.SequenceContains(8u));   // at end
  EXPECT_FALSE(iter.SequenceContains(100u)); // well past input size
}

// NextSequence() on last sequence returns false and clears state.
TEST_F(AnsiColorSequenceIteratorTest_100,
       NextSequence_NoMoreSequencesClearsState_100) {
  const std::string input = "abc\x1b[31mdef";

  AnsiColorSequenceIterator iter(input);
  ASSERT_TRUE(iter.HasSequence());

  bool has_more = iter.NextSequence();
  EXPECT_FALSE(has_more);
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());
  EXPECT_FALSE(iter.SequenceContains(0u));
}

// Multiple ANSI color sequences: iteration order and positions.
TEST_F(AnsiColorSequenceIteratorTest_100,
       MultipleSequences_IteratesInOrder_100) {
  // "x" + "\x1b[31m" + " y " + "\x1b[0m" + "z"
  const std::string input = "x\x1b[31m y \x1b[0mz";
  // Indices:
  // 0:'x'
  // 1:'\x1b', 2:'[', 3:'3', 4:'1', 5:'m'   -> first sequence [1,6)
  // 6:' ', 7:'y', 8:' '
  // 9:'\x1b',10:'[',11:'0',12:'m'          -> second sequence [9,13)
  // 13:'z'

  AnsiColorSequenceIterator iter(input);

  // First sequence
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(1u, iter.SequenceStart());
  EXPECT_EQ(6u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  // Move to second sequence
  ASSERT_TRUE(iter.NextSequence());
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(9u, iter.SequenceStart());
  EXPECT_EQ(13u, iter.SequenceEnd());
  EXPECT_EQ(4u, iter.SequenceSize());

  // No more after second
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Reset() should restart iteration from the first sequence.
TEST_F(AnsiColorSequenceIteratorTest_100,
       Reset_RestartsFromFirstSequence_100) {
  const std::string input = "x\x1b[31m y \x1b[0mz";

  AnsiColorSequenceIterator iter(input);

  // Advance to second sequence
  ASSERT_TRUE(iter.HasSequence());
  ASSERT_TRUE(iter.NextSequence());
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(9u, iter.SequenceStart());

  // Reset and verify we're back to the first sequence
  iter.Reset();
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(1u, iter.SequenceStart());
  EXPECT_EQ(6u, iter.SequenceEnd());
}

// Input with no ESC characters should have no sequences.
TEST_F(AnsiColorSequenceIteratorTest_100,
       NoAnsiSequences_HasSequenceIsFalse_100) {
  const std::string input = "just a normal string";

  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(0u, iter.SequenceEnd());
  EXPECT_EQ(0u, iter.SequenceSize());

  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Non-color ANSI sequences (no final 'm') should be ignored.
TEST_F(AnsiColorSequenceIteratorTest_100,
       NonColorSequences_AreIgnored_100) {
  // First sequence is ESC[31K (no 'm') -> non-color, should be skipped.
  // Second is ESC[32m -> color, should be detected.
  const std::string input = "\x1b[31K\x1b[32m";
  // Indices:
  // 0:'\x1b',1:'[',2:'3',3:'1',4:'K',
  // 5:'\x1b',6:'[',7:'3',8:'2',9:'m' -> sequence [5,10)

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(5u, iter.SequenceStart());
  EXPECT_EQ(10u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Incomplete or too-short color sequences should not be reported.
TEST_F(AnsiColorSequenceIteratorTest_100,
       IncompleteOrTooShortSequences_AreNotReported_100) {
  // ESC at the end: too short to form a valid color sequence.
  const std::string input1 = "abc\x1b";
  AnsiColorSequenceIterator iter1(input1);
  EXPECT_FALSE(iter1.HasSequence());
  EXPECT_FALSE(iter1.NextSequence());
  EXPECT_FALSE(iter1.HasSequence());

  // ESC[31 without trailing 'm' -> incomplete color sequence.
  const std::string input2 = "\x1b[31";
  AnsiColorSequenceIterator iter2(input2);
  EXPECT_FALSE(iter2.HasSequence());
  EXPECT_FALSE(iter2.NextSequence());
  EXPECT_FALSE(iter2.HasSequence());
}

// SequenceContains() should be safe for any index, including > input length.
TEST_F(AnsiColorSequenceIteratorTest_100,
       SequenceContains_HandlesOutOfRangeIndex_100) {
  const std::string input = "abc\x1b[31mdef";
  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_FALSE(iter.SequenceContains(static_cast<size_t>(-1))); // wraps to large
  EXPECT_FALSE(iter.SequenceContains(1000u)); // well beyond string size
}
