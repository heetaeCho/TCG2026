#include "gtest/gtest.h"
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_570 : public ::testing::Test {
 protected:
  Bitmap256 bitmap_;

  void SetUp() override {
    bitmap_.Clear();
  }
};

// Test FindNextSetBit on an empty bitmap returns -1
TEST_F(Bitmap256Test_570, FindNextSetBitEmptyBitmap_570) {
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(0));
}

// Test FindNextSetBit returns -1 when no bits are set from position 0
TEST_F(Bitmap256Test_570, FindNextSetBitEmptyFromZero_570) {
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(0));
}

// Test FindNextSetBit returns -1 when no bits are set from position 255
TEST_F(Bitmap256Test_570, FindNextSetBitEmptyFromMax_570) {
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(255));
}

// Test FindNextSetBit finds a bit set at position 0
TEST_F(Bitmap256Test_570, FindNextSetBitAtZero_570) {
  bitmap_.Set(0);
  EXPECT_EQ(0, bitmap_.FindNextSetBit(0));
}

// Test FindNextSetBit finds bit at the exact position queried
TEST_F(Bitmap256Test_570, FindNextSetBitExactPosition_570) {
  bitmap_.Set(42);
  EXPECT_EQ(42, bitmap_.FindNextSetBit(42));
}

// Test FindNextSetBit finds a bit set after the queried position
TEST_F(Bitmap256Test_570, FindNextSetBitAfterQueryPosition_570) {
  bitmap_.Set(100);
  EXPECT_EQ(100, bitmap_.FindNextSetBit(50));
}

// Test FindNextSetBit returns -1 when all set bits are before query position
TEST_F(Bitmap256Test_570, FindNextSetBitAllBitsBefore_570) {
  bitmap_.Set(10);
  bitmap_.Set(20);
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(21));
}

// Test FindNextSetBit at position 255 when bit 255 is set
TEST_F(Bitmap256Test_570, FindNextSetBitAtMax_570) {
  bitmap_.Set(255);
  EXPECT_EQ(255, bitmap_.FindNextSetBit(255));
}

// Test FindNextSetBit at position 255 when bit 255 is not set
TEST_F(Bitmap256Test_570, FindNextSetBitAtMaxNotSet_570) {
  bitmap_.Set(254);
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(255));
}

// Test FindNextSetBit across word boundaries (word 0 -> word 1)
TEST_F(Bitmap256Test_570, FindNextSetBitCrossWordBoundary01_570) {
  bitmap_.Set(70);  // In word 1 (bits 64-127)
  EXPECT_EQ(70, bitmap_.FindNextSetBit(60));  // Start in word 0
}

// Test FindNextSetBit across word boundaries (word 1 -> word 2)
TEST_F(Bitmap256Test_570, FindNextSetBitCrossWordBoundary12_570) {
  bitmap_.Set(140);  // In word 2 (bits 128-191)
  EXPECT_EQ(140, bitmap_.FindNextSetBit(100));  // Start in word 1
}

// Test FindNextSetBit across word boundaries (word 2 -> word 3)
TEST_F(Bitmap256Test_570, FindNextSetBitCrossWordBoundary23_570) {
  bitmap_.Set(200);  // In word 3 (bits 192-255)
  EXPECT_EQ(200, bitmap_.FindNextSetBit(150));  // Start in word 2
}

// Test FindNextSetBit returns the nearest set bit, not a farther one
TEST_F(Bitmap256Test_570, FindNextSetBitReturnsNearest_570) {
  bitmap_.Set(50);
  bitmap_.Set(100);
  bitmap_.Set(200);
  EXPECT_EQ(50, bitmap_.FindNextSetBit(0));
  EXPECT_EQ(50, bitmap_.FindNextSetBit(50));
  EXPECT_EQ(100, bitmap_.FindNextSetBit(51));
  EXPECT_EQ(200, bitmap_.FindNextSetBit(101));
}

// Test FindNextSetBit with multiple bits set in the same word
TEST_F(Bitmap256Test_570, FindNextSetBitMultipleBitsSameWord_570) {
  bitmap_.Set(5);
  bitmap_.Set(10);
  bitmap_.Set(63);
  EXPECT_EQ(5, bitmap_.FindNextSetBit(0));
  EXPECT_EQ(10, bitmap_.FindNextSetBit(6));
  EXPECT_EQ(63, bitmap_.FindNextSetBit(11));
}

// Test FindNextSetBit at word boundary positions (64, 128, 192)
TEST_F(Bitmap256Test_570, FindNextSetBitWordBoundaryPositions_570) {
  bitmap_.Set(64);
  EXPECT_EQ(64, bitmap_.FindNextSetBit(64));

  bitmap_.Set(128);
  EXPECT_EQ(128, bitmap_.FindNextSetBit(128));

  bitmap_.Set(192);
  EXPECT_EQ(192, bitmap_.FindNextSetBit(192));
}

// Test FindNextSetBit at positions just before word boundaries
TEST_F(Bitmap256Test_570, FindNextSetBitJustBeforeWordBoundary_570) {
  bitmap_.Set(63);
  EXPECT_EQ(63, bitmap_.FindNextSetBit(63));

  bitmap_.Set(127);
  EXPECT_EQ(127, bitmap_.FindNextSetBit(127));

  bitmap_.Set(191);
  EXPECT_EQ(191, bitmap_.FindNextSetBit(191));
}

// Test FindNextSetBit starting from word 0 with bit in word 3
TEST_F(Bitmap256Test_570, FindNextSetBitFromWord0ToWord3_570) {
  bitmap_.Set(250);
  EXPECT_EQ(250, bitmap_.FindNextSetBit(0));
}

// Test Set and Test methods
TEST_F(Bitmap256Test_570, SetAndTestBit_570) {
  EXPECT_FALSE(bitmap_.Test(42));
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test Clear method resets all bits
TEST_F(Bitmap256Test_570, ClearResetsAllBits_570) {
  bitmap_.Set(0);
  bitmap_.Set(127);
  bitmap_.Set(255);
  bitmap_.Clear();
  EXPECT_FALSE(bitmap_.Test(0));
  EXPECT_FALSE(bitmap_.Test(127));
  EXPECT_FALSE(bitmap_.Test(255));
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(0));
}

// Test FindNextSetBit with all bits set
TEST_F(Bitmap256Test_570, FindNextSetBitAllBitsSet_570) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(i, bitmap_.FindNextSetBit(i));
  }
}

// Test that setting the same bit twice doesn't cause issues
TEST_F(Bitmap256Test_570, SetSameBitTwice_570) {
  bitmap_.Set(100);
  bitmap_.Set(100);
  EXPECT_TRUE(bitmap_.Test(100));
  EXPECT_EQ(100, bitmap_.FindNextSetBit(100));
}

// Test FindNextSetBit with only bit 0 set, queried from various positions
TEST_F(Bitmap256Test_570, FindNextSetBitOnlyBitZero_570) {
  bitmap_.Set(0);
  EXPECT_EQ(0, bitmap_.FindNextSetBit(0));
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(1));
}

// Test FindNextSetBit with only bit 255 set, queried from various positions
TEST_F(Bitmap256Test_570, FindNextSetBitOnlyBit255_570) {
  bitmap_.Set(255);
  EXPECT_EQ(255, bitmap_.FindNextSetBit(0));
  EXPECT_EQ(255, bitmap_.FindNextSetBit(254));
  EXPECT_EQ(255, bitmap_.FindNextSetBit(255));
}

// Test FindNextSetBit searches correctly within each word
TEST_F(Bitmap256Test_570, FindNextSetBitEachWord_570) {
  bitmap_.Set(10);    // word 0
  bitmap_.Set(80);    // word 1
  bitmap_.Set(150);   // word 2
  bitmap_.Set(220);   // word 3

  EXPECT_EQ(10, bitmap_.FindNextSetBit(0));
  EXPECT_EQ(80, bitmap_.FindNextSetBit(64));
  EXPECT_EQ(150, bitmap_.FindNextSetBit(128));
  EXPECT_EQ(220, bitmap_.FindNextSetBit(192));
}

// Test FindNextSetBit returns -1 when starting after last set bit in word 3
TEST_F(Bitmap256Test_570, FindNextSetBitAfterLastBitInWord3_570) {
  bitmap_.Set(200);
  EXPECT_EQ(-1, bitmap_.FindNextSetBit(201));
}

// Test that Test returns false for unset bits across all words
TEST_F(Bitmap256Test_570, TestReturnsFalseForUnsetBits_570) {
  bitmap_.Set(0);
  bitmap_.Set(255);
  EXPECT_FALSE(bitmap_.Test(1));
  EXPECT_FALSE(bitmap_.Test(128));
  EXPECT_FALSE(bitmap_.Test(254));
}

}  // namespace re2
