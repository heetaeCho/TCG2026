#include "gtest/gtest.h"
#include "re2/bitmap256.h"

namespace re2 {

// Test Clear functionality
TEST(Bitmap256Test_387, ClearMakesAllBitsUnset_387) {
  Bitmap256 bitmap;
  bitmap.Set(0);
  bitmap.Set(128);
  bitmap.Set(255);
  bitmap.Clear();
  EXPECT_FALSE(bitmap.Test(0));
  EXPECT_FALSE(bitmap.Test(128));
  EXPECT_FALSE(bitmap.Test(255));
}

// Test default construction - all bits should be unset after Clear
TEST(Bitmap256Test_387, DefaultAfterClear_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap.Test(i)) << "Bit " << i << " should be unset after Clear";
  }
}

// Test Set and Test for a single bit
TEST(Bitmap256Test_387, SetAndTestSingleBit_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(42);
  EXPECT_TRUE(bitmap.Test(42));
}

// Test Set does not affect other bits
TEST(Bitmap256Test_387, SetDoesNotAffectOtherBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(100);
  EXPECT_TRUE(bitmap.Test(100));
  EXPECT_FALSE(bitmap.Test(99));
  EXPECT_FALSE(bitmap.Test(101));
}

// Test boundary: bit 0
TEST(Bitmap256Test_387, SetAndTestBitZero_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(0);
  EXPECT_TRUE(bitmap.Test(0));
  EXPECT_FALSE(bitmap.Test(1));
}

// Test boundary: bit 255
TEST(Bitmap256Test_387, SetAndTestBit255_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(255);
  EXPECT_TRUE(bitmap.Test(255));
  EXPECT_FALSE(bitmap.Test(254));
}

// Test boundary: bit 63 (end of first word)
TEST(Bitmap256Test_387, SetAndTestBit63_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(63);
  EXPECT_TRUE(bitmap.Test(63));
  EXPECT_FALSE(bitmap.Test(62));
  EXPECT_FALSE(bitmap.Test(64));
}

// Test boundary: bit 64 (start of second word)
TEST(Bitmap256Test_387, SetAndTestBit64_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(64);
  EXPECT_TRUE(bitmap.Test(64));
  EXPECT_FALSE(bitmap.Test(63));
  EXPECT_FALSE(bitmap.Test(65));
}

// Test boundary: bit 127
TEST(Bitmap256Test_387, SetAndTestBit127_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(127);
  EXPECT_TRUE(bitmap.Test(127));
}

// Test boundary: bit 128
TEST(Bitmap256Test_387, SetAndTestBit128_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(128);
  EXPECT_TRUE(bitmap.Test(128));
}

// Test boundary: bit 191
TEST(Bitmap256Test_387, SetAndTestBit191_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(191);
  EXPECT_TRUE(bitmap.Test(191));
}

// Test boundary: bit 192
TEST(Bitmap256Test_387, SetAndTestBit192_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(192);
  EXPECT_TRUE(bitmap.Test(192));
}

// Test setting multiple bits
TEST(Bitmap256Test_387, SetMultipleBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(0);
  bitmap.Set(50);
  bitmap.Set(100);
  bitmap.Set(200);
  bitmap.Set(255);
  EXPECT_TRUE(bitmap.Test(0));
  EXPECT_TRUE(bitmap.Test(50));
  EXPECT_TRUE(bitmap.Test(100));
  EXPECT_TRUE(bitmap.Test(200));
  EXPECT_TRUE(bitmap.Test(255));
  EXPECT_FALSE(bitmap.Test(1));
  EXPECT_FALSE(bitmap.Test(51));
  EXPECT_FALSE(bitmap.Test(101));
}

// Test setting all bits
TEST(Bitmap256Test_387, SetAllBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  for (int i = 0; i < 256; i++) {
    bitmap.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_TRUE(bitmap.Test(i)) << "Bit " << i << " should be set";
  }
}

// Test Clear after setting all bits
TEST(Bitmap256Test_387, ClearAfterSettingAllBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  for (int i = 0; i < 256; i++) {
    bitmap.Set(i);
  }
  bitmap.Clear();
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap.Test(i)) << "Bit " << i << " should be unset after Clear";
  }
}

// Test setting the same bit twice
TEST(Bitmap256Test_387, SetSameBitTwice_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(42);
  bitmap.Set(42);
  EXPECT_TRUE(bitmap.Test(42));
}

// Test FindNextSetBit with no bits set
TEST(Bitmap256Test_387, FindNextSetBitNoBitsSet_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  int result = bitmap.FindNextSetBit(0);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit finds the exact bit
TEST(Bitmap256Test_387, FindNextSetBitFindsExactBit_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(50);
  int result = bitmap.FindNextSetBit(50);
  EXPECT_EQ(result, 50);
}

// Test FindNextSetBit finds next bit after given position
TEST(Bitmap256Test_387, FindNextSetBitFindsNextBit_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(100);
  int result = bitmap.FindNextSetBit(50);
  EXPECT_EQ(result, 100);
}

// Test FindNextSetBit when starting from 0
TEST(Bitmap256Test_387, FindNextSetBitFromZero_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(0);
  int result = bitmap.FindNextSetBit(0);
  EXPECT_EQ(result, 0);
}

// Test FindNextSetBit returns -1 when no more bits set after position
TEST(Bitmap256Test_387, FindNextSetBitNoMoreBitsAfterPosition_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(50);
  int result = bitmap.FindNextSetBit(51);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit with bit 255
TEST(Bitmap256Test_387, FindNextSetBitLastBit_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(255);
  int result = bitmap.FindNextSetBit(200);
  EXPECT_EQ(result, 255);
}

// Test FindNextSetBit iterates through all set bits
TEST(Bitmap256Test_387, FindNextSetBitIterateAllSetBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(10);
  bitmap.Set(70);
  bitmap.Set(130);
  bitmap.Set(200);

  int result = bitmap.FindNextSetBit(0);
  EXPECT_EQ(result, 10);

  result = bitmap.FindNextSetBit(11);
  EXPECT_EQ(result, 70);

  result = bitmap.FindNextSetBit(71);
  EXPECT_EQ(result, 130);

  result = bitmap.FindNextSetBit(131);
  EXPECT_EQ(result, 200);

  result = bitmap.FindNextSetBit(201);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit across word boundaries
TEST(Bitmap256Test_387, FindNextSetBitAcrossWordBoundaries_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(63);
  bitmap.Set(64);
  
  int result = bitmap.FindNextSetBit(63);
  EXPECT_EQ(result, 63);
  
  result = bitmap.FindNextSetBit(64);
  EXPECT_EQ(result, 64);
}

// Test FindNextSetBit with all bits in same word
TEST(Bitmap256Test_387, FindNextSetBitSameWord_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(5);
  bitmap.Set(10);
  bitmap.Set(15);
  
  int result = bitmap.FindNextSetBit(0);
  EXPECT_EQ(result, 5);
  
  result = bitmap.FindNextSetBit(6);
  EXPECT_EQ(result, 10);
  
  result = bitmap.FindNextSetBit(11);
  EXPECT_EQ(result, 15);
  
  result = bitmap.FindNextSetBit(16);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit starting from 255 when 255 is set
TEST(Bitmap256Test_387, FindNextSetBitStartAt255Set_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(255);
  int result = bitmap.FindNextSetBit(255);
  EXPECT_EQ(result, 255);
}

// Test FindNextSetBit starting from 255 when 255 is not set
TEST(Bitmap256Test_387, FindNextSetBitStartAt255NotSet_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(254);
  int result = bitmap.FindNextSetBit(255);
  EXPECT_EQ(result, -1);
}

// Test multiple clears
TEST(Bitmap256Test_387, MultipleClearsWork_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  bitmap.Set(100);
  bitmap.Clear();
  bitmap.Clear();
  EXPECT_FALSE(bitmap.Test(100));
}

// Test FindNextSetBit with consecutive bits
TEST(Bitmap256Test_387, FindNextSetBitConsecutiveBits_387) {
  Bitmap256 bitmap;
  bitmap.Clear();
  for (int i = 60; i <= 68; i++) {
    bitmap.Set(i);
  }
  
  int result = bitmap.FindNextSetBit(60);
  EXPECT_EQ(result, 60);
  
  result = bitmap.FindNextSetBit(65);
  EXPECT_EQ(result, 65);
  
  result = bitmap.FindNextSetBit(69);
  EXPECT_EQ(result, -1);
}

}  // namespace re2
