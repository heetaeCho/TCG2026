#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_105 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test that hi() returns the correct value after InitByteRange
TEST_F(ProgInstTest_105, HiReturnsCorrectValueAfterInitByteRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.hi(), 0x5A);
}

// Test hi() with lo == hi (single byte range)
TEST_F(ProgInstTest_105, HiReturnsSameAsLoForSingleByteRange_105) {
  inst_.InitByteRange(0x61, 0x61, 0, 0);
  EXPECT_EQ(inst_.hi(), 0x61);
}

// Test hi() with minimum byte value
TEST_F(ProgInstTest_105, HiReturnsZeroForMinByteRange_105) {
  inst_.InitByteRange(0x00, 0x00, 0, 0);
  EXPECT_EQ(inst_.hi(), 0x00);
}

// Test hi() with maximum byte value
TEST_F(ProgInstTest_105, HiReturnsMaxForMaxByteRange_105) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test hi() with full byte range
TEST_F(ProgInstTest_105, HiReturnsFFForFullByteRange_105) {
  inst_.InitByteRange(0x00, 0xFF, 1, 0);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test lo() returns correct value after InitByteRange
TEST_F(ProgInstTest_105, LoReturnsCorrectValueAfterInitByteRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x41);
}

// Test opcode() is kInstByteRange after InitByteRange
TEST_F(ProgInstTest_105, OpcodeIsByteRangeAfterInitByteRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test foldcase() returns correct value
TEST_F(ProgInstTest_105, FoldcaseReturnsCorrectValue_105) {
  inst_.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(inst_.foldcase(), 1);
}

// Test foldcase() returns zero when not set
TEST_F(ProgInstTest_105, FoldcaseReturnsZeroWhenNotSet_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.foldcase(), 0);
}

// Test out() returns correct value after InitByteRange
TEST_F(ProgInstTest_105, OutReturnsCorrectValueAfterInitByteRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 42);
  EXPECT_EQ(inst_.out(), 42);
}

// Test InitAlt sets opcode correctly
TEST_F(ProgInstTest_105, InitAltSetsOpcodeToAlt_105) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

// Test InitAlt sets out and out1
TEST_F(ProgInstTest_105, InitAltSetsOutAndOut1_105) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitCapture sets opcode correctly
TEST_F(ProgInstTest_105, InitCaptureSetsOpcodeToCapture_105) {
  inst_.InitCapture(3, 5);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test InitCapture sets cap and out
TEST_F(ProgInstTest_105, InitCaptureSetsCap_105) {
  inst_.InitCapture(3, 5);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 5);
}

// Test InitEmptyWidth sets opcode correctly
TEST_F(ProgInstTest_105, InitEmptyWidthSetsOpcodeToEmptyWidth_105) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

// Test InitEmptyWidth sets empty and out
TEST_F(ProgInstTest_105, InitEmptyWidthSetsEmpty_105) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitMatch sets opcode correctly
TEST_F(ProgInstTest_105, InitMatchSetsOpcodeToMatch_105) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test InitMatch sets match_id
TEST_F(ProgInstTest_105, InitMatchSetsMatchId_105) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test InitNop sets opcode correctly
TEST_F(ProgInstTest_105, InitNopSetsOpcodeToNop_105) {
  inst_.InitNop(3);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitNop sets out
TEST_F(ProgInstTest_105, InitNopSetsOut_105) {
  inst_.InitNop(3);
  EXPECT_EQ(inst_.out(), 3);
}

// Test InitFail sets opcode correctly
TEST_F(ProgInstTest_105, InitFailSetsOpcodeToFail_105) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Matches for a byte within range
TEST_F(ProgInstTest_105, MatchesReturnsTrueForByteInRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x41));
  EXPECT_TRUE(inst_.Matches(0x4D));
  EXPECT_TRUE(inst_.Matches(0x5A));
}

// Test Matches for a byte outside range
TEST_F(ProgInstTest_105, MatchesReturnsFalseForByteOutOfRange_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_FALSE(inst_.Matches(0x40));
  EXPECT_FALSE(inst_.Matches(0x5B));
}

// Test Matches with foldcase
TEST_F(ProgInstTest_105, MatchesWithFoldcase_105) {
  // 'a' to 'z' with foldcase
  inst_.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  // With foldcase, uppercase letters should also match if the range covers lowercase
  // The exact behavior depends on the implementation, but 'A' should match 'a'-'z' with foldcase
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

// Test Dump produces a non-empty string
TEST_F(ProgInstTest_105, DumpProducesNonEmptyString_105) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test hi() with various byte values
TEST_F(ProgInstTest_105, HiReturnsCorrectForVariousValues_105) {
  for (int hi = 0; hi <= 255; hi += 50) {
    inst_.InitByteRange(0, hi, 0, 0);
    EXPECT_EQ(inst_.hi(), hi);
  }
}

// Test copy constructor preserves hi value
TEST_F(ProgInstTest_105, CopyConstructorPreservesHi_105) {
  inst_.InitByteRange(0x10, 0x20, 0, 5);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.hi(), 0x20);
  EXPECT_EQ(copy.lo(), 0x10);
  EXPECT_EQ(copy.out(), 5);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
}

// Test assignment operator preserves hi value
TEST_F(ProgInstTest_105, AssignmentOperatorPreservesHi_105) {
  inst_.InitByteRange(0x30, 0x40, 1, 10);
  Prog::Inst other;
  other = inst_;
  EXPECT_EQ(other.hi(), 0x40);
  EXPECT_EQ(other.lo(), 0x30);
  EXPECT_EQ(other.foldcase(), 1);
}

// Test that Matches boundary: exactly at lo
TEST_F(ProgInstTest_105, MatchesAtLoBoundary_105) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x30));
  EXPECT_FALSE(inst_.Matches(0x2F));
}

// Test that Matches boundary: exactly at hi
TEST_F(ProgInstTest_105, MatchesAtHiBoundary_105) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x39));
  EXPECT_FALSE(inst_.Matches(0x3A));
}

// Test InitMatch with id 0
TEST_F(ProgInstTest_105, InitMatchWithIdZero_105) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test Dump for different instruction types
TEST_F(ProgInstTest_105, DumpForAlt_105) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_105, DumpForMatch_105) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_105, DumpForFail_105) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_105, DumpForNop_105) {
  inst_.InitNop(0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_105, DumpForCapture_105) {
  inst_.InitCapture(0, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_105, DumpForEmptyWidth_105) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

}  // namespace re2
