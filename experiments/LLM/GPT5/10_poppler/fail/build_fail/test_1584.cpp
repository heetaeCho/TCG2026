// SplashOutBlendHardLight_tests_1584.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

// Include the implementation TU to access the file-local static function.
// This is a common unit-testing technique for testing internal helpers.
#include "SplashOutputDev.cc"

namespace {

using Byte = unsigned char;

class SplashOutBlendHardLightTest_1584 : public ::testing::Test {
protected:
  static constexpr int kBufSize = 8;

  static void FillSentinels(std::array<Byte, kBufSize> &a, Byte v) {
    a.fill(v);
  }

  static void ExpectPrefixEq(const std::array<Byte, kBufSize> &a,
                             const std::array<Byte, kBufSize> &b,
                             int n) {
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(a[i], b[i]) << "index " << i;
    }
  }

  static void ExpectSuffixEq(const std::array<Byte, kBufSize> &a,
                             Byte sentinel,
                             int start) {
    for (int i = start; i < kBufSize; ++i) {
      EXPECT_EQ(a[i], sentinel) << "index " << i;
    }
  }

  static int NumComps(SplashColorMode cm) {
    const int n = splashColorModeNComps[cm];
    EXPECT_GE(n, 1);
    EXPECT_LE(n, kBufSize);
    return n;
  }
};

TEST_F(SplashOutBlendHardLightTest_1584, SrcZeroProducesZeroBlend_Mono8_1584) {
  const SplashColorMode cm = splashModeMono8;
  const int n = NumComps(cm);

  std::array<Byte, kBufSize> src, dest, blend;
  FillSentinels(src, 0x00);
  FillSentinels(dest, 0x7B);   // arbitrary
  FillSentinels(blend, 0xAA);  // sentinel

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior: src==0 should yield blend==0 (per-channel).
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0x00) << "index " << i;
  }
  ExpectSuffixEq(blend, 0xAA, n);

  // The helper should not leave src/dest mutated for this mode.
  ExpectPrefixEq(src, src_before, n);
  ExpectPrefixEq(dest, dest_before, n);
}

TEST_F(SplashOutBlendHardLightTest_1584, SrcMaxProducesMaxBlend_RGB8_1584) {
  const SplashColorMode cm = splashModeRGB8;
  const int n = NumComps(cm);

  std::array<Byte, kBufSize> src, dest, blend;
  FillSentinels(src, 0xFF);
  // Use different dest values to ensure per-channel computation.
  FillSentinels(dest, 0xAA);
  dest[0] = 0x00;
  dest[1] = 0x80;
  dest[2] = 0xFF;
  FillSentinels(blend, 0xCC);  // sentinel

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior: src==255 should yield blend==255 (per-channel).
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0xFF) << "index " << i;
  }
  ExpectSuffixEq(blend, 0xCC, n);

  // src/dest should not be modified for this mode.
  ExpectPrefixEq(src, src_before, n);
  ExpectPrefixEq(dest, dest_before, n);
}

TEST_F(SplashOutBlendHardLightTest_1584, KnownPoint_DestZeroSrc128_YieldsOne_RGB8_1584) {
  const SplashColorMode cm = splashModeRGB8;
  const int n = NumComps(cm);

  std::array<Byte, kBufSize> src, dest, blend;
  FillSentinels(src, 0x80);   // 128
  FillSentinels(dest, 0x00);  // 0
  FillSentinels(blend, 0x5A); // sentinel

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  // For dest=0, src=128, the blend result is expected to be 1 (per-channel).
  // This is a boundary-adjacent point around the 0x80 threshold.
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0x01) << "index " << i;
  }
  ExpectSuffixEq(blend, 0x5A, n);

  ExpectPrefixEq(src, src_before, n);
  ExpectPrefixEq(dest, dest_before, n);
}

TEST_F(SplashOutBlendHardLightTest_1584, CmykMode_DoesNotLeaveSrcDestMutated_1584) {
  const SplashColorMode cm = splashModeCMYK8;
  const int n = NumComps(cm);

  std::array<Byte, kBufSize> src, dest, blend;
  // Use varied values across first 4 components.
  FillSentinels(src, 0x11);
  FillSentinels(dest, 0x22);
  src[0] = 0x00;
  src[1] = 0x7F;
  src[2] = 0x80;
  src[3] = 0xFF;
  dest[0] = 0x10;
  dest[1] = 0x20;
  dest[2] = 0x30;
  dest[3] = 0x40;
  FillSentinels(blend, 0xE3); // sentinel

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  // Observable behavior: regardless of internal transforms, the function should not
  // leave the input buffers changed after it returns.
  ExpectPrefixEq(src, src_before, n);
  ExpectPrefixEq(dest, dest_before, n);

  // Only first N components should be written in blend.
  ExpectSuffixEq(blend, 0xE3, n);
}

TEST_F(SplashOutBlendHardLightTest_1584, CmykMode_SrcZeroStillProducesZeroBlend_1584) {
  const SplashColorMode cm = splashModeCMYK8;
  const int n = NumComps(cm);

  std::array<Byte, kBufSize> src, dest, blend;
  FillSentinels(src, 0x00);
  FillSentinels(dest, 0x9C);   // arbitrary
  FillSentinels(blend, 0xA7);  // sentinel

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(blend[i], 0x00) << "index " << i;
  }
  ExpectSuffixEq(blend, 0xA7, n);
}

TEST_F(SplashOutBlendHardLightTest_1584, WritesExactlyNComponents_Mono8_1584) {
  const SplashColorMode cm = splashModeMono8;
  const int n = NumComps(cm);
  ASSERT_EQ(n, 1) << "Mono8 is expected to have exactly 1 component";

  std::array<Byte, kBufSize> src, dest, blend;
  FillSentinels(src, 0x40);
  FillSentinels(dest, 0xC0);
  FillSentinels(blend, 0xFE); // sentinel

  splashOutBlendHardLight(src.data(), dest.data(), blend.data(), cm);

  // First component should be written to something in [0,255] (Byte always is),
  // and the rest must remain sentinel.
  ExpectSuffixEq(blend, 0xFE, /*start=*/1);
}

} // namespace