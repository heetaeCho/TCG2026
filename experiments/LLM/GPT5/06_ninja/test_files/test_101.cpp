// File: ./TestProjects/ninja/tests/elide_middle_ansi_color_sequence_iterator_test_101.cc

#include <string>
#include "gtest/gtest.h"

// Include the real declaration of AnsiColorSequenceIterator.
// Adjust the include path as needed for your project layout.
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_101 : public ::testing::Test {};

// Helper to count how many sequences the iterator exposes, starting from the
// beginning. Uses only the public interface.
static size_t CountSequencesFromStart(AnsiColorSequenceIterator& it) {
  size_t count = 0;

  it.Reset();
  if (!it.HasSequence()) {
    return 0;
  }

  // Count the first sequence.
  ++count;

  // Count subsequent sequences until NextSequence() signals no more.
  while (it.NextSequence()) {
    ++count;
  }

  return count;
}

// Normal operation & boundary: empty input and plain text with no ANSI codes.
TEST_F(AnsiColorSequenceIteratorTest_101, NoSequencesInEmptyAndPlainText_101) {
  {
    // Empty string: no sequences expected.
    std::string input;
    AnsiColorSequenceIterator it(input);

    it.Reset();
    EXPECT_FALSE(it.HasSequence());
    EXPECT_FALSE(it.NextSequence());
  }

  {
    // Plain text with no escape characters: no sequences expected.
    std::string input = "Hello, world without colors.";
    AnsiColorSequenceIterator it(input);

    it.Reset();
    EXPECT_FALSE(it.HasSequence());
    EXPECT_FALSE(it.NextSequence());
  }
}

// Boundary case: input that consists only of a single ANSI color sequence.
TEST_F(AnsiColorSequenceIteratorTest_101, SinglePureSequence_AllIndicesContained_101) {
  // A typical reset ANSI sequence.
  const std::string input = "\x1b[0m";

  AnsiColorSequenceIterator it(input);
  it.Reset();

  ASSERT_TRUE(it.HasSequence());

  // For a pure sequence, it is reasonable that the sequence starts at 0.
  EXPECT_EQ(0u, it.SequenceStart());

  const size_t size = it.SequenceSize();
  EXPECT_GT(size, 0u);
  EXPECT_LE(size, input.size());

  // Every index inside [start, start + size) should be contained.
  for (size_t offset = 0; offset < size; ++offset) {
    EXPECT_TRUE(it.SequenceContains(it.SequenceStart() + offset));
  }

  // Index immediately after the sequence should not be contained (if in range).
  if (it.SequenceStart() + size < input.size()) {
    EXPECT_FALSE(it.SequenceContains(it.SequenceStart() + size));
  }

  // There is only one sequence; NextSequence() should report no more.
  EXPECT_FALSE(it.NextSequence());
}

// Normal operation: single ANSI sequence embedded in surrounding text.
TEST_F(AnsiColorSequenceIteratorTest_101, SingleEmbeddedSequence_ContainsAndSizeConsistency_101) {
  // "Hello " + red color start + "world" (we only care about the sequence itself)
  const std::string input = std::string("Hello ") + "\x1b[31m" + "world";

  AnsiColorSequenceIterator it(input);
  it.Reset();

  ASSERT_TRUE(it.HasSequence());

  const size_t start = it.SequenceStart();
  const size_t size = it.SequenceSize();

  // Basic sanity: sequence is a non-empty interval within the string.
  EXPECT_LT(start, input.size());
  EXPECT_GT(size, 0u);
  EXPECT_LE(start + size, input.size());

  // All indices inside [start, start + size) are reported as contained.
  for (size_t idx = start; idx < start + size; ++idx) {
    EXPECT_TRUE(it.SequenceContains(idx));
  }

  // If there is text before the sequence, indices before 'start' should not be contained.
  if (start > 0) {
    EXPECT_FALSE(it.SequenceContains(start - 1));
  }

  // The first index after the sequence should not be contained (if in range).
  if (start + size < input.size()) {
    EXPECT_FALSE(it.SequenceContains(start + size));
  }

  // Only one ANSI sequence was inserted; iteration should stop after it.
  EXPECT_FALSE(it.NextSequence());
}

// Normal operation + Reset behavior: multiple sequences and full traversal.
TEST_F(AnsiColorSequenceIteratorTest_101, MultipleSequencesTraversalAndReset_101) {
  // Text with two separate ANSI color sequences.
  // Layout (conceptually):
  //   "pre " + red + " mid " + green + " post"
  const std::string input =
      std::string("pre ") + "\x1b[31m" + " mid " + "\x1b[32m" + " post";

  AnsiColorSequenceIterator it(input);

  // First traversal from the beginning.
  const size_t first_count = CountSequencesFromStart(it);
  EXPECT_EQ(first_count, 2u);

  // After reaching the end, Reset() should allow us to traverse again
  // and see the same number of sequences.
  const size_t second_count = CountSequencesFromStart(it);
  EXPECT_EQ(second_count, 2u);
  EXPECT_EQ(first_count, second_count);
}
