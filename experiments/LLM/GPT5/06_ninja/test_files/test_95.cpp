// File: ./TestProjects/ninja/tests/elide_middle_ansi_color_sequence_iterator_test_95.cc

#include "gtest/gtest.h"

#include <string>

// Forward declaration of the production type under test.
// The real implementation lives in ./src/elide_middle.cc.
// We only declare the public interface needed by the tests.
struct AnsiColorSequenceIterator {
  explicit AnsiColorSequenceIterator(const std::string& input);

  bool HasSequence() const;
  size_t SequenceStart() const;
  size_t SequenceEnd() const;
  size_t SequenceSize() const;
  bool SequenceContains(size_t input_index) const;
  bool NextSequence();
  void Reset();
};

class AnsiColorSequenceIteratorTest_95 : public ::testing::Test {};

// No ANSI escape sequences: iterator should report no sequence.
TEST_F(AnsiColorSequenceIteratorTest_95,
       NoAnsiSequences_HasSequenceFalse_95) {
  std::string input = "Hello, world";

  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  // Calling NextSequence() when there are none should return false and keep
  // HasSequence() false.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Single color sequence at the very beginning of the string.
TEST_F(AnsiColorSequenceIteratorTest_95,
       SingleSequenceAtStart_IndicesAndContains_95) {
  // "\x1b[31mHello"
  // indices: 0:ESC 1:'[' 2:'3' 3:'1' 4:'m' 5:'H' ...
  std::string input = "\x1b[31mHello";

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(5u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  // Characters 0..4 belong to the sequence, 5 and beyond do not.
  EXPECT_TRUE(iter.SequenceContains(0u));
  EXPECT_TRUE(iter.SequenceContains(4u));
  EXPECT_FALSE(iter.SequenceContains(5u));

  // There is only one sequence in this string.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Single color sequence at the very end of the string.
TEST_F(AnsiColorSequenceIteratorTest_95,
       SingleSequenceAtEnd_IndicesAndContains_95) {
  // "Hello\x1b[0m"
  // indices: 0:'H' 1:'e' 2:'l' 3:'l' 4:'o'
  //          5:ESC 6:'[' 7:'0' 8:'m'
  std::string input = "Hello\x1b[0m";

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(5u, iter.SequenceStart());
  EXPECT_EQ(9u, iter.SequenceEnd());
  EXPECT_EQ(4u, iter.SequenceSize());

  EXPECT_FALSE(iter.SequenceContains(4u));
  EXPECT_TRUE(iter.SequenceContains(5u));
  EXPECT_TRUE(iter.SequenceContains(8u));
  EXPECT_FALSE(iter.SequenceContains(9u));  // past-the-end

  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Multiple color sequences in the same string.
TEST_F(AnsiColorSequenceIteratorTest_95,
       MultipleSequences_IterateAll_95) {
  // "a\x1b[31m b\x1b[0m"
  // indices: 0:'a'
  //          1:ESC 2:'[' 3:'3' 4:'1' 5:'m'
  //          6:' ' 7:'b'
  //          8:ESC 9:'[' 10:'0' 11:'m'
  std::string input = "a\x1b[31m b\x1b[0m";

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  // First sequence.
  EXPECT_EQ(1u, iter.SequenceStart());
  EXPECT_EQ(6u, iter.SequenceEnd());
  EXPECT_EQ(5u, iter.SequenceSize());

  EXPECT_TRUE(iter.SequenceContains(1u));
  EXPECT_TRUE(iter.SequenceContains(5u));
  EXPECT_FALSE(iter.SequenceContains(6u));

  // Move to second sequence.
  ASSERT_TRUE(iter.NextSequence());
  ASSERT_TRUE(iter.HasSequence());

  EXPECT_EQ(8u, iter.SequenceStart());
  EXPECT_EQ(12u, iter.SequenceEnd());
  EXPECT_EQ(4u, iter.SequenceSize());

  EXPECT_TRUE(iter.SequenceContains(8u));
  EXPECT_TRUE(iter.SequenceContains(11u));
  EXPECT_FALSE(iter.SequenceContains(12u));

  // No more sequences after the second one.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// A color sequence with multiple parameters should be treated as one sequence.
TEST_F(AnsiColorSequenceIteratorTest_95,
       MultiParameterSequence_SequenceSizeAndBounds_95) {
  // "\x1b[1;32;40mX"
  // indices: 0:ESC 1:'[' 2:'1' 3:';' 4:'3' 5:'2'
  //          6:';' 7:'4' 8:'0' 9:'m' 10:'X'
  std::string input = "\x1b[1;32;40mX";

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(0u, iter.SequenceStart());
  EXPECT_EQ(10u, iter.SequenceEnd());
  EXPECT_EQ(10u, iter.SequenceSize());

  // All characters up to but not including 'X' (index 10) are in the sequence.
  EXPECT_TRUE(iter.SequenceContains(0u));
  EXPECT_TRUE(iter.SequenceContains(9u));
  EXPECT_FALSE(iter.SequenceContains(10u));
}

// Escape sequences that are not color sequences (e.g. ending with 'K')
// must be ignored by the iterator.
TEST_F(AnsiColorSequenceIteratorTest_95,
       NonColorEscapeSequences_Ignored_95) {
  // "\x1b[0K" is an ANSI CSI Erase in Line sequence, not a color (no 'm').
  std::string input = "abc\x1b[0Kdef";

  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Incomplete / truncated sequences should not be reported as valid.
TEST_F(AnsiColorSequenceIteratorTest_95,
       IncompleteSequence_NoSequenceReported_95) {
  // ESC at end: too short to form a sequence.
  std::string input1 = "abc\x1b";
  AnsiColorSequenceIterator iter1(input1);
  EXPECT_FALSE(iter1.HasSequence());

  // ESC '[' without a terminating 'm'.
  std::string input2 = "xyz\x1b[31";
  AnsiColorSequenceIterator iter2(input2);
  EXPECT_FALSE(iter2.HasSequence());
}

// Reset() should rewind the iterator back to the first sequence.
TEST_F(AnsiColorSequenceIteratorTest_95,
       Reset_RewindsToFirstSequence_95) {
  std::string input = "a\x1b[31m b\x1b[0m";

  AnsiColorSequenceIterator iter(input);

  // First sequence.
  ASSERT_TRUE(iter.HasSequence());
  size_t first_start = iter.SequenceStart();
  size_t first_end = iter.SequenceEnd();

  // Move forward to consume all sequences.
  EXPECT_TRUE(iter.NextSequence());
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());

  // After Reset(), we should again see the first sequence.
  iter.Reset();
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(first_start, iter.SequenceStart());
  EXPECT_EQ(first_end, iter.SequenceEnd());
}
