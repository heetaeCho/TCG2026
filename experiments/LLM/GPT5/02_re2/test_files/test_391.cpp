// File: prog_initbyetrange_test_391.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;
using re2::kInstByteRange;

class ProgInstTest_391 : public ::testing::Test {
protected:
  Prog::Inst inst_;
};

// [Normal] InitByteRange sets opcode, lo/hi, foldcase, and out.
TEST_F(ProgInstTest_391, InitByteRange_SetsOpcodeAndBounds_391) {
  const int lo = 65;          // 'A'
  const int hi = 90;          // 'Z'
  const int fold = 1;
  const uint32_t out = 123;

  inst_.InitByteRange(lo, hi, fold, out);

  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), lo);
  EXPECT_EQ(inst_.hi(), hi);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));
}

// [Boundary] lo/hi are masked to 8 bits (0xFF) per interface behavior.
TEST_F(ProgInstTest_391, InitByteRange_MasksLoHiTo8Bits_391) {
  // Values that will exercise masking.
  const int lo_in = -1;       // 0xFFFFFFFF -> 0xFF
  const int hi_in = 300;      // 0x012C -> 0x2C (44)
  const int fold = 0;
  const uint32_t out = 7;

  inst_.InitByteRange(lo_in, hi_in, fold, out);

  // Expect 8-bit masking.
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), (lo_in & 0xFF));
  EXPECT_EQ(inst_.hi(), (hi_in & 0xFF));
  EXPECT_EQ(inst_.foldcase(), 0);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));
}

// [Boundary] Exact 8-bit edges should be preserved.
TEST_F(ProgInstTest_391, InitByteRange_PreservesEightBitEdges_391) {
  const int lo = 0x00;
  const int hi = 0xFF;
  const int fold = 1;
  const uint32_t out = 42;

  inst_.InitByteRange(lo, hi, fold, out);

  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.lo(), 0x00);
  EXPECT_EQ(inst_.hi(), 0xFF);
  EXPECT_EQ(inst_.foldcase(), 1);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));
}

// [Boundary] foldcase uses only the least significant bit.
TEST_F(ProgInstTest_391, InitByteRange_FoldcaseUsesLSB_391) {
  const int lo = 'a';
  const int hi = 'z';

  inst_.InitByteRange(lo, hi, /*foldcase=*/2, /*out=*/1);
  EXPECT_EQ(inst_.foldcase(), 0) << "Only LSB should be used (2 & 1 == 0)";

  inst_ = Prog::Inst(); // reset instance
  inst_.InitByteRange(lo, hi, /*foldcase=*/3, /*out=*/1);
  EXPECT_EQ(inst_.foldcase(), 1) << "Only LSB should be used (3 & 1 == 1)";
}

// [Normal] Out field is set (via set_out_opcode); observable through out().
TEST_F(ProgInstTest_391, InitByteRange_SetsOutField_391) {
  const uint32_t out = 987654321u;
  inst_.InitByteRange(10, 20, /*foldcase=*/0, out);

  EXPECT_EQ(inst_.opcode(), kInstByteRange);
  EXPECT_EQ(inst_.out(), static_cast<int>(out));
}
