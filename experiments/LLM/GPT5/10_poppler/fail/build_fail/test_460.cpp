// -*- mode: c++; -*-
// Unit tests for GfxICCBasedColorSpace::getNComps
// TEST_ID: 460

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

// A minimal concrete GfxColorSpace implementation to satisfy the
// GfxICCBasedColorSpace constructor dependency ("alt" colorspace).
// This is an external collaborator for the class under test.
class DummyColorSpace_460 : public GfxColorSpace {
public:
  explicit DummyColorSpace_460(int nCompsA) : nComps_(nCompsA) {}
  ~DummyColorSpace_460() override = default;

  GfxColorSpaceMode getMode() const override { return csDeviceRGB; }
  int getNComps() const override { return nComps_; }

  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<DummyColorSpace_460>(nComps_);
  }

  void getGray(const GfxColor * /*color*/, GfxGray *gray) override {
    if (gray) {
      gray->c[0] = 0;
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

  bool useGetRGBLine() override { return false; }
  bool useGetCMYKLine() override { return false; }
  bool useGetDeviceNLine() override { return false; }

  void getDefaultColor(GfxColor *color) override {
    if (color) {
      for (int i = 0; i < gfxColorMaxComps; ++i) {
        color->c[i] = 0;
      }
    }
  }
  void getDefaultRanges(double *decodeLow, double *decodeRange, int /*maxImgPixel*/) override {
    if (decodeLow && decodeRange) {
      for (int i = 0; i < gfxColorMaxComps; ++i) {
        decodeLow[i] = 0.0;
        decodeRange[i] = 1.0;
      }
    }
  }

private:
  int nComps_;
};

class GfxICCBasedColorSpaceTest_460 : public ::testing::Test {
protected:
  static Ref MakeNullRef() {
    Ref r;
    r.num = 0;
    r.gen = 0;
    return r;
  }
};

TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsReturnsConstructorValue_460) {
  const Ref r = MakeNullRef();

  {
    auto alt = std::make_unique<DummyColorSpace_460>(3);
    GfxICCBasedColorSpace cs(/*nCompsA=*/1, std::move(alt), &r);
    EXPECT_EQ(cs.getNComps(), 1);
  }

  {
    auto alt = std::make_unique<DummyColorSpace_460>(3);
    GfxICCBasedColorSpace cs(/*nCompsA=*/4, std::move(alt), &r);
    EXPECT_EQ(cs.getNComps(), 4);
  }
}

TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsWithZeroComponents_Boundary_460) {
  const Ref r = MakeNullRef();

  auto alt = std::make_unique<DummyColorSpace_460>(3);

  // Boundary: nCompsA == 0. We only verify observable behavior via the interface.
  EXPECT_NO_THROW({
    GfxICCBasedColorSpace cs(/*nCompsA=*/0, std::move(alt), &r);
    EXPECT_EQ(cs.getNComps(), 0);
  });
}

TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsWithLargerComponentCount_Boundary_460) {
  const Ref r = MakeNullRef();

  auto alt = std::make_unique<DummyColorSpace_460>(3);

  // Boundary-ish: a larger component count than typical ICC-based spaces.
  GfxICCBasedColorSpace cs(/*nCompsA=*/32, std::move(alt), &r);
  EXPECT_EQ(cs.getNComps(), 32);
}