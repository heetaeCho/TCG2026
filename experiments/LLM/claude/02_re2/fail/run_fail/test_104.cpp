#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_104 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test lo() after InitByteRange
TEST_F(ProgInstTest_104, LoReturnsCorrectValueAfterInitByteRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x41);
}

// Test hi() after InitByteRange
TEST_F(ProgInstTest_104, HiReturnsCorrectValueAfterInitByteRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.hi(), 0x5A);
}

// Test lo() with minimum byte value
TEST_F(ProgInstTest_104, LoReturnsZeroForMinByte_104) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x00);
}

// Test hi() with maximum byte value
TEST_F(ProgInstTest_104, HiReturnsMaxForMaxByte_104) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test lo() and hi() are equal for single byte range
TEST_F(ProgInstTest_104, LoEqualsHiForSingleByteRange_104) {
  inst_.InitByteRange(0x61, 0x61, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x61);
}

// Test opcode after InitByteRange
TEST_F(ProgInstTest_104, OpcodeIsByteRangeAfterInitByteRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test foldcase after InitByteRange with foldcase=0
TEST_F(ProgInstTest_104, FoldcaseReturnsFalseWhenNotSet_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.foldcase(), 0);
}

// Test foldcase after InitByteRange with foldcase=1
TEST_F(ProgInstTest_104, FoldcaseReturnsTrueWhenSet_104) {
  inst_.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(inst_.foldcase(), 1);
}

// Test out() after InitByteRange
TEST_F(ProgInstTest_104, OutReturnsCorrectValueAfterInitByteRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 42);
  EXPECT_EQ(inst_.out(), 42);
}

// Test InitAlt sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsAltAfterInitAlt_104) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

// Test out() after InitAlt
TEST_F(ProgInstTest_104, OutReturnsCorrectValueAfterInitAlt_104) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.out(), 10);
}

// Test out1() after InitAlt
TEST_F(ProgInstTest_104, Out1ReturnsCorrectValueAfterInitAlt_104) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitCapture sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsCaptureAfterInitCapture_104) {
  inst_.InitCapture(3, 5);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test cap() after InitCapture
TEST_F(ProgInstTest_104, CapReturnsCorrectValueAfterInitCapture_104) {
  inst_.InitCapture(3, 5);
  EXPECT_EQ(inst_.cap(), 3);
}

// Test out() after InitCapture
TEST_F(ProgInstTest_104, OutReturnsCorrectValueAfterInitCapture_104) {
  inst_.InitCapture(3, 5);
  EXPECT_EQ(inst_.out(), 5);
}

// Test InitEmptyWidth sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsEmptyWidthAfterInitEmptyWidth_104) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

// Test empty() after InitEmptyWidth
TEST_F(ProgInstTest_104, EmptyReturnsCorrectValueAfterInitEmptyWidth_104) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

// Test out() after InitEmptyWidth
TEST_F(ProgInstTest_104, OutReturnsCorrectValueAfterInitEmptyWidth_104) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitMatch sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsMatchAfterInitMatch_104) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test match_id() after InitMatch
TEST_F(ProgInstTest_104, MatchIdReturnsCorrectValueAfterInitMatch_104) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test InitNop sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsNopAfterInitNop_104) {
  inst_.InitNop(3);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test out() after InitNop
TEST_F(ProgInstTest_104, OutReturnsCorrectValueAfterInitNop_104) {
  inst_.InitNop(3);
  EXPECT_EQ(inst_.out(), 3);
}

// Test InitFail sets opcode correctly
TEST_F(ProgInstTest_104, OpcodeIsFailAfterInitFail_104) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Matches() for ByteRange - character in range
TEST_F(ProgInstTest_104, MatchesReturnsTrueForCharInRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);  // A-Z
  EXPECT_TRUE(inst_.Matches(0x41));  // 'A'
  EXPECT_TRUE(inst_.Matches(0x4D));  // 'M'
  EXPECT_TRUE(inst_.Matches(0x5A));  // 'Z'
}

// Test Matches() for ByteRange - character out of range
TEST_F(ProgInstTest_104, MatchesReturnsFalseForCharOutOfRange_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);  // A-Z
  EXPECT_FALSE(inst_.Matches(0x40));  // '@'
  EXPECT_FALSE(inst_.Matches(0x5B));  // '['
  EXPECT_FALSE(inst_.Matches(0x61));  // 'a'
}

// Test Matches() with foldcase for ByteRange
TEST_F(ProgInstTest_104, MatchesWithFoldcaseMatchesLowercase_104) {
  inst_.InitByteRange('a', 'z', 1, 0);
  // With foldcase, uppercase should match lowercase range
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

// Test Dump() returns non-empty string
TEST_F(ProgInstTest_104, DumpReturnsNonEmptyString_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump() for different instruction types
TEST_F(ProgInstTest_104, DumpForMatchReturnsNonEmptyString_104) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump() for alt
TEST_F(ProgInstTest_104, DumpForAltReturnsNonEmptyString_104) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump() for fail
TEST_F(ProgInstTest_104, DumpForFailReturnsNonEmptyString_104) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor preserves state
TEST_F(ProgInstTest_104, CopyConstructorPreservesState_104) {
  inst_.InitByteRange(0x41, 0x5A, 1, 10);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.foldcase(), 1);
  EXPECT_EQ(copy.out(), 10);
}

// Test copy assignment preserves state
TEST_F(ProgInstTest_104, CopyAssignmentPreservesState_104) {
  inst_.InitByteRange(0x41, 0x5A, 1, 10);
  Prog::Inst other;
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstByteRange);
  EXPECT_EQ(other.lo(), 0x41);
  EXPECT_EQ(other.hi(), 0x5A);
  EXPECT_EQ(other.foldcase(), 1);
  EXPECT_EQ(other.out(), 10);
}

// Test InitByteRange with boundary byte values
TEST_F(ProgInstTest_104, InitByteRangeWithBoundaryValues_104) {
  inst_.InitByteRange(0, 255, 0, 0);
  EXPECT_EQ(inst_.lo(), 0);
  EXPECT_EQ(inst_.hi(), 255);
}

// Test InitMatch with zero id
TEST_F(ProgInstTest_104, InitMatchWithZeroId_104) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.match_id(), 0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test InitCapture with zero cap
TEST_F(ProgInstTest_104, InitCaptureWithZeroCap_104) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test Matches for single byte range at boundary
TEST_F(ProgInstTest_104, MatchesSingleByteAtZero_104) {
  inst_.InitByteRange(0, 0, 0, 0);
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_FALSE(inst_.Matches(1));
}

// Test Matches for single byte range at max
TEST_F(ProgInstTest_104, MatchesSingleByteAt255_104) {
  inst_.InitByteRange(255, 255, 0, 0);
  EXPECT_TRUE(inst_.Matches(255));
  EXPECT_FALSE(inst_.Matches(254));
}

// Test reinitializing an instruction overwrites previous state
TEST_F(ProgInstTest_104, ReinitializationOverwritesPreviousState_104) {
  inst_.InitByteRange(0x41, 0x5A, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x41);

  inst_.InitMatch(99);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 99);
}

// Test InitAlt with same out and out1
TEST_F(ProgInstTest_104, InitAltWithSameOutValues_104) {
  inst_.InitAlt(5, 5);
  EXPECT_EQ(inst_.out(), 5);
  EXPECT_EQ(inst_.out1(), 5);
}

// Test multiple EmptyOp values
TEST_F(ProgInstTest_104, EmptyWidthWithMultipleFlags_104) {
  EmptyOp combined = static_cast<EmptyOp>(kEmptyBeginLine | kEmptyEndLine);
  inst_.InitEmptyWidth(combined, 3);
  EXPECT_EQ(inst_.empty(), combined);
}

}  // namespace re2
