// SplashOutputDev_splashOutBlendDifference_1586_test.cc

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

// Pull in Splash types (SplashColorPtr, SplashColorMode, splashColorModeNComps, etc.).
#include "splash/SplashTypes.h"

// The function under test is `static` inside SplashOutputDev.cc.
// Include the .cc so the test TU can directly call it (no re-declaration needed).
#include "SplashOutputDev.cc"

namespace {

static std::vector<SplashColor> MakeColor(SplashColorMode cm, std::initializer_list<int> vals) {
  const int n = splashColorModeNComps[cm];
  std::vector<SplashColor> out(static_cast<size_t>(n), 0);
  int i = 0;
  for (int v : vals) {
    if (i >= n) break;
    out[static_cast<size_t>(i)] = static_cast<SplashColor>(std::clamp(v, 0, 255));
    ++i;
  }
  return out;
}

static void ExpectVectorEq(const std::vector<SplashColor>& a, const std::vector<SplashColor>& b) {
  ASSERT_EQ(a.size(), b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]) << "index=" << i;
  }
}

} // namespace

TEST(SplashOutBlendDifferenceTest_1586, RGB8_ComputesPerComponentAbsoluteDifference_1586) {
  const SplashColorMode cm = splashModeRGB8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  auto src = MakeColor(cm, {10, 200, 30});
  auto dest = MakeColor(cm, {50, 180, 30});
  std::vector<SplashColor> blend(static_cast<size_t>(n), 0);

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDifference(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior: blend is computed; src/dest remain unchanged for non-CMYK/DeviceN.
  ExpectVectorEq(src, src_before);
  ExpectVectorEq(dest, dest_before);

  for (int i = 0; i < n; ++i) {
    const int s = static_cast<int>(src_before[static_cast<size_t>(i)]);
    const int d = static_cast<int>(dest_before[static_cast<size_t>(i)]);
    const int expected = std::abs(d - s);
    EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), expected) << "comp=" << i;
  }
}

TEST(SplashOutBlendDifferenceTest_1586, RGB8_EqualComponentsYieldZeroBlend_1586) {
  const SplashColorMode cm = splashModeRGB8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  auto src = MakeColor(cm, {0, 127, 255});
  auto dest = src; // identical
  std::vector<SplashColor> blend(static_cast<size_t>(n), 123);

  splashOutBlendDifference(src.data(), dest.data(), blend.data(), cm);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), 0) << "comp=" << i;
  }
}

TEST(SplashOutBlendDifferenceTest_1586, CMYK8_ProducesInvertedDifferenceAndPreservesInputs_1586) {
  const SplashColorMode cm = splashModeCMYK8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  auto src = MakeColor(cm, {0, 128, 255, 64});
  auto dest = MakeColor(cm, {255, 0, 200, 64});
  std::vector<SplashColor> blend(static_cast<size_t>(n), 0);

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDifference(src.data(), dest.data(), blend.data(), cm);

  // The function temporarily mutates for CMYK8 but restores before returning.
  ExpectVectorEq(src, src_before);
  ExpectVectorEq(dest, dest_before);

  // Observable output for CMYK8: per-component value is (255 - abs(dest - src)).
  for (int i = 0; i < n; ++i) {
    const int s = static_cast<int>(src_before[static_cast<size_t>(i)]);
    const int d = static_cast<int>(dest_before[static_cast<size_t>(i)]);
    const int expected = 255 - std::abs(d - s);
    EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), expected) << "comp=" << i;
  }
}

TEST(SplashOutBlendDifferenceTest_1586, CMYK8_BoundaryCasesAtExtremes_1586) {
  const SplashColorMode cm = splashModeCMYK8;
  const int n = splashColorModeNComps[cm];
  ASSERT_GT(n, 0);

  // Make a pattern that includes equal values (expect 255), max-diff (expect 0), and mid-diff.
  auto src = MakeColor(cm, {0, 255, 10, 128});
  auto dest = MakeColor(cm, {0, 0, 255, 200});
  std::vector<SplashColor> blend(static_cast<size_t>(n), 0);

  splashOutBlendDifference(src.data(), dest.data(), blend.data(), cm);

  for (int i = 0; i < n; ++i) {
    const int s = static_cast<int>(src[static_cast<size_t>(i)]);
    const int d = static_cast<int>(dest[static_cast<size_t>(i)]);
    const int expected = 255 - std::abs(d - s);
    EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), expected) << "comp=" << i;
  }
}

TEST(SplashOutBlendDifferenceTest_1586, DeviceN8_ZeroExtraChannelsBecomeZeroBlend_1586) {
  const SplashColorMode cm = splashModeDeviceN8;
  const int n = splashColorModeNComps[cm];
  if (n < 5) {
    GTEST_SKIP() << "DeviceN8 has fewer than 5 components in this build; cannot verify extra channels.";
  }

  // First 4 components: general DeviceN/CMYK-style behavior (255 - abs(d-s)).
  // Extra components (i >= 4): if dest[i]==0 && src[i]==0, blend[i] should be 0.
  std::vector<SplashColor> src(static_cast<size_t>(n), 0);
  std::vector<SplashColor> dest(static_cast<size_t>(n), 0);
  std::vector<SplashColor> blend(static_cast<size_t>(n), 0);

  // Populate first 4 comps with non-trivial values.
  src[0] = 10;  dest[0] = 50;
  src[1] = 200; dest[1] = 180;
  src[2] = 30;  dest[2] = 30;
  src[3] = 0;   dest[3] = 255;

  // Extra comps:
  // - comp 4: both zero -> expect 0
  src[4] = 0; dest[4] = 0;

  // - comp 5 (if present): not both zero -> expect 255 - abs(d-s)
  if (n > 5) {
    src[5] = 1;
    dest[5] = 0;
  }

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDifference(src.data(), dest.data(), blend.data(), cm);

  // Should be restored/preserved after call.
  ExpectVectorEq(src, src_before);
  ExpectVectorEq(dest, dest_before);

  // Verify first 4 comps match (255 - abs(d-s)).
  for (int i = 0; i < std::min(n, 4); ++i) {
    const int s = static_cast<int>(src_before[static_cast<size_t>(i)]);
    const int d = static_cast<int>(dest_before[static_cast<size_t>(i)]);
    const int expected = 255 - std::abs(d - s);
    EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), expected) << "comp=" << i;
  }

  // Verify special-case on extra channels: if both inputs are 0, output is 0.
  EXPECT_EQ(static_cast<int>(blend[4]), 0) << "comp=4";

  // Any other extra channels: still follow the inverted-difference behavior (when not both zero).
  for (int i = 5; i < n; ++i) {
    const int s = static_cast<int>(src_before[static_cast<size_t>(i)]);
    const int d = static_cast<int>(dest_before[static_cast<size_t>(i)]);
    if (s == 0 && d == 0) {
      EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), 0) << "comp=" << i;
    } else {
      const int expected = 255 - std::abs(d - s);
      EXPECT_EQ(static_cast<int>(blend[static_cast<size_t>(i)]), expected) << "comp=" << i;
    }
  }
}