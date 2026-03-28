// File: prog_flatten_test_412.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;
using re2::InstOp;

class ProgFlattenTest_412 : public ::testing::Test {
protected:
  Prog p_;
};

// [412] Default starts are zero; Flatten should keep them consistent (observable).
TEST_F(ProgFlattenTest_412, DefaultStartsRemainValid_412) {
  // Precondition sanity from the public API.
  EXPECT_EQ(p_.start(), 0);
  EXPECT_EQ(p_.start_unanchored(), 0);

  p_.Flatten();

  // Observable postconditions: starts remain valid integers and
  // (from interface perspective) still equal when they began equal at 0.
  EXPECT_GE(p_.start(), 0);
  EXPECT_GE(p_.start_unanchored(), 0);
  EXPECT_EQ(p_.start(), p_.start_unanchored());
}

// [412] Flatten should be idempotent on externally-visible state we can read.
TEST_F(ProgFlattenTest_412, IdempotentOnObservableState_412) {
  // Capture observable state before first Flatten.
  const int start0 = p_.start();
  const int startu0 = p_.start_unanchored();

  p_.Flatten();

  const int size1 = p_.size();
  const int list_count1 = p_.list_count();
  const int start1 = p_.start();
  const int startu1 = p_.start_unanchored();
  const size_t bitmax1 = p_.bit_state_text_max_size();

  // Call Flatten again; observable values should remain stable.
  p_.Flatten();

  EXPECT_EQ(p_.size(), size1);
  EXPECT_EQ(p_.list_count(), list_count1);
  EXPECT_EQ(p_.start(), start1);
  EXPECT_EQ(p_.start_unanchored(), startu1);
  EXPECT_EQ(p_.bit_state_text_max_size(), bitmax1);

  // Starts remained valid integers; if they began equal, they should stay equal.
  EXPECT_EQ(start0, 0);
  EXPECT_EQ(startu0, 0);
  EXPECT_EQ(start1, startu1);
}

// [412] Reversed flag is unrelated to flattening; ensure it is preserved.
TEST_F(ProgFlattenTest_412, PreservesReversedFlag_412) {
  p_.set_reversed(true);
  p_.Flatten();
  EXPECT_TRUE(p_.reversed());

  p_.set_reversed(false);
  p_.Flatten();
  EXPECT_FALSE(p_.reversed());
}

// [412] bit_state_text_max_size is defined for flattened programs.
// Check it’s coherent (non-negative; positive if there are lists).
TEST_F(ProgFlattenTest_412, BitStateMaxSizeIsCoherent_412) {
  p_.Flatten();
  const int lists = p_.list_count();
  const size_t bitmax = p_.bit_state_text_max_size();

  EXPECT_GE(lists, 0);
  // If there are no lists, the max size may be 0; otherwise it should be > 0.
  if (lists > 0) {
    EXPECT_GT(bitmax, 0u);
  } else {
    EXPECT_GE(bitmax, 0u);
  }
}

// [412] Sum of instruction counts across all opcodes equals size() (observable).
TEST_F(ProgFlattenTest_412, InstCountTotalsMatchSize_412) {
  p_.Flatten();

  long long total = 0;
  for (int op = 0; op < re2::kNumInst; ++op) {
    total += p_.inst_count(static_cast<InstOp>(op));
  }
  EXPECT_EQ(total, p_.size());
}

// [412] When starts begin equal and non-zero, they should remain equal afterwards.
TEST_F(ProgFlattenTest_412, EqualStartsRemainEqual_412) {
  // Set equal, non-zero via public API.
  p_.set_start(1);
  p_.set_start_unanchored(1);

  p_.Flatten();

  // Observable: equality preserved (we don’t assume exact values).
  EXPECT_EQ(p_.start(), p_.start_unanchored());
  EXPECT_GE(p_.start(), 0);
}

// [412] When starts begin different and non-zero, they should remain distinguishable.
TEST_F(ProgFlattenTest_412, DifferentStartsRemainDistinguishable_412) {
  // Set distinct, non-zero via public API.
  p_.set_start_unanchored(1);
  p_.set_start(2);

  p_.Flatten();

  // Observable: they are valid indices and not equal.
  EXPECT_GE(p_.start_unanchored(), 0);
  EXPECT_GE(p_.start(), 0);
  EXPECT_NE(p_.start_unanchored(), p_.start());
}
