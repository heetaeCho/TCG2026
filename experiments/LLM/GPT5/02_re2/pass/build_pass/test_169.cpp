// File: regexp_parseflags_xor_test_169.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using PF = re2::Regexp::ParseFlags;

class RegexpParseFlagsXorTest_169 : public ::testing::Test {};

// Normal operation: XOR with zero (right identity)
TEST_F(RegexpParseFlagsXorTest_169, XorWithZeroRight_169) {
  PF a = static_cast<PF>(0x15); // arbitrary bit pattern
  PF zero = static_cast<PF>(0);
  EXPECT_EQ(a ^ zero, a);
}

// Normal operation: XOR with zero (left identity)
TEST_F(RegexpParseFlagsXorTest_169, XorWithZeroLeft_169) {
  PF a = static_cast<PF>(0x2A); // arbitrary bit pattern
  PF zero = static_cast<PF>(0);
  EXPECT_EQ(zero ^ a, a);
}

// Boundary/consistency: self-XOR clears bits
TEST_F(RegexpParseFlagsXorTest_169, SelfXorYieldsZero_169) {
  PF a = static_cast<PF>(0x7F);
  EXPECT_EQ(a ^ a, static_cast<PF>(0));
}

// Algebraic property: commutativity
TEST_F(RegexpParseFlagsXorTest_169, Commutative_169) {
  PF a = static_cast<PF>(0x12);
  PF b = static_cast<PF>(0x34);
  EXPECT_EQ(a ^ b, b ^ a);
}

// Algebraic property: associativity
TEST_F(RegexpParseFlagsXorTest_169, Associative_169) {
  PF a = static_cast<PF>(0x01);
  PF b = static_cast<PF>(0x02);
  PF c = static_cast<PF>(0x04);
  EXPECT_EQ((a ^ b) ^ c, a ^ (b ^ c));
}

// Observable behavior: non-overlapping bits combine
TEST_F(RegexpParseFlagsXorTest_169, NonOverlappingBitsCombine_169) {
  PF a = static_cast<PF>(0x01);
  PF b = static_cast<PF>(0x02);
  EXPECT_EQ(a ^ b, static_cast<PF>(0x03));
}

// Observable behavior: overlapping bits cancel out
TEST_F(RegexpParseFlagsXorTest_169, OverlappingBitsCancel_169) {
  PF a = static_cast<PF>(0x03); // 0b0011
  PF b = static_cast<PF>(0x01); // 0b0001
  EXPECT_EQ(a ^ b, static_cast<PF>(0x02)); // 0b0010
}

// Algebraic property: cancellation ((a ^ b) ^ b == a)
TEST_F(RegexpParseFlagsXorTest_169, Cancellation_169) {
  PF a = static_cast<PF>(0x55);
  PF b = static_cast<PF>(0x0F);
  EXPECT_EQ((a ^ b) ^ b, a);
}

// Boundary: high-bit patterns within int range
TEST_F(RegexpParseFlagsXorTest_169, HighBitsWithinIntRange_169) {
  PF a = static_cast<PF>(0x40000000); // bit 30
  PF b = static_cast<PF>(0x20000000); // bit 29
  EXPECT_EQ(a ^ b, static_cast<PF>(0x60000000));
}

// Boundary/robustness: all-bits pattern with another value
TEST_F(RegexpParseFlagsXorTest_169, AllBitsPatternXor_169) {
  PF all_bits = static_cast<PF>(-1);        // all bits set in underlying int
  PF mask     = static_cast<PF>(0x00FF00FF);
  // all_bits ^ mask should flip mask's bits off -> bitwise NOT of mask
  EXPECT_EQ(all_bits ^ mask, static_cast<PF>(~0x00FF00FF));
}

}  // namespace
