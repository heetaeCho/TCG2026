#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_103 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test InitCapture and cap() accessor
TEST_F(ProgInstTest_103, InitCaptureSetsCapValue_103) {
  inst_.InitCapture(5, 10);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 5);
  EXPECT_EQ(inst_.out(), 10);
}

TEST_F(ProgInstTest_103, InitCaptureWithZeroCap_103) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 0);
}

TEST_F(ProgInstTest_103, InitCaptureWithLargeCap_103) {
  inst_.InitCapture(1000, 500);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 1000);
  EXPECT_EQ(inst_.out(), 500);
}

// Test InitAlt
TEST_F(ProgInstTest_103, InitAltSetsOpcode_103) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 1);
  EXPECT_EQ(inst_.out1(), 2);
}

TEST_F(ProgInstTest_103, InitAltWithZeroOutputs_103) {
  inst_.InitAlt(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.out1(), 0);
}

// Test InitByteRange
TEST_F(ProgInstTest_103, InitByteRangeSetsValues_103) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x5A);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 10);
}

TEST_F(ProgInstTest_103, InitByteRangeWithFoldcase_103) {
  inst_.InitByteRange(0x61, 0x7A, 1, 20);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x7A);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 20);
}

TEST_F(ProgInstTest_103, InitByteRangeSingleByte_103) {
  inst_.InitByteRange(0x00, 0x00, 0, 1);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0x00);
  EXPECT_EQ(inst_.out(), 1);
}

TEST_F(ProgInstTest_103, InitByteRangeFullRange_103) {
  inst_.InitByteRange(0x00, 0xFF, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test InitEmptyWidth
TEST_F(ProgInstTest_103, InitEmptyWidthSetsValues_103) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 3);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst_.out(), 3);
}

TEST_F(ProgInstTest_103, InitEmptyWidthEndLine_103) {
  inst_.InitEmptyWidth(kEmptyEndLine, 7);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyEndLine);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitMatch
TEST_F(ProgInstTest_103, InitMatchSetsValues_103) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

TEST_F(ProgInstTest_103, InitMatchWithZeroId_103) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

TEST_F(ProgInstTest_103, InitMatchWithLargeId_103) {
  inst_.InitMatch(999);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 999);
}

// Test InitNop
TEST_F(ProgInstTest_103, InitNopSetsOpcode_103) {
  inst_.InitNop(15);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 15);
}

TEST_F(ProgInstTest_103, InitNopWithZeroOut_103) {
  inst_.InitNop(0);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 0);
}

// Test InitFail
TEST_F(ProgInstTest_103, InitFailSetsOpcode_103) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Dump returns non-empty string for various opcodes
TEST_F(ProgInstTest_103, DumpCapture_103) {
  inst_.InitCapture(3, 7);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpAlt_103) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpByteRange_103) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpMatch_103) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpNop_103) {
  inst_.InitNop(5);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpFail_103) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_103, DumpEmptyWidth_103) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 3);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Matches for ByteRange
TEST_F(ProgInstTest_103, MatchesByteInRange_103) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);  // A-Z
  EXPECT_TRUE(inst_.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst_.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst_.Matches(0x5A));   // 'Z'
}

TEST_F(ProgInstTest_103, MatchesByteOutOfRange_103) {
  inst_.InitByteRange(0x41, 0x5A, 0, 10);  // A-Z
  EXPECT_FALSE(inst_.Matches(0x40));  // '@'
  EXPECT_FALSE(inst_.Matches(0x5B));  // '['
  EXPECT_FALSE(inst_.Matches(0x61));  // 'a'
}

TEST_F(ProgInstTest_103, MatchesSingleByte_103) {
  inst_.InitByteRange(0x41, 0x41, 0, 10);  // exactly 'A'
  EXPECT_TRUE(inst_.Matches(0x41));
  EXPECT_FALSE(inst_.Matches(0x42));
  EXPECT_FALSE(inst_.Matches(0x40));
}

TEST_F(ProgInstTest_103, MatchesWithFoldcase_103) {
  inst_.InitByteRange('a', 'z', 1, 10);
  // With foldcase, uppercase should also match
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

// Test copy constructor and assignment
TEST_F(ProgInstTest_103, CopyConstructor_103) {
  inst_.InitCapture(42, 99);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstCapture);
  EXPECT_EQ(copy.cap(), 42);
  EXPECT_EQ(copy.out(), 99);
}

TEST_F(ProgInstTest_103, AssignmentOperator_103) {
  inst_.InitMatch(77);
  Prog::Inst other;
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 77);
}

// Test overwriting an instruction with a different type
TEST_F(ProgInstTest_103, ReinitializeDifferentType_103) {
  inst_.InitCapture(5, 10);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 5);

  inst_.InitMatch(3);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 3);
}

// Test enum values
TEST_F(ProgInstTest_103, InstOpEnumValues_103) {
  EXPECT_EQ(kInstAlt, 0);
  EXPECT_EQ(kInstAltMatch, 1);
  EXPECT_EQ(kInstByteRange, 2);
  EXPECT_EQ(kInstCapture, 3);
  EXPECT_EQ(kInstEmptyWidth, 4);
  EXPECT_EQ(kInstMatch, 5);
  EXPECT_EQ(kInstNop, 6);
  EXPECT_EQ(kInstFail, 7);
  EXPECT_EQ(kNumInst, 8);
}

}  // namespace re2
