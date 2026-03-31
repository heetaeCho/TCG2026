#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstDumpTest_397 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

TEST_F(ProgInstDumpTest_397, DumpAlt_397) {
  inst_.InitAlt(10, 20);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "alt -> 10 | 20");
}

TEST_F(ProgInstDumpTest_397, DumpAltZeroOutputs_397) {
  inst_.InitAlt(0, 0);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "alt -> 0 | 0");
}

TEST_F(ProgInstDumpTest_397, DumpByteRange_397) {
  inst_.InitByteRange(0x41, 0x5A, 0, 5);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "byte [41-5a] 0 -> 5");
}

TEST_F(ProgInstDumpTest_397, DumpByteRangeWithFoldcase_397) {
  inst_.InitByteRange(0x61, 0x7A, 1, 8);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "byte/i [61-7a] 0 -> 8");
}

TEST_F(ProgInstDumpTest_397, DumpByteRangeSingleByte_397) {
  inst_.InitByteRange(0x00, 0x00, 0, 3);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "byte [00-00] 0 -> 3");
}

TEST_F(ProgInstDumpTest_397, DumpByteRangeFullRange_397) {
  inst_.InitByteRange(0x00, 0xFF, 0, 1);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "byte [00-ff] 0 -> 1");
}

TEST_F(ProgInstDumpTest_397, DumpCapture_397) {
  inst_.InitCapture(3, 7);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "capture 3 -> 7");
}

TEST_F(ProgInstDumpTest_397, DumpCaptureZero_397) {
  inst_.InitCapture(0, 0);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "capture 0 -> 0");
}

TEST_F(ProgInstDumpTest_397, DumpEmptyWidth_397) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 4);
  std::string result = inst_.Dump();
  // kEmptyBeginLine is typically 0x01
  std::string expected = "emptywidth 0x1 -> 4";
  EXPECT_EQ(result, expected);
}

TEST_F(ProgInstDumpTest_397, DumpEmptyWidthMultipleFlags_397) {
  // kEmptyBeginLine | kEmptyEndLine = 0x01 | 0x02 = 0x03
  inst_.InitEmptyWidth(static_cast<EmptyOp>(kEmptyBeginLine | kEmptyEndLine), 9);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "emptywidth 0x3 -> 9");
}

TEST_F(ProgInstDumpTest_397, DumpMatch_397) {
  inst_.InitMatch(1);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "match! 1");
}

TEST_F(ProgInstDumpTest_397, DumpMatchZero_397) {
  inst_.InitMatch(0);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "match! 0");
}

TEST_F(ProgInstDumpTest_397, DumpMatchLargeId_397) {
  inst_.InitMatch(999);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "match! 999");
}

TEST_F(ProgInstDumpTest_397, DumpNop_397) {
  inst_.InitNop(12);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "nop -> 12");
}

TEST_F(ProgInstDumpTest_397, DumpNopZeroOut_397) {
  inst_.InitNop(0);
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "nop -> 0");
}

TEST_F(ProgInstDumpTest_397, DumpFail_397) {
  inst_.InitFail();
  std::string result = inst_.Dump();
  EXPECT_EQ(result, "fail");
}

// Test opcode accessor after initialization
TEST_F(ProgInstDumpTest_397, OpcodeAlt_397) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

TEST_F(ProgInstDumpTest_397, OpcodeByteRange_397) {
  inst_.InitByteRange(0x41, 0x5A, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

TEST_F(ProgInstDumpTest_397, OpcodeCapture_397) {
  inst_.InitCapture(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

TEST_F(ProgInstDumpTest_397, OpcodeEmptyWidth_397) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 1);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

TEST_F(ProgInstDumpTest_397, OpcodeMatch_397) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

TEST_F(ProgInstDumpTest_397, OpcodeNop_397) {
  inst_.InitNop(1);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

TEST_F(ProgInstDumpTest_397, OpcodeFail_397) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test out() accessor
TEST_F(ProgInstDumpTest_397, OutAlt_397) {
  inst_.InitAlt(42, 99);
  EXPECT_EQ(inst_.out(), 42);
}

TEST_F(ProgInstDumpTest_397, Out1Alt_397) {
  inst_.InitAlt(42, 99);
  EXPECT_EQ(inst_.out1(), 99);
}

TEST_F(ProgInstDumpTest_397, OutByteRange_397) {
  inst_.InitByteRange(0x30, 0x39, 0, 15);
  EXPECT_EQ(inst_.out(), 15);
}

TEST_F(ProgInstDumpTest_397, LoHiByteRange_397) {
  inst_.InitByteRange(0x30, 0x39, 0, 15);
  EXPECT_EQ(inst_.lo(), 0x30);
  EXPECT_EQ(inst_.hi(), 0x39);
}

TEST_F(ProgInstDumpTest_397, FoldcaseByteRange_397) {
  inst_.InitByteRange(0x61, 0x7A, 1, 8);
  EXPECT_EQ(inst_.foldcase(), 1);
}

TEST_F(ProgInstDumpTest_397, NoFoldcaseByteRange_397) {
  inst_.InitByteRange(0x61, 0x7A, 0, 8);
  EXPECT_EQ(inst_.foldcase(), 0);
}

TEST_F(ProgInstDumpTest_397, CapCapture_397) {
  inst_.InitCapture(5, 10);
  EXPECT_EQ(inst_.cap(), 5);
  EXPECT_EQ(inst_.out(), 10);
}

TEST_F(ProgInstDumpTest_397, MatchId_397) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

TEST_F(ProgInstDumpTest_397, OutNop_397) {
  inst_.InitNop(77);
  EXPECT_EQ(inst_.out(), 77);
}

// Test copy constructor / assignment
TEST_F(ProgInstDumpTest_397, CopyConstruct_397) {
  inst_.InitMatch(7);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.Dump(), "match! 7");
  EXPECT_EQ(copy.opcode(), kInstMatch);
  EXPECT_EQ(copy.match_id(), 7);
}

TEST_F(ProgInstDumpTest_397, CopyAssignment_397) {
  inst_.InitNop(33);
  Prog::Inst other;
  other.InitFail();
  other = inst_;
  EXPECT_EQ(other.Dump(), "nop -> 33");
  EXPECT_EQ(other.opcode(), kInstNop);
  EXPECT_EQ(other.out(), 33);
}

}  // namespace re2
