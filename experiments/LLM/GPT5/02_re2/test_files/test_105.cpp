// File: prog_inst_hi_test_105.cc
#include <gtest/gtest.h>
#include <cstdint>
#include "re2/prog.h"

using namespace re2;

class ProgInstHiTest_105 : public ::testing::Test {
protected:
  Inst makeByteRange(int lo, int hi, int foldcase = 0, uint32_t out = 0) {
    Inst i;
    i.InitByteRange(lo, hi, foldcase, out);
    return i;
  }
};

// Normal operation: InitByteRange sets opcode and hi() returns the provided high bound.
TEST_F(ProgInstHiTest_105, InitByteRange_SetsHiAndOpcode_105) {
  auto inst = makeByteRange(10, 20, /*foldcase=*/0, /*out=*/123);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.hi(), 20);
}

// Boundary: lowest possible high bound (assuming 8-bit storage per header).
TEST_F(ProgInstHiTest_105, HiBoundary_Lowest_0_105) {
  auto inst = makeByteRange(0, 0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.hi(), 0);
}

// Boundary: highest possible high bound (uint8_t -> 255 as suggested by header fields).
TEST_F(ProgInstHiTest_105, HiBoundary_Highest_255_105) {
  auto inst = makeByteRange(0, 255);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.hi(), 255);
}

// Foldcase flag should not affect hi() observable result.
TEST_F(ProgInstHiTest_105, FoldcaseFlag_DoesNotAffectHi_105) {
  auto inst_fold0 = makeByteRange(5, 42, /*foldcase=*/0);
  auto inst_fold1 = makeByteRange(5, 42, /*foldcase=*/1);
  EXPECT_EQ(inst_fold0.hi(), 42);
  EXPECT_EQ(inst_fold1.hi(), 42);
}

// Re-initialization: calling InitByteRange again updates hi().
TEST_F(ProgInstHiTest_105, Reinit_UpdatesHi_105) {
  Inst inst;
  inst.InitByteRange(1, 7, /*foldcase=*/0, /*out=*/0);
  EXPECT_EQ(inst.hi(), 7);
  inst.InitByteRange(1, 9, /*foldcase=*/0, /*out=*/0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.hi(), 9);
}

// Copy semantics: copy-constructed instance preserves hi().
TEST_F(ProgInstHiTest_105, CopyConstructor_PreservesHi_105) {
  auto original = makeByteRange(3, 8);
  Inst copy(original); // uses public copy ctor per interface
  EXPECT_EQ(copy.opcode(), kInstByteRange);
  EXPECT_EQ(copy.hi(), 8);
}

// Interaction with other initializers (observable via public API only):
// After an unrelated init, InitByteRange should still set hi() as expected.
TEST_F(ProgInstHiTest_105, InitAfterOtherOpcode_SetsHi_105) {
  Inst inst;
  inst.InitNop(/*out=*/0); // switch opcode to something else first
  inst.InitByteRange(4, 12, /*foldcase=*/0, /*out=*/0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.hi(), 12);
}
