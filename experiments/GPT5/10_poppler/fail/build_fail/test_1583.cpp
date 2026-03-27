// SplashOutputDev_splashOutBlendColorBurn_ut_1583.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

// Poppler/Splash headers (provide SplashColorMode, SplashColorPtr, splashColorModeNComps, etc.)
#include "splash/SplashTypes.h"

// The function under test is `static` in SplashOutputDev.cc (internal linkage).
// Include the implementation file directly so the test TU can call it.
#include "poppler/SplashOutputDev.cc"

namespace {

class SplashOutBlendColorBurnTest_1583 : public ::testing::Test {
protected:
  static std::vector<unsigned char> MakeVec(int n, unsigned char fill = 0) {
    return std::vector<unsigned char>(std::max(0, n), fill);
  }
};

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_ComputesExpectedForSimpleKnownCases_1583) {
  const int n = splashColorModeNComps[splashModeRGB8];
  ASSERT_GE(n, 3);

  std::vector<unsigned char> src = MakeVec(n);
  std::vector<unsigned char> dest = MakeVec(n);
  std::vector<unsigned char> blend = MakeVec(n, 0xAA);

  // Choose values where expected results are unambiguous from interface behavior:
  // - dest=255 => (255-dest)=0 => x=0 => blend=255 (when src != 0)
  // - dest=0 and src=128 => x becomes >255 => blend=0
  // - dest=254 and src=1 => x=255 => blend=0
  src[0] = 255; dest[0] = 255;
  src[1] = 128; dest[1] = 0;
  src[2] = 1;   dest[2] = 254;

  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeRGB8);

  EXPECT_EQ(blend[0], 255);
  EXPECT_EQ(blend[1], 0);
  EXPECT_EQ(blend[2], 0);

  // For non-CMYK / non-DeviceN modes, src/dest should not be modified by the call.
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_SrcZeroForcesBlendZeroAndDoesNotModifyInputs_1583) {
  const int n = splashColorModeNComps[splashModeRGB8];
  ASSERT_GE(n, 3);

  std::vector<unsigned char> src = MakeVec(n, 0);
  std::vector<unsigned char> dest = MakeVec(n);
  std::vector<unsigned char> blend = MakeVec(n, 0xCC);

  dest[0] = 0;
  dest[1] = 128;
  dest[2] = 255;

  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeRGB8);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0);
  }
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);
}

TEST_F(SplashOutBlendColorBurnTest_1583, RGB8_Dest255WithNonZeroSrcProduces255_1583) {
  const int n = splashColorModeNComps[splashModeRGB8];
  ASSERT_GE(n, 3);

  std::vector<unsigned char> src = MakeVec(n);
  std::vector<unsigned char> dest = MakeVec(n, 255);
  std::vector<unsigned char> blend = MakeVec(n, 0);

  // Ensure all src comps non-zero.
  for (int i = 0; i < n; ++i) {
    src[i] = static_cast<unsigned char>(i + 1);
  }

  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeRGB8);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 255);
  }
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_All255SrcProducesAll255BlendAndRestoresInputs_1583) {
  const int n = splashColorModeNComps[splashModeCMYK8];
  ASSERT_GE(n, 4);

  std::vector<unsigned char> src = MakeVec(n, 255);
  std::vector<unsigned char> dest = MakeVec(n);
  std::vector<unsigned char> blend = MakeVec(n, 0x11);

  // Vary dest to ensure output behavior is not dependent on it for this specific case.
  dest[0] = 0;
  dest[1] = 64;
  dest[2] = 128;
  dest[3] = 255;

  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeCMYK8);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 255);
  }

  // CMYK path temporarily transforms src/dest, but should restore them before returning.
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);
}

TEST_F(SplashOutBlendColorBurnTest_1583, CMYK8_SpecificCornerCaseCanProduceZeroBlend_1583) {
  const int n = splashColorModeNComps[splashModeCMYK8];
  ASSERT_GE(n, 4);

  std::vector<unsigned char> src = MakeVec(n, 0);
  std::vector<unsigned char> dest = MakeVec(n, 0);
  std::vector<unsigned char> blend = MakeVec(n, 0x77);

  // This specific setup is chosen to exercise a boundary where output is deterministically 0
  // for at least one component (without requiring inspection of private state).
  // Keep remaining components at 0 as well.
  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeCMYK8);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0);
  }
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);
}

TEST_F(SplashOutBlendColorBurnTest_1583, DeviceN8_DoesNotWritePastNCompsAndRestoresInputs_1583) {
  const int n = splashColorModeNComps[splashModeDeviceN8];
  ASSERT_GT(n, 0);

  // Allocate extra sentinel bytes after the active component range to detect overruns.
  std::vector<unsigned char> src = MakeVec(n + 2, 10);
  std::vector<unsigned char> dest = MakeVec(n + 2, 200);
  std::vector<unsigned char> blend = MakeVec(n + 2, 0x5A);

  const unsigned char srcSent1 = 0xE1, srcSent2 = 0xE2;
  const unsigned char dstSent1 = 0xD1, dstSent2 = 0xD2;
  const unsigned char bldSent1 = 0xB1, bldSent2 = 0xB2;

  src[n] = srcSent1;   src[n + 1] = srcSent2;
  dest[n] = dstSent1;  dest[n + 1] = dstSent2;
  blend[n] = bldSent1; blend[n + 1] = bldSent2;

  // Ensure active src comps are non-zero to avoid the src==0 branch dominating.
  for (int i = 0; i < n; ++i) {
    src[i] = static_cast<unsigned char>((i % 254) + 1);
    dest[i] = static_cast<unsigned char>(i * 17);
  }

  const auto srcBefore = src;
  const auto destBefore = dest;

  splashOutBlendColorBurn(src.data(), dest.data(), blend.data(), splashModeDeviceN8);

  // Sentinels must remain unchanged (no out-of-bounds writes).
  EXPECT_EQ(src[n], srcSent1);
  EXPECT_EQ(src[n + 1], srcSent2);
  EXPECT_EQ(dest[n], dstSent1);
  EXPECT_EQ(dest[n + 1], dstSent2);
  EXPECT_EQ(blend[n], bldSent1);
  EXPECT_EQ(blend[n + 1], bldSent2);

  // DeviceN path temporarily transforms src/dest, but should restore them before returning.
  EXPECT_EQ(src, srcBefore);
  EXPECT_EQ(dest, destBefore);

  // Output components should stay in byte range by type; spot-check they changed from sentinel
  // initialization in the active range (not all still 0x5A unless by coincidence).
  bool anyChanged = false;
  for (int i = 0; i < n; ++i) {
    if (blend[i] != 0x5A) {
      anyChanged = true;
      break;
    }
  }
  EXPECT_TRUE(anyChanged);
}

} // namespace