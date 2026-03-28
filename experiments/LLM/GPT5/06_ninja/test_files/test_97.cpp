#include <gtest/gtest.h>
#include <string>

// Bring in the implementation that defines AnsiColorSequenceIterator.
// Adjust the include path as needed for your project layout.
#include "elide_middle.cc"

class AnsiColorSequenceIteratorTest_97 : public ::testing::Test {};

// Plain string without any ESC characters: no sequences should be found.
TEST_F(AnsiColorSequenceIteratorTest_97, PlainStringHasNoSequences_97) {
  const std::string input = "hello world";

  AnsiColorSequenceIterator iter(input);

  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), static_cast<size_t>(0));
  EXPECT_EQ(iter.SequenceEnd(), static_cast<size_t>(0));
  EXPECT_EQ(iter.SequenceSize(), static_cast<size_t>(0));

  // SequenceContains should be false for any index when there is no sequence.
  EXPECT_FALSE(iter.SequenceContains(0));
  EXPECT_FALSE(iter.SequenceContains(5));
}

// Simple case with a single ANSI color sequence in the middle of the string.
TEST_F(AnsiColorSequenceIteratorTest_97, SingleColorSequenceBasic_97) {
  // "abc" + "\x1b[31m" + "def"
  const std::string input = std::string("abc") + "\x1b[31m" + "def";
  // Indices:
  // 0:a 1:b 2:c 3:ESC 4:'[' 5:'3' 6:'1' 7:'m' 8:d 9:e 10:f
  // So the sequence is [3, 8).

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), static_cast<size_t>(3));
  EXPECT_EQ(iter.SequenceEnd(), static_cast<size_t>(8));
  EXPECT_EQ(iter.SequenceSize(), static_cast<size_t>(5));

  // Boundary checks for SequenceContains.
  EXPECT_FALSE(iter.SequenceContains(2));  // before
  EXPECT_TRUE(iter.SequenceContains(3));   // at start
  EXPECT_TRUE(iter.SequenceContains(7));   // last char in sequence
  EXPECT_FALSE(iter.SequenceContains(8));  // end is exclusive

  // After moving past the only sequence, there should be no more.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), static_cast<size_t>(0));
  EXPECT_EQ(iter.SequenceEnd(), static_cast<size_t>(0));
}

// Multiple color sequences: iterator should walk them in order and Reset()
// should bring it back to the first one.
TEST_F(AnsiColorSequenceIteratorTest_97, MultipleColorSequencesAndReset_97) {
  const std::string input = "\x1b[31mX\x1b[0mY\x1b[32mZ\x1b[0m";
  // Indices (for reference):
  // 0:ESC 1:'[' 2:'3' 3:'1' 4:'m' 5:'X'
  // 6:ESC 7:'[' 8:'0' 9:'m' 10:'Y'
  // 11:ESC 12:'[' 13:'3' 14:'2' 15:'m' 16:'Z'
  // 17:ESC 18:'[' 19:'0' 20:'m'
  // Sequences: [0,5), [6,10), [11,16), [17,21)

  const std::pair<size_t, size_t> expected[] = {
      {0u, 5u}, {6u, 10u}, {11u, 16u}, {17u, 21u}};

  AnsiColorSequenceIterator iter(input);

  size_t index = 0;
  for (; iter.HasSequence(); iter.NextSequence(), ++index) {
    ASSERT_LT(index, sizeof(expected) / sizeof(expected[0]));
    EXPECT_EQ(iter.SequenceStart(), expected[index].first);
    EXPECT_EQ(iter.SequenceEnd(), expected[index].second);
    EXPECT_EQ(iter.SequenceSize(),
              expected[index].second - expected[index].first);
  }
  EXPECT_EQ(index, sizeof(expected) / sizeof(expected[0]));

  // Reset should bring us back to the first sequence.
  iter.Reset();
  ASSERT_TRUE(iter.HasSequence());
  EXPECT_EQ(iter.SequenceStart(), expected[0].first);
  EXPECT_EQ(iter.SequenceEnd(), expected[0].second);
}

// Non-color ANSI sequences (e.g., ESC[0K) must be ignored;
// iterator should only report color sequences ending with 'm'.
TEST_F(AnsiColorSequenceIteratorTest_97, IgnoresNonColorAnsiSequences_97) {
  // "A" + "\x1b[0K" (erase line; non-color) + "BC"
  // + "\x1b[31m" + "D" + "\x1b[0m" + "E"
  const std::string input = "A\x1b[0KBC\x1b[31mD\x1b[0mE";
  // From inspection (see implementation), the first *color* sequence
  // starts at the ESC before "[31m", not at the ESC before "[0K".

  AnsiColorSequenceIterator iter(input);

  ASSERT_TRUE(iter.HasSequence());
  // Expected first color sequence: ESC[31m at index 7.
  EXPECT_EQ(iter.SequenceStart(), static_cast<size_t>(7));
  // We don't strictly need the exact end index for this behavior check,
  // but verifying it adds coverage.
  EXPECT_EQ(iter.SequenceEnd(), static_cast<size_t>(12));
  EXPECT_EQ(iter.SequenceSize(), static_cast<size_t>(5));

  // Next sequence should be the trailing "\x1b[0m".
  ASSERT_TRUE(iter.NextSequence());
  EXPECT_EQ(iter.SequenceStart(), static_cast<size_t>(13));
  EXPECT_EQ(iter.SequenceEnd(), static_cast<size_t>(17));

  // No more sequences after that.
  EXPECT_FALSE(iter.NextSequence());
  EXPECT_FALSE(iter.HasSequence());
}

// Incomplete or truncated sequences at the end of the string should be ignored.
TEST_F(AnsiColorSequenceIteratorTest_97, IncompleteOrTruncatedSequencesIgnored_97) {
  {
    // ESC as last character: too short to form a valid color sequence.
    const std::string input = "no color \x1b";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
  }

  {
    // ESC '[' '3' '1' with no trailing 'm': parameters with no command.
    const std::string input = "no color \x1b[31";
    AnsiColorSequenceIterator iter(input);
    EXPECT_FALSE(iter.HasSequence());
  }
}
