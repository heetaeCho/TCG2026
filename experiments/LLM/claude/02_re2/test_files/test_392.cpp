#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstTest_392 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
  
  void SetUp() override {
    // Zero-initialize the instruction to ensure clean state
    memset(&inst_, 0, sizeof(inst_));
  }
};

// Test InitCapture sets opcode to kInstCapture
TEST_F(ProgInstTest_392, InitCaptureSetsOpcode_392) {
  inst_.InitCapture(3, 10);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test InitCapture sets cap value correctly
TEST_F(ProgInstTest_392, InitCaptureSetsCapValue_392) {
  inst_.InitCapture(5, 10);
  EXPECT_EQ(inst_.cap(), 5);
}

// Test InitCapture sets out value correctly
TEST_F(ProgInstTest_392, InitCaptureSetsOutValue_392) {
  inst_.InitCapture(3, 42);
  EXPECT_EQ(inst_.out(), 42);
}

// Test InitCapture with cap = 0
TEST_F(ProgInstTest_392, InitCaptureWithZeroCap_392) {
  inst_.InitCapture(0, 10);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.out(), 10);
}

// Test InitCapture with out = 0
TEST_F(ProgInstTest_392, InitCaptureWithZeroOut_392) {
  inst_.InitCapture(7, 0);
  EXPECT_EQ(inst_.cap(), 7);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.out(), 0);
}

// Test InitCapture with large cap value
TEST_F(ProgInstTest_392, InitCaptureWithLargeCap_392) {
  inst_.InitCapture(1000, 500);
  EXPECT_EQ(inst_.cap(), 1000);
  EXPECT_EQ(inst_.out(), 500);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

// Test InitAlt sets opcode to kInstAlt
TEST_F(ProgInstTest_392, InitAltSetsOpcode_392) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

// Test InitAlt sets out and out1 correctly
TEST_F(ProgInstTest_392, InitAltSetsOutValues_392) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitByteRange sets opcode to kInstByteRange
TEST_F(ProgInstTest_392, InitByteRangeSetsOpcode_392) {
  inst_.InitByteRange(0x61, 0x7a, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange sets lo and hi correctly
TEST_F(ProgInstTest_392, InitByteRangeSetsLoHi_392) {
  inst_.InitByteRange(0x41, 0x5a, 0, 5);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x5a);
}

// Test InitByteRange sets foldcase
TEST_F(ProgInstTest_392, InitByteRangeSetsFoldcase_392) {
  inst_.InitByteRange(0x61, 0x7a, 1, 5);
  EXPECT_EQ(inst_.foldcase(), 1);
}

// Test InitByteRange sets out correctly
TEST_F(ProgInstTest_392, InitByteRangeSetsOut_392) {
  inst_.InitByteRange(0x61, 0x7a, 0, 15);
  EXPECT_EQ(inst_.out(), 15);
}

// Test InitEmptyWidth sets opcode to kInstEmptyWidth
TEST_F(ProgInstTest_392, InitEmptyWidthSetsOpcode_392) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

// Test InitEmptyWidth sets empty value
TEST_F(ProgInstTest_392, InitEmptyWidthSetsEmpty_392) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

// Test InitEmptyWidth sets out correctly
TEST_F(ProgInstTest_392, InitEmptyWidthSetsOut_392) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 99);
  EXPECT_EQ(inst_.out(), 99);
}

// Test InitMatch sets opcode to kInstMatch
TEST_F(ProgInstTest_392, InitMatchSetsOpcode_392) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test InitMatch sets match_id correctly
TEST_F(ProgInstTest_392, InitMatchSetsMatchId_392) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test InitMatch with match id 0
TEST_F(ProgInstTest_392, InitMatchWithZeroId_392) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.match_id(), 0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test InitNop sets opcode to kInstNop
TEST_F(ProgInstTest_392, InitNopSetsOpcode_392) {
  inst_.InitNop(10);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitNop sets out correctly
TEST_F(ProgInstTest_392, InitNopSetsOut_392) {
  inst_.InitNop(25);
  EXPECT_EQ(inst_.out(), 25);
}

// Test InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_392, InitFailSetsOpcode_392) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Dump returns a non-empty string for a valid instruction
TEST_F(ProgInstTest_392, DumpReturnsNonEmpty_392) {
  inst_.InitCapture(1, 5);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitMatch
TEST_F(ProgInstTest_392, DumpForMatch_392) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitFail
TEST_F(ProgInstTest_392, DumpForFail_392) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitNop
TEST_F(ProgInstTest_392, DumpForNop_392) {
  inst_.InitNop(3);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor works
TEST_F(ProgInstTest_392, CopyConstructor_392) {
  inst_.InitCapture(7, 15);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstCapture);
  EXPECT_EQ(copy.cap(), 7);
  EXPECT_EQ(copy.out(), 15);
}

// Test copy assignment works
TEST_F(ProgInstTest_392, CopyAssignment_392) {
  inst_.InitCapture(3, 10);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstCapture);
  EXPECT_EQ(other.cap(), 3);
  EXPECT_EQ(other.out(), 10);
}

// Test InitByteRange with single byte range
TEST_F(ProgInstTest_392, InitByteRangeSingleByte_392) {
  inst_.InitByteRange(0x41, 0x41, 0, 3);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x41);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test InitByteRange full byte range
TEST_F(ProgInstTest_392, InitByteRangeFullRange_392) {
  inst_.InitByteRange(0x00, 0xFF, 0, 3);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test Matches for byte range instruction
TEST_F(ProgInstTest_392, MatchesInRange_392) {
  inst_.InitByteRange(0x41, 0x5a, 0, 3);
  EXPECT_TRUE(inst_.Matches(0x41));  // 'A'
  EXPECT_TRUE(inst_.Matches(0x5a));  // 'Z'
  EXPECT_TRUE(inst_.Matches(0x4d));  // 'M' - middle of range
}

// Test Matches outside byte range
TEST_F(ProgInstTest_392, MatchesOutOfRange_392) {
  inst_.InitByteRange(0x41, 0x5a, 0, 3);
  EXPECT_FALSE(inst_.Matches(0x40));  // '@' - just below
  EXPECT_FALSE(inst_.Matches(0x5b));  // '[' - just above
  EXPECT_FALSE(inst_.Matches(0x61));  // 'a'
}

// Test InitAlt with both outputs zero
TEST_F(ProgInstTest_392, InitAltWithZeroOutputs_392) {
  inst_.InitAlt(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.out1(), 0);
}

// Test InitCapture with negative cap value
TEST_F(ProgInstTest_392, InitCaptureWithNegativeCap_392) {
  inst_.InitCapture(-1, 10);
  EXPECT_EQ(inst_.cap(), -1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

}  // namespace re2
