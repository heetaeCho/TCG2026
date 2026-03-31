#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compiler.h"

namespace re2 {

class ProgInstTest_109 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test InitEmptyWidth and empty() accessor
TEST_F(ProgInstTest_109, InitEmptyWidthSetsEmpty_109) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 0);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
}

TEST_F(ProgInstTest_109, InitEmptyWidthEndLine_109) {
  inst_.InitEmptyWidth(kEmptyEndLine, 5);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyEndLine);
  EXPECT_EQ(inst_.out(), 5);
}

TEST_F(ProgInstTest_109, InitEmptyWidthBeginText_109) {
  inst_.InitEmptyWidth(kEmptyBeginText, 10);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginText);
  EXPECT_EQ(inst_.out(), 10);
}

TEST_F(ProgInstTest_109, InitEmptyWidthEndText_109) {
  inst_.InitEmptyWidth(kEmptyEndText, 3);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyEndText);
}

TEST_F(ProgInstTest_109, InitEmptyWidthWordBoundary_109) {
  inst_.InitEmptyWidth(kEmptyWordBoundary, 0);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyWordBoundary);
}

TEST_F(ProgInstTest_109, InitEmptyWidthNonWordBoundary_109) {
  inst_.InitEmptyWidth(kEmptyNonWordBoundary, 7);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyNonWordBoundary);
}

TEST_F(ProgInstTest_109, InitEmptyWidthCombinedFlags_109) {
  EmptyOp combined = static_cast<EmptyOp>(kEmptyBeginLine | kEmptyEndLine);
  inst_.InitEmptyWidth(combined, 2);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), combined);
}

// Test InitAlt
TEST_F(ProgInstTest_109, InitAltSetsOpcode_109) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 1);
  EXPECT_EQ(inst_.out1(), 2);
}

// Test InitByteRange
TEST_F(ProgInstTest_109, InitByteRangeSetsFields_109) {
  inst_.InitByteRange(0x41, 0x5A, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x41);
  EXPECT_EQ(inst_.hi(), 0x5A);
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 5);
}

TEST_F(ProgInstTest_109, InitByteRangeWithFoldcase_109) {
  inst_.InitByteRange(0x61, 0x7A, 1, 10);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x61);
  EXPECT_EQ(inst_.hi(), 0x7A);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 10);
}

TEST_F(ProgInstTest_109, InitByteRangeSingleByte_109) {
  inst_.InitByteRange(0x00, 0x00, 0, 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0x00);
}

TEST_F(ProgInstTest_109, InitByteRangeFullRange_109) {
  inst_.InitByteRange(0x00, 0xFF, 0, 1);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
}

// Test InitCapture
TEST_F(ProgInstTest_109, InitCaptureSetsFields_109) {
  inst_.InitCapture(3, 7);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 7);
}

TEST_F(ProgInstTest_109, InitCaptureZero_109) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 0);
}

// Test InitMatch
TEST_F(ProgInstTest_109, InitMatchSetsFields_109) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

TEST_F(ProgInstTest_109, InitMatchZeroId_109) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 0);
}

// Test InitNop
TEST_F(ProgInstTest_109, InitNopSetsFields_109) {
  inst_.InitNop(4);
  EXPECT_EQ(inst_.opcode(), kInstNop);
  EXPECT_EQ(inst_.out(), 4);
}

// Test InitFail
TEST_F(ProgInstTest_109, InitFailSetsOpcode_109) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test Matches for byte range
TEST_F(ProgInstTest_109, ByteRangeMatchesInRange_109) {
  inst_.InitByteRange('a', 'z', 0, 1);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('m'));
  EXPECT_TRUE(inst_.Matches('z'));
}

TEST_F(ProgInstTest_109, ByteRangeDoesNotMatchOutOfRange_109) {
  inst_.InitByteRange('a', 'z', 0, 1);
  EXPECT_FALSE(inst_.Matches('A'));
  EXPECT_FALSE(inst_.Matches('0'));
  EXPECT_FALSE(inst_.Matches('{'));  // one past 'z'
}

TEST_F(ProgInstTest_109, ByteRangeMatchesBoundary_109) {
  inst_.InitByteRange(0x00, 0xFF, 0, 1);
  EXPECT_TRUE(inst_.Matches(0x00));
  EXPECT_TRUE(inst_.Matches(0xFF));
  EXPECT_TRUE(inst_.Matches(0x80));
}

TEST_F(ProgInstTest_109, ByteRangeMatchesSingleByte_109) {
  inst_.InitByteRange('x', 'x', 0, 1);
  EXPECT_TRUE(inst_.Matches('x'));
  EXPECT_FALSE(inst_.Matches('w'));
  EXPECT_FALSE(inst_.Matches('y'));
}

TEST_F(ProgInstTest_109, ByteRangeMatchesWithFoldcase_109) {
  inst_.InitByteRange('a', 'z', 1, 1);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  // With foldcase, uppercase letters should match lowercase range
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
}

// Test Dump produces non-empty strings
TEST_F(ProgInstTest_109, DumpAlt_109) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpByteRange_109) {
  inst_.InitByteRange('a', 'z', 0, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpCapture_109) {
  inst_.InitCapture(0, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpEmptyWidth_109) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpMatch_109) {
  inst_.InitMatch(0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpNop_109) {
  inst_.InitNop(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_109, DumpFail_109) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test that overwriting an instruction with different type works
TEST_F(ProgInstTest_109, OverwriteWithDifferentType_109) {
  inst_.InitNop(1);
  EXPECT_EQ(inst_.opcode(), kInstNop);

  inst_.InitEmptyWidth(kEmptyBeginText, 2);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginText);
}

// Test EmptyOp with all flags combined
TEST_F(ProgInstTest_109, InitEmptyWidthAllFlags_109) {
  EmptyOp all = static_cast<EmptyOp>(
      kEmptyBeginLine | kEmptyEndLine | kEmptyBeginText |
      kEmptyEndText | kEmptyWordBoundary | kEmptyNonWordBoundary);
  inst_.InitEmptyWidth(all, 0);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), all);
}

// Test copy semantics
TEST_F(ProgInstTest_109, CopyConstructor_109) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstEmptyWidth);
  EXPECT_EQ(copy.empty(), kEmptyBeginLine);
  EXPECT_EQ(copy.out(), 5);
}

TEST_F(ProgInstTest_109, AssignmentOperator_109) {
  inst_.InitEmptyWidth(kEmptyEndText, 3);
  Prog::Inst other;
  other.InitFail();
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstEmptyWidth);
  EXPECT_EQ(other.empty(), kEmptyEndText);
  EXPECT_EQ(other.out(), 3);
}

// Test out() for various instruction types
TEST_F(ProgInstTest_109, OutForNop_109) {
  inst_.InitNop(42);
  EXPECT_EQ(inst_.out(), 42);
}

TEST_F(ProgInstTest_109, OutForEmptyWidth_109) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 99);
  EXPECT_EQ(inst_.out(), 99);
}

TEST_F(ProgInstTest_109, OutForCapture_109) {
  inst_.InitCapture(1, 55);
  EXPECT_EQ(inst_.out(), 55);
}

TEST_F(ProgInstTest_109, OutForByteRange_109) {
  inst_.InitByteRange(0, 255, 0, 77);
  EXPECT_EQ(inst_.out(), 77);
}

TEST_F(ProgInstTest_109, OutForAlt_109) {
  inst_.InitAlt(33, 44);
  EXPECT_EQ(inst_.out(), 33);
  EXPECT_EQ(inst_.out1(), 44);
}

}  // namespace re2
