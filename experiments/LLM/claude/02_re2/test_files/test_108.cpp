#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_108 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test that InitMatch sets the opcode to kInstMatch and stores the match id
TEST_F(ProgInstTest_108, InitMatchSetsMatchId_108) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test match_id with zero
TEST_F(ProgInstTest_108, InitMatchWithZeroId_108) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test match_id with a large positive value
TEST_F(ProgInstTest_108, InitMatchWithLargeId_108) {
  inst_.InitMatch(999999);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 999999);
}

// Test match_id with value 1 (common single match)
TEST_F(ProgInstTest_108, InitMatchWithIdOne_108) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

// Test that InitAlt sets the opcode to kInstAlt
TEST_F(ProgInstTest_108, InitAltSetsOpcode_108) {
  inst_.InitAlt(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

// Test that InitAlt stores out and out1
TEST_F(ProgInstTest_108, InitAltSetsOutAndOut1_108) {
  inst_.InitAlt(5, 10);
  EXPECT_EQ(inst_.out(), 5);
  EXPECT_EQ(inst_.out1(), 10);
}

// Test that InitByteRange sets the opcode to kInstByteRange
TEST_F(ProgInstTest_108, InitByteRangeSetsOpcode_108) {
  inst_.InitByteRange(0x41, 0x5A, 0, 3);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test that InitByteRange stores lo, hi, foldcase, and out
TEST_F(ProgInstTest_108, InitByteRangeStoresFields_108) {
  inst_.InitByteRange(0x61, 0x7A, 1, 7);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x7A);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitByteRange with single character range
TEST_F(ProgInstTest_108, InitByteRangeSingleChar_108) {
  inst_.InitByteRange(0x41, 0x41, 0, 2);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x41);
}

// Test that InitCapture sets the opcode to kInstCapture
TEST_F(ProgInstTest_108, InitCaptureSetsOpcode_108) {
  inst_.InitCapture(2, 5);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test that InitCapture stores cap and out
TEST_F(ProgInstTest_108, InitCaptureStoresFields_108) {
  inst_.InitCapture(4, 8);
  EXPECT_EQ(inst_.cap(), 4);
  EXPECT_EQ(inst_.out(), 8);
}

// Test that InitEmptyWidth sets the opcode to kInstEmptyWidth
TEST_F(ProgInstTest_108, InitEmptyWidthSetsOpcode_108) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 3);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

// Test that InitEmptyWidth stores empty and out
TEST_F(ProgInstTest_108, InitEmptyWidthStoresFields_108) {
  inst_.InitEmptyWidth(kEmptyEndLine, 6);
  EXPECT_EQ(inst_.empty(), kEmptyEndLine);
  EXPECT_EQ(inst_.out(), 6);
}

// Test that InitNop sets the opcode to kInstNop
TEST_F(ProgInstTest_108, InitNopSetsOpcode_108) {
  inst_.InitNop(4);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test that InitNop stores out
TEST_F(ProgInstTest_108, InitNopStoresOut_108) {
  inst_.InitNop(12);
  EXPECT_EQ(inst_.out(), 12);
}

// Test that InitFail sets the opcode to kInstFail
TEST_F(ProgInstTest_108, InitFailSetsOpcode_108) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test that Dump returns a non-empty string for various instruction types
TEST_F(ProgInstTest_108, DumpMatchReturnsNonEmpty_108) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpAltReturnsNonEmpty_108) {
  inst_.InitAlt(0, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpByteRangeReturnsNonEmpty_108) {
  inst_.InitByteRange(0x61, 0x7A, 0, 3);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpCaptureReturnsNonEmpty_108) {
  inst_.InitCapture(0, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpEmptyWidthReturnsNonEmpty_108) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpNopReturnsNonEmpty_108) {
  inst_.InitNop(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_108, DumpFailReturnsNonEmpty_108) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Matches on a ByteRange instruction
TEST_F(ProgInstTest_108, ByteRangeMatchesInRange_108) {
  inst_.InitByteRange(0x41, 0x5A, 0, 3);  // A-Z
  EXPECT_TRUE(inst_.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst_.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst_.Matches(0x5A));   // 'Z'
}

TEST_F(ProgInstTest_108, ByteRangeDoesNotMatchOutOfRange_108) {
  inst_.InitByteRange(0x41, 0x5A, 0, 3);  // A-Z
  EXPECT_FALSE(inst_.Matches(0x40));  // '@'
  EXPECT_FALSE(inst_.Matches(0x5B));  // '['
  EXPECT_FALSE(inst_.Matches(0x61));  // 'a'
}

// Test Matches with foldcase
TEST_F(ProgInstTest_108, ByteRangeMatchesWithFoldcase_108) {
  inst_.InitByteRange(0x61, 0x7A, 1, 3);  // a-z with foldcase
  EXPECT_TRUE(inst_.Matches(0x61));   // 'a'
  EXPECT_TRUE(inst_.Matches(0x7A));   // 'z'
}

// Test copy semantics
TEST_F(ProgInstTest_108, CopyConstructor_108) {
  inst_.InitMatch(77);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstMatch);
  EXPECT_EQ(copy.match_id(), 77);
}

TEST_F(ProgInstTest_108, CopyAssignment_108) {
  inst_.InitMatch(88);
  Prog::Inst other;
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 88);
}

// Test reinitializing an instruction to a different type
TEST_F(ProgInstTest_108, ReinitializeToDifferentType_108) {
  inst_.InitMatch(5);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 5);

  inst_.InitNop(10);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 10);
}

// Test boundary: InitByteRange with full byte range
TEST_F(ProgInstTest_108, ByteRangeFullRange_108) {
  inst_.InitByteRange(0x00, 0xFF, 0, 1);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_TRUE(inst_.Matches(0x00));
  EXPECT_TRUE(inst_.Matches(0xFF));
  EXPECT_TRUE(inst_.Matches(0x80));
}

// Test InitCapture with cap=0
TEST_F(ProgInstTest_108, InitCaptureWithZeroCap_108) {
  inst_.InitCapture(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 1);
}

// Test InitAlt with same out and out1
TEST_F(ProgInstTest_108, InitAltSameOutValues_108) {
  inst_.InitAlt(3, 3);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 3);
  EXPECT_EQ(inst_.out1(), 3);
}

}  // namespace re2
