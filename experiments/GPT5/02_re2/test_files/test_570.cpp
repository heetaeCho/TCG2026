// File: bitmap256_findnextsetbit_test.cc
#include "re2/bitmap256.h"
#include <gtest/gtest.h>

namespace {

using re2::Bitmap256;

class Bitmap256Test_570 : public ::testing::Test {
 protected:
  void SetUp() override {
    bm_.Clear();
  }
  Bitmap256 bm_;
};

// Empty bitmap: should return -1 for any valid c.
TEST_F(Bitmap256Test_570, EmptyReturnsMinusOne_570) {
  const int queries[] = {0, 1, 63, 64, 127, 128, 191, 192, 255};
  for (int c : queries) {
    EXPECT_EQ(bm_.FindNextSetBit(c), -1) << "c=" << c;
  }
}

// Single bit in the same 64-bit word: finds that bit at-or-after c.
TEST_F(Bitmap256Test_570, SingleBitSameWord_570) {
  bm_.Set(5);
  EXPECT_TRUE(bm_.Test(5));

  EXPECT_EQ(bm_.FindNextSetBit(0), 5);   // before -> finds 5
  EXPECT_EQ(bm_.FindNextSetBit(5), 5);   // at -> finds 5
  EXPECT_EQ(bm_.FindNextSetBit(6), -1);  // after with no later bits -> -1
}

// Masking within first word: bits below 'c' in the same word are ignored.
TEST_F(Bitmap256Test_570, MaskIgnoresEarlierBitsInWord_570) {
  bm_.Set(1);
  bm_.Set(10);
  EXPECT_TRUE(bm_.Test(1));
  EXPECT_TRUE(bm_.Test(10));

  EXPECT_EQ(bm_.FindNextSetBit(2), 10);  // bit 1 ignored; next is 10
}

// Cross 64-bit boundary: indices 63 and 64.
TEST_F(Bitmap256Test_570, CrossWordBoundary_63_64_570) {
  bm_.Set(63);
  bm_.Set(64);
  EXPECT_TRUE(bm_.Test(63));
  EXPECT_TRUE(bm_.Test(64));

  EXPECT_EQ(bm_.FindNextSetBit(0), 63);
  EXPECT_EQ(bm_.FindNextSetBit(63), 63);
  EXPECT_EQ(bm_.FindNextSetBit(64), 64);
  EXPECT_EQ(bm_.FindNextSetBit(65), -1);
}

// First set bit only appears in a later word: should scan forward correctly.
TEST_F(Bitmap256Test_570, LaterWordScan_570) {
  bm_.Set(130);  // word index 2 (bits 128..191)
  EXPECT_TRUE(bm_.Test(130));

  EXPECT_EQ(bm_.FindNextSetBit(0), 130);     // finds in later word
  EXPECT_EQ(bm_.FindNextSetBit(129), 130);   // within same later word
  EXPECT_EQ(bm_.FindNextSetBit(131), -1);    // after with no later bits
}

// Highest boundary: bit 255.
TEST_F(Bitmap256Test_570, HighestBit255_570) {
  bm_.Set(255);
  EXPECT_TRUE(bm_.Test(255));

  EXPECT_EQ(bm_.FindNextSetBit(200), 255);
  EXPECT_EQ(bm_.FindNextSetBit(254), 255);
  EXPECT_EQ(bm_.FindNextSetBit(255), 255);
}

// Multiple bits across words: always returns the next set bit at-or-after c.
TEST_F(Bitmap256Test_570, MultipleWordsAndProgression_570) {
  bm_.Set(3);    // word 0
  bm_.Set(70);   // word 1
  bm_.Set(190);  // word 2
  EXPECT_TRUE(bm_.Test(3));
  EXPECT_TRUE(bm_.Test(70));
  EXPECT_TRUE(bm_.Test(190));

  EXPECT_EQ(bm_.FindNextSetBit(0), 3);
  EXPECT_EQ(bm_.FindNextSetBit(4), 70);
  EXPECT_EQ(bm_.FindNextSetBit(70), 70);
  EXPECT_EQ(bm_.FindNextSetBit(71), 190);
  EXPECT_EQ(bm_.FindNextSetBit(191), -1);
}

}  // namespace
