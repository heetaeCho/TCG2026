#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_107 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test InitByteRange and hint() accessor
TEST_F(ProgInstTest_107, HintAfterInitByteRange_107) {
  // InitByteRange sets up a kInstByteRange instruction
  // hint_foldcase_ stores hint in upper bits (>> 1) and foldcase in bit 0
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  // After InitByteRange with no hint set explicitly, hint should be 0
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.hint(), 0);
}

// Test hint with foldcase = 0
TEST_F(ProgInstTest_107, HintWithFoldcaseZero_107) {
  inst_.InitByteRange(0x61, 0x7A, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.hint(), 0);
}

// Test hint with foldcase = 1
TEST_F(ProgInstTest_107, HintWithFoldcaseOne_107) {
  inst_.InitByteRange(0x61, 0x7A, 1, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.hint(), 0);
}

// Test lo() accessor after InitByteRange
TEST_F(ProgInstTest_107, LoAfterInitByteRange_107) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x30);
}

// Test hi() accessor after InitByteRange
TEST_F(ProgInstTest_107, HiAfterInitByteRange_107) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);
  EXPECT_EQ(inst_.hi(), 0x39);
}

// Test out() accessor after InitByteRange
TEST_F(ProgInstTest_107, OutAfterInitByteRange_107) {
  inst_.InitByteRange(0x30, 0x39, 0, 42);
  EXPECT_EQ(inst_.out(), 42);
}

// Test opcode after InitByteRange
TEST_F(ProgInstTest_107, OpcodeAfterInitByteRange_107) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitAlt
TEST_F(ProgInstTest_107, InitAlt_107) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitCapture
TEST_F(ProgInstTest_107, InitCapture_107) {
  inst_.InitCapture(3, 15);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 15);
}

// Test InitEmptyWidth
TEST_F(ProgInstTest_107, InitEmptyWidth_107) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 5);
}

// Test InitMatch
TEST_F(ProgInstTest_107, InitMatch_107) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

// Test InitNop
TEST_F(ProgInstTest_107, InitNop_107) {
  inst_.InitNop(7);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitFail
TEST_F(ProgInstTest_107, InitFail_107) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test ByteRange with full byte range
TEST_F(ProgInstTest_107, ByteRangeFullRange_107) {
  inst_.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test ByteRange with single byte
TEST_F(ProgInstTest_107, ByteRangeSingleByte_107) {
  inst_.InitByteRange(0x41, 0x41, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x41);
}

// Test Matches on a ByteRange instruction
TEST_F(ProgInstTest_107, MatchesInRange_107) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_TRUE(inst_.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst_.Matches(0x4D));   // 'M' - middle
  EXPECT_TRUE(inst_.Matches(0x5A));   // 'Z'
  EXPECT_FALSE(inst_.Matches(0x40));  // before range
  EXPECT_FALSE(inst_.Matches(0x5B));  // after range
}

// Test Matches with foldcase
TEST_F(ProgInstTest_107, MatchesWithFoldcase_107) {
  // foldcase = 1 means case-insensitive matching for byte ranges
  inst_.InitByteRange(0x61, 0x7A, 1, 0);  // 'a'-'z' with foldcase
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  // With foldcase, uppercase letters should also match
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

// Test Matches out of range
TEST_F(ProgInstTest_107, MatchesOutOfRange_107) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);  // '0'-'9'
  EXPECT_FALSE(inst_.Matches(0x2F));
  EXPECT_FALSE(inst_.Matches(0x3A));
  EXPECT_TRUE(inst_.Matches(0x30));
  EXPECT_TRUE(inst_.Matches(0x39));
}

// Test Dump produces a non-empty string for various opcodes
TEST_F(ProgInstTest_107, DumpByteRange_107) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_107, DumpAlt_107) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_107, DumpMatch_107) {
  inst_.InitMatch(0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_107, DumpFail_107) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_107, DumpNop_107) {
  inst_.InitNop(0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor / assignment
TEST_F(ProgInstTest_107, CopyAssignment_107) {
  inst_.InitByteRange(0x41, 0x5A, 1, 10);
  Prog::Inst copy = inst_;
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.foldcase(), 1);
  EXPECT_EQ(copy.out(), 10);
  EXPECT_EQ(copy.hint(), inst_.hint());
}

// Test InitMatch with different match IDs
TEST_F(ProgInstTest_107, InitMatchVariousIds_107) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.match_id(), 0);

  inst_.InitMatch(100);
  EXPECT_EQ(inst_.match_id(), 100);
}

// Test InitCapture with cap = 0
TEST_F(ProgInstTest_107, InitCaptureZero_107) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 0);
}

// Test boundary: ByteRange with lo == hi == 0
TEST_F(ProgInstTest_107, ByteRangeZeroByte_107) {
  inst_.InitByteRange(0x00, 0x00, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0x00);
  EXPECT_TRUE(inst_.Matches(0x00));
  EXPECT_FALSE(inst_.Matches(0x01));
}

// Test boundary: ByteRange with lo == hi == 0xFF
TEST_F(ProgInstTest_107, ByteRangeMaxByte_107) {
  inst_.InitByteRange(0xFF, 0xFF, 0, 0);
  EXPECT_EQ(inst_.lo(), 0xFF);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_TRUE(inst_.Matches(0xFF));
  EXPECT_FALSE(inst_.Matches(0xFE));
}

// Test that re-initializing an Inst changes its opcode
TEST_F(ProgInstTest_107, ReinitializationChangesOpcode_107) {
  inst_.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);

  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);

  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

}  // namespace re2
