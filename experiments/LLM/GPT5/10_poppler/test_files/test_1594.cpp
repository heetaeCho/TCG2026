// SplashOutBlendColorTest_1594.cc
#include <gtest/gtest.h>

#include "splash/SplashTypes.h"

// NOTE: splashOutBlendColor is a static function in SplashOutputDev.cc.
// To test it (black-box via its public signature/observable side effects),
// we include the .cc directly so the symbol is visible in this TU.
#include "poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendColorTest_1594 : public ::testing::Test {
protected:
  static void Fill(SplashColor &c, unsigned char a, unsigned char b, unsigned char d,
                   unsigned char e) {
    c[0] = a;
    c[1] = b;
    c[2] = d;
    c[3] = e;
  }
};

TEST_F(SplashOutBlendColorTest_1594, Mono8_OnlyWritesBlend0_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 10, 20, 30, 40);
  Fill(dest, 50, 60, 70, 80);
  Fill(blend, 0xAA, 0xBB, 0xCC, 0xDD);

  splashOutBlendColor(src, dest, blend, splashModeMono8);

  // In mono modes, the implementation passes &blend[0] for all three output
  // pointers, so only blend[0] is expected to be written.
  EXPECT_EQ(blend[1], 0xBB);
  EXPECT_EQ(blend[2], 0xCC);
  EXPECT_EQ(blend[3], 0xDD);

  // src/dest should not be modified in mono paths.
  EXPECT_EQ(src[0], 10);
  EXPECT_EQ(src[1], 20);
  EXPECT_EQ(src[2], 30);
  EXPECT_EQ(src[3], 40);

  EXPECT_EQ(dest[0], 50);
  EXPECT_EQ(dest[1], 60);
  EXPECT_EQ(dest[2], 70);
  EXPECT_EQ(dest[3], 80);
}

TEST_F(SplashOutBlendColorTest_1594, Mono1_OnlyWritesBlend0_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 0, 0, 0, 123);
  Fill(dest, 255, 255, 255, 77);
  Fill(blend, 0x11, 0x22, 0x33, 0x44);

  splashOutBlendColor(src, dest, blend, splashModeMono1);

  EXPECT_EQ(blend[1], 0x22);
  EXPECT_EQ(blend[2], 0x33);
  EXPECT_EQ(blend[3], 0x44);

  EXPECT_EQ(src[3], 123);
}

TEST_F(SplashOutBlendColorTest_1594, RGB8_DoesNotTouchSrcAlpha_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 1, 2, 3, 0x17);
  Fill(dest, 4, 5, 6, 0x39);
  Fill(blend, 0xA0, 0xB0, 0xC0, 0xD0);

  splashOutBlendColor(src, dest, blend, splashModeRGB8);

  // RGB8 path should not modify src[3].
  EXPECT_EQ(src[3], 0x17);

  // Only blend[0..2] are provided as outputs in this path; blend[3] should remain.
  EXPECT_EQ(blend[3], 0xD0);
}

TEST_F(SplashOutBlendColorTest_1594, BGR8_DoesNotTouchSrcAlpha_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 9, 8, 7, 0x42);
  Fill(dest, 6, 5, 4, 0x24);
  Fill(blend, 0x01, 0x02, 0x03, 0xFE);

  splashOutBlendColor(src, dest, blend, splashModeBGR8);

  // BGR8 path should not modify src[3].
  EXPECT_EQ(src[3], 0x42);

  // blend[3] is not an output in this path.
  EXPECT_EQ(blend[3], 0xFE);
}

TEST_F(SplashOutBlendColorTest_1594, XBGR8_SetsSrcAlphaTo255_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 10, 20, 30, 0x00);
  Fill(dest, 40, 50, 60, 0x99);
  Fill(blend, 0x10, 0x20, 0x30, 0x40);

  splashOutBlendColor(src, dest, blend, splashModeXBGR8);

  // XBGR8 explicitly sets src[3] = 255 in the provided implementation.
  EXPECT_EQ(src[3], 255);

  // Like RGB/BGR, only blend[0..2] are outputs here; blend[3] should remain.
  EXPECT_EQ(blend[3], 0x40);
}

TEST_F(SplashOutBlendColorTest_1594, CMYK8_Blend3EqualsDest3_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 11, 22, 33, 44);
  Fill(dest, 55, 66, 77, 88);
  Fill(blend, 0xDE, 0xAD, 0xBE, 0xEF);

  splashOutBlendColor(src, dest, blend, splashModeCMYK8);

  // From the visible code: blend[3] ultimately becomes dest[3] (inverted twice).
  EXPECT_EQ(blend[3], dest[3]);

  // CMYK path should not modify inputs.
  EXPECT_EQ(src[0], 11);
  EXPECT_EQ(src[1], 22);
  EXPECT_EQ(src[2], 33);
  EXPECT_EQ(src[3], 44);

  EXPECT_EQ(dest[0], 55);
  EXPECT_EQ(dest[1], 66);
  EXPECT_EQ(dest[2], 77);
  EXPECT_EQ(dest[3], 88);
}

TEST_F(SplashOutBlendColorTest_1594, DeviceN8_Blend3EqualsDest3_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  Fill(src, 200, 150, 100, 50);
  Fill(dest, 10, 20, 30, 40);
  Fill(blend, 0x00, 0x11, 0x22, 0x33);

  splashOutBlendColor(src, dest, blend, splashModeDeviceN8);

  EXPECT_EQ(blend[3], dest[3]);

  // DeviceN8 path should not modify inputs.
  EXPECT_EQ(src[0], 200);
  EXPECT_EQ(src[1], 150);
  EXPECT_EQ(src[2], 100);
  EXPECT_EQ(src[3], 50);

  EXPECT_EQ(dest[0], 10);
  EXPECT_EQ(dest[1], 20);
  EXPECT_EQ(dest[2], 30);
  EXPECT_EQ(dest[3], 40);
}

TEST_F(SplashOutBlendColorTest_1594, CMYK8_BoundaryDest3MinMax_1594) {
  SplashColor src;
  SplashColor dest;
  SplashColor blend;

  // dest[3] = 0 boundary
  Fill(src, 0, 0, 0, 0);
  Fill(dest, 255, 255, 255, 0);
  Fill(blend, 0xAA, 0xBB, 0xCC, 0xDD);
  splashOutBlendColor(src, dest, blend, splashModeCMYK8);
  EXPECT_EQ(blend[3], 0);

  // dest[3] = 255 boundary
  Fill(src, 255, 255, 255, 255);
  Fill(dest, 0, 0, 0, 255);
  Fill(blend, 0x11, 0x22, 0x33, 0x44);
  splashOutBlendColor(src, dest, blend, splashModeCMYK8);
  EXPECT_EQ(blend[3], 255);
}

} // namespace