#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compiler.h"

namespace re2 {

class ProgInstTest_101 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that InitAlt sets out correctly
TEST_F(ProgInstTest_101, InitAltSetsOut_101) {
  Prog::Inst inst;
  inst.InitAlt(5, 10);
  EXPECT_EQ(5, inst.out());
}

// Test that InitAlt sets out1 correctly
TEST_F(ProgInstTest_101, InitAltSetsOut1_101) {
  Prog::Inst inst;
  inst.InitAlt(5, 10);
  EXPECT_EQ(10, inst.out1());
}

// Test that InitByteRange sets out correctly
TEST_F(ProgInstTest_101, InitByteRangeSetsOut_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);
  EXPECT_EQ(7, inst.out());
}

// Test that InitByteRange sets lo correctly
TEST_F(ProgInstTest_101, InitByteRangeSetsLo_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);
  EXPECT_EQ(0x41, inst.lo());
}

// Test that InitByteRange sets hi correctly
TEST_F(ProgInstTest_101, InitByteRangeSetsHi_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);
  EXPECT_EQ(0x5A, inst.hi());
}

// Test that InitByteRange sets foldcase correctly
TEST_F(ProgInstTest_101, InitByteRangeSetsFoldcase_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 1, 7);
  EXPECT_EQ(1, inst.foldcase());
}

// Test that InitByteRange with foldcase=0
TEST_F(ProgInstTest_101, InitByteRangeFoldcaseZero_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);
  EXPECT_EQ(0, inst.foldcase());
}

// Test that InitCapture sets out correctly
TEST_F(ProgInstTest_101, InitCaptureSetsOut_101) {
  Prog::Inst inst;
  inst.InitCapture(3, 12);
  EXPECT_EQ(12, inst.out());
}

// Test that InitCapture sets cap correctly
TEST_F(ProgInstTest_101, InitCaptureSetsCap_101) {
  Prog::Inst inst;
  inst.InitCapture(3, 12);
  EXPECT_EQ(3, inst.cap());
}

// Test that InitEmptyWidth sets out correctly
TEST_F(ProgInstTest_101, InitEmptyWidthSetsOut_101) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 8);
  EXPECT_EQ(8, inst.out());
}

// Test that InitEmptyWidth sets empty correctly
TEST_F(ProgInstTest_101, InitEmptyWidthSetsEmpty_101) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 8);
  EXPECT_EQ(kEmptyBeginLine, inst.empty());
}

// Test that InitMatch sets match_id correctly
TEST_F(ProgInstTest_101, InitMatchSetsMatchId_101) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(42, inst.match_id());
}

// Test that InitNop sets out correctly
TEST_F(ProgInstTest_101, InitNopSetsOut_101) {
  Prog::Inst inst;
  inst.InitNop(15);
  EXPECT_EQ(15, inst.out());
}

// Test that InitAlt with out=0
TEST_F(ProgInstTest_101, InitAltWithZeroOut_101) {
  Prog::Inst inst;
  inst.InitAlt(0, 0);
  EXPECT_EQ(0, inst.out());
  EXPECT_EQ(0, inst.out1());
}

// Test that InitByteRange with single byte range (lo == hi)
TEST_F(ProgInstTest_101, InitByteRangeSingleByte_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x61, 0, 3);
  EXPECT_EQ(0x61, inst.lo());
  EXPECT_EQ(0x61, inst.hi());
  EXPECT_EQ(3, inst.out());
}

// Test that InitByteRange with full byte range
TEST_F(ProgInstTest_101, InitByteRangeFullRange_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x00, 0xFF, 0, 1);
  EXPECT_EQ(0x00, inst.lo());
  EXPECT_EQ(0xFF, inst.hi());
  EXPECT_EQ(1, inst.out());
}

// Test InitMatch with id=0
TEST_F(ProgInstTest_101, InitMatchWithZeroId_101) {
  Prog::Inst inst;
  inst.InitMatch(0);
  EXPECT_EQ(0, inst.match_id());
}

// Test InitCapture with cap=0
TEST_F(ProgInstTest_101, InitCaptureWithZeroCap_101) {
  Prog::Inst inst;
  inst.InitCapture(0, 5);
  EXPECT_EQ(0, inst.cap());
  EXPECT_EQ(5, inst.out());
}

// Test that opcode is correct for Alt
TEST_F(ProgInstTest_101, InitAltOpcode_101) {
  Prog::Inst inst;
  inst.InitAlt(1, 2);
  EXPECT_EQ(kInstAlt, inst.opcode());
}

// Test that opcode is correct for ByteRange
TEST_F(ProgInstTest_101, InitByteRangeOpcode_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);
  EXPECT_EQ(kInstByteRange, inst.opcode());
}

// Test that opcode is correct for Capture
TEST_F(ProgInstTest_101, InitCaptureOpcode_101) {
  Prog::Inst inst;
  inst.InitCapture(1, 2);
  EXPECT_EQ(kInstCapture, inst.opcode());
}

// Test that opcode is correct for EmptyWidth
TEST_F(ProgInstTest_101, InitEmptyWidthOpcode_101) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 3);
  EXPECT_EQ(kInstEmptyWidth, inst.opcode());
}

// Test that opcode is correct for Match
TEST_F(ProgInstTest_101, InitMatchOpcode_101) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(kInstMatch, inst.opcode());
}

// Test that opcode is correct for Nop
TEST_F(ProgInstTest_101, InitNopOpcode_101) {
  Prog::Inst inst;
  inst.InitNop(4);
  EXPECT_EQ(kInstNop, inst.opcode());
}

// Test that opcode is correct for Fail
TEST_F(ProgInstTest_101, InitFailOpcode_101) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(kInstFail, inst.opcode());
}

// Test Dump doesn't crash (just basic invocation)
TEST_F(ProgInstTest_101, DumpAlt_101) {
  Prog::Inst inst;
  inst.InitAlt(1, 2);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for Match
TEST_F(ProgInstTest_101, DumpMatch_101) {
  Prog::Inst inst;
  inst.InitMatch(1);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for Fail
TEST_F(ProgInstTest_101, DumpFail_101) {
  Prog::Inst inst;
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for ByteRange
TEST_F(ProgInstTest_101, DumpByteRange_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x7A, 0, 3);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for Nop
TEST_F(ProgInstTest_101, DumpNop_101) {
  Prog::Inst inst;
  inst.InitNop(0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor
TEST_F(ProgInstTest_101, CopyConstructor_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 1, 7);
  Prog::Inst inst2(inst);
  EXPECT_EQ(inst.out(), inst2.out());
  EXPECT_EQ(inst.lo(), inst2.lo());
  EXPECT_EQ(inst.hi(), inst2.hi());
  EXPECT_EQ(inst.foldcase(), inst2.foldcase());
  EXPECT_EQ(inst.opcode(), inst2.opcode());
}

// Test copy assignment
TEST_F(ProgInstTest_101, CopyAssignment_101) {
  Prog::Inst inst;
  inst.InitCapture(5, 20);
  Prog::Inst inst2;
  inst2.InitNop(0);
  inst2 = inst;
  EXPECT_EQ(inst.out(), inst2.out());
  EXPECT_EQ(inst.cap(), inst2.cap());
  EXPECT_EQ(inst.opcode(), inst2.opcode());
}

// Test Matches for ByteRange - character in range
TEST_F(ProgInstTest_101, ByteRangeMatchesInRange_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);  // A-Z
  EXPECT_TRUE(inst.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst.Matches(0x5A));   // 'Z'
}

// Test Matches for ByteRange - character out of range
TEST_F(ProgInstTest_101, ByteRangeMatchesOutOfRange_101) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 7);  // A-Z
  EXPECT_FALSE(inst.Matches(0x40));  // '@'
  EXPECT_FALSE(inst.Matches(0x5B));  // '['
  EXPECT_FALSE(inst.Matches(0x61));  // 'a'
}

// Test Matches for ByteRange with foldcase
TEST_F(ProgInstTest_101, ByteRangeMatchesFoldcase_101) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 7);
  // With foldcase, uppercase should also match
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_TRUE(inst.Matches('A'));
  EXPECT_TRUE(inst.Matches('Z'));
}

// Test large out value
TEST_F(ProgInstTest_101, LargeOutValue_101) {
  Prog::Inst inst;
  uint32_t large_out = 0x0FFFFFF;  // Large but fits in the out field
  inst.InitNop(large_out);
  EXPECT_EQ(static_cast<int>(large_out), inst.out());
}

// Test InitEmptyWidth with different empty ops
TEST_F(ProgInstTest_101, InitEmptyWidthBeginText_101) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginText, 2);
  EXPECT_EQ(kEmptyBeginText, inst.empty());
  EXPECT_EQ(2, inst.out());
}

TEST_F(ProgInstTest_101, InitEmptyWidthEndLine_101) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyEndLine, 4);
  EXPECT_EQ(kEmptyEndLine, inst.empty());
  EXPECT_EQ(4, inst.out());
}

// Test InitMatch with larger match id
TEST_F(ProgInstTest_101, InitMatchLargerId_101) {
  Prog::Inst inst;
  inst.InitMatch(1000);
  EXPECT_EQ(1000, inst.match_id());
}

// Test that out() extracts correctly from out_opcode_ (shifted by 4)
TEST_F(ProgInstTest_101, OutExtractionFromOutOpcode_101) {
  Prog::Inst inst;
  inst.InitAlt(100, 200);
  EXPECT_EQ(100, inst.out());
  
  inst.InitAlt(1, 2);
  EXPECT_EQ(1, inst.out());
  
  inst.InitAlt(0, 0);
  EXPECT_EQ(0, inst.out());
}

// Test that reinitializing changes values
TEST_F(ProgInstTest_101, ReinitChangesValues_101) {
  Prog::Inst inst;
  inst.InitNop(10);
  EXPECT_EQ(10, inst.out());
  EXPECT_EQ(kInstNop, inst.opcode());
  
  inst.InitByteRange(0x30, 0x39, 0, 20);
  EXPECT_EQ(20, inst.out());
  EXPECT_EQ(kInstByteRange, inst.opcode());
  EXPECT_EQ(0x30, inst.lo());
  EXPECT_EQ(0x39, inst.hi());
}

}  // namespace re2
