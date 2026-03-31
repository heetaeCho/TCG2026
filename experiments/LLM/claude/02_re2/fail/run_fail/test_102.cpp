#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class ProgInstTest_102 : public ::testing::Test {
 protected:
  Prog::Inst inst_;
};

// Test that out1() returns the correct value after InitAlt
TEST_F(ProgInstTest_102, Out1ReturnsCorrectValueAfterInitAlt_102) {
  uint32_t expected_out = 5;
  uint32_t expected_out1 = 10;
  inst_.InitAlt(expected_out, expected_out1);
  EXPECT_EQ(inst_.out1(), static_cast<int>(expected_out1));
}

// Test that out1() returns the correct value when out1 is 0
TEST_F(ProgInstTest_102, Out1ReturnsZeroAfterInitAltWithZeroOut1_102) {
  inst_.InitAlt(3, 0);
  EXPECT_EQ(inst_.out1(), 0);
}

// Test that out1() returns the correct out value alongside out1
TEST_F(ProgInstTest_102, OutAndOut1BothCorrectAfterInitAlt_102) {
  uint32_t expected_out = 7;
  uint32_t expected_out1 = 15;
  inst_.InitAlt(expected_out, expected_out1);
  EXPECT_EQ(inst_.out(), static_cast<int>(expected_out));
  EXPECT_EQ(inst_.out1(), static_cast<int>(expected_out1));
}

// Test that opcode is kInstAlt after InitAlt
TEST_F(ProgInstTest_102, OpcodeIsAltAfterInitAlt_102) {
  inst_.InitAlt(1, 2);
  EXPECT_EQ(inst_.opcode(), kInstAlt);
}

// Test out1() with large values
TEST_F(ProgInstTest_102, Out1WithLargeValue_102) {
  uint32_t large_out1 = 100000;
  inst_.InitAlt(0, large_out1);
  EXPECT_EQ(inst_.out1(), static_cast<int>(large_out1));
}

// Test that InitAlt sets up alt correctly with both out and out1 equal
TEST_F(ProgInstTest_102, Out1WhenOutAndOut1AreEqual_102) {
  uint32_t val = 42;
  inst_.InitAlt(val, val);
  EXPECT_EQ(inst_.out(), static_cast<int>(val));
  EXPECT_EQ(inst_.out1(), static_cast<int>(val));
}

// Test various Init methods and their opcodes
TEST_F(ProgInstTest_102, InitByteRangeSetsCorrectOpcode_102) {
  inst_.InitByteRange(0, 255, 0, 5);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

TEST_F(ProgInstTest_102, InitCaptureSetsCorrectOpcode_102) {
  inst_.InitCapture(1, 5);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

TEST_F(ProgInstTest_102, InitEmptyWidthSetsCorrectOpcode_102) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 5);
  EXPECT_EQ(inst_.opcode(), kInstEmptyWidth);
}

TEST_F(ProgInstTest_102, InitMatchSetsCorrectOpcode_102) {
  inst_.InitMatch(1);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

TEST_F(ProgInstTest_102, InitNopSetsCorrectOpcode_102) {
  inst_.InitNop(5);
  EXPECT_EQ(inst_.opcode(), kInstNop);
}

TEST_F(ProgInstTest_102, InitFailSetsCorrectOpcode_102) {
  inst_.InitFail();
  EXPECT_EQ(inst_.opcode(), kInstFail);
}

// Test ByteRange lo, hi, foldcase
TEST_F(ProgInstTest_102, ByteRangeLoHiFoldcase_102) {
  inst_.InitByteRange(65, 90, 1, 10);
  EXPECT_EQ(inst_.lo(), 65);
  EXPECT_EQ(inst_.hi(), 90);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), 10);
}

// Test Capture cap
TEST_F(ProgInstTest_102, CaptureCap_102) {
  inst_.InitCapture(3, 7);
  EXPECT_EQ(inst_.cap(), 3);
  EXPECT_EQ(inst_.out(), 7);
}

// Test Match match_id
TEST_F(ProgInstTest_102, MatchId_102) {
  inst_.InitMatch(42);
  EXPECT_EQ(inst_.match_id(), 42);
}

// Test EmptyWidth empty
TEST_F(ProgInstTest_102, EmptyWidthEmpty_102) {
  inst_.InitEmptyWidth(kEmptyBeginLine, 8);
  EXPECT_EQ(inst_.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst_.out(), 8);
}

// Test Nop out
TEST_F(ProgInstTest_102, NopOut_102) {
  inst_.InitNop(12);
  EXPECT_EQ(inst_.out(), 12);
}

// Test ByteRange Matches
TEST_F(ProgInstTest_102, ByteRangeMatchesInRange_102) {
  inst_.InitByteRange(65, 90, 0, 5);
  EXPECT_TRUE(inst_.Matches(65));
  EXPECT_TRUE(inst_.Matches(90));
  EXPECT_TRUE(inst_.Matches(75));
}

TEST_F(ProgInstTest_102, ByteRangeDoesNotMatchOutOfRange_102) {
  inst_.InitByteRange(65, 90, 0, 5);
  EXPECT_FALSE(inst_.Matches(64));
  EXPECT_FALSE(inst_.Matches(91));
}

// Test ByteRange with foldcase matching
TEST_F(ProgInstTest_102, ByteRangeMatchesWithFoldcase_102) {
  // When foldcase is set, lowercase letters should match uppercase range
  inst_.InitByteRange('a', 'z', 1, 5);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_TRUE(inst_.Matches('m'));
}

// Test Dump doesn't crash (basic smoke test)
TEST_F(ProgInstTest_102, DumpDoesNotCrash_102) {
  inst_.InitAlt(1, 2);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_102, DumpForByteRange_102) {
  inst_.InitByteRange(65, 90, 0, 5);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_102, DumpForMatch_102) {
  inst_.InitMatch(1);
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgInstTest_102, DumpForFail_102) {
  inst_.InitFail();
  std::string dump = inst_.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test copy constructor and assignment
TEST_F(ProgInstTest_102, CopyConstructor_102) {
  inst_.InitAlt(3, 7);
  Prog::Inst copy(inst_);
  EXPECT_EQ(copy.opcode(), kInstAlt);
  EXPECT_EQ(copy.out(), 3);
  EXPECT_EQ(copy.out1(), 7);
}

TEST_F(ProgInstTest_102, AssignmentOperator_102) {
  inst_.InitAlt(3, 7);
  Prog::Inst other;
  other = inst_;
  EXPECT_EQ(other.opcode(), kInstAlt);
  EXPECT_EQ(other.out(), 3);
  EXPECT_EQ(other.out1(), 7);
}

// Boundary: ByteRange with single character range
TEST_F(ProgInstTest_102, ByteRangeSingleCharacter_102) {
  inst_.InitByteRange(100, 100, 0, 5);
  EXPECT_TRUE(inst_.Matches(100));
  EXPECT_FALSE(inst_.Matches(99));
  EXPECT_FALSE(inst_.Matches(101));
}

// Boundary: ByteRange full range
TEST_F(ProgInstTest_102, ByteRangeFullRange_102) {
  inst_.InitByteRange(0, 255, 0, 5);
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_TRUE(inst_.Matches(255));
  EXPECT_TRUE(inst_.Matches(128));
}

// Test InitMatch with id 0
TEST_F(ProgInstTest_102, InitMatchWithIdZero_102) {
  inst_.InitMatch(0);
  EXPECT_EQ(inst_.match_id(), 0);
  EXPECT_EQ(inst_.opcode(), kInstMatch);
}

// Test InitCapture with cap 0
TEST_F(ProgInstTest_102, InitCaptureWithCapZero_102) {
  inst_.InitCapture(0, 0);
  EXPECT_EQ(inst_.cap(), 0);
  EXPECT_EQ(inst_.out(), 0);
  EXPECT_EQ(inst_.opcode(), kInstCapture);
}

}  // namespace re2
