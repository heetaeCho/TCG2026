// File: bitmap256_test.cc

#include <gtest/gtest.h>
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_388 : public ::testing::Test {
 protected:
  Bitmap256 bm_;
};

// --- Construction / default state ---

// Verifies that a freshly constructed bitmap has no bits set.
TEST_F(Bitmap256Test_388, DefaultIsAllClear_388) {
  // Sample a spread across the range; we do not assume anything about internals.
  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(63));
  EXPECT_FALSE(bm_.Test(64));
  EXPECT_FALSE(bm_.Test(127));
  EXPECT_FALSE(bm_.Test(128));
  EXPECT_FALSE(bm_.Test(255));
}

// --- Set() / Test() behavior ---

// Setting individual bits should make only those indices report true.
TEST_F(Bitmap256Test_388, SetAndTest_SingleBits_388) {
  bm_.Set(0);
  bm_.Set(63);
  bm_.Set(64);
  bm_.Set(127);
  bm_.Set(128);
  bm_.Set(255);

  // Set bits
  EXPECT_TRUE(bm_.Test(0));
  EXPECT_TRUE(bm_.Test(63));
  EXPECT_TRUE(bm_.Test(64));
  EXPECT_TRUE(bm_.Test(127));
  EXPECT_TRUE(bm_.Test(128));
  EXPECT_TRUE(bm_.Test(255));

  // Neighboring / unrelated bits remain clear (within bounds)
  EXPECT_FALSE(bm_.Test(2));
  EXPECT_FALSE(bm_.Test(62));
  EXPECT_FALSE(bm_.Test(65));
  EXPECT_FALSE(bm_.Test(126));
  EXPECT_FALSE(bm_.Test(129));
  EXPECT_FALSE(bm_.Test(254));
}

// Setting an already-set bit should keep it set (idempotency).
TEST_F(Bitmap256Test_388, IdempotentSet_388) {
  bm_.Set(100);
  EXPECT_TRUE(bm_.Test(100));
  bm_.Set(100);
  EXPECT_TRUE(bm_.Test(100));  // remains set
}

// Boundary indices must be handled correctly.
TEST_F(Bitmap256Test_388, BoundaryIndices_388) {
  bm_.Set(0);
  bm_.Set(255);

  EXPECT_TRUE(bm_.Test(0));
  EXPECT_TRUE(bm_.Test(255));

  // Neighbors (that are valid) remain unaffected
  EXPECT_FALSE(bm_.Test(1));
  EXPECT_FALSE(bm_.Test(254));
}

// --- Clear() behavior ---

// Clear should reset all bits to false.
TEST_F(Bitmap256Test_388, ClearResetsAll_388) {
  // Arrange: set a variety of bits across different 64-bit words.
  bm_.Set(0);
  bm_.Set(63);
  bm_.Set(64);
  bm_.Set(128);
  bm_.Set(255);

  // Act
  bm_.Clear();

  // Assert: sample checks across the range (no assumptions about internals)
  EXPECT_FALSE(bm_.Test(0));
  EXPECT_FALSE(bm_.Test(63));
  EXPECT_FALSE(bm_.Test(64));
  EXPECT_FALSE(bm_.Test(128));
  EXPECT_FALSE(bm_.Test(255));
}

// --- FindNextSetBit() behavior ---
// The following tests validate observable return values from the public API
// without relying on any internal implementation details.

// With no bits set, there should be no next set bit.
TEST_F(Bitmap256Test_388, FindNextSetBit_NoBitsSet_388) {
  // Ensure empty
  bm_.Clear();

  // Expect "no bit found" sentinel; common behavior is -1 for not found.
  // We test this observable behavior via the interface.
  EXPECT_EQ(-1, bm_.FindNextSetBit(0));
  EXPECT_EQ(-1, bm_.FindNextSetBit(128));
  EXPECT_EQ(-1, bm_.FindNextSetBit(255));
}

// If a bit exists at/after the query position, it should be returned.
TEST_F(Bitmap256Test_388, FindNextSetBit_SimpleExact_388) {
  bm_.Clear();
  bm_.Set(10);

  EXPECT_EQ(10, bm_.FindNextSetBit(0));   // finds the first set bit after 0
  EXPECT_EQ(10, bm_.FindNextSetBit(10));  // exact match should return itself
  EXPECT_EQ(-1, bm_.FindNextSetBit(11));  // no bits after 10
}

// Works across 64-bit word boundaries (e.g., 63->64) and later words.
TEST_F(Bitmap256Test_388, FindNextSetBit_CrossWordBoundaries_388) {
  bm_.Clear();
  bm_.Set(63);
  bm_.Set(64);
  bm_.Set(200);

  EXPECT_EQ(63, bm_.FindNextSetBit(0));    // first found
  EXPECT_EQ(64, bm_.FindNextSetBit(64));   // exact boundary index
  EXPECT_EQ(200, bm_.FindNextSetBit(65));  // skips to later set bit
  EXPECT_EQ(-1, bm_.FindNextSetBit(201));  // nothing after 200
}

// Edge at the maximum valid index.
TEST_F(Bitmap256Test_388, FindNextSetBit_AtUpperBound_388) {
  bm_.Clear();
  bm_.Set(255);

  EXPECT_EQ(255, bm_.FindNextSetBit(0));
  EXPECT_EQ(255, bm_.FindNextSetBit(254));
  EXPECT_EQ(255, bm_.FindNextSetBit(255));
  // Do not query with out-of-range indices; behavior is constrained to 0..255.
}

}  // namespace re2
