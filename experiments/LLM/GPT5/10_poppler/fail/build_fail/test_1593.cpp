// SplashOutputDev_splashOutBlendSaturation_test_1593.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// Include the implementation file to access the static function under test.
// This is a common pattern for testing internal/translation-unit static helpers.
#include "./TestProjects/poppler/poppler/SplashOutputDev.cc"

namespace {

using Color4 = std::array<unsigned char, 4>;

static Color4 CallBlendSaturation(SplashColorMode cm, const Color4 &srcIn, const Color4 &destIn,
                                  const Color4 &blendInit, Color4 *outSrc, Color4 *outDest) {
  Color4 src = srcIn;
  Color4 dest = destIn;
  Color4 blend = blendInit;

  splashOutBlendSaturation(src.data(), dest.data(), blend.data(), cm);

  if (outSrc) *outSrc = src;
  if (outDest) *outDest = dest;
  return blend;
}

} // namespace

// -------------------- Normal operation --------------------

TEST(SplashOutBlendSaturationTest_1593, Mono8OnlyTouchesBlendChannel0_1593) {
  const Color4 src{{10, 20, 30, 40}};
  const Color4 dest{{200, 210, 220, 230}};
  const Color4 blendInit{{0x11, 0xAA, 0xBB, 0xCC}};

  Color4 srcAfter{}, destAfter{};
  Color4 blendAfter =
      CallBlendSaturation(splashModeMono8, src, dest, blendInit, &srcAfter, &destAfter);

  // src/dest should not be modified for mono modes (observable via pointers).
  EXPECT_EQ(srcAfter, src);
  EXPECT_EQ(destAfter, dest);

  // In mono modes, implementation writes &blend[0] for R/G/B, so only index 0 is targeted.
  EXPECT_EQ(blendAfter[1], blendInit[1]);
  EXPECT_EQ(blendAfter[2], blendInit[2]);
  EXPECT_EQ(blendAfter[3], blendInit[3]);
}

TEST(SplashOutBlendSaturationTest_1593, Mono1OnlyTouchesBlendChannel0_1593) {
  const Color4 src{{0, 0, 0, 0}};
  const Color4 dest{{255, 255, 255, 255}};
  const Color4 blendInit{{0x22, 0x01, 0x02, 0x03}};

  Color4 blendAfter = CallBlendSaturation(splashModeMono1, src, dest, blendInit, nullptr, nullptr);

  EXPECT_EQ(blendAfter[1], blendInit[1]);
  EXPECT_EQ(blendAfter[2], blendInit[2]);
  EXPECT_EQ(blendAfter[3], blendInit[3]);
}

TEST(SplashOutBlendSaturationTest_1593, RGB8DoesNotModifySrcOrDest_1593) {
  const Color4 src{{12, 34, 56, 78}};
  const Color4 dest{{90, 87, 65, 43}};
  const Color4 blendInit{{0xDE, 0xAD, 0xBE, 0xEF}};

  Color4 srcAfter{}, destAfter{};
  (void)CallBlendSaturation(splashModeRGB8, src, dest, blendInit, &srcAfter, &destAfter);

  EXPECT_EQ(srcAfter, src);
  EXPECT_EQ(destAfter, dest);
}

TEST(SplashOutBlendSaturationTest_1593, BGR8DoesNotModifySrcOrDest_1593) {
  const Color4 src{{1, 2, 3, 4}};
  const Color4 dest{{5, 6, 7, 8}};
  const Color4 blendInit{{9, 10, 11, 12}};

  Color4 srcAfter{}, destAfter{};
  (void)CallBlendSaturation(splashModeBGR8, src, dest, blendInit, &srcAfter, &destAfter);

  EXPECT_EQ(srcAfter, src);
  EXPECT_EQ(destAfter, dest);
}

TEST(SplashOutBlendSaturationTest_1593, XBGR8ForcesSrcAlphaTo255_1593) {
  const Color4 src{{100, 110, 120, 0}}; // src[3] should be forced to 255 in XBGR8.
  const Color4 dest{{130, 140, 150, 77}};
  const Color4 blendInit{{0, 1, 2, 3}};

  Color4 srcAfter{};
  (void)CallBlendSaturation(splashModeXBGR8, src, dest, blendInit, &srcAfter, nullptr);

  EXPECT_EQ(srcAfter[3], 255u);
  // Other src channels should remain as provided (only alpha assignment is visible in code path).
  EXPECT_EQ(srcAfter[0], src[0]);
  EXPECT_EQ(srcAfter[1], src[1]);
  EXPECT_EQ(srcAfter[2], src[2]);
}

TEST(SplashOutBlendSaturationTest_1593, RGB8WritesOnlyBlendRGBAndLeavesBlendAlphaUntouched_1593) {
  const Color4 src{{10, 20, 30, 40}};
  const Color4 dest{{200, 150, 100, 50}};
  const Color4 blendInit{{0x10, 0x20, 0x30, 0x99}};

  Color4 blendAfter = CallBlendSaturation(splashModeRGB8, src, dest, blendInit, nullptr, nullptr);

  // The RGB modes write blend[0..2]; alpha (index 3) is not passed to setLum.
  EXPECT_EQ(blendAfter[3], blendInit[3]);
}

// -------------------- Boundary conditions --------------------

TEST(SplashOutBlendSaturationTest_1593, RGB8DeterministicRegardlessOfInitialBlend_1593) {
  const Color4 src{{0, 255, 0, 123}};
  const Color4 dest{{255, 0, 255, 45}};

  const Color4 blendInitA{{0, 0, 0, 0xAA}};
  const Color4 blendInitB{{255, 128, 64, 0xBB}};

  Color4 outA = CallBlendSaturation(splashModeRGB8, src, dest, blendInitA, nullptr, nullptr);
  Color4 outB = CallBlendSaturation(splashModeRGB8, src, dest, blendInitB, nullptr, nullptr);

  // RGB outputs should not depend on prior RGB values in blend since they are written via pointers.
  EXPECT_EQ(outA[0], outB[0]);
  EXPECT_EQ(outA[1], outB[1]);
  EXPECT_EQ(outA[2], outB[2]);
  // Alpha is untouched in RGB8 and may differ because we supplied different initial alpha.
  EXPECT_EQ(outA[3], blendInitA[3]);
  EXPECT_EQ(outB[3], blendInitB[3]);
}

TEST(SplashOutBlendSaturationTest_1593, Mono8DeterministicRegardlessOfInitialBlend_1593) {
  const Color4 src{{255, 0, 0, 0}};
  const Color4 dest{{0, 255, 0, 0}};

  const Color4 blendInitA{{1, 2, 3, 4}};
  const Color4 blendInitB{{200, 201, 202, 203}};

  Color4 outA = CallBlendSaturation(splashModeMono8, src, dest, blendInitA, nullptr, nullptr);
  Color4 outB = CallBlendSaturation(splashModeMono8, src, dest, blendInitB, nullptr, nullptr);

  // Only blend[0] is written; it should be deterministic for the same src/dest.
  EXPECT_EQ(outA[0], outB[0]);

  // Non-written channels should remain whatever they were initialized to.
  EXPECT_EQ(outA[1], blendInitA[1]);
  EXPECT_EQ(outA[2], blendInitA[2]);
  EXPECT_EQ(outA[3], blendInitA[3]);
  EXPECT_EQ(outB[1], blendInitB[1]);
  EXPECT_EQ(outB[2], blendInitB[2]);
  EXPECT_EQ(outB[3], blendInitB[3]);
}

// -------------------- Exceptional / error-like cases (observable) --------------------
// No explicit error reporting is exposed by this interface. We at least validate it handles
// extreme channel values without crashing.

TEST(SplashOutBlendSaturationTest_1593, CMYK8HandlesExtremeValuesWithoutMutatingInputs_1593) {
  const Color4 src{{0, 255, 0, 255}};
  const Color4 dest{{255, 0, 255, 0}};
  const Color4 blendInit{{0xAA, 0xBB, 0xCC, 0xDD}};

  Color4 srcAfter{}, destAfter{};
  (void)CallBlendSaturation(splashModeCMYK8, src, dest, blendInit, &srcAfter, &destAfter);

  EXPECT_EQ(srcAfter, src);
  EXPECT_EQ(destAfter, dest);
}

TEST(SplashOutBlendSaturationTest_1593, DeviceN8HandlesExtremeValuesWithoutMutatingInputs_1593) {
  const Color4 src{{255, 255, 255, 255}};
  const Color4 dest{{0, 0, 0, 0}};
  const Color4 blendInit{{1, 2, 3, 4}};

  Color4 srcAfter{}, destAfter{};
  (void)CallBlendSaturation(splashModeDeviceN8, src, dest, blendInit, &srcAfter, &destAfter);

  EXPECT_EQ(srcAfter, src);
  EXPECT_EQ(destAfter, dest);
}

// -------------------- External interactions --------------------
// None observable: the function is a pure computation over provided buffers and does not accept
// callbacks/handlers. We verify the only observable interaction is buffer mutation.

TEST(SplashOutBlendSaturationTest_1593, XBGR8DoesNotMutateDest_1593) {
  const Color4 src{{9, 8, 7, 6}};
  const Color4 dest{{1, 2, 3, 4}};
  const Color4 blendInit{{0, 0, 0, 0}};

  Color4 destAfter{};
  (void)CallBlendSaturation(splashModeXBGR8, src, dest, blendInit, nullptr, &destAfter);

  EXPECT_EQ(destAfter, dest);
}