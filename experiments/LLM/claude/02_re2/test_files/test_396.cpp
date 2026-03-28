#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_396 : public ::testing::Test {
 protected:
  Prog::Inst inst;

  void SetUp() override {
    // Ensure inst is default-constructed (out_opcode_ should be 0)
    memset(&inst, 0, sizeof(inst));
  }
};

// Test InitFail sets opcode to kInstFail
TEST_F(ProgInstTest_396, InitFail_SetsOpcode_396) {
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// Test InitFail sets out to 0
TEST_F(ProgInstTest_396, InitFail_OutIsZero_396) {
  inst.InitFail();
  EXPECT_EQ(inst.out(), 0);
}

// Test InitNop sets opcode to kInstNop and preserves out
TEST_F(ProgInstTest_396, InitNop_SetsOpcodeAndOut_396) {
  inst.InitNop(42);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 42);
}

// Test InitNop with zero out
TEST_F(ProgInstTest_396, InitNop_ZeroOut_396) {
  inst.InitNop(0);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 0);
}

// Test InitMatch sets opcode to kInstMatch and match_id
TEST_F(ProgInstTest_396, InitMatch_SetsOpcodeAndMatchId_396) {
  inst.InitMatch(1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 1);
}

// Test InitMatch with id 0
TEST_F(ProgInstTest_396, InitMatch_ZeroId_396) {
  inst.InitMatch(0);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 0);
}

// Test InitByteRange sets opcode, lo, hi, foldcase, and out
TEST_F(ProgInstTest_396, InitByteRange_SetsFields_396) {
  inst.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0x41);
  EXPECT_EQ(inst.hi(), 0x5A);
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 10);
}

// Test InitByteRange with foldcase enabled
TEST_F(ProgInstTest_396, InitByteRange_WithFoldcase_396) {
  inst.InitByteRange(0x61, 0x7A, 1, 20);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0x61);
  EXPECT_EQ(inst.hi(), 0x7A);
  EXPECT_EQ(inst.foldcase(), 1);
  EXPECT_EQ(inst.out(), 20);
}

// Test InitByteRange single byte range
TEST_F(ProgInstTest_396, InitByteRange_SingleByte_396) {
  inst.InitByteRange(0x00, 0x00, 0, 5);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0x00);
  EXPECT_EQ(inst.hi(), 0x00);
  EXPECT_EQ(inst.out(), 5);
}

// Test InitByteRange full byte range
TEST_F(ProgInstTest_396, InitByteRange_FullRange_396) {
  inst.InitByteRange(0x00, 0xFF, 0, 7);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0x00);
  EXPECT_EQ(inst.hi(), 0xFF);
}

// Test InitCapture sets opcode, cap, and out
TEST_F(ProgInstTest_396, InitCapture_SetsFields_396) {
  inst.InitCapture(3, 15);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 3);
  EXPECT_EQ(inst.out(), 15);
}

// Test InitCapture with zero cap
TEST_F(ProgInstTest_396, InitCapture_ZeroCap_396) {
  inst.InitCapture(0, 0);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 0);
  EXPECT_EQ(inst.out(), 0);
}

// Test InitEmptyWidth sets opcode, empty, and out
TEST_F(ProgInstTest_396, InitEmptyWidth_SetsFields_396) {
  inst.InitEmptyWidth(kEmptyBeginLine, 8);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst.out(), 8);
}

// Test InitAlt sets opcode, out, and out1
TEST_F(ProgInstTest_396, InitAlt_SetsFields_396) {
  inst.InitAlt(3, 7);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 7);
}

// Test InitAlt with zero values
TEST_F(ProgInstTest_396, InitAlt_ZeroValues_396) {
  inst.InitAlt(0, 0);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 0);
  EXPECT_EQ(inst.out1(), 0);
}

// Test Dump returns a non-empty string for InitFail
TEST_F(ProgInstTest_396, Dump_InitFail_396) {
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump returns a non-empty string for InitMatch
TEST_F(ProgInstTest_396, Dump_InitMatch_396) {
  inst.InitMatch(1);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump returns a non-empty string for InitByteRange
TEST_F(ProgInstTest_396, Dump_InitByteRange_396) {
  inst.InitByteRange(0x41, 0x5A, 0, 10);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitNop
TEST_F(ProgInstTest_396, Dump_InitNop_396) {
  inst.InitNop(5);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitAlt
TEST_F(ProgInstTest_396, Dump_InitAlt_396) {
  inst.InitAlt(1, 2);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitCapture
TEST_F(ProgInstTest_396, Dump_InitCapture_396) {
  inst.InitCapture(0, 3);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump for InitEmptyWidth
TEST_F(ProgInstTest_396, Dump_InitEmptyWidth_396) {
  inst.InitEmptyWidth(kEmptyBeginLine, 4);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Matches on a ByteRange instruction
TEST_F(ProgInstTest_396, Matches_InRange_396) {
  inst.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_TRUE(inst.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst.Matches(0x5A));   // 'Z'
}

// Test Matches on a ByteRange instruction - out of range
TEST_F(ProgInstTest_396, Matches_OutOfRange_396) {
  inst.InitByteRange(0x41, 0x5A, 0, 10);
  EXPECT_FALSE(inst.Matches(0x40));  // Just below 'A'
  EXPECT_FALSE(inst.Matches(0x5B));  // Just above 'Z'
  EXPECT_FALSE(inst.Matches(0x00));
  EXPECT_FALSE(inst.Matches(0xFF));
}

// Test Matches with foldcase on byte range
TEST_F(ProgInstTest_396, Matches_WithFoldcase_396) {
  // 'a' to 'z' with foldcase
  inst.InitByteRange('a', 'z', 1, 10);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_TRUE(inst.Matches('m'));
  // With foldcase, uppercase letters should also match
  EXPECT_TRUE(inst.Matches('A'));
  EXPECT_TRUE(inst.Matches('Z'));
}

// Test copy constructor preserves state
TEST_F(ProgInstTest_396, CopyConstructor_396) {
  inst.InitByteRange(0x41, 0x5A, 0, 10);
  Prog::Inst copy(inst);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.out(), 10);
}

// Test copy assignment preserves state
TEST_F(ProgInstTest_396, CopyAssignment_396) {
  inst.InitMatch(42);
  Prog::Inst other;
  memset(&other, 0, sizeof(other));
  other = inst;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 42);
}

// Test that different Init functions result in correct opcodes
TEST_F(ProgInstTest_396, OpcodeValues_396) {
  // Verify enum values match expected
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

// Test InitMatch with larger id
TEST_F(ProgInstTest_396, InitMatch_LargerId_396) {
  inst.InitMatch(1000);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 1000);
}

// Test InitByteRange with boundary byte values
TEST_F(ProgInstTest_396, InitByteRange_BoundaryValues_396) {
  inst.InitByteRange(0, 255, 0, 1);
  EXPECT_EQ(inst.lo(), 0);
  EXPECT_EQ(inst.hi(), 255);
  EXPECT_TRUE(inst.Matches(0));
  EXPECT_TRUE(inst.Matches(255));
  EXPECT_TRUE(inst.Matches(128));
}

// Test Matches single-byte range boundary
TEST_F(ProgInstTest_396, Matches_SingleByteRange_396) {
  inst.InitByteRange(0x61, 0x61, 0, 5);  // exactly 'a'
  EXPECT_TRUE(inst.Matches(0x61));
  EXPECT_FALSE(inst.Matches(0x60));
  EXPECT_FALSE(inst.Matches(0x62));
}

}  // namespace re2
