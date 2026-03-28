#include "gtest/gtest.h"
#include <string>

// Include the header that declares AnsiColorSequenceIterator
// Based on the file structure, it's likely in elide_middle.h or similar
#include "elide_middle.h"

class AnsiColorSequenceIteratorTest_170 : public ::testing::Test {
};

// Test with empty string - no sequences expected
TEST_F(AnsiColorSequenceIteratorTest_170, EmptyString_170) {
  std::string input = "";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}

// Test with string containing no ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_170, NoAnsiSequences_170) {
  std::string input = "Hello, world!";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}

// Test with a single ANSI color sequence
TEST_F(AnsiColorSequenceIteratorTest_170, SingleAnsiSequence_170) {
  std::string input = "\033[31mRed text";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
  // The sequence is "\033[31m" which is 5 characters
  EXPECT_EQ(it.SequenceEnd(), 5u);
  EXPECT_EQ(it.SequenceSize(), 5u);
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_170, SingleSequenceNextReturnsFalse_170) {
  std::string input = "\033[31mRed";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_FALSE(it.NextSequence());
}

// Test with multiple ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_170, MultipleAnsiSequences_170) {
  std::string input = "\033[31mRed\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);

  EXPECT_TRUE(it.NextSequence());
  EXPECT_TRUE(it.HasSequence());
  // Second sequence starts after "Red" at position 8
  EXPECT_EQ(it.SequenceStart(), 8u);

  EXPECT_FALSE(it.NextSequence());
}

// Test SequenceContains for index inside sequence
TEST_F(AnsiColorSequenceIteratorTest_170, SequenceContainsInsideSequence_170) {
  std::string input = "\033[31mText";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  // Indices 0-4 are within the sequence "\033[31m"
  EXPECT_TRUE(it.SequenceContains(0));
  EXPECT_TRUE(it.SequenceContains(1));
  EXPECT_TRUE(it.SequenceContains(4));
}

// Test SequenceContains for index outside sequence
TEST_F(AnsiColorSequenceIteratorTest_170, SequenceContainsOutsideSequence_170) {
  std::string input = "\033[31mText";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  // Index 5 is 'T', outside the sequence
  EXPECT_FALSE(it.SequenceContains(5));
  EXPECT_FALSE(it.SequenceContains(6));
}

// Test Reset functionality
TEST_F(AnsiColorSequenceIteratorTest_170, ResetRestartsIteration_170) {
  std::string input = "\033[31mRed\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  size_t first_start = it.SequenceStart();

  it.NextSequence();
  EXPECT_NE(it.SequenceStart(), first_start);

  it.Reset();
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), first_start);
}

// Test with ANSI sequence in the middle of string
TEST_F(AnsiColorSequenceIteratorTest_170, SequenceInMiddle_170) {
  std::string input = "Hello\033[32mWorld";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 5u);
}

// Test with only an ANSI sequence (no other text)
TEST_F(AnsiColorSequenceIteratorTest_170, OnlyAnsiSequence_170) {
  std::string input = "\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
  EXPECT_EQ(it.SequenceSize(), 4u);
}

// Test with sequence at the end
TEST_F(AnsiColorSequenceIteratorTest_170, SequenceAtEnd_170) {
  std::string input = "text\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 4u);
  EXPECT_FALSE(it.NextSequence());
}

// Test with incomplete ANSI escape (no terminating letter)
TEST_F(AnsiColorSequenceIteratorTest_170, IncompleteEscapeSequence_170) {
  std::string input = "\033[31";
  AnsiColorSequenceIterator it(input);
  // Incomplete sequence - behavior depends on implementation
  // It may or may not find a sequence
  // We just verify it doesn't crash
  bool has = it.HasSequence();
  (void)has;
}

// Test with just ESC character
TEST_F(AnsiColorSequenceIteratorTest_170, JustEscCharacter_170) {
  std::string input = "\033";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}

// Test SequenceEnd and SequenceSize consistency
TEST_F(AnsiColorSequenceIteratorTest_170, SequenceEndAndSizeConsistency_170) {
  std::string input = "\033[1;31mBold Red\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceEnd() - it.SequenceStart(), it.SequenceSize());

  if (it.NextSequence()) {
    EXPECT_EQ(it.SequenceEnd() - it.SequenceStart(), it.SequenceSize());
  }
}

// Test multiple calls to Reset
TEST_F(AnsiColorSequenceIteratorTest_170, MultipleResets_170) {
  std::string input = "\033[31mA\033[32mB";
  AnsiColorSequenceIterator it(input);

  size_t orig_start = it.SequenceStart();
  it.NextSequence();
  it.Reset();
  EXPECT_EQ(it.SequenceStart(), orig_start);

  it.NextSequence();
  it.Reset();
  EXPECT_EQ(it.SequenceStart(), orig_start);
}

// Test with bold/bright sequence
TEST_F(AnsiColorSequenceIteratorTest_170, BoldSequence_170) {
  std::string input = "\033[1mBold\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
  // "\033[1m" is 4 chars
  EXPECT_EQ(it.SequenceSize(), 4u);
}
