// SplashOutBlendHueTest_1592.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// Bring in SplashColorMode.
#include "./TestProjects/poppler/splash/SplashTypes.h"

// NOTE: splashOutBlendHue is a static function in SplashOutputDev.cc.
// To test it as a black box without re-implementing logic, we include the .cc
// so the static symbol is in the same translation unit as these tests.
#include "./TestProjects/poppler/poppler/SplashOutputDev.cc"

namespace {

using Byte = unsigned char;

constexpr Byte kSentinel = 0xAA;

struct SplashOutBlendHueTest_1592 : public ::testing::Test {
  static std::array<Byte, 4> MakeColor(Byte c0, Byte c1, Byte c2, Byte c3) {
    return {c0, c1, c2, c3};
  }
};

TEST_F(SplashOutBlendHueTest_1592, Mono8_WritesOnlyFirstComponent_1592) {
  auto src = MakeColor(/*c0=*/10, /*c1=*/kSentinel, /*c2=*/kSentinel, /*c3=*/kSentinel);
  auto dest = MakeColor(/*c0=*/200, /*c1=*/kSentinel, /*c2=*/kSentinel, /*c3=*/kSentinel);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, kSentinel);

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeMono8);

  // For mono modes, the implementation writes via &blend[0] only.
  EXPECT_NE(blend[0], kSentinel);
  EXPECT_EQ(blend[1], kSentinel);
  EXPECT_EQ(blend[2], kSentinel);
  EXPECT_EQ(blend[3], kSentinel);
}

TEST_F(SplashOutBlendHueTest_1592, Mono1_BoundaryInputs_NoExtraWrites_1592) {
  auto src = MakeColor(/*c0=*/0, /*c1=*/kSentinel, /*c2=*/kSentinel, /*c3=*/kSentinel);
  auto dest = MakeColor(/*c0=*/255, /*c1=*/kSentinel, /*c2=*/kSentinel, /*c3=*/kSentinel);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, kSentinel);

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeMono1);

  EXPECT_NE(blend[0], kSentinel);
  EXPECT_EQ(blend[1], kSentinel);
  EXPECT_EQ(blend[2], kSentinel);
  EXPECT_EQ(blend[3], kSentinel);
}

TEST_F(SplashOutBlendHueTest_1592, RGB8_DoesNotTouchSrcAlpha_AndDoesNotWriteBlendAlpha_1592) {
  auto src = MakeColor(/*r=*/1, /*g=*/2, /*b=*/3, /*a=*/17);
  auto dest = MakeColor(/*r=*/200, /*g=*/150, /*b=*/100, /*a=*/99);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, /*a=*/0x5C);

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeRGB8);

  // In RGB8 path, src[3] is not modified.
  EXPECT_EQ(src[3], 17);

  // In RGB8 path, only blend[0..2] are written; blend[3] should remain unchanged.
  EXPECT_NE(blend[0], kSentinel);
  EXPECT_NE(blend[1], kSentinel);
  EXPECT_NE(blend[2], kSentinel);
  EXPECT_EQ(blend[3], static_cast<Byte>(0x5C));
}

TEST_F(SplashOutBlendHueTest_1592, BGR8_DoesNotWriteBlendAlpha_1592) {
  auto src = MakeColor(/*b=*/9, /*g=*/8, /*r=*/7, /*a=*/33);
  auto dest = MakeColor(/*b=*/100, /*g=*/110, /*r=*/120, /*a=*/44);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, /*a=*/0xC3);

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeBGR8);

  EXPECT_NE(blend[0], kSentinel);
  EXPECT_NE(blend[1], kSentinel);
  EXPECT_NE(blend[2], kSentinel);
  EXPECT_EQ(blend[3], static_cast<Byte>(0xC3));
  EXPECT_EQ(src[3], 33);  // BGR8 path does not touch src[3].
}

TEST_F(SplashOutBlendHueTest_1592, XBGR8_SetsSrcAlphaTo255_AndDoesNotWriteBlendAlpha_1592) {
  auto src = MakeColor(/*x/b=*/10, /*g=*/20, /*r=*/30, /*a=*/17);
  auto dest = MakeColor(/*x/b=*/200, /*g=*/150, /*r=*/100, /*a=*/99);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, /*a=*/0x11);

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeXBGR8);

  // Implementation explicitly forces src[3] = 255 in splashModeXBGR8.
  EXPECT_EQ(src[3], 255);

  // XBGR8 then falls through to RGB/BGR handling and writes only blend[0..2].
  EXPECT_NE(blend[0], kSentinel);
  EXPECT_NE(blend[1], kSentinel);
  EXPECT_NE(blend[2], kSentinel);
  EXPECT_EQ(blend[3], static_cast<Byte>(0x11));
}

TEST_F(SplashOutBlendHueTest_1592, CMYK8_PreservesDestFourthComponentIntoBlend_1592) {
  auto src = MakeColor(/*c=*/12, /*m=*/34, /*y=*/56, /*k=*/78);
  auto dest = MakeColor(/*c=*/210, /*m=*/220, /*y=*/230, /*k=*/240);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, kSentinel);

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeCMYK8);

  // Observable behavior in this mode: blend[3] is set based on dest[3] path and ends up equal to dest[3].
  EXPECT_EQ(blend[3], dest_before[3]);

  // Function should not mutate input buffers in CMYK path (uses local src2/dest2).
  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);
}

TEST_F(SplashOutBlendHueTest_1592, DeviceN8_PreservesDestFourthComponentIntoBlend_AndHandlesBoundaries_1592) {
  auto src = MakeColor(/*0=*/0, /*1=*/255, /*2=*/0, /*3=*/255);
  auto dest = MakeColor(/*0=*/255, /*1=*/0, /*2=*/255, /*3=*/0);
  auto blend = MakeColor(kSentinel, kSentinel, kSentinel, kSentinel);

  const auto src_before = src;
  const auto dest_before = dest;

  splashOutBlendHue(src.data(), dest.data(), blend.data(), splashModeDeviceN8);

  EXPECT_EQ(blend[3], dest_before[3]);
  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  // Only requirement here is that the first three channels are written to something (black-box).
  EXPECT_NE(blend[0], kSentinel);
  EXPECT_NE(blend[1], kSentinel);
  EXPECT_NE(blend[2], kSentinel);
}

}  // namespace