// File: ./TestProjects/ninja/tests/ansi_color_sequence_iterator_test_98.cc

#include "gtest/gtest.h"
#include <string>

// The class under test is defined in this translation unit.
// Adjust the include path as needed for your project layout.
#include "elide_middle.cc"

class AnsiColorSequenceIteratorTest_98 : public ::testing::Test {};

// Normal operation: single ANSI color sequence at the beginning
TEST_F(AnsiColorSequenceIteratorTest_98,
       SequenceSizeMatchesStartEnd_SingleSequenceAtBeginning_98) {
  // "\x1b[31mred"
  std::string input = "\x1b[31mred";

  AnsiColorSequenceIterator it(input);

  ASSERT_TRUE(it.HasSequence());

  // Public invariants: size == end - start, and contains indices in [start, end)
  size_t start = it.SequenceStart();
  size_t end = it.SequenceEnd();

  EXPECT_EQ(end - start, it.SequenceSize());
  ASSERT_LT(start, end);  // non-empty sequence

  EXPECT_TRUE(it.SequenceContains(start));
  EXPECT_TRUE(it.SequenceContains(end - 1));
  EXPECT_FALSE(it.SequenceContains(end));
}

// Normal operation: multiple ANSI sequences in one string, iteration with NextSequence
TEST_F(AnsiColorSequenceIteratorTest_98,
       SequenceSizeMatchesStartEnd_MultipleSequences_98) {
  // "a\x1b[31mred\x1b[0m"
  std::string input = std::string("a") + "\x1b[31mred" + "\x1b[0m";
  AnsiColorSequenceIterator it(input);

  // First sequence
  ASSERT_TRUE(it.HasSequence());
  size_t first_start = it.SequenceStart();
  size_t first_end = it.SequenceEnd();
  EXPECT_EQ(first_end - first_start, it.SequenceSize());
  EXPECT_TRUE(it.SequenceContains(first_start));
  EXPECT_TRUE(it.SequenceContains(first_end - 1));
  EXPECT_FALSE(it.SequenceContains(first_end));

  // Move to second sequence
  ASSERT_TRUE(it.NextSequence());
  ASSERT_TRUE(it.HasSequence());
  size_t second_start = it.SequenceStart();
  size_t second_end = it.SequenceEnd();
  EXPECT_EQ(second_end - second_start, it.SequenceSize());
  EXPECT_TRUE(it.SequenceContains(second_start));
  EXPECT_TRUE(it.SequenceContains(second_end - 1));
  EXPECT_FALSE(it.SequenceContains(second_end));

  // After the last sequence, NextSequence should report no more sequences.
  EXPECT_FALSE(it.NextSequence());
}

// Boundary condition: input with no ANSI color sequences
TEST_F(AnsiColorSequenceIteratorTest_98,
       SequenceSize_NoSequencesInInput_98) {
  std::string input = "plain text with no colors";

  AnsiColorSequenceIterator it(input);

  // With no sequences, we expect HasSequence() to be false.
  EXPECT_FALSE(it.HasSequence());

  // Publicly visible invariant: size == end - start.
  // Even if the implementation defines start/end as 0 in this case,
  // this relationship must still hold.
  size_t start = it.SequenceStart();
  size_t end = it.SequenceEnd();
  EXPECT_EQ(end - start, it.SequenceSize());

  // With no sequence, contains() should be false for typical indices.
  EXPECT_FALSE(it.SequenceContains(0));
  if (!input.empty()) {
    EXPECT_FALSE(it.SequenceContains(input.size() - 1));
  }

  // NextSequence should not find anything.
  EXPECT_FALSE(it.NextSequence());
}

// Boundary condition: Reset returns iterator to the first sequence
TEST_F(AnsiColorSequenceIteratorTest_98,
       Reset_RestoresFirstSequenceAndSequenceSizeInvariant_98) {
  // "x\x1b[32mgreen\x1b[0my"
  std::string input = std::string("x") + "\x1b[32mgreen" + "\x1b[0m" + "y";
  AnsiColorSequenceIterator it(input);

  // Capture first sequence information
  ASSERT_TRUE(it.HasSequence());
  size_t first_start = it.SequenceStart();
  size_t first_end = it.SequenceEnd();
  size_t first_size = it.SequenceSize();
  EXPECT_EQ(first_end - first_start, first_size);

  // Move to second sequence to change internal state
  ASSERT_TRUE(it.NextSequence());
  ASSERT_TRUE(it.HasSequence());
  EXPECT_NE(first_start, it.SequenceStart());

  // After Reset, we should again be at the first sequence,
  // and the size invariant must still hold.
  it.Reset();
  ASSERT_TRUE(it.HasSequence());
  EXPECT_EQ(first_start, it.SequenceStart());
  EXPECT_EQ(first_end, it.SequenceEnd());
  EXPECT_EQ(first_size, it.SequenceSize());
}

// Exceptional / malformed case: stray ESC that does not form a full sequence
TEST_F(AnsiColorSequenceIteratorTest_98,
       MalformedSequence_DoesNotProduceNonZeroSize_98) {
  // Contains an ESC but not a full standard color sequence.
  std::string input = "text \x1b[ not a full sequence";

  AnsiColorSequenceIterator it(input);

  // Implementation is free to either treat this as "no sequence"
  // or a zero-length sequence, but size must always match end - start.
  size_t start = it.SequenceStart();
  size_t end = it.SequenceEnd();
  EXPECT_EQ(end - start, it.SequenceSize());

  // Regardless of HasSequence(), SequenceContains(start) must not
  // be true unless the sequence has non-zero length.
  if (it.HasSequence() && it.SequenceSize() > 0u) {
    EXPECT_TRUE(it.SequenceContains(start));
    EXPECT_TRUE(it.SequenceContains(end - 1));
    EXPECT_FALSE(it.SequenceContains(end));
  }
}
