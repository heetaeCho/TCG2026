// SplashOutputDev_splashOutBlendLuminosity_test_1595.cc
#include <gtest/gtest.h>

#include "splash/SplashTypes.h"

// To unit-test a file-local (static) function, we include the .cc directly
// into this test translation unit.
#include "poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendLuminosityTest_1595 : public ::testing::Test {
protected:
  // Helper to create a 4-byte color buffer (works for RGB/BGR/XBGR/CMYK/DeviceN cases).
  static void Fill4(SplashColorPtr c, unsigned char a, unsigned char b,
                    unsigned char d, unsigned char e) {
    c[0] = a;
    c[1] = b;
    c[2] = d;
    c[3] = e;
  }
};

TEST_F(SplashOutBlendLuminosityTest_1595, Mono8DoesNotTouchOtherBlendBytes_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  // Put distinct values everywhere so we can see what changes.
  Fill4(src, 10, 20, 30, 40);
  Fill4(dest, 1, 2, 3, 4);
  Fill4(blend, 9, 8, 7, 6);

  splashOutBlendLuminosity(src, dest, blend, splashModeMono8);

  // In mono modes, only blend[0] is meaningfully addressed; verify others unchanged.
  EXPECT_EQ(blend[1], 8);
  EXPECT_EQ(blend[2], 7);
  EXPECT_EQ(blend[3], 6);
}

TEST_F(SplashOutBlendLuminosityTest_1595, Mono1DoesNotTouchOtherBlendBytes_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 255, 0, 123, 77);
  Fill4(dest, 0, 255, 11, 22);
  Fill4(blend, 42, 43, 44, 45);

  splashOutBlendLuminosity(src, dest, blend, splashModeMono1);

  EXPECT_EQ(blend[1], 43);
  EXPECT_EQ(blend[2], 44);
  EXPECT_EQ(blend[3], 45);
}

TEST_F(SplashOutBlendLuminosityTest_1595, RGB8DoesNotModifyBlendAlphaByte_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 12, 34, 56, 78);
  Fill4(dest, 90, 87, 65, 43);
  Fill4(blend, 1, 2, 3, 77); // sentinel alpha

  splashOutBlendLuminosity(src, dest, blend, splashModeRGB8);

  // RGB8 path writes only blend[0..2].
  EXPECT_EQ(blend[3], 77);
}

TEST_F(SplashOutBlendLuminosityTest_1595, BGR8DoesNotModifyBlendAlphaByte_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 200, 10, 50, 33);
  Fill4(dest, 5, 6, 7, 8);
  Fill4(blend, 9, 10, 11, 99); // sentinel alpha

  splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);

  EXPECT_EQ(blend[3], 99);
}

TEST_F(SplashOutBlendLuminosityTest_1595, XBGR8ForcesSrcAlphaTo255_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 1, 2, 3, 0);   // alpha intentionally not 255
  Fill4(dest, 9, 8, 7, 6);
  Fill4(blend, 10, 11, 12, 123); // sentinel alpha

  splashOutBlendLuminosity(src, dest, blend, splashModeXBGR8);

  // Observable side effect: XBGR8 sets src[3] = 255.
  EXPECT_EQ(src[3], 255);

  // XBGR8 path writes only blend[0..2].
  EXPECT_EQ(blend[3], 123);
}

TEST_F(SplashOutBlendLuminosityTest_1595, CMYK8PreservesAlphaInBlend_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 0, 128, 255, 200);   // alpha = 200
  Fill4(dest, 10, 20, 30, 40);
  Fill4(blend, 1, 2, 3, 4);

  splashOutBlendLuminosity(src, dest, blend, splashModeCMYK8);

  // Observable via interface: CMYK8 ultimately keeps blend[3] equal to src[3].
  EXPECT_EQ(blend[3], src[3]);
}

TEST_F(SplashOutBlendLuminosityTest_1595, DeviceN8PreservesAlphaInBlend_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 255, 1, 2, 17); // alpha = 17
  Fill4(dest, 3, 4, 5, 6);
  Fill4(blend, 7, 8, 9, 10);

  splashOutBlendLuminosity(src, dest, blend, splashModeDeviceN8);

  EXPECT_EQ(blend[3], src[3]);
}

TEST_F(SplashOutBlendLuminosityTest_1595, AliasingBlendAndDestDoesNotCrashRGB8_1595) {
  SplashColor src{};
  SplashColor dest_and_blend{};

  Fill4(src, 11, 22, 33, 44);
  Fill4(dest_and_blend, 55, 66, 77, 88);

  // Boundary-ish: output buffer aliases dest buffer.
  splashOutBlendLuminosity(src, dest_and_blend, dest_and_blend, splashModeRGB8);

  // Observable invariant from interface usage: alpha byte should remain as it was for RGB8 path.
  EXPECT_EQ(dest_and_blend[3], 88);
}

TEST_F(SplashOutBlendLuminosityTest_1595, ExtremeChannelValuesDoNotModifyBlendAlphaForBGR8_1595) {
  SplashColor src{};
  SplashColor dest{};
  SplashColor blend{};

  Fill4(src, 0, 255, 0, 0);
  Fill4(dest, 255, 0, 255, 255);
  Fill4(blend, 123, 124, 125, 250); // sentinel alpha

  splashOutBlendLuminosity(src, dest, blend, splashModeBGR8);

  EXPECT_EQ(blend[3], 250);
}

} // namespace