// TEST_ID: 1580
// Unit tests for splashOutBlendDarken (static function in SplashOutputDev.cc)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "splash/SplashTypes.h"

// Include the implementation file to access the TU-local static function.
// This is a common unit-testing technique for static helpers.
#include "poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendDarkenTest_1580 : public ::testing::Test {
protected:
  static int NComps(SplashColorMode cm) { return splashColorModeNComps[cm]; }

  static std::vector<unsigned char> MakeColor(SplashColorMode cm,
                                              std::initializer_list<int> comps) {
    std::vector<unsigned char> v(NComps(cm), 0);
    int i = 0;
    for (int c : comps) {
      if (i >= static_cast<int>(v.size())) break;
      v[i++] = static_cast<unsigned char>(std::clamp(c, 0, 255));
    }
    return v;
  }

  static std::vector<unsigned char> MakePattern(SplashColorMode cm,
                                                unsigned char start,
                                                unsigned char step) {
    std::vector<unsigned char> v(NComps(cm), 0);
    unsigned int x = start;
    for (size_t i = 0; i < v.size(); ++i) {
      v[i] = static_cast<unsigned char>(x & 0xFF);
      x = (x + step) & 0xFF;
    }
    return v;
  }
};

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_BlendIsComponentwiseMinAndInputsUnchanged_1580) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(NComps(cm), 3);

  auto src  = MakeColor(cm, {10, 200, 30});
  auto dest = MakeColor(cm, {20, 100, 40});
  auto blend = MakeColor(cm, {0, 0, 0});

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDarken(src.data(), dest.data(), blend.data(), cm);

  // Inputs should not be mutated (observable behavior for callers).
  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  // For an additive model like RGB, "Darken" is expected to pick the darker (min) componentwise.
  for (int i = 0; i < NComps(cm); ++i) {
    const unsigned char expected = std::min(src_before[i], dest_before[i]);
    EXPECT_EQ(blend[i], expected) << "component " << i;
    EXPECT_TRUE(blend[i] == src_before[i] || blend[i] == dest_before[i]) << "component " << i;
    EXPECT_LE(blend[i], src_before[i]) << "component " << i;
    EXPECT_LE(blend[i], dest_before[i]) << "component " << i;
  }
}

TEST_F(SplashOutBlendDarkenTest_1580, RGB8_BoundaryValues_1580) {
  const SplashColorMode cm = splashModeRGB8;
  ASSERT_EQ(NComps(cm), 3);

  auto src  = MakeColor(cm, {0, 255, 0});
  auto dest = MakeColor(cm, {255, 0, 128});
  auto blend = MakeColor(cm, {123, 123, 123}); // overwritten

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDarken(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  EXPECT_EQ(blend[0], 0u);   // min(0,255)
  EXPECT_EQ(blend[1], 0u);   // min(255,0)
  EXPECT_EQ(blend[2], 0u);   // min(0,128)
}

TEST_F(SplashOutBlendDarkenTest_1580, CMYK8_BlendIsComponentwiseMaxAndInputsUnchanged_1580) {
  const SplashColorMode cm = splashModeCMYK8;
  ASSERT_EQ(NComps(cm), 4);

  auto src  = MakeColor(cm, {10, 200, 30, 90});
  auto dest = MakeColor(cm, {20, 100, 40, 10});
  auto blend = MakeColor(cm, {0, 0, 0, 0});

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDarken(src.data(), dest.data(), blend.data(), cm);

  // Inputs should be restored/unchanged for callers.
  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  // For a subtractive model like CMYK, "Darken" corresponds to higher ink coverage (max).
  for (int i = 0; i < NComps(cm); ++i) {
    const unsigned char expected = std::max(src_before[i], dest_before[i]);
    EXPECT_EQ(blend[i], expected) << "component " << i;
    EXPECT_TRUE(blend[i] == src_before[i] || blend[i] == dest_before[i]) << "component " << i;
    EXPECT_GE(blend[i], src_before[i]) << "component " << i;
    EXPECT_GE(blend[i], dest_before[i]) << "component " << i;
  }
}

TEST_F(SplashOutBlendDarkenTest_1580, DeviceN8_RespectsComponentCountAndInputsUnchanged_1580) {
  const SplashColorMode cm = splashModeDeviceN8;
  const int n = NComps(cm);
  ASSERT_GT(n, 0);

  auto src  = MakePattern(cm, /*start=*/5, /*step=*/37);
  auto dest = MakePattern(cm, /*start=*/250, /*step=*/19);
  std::vector<unsigned char> blend(n, 0);

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendDarken(src.data(), dest.data(), blend.data(), cm);

  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  // Same expectation as other subtractive-like modes: componentwise max.
  for (int i = 0; i < n; ++i) {
    const unsigned char expected = std::max(src_before[i], dest_before[i]);
    EXPECT_EQ(blend[i], expected) << "component " << i;
  }
}

} // namespace