#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_106 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test foldcase returns 0 when initialized with foldcase=0
TEST_F(ProgInstTest_106, FoldcaseReturnsFalseWhenNotSet_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(0, inst_.foldcase());
}

// Test foldcase returns 1 when initialized with foldcase=1
TEST_F(ProgInstTest_106, FoldcaseReturnsTrueWhenSet_106) {
  inst_.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(1, inst_.foldcase());
}

// Test opcode is kInstByteRange after InitByteRange
TEST_F(ProgInstTest_106, OpcodeIsByteRangeAfterInitByteRange_106) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(kInstByteRange, inst_.opcode());
}

// Test lo and hi values after InitByteRange
TEST_F(ProgInstTest_106, LoHiValuesAfterInitByteRange_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(0x41, inst_.lo());
  EXPECT_EQ(0x5A, inst_.hi());
}

// Test out value after InitByteRange
TEST_F(ProgInstTest_106, OutValueAfterInitByteRange_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 42);
  EXPECT_EQ(42, inst_.out());
}

// Test InitByteRange with full byte range
TEST_F(ProgInstTest_106, InitByteRangeFullRange_106) {
  inst_.InitByteRange(0x00, 0xFF, 1, 100);
  EXPECT_EQ(0x00, inst_.lo());
  EXPECT_EQ(0xFF, inst_.hi());
  EXPECT_EQ(1, inst_.foldcase());
  EXPECT_EQ(100, inst_.out());
}

// Test InitByteRange with single byte range
TEST_F(ProgInstTest_106, InitByteRangeSingleByte_106) {
  inst_.InitByteRange(0x61, 0x61, 0, 5);
  EXPECT_EQ(0x61, inst_.lo());
  EXPECT_EQ(0x61, inst_.hi());
  EXPECT_EQ(0, inst_.foldcase());
}

// Test InitAlt sets opcode to kInstAlt
TEST_F(ProgInstTest_106, InitAltSetsCorrectOpcode_106) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(kInstAlt, inst_.opcode());
}

// Test InitAlt out and out1
TEST_F(ProgInstTest_106, InitAltOutValues_106) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(10, inst_.out());
  EXPECT_EQ(20, inst_.out1());
}

// Test InitCapture sets opcode to kInstCapture
TEST_F(ProgInstTest_106, InitCaptureSetsCorrectOpcode_106) {
  inst_.InitCapture(3, 50);
  EXPECT_EQ(kInstCapture, inst_.opcode());
}

// Test InitCapture cap and out values
TEST_F(ProgInstTest_106, InitCaptureValues_106) {
  inst_.InitCapture(3, 50);
  EXPECT_EQ(3, inst_.cap());
  EXPECT_EQ(50, inst_.out());
}

// Test InitEmptyWidth sets opcode to kInstEmptyWidth
TEST_F(ProgInstTest_106, InitEmptyWidthSetsCorrectOpcode_106) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(kInstEmptyWidth, inst_.opcode());
}

// Test InitEmptyWidth values
TEST_F(ProgInstTest_106, InitEmptyWidthValues_106) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(kEmptyBeginLine, inst_.empty());
  EXPECT_EQ(7, inst_.out());
}

// Test InitMatch sets opcode to kInstMatch
TEST_F(ProgInstTest_106, InitMatchSetsCorrectOpcode_106) {
  inst_.InitMatch(1);
  EXPECT_EQ(kInstMatch, inst_.opcode());
}

// Test InitMatch match_id
TEST_F(ProgInstTest_106, InitMatchId_106) {
  inst_.InitMatch(42);
  EXPECT_EQ(42, inst_.match_id());
}

// Test InitNop sets opcode to kInstNop
TEST_F(ProgInstTest_106, InitNopSetsCorrectOpcode_106) {
  inst_.InitNop(15);
  EXPECT_EQ(kInstNop, inst_.opcode());
}

// Test InitNop out value
TEST_F(ProgInstTest_106, InitNopOutValue_106) {
  inst_.InitNop(15);
  EXPECT_EQ(15, inst_.out());
}

// Test InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_106, InitFailSetsCorrectOpcode_106) {
  inst_.InitFail();
  EXPECT_EQ(kInstFail, inst_.opcode());
}

// Test Matches returns true for byte in range
TEST_F(ProgInstTest_106, MatchesReturnsTrueForByteInRange_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x41));
  EXPECT_TRUE(inst_.Matches(0x4D));
  EXPECT_TRUE(inst_.Matches(0x5A));
}

// Test Matches returns false for byte outside range
TEST_F(ProgInstTest_106, MatchesReturnsFalseForByteOutsideRange_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_FALSE(inst_.Matches(0x40));
  EXPECT_FALSE(inst_.Matches(0x5B));
  EXPECT_FALSE(inst_.Matches(0x00));
  EXPECT_FALSE(inst_.Matches(0xFF));
}

// Test Matches with foldcase - lowercase should match uppercase range
TEST_F(ProgInstTest_106, MatchesWithFoldcase_106) {
  // 'a' to 'z' with foldcase
  inst_.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_TRUE(inst_.Matches('m'));
}

// Test Matches with single byte range
TEST_F(ProgInstTest_106, MatchesSingleByteRange_106) {
  inst_.InitByteRange(0x61, 0x61, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x61));
  EXPECT_FALSE(inst_.Matches(0x60));
  EXPECT_FALSE(inst_.Matches(0x62));
}

// Test copy construction
TEST_F(ProgInstTest_106, CopyConstruction_106) {
  inst_.InitByteRange(0x41, 0x5A, 1, 42);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.foldcase(), 1);
  EXPECT_EQ(copy.out(), 42);
}

// Test copy assignment
TEST_F(ProgInstTest_106, CopyAssignment_106) {
  inst_.InitByteRange(0x41, 0x5A, 1, 42);
  Prog::Inst other;
  other.InitNop(0);
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstByteRange);
  EXPECT_EQ(other.lo(), 0x41);
  EXPECT_EQ(other.hi(), 0x5A);
  EXPECT_EQ(other.foldcase(), 1);
}

// Test Dump produces non-empty string for ByteRange
TEST_F(ProgInstTest_106, DumpByteRangeNotEmpty_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump produces non-empty string for Match
TEST_F(ProgInstTest_106, DumpMatchNotEmpty_106) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump produces non-empty string for Fail
TEST_F(ProgInstTest_106, DumpFailNotEmpty_106) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test InitByteRange boundary values for lo and hi (0 and 255)
TEST_F(ProgInstTest_106, InitByteRangeBoundaryValues_106) {
  inst_.InitByteRange(0, 255, 0, 0);
  EXPECT_EQ(0, inst_.lo());
  EXPECT_EQ(255, inst_.hi());
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_TRUE(inst_.Matches(255));
  EXPECT_TRUE(inst_.Matches(128));
}

// Test InitMatch with match id of 0
TEST_F(ProgInstTest_106, InitMatchWithZeroId_106) {
  inst_.InitMatch(0);
  EXPECT_EQ(kInstMatch, inst_.opcode());
  EXPECT_EQ(0, inst_.match_id());
}

// Test InitCapture with cap 0
TEST_F(ProgInstTest_106, InitCaptureWithZeroCap_106) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(kInstCapture, inst_.opcode());
  EXPECT_EQ(0, inst_.cap());
  EXPECT_EQ(0, inst_.out());
}

// Test hint after InitByteRange with foldcase=0
TEST_F(ProgInstTest_106, HintAfterInitByteRange_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  // hint should be accessible (value depends on initialization, but should not crash)
  int h = inst_.hint();
  (void)h;  // Just verify it doesn't crash
}

// Test InitByteRange with out value of 0
TEST_F(ProgInstTest_106, InitByteRangeOutZero_106) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(0, inst_.out());
}

// Test InitNop with out value of 0
TEST_F(ProgInstTest_106, InitNopOutZero_106) {
  inst_.InitNop(0);
  EXPECT_EQ(kInstNop, inst_.opcode());
  EXPECT_EQ(0, inst_.out());
}

// Test foldcase bit isolation (hint_foldcase_ & 1)
TEST_F(ProgInstTest_106, FoldcaseBitIsolation_106) {
  // With foldcase=0
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(0, inst_.foldcase());
  
  // With foldcase=1
  inst_.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(1, inst_.foldcase());
}

}  // namespace re2
