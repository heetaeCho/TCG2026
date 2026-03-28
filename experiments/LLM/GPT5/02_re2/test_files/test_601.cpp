// File: ./TestProjects/re2/re2/bitmap256_test_601.cc
#include "re2/bitmap256.h"
#include <gtest/gtest.h>
#include <vector>

namespace re2 {

class Bitmap256Test_601 : public ::testing::Test {
protected:
  // Helper to probe a few representative bytes to avoid assuming internals.
  static void ExpectAllClearedSamples(const Bitmap256& bm) {
    const int samples[] = {0, 1, 2, 15, 31, 63, 64, 65, 127, 128, 129, 190, 254, 255};
    for (int c : samples) {
      EXPECT_FALSE(bm.Test(c)) << "Bit " << c << " should be clear";
    }
  }
};

// Ensures default construction performs Clear() and nothing is set.
TEST_F(Bitmap256Test_601, DefaultConstructedIsCleared_601) {
  Bitmap256 bm;
  ExpectAllClearedSamples(bm);

  // With no bits set, there should be no "next set bit" from any reasonable start.
  // We only assert the most typical query from 0 to avoid relying on undefined input ranges.
  EXPECT_EQ(-1, bm.FindNextSetBit(0));
}

// Basic Set/Test at the extreme boundaries (0 and 255).
TEST_F(Bitmap256Test_601, SetAndTest_Boundaries_601) {
  Bitmap256 bm;

  bm.Set(0);
  EXPECT_TRUE(bm.Test(0));
  EXPECT_FALSE(bm.Test(1));      // neighbor unaffected

  bm.Set(255);
  EXPECT_TRUE(bm.Test(255));
  EXPECT_FALSE(bm.Test(254));    // neighbor unaffected
}

// FindNextSetBit with a single bit: exact index, before it, and after it.
TEST_F(Bitmap256Test_601, FindNextSetBit_SingleBit_601) {
  Bitmap256 bm;

  bm.Set(128);
  // Starting exactly at the set bit should find it.
  EXPECT_EQ(128, bm.FindNextSetBit(128));
  // Starting before should advance to it.
  EXPECT_EQ(128, bm.FindNextSetBit(0));
  EXPECT_EQ(128, bm.FindNextSetBit(127));
  // Starting after should report no further set bit.
  EXPECT_EQ(-1, bm.FindNextSetBit(129));
  EXPECT_EQ(-1, bm.FindNextSetBit(255));
}

// FindNextSetBit across multiple set bits should progress to the next one >= start.
TEST_F(Bitmap256Test_601, FindNextSetBit_Multiple_Progression_601) {
  Bitmap256 bm;

  bm.Set(10);
  bm.Set(20);
  bm.Set(30);

  EXPECT_EQ(10, bm.FindNextSetBit(0));
  EXPECT_EQ(10, bm.FindNextSetBit(10));
  EXPECT_EQ(20, bm.FindNextSetBit(11));
  EXPECT_EQ(20, bm.FindNextSetBit(20));
  EXPECT_EQ(30, bm.FindNextSetBit(21));
  EXPECT_EQ(30, bm.FindNextSetBit(30));
  EXPECT_EQ(-1, bm.FindNextSetBit(31));
  EXPECT_EQ(-1, bm.FindNextSetBit(255));
}

// Clear should reset all observable state.
TEST_F(Bitmap256Test_601, ClearResetsAll_601) {
  Bitmap256 bm;

  bm.Set(0);
  bm.Set(64);
  bm.Set(255);

  bm.Clear();

  ExpectAllClearedSamples(bm);
  EXPECT_EQ(-1, bm.FindNextSetBit(0));
}

} // namespace re2
