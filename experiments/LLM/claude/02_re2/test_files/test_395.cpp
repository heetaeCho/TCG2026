#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_395 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Zero-initialize the Inst to ensure out_opcode_ starts at 0
    memset(&inst_, 0, sizeof(inst_));
  }

  Prog::Inst inst_;
};

// Test InitNop sets opcode to kInstNop
TEST_F(ProgInstTest_395, InitNopSetsOpcode_395) {
  inst_.InitNop(0);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitNop sets the out value
TEST_F(ProgInstTest_395, InitNopSetsOut_395) {
  inst_.InitNop(42);
  EXPECT_EQ(inst_.out(), 42);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitNop with zero out
TEST_F(ProgInstTest_395, InitNopWithZeroOut_395) {
  inst_.InitNop(0);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitNop with large out value
TEST_F(ProgInstTest_395, InitNopWithLargeOut_395) {
  inst_.InitNop(1000000);
  EXPECT_EQ(inst_.out(), 1000000);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

// Test InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_395, InitFailSetsOpcode_395) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test InitMatch sets opcode to kInstMatch
TEST_F(ProgInstTest_395, InitMatchSetsOpcode_395) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 1);
}

// Test InitMatch with different match id
TEST_F(ProgInstTest_395, InitMatchWithDifferentId_395) {
  inst_.InitMatch(5);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
  EXPECT_EQ(inst_.match_id(), 5);
}

// Test InitAlt sets opcode to kInstAlt
TEST_F(ProgInstTest_395, InitAltSetsOpcode_395) {
  inst_.InitAlt(10, 20);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
  EXPECT_EQ(inst_.out(), 10);
  EXPECT_EQ(inst_.out1(), 20);
}

// Test InitByteRange sets opcode to kInstByteRange
TEST_F(ProgInstTest_395, InitByteRangeSetsOpcode_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 'a');
  EXPECT_EQ(inst_.hi(), 'z');
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), 5);
}

// Test InitByteRange with foldcase
TEST_F(ProgInstTest_395, InitByteRangeWithFoldcase_395) {
  inst_.InitByteRange('A', 'Z', 1, 10);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 'A');
  EXPECT_EQ(inst_.hi(), 'Z');
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 10);
}

// Test InitByteRange with single byte range
TEST_F(ProgInstTest_395, InitByteRangeSingleByte_395) {
  inst_.InitByteRange('x', 'x', 0, 3);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 'x');
  EXPECT_EQ(inst_.hi(), 'x');
  EXPECT_EQ(inst_.out(), 3);
}

// Test InitCapture sets opcode to kInstCapture
TEST_F(ProgInstTest_395, InitCaptureSetsOpcode_395) {
  inst_.InitCapture(2, 7);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 2);
  EXPECT_EQ(inst_.out(), 7);
}

// Test InitEmptyWidth sets opcode to kInstEmptyWidth
TEST_F(ProgInstTest_395, InitEmptyWidthSetsOpcode_395) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 8);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst_.out(), 8);
}

// Test Dump returns a non-empty string for initialized instructions
TEST_F(ProgInstTest_395, DumpNop_395) {
  inst_.InitNop(0);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpFail_395) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpMatch_395) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpByteRange_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpAlt_395) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpCapture_395) {
  inst_.InitCapture(0, 3);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_395, DumpEmptyWidth_395) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 4);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Matches for byte range
TEST_F(ProgInstTest_395, MatchesByteInRange_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_TRUE(inst_.Matches('m'));
}

TEST_F(ProgInstTest_395, MatchesByteAtLowerBound_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_TRUE(inst_.Matches('a'));
}

TEST_F(ProgInstTest_395, MatchesByteAtUpperBound_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_TRUE(inst_.Matches('z'));
}

TEST_F(ProgInstTest_395, DoesNotMatchByteOutOfRange_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_FALSE(inst_.Matches('A'));
}

TEST_F(ProgInstTest_395, DoesNotMatchByteBelowRange_395) {
  inst_.InitByteRange('a', 'z', 0, 5);
  EXPECT_FALSE(inst_.Matches('0'));
}

// Test Matches with foldcase
TEST_F(ProgInstTest_395, MatchesByteWithFoldcase_395) {
  inst_.InitByteRange('a', 'z', 1, 5);
  // With foldcase, uppercase should also match
  EXPECT_TRUE(inst_.Matches('A'));
}

// Test copy and assignment of Inst
TEST_F(ProgInstTest_395, CopyConstructor_395) {
  inst_.InitNop(42);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstNop);
  EXPECT_EQ(copy.out(), 42);
}

TEST_F(ProgInstTest_395, AssignmentOperator_395) {
  inst_.InitNop(42);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstNop);
  EXPECT_EQ(other.out(), 42);
}

// Test enum values are distinct
TEST_F(ProgInstTest_395, EnumValuesAreDistinct_395) {
  EXPECT_NE(kInstAlt, kInstNop);
  EXPECT_NE(kInstAlt, kInstFail);
  EXPECT_NE(kInstAlt, kInstMatch);
  EXPECT_NE(kInstByteRange, kInstCapture);
  EXPECT_NE(kInstEmptyWidth, kInstMatch);
  EXPECT_EQ(kNumInst, 8);
}

// Test InitCapture with cap=0
TEST_F(ProgInstTest_395, InitCaptureWithZeroCap_395) {
  inst_.InitCapture(0, 1);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 1);
}

// Test InitByteRange full byte range
TEST_F(ProgInstTest_395, InitByteRangeFullRange_395) {
  inst_.InitByteRange(0x00, 0xFF, 0, 1);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_TRUE(inst_.Matches(127));
  EXPECT_TRUE(inst_.Matches(255));
}

// Integration test: compile a regex and verify the resulting Prog exists
TEST(ProgIntegration_395, CompileSimpleRegex_395) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

}  // namespace re2
