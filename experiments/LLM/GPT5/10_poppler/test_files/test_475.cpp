// Copyright (C) 2026
// Unit tests for GfxSeparationColorSpace::getMode
// TEST_ID: 475

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "GfxState.h" // From ./TestProjects/poppler/poppler/GfxState.h

// A minimal concrete GfxColorSpace used only as a constructor dependency.
// This is an external collaborator for the SUT; it should not try to emulate
// GfxSeparationColorSpace internals.
class DummyAltColorSpace final : public GfxColorSpace {
public:
  ~DummyAltColorSpace() override = default;

  GfxColorSpaceMode getMode() const override { return csDeviceRGB; }
  int getNComps() const override { return 3; }

  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<DummyAltColorSpace>();
  }

  void getGray(const GfxColor * /*color*/, GfxGray *gray) override {
    if (gray) *gray = 0;
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
  void getDeviceN(const GfxColor * /*color*/, GfxColor *deviceN) override {
    if (deviceN) {
      // Best-effort zero-initialize, respecting the compile-time array size.
      for (size_t i = 0; i < sizeof(deviceN->c) / sizeof(deviceN->c[0]); ++i) {
        deviceN->c[i] = 0;
      }
    }
  }

  void getDefaultColor(GfxColor *color) override {
    if (color) {
      for (size_t i = 0; i < sizeof(color->c) / sizeof(color->c[0]); ++i) {
        color->c[i] = 0;
      }
    }
  }

  void createMapping(std::vector<std::unique_ptr<GfxSeparationColorSpace>> * /*separationList*/,
                     size_t /*maxSepComps*/) override {
    // No-op for dummy.
  }
};

class GfxSeparationColorSpaceTest_475 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxSeparationColorSpace> MakeSutWithNullFunc() {
    auto name = std::make_unique<GooString>("SpotColor");
    auto alt = std::make_unique<DummyAltColorSpace>();

    // Constructor accepts std::unique_ptr<Function> by value in the provided signature;
    // passing nullptr is a boundary case (no function).
    std::unique_ptr<Function> func;
    return std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func));
  }
};

TEST_F(GfxSeparationColorSpaceTest_475, GetModeReturnsSeparation_475) {
  auto sut = MakeSutWithNullFunc();

  EXPECT_EQ(sut->getMode(), csSeparation);
}

TEST_F(GfxSeparationColorSpaceTest_475, GetModeWorksThroughBasePointer_475) {
  auto sut = MakeSutWithNullFunc();

  GfxColorSpace *asBase = sut.get();
  ASSERT_NE(asBase, nullptr);
  EXPECT_EQ(asBase->getMode(), csSeparation);
}

TEST_F(GfxSeparationColorSpaceTest_475, GetModeIsConstCallable_475) {
  auto sut = MakeSutWithNullFunc();

  const GfxSeparationColorSpace &cref = *sut;
  EXPECT_EQ(cref.getMode(), csSeparation);
}

TEST_F(GfxSeparationColorSpaceTest_475, GetModeUnaffectedByNullFunctionBoundary_475) {
  // Boundary/robustness: construct with a null Function dependency (if supported),
  // and verify observable behavior remains correct.
  auto sut = MakeSutWithNullFunc();

  EXPECT_EQ(sut->getMode(), csSeparation);
}