// File: bitmap256_set_test_389.cc
#include <gtest/gtest.h>
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_389 : public ::testing::Test {
protected:
  Bitmap256 bm_;
};

// --- Normal operation ---

// Setting a single bit should make Test(c) return true for that bit.
TEST_F(Bitmap256Test_389, Set_SetsSpecifiedBit_389) {
  bm_.Clear();

  bm_.Set(0);
  EXPECT_TRUE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));   // neighbor remains unaffected

  bm_.Clear();
  bm_.Set(123);
  EXPECT_TRUE(bm_.Test(123));
  EXPECT_FALSE(bm_.Test(122)); // neighbor remains unaffected
  EXPECT_FALSE(bm_.Test(124));
}

// Setting the same bit multiple times should be idempotent (still set, no side effects visible via public API).
TEST_F(Bitmap256Test_389, Set_IsIdempotent_389) {
  bm_.Clear();

  bm_.Set(77);
  bm_.Set(77);
  bm_.Set(77);

  EXPECT_TRUE(bm_.Test(77));
  EXPECT_FALSE(bm_.Test(76));
  EXPECT_FALSE(bm_.Test(78));
}

// Setting multiple bits across word boundaries should work (observable via Test()).
TEST_F(Bitmap256Test_389, Set_MultipleBitsAcrossBoundaries_389) {
  bm_.Clear();

  // Typical 64-bit word boundaries occur at 63/64 and 127/128, etc.
  bm_.Set(63);
  bm_.Set(64);
  bm_.Set(128);

  EXPECT_TRUE(bm_.Test(63));
  EXPECT_TRUE(bm_.Test(64));
  EXPECT_TRUE(bm_.Test(128));

  EXPECT_FALSE(bm_.Test(62));
  EXPECT_FALSE(bm_.Test(65));
  EXPECT_FALSE(bm_.Test(127));
  EXPECT_FALSE(bm_.Test(129));
}

// --- Boundary conditions ---

// Lower bound: 0
TEST_F(Bitmap256Test_389, Set_LowerBoundaryZero_389) {
  bm_.Clear();

  bm_.Set(0);
  EXPECT_TRUE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));
}

// Upper bound: 255
TEST_F(Bitmap256Test_389, Set_UpperBoundary255_389) {
  bm_.Clear();

  bm_.Set(255);
  EXPECT_TRUE(bm_.Test(255));
  EXPECT_FALSE(bm_.Test(254));
}

// --- Interaction with Clear() ---

// After Clear(), previously set bits should no longer be visible via Test().
TEST_F(Bitmap256Test_389, Clear_ResetsAllObservedBits_389) {
  bm_.Clear();

  bm_.Set(0);
  bm_.Set(64);
  bm_.Set(255);

  EXPECT_TRUE(bm_.Test(0));
  EXPECT_TRUE(bm_.Test(64));
  EXPECT_TRUE(bm_.Test(255));

  bm_.Clear();

  // Spot-check a few positions, including ones previously set.
  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(64));
  EXPECT_FALSE(bm_.Test(127));
  EXPECT_FALSE(bm_.Test(128));
  EXPECT_FALSE(bm_.Test(255));
}

// --- Exceptional/error cases (observable via debug assertions) ---

// These rely on ABSL_DCHECK in Set(int). In debug builds, invalid inputs should die.
// EXPECT_DEATH_IF_SUPPORTED gracefully no-ops on platforms/builds without death test support.
#if GTEST_HAS_DEATH_TEST
TEST_F(Bitmap256Test_389, Set_NegativeIndex_Death_389) {
  bm_.Clear();
  EXPECT_DEATH_IF_SUPPORTED(bm_.Set(-1), "");  // message unspecified; we only check that it dies
}

TEST_F(Bitmap256Test_389, Set_IndexAbove255_Death_389) {
  bm_.Clear();
  EXPECT_DEATH_IF_SUPPORTED(bm_.Set(256), "");
}
#endif  // GTEST_HAS_DEATH_TEST

// --- Sanity checks on default/cleared state (observable only through public API) ---

TEST_F(Bitmap256Test_389, DefaultOrClearedState_HasNoObservedBits_389) {
  // Newly constructed or cleared bitmap should have no bits set at checked positions.
  bm_.Clear();
  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(63));
  EXPECT_FALSE(bm_.Test(64));
  EXPECT_FALSE(bm_.Test(128));
  EXPECT_FALSE(bm_.Test(255));
}

}  // namespace re2
