#include "gtest/gtest.h"
#include <string>

// Forward declaration based on the known interface
struct AnsiColorSequenceIterator {
private:
  size_t cur_start_ = 0;
  size_t cur_end_ = 0;
  const char* input_;
  const char* input_end_;

public:
  AnsiColorSequenceIterator(const std::string& input);
  bool HasSequence() const;
  size_t SequenceStart() const;
  size_t SequenceEnd() const;
  size_t SequenceSize() const;
  bool SequenceContains(size_t input_index) const;
  bool NextSequence();
  void Reset();

private:
  bool FindNextSequenceFrom(const char* from);
};

// Include the actual implementation
#include "elide_middle.cc"

class AnsiColorSequenceIteratorTest_96 : public ::testing::Test {};

// Test with empty string - no sequences expected
TEST_F(AnsiColorSequenceIteratorTest_96, EmptyString_96) {
  std::string input = "";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}

// Test with string containing no ANSI sequences
TEST_F(AnsiColorSequenceIteratorTest_96, NoAnsiSequences_96) {
  std::string input = "Hello World";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}

// Test with a single ANSI color sequence
TEST_F(AnsiColorSequenceIteratorTest_96, SingleAnsiSequence_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
  EXPECT_GT(it.SequenceEnd(), it.SequenceStart());
  EXPECT_GT(it.SequenceSize(), 0u);
}

// Test SequenceStart returns correct position for sequence at beginning
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceStartAtBeginning_96) {
  std::string input = "\033[0mtext";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
}

// Test SequenceStart for sequence in middle of string
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceStartInMiddle_96) {
  std::string input = "Hello\033[31mWorld";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 5u);
}

// Test SequenceEnd is after SequenceStart
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceEndAfterStart_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_GT(it.SequenceEnd(), it.SequenceStart());
}

// Test SequenceSize equals End - Start
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceSizeConsistency_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceSize(), it.SequenceEnd() - it.SequenceStart());
}

// Test SequenceContains for index within sequence
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceContainsWithinRange_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  // Index 0 should be within the sequence
  EXPECT_TRUE(it.SequenceContains(0));
}

// Test SequenceContains for index outside sequence
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceContainsOutsideRange_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  // Index well past the sequence should not be contained
  EXPECT_FALSE(it.SequenceContains(input.size() - 1));
}

// Test NextSequence with multiple sequences
TEST_F(AnsiColorSequenceIteratorTest_96, MultipleSequencesNextSequence_96) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  size_t first_start = it.SequenceStart();
  
  bool has_next = it.NextSequence();
  if (has_next) {
    EXPECT_GT(it.SequenceStart(), first_start);
  }
}

// Test NextSequence returns false when no more sequences
TEST_F(AnsiColorSequenceIteratorTest_96, NextSequenceReturnsFalseAtEnd_96) {
  std::string input = "\033[31mHello";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  
  // Keep calling NextSequence until it returns false
  while (it.NextSequence()) {
    // continue
  }
  EXPECT_FALSE(it.NextSequence());
}

// Test Reset brings iterator back to first sequence
TEST_F(AnsiColorSequenceIteratorTest_96, ResetReturnsToFirstSequence_96) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator it(input);
  
  if (it.HasSequence()) {
    size_t first_start = it.SequenceStart();
    size_t first_end = it.SequenceEnd();
    
    it.NextSequence();
    it.Reset();
    
    EXPECT_TRUE(it.HasSequence());
    EXPECT_EQ(it.SequenceStart(), first_start);
    EXPECT_EQ(it.SequenceEnd(), first_end);
  }
}

// Test with only ANSI sequence and no other text
TEST_F(AnsiColorSequenceIteratorTest_96, OnlyAnsiSequence_96) {
  std::string input = "\033[31m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
}

// Test with reset sequence
TEST_F(AnsiColorSequenceIteratorTest_96, ResetSequence_96) {
  std::string input = "\033[0m";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
}

// Test with multiple parameters in sequence
TEST_F(AnsiColorSequenceIteratorTest_96, MultiParamSequence_96) {
  std::string input = "\033[1;31;42mColored";
  AnsiColorSequenceIterator it(input);
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
}

// Test that HasSequence is consistent before and after check
TEST_F(AnsiColorSequenceIteratorTest_96, HasSequenceConsistency_96) {
  std::string input = "text\033[31mmore";
  AnsiColorSequenceIterator it(input);
  bool first_call = it.HasSequence();
  bool second_call = it.HasSequence();
  EXPECT_EQ(first_call, second_call);
}

// Test with incomplete escape sequence (just ESC without '[')
TEST_F(AnsiColorSequenceIteratorTest_96, IncompleteEscapeSequence_96) {
  std::string input = "\033Hello";
  AnsiColorSequenceIterator it(input);
  // Incomplete sequence - implementation may or may not detect
  // Just verify it doesn't crash
  it.HasSequence();
}

// Test with string containing only escape character
TEST_F(AnsiColorSequenceIteratorTest_96, OnlyEscapeChar_96) {
  std::string input = "\033";
  AnsiColorSequenceIterator it(input);
  // Just verify no crash
  it.HasSequence();
}

// Test SequenceContains at boundary of sequence
TEST_F(AnsiColorSequenceIteratorTest_96, SequenceContainsBoundary_96) {
  std::string input = "AB\033[31mCD";
  AnsiColorSequenceIterator it(input);
  if (it.HasSequence()) {
    size_t start = it.SequenceStart();
    size_t end = it.SequenceEnd();
    
    // Just before start should not be contained (if start > 0)
    if (start > 0) {
      EXPECT_FALSE(it.SequenceContains(start - 1));
    }
    // Start should be contained
    EXPECT_TRUE(it.SequenceContains(start));
    // End should not be contained (half-open interval) or check behavior
    // The exact boundary behavior depends on implementation
  }
}

// Test three sequences and iterate through all
TEST_F(AnsiColorSequenceIteratorTest_96, ThreeSequencesIteration_96) {
  std::string input = "\033[31mRed\033[32mGreen\033[0mNormal";
  AnsiColorSequenceIterator it(input);
  
  int count = 0;
  if (it.HasSequence()) {
    count = 1;
    while (it.NextSequence()) {
      count++;
    }
  }
  EXPECT_EQ(count, 3);
}

// Test Reset after full iteration
TEST_F(AnsiColorSequenceIteratorTest_96, ResetAfterFullIteration_96) {
  std::string input = "\033[31mHello\033[0m";
  AnsiColorSequenceIterator it(input);
  
  // Iterate through all
  while (it.HasSequence() && it.NextSequence()) {}
  
  it.Reset();
  EXPECT_TRUE(it.HasSequence());
  EXPECT_EQ(it.SequenceStart(), 0u);
}

// Test with no-op on string with special characters but no ANSI
TEST_F(AnsiColorSequenceIteratorTest_96, SpecialCharsNoAnsi_96) {
  std::string input = "Hello [31m World";
  AnsiColorSequenceIterator it(input);
  EXPECT_FALSE(it.HasSequence());
}
