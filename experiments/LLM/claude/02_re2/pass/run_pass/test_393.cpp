#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"

namespace re2 {

class ProgInstTest_393 : public ::testing::Test {
 protected:
  Prog::Inst inst_;

  void SetUp() override {
    // Zero-initialize the instruction
    memset(&inst_, 0, sizeof(inst_));
  }
};

// Test InitEmptyWidth sets opcode to kInstEmptyWidth
TEST_F(ProgInstTest_393, InitEmptyWidth_SetsOpcode_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

// Test InitEmptyWidth sets the out value correctly
TEST_F(ProgInstTest_393, InitEmptyWidth_SetsOut_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 42);
  EXPECT_EQ(inst_.out(), 42);
}

// Test InitEmptyWidth sets the empty value correctly
TEST_F(ProgInstTest_393, InitEmptyWidth_SetsEmpty_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 10);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

// Test InitEmptyWidth with kEmptyEndLine
TEST_F(ProgInstTest_393, InitEmptyWidth_EndLine_393) {
  inst_.InitEmptyWidth(kEmptyEndLine, 20);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 20);
  EXPECT_EQ(inst_.empty(), kEmptyEndLine);
}

// Test InitEmptyWidth with kEmptyBeginText
TEST_F(ProgInstTest_393, InitEmptyWidth_BeginText_393) {
  inst_.InitEmptyWidth(kEmptyBeginText, 0);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.empty(), kEmptyBeginText);
}

// Test InitEmptyWidth with kEmptyEndText
TEST_F(ProgInstTest_393, InitEmptyWidth_EndText_393) {
  inst_.InitEmptyWidth(kEmptyEndText, 100);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 100);
  EXPECT_EQ(inst_.empty(), kEmptyEndText);
}

// Test InitEmptyWidth with kEmptyWordBoundary
TEST_F(ProgInstTest_393, InitEmptyWidth_WordBoundary_393) {
  inst_.InitEmptyWidth(kEmptyWordBoundary, 55);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 55);
  EXPECT_EQ(inst_.empty(), kEmptyWordBoundary);
}

// Test InitEmptyWidth with kEmptyNonWordBoundary
TEST_F(ProgInstTest_393, InitEmptyWidth_NonWordBoundary_393) {
  inst_.InitEmptyWidth(kEmptyNonWordBoundary, 77);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 77);
  EXPECT_EQ(inst_.empty(), kEmptyNonWordBoundary);
}

// Test InitEmptyWidth with out = 0 (boundary)
TEST_F(ProgInstTest_393, InitEmptyWidth_OutZero_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 0);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.out(), 0);
}

// Test InitAlt sets opcode and out values
TEST_F(ProgInstTest_393, InitAlt_SetsOpcodeAndOut_393) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitByteRange sets opcode and range
TEST_F(ProgInstTest_393, InitByteRange_SetsOpcodeAndRange_393) {
  inst_.InitByteRange('a', 'z', 0, 15);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 'a');
  EXPECT_EQ(inst_.hi(), 'z');
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 15);
}

// Test InitByteRange with foldcase
TEST_F(ProgInstTest_393, InitByteRange_WithFoldcase_393) {
  inst_.InitByteRange('A', 'Z', 1, 30);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 'A');
  EXPECT_EQ(inst_.hi(), 'Z');
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 30);
}

// Test InitCapture sets opcode and cap
TEST_F(ProgInstTest_393, InitCapture_SetsOpcodeAndCap_393) {
  inst_.InitCapture(3, 25);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 25);
}

// Test InitMatch sets opcode and match_id
TEST_F(ProgInstTest_393, InitMatch_SetsOpcodeAndMatchId_393) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

// Test InitNop sets opcode
TEST_F(ProgInstTest_393, InitNop_SetsOpcode_393) {
  inst_.InitNop(12);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 12);
}

// Test InitFail sets opcode
TEST_F(ProgInstTest_393, InitFail_SetsOpcode_393) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Dump returns non-empty string for EmptyWidth
TEST_F(ProgInstTest_393, Dump_EmptyWidth_ReturnsNonEmpty_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump returns non-empty string for Fail
TEST_F(ProgInstTest_393, Dump_Fail_ReturnsNonEmpty_393) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test InitByteRange with single byte range
TEST_F(ProgInstTest_393, InitByteRange_SingleByte_393) {
  inst_.InitByteRange(0x61, 0x61, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x61);
}

// Test InitByteRange with full byte range
TEST_F(ProgInstTest_393, InitByteRange_FullRange_393) {
  inst_.InitByteRange(0x00, 0xff, 0, 8);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xff);
  EXPECT_EQ(inst_.out(), 8);
}

// Test InitCapture with cap = 0
TEST_F(ProgInstTest_393, InitCapture_CapZero_393) {
  inst_.InitCapture(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 1);
}

// Test InitMatch with match_id = 0
TEST_F(ProgInstTest_393, InitMatch_MatchIdZero_393) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test combined EmptyOp flags
TEST_F(ProgInstTest_393, InitEmptyWidth_CombinedFlags_393) {
  EmptyOp combined = static_cast<EmptyOp>(kEmptyBeginLine | kEmptyEndLine);
  inst_.InitEmptyWidth(combined, 33);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), combined);
  EXPECT_EQ(inst_.out(), 33);
}

// Test Inst copy constructor preserves state
TEST_F(ProgInstTest_393, CopyConstructor_PreservesState_393) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 99);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstEmptyWidth);
  EXPECT_EQ(copy.out(), 99);
  EXPECT_EQ(copy.empty(), kEmptyBeginLine);
}

// Test Inst assignment operator preserves state
TEST_F(ProgInstTest_393, AssignmentOperator_PreservesState_393) {
  inst_.InitEmptyWidth(kEmptyEndText, 50);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstEmptyWidth);
  EXPECT_EQ(other.out(), 50);
  EXPECT_EQ(other.empty(), kEmptyEndText);
}

}  // namespace re2
