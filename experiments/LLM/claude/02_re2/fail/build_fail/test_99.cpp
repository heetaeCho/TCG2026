#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compiler.h"

namespace re2 {

class ProgInstTest_99 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_99, InitFailSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(kInstFail, inst.opcode());
}

// Test that InitMatch sets opcode to kInstMatch
TEST_F(ProgInstTest_99, InitMatchSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(kInstMatch, inst.opcode());
}

// Test that InitMatch stores the match id
TEST_F(ProgInstTest_99, InitMatchStoresMatchId_99) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(kInstMatch, inst.opcode());
  EXPECT_EQ(42, inst.match_id());
}

// Test that InitNop sets opcode to kInstNop
TEST_F(ProgInstTest_99, InitNopSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitNop(0);
  EXPECT_EQ(kInstNop, inst.opcode());
}

// Test that InitNop stores the out value
TEST_F(ProgInstTest_99, InitNopStoresOut_99) {
  Prog::Inst inst;
  inst.InitNop(5);
  EXPECT_EQ(kInstNop, inst.opcode());
  EXPECT_EQ(5, inst.out());
}

// Test that InitByteRange sets opcode to kInstByteRange
TEST_F(ProgInstTest_99, InitByteRangeSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(kInstByteRange, inst.opcode());
}

// Test that InitByteRange stores lo and hi
TEST_F(ProgInstTest_99, InitByteRangeStoresLoHi_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x7A, 0, 10);
  EXPECT_EQ(0x61, inst.lo());
  EXPECT_EQ(0x7A, inst.hi());
  EXPECT_EQ(0, inst.foldcase());
  EXPECT_EQ(10, inst.out());
}

// Test that InitByteRange with foldcase stores foldcase
TEST_F(ProgInstTest_99, InitByteRangeWithFoldcase_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(kInstByteRange, inst.opcode());
  EXPECT_EQ(1, inst.foldcase());
}

// Test that InitCapture sets opcode to kInstCapture
TEST_F(ProgInstTest_99, InitCaptureSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitCapture(0, 0);
  EXPECT_EQ(kInstCapture, inst.opcode());
}

// Test that InitCapture stores cap value
TEST_F(ProgInstTest_99, InitCaptureStoresCap_99) {
  Prog::Inst inst;
  inst.InitCapture(3, 7);
  EXPECT_EQ(3, inst.cap());
  EXPECT_EQ(7, inst.out());
}

// Test that InitEmptyWidth sets opcode to kInstEmptyWidth
TEST_F(ProgInstTest_99, InitEmptyWidthSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 0);
  EXPECT_EQ(kInstEmptyWidth, inst.opcode());
}

// Test that InitEmptyWidth stores empty value
TEST_F(ProgInstTest_99, InitEmptyWidthStoresEmpty_99) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyEndLine, 5);
  EXPECT_EQ(kEmptyEndLine, inst.empty());
  EXPECT_EQ(5, inst.out());
}

// Test that InitAlt sets opcode to kInstAlt
TEST_F(ProgInstTest_99, InitAltSetsOpcode_99) {
  Prog::Inst inst;
  inst.InitAlt(1, 2);
  EXPECT_EQ(kInstAlt, inst.opcode());
}

// Test that InitAlt stores out and out1
TEST_F(ProgInstTest_99, InitAltStoresOutAndOut1_99) {
  Prog::Inst inst;
  inst.InitAlt(3, 4);
  EXPECT_EQ(3, inst.out());
  EXPECT_EQ(4, inst.out1());
}

// Test copy constructor preserves state
TEST_F(ProgInstTest_99, CopyConstructorPreservesState_99) {
  Prog::Inst inst;
  inst.InitMatch(7);
  Prog::Inst copy(inst);
  EXPECT_EQ(kInstMatch, copy.opcode());
  EXPECT_EQ(7, copy.match_id());
}

// Test assignment operator preserves state
TEST_F(ProgInstTest_99, AssignmentOperatorPreservesState_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x30, 0x39, 0, 15);
  Prog::Inst other;
  other.InitFail();
  other = inst;
  EXPECT_EQ(kInstByteRange, other.opcode());
  EXPECT_EQ(0x30, other.lo());
  EXPECT_EQ(0x39, other.hi());
  EXPECT_EQ(15, other.out());
}

// Test InitMatch with id 0 (boundary)
TEST_F(ProgInstTest_99, InitMatchWithZeroId_99) {
  Prog::Inst inst;
  inst.InitMatch(0);
  EXPECT_EQ(kInstMatch, inst.opcode());
  EXPECT_EQ(0, inst.match_id());
}

// Test InitByteRange with single byte range (lo == hi)
TEST_F(ProgInstTest_99, InitByteRangeSingleByte_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x41, 0, 0);
  EXPECT_EQ(kInstByteRange, inst.opcode());
  EXPECT_EQ(0x41, inst.lo());
  EXPECT_EQ(0x41, inst.hi());
}

// Test InitByteRange full range
TEST_F(ProgInstTest_99, InitByteRangeFullRange_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_EQ(kInstByteRange, inst.opcode());
  EXPECT_EQ(0x00, inst.lo());
  EXPECT_EQ(0xFF, inst.hi());
}

// Test Matches on a ByteRange instruction
TEST_F(ProgInstTest_99, ByteRangeMatchesCharInRange_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_TRUE(inst.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst.Matches(0x5A));   // 'Z'
}

// Test Matches on a ByteRange instruction for char outside range
TEST_F(ProgInstTest_99, ByteRangeDoesNotMatchCharOutOfRange_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_FALSE(inst.Matches(0x40));  // '@' - just below range
  EXPECT_FALSE(inst.Matches(0x5B));  // '[' - just above range
  EXPECT_FALSE(inst.Matches(0x61));  // 'a'
}

// Test Dump produces non-empty string for various inst types
TEST_F(ProgInstTest_99, DumpNonEmptyForFail_99) {
  Prog::Inst inst;
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_99, DumpNonEmptyForMatch_99) {
  Prog::Inst inst;
  inst.InitMatch(1);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_99, DumpNonEmptyForByteRange_99) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x7A, 0, 0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test InitNop with out value 0
TEST_F(ProgInstTest_99, InitNopWithZeroOut_99) {
  Prog::Inst inst;
  inst.InitNop(0);
  EXPECT_EQ(kInstNop, inst.opcode());
  EXPECT_EQ(0, inst.out());
}

// Test InitCapture with cap 0
TEST_F(ProgInstTest_99, InitCaptureWithZeroCap_99) {
  Prog::Inst inst;
  inst.InitCapture(0, 0);
  EXPECT_EQ(kInstCapture, inst.opcode());
  EXPECT_EQ(0, inst.cap());
}

// Test that overwriting an instruction works (reinitialize)
TEST_F(ProgInstTest_99, ReinitializeInst_99) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(kInstFail, inst.opcode());
  
  inst.InitMatch(5);
  EXPECT_EQ(kInstMatch, inst.opcode());
  EXPECT_EQ(5, inst.match_id());
}

// Test InitEmptyWidth with combined empty flags
TEST_F(ProgInstTest_99, InitEmptyWidthCombinedFlags_99) {
  Prog::Inst inst;
  EmptyOp combined = static_cast<EmptyOp>(kEmptyBeginLine | kEmptyEndLine);
  inst.InitEmptyWidth(combined, 0);
  EXPECT_EQ(kInstEmptyWidth, inst.opcode());
  EXPECT_EQ(combined, inst.empty());
}

// Integration-level: Compile a regex and check that the resulting Prog is valid
TEST_F(ProgInstTest_99, CompiledProgFromSimpleRegex_99) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
}

TEST_F(ProgInstTest_99, CompiledProgFromCharClassRegex_99) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
}

TEST_F(ProgInstTest_99, CompiledProgFromAlternation_99) {
  RE2 re("abc|def");
  ASSERT_TRUE(re.ok());
}

// Test ByteRange with foldcase matching
TEST_F(ProgInstTest_99, ByteRangeWithFoldcaseMatches_99) {
  Prog::Inst inst;
  // 'a' to 'z' with foldcase
  inst.InitByteRange(0x61, 0x7A, 1, 0);
  EXPECT_TRUE(inst.Matches(0x61));   // 'a'
  EXPECT_TRUE(inst.Matches(0x7A));   // 'z'
  // With foldcase, uppercase should also match
  EXPECT_TRUE(inst.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst.Matches(0x5A));   // 'Z'
}

}  // namespace re2
