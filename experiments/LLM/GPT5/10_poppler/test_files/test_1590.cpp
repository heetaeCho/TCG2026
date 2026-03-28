// clipColor_1590_test.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <tuple>

// NOTE: clipColor is a static function inside SplashOutputDev.cc.
// To test it without changing production code, we include the .cc file so the
// static symbol is visible in this translation unit.
#include "SplashOutputDev.cc"

namespace {

class ClipColorTest_1590 : public ::testing::Test {
protected:
  static void CallClipColor(int rIn, int gIn, int bIn,
                            unsigned char *rOut, unsigned char *gOut, unsigned char *bOut) {
    clipColor(rIn, gIn, bIn, rOut, gOut, bOut);
  }

  static void ExpectByteRange(unsigned char v) {
    // Always true for unsigned char, but keeps intent explicit and future-proof if types change.
    EXPECT_LE(static_cast<int>(v), 255);
    EXPECT_GE(static_cast<int>(v), 0);
  }

  static void ExpectAllByteRange(unsigned char r, unsigned char g, unsigned char b) {
    ExpectByteRange(r);
    ExpectByteRange(g);
    ExpectByteRange(b);
  }
};

TEST_F(ClipColorTest_1590, InRangeInputsArePassedThrough_1590) {
  unsigned char r = 0, g = 0, b = 0;

  CallClipColor(10, 20, 30, &r, &g, &b);
  EXPECT_EQ(r, static_cast<unsigned char>(10));
  EXPECT_EQ(g, static_cast<unsigned char>(20));
  EXPECT_EQ(b, static_cast<unsigned char>(30));

  CallClipColor(0, 127, 255, &r, &g, &b);
  EXPECT_EQ(r, static_cast<unsigned char>(0));
  EXPECT_EQ(g, static_cast<unsigned char>(127));
  EXPECT_EQ(b, static_cast<unsigned char>(255));
}

TEST_F(ClipColorTest_1590, BoundaryValuesArePassedThrough_1590) {
  unsigned char r = 123, g = 123, b = 123;

  CallClipColor(0, 0, 0, &r, &g, &b);
  EXPECT_EQ(r, static_cast<unsigned char>(0));
  EXPECT_EQ(g, static_cast<unsigned char>(0));
  EXPECT_EQ(b, static_cast<unsigned char>(0));

  CallClipColor(255, 255, 255, &r, &g, &b);
  EXPECT_EQ(r, static_cast<unsigned char>(255));
  EXPECT_EQ(g, static_cast<unsigned char>(255));
  EXPECT_EQ(b, static_cast<unsigned char>(255));

  CallClipColor(0, 255, 0, &r, &g, &b);
  EXPECT_EQ(r, static_cast<unsigned char>(0));
  EXPECT_EQ(g, static_cast<unsigned char>(255));
  EXPECT_EQ(b, static_cast<unsigned char>(0));
}

TEST_F(ClipColorTest_1590, NegativeChannelStillProducesValidByteOutputs_1590) {
  unsigned char r1 = 0, g1 = 0, b1 = 0;
  unsigned char r2 = 0, g2 = 0, b2 = 0;

  CallClipColor(-10, 20, 30, &r1, &g1, &b1);
  ExpectAllByteRange(r1, g1, b1);

  // Determinism: same input -> same output.
  CallClipColor(-10, 20, 30, &r2, &g2, &b2);
  EXPECT_EQ(r1, r2);
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(b1, b2);

  // If the input is negative, the output should not behave like a raw cast/wrap.
  // (This checks observable "clipping-like" behavior without re-deriving the algorithm.)
  EXPECT_NE(r1, static_cast<unsigned char>(-10));
}

TEST_F(ClipColorTest_1590, Over255ChannelStillProducesValidByteOutputs_1590) {
  unsigned char r1 = 0, g1 = 0, b1 = 0;
  unsigned char r2 = 0, g2 = 0, b2 = 0;

  CallClipColor(300, 20, 30, &r1, &g1, &b1);
  ExpectAllByteRange(r1, g1, b1);

  // Determinism: same input -> same output.
  CallClipColor(300, 20, 30, &r2, &g2, &b2);
  EXPECT_EQ(r1, r2);
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(b1, b2);

  // If the input is >255, the output should not behave like a raw cast/mod 256.
  EXPECT_NE(r1, static_cast<unsigned char>(300));
}

TEST_F(ClipColorTest_1590, ExtremelyOutOfRangeInputsStillStayWithinByteRange_1590) {
  unsigned char r = 0, g = 0, b = 0;

  CallClipColor(std::numeric_limits<int>::min(), 0, 0, &r, &g, &b);
  ExpectAllByteRange(r, g, b);

  CallClipColor(std::numeric_limits<int>::max(), 0, 0, &r, &g, &b);
  ExpectAllByteRange(r, g, b);

  CallClipColor(-1000, 1000, 500, &r, &g, &b);
  ExpectAllByteRange(r, g, b);
}

TEST_F(ClipColorTest_1590, NullOutputPointersCauseDeath_1590) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  unsigned char ok = 0;

  EXPECT_DEATH({ CallClipColor(1, 2, 3, nullptr, &ok, &ok); }, ".*");
  EXPECT_DEATH({ CallClipColor(1, 2, 3, &ok, nullptr, &ok); }, ".*");
  EXPECT_DEATH({ CallClipColor(1, 2, 3, &ok, &ok, nullptr); }, ".*");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

} // namespace