// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for XRefEntry::setFlag
//
// File: xrefentry_setflag_test_256.cpp

#include <gtest/gtest.h>

#include "poppler/XRef.h"

namespace {

class XRefEntryTest_256 : public ::testing::Test {
 protected:
  // Helper to get a "flag" value without relying on specific enumerators.
  // We intentionally only use small indices to avoid undefined shifts.
  static auto FlagAt(int idx) -> decltype(XRefEntry::Flag{}) {
    return static_cast<XRefEntry::Flag>(idx);
  }
};

TEST_F(XRefEntryTest_256, SetFlagTrueSetsCorrespondingBit_256) {
  XRefEntry entry{};
  entry.flags = 0;

  const auto f0 = FlagAt(0);
  entry.setFlag(f0, true);

  EXPECT_EQ(entry.flags, 1);
}

TEST_F(XRefEntryTest_256, SetFlagFalseClearsCorrespondingBit_256) {
  XRefEntry entry{};
  // Pre-set some bits (including bit 0).
  entry.flags = 0b1011;

  const auto f0 = FlagAt(0);
  entry.setFlag(f0, false);

  EXPECT_EQ(entry.flags, 0b1010);
}

TEST_F(XRefEntryTest_256, SettingSameFlagTrueIsIdempotent_256) {
  XRefEntry entry{};
  entry.flags = 0;

  const auto f1 = FlagAt(1);
  entry.setFlag(f1, true);
  const int after_first = entry.flags;

  entry.setFlag(f1, true);
  EXPECT_EQ(entry.flags, after_first);
  EXPECT_EQ(entry.flags, (1 << 1));
}

TEST_F(XRefEntryTest_256, ClearingAlreadyClearedFlagDoesNotChangeOtherBits_256) {
  XRefEntry entry{};
  entry.flags = 0b1100;  // bits 2 and 3 set, bit 0 clear.

  const auto f0 = FlagAt(0);
  entry.setFlag(f0, false);

  EXPECT_EQ(entry.flags, 0b1100);
}

TEST_F(XRefEntryTest_256, SetFlagDoesNotAffectOtherBitsWhenSetting_256) {
  XRefEntry entry{};
  entry.flags = 0b1000;  // bit 3 set

  const auto f1 = FlagAt(1);
  entry.setFlag(f1, true);

  EXPECT_EQ(entry.flags, 0b1010);  // bit 3 preserved, bit 1 set
}

TEST_F(XRefEntryTest_256, SetFlagDoesNotAffectOtherBitsWhenClearing_256) {
  XRefEntry entry{};
  entry.flags = 0b1111;  // bits 0..3 set

  const auto f2 = FlagAt(2);
  entry.setFlag(f2, false);

  EXPECT_EQ(entry.flags, 0b1011);  // only bit 2 cleared
}

TEST_F(XRefEntryTest_256, CanIndependentlyToggleTwoDifferentFlags_256) {
  XRefEntry entry{};
  entry.flags = 0;

  const auto f0 = FlagAt(0);
  const auto f1 = FlagAt(1);

  entry.setFlag(f0, true);
  entry.setFlag(f1, true);
  EXPECT_EQ(entry.flags, 0b0011);

  entry.setFlag(f0, false);
  EXPECT_EQ(entry.flags, 0b0010);

  entry.setFlag(f1, false);
  EXPECT_EQ(entry.flags, 0);
}

}  // namespace