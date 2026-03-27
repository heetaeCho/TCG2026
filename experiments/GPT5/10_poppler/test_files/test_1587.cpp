// TEST_ID = 1587
// Unit tests for splashOutBlendExclusion (static in SplashOutputDev.cc)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "./TestProjects/poppler/splash/SplashTypes.h"

// The function under test is `static` inside SplashOutputDev.cc.
// Include the .cc so the symbol is available in this translation unit.
#include "./TestProjects/poppler/poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendExclusionTest_1587 : public ::testing::Test {
protected:
  static int nComps(SplashColorMode cm) {
    return ::splashColorModeNComps[cm];
  }

  static std::vector<uint8_t> makeColor(SplashColorMode cm, std::initializer_list<int> vals) {
    std::vector<uint8_t> c(static_cast<size_t>(nComps(cm)), 0);
    size_t i = 0;
    for (int v : vals) {
      if (i >= c.size()) break;
      c[i++] = static_cast<uint8_t>(std::clamp(v, 0, 255));
    }
    return c;
  }
};

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_ComputesExpectedBlendAndPreservesInputs_1587) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(nComps(cm), 3);

  auto dest = makeColor(cm, {10, 20, 30});
  auto src  = makeColor(cm, {40, 50, 60});
  std::vector<uint8_t> blend(dest.size(), 0);

  const auto destBefore = dest;
  const auto srcBefore  = src;

  splashOutBlendExclusion(src.data(), dest.data(), blend.data(), cm);

  // Expected values for these specific inputs (checked as a black-box “golden” case).
  EXPECT_EQ(blend[0], 47);
  EXPECT_EQ(blend[1], 63);
  EXPECT_EQ(blend[2], 76);

  // For RGB8, src/dest should not be modified by the call.
  EXPECT_EQ(dest, destBefore);
  EXPECT_EQ(src, srcBefore);
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_BoundarySrcAllZeroActsAsIdentity_1587) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(nComps(cm), 3);

  auto dest = makeColor(cm, {0, 128, 255});
  auto src  = makeColor(cm, {0, 0, 0});
  std::vector<uint8_t> blend(dest.size(), 123);

  const auto destBefore = dest;
  const auto srcBefore  = src;

  splashOutBlendExclusion(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(blend[0], destBefore[0]);
  EXPECT_EQ(blend[1], destBefore[1]);
  EXPECT_EQ(blend[2], destBefore[2]);

  EXPECT_EQ(dest, destBefore);
  EXPECT_EQ(src, srcBefore);
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_BoundarySrcAll255InvertsDest_1587) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(nComps(cm), 3);

  auto dest = makeColor(cm, {0, 1, 254});
  auto src  = makeColor(cm, {255, 255, 255});
  std::vector<uint8_t> blend(dest.size(), 0);

  const auto destBefore = dest;
  const auto srcBefore  = src;

  splashOutBlendExclusion(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(blend[0], 255);
  EXPECT_EQ(blend[1], 254);
  EXPECT_EQ(blend[2], 1);

  EXPECT_EQ(dest, destBefore);
  EXPECT_EQ(src, srcBefore);
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_SwappingSrcAndDestProducesSameBlend_1587) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(nComps(cm), 3);

  auto a = makeColor(cm, {12, 34, 56});
  auto b = makeColor(cm, {78, 90, 123});

  std::vector<uint8_t> blendAB(3, 0);
  std::vector<uint8_t> blendBA(3, 0);

  {
    auto dest = a;
    auto src = b;
    splashOutBlendExclusion(src.data(), dest.data(), blendAB.data(), cm);
  }
  {
    auto dest = b;
    auto src = a;
    splashOutBlendExclusion(src.data(), dest.data(), blendBA.data(), cm);
  }

  EXPECT_EQ(blendAB, blendBA);
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_ComputesExpectedBlendAndRestoresInputs_1587) {
  const SplashColorMode cm = splashModeCMYK8;
  ASSERT_EQ(nComps(cm), 4);

  auto dest = makeColor(cm, {10, 20, 30, 40});
  auto src  = makeColor(cm, {50, 60, 70, 80});
  std::vector<uint8_t> blend(dest.size(), 0);

  const auto destBefore = dest;
  const auto srcBefore  = src;

  splashOutBlendExclusion(src.data(), dest.data(), blend.data(), cm);

  // Golden expected values for these specific CMYK inputs.
  EXPECT_EQ(blend[0], 198);
  EXPECT_EQ(blend[1], 184);
  EXPECT_EQ(blend[2], 171);
  EXPECT_EQ(blend[3], 160);

  // CMYK path temporarily mutates src/dest but should restore them before returning.
  EXPECT_EQ(dest, destBefore);
  EXPECT_EQ(src, srcBefore);
}

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_ExtraComponentsBothZeroForcesBlendToZero_1587) {
  const SplashColorMode cm = splashModeDeviceN8;
  const int comps = nComps(cm);
  if (comps <= 4) {
    GTEST_SKIP() << "splashModeDeviceN8 has <= 4 components in this build; extra-component rule not applicable.";
  }

  std::vector<uint8_t> dest(static_cast<size_t>(comps), 0);
  std::vector<uint8_t> src(static_cast<size_t>(comps), 0);
  std::vector<uint8_t> blend(static_cast<size_t>(comps), 255);

  // Fill first 4 components with non-trivial values.
  dest[0] = 10; dest[1] = 20; dest[2] = 30; dest[3] = 40;
  src[0]  = 50; src[1]  = 60; src[2]  = 70; src[3]  = 80;

  // For an extra component (>=4), set both src/dest to 0 to trigger the special rule.
  dest[4] = 0;
  src[4]  = 0;

  // Another extra component with non-zero values (should not be forced to 0 by the special rule).
  if (comps > 5) {
    dest[5] = 7;
    src[5]  = 9;
  }

  const auto destBefore = dest;
  const auto srcBefore  = src;

  splashOutBlendExclusion(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(blend[4], 0) << "DeviceN extra component with both inputs 0 must yield blend 0.";

  // Inputs should be restored after call.
  EXPECT_EQ(dest, destBefore);
  EXPECT_EQ(src, srcBefore);

  // Sanity: output components remain in valid byte range (vector stores uint8_t).
  for (int i = 0; i < comps; ++i) {
    EXPECT_LE(blend[static_cast<size_t>(i)], 255);
  }
}

} // namespace