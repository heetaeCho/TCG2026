#include "gtest/gtest.h"
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_388 : public ::testing::Test {
 protected:
  Bitmap256 bitmap_;
};

// Test that a newly constructed Bitmap256 has no bits set
TEST_F(Bitmap256Test_388, DefaultConstructorAllClear_388) {
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set after construction";
  }
}

// Test setting a single bit and verifying it
TEST_F(Bitmap256Test_388, SetAndTestSingleBit_388) {
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test that setting a bit doesn't affect other bits
TEST_F(Bitmap256Test_388, SetDoesNotAffectOtherBits_388) {
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
TEST_F(Bitmap256Test_388, SetBoundaryMin_388) {
  bitmap_.Set(0);
  EXPECT_TRUE(bitmap_.Test(0));
}

// Test setting the maximum boundary value (255)
TEST_F(Bitmap256Test_388, SetBoundaryMax_388) {
  bitmap_.Set(255);
  EXPECT_TRUE(bitmap_.Test(255));
}

// Test setting multiple bits
TEST_F(Bitmap256Test_388, SetMultipleBits_388) {
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

  // Verify some bits in between are not set
  EXPECT_FALSE(bitmap_.Test(1));
  EXPECT_FALSE(bitmap_.Test(62));
  EXPECT_FALSE(bitmap_.Test(65));
  EXPECT_FALSE(bitmap_.Test(126));
  EXPECT_FALSE(bitmap_.Test(129));
  EXPECT_FALSE(bitmap_.Test(190));
  EXPECT_FALSE(bitmap_.Test(193));
  EXPECT_FALSE(bitmap_.Test(254));
}

// Test setting all bits
TEST_F(Bitmap256Test_388, SetAllBits_388) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_TRUE(bitmap_.Test(i)) << "Bit " << i << " should be set";
  }
}

// Test Clear resets all bits
TEST_F(Bitmap256Test_388, ClearResetsAllBits_388) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  bitmap_.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set after Clear()";
  }
}

// Test Clear on an already empty bitmap
TEST_F(Bitmap256Test_388, ClearOnEmptyBitmap_388) {
  bitmap_.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i));
  }
}

// Test Clear after setting a few bits
TEST_F(Bitmap256Test_388, ClearAfterPartialSet_388) {
  bitmap_.Set(10);
  bitmap_.Set(200);
  bitmap_.Clear();
  EXPECT_FALSE(bitmap_.Test(10));
  EXPECT_FALSE(bitmap_.Test(200));
}

// Test FindNextSetBit finds the first set bit
TEST_F(Bitmap256Test_388, FindNextSetBitFindsFirstBit_388) {
  bitmap_.Set(50);
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, 50);
}

// Test FindNextSetBit starting from the set bit itself
TEST_F(Bitmap256Test_388, FindNextSetBitStartingAtSetBit_388) {
  bitmap_.Set(100);
  int result = bitmap_.FindNextSetBit(100);
  EXPECT_EQ(result, 100);
}

// Test FindNextSetBit returns next set bit when starting past one
TEST_F(Bitmap256Test_388, FindNextSetBitSkipsPreviousBits_388) {
  bitmap_.Set(10);
  bitmap_.Set(200);
  int result = bitmap_.FindNextSetBit(11);
  EXPECT_EQ(result, 200);
}

// Test FindNextSetBit when no bits are set returns -1 or 256 (sentinel)
TEST_F(Bitmap256Test_388, FindNextSetBitNoBitsSet_388) {
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_GE(result, 256);  // Should return 256 or -1 indicating no bit found
}

// Test FindNextSetBit when starting after all set bits
TEST_F(Bitmap256Test_388, FindNextSetBitPastAllSetBits_388) {
  bitmap_.Set(10);
  int result = bitmap_.FindNextSetBit(11);
  EXPECT_GE(result, 256);
}

// Test FindNextSetBit starting from 0 with bit 0 set
TEST_F(Bitmap256Test_388, FindNextSetBitAtZero_388) {
  bitmap_.Set(0);
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, 0);
}

// Test FindNextSetBit with bit 255 set
TEST_F(Bitmap256Test_388, FindNextSetBitAtMax_388) {
  bitmap_.Set(255);
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, 255);
}

// Test FindNextSetBit starting at 255 with bit 255 set
TEST_F(Bitmap256Test_388, FindNextSetBitStartingAtMax_388) {
  bitmap_.Set(255);
  int result = bitmap_.FindNextSetBit(255);
  EXPECT_EQ(result, 255);
}

// Test FindNextSetBit iteration over multiple set bits
TEST_F(Bitmap256Test_388, FindNextSetBitIteratesCorrectly_388) {
  bitmap_.Set(10);
  bitmap_.Set(64);
  bitmap_.Set(128);
  bitmap_.Set(200);

  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, 10);

  result = bitmap_.FindNextSetBit(11);
  EXPECT_EQ(result, 64);

  result = bitmap_.FindNextSetBit(65);
  EXPECT_EQ(result, 128);

  result = bitmap_.FindNextSetBit(129);
  EXPECT_EQ(result, 200);

  result = bitmap_.FindNextSetBit(201);
  EXPECT_GE(result, 256);
}

// Test bits at word boundaries (63, 64, 127, 128, 191, 192)
TEST_F(Bitmap256Test_388, SetBitsAtWordBoundaries_388) {
  bitmap_.Set(63);
  bitmap_.Set(64);
  bitmap_.Set(127);
  bitmap_.Set(128);
  bitmap_.Set(191);
  bitmap_.Set(192);

  EXPECT_TRUE(bitmap_.Test(63));
  EXPECT_TRUE(bitmap_.Test(64));
  EXPECT_TRUE(bitmap_.Test(127));
  EXPECT_TRUE(bitmap_.Test(128));
  EXPECT_TRUE(bitmap_.Test(191));
  EXPECT_TRUE(bitmap_.Test(192));
}

// Test setting the same bit twice doesn't cause issues
TEST_F(Bitmap256Test_388, SetSameBitTwice_388) {
  bitmap_.Set(42);
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test FindNextSetBit with all bits set
TEST_F(Bitmap256Test_388, FindNextSetBitAllBitsSet_388) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    int result = bitmap_.FindNextSetBit(i);
    EXPECT_EQ(result, i) << "FindNextSetBit(" << i << ") should return " << i;
  }
}

// Test FindNextSetBit at word boundary transitions
TEST_F(Bitmap256Test_388, FindNextSetBitCrossesWordBoundary_388) {
  bitmap_.Set(128);
  int result = bitmap_.FindNextSetBit(64);
  EXPECT_EQ(result, 128);
}

// Test Set and Clear cycle
TEST_F(Bitmap256Test_388, SetClearCycle_388) {
  bitmap_.Set(50);
  EXPECT_TRUE(bitmap_.Test(50));
  bitmap_.Clear();
  EXPECT_FALSE(bitmap_.Test(50));
  bitmap_.Set(50);
  EXPECT_TRUE(bitmap_.Test(50));
}

}  // namespace re2
