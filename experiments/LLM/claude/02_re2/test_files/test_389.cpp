#include "gtest/gtest.h"
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_389 : public ::testing::Test {
 protected:
  Bitmap256 bitmap_;
};

// Test that a freshly constructed Bitmap256 has no bits set
TEST_F(Bitmap256Test_389, DefaultConstructorAllClear_389) {
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set after construction";
  }
}

// Test setting a single bit and verifying it
TEST_F(Bitmap256Test_389, SetSingleBit_389) {
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test that setting a bit doesn't affect other bits
TEST_F(Bitmap256Test_389, SetDoesNotAffectOtherBits_389) {
  bitmap_.Set(100);
  for (int i = 0; i < 256; i++) {
    if (i == 100) {
      EXPECT_TRUE(bitmap_.Test(i));
    } else {
      EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set";
    }
  }
}

// Test setting the minimum boundary value (0)
TEST_F(Bitmap256Test_389, SetBoundaryMin_389) {
  bitmap_.Set(0);
  EXPECT_TRUE(bitmap_.Test(0));
}

// Test setting the maximum boundary value (255)
TEST_F(Bitmap256Test_389, SetBoundaryMax_389) {
  bitmap_.Set(255);
  EXPECT_TRUE(bitmap_.Test(255));
}

// Test setting multiple bits
TEST_F(Bitmap256Test_389, SetMultipleBits_389) {
  bitmap_.Set(0);
  bitmap_.Set(63);
  bitmap_.Set(64);
  bitmap_.Set(127);
  bitmap_.Set(128);
  bitmap_.Set(191);
  bitmap_.Set(192);
  bitmap_.Set(255);

  EXPECT_TRUE(bitmap_.Test(0));
  EXPECT_TRUE(bitmap_.Test(63));
  EXPECT_TRUE(bitmap_.Test(64));
  EXPECT_TRUE(bitmap_.Test(127));
  EXPECT_TRUE(bitmap_.Test(128));
  EXPECT_TRUE(bitmap_.Test(191));
  EXPECT_TRUE(bitmap_.Test(192));
  EXPECT_TRUE(bitmap_.Test(255));

  // Verify some unset bits
  EXPECT_FALSE(bitmap_.Test(1));
  EXPECT_FALSE(bitmap_.Test(62));
  EXPECT_FALSE(bitmap_.Test(65));
  EXPECT_FALSE(bitmap_.Test(130));
}

// Test setting all bits
TEST_F(Bitmap256Test_389, SetAllBits_389) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_TRUE(bitmap_.Test(i)) << "Bit " << i << " should be set";
  }
}

// Test setting the same bit twice is idempotent
TEST_F(Bitmap256Test_389, SetIdempotent_389) {
  bitmap_.Set(50);
  bitmap_.Set(50);
  EXPECT_TRUE(bitmap_.Test(50));
}

// Test Clear resets all bits
TEST_F(Bitmap256Test_389, ClearResetsAllBits_389) {
  bitmap_.Set(0);
  bitmap_.Set(100);
  bitmap_.Set(200);
  bitmap_.Set(255);
  bitmap_.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set after Clear";
  }
}

// Test Clear on already empty bitmap
TEST_F(Bitmap256Test_389, ClearOnEmptyBitmap_389) {
  bitmap_.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i));
  }
}

// Test FindNextSetBit finds the correct next set bit
TEST_F(Bitmap256Test_389, FindNextSetBitBasic_389) {
  bitmap_.Set(10);
  bitmap_.Set(50);
  bitmap_.Set(200);

  int next = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(next, 10);

  next = bitmap_.FindNextSetBit(10);
  EXPECT_EQ(next, 10);

  next = bitmap_.FindNextSetBit(11);
  EXPECT_EQ(next, 50);

  next = bitmap_.FindNextSetBit(50);
  EXPECT_EQ(next, 50);

  next = bitmap_.FindNextSetBit(51);
  EXPECT_EQ(next, 200);

  next = bitmap_.FindNextSetBit(200);
  EXPECT_EQ(next, 200);
}

// Test FindNextSetBit returns 256 when no more bits are set
TEST_F(Bitmap256Test_389, FindNextSetBitNoMoreBits_389) {
  bitmap_.Set(10);
  int next = bitmap_.FindNextSetBit(11);
  EXPECT_EQ(next, 256);
}

// Test FindNextSetBit on empty bitmap
TEST_F(Bitmap256Test_389, FindNextSetBitEmpty_389) {
  int next = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(next, 256);
}

// Test FindNextSetBit starting from 0 with bit 0 set
TEST_F(Bitmap256Test_389, FindNextSetBitAtZero_389) {
  bitmap_.Set(0);
  int next = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(next, 0);
}

// Test FindNextSetBit with bit 255 set
TEST_F(Bitmap256Test_389, FindNextSetBitAtMax_389) {
  bitmap_.Set(255);
  int next = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(next, 255);

  next = bitmap_.FindNextSetBit(255);
  EXPECT_EQ(next, 255);
}

// Test FindNextSetBit past the last set bit
TEST_F(Bitmap256Test_389, FindNextSetBitPastLast_389) {
  bitmap_.Set(255);
  // Starting search from a position beyond any possible set bit
  // The function signature takes int c, searching from c onwards
  // Since 255 is max, searching from 256 should be handled
  // But based on interface, valid range should be 0-255 for input
}

// Test word boundaries for Set (bits 63 and 64 are in different words)
TEST_F(Bitmap256Test_389, SetWordBoundaries_389) {
  bitmap_.Set(63);
  bitmap_.Set(64);
  EXPECT_TRUE(bitmap_.Test(63));
  EXPECT_TRUE(bitmap_.Test(64));
  EXPECT_FALSE(bitmap_.Test(62));
  EXPECT_FALSE(bitmap_.Test(65));
}

// Test second word boundary (127 and 128)
TEST_F(Bitmap256Test_389, SetSecondWordBoundary_389) {
  bitmap_.Set(127);
  bitmap_.Set(128);
  EXPECT_TRUE(bitmap_.Test(127));
  EXPECT_TRUE(bitmap_.Test(128));
  EXPECT_FALSE(bitmap_.Test(126));
  EXPECT_FALSE(bitmap_.Test(129));
}

// Test third word boundary (191 and 192)
TEST_F(Bitmap256Test_389, SetThirdWordBoundary_389) {
  bitmap_.Set(191);
  bitmap_.Set(192);
  EXPECT_TRUE(bitmap_.Test(191));
  EXPECT_TRUE(bitmap_.Test(192));
  EXPECT_FALSE(bitmap_.Test(190));
  EXPECT_FALSE(bitmap_.Test(193));
}

// Test FindNextSetBit across word boundaries
TEST_F(Bitmap256Test_389, FindNextSetBitAcrossWordBoundaries_389) {
  bitmap_.Set(63);
  bitmap_.Set(128);

  int next = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(next, 63);

  next = bitmap_.FindNextSetBit(64);
  EXPECT_EQ(next, 128);
}

// Test FindNextSetBit iteration pattern (iterate all set bits)
TEST_F(Bitmap256Test_389, FindNextSetBitIteration_389) {
  bitmap_.Set(5);
  bitmap_.Set(70);
  bitmap_.Set(135);
  bitmap_.Set(240);

  std::vector<int> found;
  for (int c = bitmap_.FindNextSetBit(0); c < 256; c = bitmap_.FindNextSetBit(c + 1)) {
    found.push_back(c);
  }

  ASSERT_EQ(found.size(), 4u);
  EXPECT_EQ(found[0], 5);
  EXPECT_EQ(found[1], 70);
  EXPECT_EQ(found[2], 135);
  EXPECT_EQ(found[3], 240);
}

// Test Set and Clear cycle
TEST_F(Bitmap256Test_389, SetThenClearThenSet_389) {
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));

  bitmap_.Clear();
  EXPECT_FALSE(bitmap_.Test(42));

  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test bits within each of the four words
TEST_F(Bitmap256Test_389, BitsInEachWord_389) {
  // Word 0: bits 0-63
  bitmap_.Set(30);
  // Word 1: bits 64-127
  bitmap_.Set(90);
  // Word 2: bits 128-191
  bitmap_.Set(150);
  // Word 3: bits 192-255
  bitmap_.Set(220);

  EXPECT_TRUE(bitmap_.Test(30));
  EXPECT_TRUE(bitmap_.Test(90));
  EXPECT_TRUE(bitmap_.Test(150));
  EXPECT_TRUE(bitmap_.Test(220));
}

// Test Test() returns false for unset bit
TEST_F(Bitmap256Test_389, TestReturnsFalseForUnsetBit_389) {
  EXPECT_FALSE(bitmap_.Test(0));
  EXPECT_FALSE(bitmap_.Test(128));
  EXPECT_FALSE(bitmap_.Test(255));
}

}  // namespace re2
