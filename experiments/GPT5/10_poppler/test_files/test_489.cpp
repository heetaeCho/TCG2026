// TEST_ID = 489
// File: gfx_pattern_colorspace_getunder_test_489.cpp

#include <gtest/gtest.h>

#include <memory>

#include "GfxState.h"

// A minimal concrete GfxColorSpace we can own via std::unique_ptr and pass into
// GfxPatternColorSpace, without relying on any internal behavior.
class DummyColorSpace_489 final : public GfxColorSpace {
public:
  DummyColorSpace_489() = default;
  ~DummyColorSpace_489() override = default;

  std::unique_ptr<GfxColorSpace> copy() override {
    return std::make_unique<DummyColorSpace_489>();
  }

  void getGray(const GfxColor * /*color*/, GfxGray * /*gray*/) override {}
  void getRGB(const GfxColor * /*color*/, GfxRGB * /*rgb*/) override {}
  void getCMYK(const GfxColor * /*color*/, GfxCMYK * /*cmyk*/) override {}
  void getDeviceN(const GfxColor * /*color*/, GfxColor * /*deviceN*/) override {}
  void getDefaultColor(GfxColor * /*color*/) override {}

  GfxColorSpaceMode getMode() const override {
    return static_cast<GfxColorSpaceMode>(0);
  }

  int getNComps() const override { return 1; }
};

class GfxPatternColorSpaceTest_489 : public ::testing::Test {};

TEST_F(GfxPatternColorSpaceTest_489, GetUnderReturnsNullWhenConstructedWithNull_489) {
  std::unique_ptr<GfxColorSpace> under;
  GfxPatternColorSpace cs(std::move(under));

  EXPECT_EQ(cs.getUnder(), nullptr);
  EXPECT_EQ(cs.getUnder(), nullptr); // repeated call should be stable
}

TEST_F(GfxPatternColorSpaceTest_489, GetUnderReturnsSamePointerPassedIn_489) {
  auto under = std::make_unique<DummyColorSpace_489>();
  GfxColorSpace *raw = under.get();

  GfxPatternColorSpace cs(std::move(under));

  EXPECT_EQ(under.get(), nullptr);     // ownership moved
  EXPECT_EQ(cs.getUnder(), raw);       // observable behavior: returns underlying pointer
  EXPECT_EQ(cs.getUnder(), raw);       // repeated call stable
  EXPECT_NE(cs.getUnder(), nullptr);   // boundary: not null when provided
}

TEST_F(GfxPatternColorSpaceTest_489, GetUnderDoesNotChangeAcrossMultipleCalls_489) {
  auto under = std::make_unique<DummyColorSpace_489>();
  GfxColorSpace *raw = under.get();

  GfxPatternColorSpace cs(std::move(under));

  GfxColorSpace *p1 = cs.getUnder();
  GfxColorSpace *p2 = cs.getUnder();
  GfxColorSpace *p3 = cs.getUnder();

  EXPECT_EQ(p1, raw);
  EXPECT_EQ(p2, raw);
  EXPECT_EQ(p3, raw);
}