#include "gtest/gtest.h"
#include "re2/bitmap256.h"

namespace re2 {

class Bitmap256Test_601 : public ::testing::Test {
 protected:
  Bitmap256 bitmap_;
};

// Test that a newly constructed Bitmap256 has all bits cleared
TEST_F(Bitmap256Test_601, DefaultConstructorAllBitsClear_601) {
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should be clear after construction";
  }
}

// Test setting a single bit and testing it
TEST_F(Bitmap256Test_601, SetAndTestSingleBit_601) {
  bitmap_.Set(42);
  EXPECT_TRUE(bitmap_.Test(42));
}

// Test that setting a bit doesn't affect other bits
TEST_F(Bitmap256Test_601, SetDoesNotAffectOtherBits_601) {
  bitmap_.Set(100);
  for (int i = 0; i < 256; i++) {
    if (i == 100) {
      EXPECT_TRUE(bitmap_.Test(i));
    } else {
      EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should not be set";
    }
  }
}

// Test setting bit 0 (boundary: lowest bit)
TEST_F(Bitmap256Test_601, SetBitZero_601) {
  bitmap_.Set(0);
  EXPECT_TRUE(bitmap_.Test(0));
}

// Test setting bit 255 (boundary: highest bit)
TEST_F(Bitmap256Test_601, SetBit255_601) {
  bitmap_.Set(255);
  EXPECT_TRUE(bitmap_.Test(255));
}

// Test setting multiple bits
TEST_F(Bitmap256Test_601, SetMultipleBits_601) {
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

  // Check some bits that should not be set
  EXPECT_FALSE(bitmap_.Test(1));
  EXPECT_FALSE(bitmap_.Test(62));
  EXPECT_FALSE(bitmap_.Test(65));
  EXPECT_FALSE(bitmap_.Test(126));
  EXPECT_FALSE(bitmap_.Test(129));
  EXPECT_FALSE(bitmap_.Test(190));
  EXPECT_FALSE(bitmap_.Test(193));
  EXPECT_FALSE(bitmap_.Test(254));
}

// Test Clear resets all bits
TEST_F(Bitmap256Test_601, ClearResetsAllBits_601) {
  // Set several bits
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  // Verify they're all set
  for (int i = 0; i < 256; i++) {
    EXPECT_TRUE(bitmap_.Test(i));
  }
  // Clear
  bitmap_.Clear();
  // Verify they're all cleared
  for (int i = 0; i < 256; i++) {
    EXPECT_FALSE(bitmap_.Test(i)) << "Bit " << i << " should be clear after Clear()";
  }
}

// Test setting all 256 bits
TEST_F(Bitmap256Test_601, SetAllBits_601) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_TRUE(bitmap_.Test(i)) << "Bit " << i << " should be set";
  }
}

// Test FindNextSetBit with no bits set
TEST_F(Bitmap256Test_601, FindNextSetBitNoBitsSet_601) {
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit finds the only set bit
TEST_F(Bitmap256Test_601, FindNextSetBitFindsOnlySetBit_601) {
  bitmap_.Set(100);
  int result = bitmap_.FindNextSetBit(0);
  EXPECT_EQ(result, 100);
}

// Test FindNextSetBit starting from the set bit itself
TEST_F(Bitmap256Test_601, FindNextSetBitStartingFromSetBit_601) {
  bitmap_.Set(50);
  int result = bitmap_.FindNextSetBit(50);
  EXPECT_EQ(result, 50);
}

// Test FindNextSetBit starting after the set bit returns -1
TEST_F(Bitmap256Test_601, FindNextSetBitStartingAfterSetBit_601) {
  bitmap_.Set(50);
  int result = bitmap_.FindNextSetBit(51);
  EXPECT_EQ(result, -1);
}

// Test FindNextSetBit with multiple bits set
TEST_F(Bitmap256Test_601, FindNextSetBitMultipleBits_601) {
  bitmap_.Set(10);
  bitmap_.Set(100);
  bitmap_.Set(200);

  EXPECT_EQ(bitmap_.FindNextSetBit(0), 10);
  EXPECT_EQ(bitmap_.FindNextSetBit(10), 10);
  EXPECT_EQ(bitmap_.FindNextSetBit(11), 100);
  EXPECT_EQ(bitmap_.FindNextSetBit(100), 100);
  EXPECT_EQ(bitmap_.FindNextSetBit(101), 200);
  EXPECT_EQ(bitmap_.FindNextSetBit(200), 200);
  EXPECT_EQ(bitmap_.FindNextSetBit(201), -1);
}

// Test FindNextSetBit at word boundaries (0, 64, 128, 192)
TEST_F(Bitmap256Test_601, FindNextSetBitAtWordBoundaries_601) {
  bitmap_.Set(0);
  bitmap_.Set(64);
  bitmap_.Set(128);
  bitmap_.Set(192);

  EXPECT_EQ(bitmap_.FindNextSetBit(0), 0);
  EXPECT_EQ(bitmap_.FindNextSetBit(1), 64);
  EXPECT_EQ(bitmap_.FindNextSetBit(64), 64);
  EXPECT_EQ(bitmap_.FindNextSetBit(65), 128);
  EXPECT_EQ(bitmap_.FindNextSetBit(128), 128);
  EXPECT_EQ(bitmap_.FindNextSetBit(129), 192);
  EXPECT_EQ(bitmap_.FindNextSetBit(192), 192);
  EXPECT_EQ(bitmap_.FindNextSetBit(193), -1);
}

// Test FindNextSetBit at end of word boundaries (63, 127, 191, 255)
TEST_F(Bitmap256Test_601, FindNextSetBitAtEndOfWordBoundaries_601) {
  bitmap_.Set(63);
  bitmap_.Set(127);
  bitmap_.Set(191);
  bitmap_.Set(255);

  EXPECT_EQ(bitmap_.FindNextSetBit(0), 63);
  EXPECT_EQ(bitmap_.FindNextSetBit(63), 63);
  EXPECT_EQ(bitmap_.FindNextSetBit(64), 127);
  EXPECT_EQ(bitmap_.FindNextSetBit(127), 127);
  EXPECT_EQ(bitmap_.FindNextSetBit(128), 191);
  EXPECT_EQ(bitmap_.FindNextSetBit(191), 191);
  EXPECT_EQ(bitmap_.FindNextSetBit(192), 255);
  EXPECT_EQ(bitmap_.FindNextSetBit(255), 255);
}

// Test FindNextSetBit with bit 255 set
TEST_F(Bitmap256Test_601, FindNextSetBitLastBit_601) {
  bitmap_.Set(255);
  EXPECT_EQ(bitmap_.FindNextSetBit(0), 255);
  EXPECT_EQ(bitmap_.FindNextSetBit(255), 255);
}

// Test FindNextSetBit with bit 0 set
TEST_F(Bitmap256Test_601, FindNextSetBitFirstBit_601) {
  bitmap_.Set(0);
  EXPECT_EQ(bitmap_.FindNextSetBit(0), 0);
  EXPECT_EQ(bitmap_.FindNextSetBit(1), -1);
}

// Test setting the same bit twice doesn't cause issues
TEST_F(Bitmap256Test_601, SetSameBitTwice_601) {
  bitmap_.Set(77);
  bitmap_.Set(77);
  EXPECT_TRUE(bitmap_.Test(77));
}

// Test iterating through all set bits using FindNextSetBit
TEST_F(Bitmap256Test_601, IterateAllSetBits_601) {
  std::vector<int> expected = {5, 33, 64, 99, 128, 200, 255};
  for (int bit : expected) {
    bitmap_.Set(bit);
  }

  std::vector<int> found;
  for (int c = bitmap_.FindNextSetBit(0); c != -1; c = bitmap_.FindNextSetBit(c + 1)) {
    found.push_back(c);
  }

  EXPECT_EQ(found, expected);
}

// Test Clear followed by Set works properly
TEST_F(Bitmap256Test_601, ClearThenSet_601) {
  bitmap_.Set(50);
  bitmap_.Clear();
  EXPECT_FALSE(bitmap_.Test(50));
  bitmap_.Set(100);
  EXPECT_TRUE(bitmap_.Test(100));
  EXPECT_FALSE(bitmap_.Test(50));
}

// Test FindNextSetBit with all bits set
TEST_F(Bitmap256Test_601, FindNextSetBitAllBitsSet_601) {
  for (int i = 0; i < 256; i++) {
    bitmap_.Set(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bitmap_.FindNextSetBit(i), i);
  }
}

// Test FindNextSetBit consecutive bits
TEST_F(Bitmap256Test_601, FindNextSetBitConsecutiveBits_601) {
  bitmap_.Set(62);
  bitmap_.Set(63);
  bitmap_.Set(64);
  bitmap_.Set(65);

  EXPECT_EQ(bitmap_.FindNextSetBit(0), 62);
  EXPECT_EQ(bitmap_.FindNextSetBit(62), 62);
  EXPECT_EQ(bitmap_.FindNextSetBit(63), 63);
  EXPECT_EQ(bitmap_.FindNextSetBit(64), 64);
  EXPECT_EQ(bitmap_.FindNextSetBit(65), 65);
  EXPECT_EQ(bitmap_.FindNextSetBit(66), -1);
}

}  // namespace re2
