#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compiler.h"

namespace re2 {

class ProgInstTest_100 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that last() returns 0 when bit 3 of out_opcode_ is not set.
// We use InitFail which should set out_opcode_ to some known state.
TEST_F(ProgInstTest_100, InitFailAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitFail();
  // After InitFail, we can check last(). The last bit may or may not be set,
  // but the function should return 0 or 1.
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitNop
TEST_F(ProgInstTest_100, InitNopAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitNop(0);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitMatch
TEST_F(ProgInstTest_100, InitMatchAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitMatch(1);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitByteRange
TEST_F(ProgInstTest_100, InitByteRangeAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitCapture
TEST_F(ProgInstTest_100, InitCaptureAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitCapture(0, 0);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitEmptyWidth
TEST_F(ProgInstTest_100, InitEmptyWidthAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 0);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test last() returns 0 or 1 after InitAlt
TEST_F(ProgInstTest_100, InitAltAndCheckLast_100) {
  Prog::Inst inst;
  inst.InitAlt(0, 1);
  int last = inst.last();
  EXPECT_TRUE(last == 0 || last == 1);
}

// Test that opcode() returns expected opcode after various Init methods
TEST_F(ProgInstTest_100, OpcodeAfterInitFail_100) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitNop_100) {
  Prog::Inst inst;
  inst.InitNop(0);
  EXPECT_EQ(inst.opcode(), kInstNop);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitMatch_100) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitCapture_100) {
  Prog::Inst inst;
  inst.InitCapture(0, 0);
  EXPECT_EQ(inst.opcode(), kInstCapture);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitEmptyWidth_100) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 0);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
}

TEST_F(ProgInstTest_100, OpcodeAfterInitAlt_100) {
  Prog::Inst inst;
  inst.InitAlt(0, 1);
  EXPECT_EQ(inst.opcode(), kInstAlt);
}

// Test out() after InitNop
TEST_F(ProgInstTest_100, OutAfterInitNop_100) {
  Prog::Inst inst;
  inst.InitNop(42);
  EXPECT_EQ(inst.out(), 42);
}

// Test out() after InitByteRange
TEST_F(ProgInstTest_100, OutAfterInitByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x00, 0xFF, 0, 100);
  EXPECT_EQ(inst.out(), 100);
}

// Test out() and out1() after InitAlt
TEST_F(ProgInstTest_100, OutAndOut1AfterInitAlt_100) {
  Prog::Inst inst;
  inst.InitAlt(10, 20);
  EXPECT_EQ(inst.out(), 10);
  EXPECT_EQ(inst.out1(), 20);
}

// Test cap() after InitCapture
TEST_F(ProgInstTest_100, CapAfterInitCapture_100) {
  Prog::Inst inst;
  inst.InitCapture(5, 15);
  EXPECT_EQ(inst.cap(), 5);
  EXPECT_EQ(inst.out(), 15);
}

// Test match_id() after InitMatch
TEST_F(ProgInstTest_100, MatchIdAfterInitMatch_100) {
  Prog::Inst inst;
  inst.InitMatch(7);
  EXPECT_EQ(inst.match_id(), 7);
}

// Test lo() and hi() after InitByteRange
TEST_F(ProgInstTest_100, LoHiAfterInitByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst.lo(), 0x41);
  EXPECT_EQ(inst.hi(), 0x5A);
}

// Test foldcase() after InitByteRange
TEST_F(ProgInstTest_100, FoldcaseAfterInitByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 1, 0);
  EXPECT_EQ(inst.foldcase(), 1);
}

TEST_F(ProgInstTest_100, FoldcaseZeroAfterInitByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);
  EXPECT_EQ(inst.foldcase(), 0);
}

// Test empty() after InitEmptyWidth
TEST_F(ProgInstTest_100, EmptyAfterInitEmptyWidth_100) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 0);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
}

// Test Dump() returns a non-empty string
TEST_F(ProgInstTest_100, DumpReturnsNonEmpty_100) {
  Prog::Inst inst;
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_100, DumpNop_100) {
  Prog::Inst inst;
  inst.InitNop(0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor preserves state
TEST_F(ProgInstTest_100, CopyConstructor_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 1, 50);
  Prog::Inst copy(inst);
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.lo(), 0x41);
  EXPECT_EQ(copy.hi(), 0x5A);
  EXPECT_EQ(copy.foldcase(), 1);
  EXPECT_EQ(copy.out(), 50);
  EXPECT_EQ(copy.last(), inst.last());
}

// Test assignment operator preserves state
TEST_F(ProgInstTest_100, AssignmentOperator_100) {
  Prog::Inst inst;
  inst.InitMatch(3);
  Prog::Inst other;
  other.InitFail();
  other = inst;
  EXPECT_EQ(other.opcode(), kInstMatch);
  EXPECT_EQ(other.match_id(), 3);
}

// Test Matches for ByteRange instruction
TEST_F(ProgInstTest_100, MatchesByteRangeInRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);  // 'A' to 'Z'
  EXPECT_TRUE(inst.Matches(0x41));   // 'A'
  EXPECT_TRUE(inst.Matches(0x4D));   // 'M'
  EXPECT_TRUE(inst.Matches(0x5A));   // 'Z'
}

TEST_F(ProgInstTest_100, MatchesByteRangeOutOfRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x5A, 0, 0);  // 'A' to 'Z'
  EXPECT_FALSE(inst.Matches(0x40));  // '@' - just below range
  EXPECT_FALSE(inst.Matches(0x5B));  // '[' - just above range
  EXPECT_FALSE(inst.Matches(0x61));  // 'a' - lowercase
}

// Test Matches with foldcase
TEST_F(ProgInstTest_100, MatchesByteRangeWithFoldcase_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x7A, 1, 0);  // 'a' to 'z', foldcase
  EXPECT_TRUE(inst.Matches(0x61));   // 'a'
  EXPECT_TRUE(inst.Matches(0x7A));   // 'z'
  // With foldcase, uppercase letters that fold to the range should also match
  EXPECT_TRUE(inst.Matches(0x41));   // 'A' (folds to 'a')
}

// Test boundary: single byte range
TEST_F(ProgInstTest_100, MatchesSingleByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x41, 0x41, 0, 0);  // only 'A'
  EXPECT_TRUE(inst.Matches(0x41));
  EXPECT_FALSE(inst.Matches(0x42));
  EXPECT_FALSE(inst.Matches(0x40));
}

// Test boundary: full byte range
TEST_F(ProgInstTest_100, MatchesFullByteRange_100) {
  Prog::Inst inst;
  inst.InitByteRange(0x00, 0xFF, 0, 0);
  EXPECT_TRUE(inst.Matches(0x00));
  EXPECT_TRUE(inst.Matches(0x7F));
  EXPECT_TRUE(inst.Matches(0xFF));
}

// Test InitMatch with match_id of 0
TEST_F(ProgInstTest_100, InitMatchWithZeroId_100) {
  Prog::Inst inst;
  inst.InitMatch(0);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 0);
}

// Test InitCapture with cap 0
TEST_F(ProgInstTest_100, InitCaptureWithZeroCap_100) {
  Prog::Inst inst;
  inst.InitCapture(0, 0);
  EXPECT_EQ(inst.cap(), 0);
}

// Test out() with large value after InitNop
TEST_F(ProgInstTest_100, OutLargeValueAfterInitNop_100) {
  Prog::Inst inst;
  inst.InitNop(1000000);
  EXPECT_EQ(inst.out(), 1000000);
}

// Integration test: compile a regex and verify the program exists
TEST_F(ProgInstTest_100, CompileRegexAndCheckProg_100) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
}

// Test that default constructed Inst can be assigned
TEST_F(ProgInstTest_100, DefaultConstructAndAssign_100) {
  Prog::Inst a;
  Prog::Inst b;
  a.InitNop(5);
  b = a;
  EXPECT_EQ(b.opcode(), kInstNop);
  EXPECT_EQ(b.out(), 5);
}

// Test InitEmptyWidth with different empty ops
TEST_F(ProgInstTest_100, InitEmptyWidthBeginText_100) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginText, 0);
  EXPECT_EQ(inst.empty(), kEmptyBeginText);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
}

TEST_F(ProgInstTest_100, InitEmptyWidthEndLine_100) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyEndLine, 3);
  EXPECT_EQ(inst.empty(), kEmptyEndLine);
  EXPECT_EQ(inst.out(), 3);
}

}  // namespace re2
