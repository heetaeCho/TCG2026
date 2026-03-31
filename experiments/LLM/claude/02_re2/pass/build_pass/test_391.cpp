#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstTest_391 : public ::testing::Test {
 protected:
  Prog::Inst inst_;

  void SetUp() override {
    // Zero-initialize the instruction
    memset(&inst_, 0, sizeof(inst_));
  }
};

// Test InitByteRange with normal ASCII range
TEST_F(ProgInstTest_391, InitByteRange_NormalRange_391) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x5A);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange with foldcase enabled
TEST_F(ProgInstTest_391, InitByteRange_WithFoldcase_391) {
  inst_.InitByteRange(0x61, 0x7A, 1, 20);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x7A);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 20);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange with single byte range (lo == hi)
TEST_F(ProgInstTest_391, InitByteRange_SingleByte_391) {
  inst_.InitByteRange(0x42, 0x42, 0, 5);
  EXPECT_EQ(inst_.lo(), 0x42);
  EXPECT_EQ(inst_.hi(), 0x42);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange with boundary values (0x00 to 0xFF)
TEST_F(ProgInstTest_391, InitByteRange_FullRange_391) {
  inst_.InitByteRange(0x00, 0xFF, 0, 100);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 100);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange lo boundary = 0
TEST_F(ProgInstTest_391, InitByteRange_LoZero_391) {
  inst_.InitByteRange(0, 0x10, 0, 7);
  EXPECT_EQ(inst_.lo(), 0);
  EXPECT_EQ(inst_.hi(), 0x10);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitByteRange hi boundary = 0xFF
TEST_F(ProgInstTest_391, InitByteRange_HiMax_391) {
  inst_.InitByteRange(0xF0, 0xFF, 1, 15);
  EXPECT_EQ(inst_.lo(), 0xF0);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 15);
}

// Test InitByteRange with out = 0
TEST_F(ProgInstTest_391, InitByteRange_OutZero_391) {
  inst_.InitByteRange(0x30, 0x39, 0, 0);
  EXPECT_EQ(inst_.lo(), 0x30);
  EXPECT_EQ(inst_.hi(), 0x39);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test that foldcase only uses bit 0 (passing value > 1)
TEST_F(ProgInstTest_391, InitByteRange_FoldcaseMasked_391) {
  inst_.InitByteRange(0x41, 0x5A, 3, 10);
  // foldcase should be 3 & 1 = 1
  EXPECT_EQ(inst_.foldcase(), 1);
}

// Test that foldcase with even value > 0 gives 0
TEST_F(ProgInstTest_391, InitByteRange_FoldcaseEvenValue_391) {
  inst_.InitByteRange(0x41, 0x5A, 2, 10);
  // foldcase should be 2 & 1 = 0
  EXPECT_EQ(inst_.foldcase(), 0);
}

// Test lo and hi are masked to 0xFF
TEST_F(ProgInstTest_391, InitByteRange_LoHiMasked_391) {
  inst_.InitByteRange(0x141, 0x2FF, 0, 50);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test Matches for a byte within range
TEST_F(ProgInstTest_391, InitByteRange_MatchesInRange_391) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_TRUE(inst_.Matches(0x41));   // lo boundary
  EXPECT_TRUE(inst_.Matches(0x5A));   // hi boundary
  EXPECT_TRUE(inst_.Matches(0x4D));   // middle
}

// Test Matches for a byte outside range
TEST_F(ProgInstTest_391, InitByteRange_MatchesOutOfRange_391) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_FALSE(inst_.Matches(0x40));  // just below lo
  EXPECT_FALSE(inst_.Matches(0x5B));  // just above hi
  EXPECT_FALSE(inst_.Matches(0x00));  // far below
  EXPECT_FALSE(inst_.Matches(0xFF));  // far above
}

// Test InitAlt sets opcode and outputs
TEST_F(ProgInstTest_391, InitAlt_Normal_391) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitCapture
TEST_F(ProgInstTest_391, InitCapture_Normal_391) {
  inst_.InitCapture(3, 42);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 42);
}

// Test InitMatch
TEST_F(ProgInstTest_391, InitMatch_Normal_391) {
  inst_.InitMatch(7);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 7);
}

// Test InitNop
TEST_F(ProgInstTest_391, InitNop_Normal_391) {
  inst_.InitNop(99);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 99);
}

// Test InitFail
TEST_F(ProgInstTest_391, InitFail_Normal_391) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test InitEmptyWidth
TEST_F(ProgInstTest_391, InitEmptyWidth_Normal_391) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 55);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 55);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

// Test Dump doesn't crash (smoke test)
TEST_F(ProgInstTest_391, InitByteRange_Dump_391) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test InitMatch with id = 0
TEST_F(ProgInstTest_391, InitMatch_ZeroId_391) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test InitCapture with cap = 0
TEST_F(ProgInstTest_391, InitCapture_ZeroCap_391) {
  inst_.InitCapture(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 1);
}

// Test copy constructor preserves state
TEST_F(ProgInstTest_391, CopyConstructor_391) {
  inst_.InitByteRange(0x41, 0x5A, 1, 10);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.foldcase(), 1);
  EXPECT_EQ(copy.out(), 10);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
}

// Test assignment operator preserves state
TEST_F(ProgInstTest_391, AssignmentOperator_391) {
  inst_.InitByteRange(0x41, 0x5A, 1, 10);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other = inst_;
  EXPECT_EQ(other.lo(), 0x41);
  EXPECT_EQ(other.hi(), 0x5A);
  EXPECT_EQ(other.foldcase(), 1);
  EXPECT_EQ(other.out(), 10);
  EXPECT_EQ(other.opcode(), kInstByteRange);
}

// Test Matches with foldcase enabled - lowercase should match uppercase range
TEST_F(ProgInstTest_391, InitByteRange_MatchesWithFoldcase_391) {
  inst_.InitByteRange('a', 'z', 1, 10);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_TRUE(inst_.Matches('m'));
  // With foldcase, uppercase letters should also match
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

}  // namespace re2
