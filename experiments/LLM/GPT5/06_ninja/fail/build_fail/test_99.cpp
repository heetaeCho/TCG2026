// File: elide_middle_sequence_contains_test_99.cc

#include <gtest/gtest.h>
#include <string>
#include <limits>

#include "elide_middle.cc"  // or appropriate header that declares AnsiColorSequenceIterator

class AnsiColorSequenceIteratorTest_99 : public ::testing::Test {};

// Normal operation: plain text without any ANSI color sequence
TEST_F(AnsiColorSequenceIteratorTest_99, PlainTextHasNoSequence_99) {
  std::string input = "hello world";
  AnsiColorSequenceIterator it(input);

  // No ANSI sequence should be detected.
  EXPECT_FALSE(it.HasSequence());

  // SequenceContains should be false for all valid indices.
  for (size_t i = 0; i < input.size(); ++i) {
    EXPECT_FALSE(it.SequenceContains(i)) << "Unexpected sequence at index " << i;
  }

  // Also false for index equal to input size (one past last character).
  EXPECT_FALSE(it.SequenceContains(input.size()));
}

// Normal operation: single ANSI sequence, SequenceContains matches [start, end)
TEST_F(AnsiColorSequenceIteratorTest_99, SingleSequence_ContainsWithinRange_99) {
  // Simple colored text: ESC[31mred
  std::string input = "\x1b[31mred";
  AnsiColorSequenceIterator it(input);

  it.Reset();

  ASSERT_TRUE(it.HasSequence()) << "Expected at least one ANSI sequence";

  const size_t start = it.SequenceStart();
  const size_t end = it.SequenceEnd();

  ASSERT_LT(start, end);
  ASSERT_LE(end, input.size());

  // All indices in [start, end) must be contained.
  for (size_t i = start; i < end; ++i) {
    EXPECT_TRUE(it.SequenceContains(i))
        << "Expected index " << i << " to be inside sequence";
    // Cross-check with start/end for self-consistency.
    EXPECT_EQ(it.SequenceContains(i),
              (i >= it.SequenceStart() && i < it.SequenceEnd()));
  }

  // Boundary checks: just before start (if any) and at end must not be contained.
  if (start > 0) {
    EXPECT_FALSE(it.SequenceContains(start - 1))
        << "Index just before start should not be contained";
  }
  EXPECT_FALSE(it.SequenceContains(end))
      << "Index equal to end should not be contained";
}

// Normal operation: multiple sequences, iterator moves and SequenceContains tracks current one
TEST_F(AnsiColorSequenceIteratorTest_99, MultipleSequences_IteratorAdvances_99) {
  // ESC[31mredESC[0m
  std::string input = "\x1b[31mred\x1b[0m";
  AnsiColorSequenceIterator it(input);

  it.Reset();

  ASSERT_TRUE(it.HasSequence()) << "Expected first ANSI sequence";

  // First sequence range
  const size_t first_start = it.SequenceStart();
  const size_t first_end = it.SequenceEnd();

  ASSERT_LT(first_start, first_end);
  ASSERT_LE(first_end, input.size());

  // A position inside the first range must be contained.
  const size_t first_mid = first_start;
  EXPECT_TRUE(it.SequenceContains(first_mid));
  EXPECT_EQ(it.SequenceContains(first_mid),
            (first_mid >= it.SequenceStart() && first_mid < it.SequenceEnd()));

  // Move to next sequence
  ASSERT_TRUE(it.NextSequence()) << "Expected second ANSI sequence";
  ASSERT_TRUE(it.HasSequence());

  const size_t second_start = it.SequenceStart();
  const size_t second_end = it.SequenceEnd();

  ASSERT_LT(second_start, second_end);
  ASSERT_LE(second_end, input.size());

  // A position inside the second range must be contained.
  const size_t second_mid = second_start;
  EXPECT_TRUE(it.SequenceContains(second_mid));
  EXPECT_EQ(it.SequenceContains(second_mid),
            (second_mid >= it.SequenceStart() && second_mid < it.SequenceEnd()));

  // A position in the first sequence should typically not belong to the second.
  EXPECT_FALSE(it.SequenceContains(first_mid))
      << "After advancing, old sequence index should no longer be contained";
}

// Boundary condition: very large index is never contained
TEST_F(AnsiColorSequenceIteratorTest_99, LargeIndexIsNotContained_99) {
  std::string input = "\x1b[31mred\x1b[0m";
  AnsiColorSequenceIterator it(input);

  it.Reset();
  ASSERT_TRUE(it.HasSequence()) << "Expected at least one sequence";

  const size_t large_index = std::numeric_limits<size_t>::max();
  EXPECT_FALSE(it.SequenceContains(large_index))
      << "Extremely large index should never be contained in a finite sequence";

  // Cross-check with start/end for self-consistency.
  EXPECT_EQ(it.SequenceContains(large_index),
            (large_index >= it.SequenceStart() &&
             large_index < it.SequenceEnd()));
}

// Behavior after Reset: iterator returns to first sequence and SequenceContains updates
TEST_F(AnsiColorSequenceIteratorTest_99, ResetRestoresFirstSequence_99) {
  std::string input = "XX\x1b[31mred\x1b[0mYY";
  AnsiColorSequenceIterator it(input);

  it.Reset();
  ASSERT_TRUE(it.HasSequence());

  const size_t first_start = it.SequenceStart();
  const size_t first_end = it.SequenceEnd();

  // Advance to next sequence (if any).
  it.NextSequence();

  // After Reset, we should be back to the first sequence range.
  it.Reset();
  ASSERT_TRUE(it.HasSequence());

  EXPECT_EQ(it.SequenceStart(), first_start);
  EXPECT_EQ(it.SequenceEnd(), first_end);

  if (first_start < first_end) {
    size_t inside = first_start;
    EXPECT_TRUE(it.SequenceContains(inside));
    EXPECT_EQ(it.SequenceContains(inside),
              (inside >= it.SequenceStart() && inside < it.SequenceEnd()));
  }
}
