// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xrefentry_getflag_255.cpp

#include <gtest/gtest.h>

#include "poppler/XRef.h"

namespace {

// Helper to avoid depending on specific enumerator names.
static inline Flag FlagFromInt(int v) { return static_cast<Flag>(v); }

class XRefEntryTest_255 : public ::testing::Test {
protected:
  XRefEntry makeEntryZeroed() {
    XRefEntry e{};
    e.flags = 0;
    return e;
  }
};

TEST_F(XRefEntryTest_255, GetFlagReturnsFalseWhenFlagsZero_255) {
  XRefEntry e = makeEntryZeroed();

  EXPECT_FALSE(e.getFlag(FlagFromInt(0)));
  EXPECT_FALSE(e.getFlag(FlagFromInt(1)));
  EXPECT_FALSE(e.getFlag(FlagFromInt(2)));
}

TEST_F(XRefEntryTest_255, SetFlagTrueThenGetFlagTrue_255) {
  XRefEntry e = makeEntryZeroed();

  e.setFlag(FlagFromInt(0), true);

  EXPECT_TRUE(e.getFlag(FlagFromInt(0)));
  EXPECT_FALSE(e.getFlag(FlagFromInt(1)));
}

TEST_F(XRefEntryTest_255, SetFlagFalseClearsPreviouslySetFlag_255) {
  XRefEntry e = makeEntryZeroed();

  e.setFlag(FlagFromInt(0), true);
  ASSERT_TRUE(e.getFlag(FlagFromInt(0)));

  e.setFlag(FlagFromInt(0), false);
  EXPECT_FALSE(e.getFlag(FlagFromInt(0)));
}

TEST_F(XRefEntryTest_255, MultipleFlagsCanBeSetIndependently_255) {
  XRefEntry e = makeEntryZeroed();

  e.setFlag(FlagFromInt(0), true);
  e.setFlag(FlagFromInt(1), true);

  EXPECT_TRUE(e.getFlag(FlagFromInt(0)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(1)));

  // Clearing one should not clear the other.
  e.setFlag(FlagFromInt(0), false);

  EXPECT_FALSE(e.getFlag(FlagFromInt(0)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(1)));
}

TEST_F(XRefEntryTest_255, GetFlagReflectsAllBitsSetWhenFlagsIsMinusOne_255) {
  XRefEntry e = makeEntryZeroed();
  e.flags = -1;

  // For low flag indices, all bits should be set.
  EXPECT_TRUE(e.getFlag(FlagFromInt(0)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(1)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(2)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(3)));
}

TEST_F(XRefEntryTest_255, BoundaryLowFlagIndexDoesNotAffectOtherFlags_255) {
  XRefEntry e = makeEntryZeroed();

  // Set one low flag, confirm neighboring flags remain false.
  e.setFlag(FlagFromInt(1), true);

  EXPECT_FALSE(e.getFlag(FlagFromInt(0)));
  EXPECT_TRUE(e.getFlag(FlagFromInt(1)));
  EXPECT_FALSE(e.getFlag(FlagFromInt(2)));
}

}  // namespace