// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 459
//
// Unit tests for GfxICCBasedColorSpace::getMode()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "GfxState.h"

// A minimal concrete GfxColorSpace used only as a collaborator for constructing
// GfxICCBasedColorSpace. Behavior is intentionally trivial and does not attempt
// to emulate Poppler internals.
class DummyAltColorSpace final : public GfxColorSpace {
public:
  DummyAltColorSpace() = default;
  ~DummyAltColorSpace() override = default;

  GfxColorSpaceMode getMode() const override { return csDeviceRGB; }
  int getNComps() const override { return 3; }

  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<DummyAltColorSpace>();
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
  void getDeviceN(const GfxColor *color, GfxColor *deviceN) override {
    if (deviceN && color) {
      *deviceN = *color;
    }
  }

  void getRGBLine(unsigned char * /*in*/, unsigned int *out, int length) override {
    if (!out || length <= 0) {
      return;
    }
    for (int i = 0; i < length; ++i) {
      out[i] = 0;
    }
  }
  void getRGBLine(unsigned char * /*in*/, unsigned char *out, int length) override {
    if (!out || length <= 0) {
      return;
    }
    for (int i = 0; i < length * 3; ++i) {
      out[i] = 0;
    }
  }
  void getRGBXLine(unsigned char * /*in*/, unsigned char *out, int length) override {
    if (!out || length <= 0) {
      return;
    }
    for (int i = 0; i < length * 4; ++i) {
      out[i] = 0;
    }
  }
  void getCMYKLine(unsigned char * /*in*/, unsigned char *out, int length) override {
    if (!out || length <= 0) {
      return;
    }
    for (int i = 0; i < length * 4; ++i) {
      out[i] = 0;
    }
  }
  void getDeviceNLine(unsigned char * /*in*/, unsigned char *out, int length) override {
    if (!out || length <= 0) {
      return;
    }
    for (int i = 0; i < length; ++i) {
      out[i] = 0;
    }
  }

  bool useGetRGBLine() const override { return false; }
  bool useGetCMYKLine() const override { return false; }
  bool useGetDeviceNLine() const override { return false; }

  void getDefaultColor(GfxColor *color) const override {
    if (!color) {
      return;
    }
    // Keep this minimal: set all components to 0.
    for (int i = 0; i < gfxColorMaxComps; ++i) {
      color->c[i] = 0;
    }
  }

  void getDefaultRanges(double *decodeLow, double *decodeRange, int maxImgPixel) const override {
    (void)maxImgPixel;
    if (decodeLow) {
      for (int i = 0; i < 4; ++i) {
        decodeLow[i] = 0.0;
      }
    }
    if (decodeRange) {
      for (int i = 0; i < 4; ++i) {
        decodeRange[i] = 0.0;
      }
    }
  }
};

class GfxICCBasedColorSpaceTest_459 : public ::testing::Test {
protected:
  static Ref MakeNullRef() {
    Ref r;
    r.num = 0;
    r.gen = 0;
    return r;
  }
};

TEST_F(GfxICCBasedColorSpaceTest_459, GetModeReturnsCsICCBased_459) {
  Ref ref = MakeNullRef();
  auto alt = std::make_unique<DummyAltColorSpace>();

  // Construct the ICCBased colorspace using a minimal alternate colorspace.
  GfxICCBasedColorSpace cs(/*nCompsA=*/3, std::move(alt), &ref);

  EXPECT_EQ(cs.getMode(), csICCBased);
}

TEST_F(GfxICCBasedColorSpaceTest_459, GetModeViaBasePointerReturnsCsICCBased_459) {
  Ref ref = MakeNullRef();
  auto alt = std::make_unique<DummyAltColorSpace>();
  GfxICCBasedColorSpace cs(/*nCompsA=*/3, std::move(alt), &ref);

  // Verify observable behavior through the base interface (polymorphism).
  const GfxColorSpace *base = &cs;
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getMode(), csICCBased);
}

TEST_F(GfxICCBasedColorSpaceTest_459, GetModeIsStableAcrossMultipleInstances_459) {
  Ref ref1 = MakeNullRef();
  Ref ref2 = MakeNullRef();

  auto alt1 = std::make_unique<DummyAltColorSpace>();
  auto alt2 = std::make_unique<DummyAltColorSpace>();

  GfxICCBasedColorSpace cs1(/*nCompsA=*/3, std::move(alt1), &ref1);
  GfxICCBasedColorSpace cs2(/*nCompsA=*/3, std::move(alt2), &ref2);

  EXPECT_EQ(cs1.getMode(), csICCBased);
  EXPECT_EQ(cs2.getMode(), csICCBased);
}