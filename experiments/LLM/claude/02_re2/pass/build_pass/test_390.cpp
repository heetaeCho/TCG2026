#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgInstTest_390 : public ::testing::Test {
 protected:
  Prog::Inst inst;

  void SetUp() override {
    // Default-constructed Inst should have out_opcode_ = 0
    inst = Prog::Inst();
  }
};

// =============================================================================
// Tests for InitAlt
// =============================================================================

TEST_F(ProgInstTest_390, InitAlt_SetsOpcodeToAlt_390) {
  inst.InitAlt(10, 20);
  EXPECT_EQ(inst.opcode(), kInstAlt);
}

TEST_F(ProgInstTest_390, InitAlt_SetsOut_390) {
  inst.InitAlt(10, 20);
  EXPECT_EQ(inst.out(), 10);
}

TEST_F(ProgInstTest_390, InitAlt_SetsOut1_390) {
  inst.InitAlt(10, 20);
  EXPECT_EQ(inst.out1(), 20);
}

TEST_F(ProgInstTest_390, InitAlt_ZeroValues_390) {
  inst.InitAlt(0, 0);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 0);
  EXPECT_EQ(inst.out1(), 0);
}

TEST_F(ProgInstTest_390, InitAlt_LargeOut_390) {
  inst.InitAlt(1000000, 2000000);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 1000000);
  EXPECT_EQ(inst.out1(), 2000000);
}

// =============================================================================
// Tests for InitByteRange
// =============================================================================

TEST_F(ProgInstTest_390, InitByteRange_SetsOpcode_390) {
  inst.InitByteRange(0, 255, 0, 5);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
}

TEST_F(ProgInstTest_390, InitByteRange_SetsLoHi_390) {
  inst.InitByteRange(65, 90, 0, 5);
  EXPECT_EQ(inst.lo(), 65);
  EXPECT_EQ(inst.hi(), 90);
}

TEST_F(ProgInstTest_390, InitByteRange_SetsFoldcase_390) {
  inst.InitByteRange(65, 90, 1, 5);
  EXPECT_EQ(inst.foldcase(), 1);
}

TEST_F(ProgInstTest_390, InitByteRange_SetsOut_390) {
  inst.InitByteRange(65, 90, 0, 42);
  EXPECT_EQ(inst.out(), 42);
}

TEST_F(ProgInstTest_390, InitByteRange_SingleByte_390) {
  inst.InitByteRange(97, 97, 0, 3);
  EXPECT_EQ(inst.lo(), 97);
  EXPECT_EQ(inst.hi(), 97);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
}

TEST_F(ProgInstTest_390, InitByteRange_FullRange_390) {
  inst.InitByteRange(0, 255, 0, 1);
  EXPECT_EQ(inst.lo(), 0);
  EXPECT_EQ(inst.hi(), 255);
}

TEST_F(ProgInstTest_390, InitByteRange_NoFoldcase_390) {
  inst.InitByteRange(0, 255, 0, 1);
  EXPECT_EQ(inst.foldcase(), 0);
}

// =============================================================================
// Tests for InitCapture
// =============================================================================

TEST_F(ProgInstTest_390, InitCapture_SetsOpcode_390) {
  inst.InitCapture(2, 10);
  EXPECT_EQ(inst.opcode(), kInstCapture);
}

TEST_F(ProgInstTest_390, InitCapture_SetsCap_390) {
  inst.InitCapture(2, 10);
  EXPECT_EQ(inst.cap(), 2);
}

TEST_F(ProgInstTest_390, InitCapture_SetsOut_390) {
  inst.InitCapture(2, 10);
  EXPECT_EQ(inst.out(), 10);
}

TEST_F(ProgInstTest_390, InitCapture_ZeroCap_390) {
  inst.InitCapture(0, 5);
  EXPECT_EQ(inst.cap(), 0);
  EXPECT_EQ(inst.out(), 5);
}

// =============================================================================
// Tests for InitEmptyWidth
// =============================================================================

TEST_F(ProgInstTest_390, InitEmptyWidth_SetsOpcode_390) {
  inst.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
}

TEST_F(ProgInstTest_390, InitEmptyWidth_SetsEmpty_390) {
  inst.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
}

TEST_F(ProgInstTest_390, InitEmptyWidth_SetsOut_390) {
  inst.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst.out(), 7);
}

TEST_F(ProgInstTest_390, InitEmptyWidth_EndLine_390) {
  inst.InitEmptyWidth(kEmptyEndLine, 3);
  EXPECT_EQ(inst.empty(), kEmptyEndLine);
  EXPECT_EQ(inst.out(), 3);
}

// =============================================================================
// Tests for InitMatch
// =============================================================================

TEST_F(ProgInstTest_390, InitMatch_SetsOpcode_390) {
  inst.InitMatch(1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
}

TEST_F(ProgInstTest_390, InitMatch_SetsMatchId_390) {
  inst.InitMatch(42);
  EXPECT_EQ(inst.match_id(), 42);
}

TEST_F(ProgInstTest_390, InitMatch_ZeroId_390) {
  inst.InitMatch(0);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 0);
}

// =============================================================================
// Tests for InitNop
// =============================================================================

TEST_F(ProgInstTest_390, InitNop_SetsOpcode_390) {
  inst.InitNop(5);
  EXPECT_EQ(inst.opcode(), kInstNop);
}

TEST_F(ProgInstTest_390, InitNop_SetsOut_390) {
  inst.InitNop(5);
  EXPECT_EQ(inst.out(), 5);
}

TEST_F(ProgInstTest_390, InitNop_ZeroOut_390) {
  inst.InitNop(0);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 0);
}

// =============================================================================
// Tests for InitFail
// =============================================================================

TEST_F(ProgInstTest_390, InitFail_SetsOpcode_390) {
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// =============================================================================
// Tests for Dump
// =============================================================================

TEST_F(ProgInstTest_390, Dump_AltReturnsNonEmpty_390) {
  inst.InitAlt(10, 20);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_390, Dump_MatchReturnsNonEmpty_390) {
  inst.InitMatch(1);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_390, Dump_FailReturnsNonEmpty_390) {
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_390, Dump_ByteRangeReturnsNonEmpty_390) {
  inst.InitByteRange(65, 90, 0, 5);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_390, Dump_NopReturnsNonEmpty_390) {
  inst.InitNop(3);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// =============================================================================
// Tests for Matches (on InitByteRange)
// =============================================================================

TEST_F(ProgInstTest_390, Matches_InRange_390) {
  inst.InitByteRange(65, 90, 0, 5);  // A-Z
  EXPECT_TRUE(inst.Matches(65));   // 'A'
  EXPECT_TRUE(inst.Matches(90));   // 'Z'
  EXPECT_TRUE(inst.Matches(75));   // 'K'
}

TEST_F(ProgInstTest_390, Matches_OutOfRange_390) {
  inst.InitByteRange(65, 90, 0, 5);  // A-Z
  EXPECT_FALSE(inst.Matches(64));
  EXPECT_FALSE(inst.Matches(91));
  EXPECT_FALSE(inst.Matches(97));  // 'a'
}

TEST_F(ProgInstTest_390, Matches_WithFoldcase_390) {
  // With foldcase enabled, lowercase should match uppercase range
  inst.InitByteRange(65, 90, 1, 5);  // A-Z with foldcase
  EXPECT_TRUE(inst.Matches(65));   // 'A'
  EXPECT_TRUE(inst.Matches(97));   // 'a' (folded)
}

TEST_F(ProgInstTest_390, Matches_SingleByte_390) {
  inst.InitByteRange(97, 97, 0, 3);  // just 'a'
  EXPECT_TRUE(inst.Matches(97));
  EXPECT_FALSE(inst.Matches(98));
  EXPECT_FALSE(inst.Matches(96));
}

// =============================================================================
// Tests for copy semantics
// =============================================================================

TEST_F(ProgInstTest_390, CopyConstructor_390) {
  inst.InitAlt(10, 20);
  Prog::Inst copy(inst);
  EXPECT_EQ(copy.opcode(), kInstAlt);
  EXPECT_EQ(copy.out(), 10);
  EXPECT_EQ(copy.out1(), 20);
}

TEST_F(ProgInstTest_390, CopyAssignment_390) {
  inst.InitMatch(7);
  Prog::Inst other;
  other = inst;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 7);
}

}  // namespace re2
