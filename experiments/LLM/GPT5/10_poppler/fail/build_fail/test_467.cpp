// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for GfxIndexedColorSpace::useGetCMYKLine()
// TEST_ID: 467

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

// A minimal concrete GfxColorSpace implementation to satisfy GfxIndexedColorSpace's
// constructor dependency (external collaborator). Behavior is intentionally trivial.
class DummyColorSpaceForIndexed_467 final : public GfxColorSpace {
public:
  ~DummyColorSpaceForIndexed_467() override = default;

  std::unique_ptr<GfxColorSpace> copy() override {
    return std::make_unique<DummyColorSpaceForIndexed_467>();
  }

  void getGray(const GfxColor * /*color*/, GfxGray *gray) override {
    if (gray) {
      *gray = 0;
    }
  }

  void getRGB(const GfxColor * /*color*/, GfxRGB *rgb) override {
    if (rgb) {
      rgb->r = 0;
      rgb->g = 0;
      rgb->b = 0;
    }
  }

  void getCMYK(const GfxColor * /*color*/, GfxCMYK *cmyk) override {
    if (cmyk) {
      cmyk->c = 0;
      cmyk->m = 0;
      cmyk->y = 0;
      cmyk->k = 0;
    }
  }

  void getDeviceN(const GfxColor * /*color*/, GfxColor * /*deviceN*/) override {}

  void getRGBLine(unsigned char * /*in*/, unsigned int * /*out*/, int /*length*/) override {}
  void getRGBLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getRGBXLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getCMYKLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getDeviceNLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}

  void getDefaultColor(GfxColor * /*color*/) override {}
  void getDefaultRanges(double * /*decodeLow*/, double * /*decodeRange*/, int /*maxImgPixel*/) override {}

  GfxColorSpaceMode getMode() const override { return csDeviceGray; }

  bool useGetRGBLine() const override { return false; }
  bool useGetCMYKLine() const override { return false; }
  bool useGetDeviceNLine() const override { return false; }

  int getNComps() const override { return 1; }
};

class GfxIndexedColorSpaceTest_467 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxIndexedColorSpace> MakeIndexed(int indexHigh) {
    auto base = std::make_unique<DummyColorSpaceForIndexed_467>();
    return std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
  }
};

TEST_F(GfxIndexedColorSpaceTest_467, UseGetCMYKLineAlwaysTrue_467) {
  auto cs = MakeIndexed(/*indexHigh=*/0);
  ASSERT_NE(cs, nullptr);

  EXPECT_TRUE(cs->useGetCMYKLine());
}

TEST_F(GfxIndexedColorSpaceTest_467, UseGetCMYKLineWorksOnConstObject_467) {
  const auto cs = MakeIndexed(/*indexHigh=*/255);
  ASSERT_NE(cs, nullptr);

  const GfxIndexedColorSpace &ref = *cs;
  EXPECT_TRUE(ref.useGetCMYKLine());
}

TEST_F(GfxIndexedColorSpaceTest_467, UseGetCMYKLineIndependentOfIndexHigh_467) {
  auto csLow = MakeIndexed(/*indexHigh=*/0);
  auto csMid = MakeIndexed(/*indexHigh=*/128);
  auto csHigh = MakeIndexed(/*indexHigh=*/1024);

  ASSERT_NE(csLow, nullptr);
  ASSERT_NE(csMid, nullptr);
  ASSERT_NE(csHigh, nullptr);

  EXPECT_TRUE(csLow->useGetCMYKLine());
  EXPECT_TRUE(csMid->useGetCMYKLine());
  EXPECT_TRUE(csHigh->useGetCMYKLine());
}