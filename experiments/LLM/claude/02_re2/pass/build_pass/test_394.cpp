#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstTest_394 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default-construct an Inst; out_opcode_ should be 0 by default
    // since Inst() = default and we zero-initialize.
    memset(&inst_, 0, sizeof(inst_));
  }

  Prog::Inst inst_;
};

// Test that InitMatch sets the opcode to kInstMatch
TEST_F(ProgInstTest_394, InitMatchSetsOpcode_394) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test that InitMatch sets the match_id correctly
TEST_F(ProgInstTest_394, InitMatchSetsMatchId_394) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test InitMatch with match id of 0
TEST_F(ProgInstTest_394, InitMatchWithZeroId_394) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test InitMatch with a large match id
TEST_F(ProgInstTest_394, InitMatchWithLargeId_394) {
  inst_.InitMatch(999999);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 999999);
}

// Test InitMatch with a negative match id
TEST_F(ProgInstTest_394, InitMatchWithNegativeId_394) {
  inst_.InitMatch(-1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), -1);
}

// Test InitAlt sets opcode and out/out1
TEST_F(ProgInstTest_394, InitAltSetsOpcode_394) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitByteRange sets opcode, lo, hi, foldcase, and out
TEST_F(ProgInstTest_394, InitByteRangeSetsFields_394) {
  inst_.InitByteRange(0x41, 0x5A, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x5A);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 5);
}

// Test InitByteRange with foldcase enabled
TEST_F(ProgInstTest_394, InitByteRangeWithFoldcase_394) {
  inst_.InitByteRange(0x61, 0x7A, 1, 3);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x7A);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 3);
}

// Test InitCapture sets opcode, cap, and out
TEST_F(ProgInstTest_394, InitCaptureSetsFields_394) {
  inst_.InitCapture(2, 7);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 2);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitEmptyWidth sets opcode, empty, and out (using kEmptyBeginLine as an example)
TEST_F(ProgInstTest_394, InitEmptyWidthSetsFields_394) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 4);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

// Test InitNop sets opcode and out
TEST_F(ProgInstTest_394, InitNopSetsFields_394) {
  inst_.InitNop(8);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 8);
}

// Test InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_394, InitFailSetsOpcode_394) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Dump returns a non-empty string for a match instruction
TEST_F(ProgInstTest_394, DumpReturnsNonEmptyForMatch_394) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump returns a non-empty string for a fail instruction
TEST_F(ProgInstTest_394, DumpReturnsNonEmptyForFail_394) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy construction preserves fields
TEST_F(ProgInstTest_394, CopyConstructorPreservesFields_394) {
  inst_.InitMatch(55);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstMatch);
  EXPECT_EQ(copy.match_id(), 55);
}

// Test copy assignment preserves fields
TEST_F(ProgInstTest_394, CopyAssignmentPreservesFields_394) {
  inst_.InitMatch(77);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other.InitFail();
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 77);
}

// Test InitByteRange boundary: single byte range (lo == hi)
TEST_F(ProgInstTest_394, InitByteRangeSingleByte_394) {
  inst_.InitByteRange(0x00, 0x00, 0, 1);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0x00);
}

// Test InitByteRange boundary: full byte range
TEST_F(ProgInstTest_394, InitByteRangeFullRange_394) {
  inst_.InitByteRange(0x00, 0xFF, 0, 2);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test InitCapture with cap = 0
TEST_F(ProgInstTest_394, InitCaptureWithZeroCap_394) {
  inst_.InitCapture(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 1);
}

// Test InitAlt with zero values
TEST_F(ProgInstTest_394, InitAltWithZeroValues_394) {
  inst_.InitAlt(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.out1(), 0);
}

// Test InitNop with zero out
TEST_F(ProgInstTest_394, InitNopWithZeroOut_394) {
  inst_.InitNop(0);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 0);
}

// Test Matches on a ByteRange instruction for a character within range
TEST_F(ProgInstTest_394, MatchesByteInRange_394) {
  inst_.InitByteRange('a', 'z', 0, 1);
  EXPECT_TRUE(inst_.Matches('m'));
}

// Test Matches on a ByteRange instruction for a character outside range
TEST_F(ProgInstTest_394, MatchesByteOutOfRange_394) {
  inst_.InitByteRange('a', 'z', 0, 1);
  EXPECT_FALSE(inst_.Matches('A'));
}

// Test Matches on boundary characters
TEST_F(ProgInstTest_394, MatchesByteAtBoundary_394) {
  inst_.InitByteRange('a', 'z', 0, 1);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
}

// Test Matches with foldcase on uppercase letter matching lowercase range
TEST_F(ProgInstTest_394, MatchesByteWithFoldcase_394) {
  inst_.InitByteRange('a', 'z', 1, 1);
  // With foldcase, 'A' should match 'a'-'z' range
  EXPECT_TRUE(inst_.Matches('A'));
}

}  // namespace re2
