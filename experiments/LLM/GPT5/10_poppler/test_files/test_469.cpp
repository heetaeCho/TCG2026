// TEST_ID 469
// Unit tests for GfxIndexedColorSpace::getNComps()
// File: gfx_indexed_colorspace_getncomps_test_469.cc

#include <gtest/gtest.h>

#include <memory>

// Include the real header from the codebase under test.
#include "poppler/GfxState.h"

// A minimal external collaborator used only to satisfy construction of
// GfxIndexedColorSpace in a black-box manner.
//
// NOTE: This is *not* re-implementing GfxIndexedColorSpace logic.
// It is a stub for the dependency passed into the constructor.
class DummyColorSpaceForIndexed_469 final : public GfxColorSpace {
public:
  explicit DummyColorSpaceForIndexed_469(int nComps) : nComps_(nComps) {}
  ~DummyColorSpaceForIndexed_469() override = default;

  std::unique_ptr<GfxColorSpace> copy() override {
    return std::make_unique<DummyColorSpaceForIndexed_469>(nComps_);
  }

  void getGray(const GfxColor *, GfxGray *) override {}
  void getRGB(const GfxColor *, GfxRGB *) override {}
  void getCMYK(const GfxColor *, GfxCMYK *) override {}
  void getDeviceN(const GfxColor *, GfxColor *) override {}

  void getRGBLine(unsigned char *, unsigned int *, int) override {}
  void getRGBLine(unsigned char *, unsigned char *, int) override {}
  void getRGBXLine(unsigned char *, unsigned char *, int) override {}
  void getCMYKLine(unsigned char *, unsigned char *, int) override {}
  void getDeviceNLine(unsigned char *, unsigned char *, int) override {}

  void getDefaultColor(GfxColor *) override {}
  void getDefaultRanges(double *, double *, int) override {}

  GfxColorSpaceMode getMode() const override { return csDeviceGray; }
  bool useGetRGBLine() const override { return false; }
  bool useGetCMYKLine() const override { return false; }
  bool useGetDeviceNLine() const override { return false; }
  int getNComps() const override { return nComps_; }

  unsigned int getOverprintMask() const override { return 0u; }

  void createMapping(std::vector<std::unique_ptr<GfxSeparationColorSpace>> *,
                     size_t) override {}

private:
  int nComps_;
};

class GfxIndexedColorSpaceTest_469 : public ::testing::Test {};

TEST_F(GfxIndexedColorSpaceTest_469, GetNCompsAlwaysOne_469) {
  auto base = std::make_unique<DummyColorSpaceForIndexed_469>(3);
  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/255);

  EXPECT_EQ(cs.getNComps(), 1);
  EXPECT_EQ(cs.getNComps(), 1); // repeatability
}

TEST_F(GfxIndexedColorSpaceTest_469, GetNCompsIndependentOfBaseComps_469) {
  auto base1 = std::make_unique<DummyColorSpaceForIndexed_469>(1);
  GfxIndexedColorSpace cs1(std::move(base1), /*indexHighA=*/0);
  EXPECT_EQ(cs1.getNComps(), 1);

  auto base4 = std::make_unique<DummyColorSpaceForIndexed_469>(4);
  GfxIndexedColorSpace cs4(std::move(base4), /*indexHighA=*/4096);
  EXPECT_EQ(cs4.getNComps(), 1);
}

TEST_F(GfxIndexedColorSpaceTest_469, GetNCompsWorksOnConstInstance_469) {
  auto base = std::make_unique<DummyColorSpaceForIndexed_469>(2);
  const GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/128);

  EXPECT_EQ(cs.getNComps(), 1);
}

TEST_F(GfxIndexedColorSpaceTest_469, GetNCompsUnaffectedByIndexHighBoundaryValues_469) {
  {
    auto base = std::make_unique<DummyColorSpaceForIndexed_469>(3);
    GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/0);
    EXPECT_EQ(cs.getNComps(), 1);
  }
  {
    auto base = std::make_unique<DummyColorSpaceForIndexed_469>(3);
    GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/255);
    EXPECT_EQ(cs.getNComps(), 1);
  }
}