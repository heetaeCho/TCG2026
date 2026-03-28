// File: bitmap256_test_387.cc
#include <gtest/gtest.h>
#include <cstdint>
#include "re2/bitmap256.h"

using re2::Bitmap256;

// Test fixture for shared setup if needed later.
class Bitmap256Test_387 : public ::testing::Test {
protected:
  Bitmap256 bm_;
};

// Verifies that a newly constructed bitmap has no bits set (observable via Test()).
TEST_F(Bitmap256Test_387, DefaultConstructed_AllBitsClear_387) {
  // Check a few representative positions including boundaries.
  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(127));
  EXPECT_FALSE(bm_.Test(254));
  EXPECT_FALSE(bm_.Test(255));
}

// Verifies Set() makes the target bit observable via Test(), including boundary indices.
TEST_F(Bitmap256Test_387, SetAndTest_BoundaryBits_387) {
  bm_.Set(0);
  bm_.Set(127);
  bm_.Set(255);

  EXPECT_TRUE(bm_.Test(0));
  EXPECT_TRUE(bm_.Test(127));
  EXPECT_TRUE(bm_.Test(255));

  // Neighbor checks (should remain unaffected)
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(126));
  EXPECT_FALSE(bm_.Test(128));
  EXPECT_FALSE(bm_.Test(254));
}

// Verifies that setting the same bit multiple times does not affect other bits.
TEST_F(Bitmap256Test_387, Set_IsIdempotent_PerBit_387) {
  bm_.Set(42);
  bm_.Set(42);  // repeat

  EXPECT_TRUE(bm_.Test(42));
  // Spot-check that unrelated bits remain clear
  EXPECT_FALSE(bm_.Test(41));
  EXPECT_FALSE(bm_.Test(43));
}

// Verifies Clear() makes previously set bits no longer observable via Test().
TEST_F(Bitmap256Test_387, Clear_ResetsAllBits_387) {
  bm_.Set(0);
  bm_.Set(200);
  bm_.Set(255);

  bm_.Clear();

  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(200));
  EXPECT_FALSE(bm_.Test(255));
  // Also spot-check a few random positions
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(127));
  EXPECT_FALSE(bm_.Test(254));
}

// Verifies FindNextSetBit() returns the next set bit at-or-after the query,
// across multiple separated ranges, including boundary behavior.
TEST_F(Bitmap256Test_387, FindNextSetBit_FindsAtOrAfterAndSkipsGaps_387) {
  bm_.Set(5);
  bm_.Set(10);
  bm_.Set(200);

  // Query before first set bit
  EXPECT_EQ(5, bm_.FindNextSetBit(0));

  // Query exactly at a set bit
  EXPECT_EQ(5, bm_.FindNextSetBit(5));

  // Query between set bits should jump forward
  EXPECT_EQ(10, bm_.FindNextSetBit(6));

  // Query exactly at 10
  EXPECT_EQ(10, bm_.FindNextSetBit(10));

  // Query after 10 but before 200
  EXPECT_EQ(200, bm_.FindNextSetBit(11));

  // Query beyond the last set bit should indicate none remain
  EXPECT_EQ(-1, bm_.FindNextSetBit(201));
}

// Verifies FindNextSetBit() near the upper boundary (255) and on empty bitmaps.
TEST_F(Bitmap256Test_387, FindNextSetBit_UpperBoundaryAndEmpty_387) {
  // Empty bitmap: no bits set
  EXPECT_EQ(-1, bm_.FindNextSetBit(0));
  EXPECT_EQ(-1, bm_.FindNextSetBit(128));

  // Set the highest valid bit and query at/just before it
  bm_.Set(255);
  EXPECT_EQ(255, bm_.FindNextSetBit(255)); // at the bit
  EXPECT_EQ(255, bm_.FindNextSetBit(254)); // just before

  // Clear and confirm it returns to empty behavior
  bm_.Clear();
  EXPECT_EQ(-1, bm_.FindNextSetBit(0));
}
