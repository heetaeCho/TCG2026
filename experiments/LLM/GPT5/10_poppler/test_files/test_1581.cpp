// File: SplashOutputDev_splashOutBlendLighten_1581_test.cc

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "splash/SplashTypes.h"

// Bring the static function into this test translation unit by including the .cc.
// This allows calling the function without altering production code.
#include "poppler/SplashOutputDev.cc"

namespace {

static std::vector<SplashColor> MakePattern(int nComps, int base) {
  std::vector<SplashColor> v(nComps);
  for (int i = 0; i < nComps; ++i) {
    // Keep within 0..255 and vary per component.
    v[i] = static_cast<SplashColor>((base + i * 37) & 0xFF);
  }
  return v;
}

static void ExpectEqVec(const std::vector<SplashColor> &a,
                        const std::vector<SplashColor> &b) {
  ASSERT_EQ(a.size(), b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]) << "index=" << i;
  }
}

} // namespace

class SplashOutBlendLightenTest_1581 : public ::testing::Test {};

TEST_F(SplashOutBlendLightenTest_1581, RGB8_BlendIsComponentwiseMax_1581) {
  const SplashColorMode cm = splashModeRGB8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  std::vector<SplashColor> src = MakePattern(n, 10);
  std::vector<SplashColor> dest = MakePattern(n, 200);
  std::vector<SplashColor> blend(n, 0);

  const auto src0 = src;
  const auto dest0 = dest;

  splashOutBlendLighten(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior for "Lighten" (RGB): per-component max.
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], std::max(src0[i], dest0[i])) << "comp=" << i;
  }

  // No observable mutation of src/dest for non-CMYK/DeviceN modes.
  ExpectEqVec(src, src0);
  ExpectEqVec(dest, dest0);
}

TEST_F(SplashOutBlendLightenTest_1581, Mono8_BoundaryValues_1581) {
  const SplashColorMode cm = splashModeMono8;
  const int n = splashColorModeNComps[cm];
  ASSERT_EQ(n, 1);

  std::vector<SplashColor> src(n, 0);
  std::vector<SplashColor> dest(n, 255);
  std::vector<SplashColor> blend(n, 123);

  const auto src0 = src;
  const auto dest0 = dest;

  splashOutBlendLighten(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(blend[0], std::max(src0[0], dest0[0]));
  ExpectEqVec(src, src0);
  ExpectEqVec(dest, dest0);
}

TEST_F(SplashOutBlendLightenTest_1581, CMYK8_BlendIsComponentwiseMinAndSrcDestRestored_1581) {
  const SplashColorMode cm = splashModeCMYK8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  std::vector<SplashColor> src = MakePattern(n, 20);
  std::vector<SplashColor> dest = MakePattern(n, 180);
  std::vector<SplashColor> blend(n, 0);

  // Make sure we also include explicit boundaries in a couple components (if possible).
  if (n >= 1) {
    src[0] = 0;
    dest[0] = 255;
  }
  if (n >= 2) {
    src[1] = 255;
    dest[1] = 0;
  }

  const auto src0 = src;
  const auto dest0 = dest;

  splashOutBlendLighten(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior for CMYK implementation: src/dest are inverted internally,
  // then max is taken, then inverted back => equivalent to per-component min in original space.
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], std::min(src0[i], dest0[i])) << "comp=" << i;
  }

  // src/dest should end up restored (inverted twice).
  ExpectEqVec(src, src0);
  ExpectEqVec(dest, dest0);
}

TEST_F(SplashOutBlendLightenTest_1581, DeviceN8_UsesModeComponentCountAndProducesMinPerComponent_1581) {
  const SplashColorMode cm = splashModeDeviceN8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  std::vector<SplashColor> src = MakePattern(n, 5);
  std::vector<SplashColor> dest = MakePattern(n, 250);
  std::vector<SplashColor> blend(n, 0);

  const auto src0 = src;
  const auto dest0 = dest;

  splashOutBlendLighten(src.data(), dest.data(), blend.data(), cm);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], std::min(src0[i], dest0[i])) << "comp=" << i;
  }

  ExpectEqVec(src, src0);
  ExpectEqVec(dest, dest0);
}