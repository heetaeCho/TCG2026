// SplashOutputDev_softlight_unittest_1585.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

// Pull in SplashColorMode and splashColorModeNComps.
// (Path matches the prompt's repository layout.)
#include "splash/SplashTypes.h"

// We need to test a TU-local (static) function. The most reliable black-box way
// is to compile the production implementation into this test translation unit.
// This is NOT re-implementing logic; it is directly exercising the real code.
#include "poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendSoftLightTest_1585 : public ::testing::Test {
protected:
  static int nComps(SplashColorMode cm) {
    // splashColorModeNComps is provided by SplashTypes.h (as per prompt).
    return splashColorModeNComps[cm];
  }

  static std::vector<unsigned char> MakeColor(SplashColorMode cm,
                                              std::initializer_list<int> vals,
                                              int extraSentinelBytes = 2,
                                              unsigned char sentinel = 0xA5) {
    const int comps = nComps(cm);
    std::vector<unsigned char> buf(static_cast<size_t>(comps + extraSentinelBytes), sentinel);
    int i = 0;
    for (int v : vals) {
      if (i >= comps) break;
      buf[static_cast<size_t>(i)] = static_cast<unsigned char>(v);
      ++i;
    }
    // If fewer vals than comps, fill remaining components with a simple pattern.
    for (; i < comps; ++i) {
      buf[static_cast<size_t>(i)] = static_cast<unsigned char>((17 * i) & 0xFF);
    }
    return buf;
  }

  static void ExpectSentinelUnchanged(const std::vector<unsigned char>& buf,
                                      int comps,
                                      unsigned char sentinel = 0xA5) {
    ASSERT_GE(static_cast<int>(buf.size()), comps);
    for (size_t i = static_cast<size_t>(comps); i < buf.size(); ++i) {
      EXPECT_EQ(buf[i], sentinel) << "Sentinel byte modified at index " << i;
    }
  }
};

TEST_F(SplashOutBlendSoftLightTest_1585, DoesNotModifySrcOrDest_AllColorModes_1585) {
  const std::array<SplashColorMode, 7> modes = {
      splashModeMono1, splashModeMono8, splashModeRGB8,  splashModeBGR8,
      splashModeXBGR8, splashModeCMYK8, splashModeDeviceN8};

  for (SplashColorMode cm : modes) {
    const int comps = nComps(cm);
    ASSERT_GT(comps, 0) << "Expected at least 1 component for mode " << static_cast<int>(cm);

    auto src = MakeColor(cm, {0, 0x7F, 0x80, 0xFF});
    auto dest = MakeColor(cm, {0xFF, 0x80, 0x7F, 0x00});
    auto blend = MakeColor(cm, {0x11, 0x22, 0x33, 0x44});  // initial contents shouldn't matter

    std::vector<unsigned char> srcBefore = src;
    std::vector<unsigned char> destBefore = dest;

    splashOutBlendSoftLight(src.data(), dest.data(), blend.data(), cm);

    EXPECT_EQ(src, srcBefore) << "src modified for mode " << static_cast<int>(cm);
    EXPECT_EQ(dest, destBefore) << "dest modified for mode " << static_cast<int>(cm);

    // Also verify we didn't write past the component count into the sentinel.
    ExpectSentinelUnchanged(src, comps);
    ExpectSentinelUnchanged(dest, comps);
    ExpectSentinelUnchanged(blend, comps);
  }
}

TEST_F(SplashOutBlendSoftLightTest_1585, DeterministicOutput_SameInputsSameBlend_1585) {
  const std::array<SplashColorMode, 7> modes = {
      splashModeMono1, splashModeMono8, splashModeRGB8,  splashModeBGR8,
      splashModeXBGR8, splashModeCMYK8, splashModeDeviceN8};

  for (SplashColorMode cm : modes) {
    auto src1 = MakeColor(cm, {3, 42, 128, 250});
    auto dest1 = MakeColor(cm, {250, 128, 42, 3});
    auto blend1 = MakeColor(cm, {0, 0, 0, 0});

    auto src2 = src1;
    auto dest2 = dest1;
    auto blend2 = MakeColor(cm, {0, 0, 0, 0});

    splashOutBlendSoftLight(src1.data(), dest1.data(), blend1.data(), cm);
    splashOutBlendSoftLight(src2.data(), dest2.data(), blend2.data(), cm);

    EXPECT_EQ(blend1, blend2) << "Non-deterministic output for mode " << static_cast<int>(cm);
  }
}

TEST_F(SplashOutBlendSoftLightTest_1585, RespectsComponentCount_DoesNotTouchBeyondNComps_1585) {
  // Focus on modes commonly having >1 components.
  const std::array<SplashColorMode, 4> modes = {splashModeRGB8, splashModeBGR8, splashModeCMYK8,
                                                splashModeDeviceN8};

  for (SplashColorMode cm : modes) {
    const int comps = nComps(cm);
    ASSERT_GT(comps, 0);

    // Put distinct sentinel bytes beyond the component range to detect overruns.
    auto src = MakeColor(cm, {10, 20, 30, 40}, /*extraSentinelBytes=*/5, /*sentinel=*/0x5A);
    auto dest = MakeColor(cm, {200, 180, 160, 140}, /*extraSentinelBytes=*/5, /*sentinel=*/0x5A);
    std::vector<unsigned char> blend(static_cast<size_t>(comps + 5), 0x5A);

    splashOutBlendSoftLight(src.data(), dest.data(), blend.data(), cm);

    ExpectSentinelUnchanged(src, comps, 0x5A);
    ExpectSentinelUnchanged(dest, comps, 0x5A);
    ExpectSentinelUnchanged(blend, comps, 0x5A);
  }
}

TEST_F(SplashOutBlendSoftLightTest_1585, SameDataSameBlendForSameComponentCount_RGB8vsBGR8_1585) {
  // The function operates per-component; with identical component arrays and the same component
  // count, output should match regardless of channel-order semantics outside this function.
  ASSERT_EQ(nComps(splashModeRGB8), nComps(splashModeBGR8));
  const int comps = nComps(splashModeRGB8);
  ASSERT_GT(comps, 0);

  auto srcRGB = MakeColor(splashModeRGB8, {12, 128, 250});
  auto destRGB = MakeColor(splashModeRGB8, {250, 128, 12});
  auto blendRGB = MakeColor(splashModeRGB8, {0, 0, 0});

  auto srcBGR = srcRGB;   // same bytes
  auto destBGR = destRGB; // same bytes
  auto blendBGR = MakeColor(splashModeBGR8, {0, 0, 0});

  splashOutBlendSoftLight(srcRGB.data(), destRGB.data(), blendRGB.data(), splashModeRGB8);
  splashOutBlendSoftLight(srcBGR.data(), destBGR.data(), blendBGR.data(), splashModeBGR8);

  // Compare only the computed component range; ignore sentinels.
  ASSERT_GE(static_cast<int>(blendRGB.size()), comps);
  ASSERT_GE(static_cast<int>(blendBGR.size()), comps);
  EXPECT_TRUE(std::equal(blendRGB.begin(), blendRGB.begin() + comps, blendBGR.begin()))
      << "Blend differs between RGB8 and BGR8 for identical component bytes";
}

TEST_F(SplashOutBlendSoftLightTest_1585, HandlesBoundaryInputValues_NoCrash_AllModes_1585) {
  const std::array<SplashColorMode, 7> modes = {
      splashModeMono1, splashModeMono8, splashModeRGB8,  splashModeBGR8,
      splashModeXBGR8, splashModeCMYK8, splashModeDeviceN8};

  // Boundary values around 0x80 branch point and extremes.
  const std::array<int, 6> vals = {0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF};

  for (SplashColorMode cm : modes) {
    const int comps = nComps(cm);
    ASSERT_GT(comps, 0);

    for (int s : vals) {
      for (int d : vals) {
        auto src = MakeColor(cm, {s, s, s, s});
        auto dest = MakeColor(cm, {d, d, d, d});
        auto blend = MakeColor(cm, {0, 0, 0, 0});

        // Primary observable expectation here is simply: call succeeds and stays in-bounds
        // (sentinel check).
        splashOutBlendSoftLight(src.data(), dest.data(), blend.data(), cm);
        ExpectSentinelUnchanged(src, comps);
        ExpectSentinelUnchanged(dest, comps);
        ExpectSentinelUnchanged(blend, comps);
      }
    }
  }
}

} // namespace