// File: prog_inst_foldcase_test_106.cc

#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;
using re2::InstOp;

class ProgInstFoldcaseTest_106 : public ::testing::Test {};

// [Normal] foldcase() reflects the flag passed to InitByteRange when 0.
TEST(ProgInstFoldcaseTest_106, FoldcaseDisabledReturnsZero_106) {
  Prog::Inst inst;
  // lo/hi/out are arbitrary valid values; behavior under test is foldcase()
  inst.InitByteRange(/*lo=*/'A', /*hi=*/'Z', /*foldcase=*/0, /*out=*/0);
  EXPECT_EQ(inst.foldcase(), 0);
}

// [Normal] foldcase() reflects the flag passed to InitByteRange when 1.
TEST(ProgInstFoldcaseTest_106, FoldcaseEnabledReturnsOne_106) {
  Prog::Inst inst;
  inst.InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/1, /*out=*/0);
  EXPECT_EQ(inst.foldcase(), 1);
}

// [Boundary] Using boundary range values (single-point range) does not
// affect the observable foldcase() result.
TEST(ProgInstFoldcaseTest_106, SinglePointRangeKeepsFoldcaseValue_106) {
  Prog::Inst inst0;
  inst0.InitByteRange(/*lo=*/'A', /*hi=*/'A', /*foldcase=*/0, /*out=*/0);
  EXPECT_EQ(inst0.foldcase(), 0);

  Prog::Inst inst1;
  inst1.InitByteRange(/*lo=*/'z', /*hi=*/'z', /*foldcase=*/1, /*out=*/0);
  EXPECT_EQ(inst1.foldcase(), 1);
}

// [Sanity/Precondition] After InitByteRange, opcode() reports kInstByteRange.
// This ensures foldcase() is called in a valid state per the interface.
TEST(ProgInstFoldcaseTest_106, OpcodeIsByteRangeAfterInitByteRange_106) {
  Prog::Inst inst;
  inst.InitByteRange(/*lo=*/'0', /*hi=*/'9', /*foldcase=*/1, /*out=*/0);
  EXPECT_EQ(inst.opcode(), re2::kInstByteRange);
  // And foldcase() remains consistent.
  EXPECT_EQ(inst.foldcase(), 1);
}

// [Robustness] Different lo/hi values do not change the observable foldcase()
// when the same flag is provided (we only assert on foldcase()).
TEST(ProgInstFoldcaseTest_106, FoldcaseIndependentOfRangeValues_106) {
  Prog::Inst inst_low;
  inst_low.InitByteRange(/*lo=*/0, /*hi=*/127, /*foldcase=*/1, /*out=*/0);
  EXPECT_EQ(inst_low.foldcase(), 1);

  Prog::Inst inst_high;
  inst_high.InitByteRange(/*lo=*/128, /*hi=*/255, /*foldcase=*/1, /*out=*/0);
  EXPECT_EQ(inst_high.foldcase(), 1);
}

}  // namespace
